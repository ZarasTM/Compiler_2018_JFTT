Imie i Nazwisko: Piotr Zaraś
Nr. indeksu: 236671

Opis plików:
./
  Makefile - kompiluje kompilator
  kompilator - uruchamia kompilator zgodnie z wymaganiami to znaczy: ./kompilator <file_in> <file_out>

./src/
  scanner.l - analizator lexykalny
  parser.y - parser do załączonej gramatyki

./src/utils/
  main.h - główny kod odpowiedzialny za przypisywanie zmiennych, testowanie, wczytywanie i wypisywanie
  Inserter.h - klasa służąca do ładowania zmiennych/stałych/elementów_tablicy do podanych rejestrów
  Labeler.h - klasa odpowiedzialna za wstawianie jumpów/labeli oraz za naprawę pętli i instrukcji warunkowych
  OperationGenerator.h - klasa generująca kod operacji takich jak ADD/SUB/DIV/MUL/MOD/=/!=/</>/<=/>=
  SymbolTable.h - klasa przechowująca wszystkie zmienne/tablice oraz odpowiedzialna za ich inicjalizacje oraz deklaracje
  Variable.h - klasa zmiennej posiadająca informacje o dowolnej zmiennej/tablicy/iteratorze/stałej
  utility.h - zawiera przydatne metody takie jak zamiana liczby dziesiętnej na binarną
