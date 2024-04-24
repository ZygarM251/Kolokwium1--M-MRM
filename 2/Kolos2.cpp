#include <iostream>
#include <cstdio>
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

using namespace std;



// Struktura zawierająca dwie zmienne: int i double
struct Typ {
	int calkowita;
	double zmiennoprzecinkowa;
};

// Funkcja do alokacji tablicy instancji struktury
Typ* alokujTablice(int rozmiar, const Typ& wzorzec) {
	// Alokacja pamięci dla tablicy
	Typ* tablica = new Typ[rozmiar];

	// Inicjalizacja tablicy przy użyciu instancji wzorcowej
	for (int i = 0; i < rozmiar; ++i) {
		tablica[i] = wzorzec;
	}

	// Zwrócenie wskaźnika na utworzoną tablicę
	return tablica;
}


void zapiszPlik(const char* nazwaPliku, Typ* tablica, int rozmiar) {
	// Otwarcie pliku do zapisu
	ofstream plik(nazwaPliku);

	// Zapisanie wymiarów tablicy
	plik << rozmiar << endl;

	// Zapisanie zawartości tablicy
	for (int i = 0; i < rozmiar; ++i) {
		plik << tablica[i].calkowita << " " << tablica[i].zmiennoprzecinkowa << endl;
	}

	// Zamknięcie pliku
	plik.close();
}


Typ* odczytajPlik(const char* nazwaPliku, int& rozmiar) {
	// Otwarcie pliku do odczytu
	ifstream plik(nazwaPliku);

	// Odczytanie wymiarów tablicy
	plik >> rozmiar;

	// Alokacja pamięci dla tablicy
	Typ* tablica = new Typ[rozmiar];

	// Odczytanie zawartości tablicy
	for (int i = 0; i < rozmiar; ++i) {
		plik >> tablica[i].calkowita >> tablica[i].zmiennoprzecinkowa;
	}

	// Zamknięcie pliku
	plik.close();

	// Zwrócenie wskaźnika na utworzoną tablicę
	return tablica;
}

int main()
{
   
	Typ wzorzec = { 1, 2.5 };
	int rozmiar = 71;

	Typ* tablica = alokujTablice(rozmiar, wzorzec);
	zapiszPlik("plik.txt", tablica, rozmiar);

	Typ* odczytanaTablica = odczytajPlik("plik.txt", rozmiar);
	

	bool identyczne = true;
	for (int i = 0; i < rozmiar; ++i) {
		if (tablica[i].calkowita != odczytanaTablica[i].calkowita ||
			tablica[i].zmiennoprzecinkowa != odczytanaTablica[i].zmiennoprzecinkowa) {
			identyczne = false;
			break;
		}
	}

	if (identyczne) {
		cout << "Tablice są identyczne" << endl;
	}
	else {
		cout << "Tablice nie są identyczne" << endl;
	}
	

	delete[] tablica;
	delete[] odczytanaTablica;

	return 0;
}

