#pragma once
#ifndef SAMOCHOD_H
#define SAMOCHOD_H
#include "Pojazd.h"

class Samochod :public Pojazd {
protected:
	string 	wersja,
		kolor,
		przebieg;
public:
	Samochod(string& wersja, string& kolor, string& przebieg, 
		string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc);
	virtual ~Samochod();
	virtual void show();
};

#endif

