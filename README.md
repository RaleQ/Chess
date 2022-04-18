Jest to projekt na zaliczenie.

Aktualnie projekt napisany jest cały w jednym pliku, w sposób dosyć chaotyczny.

Aktualne zaimplementowane rzeczy:
  - Podstawowe ruszanie się figurami po planszy
  - Wszystkie figury mogą poruszać się jedynie po dozwolonych polach
  - Enpasant
  - Roszada
  - Podświetlanie pól na które podniesiona figura może wejść
  - Możliwość zmienienia wariantu wizualnego planszy
  - Możliwość ustawienia figury na którą pionek ma awansować po przejściu na drugi koniec szachownicy
  - Możliwość resetu pozycji do defaultowej
  - Możliwość ustawienia dowolnej pozycji przy starcie programu za pomocą notacji FEN
  - Możliwość zmiany strony na szachownicy
  - Wyświetlanie bilansu materiału (Wartośći figur: pionek - 1 ; koń - 3 ; goniec - 3; wieża - 5 ; królowa - 9)
  - Wyświetlanie napisu "Checkmate!" przy wygraniu rozgrywki

Do zaimplemenowania:
  - Remis (aktualnie jeśli strona nie ma wolnego ruchu a król nie jest w szachu to gra się nie kończy i nie wyświetla się żaden napis)
  - Zaimplementowanie funkcji ewaluacji pozycji która będzie wyliczać wartość danej pozycji na podstawie wielu zmiennych
  - Zaimplemenowanie funkcji która będzie wyszukiwać najlepsze ruchy dla konkretnej głębokości korzystając z funkcji ewaluacji
  - Przyspieszenie funkcji wyszukiwania ruchów za pomocą alpha-beta-pruning'u oraz move ordering'u
  - Przepisanie kodu na ładniejszy, schludniejszy i szybszy
