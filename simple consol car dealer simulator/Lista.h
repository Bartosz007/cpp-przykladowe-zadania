#pragma once
#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "funkcje.hpp"
using namespace std;

class Element;
template <class T>

class Lista
{
public:
	Lista();
	~Lista();

	class Element {
	public:
		T value;
		Element* next;
		Element(T wartosc) {
			value = wartosc;
			next = NULL;
		};
	};

	void show();//zrobione
	void add(T value);//zrobione
	void del(int x);//zrobione
	void remove();//zrobione
	int length();//zrobione
	bool isNull();

	Element get(int x) {//inaczej nie chcia³o zaskoczyæ
		int l = length(),
			licznik = 0;
		if (x < l && head != NULL) {
			Element* tmp = head;
			while (x != licznik && tmp != NULL) {
				tmp = tmp->next;
				licznik++;
			}
			return *tmp;
		}

		return NULL;//wyrzuci NULLPTR jeœli x>=l
	}

	/*
	Element* getPointer(int x);
	Element* getHead();
	Element* getTail();*/

private:
	Element* head;
	Element* tail;
};

//----------------------metody do klasy zewnêtrznej------------------------
template <class T>
Lista<T>::Lista() {
	head = NULL;
	tail = NULL;
};

template <class T>
Lista<T>::~Lista() {
	//cout << "Usunieto liste" << endl;
};

//----------------------metody do klasy wewnêtrznej------------------------
template <class T>
void Lista<T>::add(T wartosc) {
	if (head != NULL) {
		Element* tmp = new Element(wartosc);
		if (tmp == NULL) throw "Blad alokacji pamiêci, przy dodawaniu elementu do listy!";
		tail->next = tmp;
		tail = tmp;
	}
	else {
		head = new Element(wartosc);
		tail = head;
	}
}

template <class T>
void Lista<T>::show() {
	if (head != NULL) {
		Element* tmp = head;
		while (tmp != NULL) {
			cout << tmp->value;
			tmp = tmp->next;
		}
	}	
}

template <class T>
int Lista<T>::length() {
	int licznik = 0;
	Element* tmp = head;
		while (tmp != NULL) {
			tmp = tmp->next;
			licznik++;
		}

	return licznik;
}

template <class T>
void Lista<T>::del(int x) {//numeracja jak w tablicach
	if (head != NULL) {
		int l = length();
		if (head != NULL && l >= x) {


			if (l == 1) {//pierwszy element listy i jedyny
				head = NULL;
				tail = NULL;
			}
			else if (x == 0) {//lista dwuelementowa - usuwamy pierwszy element
				Element* tmp = head;
				head = head->next;
				delete tmp;
			}
			else if (l == x) {//ostatni element listy
				Element* tmp2 = head;
				while (tmp2 != NULL) {
					Element* tmp3 = tmp2->next;
					if (tmp3->next == NULL) {
						delete tmp3;
						tmp2->next = NULL;
						break;
					}

					tmp2 = tmp2->next;
				}
			}

			else {
				int licznik = 0;
				Element* tmp = NULL;
				Element* tmp2 = head;
				while (tmp2 != NULL && licznik != x) {
					tmp = tmp2;
					tmp2 = tmp2->next;
					licznik++;
				}
				tmp->next = tmp2->next;
				delete tmp2;
			}

			cout <<pl("Usuniêto ") << x << " element" << endl;
		}
	}
	else {
		cout << "Lista jest pusta" << endl;
	}
}

template <class T>
void Lista<T>::remove() {//usuwa wszystkie elementy listy i pozostawia puste wskaŸniki head i tail,
	//aby usun¹æ listê z pamiêci, nale¿y zdefiniowaæ j¹ przez wskaŸnik, a do usuniêci¹ u¿yæ operatora delete
	Element* tmp = head;
	Element* tmp2 = head->next;
	while (tmp2 != NULL) {
		delete tmp;
		tmp2 = tmp2->next;
	}
	cout << "Wyczyszono liste" << endl;
	head = NULL;
	tail = NULL;
}

template <class T>
bool Lista<T>::isNull() {
	if (head == NULL)
		return 0;
	else
		return 1;
}
#endif // !LISTA_H