#pragma once
#ifndef IO_H
#define IO_H

#include "Pojazd.h"
#include "Lista.h"

extern bool zapisz_dane(Pojazd* );
extern Lista <string*> wczytaj_dane();
extern Lista <Pojazd*> stringToObj(Lista <string*>);
extern string* dane(string, string[], int);

#endif