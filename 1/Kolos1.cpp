#include <iostream>
#include <cstdio>
#include <fstream>
#include <iostream>
#pragma warning(disable:4996)

// Struktura zawierająca dwie zmienne: int i double
struct PrzykladowaStruktura {
    int calkowita;
    double zmiennoprzecinkowa;
};

// Funkcja do alokacji tablicy instancji struktury
PrzykladowaStruktura* alokujTablice(int rozmiar, const PrzykladowaStruktura& wzorzec) {
    // Alokacja pamięci dla tablicy
    PrzykladowaStruktura* tablica = new PrzykladowaStruktura[rozmiar];

    // Inicjalizacja tablicy przy użyciu instancji wzorcowej
    for (int i = 0; i < rozmiar; ++i) {
        tablica[i] = wzorzec;
    }

    // Zwrócenie wskaźnika na utworzoną tablicę
    return tablica;
}

// Funkcja do zapisu tablicy do pliku w trybie tekstowym
void zapiszTabliceDoPliku(const char* nazwaPliku, const PrzykladowaStruktura* tablica, int rozmiar) {
    // Otwarcie pliku do zapisu
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku do zapisu." << std::endl;
        return;
    }

    // Zapisanie rozmiaru tablicy do pliku
    plik << rozmiar << std::endl;

    // Zapisanie zawartości tablicy do pliku
    for (int i = 0; i < rozmiar; ++i) {
        plik << tablica[i].calkowita << " " << tablica[i].zmiennoprzecinkowa << std::endl;
    }

    // Zamknięcie pliku
    plik.close();
}

// Funkcja do odczytu tablicy z pliku w trybie tekstowym
PrzykladowaStruktura* odczytajTabliceZPliku(const char* nazwaPliku, int& rozmiar) {
    // Otwarcie pliku do odczytu
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku do odczytu." << std::endl;
        return nullptr;
    }

    // Odczytanie rozmiaru tablicy z pliku
    plik >> rozmiar;

    // Alokacja pamięci dla tablicy na podstawie odczytanego rozmiaru
    PrzykladowaStruktura* tablica = new PrzykladowaStruktura[rozmiar];

    // Odczytanie zawartości tablicy z pliku
    for (int i = 0; i < rozmiar; ++i) {
        plik >> tablica[i].calkowita >> tablica[i].zmiennoprzecinkowa;
    }

    // Zamknięcie pliku
    plik.close();

    // Zwrócenie wskaźnika do wczytanej tablicy
    return tablica;
}



int main() {
    // Kod ASCII litery 'Z'
    int rozmiar = 90;

    // Przykładowa instancja wzorcowa
    PrzykladowaStruktura wzorzec;
    wzorzec.calkowita = 10;
    wzorzec.zmiennoprzecinkowa = 3.14;

    // Użycie funkcji do alokacji tablicy
    PrzykladowaStruktura* tablica = alokujTablice(rozmiar, wzorzec);

    // Zapis tablicy do pliku
    zapiszTabliceDoPliku("tablica.txt", tablica, rozmiar);


    // Sprawdzenie, czy tablice są identyczne
    bool identyczne = true;
    for (int i = 0; i < rozmiar; ++i) {
        if (tablica[i].calkowita != wzorzec.calkowita || tablica[i].zmiennoprzecinkowa != wzorzec.zmiennoprzecinkowa) {
			identyczne = false;
			break;
		}
	}

    if (identyczne) {
        std::cout << "Tablice sa identyczne." << std::endl;
    }
    else {
        std::cout << "Tablice nie sa identyczne." << std::endl;
    }

    // Zwolnienie zaalokowanej pamięci
    delete[] tablica;

    return 0;
}