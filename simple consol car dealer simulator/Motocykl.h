#pragma once
#ifndef MOTOCYKL_H
#define MOTOCYKL_H

#include "Pojazd.h"

class Motocykl :public Pojazd {
protected:
	string wersja,
		kolor,
		przebieg,
		rodzaj_napedu,
		typ_silnika,
		typ;
public:
	Motocykl(string& wersja, string& kolor, string& przebieg, string& rodzaj_napedu, string& typ_silnika, string& typ,
		string& id,string& masa, string& rok_produkcji, string& pojemnosc, string& rodzaj_paliwa, string& marka, string& model, string& moc);
	virtual ~Motocykl();
	void show();
	friend bool zapisz_dane(Pojazd *);
};

#endif // 

