#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <regex>

#include "Pojazd.h"
#include "Osobowy.h"
#include "Motocykl.h"
#include "Dostawczy.h"
#include "Ciezarowy.h"
#include "funkcje.hpp"
#include "kreatory.hpp"
#include "menu.hpp"
#include <time.h>
#include "Lista.h"
#include "io.hpp"
#include "operacje.hpp"

using namespace std;

int main()
{
	time_t czas;
	time(&czas);

	cout << ctime(&czas);

	cout << "-------------------------------\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "|      Serwis samochodowy     |\n";
	cout << "|                             |\n";
	cout << "|                             |\n";
	cout << "-------------------------------\n";

	int stan = 1;
	while (stan) {
		cout << pl("Wpisz 'spis' aby wyświetlić spis pojazdów") << endl;
		cout << pl("Wpisz 'dodaj' aby dodać pojazd do bazy") << endl;
		cout << pl("Wpisz 'exit', aby zamknąć program") << endl;

		string akcja;
		cin >> akcja;
		stan = menu(akcja, "spis$", "dodaj$", "exit$");

		if (stan == 1) {//spis pojazdow

			Lista <string*> dane = wczytaj_dane();//to dopiero lista z tablicą stringow, konwertujemy ją na listę obiektów
			Lista <Pojazd*> listaPojazdow = stringToObj(dane);
			if (listaPojazdow.length() == 0) {
				cout << pl(">>Brak pojazdów w bazie") << endl;
				continue;
			}
			else {
				for (int i = 0; i < listaPojazdow.length(); i++) {
					listaPojazdow.get(i).value->shortShow();
				}
			}

			string akcja;
			int op = 0;
			cin.ignore();
			while (op != 2) {

				cout << endl << pl("Wpisz 'info id_pojazdu' aby wyświetlić szczegóły") << endl;
				cout << pl("Wpisz 'rm id_pojazdu' aby usunąć pojazd z bazy") << endl;
				cout << pl("Wpisz 'exit', aby się cofnąć do poprzedniego menu") << endl;
				getline(cin, akcja);
				op = ~akcja;
				if (op == 0) {
					cout << pl("Błędne polecenie") << endl;
				}
				else if (op == 1) {//usuwanie - może być tu błąd
					listaPojazdow = listaPojazdow - akcja;
					for (int i = 0; i < listaPojazdow.length(); i++) {
						listaPojazdow.get(i).value->shortShow();
					}
				}
				else if (op == 3) {//wyszukiwanie
					wyszukiwanie(listaPojazdow, akcja);
				}
			}
		}
		else if (stan == 2) {//dodawanie pojazdow
			cout << endl << pl("Witaj w kreatorze pojazdów!") << endl << pl("Wybierz typ pojazdu jaki chcesz dodać: ") << endl;
			Pojazd* pojazd = NULL;
			int typ = typ_pojazdu();
			if (typ)
				pojazd = kreator(typ);

			if (pojazd != NULL) {
				cout << ">>Dodano pojazd " << endl << endl << "Dane: ";
				pojazd->show();
				zapisz_dane(pojazd);
				//	delete pojazd;
			}
			else
				cout << endl;

		}
		else if (stan == 3) {
			cout << pl(">>Błędne polecenie") << endl;
		}

	}

}