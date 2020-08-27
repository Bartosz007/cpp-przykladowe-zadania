#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>      

#define M_PI 3.141592653589793
#define WYNIKI 9
#define KROKI 150
#define DZIELNIK 1.4

using namespace std;

template<typename T> inline T f(T x) {
	return sin(x);
}
template<typename T> inline T df(T x) {
	return cos(x);
}
template <typename T> inline T _2p_roznica_progresywna(T x, T h) {
	return (f(x + h) - f(x)) / h;
}
template <typename T> inline T _2p_roznica_wsteczna(T x, T h) {
	return (f(x) - f(x - h)) / h;
}
template <typename T> inline T _2p_roznica_centralna(T x, T h) {
	return (f(x + h) - f(x - h)) / (2 * h);
}
template <typename T> inline T _3p_roznica_progresywna(T x, T h) {
	return ((T)-3 * f(x) + (T)4 * f(x + h) - f(x + h + h)) / (T(2) * h);
}
template <typename T> inline T _3p_roznica_wsteczna(T x, T h) {
	return ((T)3 * f(x) - (T)4 * f(x - h) + f(x - h - h)) / ((T)2 * h);
}

template <typename T> void wypisz_tablice_2d(T** dane, int k, int l) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < l; j++) {
			cout << dane[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename T> T** wyznacz_roznice(T** dane, int liczba_krokow) {//
	T start = (T)0;
	T koniec = (T)M_PI / (T)2;
	T srodek = (start + koniec) / (T)2;

	T h = (T)0.1;
	for (int i = 0; i < liczba_krokow; i++) {

		dane[i] = new T[WYNIKI];

		dane[i][0] = log10(fabs(df(start) - _2p_roznica_progresywna(start, h)));


		dane[i][1] = log10(fabs(df(srodek) - _2p_roznica_progresywna(srodek, h)));
		dane[i][2] = log10(fabs(df(srodek) - _2p_roznica_centralna(srodek, h)));
		dane[i][3] = log10(fabs(df(srodek) - _2p_roznica_wsteczna(srodek, h)));

		dane[i][4] = log10(fabs(df(koniec) - _2p_roznica_wsteczna(koniec, h)));


		dane[i][5] = log10(fabs(df(start) - _3p_roznica_progresywna(start, h)));

		dane[i][6] = log10(fabs(df(srodek) - _3p_roznica_progresywna(srodek, h)));
		dane[i][7] = log10(fabs(df(srodek) - _3p_roznica_wsteczna(srodek, h)));

		dane[i][8] = log10(fabs(df(koniec) - _3p_roznica_wsteczna(koniec, h)));

		h = h / (T)DZIELNIK;
	}

	return dane;
};


template <typename T> void zapis_do_pliku(T** dane, int k, int l, string nazwa) {
	fstream plik, dokladnosc;
	plik << scientific;
	plik.precision(15);
	plik.open(nazwa, ios::out);

	stringstream ss;
	ss << "rzad_dokladnosci_" << nazwa;
	dokladnosc << scientific;
	dokladnosc.precision(15);
	dokladnosc.open(ss.str(), ios::out);

	if (plik.good() != true) {
		cout << "Nie udalo sie otworzyc pliku: " << nazwa << endl;
		return;
	}

	T h = 0.1;
	for (int i = 0; i < k; i++) {
		plik << log10(h) << " ";

		for (int j = 0; j < l; j++) {
			plik << dane[i][j] << " ";
		}
		
		plik << endl;
		h = h / DZIELNIK;
	}
	   	
	for (int i = 0; i < l; i++) {
		dokladnosc << fabs( (dane[1][i] - dane[0][i]) / (dane[1][0] - dane[0][0]) ) << endl;
	}


	plik.close();
	dokladnosc.close();
}

int main()
{

	cout << scientific;
	cout.precision(10);

	double** roznice_double = new double* [KROKI];
	roznice_double = wyznacz_roznice(roznice_double, KROKI);

	zapis_do_pliku(roznice_double, KROKI, WYNIKI, "blad_double.txt");

	float** roznice_float = new float* [KROKI];
	roznice_float = wyznacz_roznice(roznice_float, KROKI);

	zapis_do_pliku(roznice_float, KROKI, WYNIKI, "blad_float.txt");
	cout << "Wykonano obliczenia!\n";
}
