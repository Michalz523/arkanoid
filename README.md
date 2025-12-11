# arkanoid
Arkanoid, an iconic arcade game.

Projekt implementuje klasyczną grę zręcznościową Arkanoid przy użyciu biblioteki SFML w języku C++.

Opis Scenariusza Gry:
Gra polega na odbijaniu piłki za pomocą ruchomej paletki, aby niszczyć klocki umieszczone w górnej części ekranu.

Kluczowe Funkcjonalności:
Klocki z Życiem: Klocki mają losowo od 1 do 3 punktów życia. Różne kolory klocków odpowiadają różnym poziomom wytrzymałości. Klocek zostaje zniszczony dopiero po utracie wszystkich punktów życia.
System Żyć: Gracz ma 3 życia. Utrata wszystkich żyć powoduje wyświetlenie ekranu "PRZEGRAŁEŚ".
Maszyna Stanów: Program działa w trzech głównych stanach: Menu, Zasady, i Gra.
Zapis i Odczyt Gry: Możliwość zapisania aktualnego stanu gry (pozycja piłki, paletki, pozostałe życia, stan i położenie klocków) oraz wczytania go w późniejszym czasie z menu głównego.

Wymagania i Sposób Uruchomienia
Aby skompilować i uruchomić projekt, potrzebne są następujące narzędzia i kroki:

Wymagania:
1. Kompilator C++: Obsługujący standard C++11 lub nowszy.
2. Biblioteka SFML: Wersja 2.5.x.
3. Plik Czcionki: Plik arial.ttf musi znajdować się w tym samym katalogu co skompilowany plik wykonywalny .exe.

Instrukcja Uruchomienia:
1. Kompilacja: Skonfiguruj projekt w swoim np. Visual Studio tak, aby poprawnie linkował do wszystkich modułów SFML. Upewnij się, że wszystkie pliki .cpp (main.cpp, Game.cpp, menu.cpp, RulesScreen.cpp, Brick.cpp, Ball.cpp, Paddle.cpp) są dodane do projektu.
2. Katalog Roboczy: Upewnij się, że plik arial.ttf oraz pliki DLL biblioteki SFML znajdują się w katalogu, w którym generowany jest plik .exe.
3. Start: Uruchom skompilowany plik. Gra rozpocznie się w Menu Głównym.

Kontrola i Funkcjonalność:

| Menu |
Strzałki GÓRA/DÓŁ - Wybór opcji w Menu Głównym. 
ENTER - Zatwierdzenie wyboru w Menu / Powrót z ekranu Zasad.

| Gra |
Strzałki LEWO/PRAWO - Sterowanie paletką (ruch poziomy). 
P - Włączenie/wyłączenie pauzy.
ESC - W trakcie Pauzy: Zapisanie stanu gry i powrót do Menu Głównego.
ESC / Zamknięcie Okna - Powrót do Menu Głównego (z Zasad) lub wyjście z programu.

Struktura Plików:
main.cpp - Zawiera główną pętlę sterującą stanami gry (Menu, Gra, Zasady, Wyjście). 
Game.h / Game.cpp - Główna klasa zarządzająca rozgrywką, kolizjami, logiką żyć, zapisem i odczytem stanu gry. 
Menu.h / Menu.cpp - Klasa tworząca i obsługująca interaktywne Menu Główne. 
RulesScreen.h / RulesScreen.cpp - Klasa odpowiedzialna za wyświetlanie zasad gry.
Brick.h / Brick.cpp - Klasa reprezentująca klocek/cegłe z systemem żyć (1-3 uderzenia) i odpowiadającą mu kolorystyką. 
Ball.h / Ball.cpp - Klasa reprezentująca piłkę. 
Paddle.h / Paddle.cpp - Klasa reprezentująca paletkę gracza. 
GameState.h - Plik nagłówkowy z definicją GameState. 
