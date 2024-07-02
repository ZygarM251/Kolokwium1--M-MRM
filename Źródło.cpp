using namespace std;
#include <iostream>
#include <iomanip>
#pragma warning(disable: 4996)

enum class Stan
{
	dopuszczony,
	niedopuszczony
};

class Wlasciciel
{
private:
	char m_nazwisko[50];
public:
	void setNazwisko(const char* nazwisko)
	{
		strcpy_s(m_nazwisko, nazwisko);
	}

	const char* getNazwisko()
	{
		return m_nazwisko;
	}

	Wlasciciel(const char* nazwisko)
	{
		setNazwisko(nazwisko);
	}

	Wlasciciel() : m_nazwisko("")
	{
		
	}
};

class Samochód
{
protected:
	char numerRejLit[50];
	int numerRejCyf;
	double stanLicznika;
	Stan stan;
	Wlasciciel* wl;
	static int ostatniNumerRej;
public:
	void setNumerRej(const char* numRej)
	{
		strcpy_s(numerRejLit,numRej);
	}

	const char* getNumerRej()
	{
		return numerRejLit;
	}

	int getNumerRejCyf()
	{
		return numerRejCyf;
	}

	void setStanLicznika(double stan)
	{
		if (stan < 0)
		{
			throw invalid_argument("Stan licznika nie moze byc ujemny!");
		}
		else
		{
			this->stanLicznika = stan;
		}
	}

	double getStanLicznika()
	{
		return stanLicznika;
	}

	void setStan(Stan stan)
	{
		this->stan = stan;
	}

	Stan getStan()
	{
		return stan;
	}

	int getOstatni()
	{
		return ostatniNumerRej;
	}

	void setWlasciciel(Wlasciciel* wl)
	{
		this->wl = wl;
	}

	Wlasciciel* getWlasciciel()
	{
		return wl;
	}

	void setAll(const char* numRej, double stan, Stan st, Wlasciciel* wl)
	{
		setNumerRej(numRej);
		setStanLicznika(stan);
		setStan(st);
		setWlasciciel(wl);
	}

	Samochód(const char* numRej, double stan, Stan st, Wlasciciel* wl)
	{
		setAll(numRej, stan, st, wl);
		ostatniNumerRej++;
		numerRejCyf = ostatniNumerRej;
	}

	virtual double Zasieg()
	{
		return 800.0;
	}

	double WartoscSamochodu(double warPocz)
	{
		double cena = (warPocz - 0.1 * stanLicznika);

		if (getStan() == Stan::dopuszczony)
		{
			cena *= 1.0;
		}
		else
		{
			cena *= 0.2;
		}

		if (cena < 400)
		{
			cena = 400;
		}

		return cena;
	}

	bool operator==(const Samochód& a)
	{
		const char* numA = a.numerRejLit;
		return (strcmp(numerRejLit,a.numerRejLit) && abs(stanLicznika - a.stanLicznika) <= 10);
	}

};

class SamochódElektryczny : public Samochód
{
private:
	int stanBaterii;
public:
	void setStanBaterii(int stanBaterii)
	{
		if (stanBaterii < 0 || stanBaterii > 100)
		{
			throw invalid_argument("Stan baterii musi byc w przedziale 0-100!");
		}
		else
		{
			this->stanBaterii = stanBaterii;
		}
	}

	int getStanBaterii()
	{
		return stanBaterii;
	}

	SamochódElektryczny(int stanBaterii, const char* numRej, double stan, Stan st, Wlasciciel* wl) : Samochód(numRej, stan, st, wl)
	{
		setStanBaterii(stanBaterii);
	}

	double Zasieg() override
	{
		return 2.5 * stanBaterii;
	}
};

int Samochód::ostatniNumerRej = 0;

int main()
{
	Wlasciciel w1("Nowak");
	Wlasciciel w2("Kowalski");

	Samochód s1("ABC", 5000.0, Stan::dopuszczony, &w1);
	Samochód s2("ABC", 5000.0, Stan::dopuszczony, &w2);
	SamochódElektryczny s3(80, "ABC", 5005.0, Stan::dopuszczony, &w2);
	Samochód s4("ABC", 1000.0, Stan::niedopuszczony,&w1);

	if (s1 == s2)
		cout << "Samochody sa takie same!" << endl;
	else
		cout << "Samochody roznia sie od siebie!" << endl;

	cout << endl;

	double zasieg = s1.Zasieg();
	cout << zasieg << endl;
	double zasieg3 = s3.Zasieg();
	cout << zasieg3 << endl;

	cout << endl;

	double wartosc1 = s1.WartoscSamochodu(1000.0);
	cout << wartosc1 << endl;
	double wartosc2 = s4.WartoscSamochodu(1000.0);
	cout << wartosc2 << endl;

	cout << endl;

	int numer = s1.getNumerRejCyf();
	cout << numer << endl;
	int numer2 = s2.getNumerRejCyf();
	cout << numer2 << endl;

	cout << endl;

	double wartosc5 = s1.WartoscSamochodu(100.0);
	cout << wartosc5 << endl;
}