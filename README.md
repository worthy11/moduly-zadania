# Moduły - zadania

Treść zadań: [ZADANIA.md](ZADANIA.md).

| Zadanie | Katalog        | Dostajesz                                          | Dopisujesz                      |
| ------- | -------------- | -------------------------------------------------- | ------------------------------- |
| 1       | [task1](task1) | `main.cpp`, `data/cases.txt`, CMake                | `album.cppm`                    |
| 2       | [task2](task2) | `main.cpp`, `data/cases.txt`, CMake                | `album.cppm`, `dorm.cppm`       |
| 3       | [task3](task3) | `main.cpp`, `data/cases.txt`, CMake                | `waitlist.cppm`, `waitlist.cpp` |
| 4       | [task4](task4) | `main_fines.cpp`, `legacy_fines.*`, `data/`, CMake | `fines.cppm`, `fines.cpp`       |
| 5       | [task4](task4) | `main_receipt.cpp` (+ to samo co w zad. 4)         | `receipt.cppm`, `receipt.cpp`   |

Sukces = program wypisuje `OK` (zadania 1–3 i 5) albo wyjście zgodne z `data/expected.txt` (zadanie 4).

## Wymagania

- C++20 z obsługą modułów
- CMake >= 3.28
- **Ninja** (>= 1.11) albo Visual Studio 2022 (MSVC)

Uruchamiaj zawsze z katalogu danego zadania (`task1` … `task4`), bo ścieżki do `data/` są względne.
