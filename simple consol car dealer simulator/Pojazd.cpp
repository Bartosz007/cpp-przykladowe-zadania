#include "Pojazd.h"
#include <iostream>

using namespace std;
extern string pl(string);

Pojazd::Pojazd(string& id, string& masa, string& rok_produkcji, string& pojemnosc, string& rodzaj_paliwa, string& marka, string& model, string& moc)
	:id(id), masa(masa), rok_produkcji(rok_produkcji), pojemnosc(pojemnosc), rodzaj_paliwa(rodzaj_paliwa), marka(marka), model(model), moc(moc) {};

void Pojazd::show() {
	
	cout << endl <<  "ID: " << this->id;
	cout << endl << "Marka: " << this->marka;
	cout << endl << "Model: " << this->model;
	cout << endl << "Masa: " << this->masa;
	cout << endl << "Rok produkcji: " << this->rok_produkcji;
	cout << endl << "Rodzaj paliwa: " << this->rodzaj_paliwa;
	cout << endl << pl("Pojemnoœæ: ") << this->pojemnosc;
};

void Pojazd::shortShow(){
	cout << endl << "ID: " << this->id;
	cout << endl << "Marka: " << this->marka;
	cout << endl << "Model: " << this->model<<endl;
};

string Pojazd::getId() {
	return this->id;
}

Pojazd::~Pojazd() {
	
	//cout << "Usunieto pojazd!" << endl;
};

