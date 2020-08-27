#include "Ciezarowy.h"
#include <iostream>
using namespace std;
extern string pl(string);
Ciezarowy::Ciezarowy(string& liczba_osi, string& dop_masa_calkowita, string& dop_ladownosc,
	string& wersja, string& kolor, string& przebieg,
	string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc)
	:liczba_osi(liczba_osi), dop_masa_calkowita(dop_masa_calkowita), dop_ladownosc(dop_ladownosc),
	Samochod( wersja, kolor, przebieg, 
		id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc) {};

void Ciezarowy::show() {
	Samochod::show();
	cout << endl << "Liczba osi: " << this->liczba_osi;
	cout << endl << pl("Dopuszczalna masa ca³kowita: ") << this->dop_masa_calkowita;
	cout << endl << pl("Dopuszczalna ³adownoœæ: ") << this->dop_ladownosc << endl;
}
Ciezarowy::~Ciezarowy() {

//	cout << endl << "Usunieto ciezarowy" << endl;
};