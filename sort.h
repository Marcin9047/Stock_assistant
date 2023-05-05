/*
clasa otrzymująca dane od użytkownika w postaci kapitału, minimalnych zyskow, maksymalnych strat i czasu
na tej podstawie wybiera optymalne firmy
*/
class sort
{
    private:
    char brand_name;

    public:
    sort(int capital, char attitude);
    brand best_match();


}