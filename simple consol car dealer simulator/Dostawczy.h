#pragma once
#ifndef DOSTAWCZY_H
#define DOSTAWCZY_H

#include "Samochod.h"
class Dostawczy :public Samochod {
protected:
	string typ,
		dopuszczalna_masa,
		dlugosc,
		szerokosc,
		wysokosc;
public:
	Dostawczy(string &typ, string &dopuszczalna_masa, string &dlugosc, string &szerokosc, string &wysokosc,
		string& wersja, string& kolor, string& przebieg,
		string& id,string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc);
	virtual ~Dostawczy();
	void show();
	friend bool zapisz_dane(Pojazd*);
};

#endif // !DOSTAWCZY_H