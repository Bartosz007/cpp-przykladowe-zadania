#pragma once
#ifndef OSOBOWY_H
#define OSOBOWY_H
#include "Samochod.h"
#include <string>

class Osobowy :public Samochod
{
protected:
	string liczba_drzwi,
		liczba_miejsc,
		typ_lakieru;

public:
	Osobowy(string& liczba_drzwi, string& liczba_miejsc, string& typ_lakieru,
		string& wersja, string& kolor, string& przebieg,
		string& id,string& masa, string& rok_produkcji, string& pojemnosc, string& marka, string& model, string& rodzaj_paliwa, string& moc);

	virtual ~Osobowy();
	virtual void show();
	friend bool zapisz_dane(Pojazd*);
};

#endif