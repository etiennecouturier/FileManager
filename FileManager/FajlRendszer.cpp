#include <iostream>
#include <fstream>
#include <string>
#include "Fajl.cpp"
#include <optional>
class FajlRendszer
{

private:
	Bejegyzes* gyoker;

	bool hozzaadFajl(Bejegyzes* gyoker, Bejegyzes* ujFajl)
	{
		if (gyoker->konyvtar() == true && gyoker->getNev().compare(ujFajl->getSzulo()) == 0)
		{
			gyoker->hozzaadBejegyzes(ujFajl);
			return true;
		}
		for (Bejegyzes* bejegyzes : gyoker->getBejegyzesek())
		{
			bool eredmeny = hozzaadFajl(bejegyzes, ujFajl);
			if (eredmeny == true)
			{
				return true;
			}
		}
		return false;
	}

	optional<Bejegyzes*> keres(Bejegyzes* gyoker, string keresett)
	{
		if (gyoker->konyvtar() && gyoker->getNev().compare(keresett) == 0)
		{
			return make_optional(gyoker);
		}
		for (Bejegyzes* bejegyzes : gyoker->getBejegyzesek())
		{
			optional<Bejegyzes*> talalat = keres(bejegyzes, keresett);
			if (talalat != nullopt)
			{
				return talalat;
			}
		}

		return nullopt;
	}

	void kiirFajlokLaposan(Bejegyzes* gyoker)
	{
		cout << gyoker->getNev() << endl;

		for (Bejegyzes* bejegyzes : gyoker->getBejegyzesek())
		{
			kiirFajlokLaposan(bejegyzes);
		}
	}

public:

	FajlRendszer(string fajlNev)
	{
		cout << "------------------" << endl;
		cout << "gyoker letrehozasa" << endl;
		gyoker = new Konyvtar("gyoker", 0, "-");
		beolvasFajlRendszer(fajlNev);
	}

	optional<Bejegyzes*> keres(string keresett)
	{
		return keres(gyoker, keresett);
	}

	void kiirFajlokLaposan()
	{
		kiirFajlokLaposan(gyoker);
	}

	Bejegyzes* beolvasFajlRendszer(string fajlNev)
	{
		ifstream f(fajlNev);
		if (f.fail())
		{
			cerr << "Hibas fajlnev\n";
			return nullptr;
		}

		string tipus, nev, szulo;
		int meret;
		while (f >> tipus >> nev >> meret >> szulo)
		{
			if (tipus.compare("D") == 0)
			{
				cout << "konyvtar letrehozasa " << nev << endl;
				hozzaadFajl(gyoker, new Konyvtar(nev, meret, szulo));
			}
			else if (tipus.compare("F") == 0)
			{
				cout << "fajl letrehozasa  " << nev << endl;
				hozzaadFajl(gyoker, new Fajl(nev, meret, szulo));
			}
		}
		cout << "------------------" << endl;
		return gyoker;
	}

	void cleanup(Bejegyzes* gyoker)
	{
		for (Bejegyzes* bejegyzes : gyoker->getBejegyzesek())
		{
			cleanup(bejegyzes);
		}
		cout << "konyvtar/fajl torlese " << gyoker->getNev() << endl;
		delete gyoker;
	}

	~FajlRendszer()
	{
		cout << "------------------" << endl;
		cout << "takaritas..." << endl;
		cleanup(gyoker);
		cout << "------------------" << endl;
	}

};
