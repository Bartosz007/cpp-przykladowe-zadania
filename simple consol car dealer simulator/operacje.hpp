#pragma once
#ifndef OPERACJE_H
#define OPERACJE_H

#include "Pojazd.h"
#include "Lista.h"

extern void wyszukiwanie(Lista <Pojazd*>, string);
extern void usun(Lista <Pojazd*>, string);
extern Lista <Pojazd*> operator -(Lista <Pojazd*>, string);

#endif // !OPERACJE_H