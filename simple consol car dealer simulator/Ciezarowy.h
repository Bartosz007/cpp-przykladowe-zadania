#pragma once
#ifndef CIEZAROWY_H
#define CIEZAROWY_H

#include "Samochod.h"
class Ciezarowy :public Samochod {
protected:
	string liczba_osi,
		dop_masa_calkowita,
		dop_ladownosc;
public:
	Ciezarowy(string &liczba_osi, string &dop_masa_calkowita, string &dop_ladownosc,
		string& wersja, string& kolor, string& przebieg,
		string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc);
	virtual ~Ciezarowy();
	void show();
	friend bool zapisz_dane(Pojazd*);
};

#endif // !CIEZAROWY_H

