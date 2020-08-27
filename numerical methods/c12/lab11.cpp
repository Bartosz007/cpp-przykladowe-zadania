#include <iostream>
#include <fstream>
#define WEZLY 17
#define KROKI 150;
using namespace std;

double fun(double x) {
	return 1 / (1 + 10 * x * x * x * x * x * x);
}

void wezly_rownoodlegle(double a, double b, int wezly, double* wsk_x, double* wsk_y) {

	double krok_wezly = (b - a) / (wezly - 1.0);
	int i = 0;

	double x = a;
	while (x <= b) {
		wsk_x[i] = x;
		wsk_y[i] = fun(x);
		x = x + krok_wezly;
		i++;
	}

}

void wezly_Czybyszew(double a, double b, int wezly, double* wsk_x, double* wsk_y) {

	for (int i = 0; i < wezly; i++) {
		wsk_x[i] = cos(((2.0 * i + 1.0) * 3.14159265359) / (2.0 * wezly + 2)); //z równiania (a+b)/2 + (b-a)/2*ksi = (1-1)/2+(1+1)/2*ksi = ksi
		wsk_y[i] = fun(wsk_x[i]);
	}
}

void baza_Newtona(double* wsk_x, double* wsk_y, int wezly) {

	for (int j = wezly - 1, k = 1; j > 0; j--, k++) {
		for (int i = wezly - 1; i >= k; i--) {
			wsk_y[i] = (wsk_y[i] - wsk_y[i - 1]) / (wsk_x[i] - wsk_x[i - k]);
		}
	}
}


int main()
{

	double a = -1.0;
	double b = 1.0;

	double* x_rownoodlegly;
	double* y_rownoodlegly;

	double* x_czybyszew;
	double* y_czybyszew;

	x_rownoodlegly = new double[WEZLY];
	y_rownoodlegly = new double[WEZLY];

	x_czybyszew = new double[WEZLY];
	y_czybyszew = new double[WEZLY];

	//zapełnianie węzłami
	wezly_rownoodlegle(a, b, WEZLY, x_rownoodlegly, y_rownoodlegly);
	wezly_Czybyszew(a, b, WEZLY, x_czybyszew, y_czybyszew);

	//obliczanie y
	baza_Newtona(x_rownoodlegly, y_rownoodlegly, WEZLY);
	baza_Newtona(x_czybyszew, y_czybyszew, WEZLY);

	double h = (b - a) / KROKI;
	double fx_c, fx_r;
	fstream zapis;
	zapis.open("wykres.txt", fstream::out);
	zapis.precision(20);
	zapis << scientific;
	//obliczanie punktów	
	for (double x = a; x <= b; x += h) {
		fx_r = y_rownoodlegly[WEZLY - 1];
		fx_c = y_czybyszew[WEZLY - 1];
		for (int i = WEZLY - 1; i >= 0; i--) {
			fx_r = fx_r * (x - x_rownoodlegly[i]) + y_rownoodlegly[i];
			fx_c = fx_c * (x - x_czybyszew[i]) + y_czybyszew[i];
		}

		zapis << x << " " << fun(x) << " ";
		zapis << fx_r << " ";
		zapis << fx_c;
		zapis << endl;
	}
	zapis.close();

	cout << "Wykonano obliczenia" << endl;
}