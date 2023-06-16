# Asystent giełdowy

Celem projektu jest stworzenie aplikacji, która umożliwi użytkownikowi pozyskiwanie informacje odnośnie zmian cen akcji poszczególnych firm w celu ułatwienia wykonywania inwestycji. Każdy użytkownik, po zalogowaniu, będzie mógł przeglądać dane pozyskane za pomocą API ze stron giełd. 

## System sortowania

System przedstawi mu listę firm, których zmiana na rynku będzie pasowała do charakterystyki inwestycji użytkownika np. na podstawie jego skłonności do ryzyka. Użytkownik uzyska propozycje najlepsze dla niego co znacznie skróci czas wyboru odpowiedniej firmy.

## Lista ulubionych

Inwestor będzie również mógł zapisać firmy na liście ulubionych w celu łatwiejszego dostępu.
Dzięki temu, możliwe będzie również uzyskanie codziennej informacji odnośnie zmian cen ulubionych akcji. Cała lista costanie również zapisana do pliku. 

## Interface

Całość zostanie przedstawiona w postaci wykresów w celu łatwiejszego odczytu tendencji. W sposób czytelny użytkownik będzie mógł zobaczyć zmiany cen z ostatnich dni co jest kluczowe w ocenie ryzyka.


# Podział ról

Małgosia Dulikowska:
- Interface. Zewnętrzna biblioteka do obsługi aplikacji. 

Olek Przyborek:
- Algorytm sortujący dane. Uzyskanie odpowiedniej listy sugerowanych firm.

Radek Ślepowroński:
- API. Pozyskanie histori zmian parametrów ze strony giełdy i zapisanie ich jako obiekty klasy.

Marcin Połosak:
- Podstawowe klasy służące do obsługi i łatwiejszego dostępu do firm oraz ich historii zmian.

## Postęp projektu

Uzyskaliśmy schemat budowy aplikacji. Wybraliśmy odpowiednią bibliotekę interface'u oraz wprowadziliśmy funkcje służące do odczytu API ze stron giełd.

# Wykorzystane biblioteki i narzędzia

- `libcurl` - biblioteka umożliwiająca wysyłanie zapytań HTTP i pobieranie danych z serwerów.
    - Linux: `sudo apt-get install libcurl4-openssl-dev`

- `nlohmann/json.hpp` - obsługa danych w formacie json
    - Linux: `sudo apt-get install nlohmann-json3-dev`

- `glfw3` - biblioteka do wyświetlania głównego okna aplikacji
    - Linux: `sudo apt install libglfw3-dev`


# Zaimplementowane klasy

## API

- `class Api` - obsługuje wysyłanie zapytań HTTP, pobieranie danych i odpowiedni ich zapis

    - Jeśli posiadamy odpowiednio przygotowany URL możemy wykorzystać tę klasę podając URL w konstruktorze 
    - Każdy request API oraz error zostanie zapisany do pliku `api_log.txt` wraz z datą i godziną
    - `get_data()` - zwraca string danych w formacie json
    - `save_data_to_json()` - zapisuje dane do pliku .json

- `class ApiCC` - dziedziczy po `class Api`. Odpowiada za tworzenie zapytań odpowiednich dla cryptocompare.com

    - `set_type()` - ustawia typ pobieranych danych
        - `"single"` aktualna cena
        - `"daily"` dane historyczne próbkowane dziennie (domyślnie 30 dni)
        - `"hourly"` dane historyczne próbkowane godzinowo (domyślnie 7 dni)
        - `"minute"` dane historyczne próbkowane minutowo (domyślnie 1 dzień)
        - `"symbol"` zwraca symbole wszystkich kryptowalut dostępnych na stronie

    - `set_crypro()` - ustawia symbol krypto np. "BTC", "ETH", ...
    - `set_currency()` - ustawia walutę np. "USD", "PLN", ...

- `class ApiNasdaq` - dziedziczy po `class Api`. Zapytania odpowiednie dla nasdaq.com

    - `set_type()` - ustawia typ pobieranych danych
        - `"databases"` pobiera dane o dostępnych bazach danych (wewnątrz nich są datasets)
    - `set_database` - ustawia wybraną bazę danych np. `WIKI` ...
    - `set_company` - ustawia wybraną firmę np. `FB` ...

- TBA

## Klasy danych

- `class user` - obsługa użytkownika, przechowuje jego listę ulubionych firm.
    - `get_capital() / set_capital()` - obsługa kapitału użytkownika (prywatne),
    - `get_daily_info()` - wyświetla codzienną informacje odnośnie ulubionych spółek,
    - `add_favourite() / delate_favourite()` - obsługa listy ulubionych,
    - `get_favourites()` - zwraca listę ulubionych,
    - `get_suggestions()` - użytkownik uzyskuje listę polecanych firm na podstawie jego preferencji.


- `class brand` - klasa przechowująca informacje o jednej firmie.
    - `clear_before()` - usuwa historię z przed określonego terminu (prywatna),
    - `get_brand()` - zwraca nazwę firmy,
    - `add_raport()` - dodaje aktualizacje z rynku,
    - `last_value()` - zwraca ostatnią wartość akcji,
    - `last_read_time()` - zwraca czas ostatniej aktualizacji,
    - `is_rising()` - zwraca prawdę jeśli akcje firmy rosną.


- `class data` - przechowuje pojedyńcze rejestry uzyskane z rynku.
    - `get_time()` - zwraca czas rejestru,
    - `get_high_value() / get_low_value()` - zwraca parametry rejestru.

## Sort

- `class JsonFile` - obsługuje odczyt i zapis plików .json
    - `read()` - zwraca string danych w formacie json
    - `write()` - zapisuje dane do pliku .json


- `class JsonParser` - dokonuje dekompozycji pliku .json  
    - `parseJSON()` - zwraca wektor danych vector<DataPoint> posiadający
    atrybuty .time .open .close .high .low .volumeTo .volumeFrom
    - `get(..)List` - zwraca listy porządanych wartości (Time, Open, Close, High, Low, VolumeTo, VolumeFrom)    
    - `get(..)Vector` - analogicznie do get(..)List zwraca wektor
    

- `class NASDAQ_pars` dziedziczy po `class JsonParser`. Dekompozycja pliku do wektora danych odpowiednia formatu .json zwracanego przez `class ApiNasdaq`

- `class NamePars` - dokonuje dekompozycji pliku .json 
    - `parseNames` - zwraca wektor nazw kryptowalut dostęnych na rynku, przy okazji losowo zmiejszając rozmiar wektora aby skrócić późniejszą analizę rynku

- `class sort` - dokonuje wyboru odpowiedniej giełdy dla użytkownika na podstawie jego preferencji oraz aktualnej sytuacji giełdowej
    - `recentdiff()` - zwraca iloraz ostatniej wartości do średniej z 3 ostatnich cykli
    - `isrising()` - zwraca prawde jeśli wykres jest globalnie rosnący
    - `islqrising()` - zwraca prawdę jeśli ostatnia ilość wymienionych wolumenów jest większa od średniej z 3 ostatnich cykli
    - `hop()` - zwraca współczynnik rozbieżności ekstremalnych wartości do średniej wartości w trakcie zadanego przedziału czasowego
    - `best_match_str` - zwraca wektor co najwyżej 3 kryptowalut o najlepszych wynikach spośród analizowanych
    

## Interface

- `class window` - klasa bazowa, po której dziedziczą poszczególne wyświetlane okna
    - `show()` - wyświetla puste okno

- `class login_window` - klasa umożliwiająca stworzenie oka służącego do logowania
    - `show()` - wyświetla okno służące do zalogowania się użytkownikowi

- `class profile_window` - klasa umożliwiająca stworzenie oka wyświetlającego informacje dotyczące profilu żytkownika, 
    dodawanie nowych akcji i wyświetlanie wykresów
    - `show()` - wyświetla okno profilowe

- `class registration_window` - klasa umożliwiająca stworzenie oka służącego do rejestracji nowego użytkownika
    - `show()` - wyświetla okno służące do zarejestrowania się użytkownikowi

## TBA