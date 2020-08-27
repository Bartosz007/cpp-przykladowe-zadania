#include <iostream>
#include <string>
#include <sstream>

#include "Pojazd.h"
#include "Osobowy.h"
#include "Motocykl.h"
#include "Dostawczy.h"
#include "Ciezarowy.h"

#include "kreatory.hpp"
#include <time.h>
#include "menu.hpp"
#include "funkcje.hpp"

using namespace std;

inline void dopisz(string s) {
	cout << ">Podaj " << s;
}

int typ_pojazdu() {
	int stan = 1;

	while (stan) {
		string akcja;
		cout << pl("Wpisz 'auto', aby doda� samoch�d") << endl;
		cout << pl("Wpisz 'moto', aby doda� motocykl ") << endl;
		cout << pl("Wpisz 'exit', aby si� cofn�� do poprzedniego menu") << endl;
		cin >> akcja;
		stan = menu(akcja, "auto$", "moto$", "exit$");

		if (stan < 3) {
			return stan;
		}
		else {
			cout << pl(">>B��dne polecenie") << endl;
		}

	}
	return 0;
}

Pojazd* kreator(int typ_pojazdu) {
	if (typ_pojazdu == 1) {
		int typ2 = 1;
		while (typ2) {
			cout << pl(">>Wybrales samochod, wybierz kategorie") << endl;

			string akcja;
			cout << pl("Wpisz 'osobowy', aby doda� samoch�d osobowy") << endl;
			cout << pl("Wpisz 'dostawczy', aby doda� samoch�d dostawczy") << endl;
			cout << pl("Wpisz 'ciezarowy', aby doda� samoch�d ci�arowy") << endl;
			cout << pl("Wpisz 'exit', aby si� cofn�� do poprzedniego menu") << endl;
			cin >> akcja;
			typ2 = menu(akcja, "osobowy$", "dostawczy$", "ciezarowy$", "exit$");

			if (typ2 == 0)
				return NULL;
			else if (typ2 < 4)
				return kreatorSamochodu(typ2);

		}
	}
	else if (typ_pojazdu == 2) {
		return kreatorMotocyklu();
	}

	return NULL;
}

Pojazd* kreatorSamochodu(int typ2) {

	string id = "id";
	string masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc;
	cout << pl(">>Witaj w kreatorze samochodu, czeka Ci� kilka etap�w wprowadzania danych") << endl;
	cout << pl(">>Etap pierwszy - dane pojazdu") << endl;

	time_t czas;
	time(&czas);
	stringstream ss;
	ss << czas;
	string czass = ss.str();
	czass = czass.substr(5, 5);
	id.insert(id.length(), czass);

	cin.ignore();
	dopisz(pl("mark�: "));
	getline(cin, marka);

	dopisz("model: ");
	getline(cin, model);
	dopisz(pl("mas�: "));
	getline(cin, masa);
	dopisz("rok produkcji: ");
	getline(cin, rok_produkcji);
	dopisz("rodzaj paliwa: ");
	getline(cin, rodzaj_paliwa);
	dopisz(pl("pojemno��: "));
	getline(cin, pojemnosc);
	dopisz(pl("moc: "));
	getline(cin, moc);

	string wersja, kolor, przebieg;
	cout << ">>Etap drugi - dane samochodu" << endl;

	dopisz(pl("wersj� modelu: "));;
	getline(cin, wersja);
	dopisz("kolor: ");
	getline(cin, kolor);
	dopisz("przebieg: ");
	getline(cin, przebieg);


	if (typ2 == 1) {
		cout << ">>Etap trzeci - dane samochodu osobowego" << endl;
		string liczba_drzwi, liczba_miejsc, typ_lakieru;
		dopisz(pl("liczb� drzwi: "));
		getline(cin, liczba_drzwi);
		dopisz(pl("liczb� miejsc: "));
		getline(cin, liczba_miejsc);
		dopisz("typ lakieru: ");
		getline(cin, typ_lakieru);
		return new Osobowy(liczba_drzwi, liczba_miejsc, typ_lakieru,
			wersja, kolor, przebieg,
			id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc);
	}
	else if (typ2 == 2) {
		cout << "Etap trzeci - dane samochodu dostawczego" << endl;
		string typ, dopuszczalna_masa, dlugosc, szerokosc, wysokosc;
		dopisz("typ: ");
		getline(cin, typ);
		dopisz(pl("dopuszczaln� mas�: "));
		getline(cin, dopuszczalna_masa);
		dopisz(pl("d�ugo��: "));
		getline(cin, dlugosc);
		dopisz(pl("szeroko��: "));
		getline(cin, szerokosc);
		dopisz(pl("wysoko��: "));
		getline(cin, wysokosc);
		return new Dostawczy(typ, dopuszczalna_masa, dlugosc, szerokosc, wysokosc, wersja, kolor, przebieg,
			id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc);

	}
	else if (typ2 == 3) {
		cout << "Etap trzeci - dane samochodu ciezarowego -" << endl;
		string liczba_osi, dop_masa_calkowita, dop_ladownosc;
		dopisz(pl("liczb� osi: "));
		getline(cin, liczba_osi);
		dopisz(pl("dopuszczaln� mas� ca�kowit�: "));
		getline(cin, dop_masa_calkowita);
		dopisz(pl("dopuszczaln� �adowno��: "));
		getline(cin, dop_ladownosc);
		return new Ciezarowy(liczba_osi, dop_masa_calkowita, dop_ladownosc, wersja, kolor, przebieg,
			id, masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc);
	}

	return NULL;//�eby kompilator by� zadowolony
}

Pojazd* kreatorMotocyklu() {

	string id = "id";
	string masa, rok_produkcji, pojemnosc, marka, model, rodzaj_paliwa, moc;
	cout << pl(">>Witaj w kreatorze pojazdu, czeka Ci� kilka etap�w wprowadzania danych") << endl;
	cout << ">>Etap pierwszy - dane podstawowe" << endl;

	time_t czas;
	time(&czas);
	stringstream ss;
	ss << czas;
	string czass = ss.str();
	czass = czass.substr(5, 5);
	id.insert(id.length(), czass);

	cin.ignore();
	dopisz(pl("marke: "));
	getline(cin, marka);
	dopisz("model: ");
	getline(cin, model);
	dopisz(pl("mas�: "));
	getline(cin, masa);
	dopisz("rok produkcji: ");
	getline(cin, rok_produkcji);
	dopisz("rodzaj paliwa: ");
	getline(cin, rodzaj_paliwa);
	dopisz(pl("pojemno��: "));
	getline(cin, pojemnosc);
	dopisz("moc: ");
	getline(cin, moc);

	string wersja, kolor, przebieg, rodzaj_napedu, typ_silnika, typ;
	cout << "Etap drugi - dane motocyklu" << endl;
	dopisz(pl("wersj�: "));
	getline(cin, wersja);
	dopisz("kolor: ");
	getline(cin, kolor);
	dopisz("przebieg: ");
	getline(cin, przebieg);
	dopisz(pl("rodzaj nap�du: "));
	getline(cin, rodzaj_napedu);
	dopisz("typ silnika: ");
	getline(cin, typ_silnika);
	dopisz("typ: ");
	getline(cin, typ);
	return new Motocykl(wersja, kolor, przebieg, rodzaj_napedu, typ_silnika, typ,
		id, masa, rok_produkcji, pojemnosc, rodzaj_paliwa, marka, model, moc);
}

