'''
source .venv/bin/activate
mpirun -n 3 python3.14 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt lorem
'''

'''
jezeli chcemy odpalic wiecej procesow niz watkow w procesorze, musimy uzyc flagi --oversubscribe dla mpirun

np.
mpirun --oversubscribe -n 8 python3.14 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt lorem
'''

from mpi4py import MPI
from abc import ABC, abstractmethod
from dataclasses import dataclass
import sys
import os
import time
import argparse


COMM = MPI.COMM_WORLD
RANK = COMM.Get_rank()
SIZE = COMM.Get_size()


class ISearchAlgorithm(ABC):
    @abstractmethod
    def setup(self):
        pass


    @abstractmethod
    def run(self):
        pass


class BruteForce(ISearchAlgorithm):
    def setup(self):
        pass


    def run(self):
        global WINNER, WINNER_INDEX

        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        search_key_index = 0

        file_index = 0

        start_index = APP_CONFIG.range[0]
        end_index = APP_CONFIG.range[1]

        chars_to_check = end_index - start_index

        comparison_counter = 0

        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            full_text = f.read()

        if not APP_CONFIG.keep_newlines:
            full_text = full_text.replace("\n", "").replace("\r", "")
            
        text_fragment = full_text[start_index : end_index + 1]

        if APP_CONFIG.ignore_case:
            text_fragment = text_fragment.lower()

        if RANK == 0 and APP_CONFIG.checks:
            print("Logi procesów".center(100, "-"))

        while file_index <= chars_to_check:

            if APP_CONFIG.race and COMM.iprobe(source=MPI.ANY_SOURCE, tag=TAG_STOP):
                WINNER, WINNER_INDEX = COMM.recv(source=MPI.ANY_SOURCE, tag=TAG_STOP)
                break

            char = text_fragment[file_index]

            comparison_counter += 1

            if char == search_key[search_key_index]:
                search_key_index += 1
            else:
                file_index -= search_key_index
                search_key_index = 0

            if APP_CONFIG.checks:
                print(f"[Process {RANK}] sprawdza {char} na index'ie {file_index + start_index} - na razie pasuje {search_key_index} znaków")

            if search_key_index == search_key_len:
                key_found_at_index = file_index + start_index - (search_key_len - 1)

                if APP_CONFIG.finds:
                    print(f"[Process {RANK}] znaleziono klucz na index'ie: {key_found_at_index}")

                APP_CONFIG.keys_found_indexes.append(key_found_at_index)
                file_index -= (search_key_index - 1)
                search_key_index = 0

                if APP_CONFIG.race:
                    WINNER = RANK
                    WINNER_INDEX = key_found_at_index
                    for p in range(SIZE):
                        if p != RANK:
                            COMM.isend((RANK, key_found_at_index) , dest=p, tag=TAG_STOP)
                    break

            file_index += 1
        
        APP_CONFIG.comparison_counter = comparison_counter


class BoyerMoore(ISearchAlgorithm):
    def setup(self):
        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        bad_match_table = {}

        for i in range(search_key_len - 1):
            bad_match_table[search_key[i]] = search_key_len - i - 1

        print("Przygotowanie algorytmu".center(100, "-"))
        print("Słownik bad match:")
        print(bad_match_table)

        APP_CONFIG.bad_match_table = bad_match_table


    def run(self):
        global WINNER, WINNER_INDEX

        bad_match_table = APP_CONFIG.bad_match_table

        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        search_key_index = 0

        file_index = 0

        start_index = APP_CONFIG.range[0]
        end_index = APP_CONFIG.range[1]

        chars_to_check = end_index - start_index

        comparison_counter = 0

        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            full_text = f.read()

        if not APP_CONFIG.keep_newlines:
            full_text = full_text.replace("\n", "").replace("\r", "")
            
        text_fragment = full_text[start_index : end_index + 1]

        if APP_CONFIG.ignore_case:
            text_fragment = text_fragment.lower()

        if RANK == 0 and APP_CONFIG.checks:
            print("Logi procesów".center(100, "-"))

        while file_index <= chars_to_check - search_key_len + 1:
            
            search_key_index = search_key_len - 1

            comparison_counter += 1

            while search_key_index >= 0 and text_fragment[file_index + search_key_index] == search_key[search_key_index]:
                if APP_CONFIG.race and COMM.iprobe(source=MPI.ANY_SOURCE, tag=TAG_STOP):
                    WINNER, WINNER_INDEX = COMM.recv(source=MPI.ANY_SOURCE, tag=TAG_STOP)
                    break

                if APP_CONFIG.checks:
                    print(f"[Process {RANK}] sprawdza {text_fragment[file_index + search_key_index]} na index'ie {file_index + search_key_index} - na razie pasuje {search_key_len - search_key_index} znaków")

                comparison_counter += 1

                search_key_index -= 1

            if search_key_index < 0:
                key_found_at_index = file_index + start_index

                if APP_CONFIG.finds:
                    print(f"[Process {RANK}] znaleziono klucz na index'ie: {key_found_at_index}")

                APP_CONFIG.keys_found_indexes.append(key_found_at_index)
                shift = 1

                if APP_CONFIG.race:
                    WINNER = RANK
                    WINNER_INDEX = key_found_at_index
                    for p in range(SIZE):
                        if p != RANK:
                            COMM.isend((RANK, key_found_at_index) , dest=p, tag=TAG_STOP)
                    break
            else:
                char_at_end_of_window = text_fragment[file_index + search_key_len - 1]
                shift = bad_match_table.get(char_at_end_of_window, search_key_len)

            file_index += shift

        APP_CONFIG.comparison_counter = comparison_counter


class KMP(ISearchAlgorithm):
    def setup(self):
        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        longest_prefix_table = [0] * search_key_len

        prev_prefix_len = 0
        search_key_index = 1

        while search_key_index < search_key_len:

            if search_key[search_key_index] == search_key[prev_prefix_len]:
                prev_prefix_len += 1
                longest_prefix_table[search_key_index] = prev_prefix_len
                search_key_index += 1

            else:
                if prev_prefix_len != 0:
                    prev_prefix_len = longest_prefix_table[prev_prefix_len - 1]
                
                else:
                    longest_prefix_table[search_key_index] = 0
                    search_key_index += 1

        print("Przygotowanie algorytmu".center(100, "-"))
        print("Tabela prefix'ów:")
        print(f"[{", ".join([char for char in search_key])}]")
        print(longest_prefix_table)

        APP_CONFIG.longest_prefix_table = longest_prefix_table


    def run(self):
        global WINNER, WINNER_INDEX

        longest_prefix_table = APP_CONFIG.longest_prefix_table

        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        search_key_index = 0

        file_index = 0

        start_index = APP_CONFIG.range[0]
        end_index = APP_CONFIG.range[1]

        chars_to_check = end_index - start_index

        comparison_counter = 0

        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            full_text = f.read()

        if not APP_CONFIG.keep_newlines:
            full_text = full_text.replace("\n", "").replace("\r", "")
            
        text_fragment = full_text[start_index : end_index + 1]

        if APP_CONFIG.ignore_case:
            text_fragment = text_fragment.lower()

        if RANK == 0 and APP_CONFIG.checks:
            print("Logi procesów".center(100, "-"))

        while file_index <= chars_to_check:
            
            if APP_CONFIG.race and COMM.iprobe(source=MPI.ANY_SOURCE, tag=TAG_STOP):
                WINNER, WINNER_INDEX = COMM.recv(source=MPI.ANY_SOURCE, tag=TAG_STOP)
                break

            char = text_fragment[file_index]

            comparison_counter += 1

            if APP_CONFIG.checks:
                print(f"[Process {RANK}] sprawdza {char} na index'ie {file_index + start_index} - na razie pasuje {search_key_index} znaków")

            if char == search_key[search_key_index]:
                search_key_index += 1
                file_index += 1
            
            else:
                if search_key_index != 0:
                    search_key_index = longest_prefix_table[search_key_index - 1]
                else:
                    file_index += 1

            if search_key_index == search_key_len:
                key_found_at_index = (file_index - 1) + start_index - (search_key_len - 1)

                if APP_CONFIG.finds:
                    print(f"[Process {RANK}] znaleziono klucz na index'ie: {key_found_at_index}")

                APP_CONFIG.keys_found_indexes.append(key_found_at_index)
                search_key_index = longest_prefix_table[search_key_index - 1]

                if APP_CONFIG.race:
                    WINNER = RANK
                    WINNER_INDEX = key_found_at_index
                    for p in range(SIZE):
                        if p != RANK:
                            COMM.isend((RANK, key_found_at_index) , dest=p, tag=TAG_STOP)
                    break
        
        APP_CONFIG.comparison_counter = comparison_counter


class AlgorithmFactory:
    _ALGORITHMS = {
        1: BruteForce,
        2: BoyerMoore,
        3: KMP
    }

    def get_algorithm(self, choice: int) -> ISearchAlgorithm | None:
        algorithm_class = self._ALGORITHMS.get(choice)
        return algorithm_class() if algorithm_class else None


@dataclass
class AppConfig:
    file_path: str
    search_key: str
    ignore_case: bool = False
    keep_newlines: bool = False
    checks: bool = False
    finds: bool = False
    stats: bool = False
    race: bool = False
    keys_found_indexes: list[int] | None = None
    algorithm_choice: int | None = None
    range: tuple[int, int] | None = None
    comparison_counter: int | None = None
    bad_match_table: dict[str, int] | None = None
    longest_prefix_table: list[int] | None = None


class FilePathValidator:
    def is_valid(self, file_path, keep_newlines) -> bool:
        return (self._check_if_exists(file_path)
                and self._check_if_is_file(file_path)
                and self._check_if_has_access(file_path)
                and self._check_if_big_enough(file_path, keep_newlines))


    def _check_if_exists(self, file_path) -> bool:
        exists = os.path.exists(file_path)

        if not exists:
            if RANK == 0:
                print("Podany plik nie istieje! Zamykanie programu...")
            sys.stdout.flush()
            MPI.COMM_WORLD.Abort(1)

        return exists


    def _check_if_is_file(self, file_path) -> bool:
        is_file = os.path.isfile(file_path)
        
        if not is_file:
            if RANK == 0:
                print("Podana ścieżka nie prowadzi do pliku! Zamykanie programu...")
            sys.stdout.flush()
            MPI.COMM_WORLD.Abort(1)

        return is_file


    def _check_if_has_access(self, file_path) -> bool:
        has_access = os.access(file_path, os.R_OK)

        if not has_access:
            if RANK == 0:
                print("Program nie posiada autoryzacji do podanego pliku! Zamykanie programu...")
            sys.stdout.flush()
            MPI.COMM_WORLD.Abort(1)

        return has_access


    def _check_if_big_enough(self, file_path, keep_newlines) -> bool:
        with open(file_path, "r", encoding="utf-8") as f:
            content = f.read()

        if keep_newlines:
            content = content.replace("\n", "").replace("\r", "")

        char_count = len(content)

        big_enough = True if char_count >= SIZE else False

        if not big_enough:
            if RANK == 0:
                print("Plik posiada zbyt mało znaków do podzielenia! Zmniejsz ilośc procesów lub wybierz plik z większą ilością znaków! Zamykanie programu...")
            sys.stdout.flush()
            MPI.COMM_WORLD.Abort(1)

        return big_enough


class InputReader:
    def __init__(self, validator: FilePathValidator):
        self.parser = argparse.ArgumentParser(description="Wyszukiwanie wzorców w pliku za pomocą MPI")
    
        self.parser.add_argument("file_path", type=str, nargs="?", default=None, help="Ścieżka do pliku tekstowego")
        self.parser.add_argument("search_key", type=str, nargs="?", default=None, help="Szukany wzorzec (klucz)")
        
        self.parser.add_argument("-i", "--ignore-case", action="store_true", help="Ignorowanie wielkości liter podczas wyszukiwania")
        self.parser.add_argument("-n", "--keep-newlines", action="store_true", help="Zachowanie znaków nowej linii w tekście pliku")
        self.parser.add_argument("-c", "--checks", action="store_true", help="Wyświetlenie informacji o sprawdzanych znakach")
        self.parser.add_argument("-f", "--finds", action="store_true", help="Wyświetlenie informacji o znalezeniu kluczy przez procesy")
        self.parser.add_argument("-s", "--stats", action="store_true", help="Wyświetlenie statystyk na początku i końcu")
        self.parser.add_argument("-r", "--race", action="store_true", help="Pierwszy proces, który znajdzie klucz wygrywa")

        self.args = self.parser.parse_args()
        
        self.validator = validator


    def get_config(self) -> AppConfig:
        file_path = ""
        search_key = ""

        file_path = self._get_file_path()           
        search_key = self._get_search_key()

        if self.args.ignore_case:
            search_key = search_key.lower()

        return AppConfig(
            file_path=file_path, 
            search_key=search_key,
            ignore_case=self.args.ignore_case,
            keep_newlines=self.args.keep_newlines,
            checks=self.args.checks,
            finds=self.args.finds,
            stats=self.args.stats,
            race=self.args.race,
            keys_found_indexes=[]
            )


    def _get_file_path(self) -> str:
        file_path = self.args.file_path if self.args.file_path else input("Podaj sciezke do pliku:")

        self.validator.is_valid(file_path, self.args.keep_newlines)

        return file_path

    
    def _get_search_key(self) -> str:
        return self.args.search_key if self.args.search_key else input("Podaj poszukiwany wzorzec:")


@dataclass(frozen=True)
class MenuOption:
    id: int
    description: str


class Menu:
    title: str
    prompt: str
    options: list[MenuOption]
    possible_options: set[int]
    options_string: str


    def __init__(self, title: str, prompt: str, options: list[MenuOption]):
        self.title = title
        self.prompt = prompt
        self.options = options

        self.possible_options = {option.id for option in options}

        self.options_string = '\n'.join([f"{option.id} - {option.description}" for option in options])


    def run_choice_loop(self) -> int:
        print("Menu".center(100, "-"))
        print(self.title)
        print(self.options_string)
        print(self.prompt)

        choice = -1

        while True:
            choice = input()

            try:
                clean_choice = int(choice)
                choice = clean_choice

                if choice in self.possible_options:
                    return choice

                print("Wybrana opcja nie występuje na liście! Spróbuj ponownie:")

            except ValueError:
                print("Wybrana opcja nie jest liczbą! Spróbuj ponownie:")

            sys.stdout.flush()


    def calculate_ranges(self) -> list[tuple[int, int]]:
        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            content = f.read()

        if not APP_CONFIG.keep_newlines:
            content = content.replace("\n", "").replace("\r", "")

        char_count = len(content)
        search_key_size = len(APP_CONFIG.search_key)
        
        chunk_size = char_count // SIZE
        remainder = char_count % SIZE

        start = 0
        ranges = []

        for process in range(SIZE):
            end = start + (chunk_size - 1)
            ranges.append([start, end + ((search_key_size - 1) if process < (SIZE - 1) else 0) + (remainder if process == (SIZE - 1) else 0)])
            start = end + (1 if process < (SIZE - 1) else 0)

        if APP_CONFIG.stats:
            print("Statystyki początkowe".center(100, "-"))
            print(f"Ścieżka do pliku: {APP_CONFIG.file_path}")
            print(f"Ilość znaków w pliku: {char_count}")
            print(f"Poszukiwany klucz: {APP_CONFIG.search_key}")
            print(f"Ilość znaków w kluczu: {search_key_size}")
            print("Wyznaczone przedziały (index'owane od 0):")
            print(ranges)

        return ranges


APP_CONFIG = 0
RANGES = None
RUN_TIME = 0
SETUP_TIME = 0

TAG_STOP = 99
WINNER = -1
WINNER_INDEX = -1

if __name__ == "__main__":

    if RANK == 0:
        validator = FilePathValidator()
        reader = InputReader(validator)
        APP_CONFIG = reader.get_config()
    
    APP_CONFIG = COMM.bcast(APP_CONFIG, root=0)

    if RANK == 0:

        menu_options = [
            MenuOption(1, "Brute force"),
            MenuOption(2, "Boyer-Moore"),
            MenuOption(3, "Knuth-Morris-Pratt"),
            MenuOption(9, "Wyjdz z programu")
        ]

        menu = Menu("Witaj w programie do znajdowania wzorca w pliku:", "Wybierz jedną z opcji:", menu_options)
        APP_CONFIG.algorithm_choice = menu.run_choice_loop()

    APP_CONFIG.algorithm_choice = COMM.bcast(APP_CONFIG.algorithm_choice, root=0)

    if APP_CONFIG.algorithm_choice == 9:
        MPI.Finalize()
        if RANK == 0:
            print("Zamykanie programu...")

        sys.exit(0)

    if RANK == 0:
        RANGES = menu.calculate_ranges()

    APP_CONFIG.range = COMM.scatter(RANGES, root=0)

    sys.stdout.flush()
    COMM.Barrier()

    algorithm_factory = AlgorithmFactory()
    algorithm = algorithm_factory.get_algorithm(APP_CONFIG.algorithm_choice)

    if RANK == 0:
        setup_start_time = time.perf_counter()
        algorithm.setup()
        SETUP_TIME = time.perf_counter() - setup_start_time
    
    APP_CONFIG.bad_match_table = COMM.bcast(APP_CONFIG.bad_match_table, root=0)
    APP_CONFIG.longest_prefix_table = COMM.bcast(APP_CONFIG.longest_prefix_table, root=0)

    sys.stdout.flush()
    COMM.Barrier()

    run_start_time = time.perf_counter()

    algorithm.run()

    sys.stdout.flush()
    COMM.Barrier()

    RUN_TIME = time.perf_counter() - run_start_time

    if APP_CONFIG.race:
        WINNER = COMM.reduce(WINNER, op=MPI.MAX, root=0)
        WINNER_INDEX = COMM.reduce(WINNER_INDEX, op=MPI.MAX, root=0)

    all_keys_found_indexes = COMM.gather(APP_CONFIG.keys_found_indexes, root=0)
    all_comparison_counters = COMM.gather(APP_CONFIG.comparison_counter, root=0)

    if RANK == 0:
        print("Wyniki".center(100, "-"))
        flat_list = [item for sublist in all_keys_found_indexes for item in sublist]

        if APP_CONFIG.race:
            print(f"Wygrywa proces: {WINNER}")
            print(f"Znalazł klucz na index'ie: {WINNER_INDEX}")

        else:
            print(f"Ilość znalezionych kluczy: {len(flat_list)}")
            print("Na index'ach poniżej:")
            print(flat_list)

        if APP_CONFIG.stats:
            comparisons = sum(all_comparison_counters)
            print("Statystyki końcowe".center(100, "-"))
            print(f"Ilość procesów: {SIZE}")
            print(f"Ilość porównań znaków {comparisons}")
            print(f"Czas przygotowania do algorytmu: {SETUP_TIME:.6f} s")
            print(f"Czas działania algorytmu: {RUN_TIME:.6f} s")
            print(f"Łączny czas (przygotowanie i algorytm): {SETUP_TIME + RUN_TIME:.6f} s")

        print("Dziękuję za skorzystanie z programu!".center(100, "-"))

    MPI.Finalize()