#include "Motocykl.h"
#include <iostream>
using namespace std;
extern string pl(string);
Motocykl::Motocykl(string& wersja, string& kolor, string& przebieg, string& rodzaj_napedu, string& typ_silnika, string& typ,
	string& id,string& masa, string& rok_produkcji, string& pojemnosc, string& rodzaj_paliwa, string& marka, string& model, string& moc)
	:wersja(wersja), kolor(kolor), przebieg(przebieg), rodzaj_napedu(rodzaj_napedu), typ_silnika(typ_silnika), typ(typ),
	Pojazd(id,masa, rok_produkcji, pojemnosc, rodzaj_paliwa, marka, model, moc) {};

void Motocykl::show() {
	Pojazd::show();
	cout << endl << "Wersja: " << this->wersja;
	cout << endl << "Kolor: " << this->kolor;
	cout << endl << "Przebieg: " << this->przebieg;
	cout << endl << pl("Rodzaj napêdu: ") << this->rodzaj_napedu;
	cout << endl << "Typ silnika: " << this->typ_silnika;
	cout << endl << "Typ: " << this->typ << endl ;
}

Motocykl::~Motocykl() {

	//cout << endl << "Usunieto motocykl" << endl;
};

