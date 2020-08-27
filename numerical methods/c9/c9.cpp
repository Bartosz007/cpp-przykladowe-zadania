#include<iostream>
#include<cmath>
#include<fstream>
#define IL_H 80000
#define DZIELNIK 1.4

using namespace std;

double p = 1.0, q = 0, r = -4;

// we wszystich czynnościach ponizej, wykorzystywana była funkcja -s, tudzież -(-x)=x, taki zabieg zmiejszy ilość odejmowań, a ponieważ odejmowanie jest numerycznie niestabilne, to staramy się go pomijać
double s(double x) {
	return (x);
}

double alfa = 0, beta = 1, gamma = -1;
double phi = 0, psi = 441, theta = 0; //psi może być dowolne, bo u(1)=0
double x_pocz = 0, x_kon = 1;

double rownanie_analityczne(double x) {
	return (exp(2 - 2 * x) - 4 * exp(4 - 2 * x) + 4 * exp(2 * x) - exp(2 + 2 * x) - x + x * exp(4)) / (4 - 4 * exp(4));
}

void redukcjeLDU(double** M, double* b, double* x, int N)
{
	double* l = new double[N];
	double* d = new double[N];
	double* u = new double[N];
	double* b_cp = new double[N];

	for (int i = 0; i < N; i++) {//kopiowanie
		l[i] = M[0][i];
		d[i] = M[1][i];
		u[i] = M[2][i];

		b_cp[i] = b[i];
	}


	for (int i = 1; i < N; i++) {
		d[i] = d[i] - l[i - 1] * (u[i - 1] / d[i - 1]);
	}

	for (int i = 1; i < N; i++) {
		b_cp[i] = b_cp[i] - l[i - 1] * b_cp[i - 1] / d[i - 1];
	}

	x[N - 1] = b_cp[N - 1] / d[N - 1];

	for (int i = N - 2; i >= 0; i--) {
		x[i] = (b_cp[i] - u[i] * x[i + 1]) / d[i];
	}

}

double max(double* blad, int n)
{
	double max = fabs(blad[0]);
	for (int i = 0; i < n; i++) {
		if (fabs(blad[i]) > max) {
			max = fabs(blad[i]);

		}
	}

	return max;
}

void numerowa(double** M, double* b, int n, double h) {

	for (int i = 1; i < n - 1; i++)
	{
		M[0][i - 1] = p / (h * h) + r / 12;
		M[1][i] = (-2.0 * p) / (h * h) + r * (10.0 / 12.0);
		M[2][i] = p / (h * h) + r / 12.0;
		b[i] = s(x_pocz + i * h - h) / 12.0 + (10.0 / 12.0) * s(x_pocz + i * h) + s(x_pocz + i * h + h) / 12.0;
	}

}

void konwencjonalna_trzypunktowa(double** M, double* b, int n, double h) {

	for (int i = 1; i < n - 1; i++)
	{
		M[0][i - 1] = p / (h * h) - q / (2.0 * h);
		M[1][i] = (-2.0 * p) / (h * h) + r;
		M[2][i] = p / (h * h) + q / (2.0 * h);
		b[i] = s(x_pocz + i * h);
	}

}

double* dyskretyzacja(void (*typ_dyskretyzacji)(double** M, double* b, int n, double h), double h, int n)
{
	double** M;
	double* b, * x, * blad;

	M = new double* [3];
	for (int i = 0; i < 3; i++)
		M[i] = new double[n];

	b = new double[n];
	x = new double[n];
	blad = new double[n];


	M[0][0] = 0;
	M[1][0] = beta - alfa / h;
	M[2][0] = alfa / h;
	b[0] = -gamma;

	typ_dyskretyzacji(M, b, n, h);

	M[0][n - 2] = -phi / h;
	M[1][n - 1] = -phi / h + psi;
	M[2][n - 1] = 0;
	b[n - 1] = -theta;


	redukcjeLDU(M, b, x, n);


	return x;

}



int main() {
	double h;
	fstream blad,wykres;
	double* wyniki_konwekcjonalna, * wyniki_numerowa, x_p,*blad_konwekcjonalna,*blad_numerowa;
	double maxblad;

	blad.open("blad.txt", ios::out);

	blad.precision(20);
	blad << scientific;


	for (int i = 3; i < IL_H; i=i+300) {
		h = (x_kon - x_pocz) / (i - 1);
		wyniki_konwekcjonalna = dyskretyzacja(konwencjonalna_trzypunktowa, h, i);
		wyniki_numerowa = dyskretyzacja(numerowa, h, i);
		x_p = x_pocz;

		blad_konwekcjonalna = new double[i - 1];
		blad_numerowa = new double[i - 1];

		for (int j = 0; j < (i - 1); j++)
		{
			blad_konwekcjonalna[j] = fabs(wyniki_konwekcjonalna[j] - rownanie_analityczne(x_p));
			blad_numerowa[j] = fabs(wyniki_numerowa[j] - rownanie_analityczne(x_p));
			x_p += h;
		}

		maxblad = max(blad_konwekcjonalna, i - 1);
		blad << log10(h) << " " << log10(maxblad)<< " ";
		maxblad = max(blad_numerowa, i - 1);

		blad << log10(maxblad) << endl;

		delete[] blad_konwekcjonalna;
		delete[] blad_numerowa;
		delete[] wyniki_konwekcjonalna;
		delete[] wyniki_numerowa;

	}
	blad.close();

	wykres.open("wykres.txt", ios::out);
	wykres.precision(20);
	wykres << scientific;

	h = (x_kon - x_pocz) / (101);
	x_p = x_pocz;
	wyniki_konwekcjonalna = dyskretyzacja(konwencjonalna_trzypunktowa, ((x_kon - x_pocz) / 100), 101);
	wyniki_numerowa = dyskretyzacja(numerowa, ((x_kon - x_pocz) / 100), 101);
	


	for (int j = 0; j < (100); j++)
	{
		wykres << x_p << " " << rownanie_analityczne(x_p) << " " << wyniki_konwekcjonalna[j] << " " << wyniki_numerowa[j] << endl;

		x_p += h;
	}
	wykres.close();
	cout << "Wykonano obliczenia" << endl;


	return 0;
}