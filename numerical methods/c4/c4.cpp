#include <iostream>
#include <fstream>
#define ITER 20
#define TOLX 1e-16
#define TOLF 1e-16

using namespace std;

double f1(double x, double y, double z);

double f2(double x, double y);

double f3(double x, double y);
double max(double a, double b, double c);
void newton(double x, double y, double z);

int main()
{
//	newton(4, 5, 7);
	newton(4, 5, 700);
}

double f1(double x, double y, double z) {
	return x * x + y * y + z * z - 2.0;
}

double f2(double x, double y) {
	return x * x + y * y - 1.0;
}

double f3(double x, double y) {
	return x * x - y;
}

double max(double *tab) {
	double max = tab[0];
	if (tab[1] > max)
		max = tab[1];
	if (tab[2] > max)
		max = tab[2];

	return max;
}

void newton(double x, double y, double z) {
	double jacobi[3][3];
	double delta[3];
	double f[3];

	fstream plik;
	plik.open("wynikic4.txt", ios::out);

	if (plik.good() != true) {
		cout << "Bład otwarcia pliku" << endl;
		return;
	}
	double estymator[3], reziduum[3];
	for (int i = 0; i < 3; i++) {//nie dało się wypełnić zerami
		estymator[i] = 1.;
		reziduum[i] = 1.;
	}


	f[0] = f1(x, y, z);
	f[1] = f2(x, y);
	f[2] = f3(x, y);

	int i = 0;
	cout.precision(20);
	cout << scientific;
	plik.precision(20);
	plik << scientific;
	while (i<ITER && max(estymator)>TOLX&& max(reziduum) > TOLF) {

		if (z == 0 || y == -0.5 || x == 0) {
			cout << "dzielenie przez zero, przerwano funkcje" << endl;
			break;
		}

		delta[0] = (x * x - ((y * y + 1) / (2 * y + 1))) / (2 * x);
		delta[1] = (y*y+y-1)/(2*y+1);
		delta[2] = (z * z - 1) / (2 * z);

		jacobi[0][0] = 2.0*x;
		jacobi[0][1] = 2.0 * y;
		jacobi[0][2] = 2.0 * z;
		jacobi[1][0] = 2.0 * x;
		jacobi[1][1] = 2.0 * y;
		jacobi[1][2] = 0.0;
		jacobi[2][0] = 2 * x;
		jacobi[2][1] = -1;
		jacobi[2][2] = 0.0;

		x = x - delta[0];
		y = y - delta[1];
		z = z - delta[2];

		f[0] = f1(x, y, z);
		f[1] = f2(x, y);
		f[2] = f3(x, y);

		for (int i = 0; i < 3; i++) {
			estymator[i] = fabs(delta[i]);
			reziduum[i] = fabs(f[i]);
		}
		cout <<endl<< "Iteracja :" << i + 1 << endl;
		cout << "x: " << x << " estymator: " << estymator[0] << " reziduum: " << reziduum[0] <<endl;
		cout << "y: " << y << " estymator: " << estymator[1] << " reziduum: " << reziduum[1] <<endl;
		cout << "z: " << z << " estymator: " << estymator[2] << " reziduum: " << reziduum[2] <<endl;

		plik << endl << "Iteracja :" << i + 1 << endl;
		plik << "x: " << x << " estymator: " << estymator[0] << " reziduum: " << reziduum[0] << endl;
		plik << "y: " << y << " estymator: " << estymator[1] << " reziduum: " << reziduum[1] << endl;
		plik << "z: " << z << " estymator: " << estymator[2] << " reziduum: " << reziduum[2] << endl;
		
		i++;
	}

	cout << fixed;
	cout << endl << endl << "Wyniki koncowe w zwyklej notacji" << endl;
	cout << "X: " << endl;
	cout << "x: " << x << " estymator: " << estymator[0] << " reziduum: " << reziduum[0] << endl << endl;
	cout << "Y: " << endl;
	cout << "y: " << y << " estymator: " << estymator[1] << " reziduum: " << reziduum[1] << endl << endl;
	cout << "Z: " << endl;
	cout << "z: " << z << " estymator: " << estymator[2] << " reziduum: " << reziduum[2] << endl << endl;

	plik.close();

}

