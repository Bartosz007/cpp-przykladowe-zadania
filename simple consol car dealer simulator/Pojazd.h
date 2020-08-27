#pragma once
#ifndef POJAZD_H
#define POJAZD_H
#include <string>

using namespace std;

class Pojazd
{
protected:
	string id,
		masa,
		rok_produkcji,
		pojemnosc,
		marka,
		model,
		rodzaj_paliwa,
		moc;
public:
	Pojazd(string &id,string &masa, string &rok_produkcji, string &pojemnosc, string &rodzaj_paliwa,string &marka, string &model,string &moc);
	~Pojazd();
	string getId();
	virtual void show();
	friend bool zapisz_dane(Pojazd *);
	void shortShow();
};

#endif // !POJAZD_H
