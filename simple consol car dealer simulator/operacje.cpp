#include <fstream>

#include "operacje.hpp"
#include "funkcje.hpp"

#include "Motocykl.h"
#include "Pojazd.h"
#include "Osobowy.h"
#include "Motocykl.h"
#include "Dostawczy.h"
#include "Ciezarowy.h"


Lista <Pojazd*> stringToObj(Lista <string*> ilista) {
	Lista <Pojazd*> olista;
	for (int i = 0; i < ilista.length(); i++) {

		string* tablica = ilista.get(i).value;

		Pojazd* poj = NULL;
		if (tablica[0].find("Motocykl") != string::npos) {
			poj = new Motocykl(tablica[9], tablica[10], tablica[11], tablica[12], tablica[13], tablica[14],
				tablica[1], tablica[2], tablica[3], tablica[4], tablica[7], tablica[5], tablica[6], tablica[8]);
		}
		else if (tablica[0].find("Ciezarowy") != string::npos) {
			poj = new Ciezarowy(tablica[12], tablica[13], tablica[14], tablica[9], tablica[10], tablica[11],
				tablica[1], tablica[2], tablica[3], tablica[4], tablica[5], tablica[6], tablica[7], tablica[8]);
		}
		else if (tablica[0].find("Dostawczy") != string::npos) {
			poj = new Dostawczy(tablica[12], tablica[13], tablica[14], tablica[15], tablica[16],
				tablica[9], tablica[10], tablica[11],
				tablica[1], tablica[2], tablica[3], tablica[4], tablica[5], tablica[6], tablica[7], tablica[8]);
		}
		else if (tablica[0].find("Osobowy") != string::npos) {
			poj = new Osobowy(tablica[12], tablica[13], tablica[14],
				tablica[9], tablica[10], tablica[11],
				tablica[1], tablica[2], tablica[3], tablica[4], tablica[5], tablica[6], tablica[7], tablica[8]);
		}
		else {
			poj = NULL;
		}

		if (poj != NULL)
			olista.add(poj);

	}

	return olista;
};

void wyszukiwanie(Lista <Pojazd*> lista, string akcja) {
	string id = akcja.substr(5, 7);

	for (int i = 0; i < lista.length(); i++) {
		if (!id.compare(lista.get(i).value->getId())) {
			lista.get(i).value->show();

			return;
		}
	}
	cout << ">>Nie znaleziono takiego elementu" << endl;
}

Lista <Pojazd*> operator -(Lista <Pojazd*> lista, string akcja) {
	string id = akcja.substr(3, 7);

	for (int i = 0; i < lista.length(); i++) {
		if (!id.compare(lista.get(i).value->getId())) {
			lista.del(i);

			ofstream komis;
			try {
				komis.open("komis.txt", ios_base::trunc);
				komis.close();
			}
			catch (runtime_error & ex)
			{
				cout << endl << "Runtime error: " << ex.what() << endl;
				return lista;
			}
			catch (exception & ex) {
				cout << endl << pl(">>B³¹d: ") << ex.what() << endl;
				return lista;
			}

			for (int k = 0; k < lista.length(); k++) {
				bool a = zapisz_dane(lista.get(k).value);
			
				if (!a)
					cout << pl(">>B³ad") << endl;

				//	cout << ">>Usuniêto element z bazy" << endl;
				//else
					
			}

			return lista;
		}
	}
	cout << ">>Nie znaleziono takiego elementu" << endl;

	Lista <Pojazd*> a;
	return a;
}
