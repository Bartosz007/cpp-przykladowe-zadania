#include "Pojazd.h"
#include "Lista.h"
#include "io.hpp"
#include "Motocykl.h"
#include "Ciezarowy.h"
#include "Dostawczy.h"
#include "Osobowy.h"
#include "funkcje.hpp"
#include <fstream>

bool zapisz_dane(Pojazd* pojazd) {

	ofstream komis;
	try {

		komis.open("komis.txt", ios_base::app);
		string type = typeid(*pojazd).name();

		if (type.find("Motocykl") != string::npos) {

			Motocykl* poj = dynamic_cast<Motocykl*>(pojazd);
			komis << endl << "Motocykl," << poj->id << "," << poj->masa << "," << poj->rok_produkcji << "," <<
				poj->pojemnosc << "," << poj->marka << "," << poj->model << "," << poj->rodzaj_paliwa << "," << poj->moc << "," <<
				poj->wersja << "," << poj->kolor << "," << poj->przebieg << "," << poj->rodzaj_napedu << "," << poj->typ_silnika << "," << poj->typ;
			//	cout << endl << ">>Zapisano motocykl do pliku " << endl;

		}
		else if (type.find("Ciezarowy") != string::npos) {

			Ciezarowy* poj = dynamic_cast<Ciezarowy*>(pojazd);
			komis << endl << "Ciezarowy," << poj->id << "," << poj->masa << "," << poj->rok_produkcji << "," <<
				poj->pojemnosc << "," << poj->marka << "," << poj->model << "," << poj->rodzaj_paliwa << "," << poj->moc << "," <<
				poj->wersja << "," << poj->kolor << "," << poj->przebieg << "," <<
				poj->liczba_osi << "," << poj->dop_masa_calkowita << "," << poj->dop_ladownosc;

			//	cout << endl << pl(">>Zapisano samochód ciê¿arowy do pliku ") << endl;
		}
		else if (type.find("Dostawczy") != string::npos) {

			Dostawczy* poj = dynamic_cast<Dostawczy*>(pojazd);
			komis << endl << "Dostawczy," << poj->id << "," << poj->masa << "," << poj->rok_produkcji << "," <<
				poj->pojemnosc << "," << poj->marka << "," << poj->model << "," << poj->rodzaj_paliwa << "," << poj->moc << "," <<
				poj->wersja << "," << poj->kolor << "," << poj->przebieg << "," <<
				poj->typ << "," << poj->dopuszczalna_masa << "," << poj->dlugosc << "," << poj->szerokosc << "," << poj->wysokosc;

			//cout << endl << pl(">>Zapisano samochód dostawczy do pliku ") << endl;
		}
		else if (type.find("Osobowy") != string::npos) {

			Osobowy* poj = dynamic_cast<Osobowy*>(pojazd);
			komis << endl << "Osobowy," << poj->id << "," << poj->masa << "," << poj->rok_produkcji << "," <<
				poj->pojemnosc << "," << poj->marka << "," << poj->model << "," << poj->rodzaj_paliwa << "," << poj->moc << "," <<
				poj->wersja << "," << poj->kolor << "," << poj->przebieg << "," <<
				poj->liczba_drzwi << "," << poj->liczba_miejsc << "," << poj->typ_lakieru;

			//	cout << endl << pl(">>Zapisano samochód osobowy do pliku ") << endl;
		}

		komis.close();
		return 1;
	}
	catch (runtime_error & ex)
	{
		cout << endl << "Runtime error: " << ex.what() << endl;
		return 0;
	}
	catch (exception & ex) {
		cout << endl << pl("B³ad: ") << ex.what() << endl;
		return 0;
	}

	return 0;
}

Lista <string*> wczytaj_dane() {
	ifstream komis, ckomis;
	string linia;
	Lista <string*> lista;
	try {

		komis.open("komis.txt", ios_base::in);

		if (komis.good() == true)
		{
			int licznik = 0;
			while (!komis.eof())
			{
				getline(komis, linia);
				int n = dlugosc(linia);
				if (n < 0)//czy s¹ dane
					return lista;

				string* tablica = new string[n];
				tablica = dane(linia, tablica, n);

				lista.add(tablica);

			}

			komis.close();
		}

		return lista;
	}
	catch (runtime_error & ex)
	{
		cout << endl << "Runtime error: " << ex.what() << endl;
	}
	catch (exception & ex) {
		cout << endl << pl("B³ad: ") << ex.what() << endl;
	}
	return lista;

}

string* dane(string s, string tablica[], int dlugosc) {
	int n = 0;
	int poz = 0, pom = 0;

	while (n < dlugosc) {
		pom = poz;
		poz = s.find(",", ++poz);

		tablica[n] = s.substr(pom, poz - pom);
		poz++;
		n++;
	}

	return tablica;
}