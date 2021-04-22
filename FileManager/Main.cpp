#include "FajlRendszer.cpp"

int main()
{
	FajlRendszer fajlRendszer("input.txt");
	cout << endl << "Adjon meg egy konyvtar nevet:" << endl;
	string bekertKonyvtar;
	cin >> bekertKonyvtar;
	optional<Bejegyzes*> talalat = fajlRendszer.keres(bekertKonyvtar);
	if (talalat.has_value() == true)
	{
		cout << "A konyvtar merete: " << talalat.value()->getMeret() << endl << endl;
	}
	else
	{
		cout << "Nem letezik ilyen nevu konyvtar: " << bekertKonyvtar << endl << endl;
	}
}
