#include "Osobowy.h"
#include <string>
#include <iostream>
using namespace std;

Osobowy::Osobowy(string& liczba_drzwi, string& liczba_miejsc, string& typ_lakieru,
	string& wersja, string& kolor, string& przebieg,
	string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc)
	:liczba_drzwi(liczba_drzwi), liczba_miejsc(liczba_miejsc), typ_lakieru(typ_lakieru),
	Samochod(wersja, kolor, przebieg,
		id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc) {};

void Osobowy::show() {
	Samochod::show();
	cout << endl << "Liczba drzwi: " << this->liczba_drzwi;
	cout << endl << "Liczba miejsc: " << this->liczba_miejsc;
	cout << endl << "Typ lakieru: " << this->typ_lakieru<<endl;
}


Osobowy::~Osobowy() {
	
	//cout << endl << "Usunieto samochod osobowy" << endl;
}
