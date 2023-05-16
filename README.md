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

- TBA


# Zaimplementowane klasy

## API

- `class Api` - obsługuje wysyłanie zapytań HTTP, pobieranie danych i odpowiedni ich zapis

    - Jeśli posiadamy odpowiednio przygotowany URL możemy wykorzystać tę klasę podając URL w konstruktorze 
    - `get_data()` - zwraca string danych
    - `save_data_to_json()` - zapisuje dane do pliku .json

- `class ApiCC` - dziedziczy po `class Api`. Odpowiada za tworzenie zapytań odpowiednich dla cryptocompare.com

    - `set_type()` - ustawia typ pobieranych danych
        - `"single"` aktualna cena
        - `"daily"` dane historyczne próbkowane dziennie (domyślnie 30 dni)
        - `"hourly"` dane historyczne próbkowane godzinowo (domyślnie 7 dni)
        - `"minute"` dane historyczne próbkowane minutowo (domyślnie 1 dzień)

    - `set_crypro()` - ustawia symbol krypto np. "BTC", "ETH", ...
    - `set_currency()` - ustawia walutę np. "USD", "PLN", ...

- `class ApiNasdaq` - dziedziczy po `class Api`. Zapytania odpowiednie dla nasdaq.com

    - TBA

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


## TBA
