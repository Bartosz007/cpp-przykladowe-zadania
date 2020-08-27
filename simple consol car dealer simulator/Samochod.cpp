#include "Samochod.h"
#include <iostream>
using namespace std;

Samochod::Samochod(string& wersja, string& kolor, string& przebieg, 
	string& id,string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc)
	:wersja(wersja), kolor(kolor), przebieg(przebieg),Pojazd(id,masa, rok_produkcji, pojemnosc, rodzaj_paliwa, marka, model, moc) {};

void Samochod::show() {
	Pojazd::show();
	cout << endl << "Wersja: " << this->wersja;
	cout << endl << "Kolor: " << this->kolor;
	cout << endl << "Przebieg: " << this->przebieg;
}

Samochod::~Samochod() {
	//cout << "Usunieto samochod!" << endl;
}



