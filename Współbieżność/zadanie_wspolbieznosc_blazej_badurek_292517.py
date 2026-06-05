'''
source .venv/bin/activate
mpiexec -n 3 python3.14 zadanie_wspolbieznosc_blazej_badurek_292517.py ./text.txt tat
'''

from mpi4py import MPI
from abc import ABC, abstractmethod
from dataclasses import dataclass
import sys
import os


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
        search_key = APP_CONFIG.search_key
        search_key_len = len(search_key)
        search_key_index = 0

        file_index = 0
        chars_to_check = APP_CONFIG.range[1] - APP_CONFIG.range[0]

        start_index = APP_CONFIG.range[0]
        end_index = APP_CONFIG.range[1]

        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            text_fragment = f.read()[start_index : end_index + 1]

        #print(f"{RANK} {text_fragment}")

        while file_index <= chars_to_check:

            char = text_fragment[file_index]

            if char == search_key[search_key_index]:
                search_key_index += 1
            else:
                file_index -= search_key_index
                search_key_index = 0

            #print(f"Process {RANK} has {char} at {file_index + start_index} - hits so far {search_key_index}")

            if search_key_index == search_key_len:
                print(f"Process {RANK} found key at {file_index + start_index - (search_key_len - 1)}")
                file_index -= (search_key_index - 1)
                search_key_index = 0

            file_index += 1


class BoyerMoore(ISearchAlgorithm):
    def setup(self):
        pass

    def run(self):
        print("Boyer-Moore")


class KMP(ISearchAlgorithm):
    def setup(self):
        pass

    def run(self):
        print("KMP")


class Exit(ISearchAlgorithm):
    def setup(self):
        pass

    def run(self):
        if RANK == 0:
            print("Zamykanie programu...")
            
        COMM.Abort(0)


#TODO brzydal
class AlgorithmFactory():
    def get_algorithm(self, choice: int) -> ISearchAlgorithm | None:
        if choice == 1: return BruteForce()
        if choice == 2: return BoyerMoore()
        if choice == 3: return KMP()
        if choice == 9: return Exit()
        return None


@dataclass
class AppConfig:
    file_path: str
    search_key: str
    algorithm_choice: int | None = None
    range: tuple[int, int] | None = None


class FilePathValidator:
    def is_valid(self, file_path) -> bool:
        return os.path.exists(file_path) and os.path.isfile(file_path)


class InputReader:
    def __init__(self, validator: FilePathValidator):
        self.validator = validator
    
    def get_config(self) -> AppConfig:
        file_path = ""
        search_key = ""

        file_path = self._get_file_path()

        if not self.validator.is_valid(file_path):
            #Dodac expection handling
            print("Podana sciezka pliku jest niepoprawna!")
            COMM.Abort(1)
            
        search_key = self._get_search_key()

        return AppConfig(file_path=file_path, search_key=search_key)

    def _get_file_path(self) -> str:
        if len(sys.argv) > 1:
            return sys.argv[1]
        else:
            return input("Podaj sciezke do pliku:")
    
    def _get_search_key(self) -> str:
        if len(sys.argv) > 2:
            return sys.argv[2]
        else:
            return input("Podaj poszukiwany wzorzec:")


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
        print(self.title)
        print(self.options_string)
        print(self.prompt)

        choice = -1

        while choice not in self.possible_options:
            choice = int(input())
        
        return choice


    def calculate_ranges(self) -> list[tuple[int, int]]:
        with open(APP_CONFIG.file_path, "r", encoding="utf-8") as f:
            content = f.read().rstrip('\r\n')

        char_count = len(content)
        search_key_size = len(APP_CONFIG.search_key)

        #print(char_count, search_key_size)
        
        chunk_size = char_count // SIZE
        remainder = char_count % SIZE

        #print(chunk_size, remainder)

        start = 0
        ranges = []

        for process in range(SIZE):
            end = start + (chunk_size - 1)
            ranges.append([start, end + ((search_key_size - 1) if process < (SIZE - 1) else 0) + (remainder if process == (SIZE - 1) else 0)])
            start = end + (1 if process < (SIZE - 1) else 0)

        return ranges


APP_CONFIG = 0
RANGES = None

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
        RANGES = menu.calculate_ranges()

    APP_CONFIG.algorithm_choice = COMM.bcast(APP_CONFIG.algorithm_choice, root=0)
    APP_CONFIG.range = COMM.scatter(RANGES, root=0)

    COMM.Barrier()

    #print(RANK, APP_CONFIG)

    algorithm_factory = AlgorithmFactory()
    algorithm = algorithm_factory.get_algorithm(APP_CONFIG.algorithm_choice)

    if RANK == 0:
        algorithm.setup()

    algorithm.run()

    MPI.Finalize()