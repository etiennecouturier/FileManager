#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Bejegyzes
{
protected:

	string nev;
	int meret;
	string szulo;

public:

	Bejegyzes(string nev, int meret, string szulo): nev(nev), meret(meret), szulo(szulo) {}

	string getNev()
	{
		return nev;
	}

	string getSzulo()
	{
		return szulo;
	}

	virtual int getMeret() { return 0; };

	virtual bool konyvtar() { return false; }
	   
	virtual vector<Bejegyzes*> getBejegyzesek()
	{
		vector<Bejegyzes*> bejegyzesek;
		return bejegyzesek;
	}

	virtual void hozzaadBejegyzes(Bejegyzes* bejegyzes) {};

	virtual void print()
	{
		cout << nev << " // " << meret << " // " << szulo << endl;
	}

};

class Konyvtar : public Bejegyzes
{
private:

	vector<Bejegyzes*> bejegyzesek;

public:

	Konyvtar(string nev, int meret, string szulo) : Bejegyzes(nev, meret, szulo) {}

	int getMeret()
	{
		int sum = 0;
		for (auto bejegyzes : bejegyzesek)
		{
			sum += bejegyzes->getMeret();
		}
		return sum;
	}

	virtual bool konyvtar() { return true; }

	vector<Bejegyzes*> getBejegyzesek()
	{
		return bejegyzesek;
	}

	void hozzaadBejegyzes(Bejegyzes* bejegyzes)
	{
		bejegyzesek.push_back(bejegyzes);
	}

	void print()
	{
		cout << "konyvtar ";
	}
	
};

class Fajl : public Bejegyzes
{

public: 

	Fajl(string nev, int meret, string szulo) : Bejegyzes(nev, meret, szulo) {}

	int getMeret()
	{
		return meret;
	}

	void print()
	{
		cout << "fajl ";
	}

};