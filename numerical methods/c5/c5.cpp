#include <iostream>
#include <fstream>
#include <cmath>


void piszMacierz(double** M, int k, int l);
void piszWektor(double* w, int k);

void dekompozycjaLU(double** L, double** U, double* b, int n);
void ukladxy(double** L, double** U, double* b, double* x, double* y, int n);

using namespace std;

fstream zapis;

int main()
{
	fstream dane;
	dane.open("dane.txt", ios::in);
	zapis.open("lab5.txt", ios::out);

	int n;  //wielkość macierzy i wektora
	double** A, ** U, ** L;
	double* x, * y, * b;

	if (dane.good() != true)
	{
		cout << "Nie wczytano pliku " << endl;
		return 1;
	}

	double read;
	dane >> n;//rozmiar macierzy

	A = new double* [n];//zaalokowanie pamięci i wczytanie macierzy
	L = new double* [n];
	U = new double* [n];

	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
		L[i] = new double[n];
		U[i] = new double[n];

		for (int j = 0; j < n; j++) {
			dane >> read;
			A[i][j] = read;
			U[i][j] = read;
			L[i][j] = 0;
		}

	}

	x = new double[n];
	y = new double[n];
	b = new double[n];

	for (int i = 0; i < n; i++) {
		dane >> b[i];
		x[i] = 0;
		y[i] = 0;
	}
	cout << "Wczytano macierz A" << endl;
	zapis << "Wczytano macierz A" << endl;
	piszMacierz(A, n, n);
	cout << "Wczytano wektor b" << endl;
	zapis << "Wczytano wektor b" << endl;
	piszWektor(b, n);


	dekompozycjaLU(L, U, b, n);
	ukladxy(L, U, b, x, y, n);

	cout << "Wyniki koncowe: " << endl;
	zapis << "Wyniki koncowe: " << endl;
	cout << "Macierz A:" << endl;
	zapis << "Macierz A:" << endl;
	piszMacierz(A, n, n);
	cout << "Wektror b:" << endl;
	zapis << "Wektror b:" << endl;
	piszWektor(b, n);
	cout << "Macierz U:" << endl;
	zapis << "Macierz U:" << endl;
	piszMacierz(U, n, n);
	cout << "Macierz L:" << endl;
	zapis << "Macierz L:" << endl;
	piszMacierz(L, n, n);
	cout << "Wektror y:" << endl;
	zapis << "Wektror y:" << endl;
	piszWektor(y, n);
	cout << "Wektror x: " << endl;
	zapis << "Wektror x: " << endl;
	piszWektor(x, n);

	dane.close();

	return 0;
}

void piszMacierz(double** M, int k, int l)
{

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < l; j++) {
			cout << M[i][j] << " ";
			zapis << M[i][j] << " ";
		}
		cout << endl; 
		zapis << endl;
	}
	cout << endl;
	zapis << endl;
}

void piszWektor(double* w, int k)
{

	for (int i = 0; i < k; i++) {
		cout << w[i] << " ";
		zapis<<  w[i] << " ";
	}
	zapis<< endl << endl;
	cout << endl << endl;
}

void dekompozycjaLU(double** L, double** U, double* b, int n)
{
	cout << "Dekompozycja LU:" << endl << endl;
	zapis<< "Dekompozycja LU:" << endl << endl;
	for (int i = 0; i < n; i++) {       //eliminacja gaussa

		L[i][i] = 1;
		
		int a = i, ai = i;
		double max = U[i][i];

		for (int k = i; k < n; k++) { //wybieranie wersa macierzy do zamiany
			if (fabs(U[k][i]) > max) {
				max = fabs(U[k][i]);
				ai = k;
			}
		}

		double* t = U[i];  //zamiana wersów w macierzy U
		U[i] = U[ai];
		U[ai] = t;

		t = L[i];          //zamiana wersów w macierzy L
		L[i] = L[ai];
		L[ai] = t;

		double z = b[i];  //zamiana pozycji w wektorze b
		b[i] = b[ai];
		b[ai] = z;


		for (int k = i + 1; k < n; k++) { //obliczanie macierzy U
			double w = U[k][i] / U[i][i];//współczynnik dzielenia

			L[k][i] = w;
			for (int j = 0; j <= n; j++) {

				U[k][j] = U[k][j] - w * U[i][j];
			}
		}
		cout << "Iteracja I: "<<i << endl;
		zapis << "Iteracja I: " << i << endl;
		cout << "Macierz U: " << endl;
		zapis << "Macierz U: " << endl;
		piszMacierz(U, n, n);
		cout << "Macierz L: " << endl;
		zapis << "Macierz L: " << endl;
		piszMacierz(L, n, n);
	}

}

void ukladxy(double** L, double** U, double* b, double* x, double* y, int n) {
	cout << "Liczenie ukladu rownan: " << endl << endl;
	zapis << "Liczenie ukladu rownan: " << endl << endl;

	cout << "Wektor y: " << endl;
	zapis << "Wektor y: " << endl;

	y[0] = b[0];
	for (int i = 1; i < n; i++) {//obliczanie wektoru y

		y[i] = b[i];
		for (int j = 0; j < i; j++) {
			y[i] = y[i] - L[i][j] * y[j];

			cout << "Iteracja I:" << i << endl;
			zapis << "Iteracja I:" << i << endl;
			piszWektor(y,n);
		}
	}

	cout << "Wektor x: " << endl;
	zapis << "Wektor x: " << endl;

	x[n - 1] = y[n - 1] / U[n - 1][n - 1];
	for (int i = n - 1; i >= 0; i--) {//obliczanie wektoru y

		x[i] = y[i];
		for (int j = i + 1; j < n; j++) {
			x[i] = x[i] - U[i][j] * x[j];

			cout << "Iteracja I:" << i << endl;
			zapis << "Iteracja I:" << i << endl;
			piszWektor(x, n);

		}

		x[i] = x[i] / U[i][i];

	}

}
