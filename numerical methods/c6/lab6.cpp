#include <iostream>
#include <fstream>
#define N 6
#define K N/2
using namespace std;

void redukcjeLDU(double M[K][N], double* b);

void wyznaczanieX(double M[K][N], double* b, double x[N]);

void piszWektor(double w[N], int k);

void piszMacierz3D(double M[K][N], int k, int l);

fstream zapis;

int main() {
	zapis.open("lab6.txt", ios::out);

	double M[K][N] = { {1.0 / 2.0, 1.0 / 4.0, 1.0 / 6.0, 1.0 / 8.0, 1.0 / 10.0, 0.0	},
						{10.0, 20.0, 30.0, 30.0, 20.0, 10.0},
						{0.0, 1.0 / 3.0, 1.0 / 5.0, 1.0 / 7.0, 1.0 / 9.0, 1.0 / 11.0 } };

	double b[N] = { 31.0, 165.0 / 4.0, 917.0 / 30.0, 851.0 / 28.0, 3637.0 / 90.0, 332.0 / 11.0 };

	double x[N];

	cout << "Startowa macierz M:" << endl;
	zapis << "Startowa macierz M:" << endl;
	piszMacierz3D(M, K, N);
	cout << "Startowy wektor b:" << endl;
	zapis << "Startowy wektor b:" << endl;
	piszWektor(b, N);

	redukcjeLDU(M, b);
	cout << "Macierz M po redukcji:" << endl;
	zapis << "Macierz M po redukcji:" << endl;
	piszMacierz3D(M, K, N);


	wyznaczanieX( M, b, x);
	cout << "Wektor x po obliczeniach:" << endl;
	zapis << "Wektor x po obliczeniach:" << endl;
	piszWektor(x, N);

	zapis.close();
	return 0;
}

void piszMacierz3D(double M[K][N], int k, int l)
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

void piszMacierz3Dw2D(double M[N][N],  int l)
{

	for (int i = 0; i < l; i++) {
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

void piszWektor(double w[N], int k)
{

	for (int i = 0; i < k; i++) {
		cout << w[i] << " ";
		zapis << w[i] << " ";
	}
	zapis << endl << endl;
	cout << endl << endl;
}

void redukcjeLDU(double M[K][N], double* b) {
	cout << "Redukcje LDU: " << endl;
	zapis << "Redukcje LDU: " << endl;
	cout << "Redukcja D: " << endl;
	zapis << "Redukcja D: " << endl;
	for (int i = 1; i < N; i++) {
		M[1][i] = M[1][i] - (M[2][i] / M[1][i - 1] * M[0][i - 1]);
		cout << "Iteracja I: " << i << endl;
		zapis << "Iteracja I: " << i << endl;
		piszMacierz3D(M, K, N);
	}

	cout << "Redukcja b: " << endl;
	zapis << "Redukcja b: " << endl;
	for (int i = 1; i < N; i++) {
		b[i] = b[i] - (M[2][i] / M[1][i - 1] * b[i - 1]);
		cout << "Iteracja I: " << i << endl;
		zapis << "Iteracja I: " << i << endl;
		piszMacierz3D(M, K, N);
	}

}

void wyznaczanieX(double M[K][N], double* b, double x[N]) {
	cout << "Wyznaczanie x: "<<endl;
	zapis << "Wyznaczanie x: " << endl;
	x[N - 1] = b[N - 1] / M[1][N - 1];

	for (int i = N - 2; i >= 0; i--) {
		x[i] = (b[i] - M[0][i] * x[i + 1]) / M[1][i];
		cout << "Iteracja I: " << N-i << endl;
		zapis << "Iteracja I: " << N - i << endl;
		piszWektor(x, N);
	}

}