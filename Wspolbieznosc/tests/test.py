import subprocess
import os


SCRIPT_NAME = "zadanie_wspolbieznosc_blazej_badurek_292517.py"
TEST_FILE = "test_data.txt"


def setup_test_file(test_content):
    with open(TEST_FILE, "w", encoding="utf-8") as f:
        f.write(test_content)


def remove_test_file():
    if os.path.exists(TEST_FILE):
        os.remove(TEST_FILE)


def run_mpi_command(processes, algorithm_choice, key, flags=[]):
    command = ["mpirun", "--oversubscribe", "-n", str(processes), "python3", SCRIPT_NAME, TEST_FILE, key] + flags
    
    menu_input = f"{algorithm_choice}\n"
    
    result = subprocess.run(
        command,
        input=menu_input,
        text=True,
        capture_output=True
    )
    return result.stdout, result.stderr


def run_test(name, processes, algorithm, key, result, flags):
    print(name + "... ", end="")
    output, _ = run_mpi_command(processes=processes, algorithm_choice=algorithm, key=key, flags=flags)
    if result in output:
        print("OK")
    else:
        print("FAIL")


def run_test_block(id, name, processes, file_content, key, result, flags):
    print(f"[TEST {id}] " + name)

    setup_test_file(file_content)

    run_test(f"[TEST {id}.1] Brute force", processes, 1, key, result, flags)
    run_test(f"[TEST {id}.2] Boyer-Moore", processes, 2, key, result, flags)
    run_test(f"[TEST {id}.3] Knuth-Morris-Pratt", processes, 3, key, result, flags)

def run_tests():
    print("Rozpoczynanie automatycznych testów".center(100, "-"))
    
    try:

        run_test_block(1, "Jeden klucz w pliku", 1, "ababc", "ababc", "[0]", [])
        run_test_block(2, "Wiele kluczy w pliku", 1, "aababababc", "abab", "[1, 3, 5]", [])
        run_test_block(3, "Klucz na skraju zakresów", 2, "aaaabaaa", "ab", "[3]", [])
        run_test_block(4, "Wiele kluczy w pliku i wiele procesów", 2, "aababababc", "abab", "[1, 3, 5]", [])
        run_test_block(5, "Wiele kluczy w pliku i wiele procesów", 3, "abcaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "abc", "[0]", [])
        run_test_block(6, "Wiele kluczy w pliku i wiele procesów", 3, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaabc", "abc", "[28]", [])
        run_test_block(7, "Flaga ignore case", 3, "aaaABccc", "aBc", "[3]", ["-i"])
        run_test_block(8, "Flaga keep_newlines", 3, "ab\ncabc", "abc", "[4]", ["-n"])
        run_test_block(9, "Flaga race", 2, "xyzabc", "abc", "Wygrywa proces: 1", ["-r"])
        run_test_block(10, "Więcej procesów niż rdzeni", 32, "aaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "ab", "[2]", [])

    finally:
        remove_test_file()
        print("Testy zakończone".center(100, "-"))


if __name__ == "__main__":
    run_tests()