#include "Dostawczy.h"
#include <iostream>
using namespace std;
extern string pl(string);
Dostawczy::Dostawczy( string& typ, string& dopuszczalna_masa, string& dlugosc, string& szerokosc, string& wysokosc,
	string& wersja, string& kolor, string& przebieg,
	string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc) :
	typ(typ), dopuszczalna_masa(dopuszczalna_masa), dlugosc(dlugosc), szerokosc(szerokosc), wysokosc(wysokosc),
	Samochod(wersja, kolor, przebieg, id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc) {};


void Dostawczy::show() {
	Samochod::show();
	cout << endl << "Typ: " << this->typ;
	cout << endl << "Dopuszczalna masa: " << this->dopuszczalna_masa;
	cout << endl << pl("D³ugoœæ: ") << this->dlugosc;
	cout << endl << pl("Szerokoœæ: ") << this->szerokosc;
	cout << endl << pl("Wysokoœæ: ") << this->wysokosc << endl ;
}
Dostawczy::~Dostawczy() {
	
	//cout << endl << "Usunieto dostawczy! " << endl;
}
