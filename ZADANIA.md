# Moduły: zadania

🟢 najprostsze · 🟡 konkretne · 🟠 praktyczne

## 1. 🟢 Numery albumów

W dziekanacie numery albumu mają zawsze 6 cyfr. Załóżmy, że dwie pierwsze oznaczają rok rozpoczęcia studiów (np. `231045` to rocznik `23`).

W [task1](task1) dopisz moduł `album` (`album.cppm`) z funkcją:

```cpp
bool sameStartYear(const char* idA, const char* idB);
```

Funkcja zwraca `true` tylko wtedy, gdy oba napisy mają dokładnie 6 znaków z zakresu `0-9` i ich dwa pierwsze znaki są takie same. W każdym innym przypadku (inna długość, litera, spacja, pusty napis, różny rocznik) wynikiem jest `false`. Nie zakładaj, że wskaźniki są `nullptr`.

Przypadki testowe są w `data/cases.txt`; uruchamia je dostarczony `main.cpp`.

## 2. 🟢 Wspólny pokój w Kapitolu

Powiedzmy, że akademik pozwala dzielić pokój tylko osobom z tego samego rocznika (te same dwie pierwsze cyfry albumu). W [task2](task2) napisz moduł `dorm` (`dorm.cppm`) z funkcją:

```cpp
const char* roomDecision(const char* idA, const char* idB);
```

Zaimportuj w nim moduł `album` z zadania 1 (bez wklejania jego kodu) i użyj `sameStartYear`, żeby zwrócić jeden z napisów:

- ten sam rocznik → `shared-room`;
- oba albumy poprawne (po 6 cyfr), ale różny rocznik → `separate-rooms`;
- którykolwiek album niepoprawny → `rejected`.

Do katalogu skopiuj też swoje `album.cppm`. Dostarczony `main` importuje tylko `dorm` i czyta `data/cases.txt`.

Czy po samym `import dorm;` da się w `main` bezpośrednio wywołać `sameStartYear`?

## 3. 🟡 Kolejka na egzamin

Sala egzaminacyjna ma ograniczoną liczbę miejsc. Prowadzący prowadzi prostą listę: ile osób już siedzi (`seated`) i jaki jest limit miejsc w sali (`capacity`). W [task3](task3) zaimplementuj to jako moduł `waitlist`.

**Podział plików**

| Plik            | Zawartość                                                                              |
| --------------- | -------------------------------------------------------------------------------------- |
| `waitlist.cppm` | `export module waitlist;` oraz eksportowane deklaracje (struktura + trzy funkcje)      |
| `waitlist.cpp`  | `module waitlist;` oraz definicje funkcji; tu mogą być też prywatne funkcje pomocnicze |

Publiczny interfejs:

```cpp
struct Waitlist {
    int seated;
    int capacity;
};

bool isConsistent(Waitlist waitlist);
bool tryJoin(Waitlist& waitlist);
bool tryLeave(Waitlist& waitlist);
```

**Spójność stanu** (`isConsistent`)

Stan uznajemy za poprawny tylko gdy jednocześnie:

1. `capacity` jest z zakresu `1..100`,
2. `seated` jest z zakresu `0..capacity`.

Przykłady: `{0, 30}`, `{30, 30}` i `{10, 60}` są spójne; `{0, 0}`, `{3, 2}`, `{-1, 5}`, `{10, 101}` nie są.

**Dołączanie i opuszczanie sali**

- `tryJoin` zwiększa `seated` o 1, jeśli wynikowy stan byłby spójny; wtedy `true`. W przeciwnym razie bez zmian i `false`.
- `tryLeave` działa odwrotnie.

`tryJoin` / `tryLeave` biorą `Waitlist` przez referencję; `isConsistent` przez wartość. Scenariusze: `data/cases.txt`.

## 4. 🟠 Kary w bibliotece: Wrapper

Biblioteka AGH ma stary backend i zamiast korzystać z modułów nadal używa plików nagłówkowych i źródłowych: `legacy_fines.h` / `legacy_fines.cpp`. Zaimplementowana tam funkcjonalność śledzenia naliczonych studentom kar umie dodawać kwoty, cofać ostatnią karę, czyścić i odczytywać zapisane kary. Wymaga jednak nowoczesnego opakowania.

Twoje zadanie w [task4](task4) to napisać moduł `fines`, który:

1. W jednostce implementacji używa globalnego fragmentu modułu, żeby dołączyć stary nagłówek:

```cpp
module;

#include "legacy_fines.h"

module fines;
```

2. Eksportuje nowoczesne API (deklaracje w `fines.cppm`, definicje w `fines.cpp`):

```cpp
struct Totals {
    int count;
    double total;
    double minFine;
    double maxFine;
    double average;
};

void addFine(double amount);
Totals getTotals();
bool undoLast();
void reset();
```

3. Wewnątrz woła wyłącznie funkcje `legacy_*`. `getTotals()` ma wyliczyć min / max / sumę / średnią na podstawie `legacy_count` i `legacy_at`.
4. W `main_fines.cpp` wolno importować tylko `fines` - bez `#include "legacy_fines.h"`. Plików `legacy_*` oraz `main_fines.cpp` nie zmieniaj.

CLI (target `fines_cli`): `fine`, `summary`, `undo`, `reset`, `exit`.  
Testy: `data/input.txt` → `data/expected.txt`.

## 5. 🟠 Kary w bibliotece: Paragony

W **tym samym** katalogu [task4](task4) dodaj moduł `receipt` obok fasady `fines`.

```cpp
bool writeFineReceipt(const char* path, double minTotal);
```

- Dopisz `receipt.cppm` + `receipt.cpp`; implementacja powinna korzystać z `getTotals()` z modułu `fines` .
- Zwróć `false` (bez tworzenia/nadpisywania pliku), gdy `count == 0` albo `total < minTotal`, albo zapis się nie uda.
- Jeśli wszystko gra, nadpisz plik; format:

```text
count=<n>
total=<…>
min=<…>
max=<…>
average=<…>
```

Templatki znajdziesz w `data/golden_three.txt` i `data/golden_four.txt`.
