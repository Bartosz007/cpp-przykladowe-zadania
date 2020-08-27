#include <iostream>
#include <fstream>
#define PI 3.14159265359

using namespace std;

double fun() {
    return 2.0/sqrt(PI);
}
double fun_e(double x) {
    return exp(-x * x);
}

double calkowanie_prostokatow_lewy(double a, double b, int n) {
    double h = (a + b) / n;
    double pole = 0.0;
    double xi = a;

    for (int i = 0; i < n; i++) {
        pole = pole + h * fun_e(xi);
        xi = xi + h;
    }

    return fun() * pole;
}

double calkowanie_prostokatow_prawy(double a, double b, int n) {
    double h = (a + b) / n;
    double pole = 0.0;
    double xi = a;

    for (int i = 0; i < n; i++) {
        xi = xi + h;
        pole = pole + h * fun_e(xi);
    }

    return fun() * pole;
}

double calkowanie_prostokatow_srodkowy(double a, double b, int n) {
    double h = (a + b) / n;
    double pole = 0.0;
    double xi = a;
    double h2 = h / 2.0; // w celu zmiejszenia liczby obliczeń
    for (int i = 0; i < n; i++) {
        xi = xi + h2;
        pole = pole + h * fun_e(xi);
        xi = xi + h2;
    }

    return fun() * pole;
}

double calkowanie_trapezow(double a, double b, int n) {
    double h = (a + b) / n;
    double pole = 0.0;
    double xi = a;

    for (int i = 0; i < n; i++) {
        pole = pole + h * ((fun_e(xi) + fun_e(xi + h)) / 2.0);
        xi = xi + h;
    }

    return fun() * pole;
}

double calkowanie_parabol(double a, double b, int n) {
    double h = (a + b) / n;
    double pole = 0;
    double xi = a;

    for (int i = 0; i < n; i++) {
        pole = pole + h * ((fun_e(xi) + 4.0 * fun_e(xi + h / 2.0) + fun_e(xi + h)) / 6.0);
        xi = xi + h;
    }

    return fun() * pole;
}

void wypisz(int n);

void blad() {
    double iter = 26;
    double a = 0;
    double b = 3;

    double h = 1;
    double n;
    fstream blad;
    blad.open("blad_prostokaty.txt", ios::out);


    for (int i = 0; i < iter; i++) {
        cout << h << endl;
        n = (a + b) / h;

        blad << log10(h) << " ";
        blad << log10(fabs((calkowanie_prostokatow_lewy(a, b, n) - erf(b)) / erf(b))) << " ";
        blad << log10(fabs((calkowanie_prostokatow_prawy(a, b, n) - erf(b)) / erf(b))) << " ";
        blad << log10(fabs((calkowanie_prostokatow_srodkowy(a, b, n) - erf(b)) / erf(b))) << " ";



        blad << log10(fabs((calkowanie_trapezow(a, b, n) - erf(b)) / erf(b))) << " ";
        blad << log10(fabs((calkowanie_parabol(a, b, n) - erf(b)) / erf(b))) << " ";
        blad << endl;
                
        h = h / 2;

    }
    blad.close();
}

int main()
{
    int n = 100000; //dokładność
    
   // wypisz(n);
    blad();
    //cout << "Hello World!\n";
    //cout << erf(1) << endl;
   // cout << erf(2) << endl;
   // cout << erf(3) << endl;
}

void wypisz(int n) {

    cout << scientific;
    cout.precision(10);

    cout << "Ponieważ wyrazenie jest nieujemne dla x=[0;+inf], świadomie pominieto obliczanie wartosci bezwzglednych " << endl;

    cout << "Ilosc przedzialow: " << n << endl;
    cout << "Calka kwadratura prostokatow, z wezlem interpolacji z lewej strony przedzialu: " << endl;
    cout << "Dla a = " << 0 << ", b = " << 1 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_lewy(0, 1, n) << endl;
    cout << "Wartosc scisla:           " << erf(1) << endl;
    cout << "Dla a = " << 0 << ", b = " << 2 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_lewy(0, 2, n) << endl;
    cout << "Wartosc scisla:           " << erf(2) << endl;
    cout << "Dla a = " << 0 << ", b = " << 3 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_lewy(0, 3, n) << endl;
    cout << "Wartosc scisla:           " << erf(3) << endl;
    cout << endl;

    cout << "Calka kwadratura prostokatow, z wezlem interpolacji z prawej strony przedzialu: " << endl;
    cout << "Dla a = " << 0 << ", b = " << 1 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_prawy(0, 1, n) << endl;
    cout << "Wartosc scisla:           " << erf(1) << endl;
    cout << "Dla a = " << 0 << ", b = " << 2 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_prawy(0, 2, n) << endl;
    cout << "Wartosc scisla:           " << erf(2) << endl;
    cout << "Dla a = " << 0 << ", b = " << 3 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_prawy(0, 3, n) << endl;
    cout << "Wartosc scisla:           " << erf(3) << endl;
    cout << endl;

    cout << "Calka kwadratura prostokatow, z wezlem interpolacji srodku przedzialu: " << endl;
    cout << "Dla a = " << 0 << ", b = " << 1 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 1, n) << endl;
    cout << "Wartosc scisla:           " << erf(1) << endl;
    cout << "Dla a = " << 0 << ", b = " << 2 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 2, n) << endl;
    cout << "Wartosc scisla:           " << erf(2) << endl;
    cout << "Dla a = " << 0 << ", b = " << 3 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 3, n) << endl;
    cout << "Wartosc scisla:           " << erf(3) << endl;
    cout << endl;

    cout << "Calka kwadratura trapezow: " << endl;
    cout << "Dla a = " << 0 << ", b = " << 1 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 1, n) << endl;
    cout << "Wartosc scisla:           " << erf(1) << endl;
    cout << "Dla a = " << 0 << ", b = " << 2 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 2, n) << endl;
    cout << "Wartosc scisla:           " << erf(2) << endl;
    cout << "Dla a = " << 0 << ", b = " << 3 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_prostokatow_srodkowy(0, 3, n) << endl;
    cout << "Wartosc scisla:           " << erf(3) << endl;
    cout << endl;

    cout << "Calka kwadratura parabol: " << endl;
    cout << "Dla a = " << 0 << ", b = " << 1 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_parabol(0, 1, n) << endl;
    cout << "Wartosc scisla:           " << erf(1) << endl;
    cout << "Dla a = " << 0 << ", b = " << 2 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_parabol(0, 2, n) << endl;
    cout << "Wartosc scisla:           " << erf(2) << endl;
    cout << "Dla a = " << 0 << ", b = " << 3 << ": " << endl;
    cout << "Wartosc calego wyrazenia: " << calkowanie_parabol(0, 3, n) << endl;
    cout << "Wartosc scisla:           " << erf(3) << endl;
    cout << endl;

}