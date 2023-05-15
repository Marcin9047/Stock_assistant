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
