#include <iostream>
#include <cmath>
#include <fstream>
#define ITER 500
#define TOLX 1e-15
#define TOLF 1e-15
using namespace std;

double f1(double x);
double f2(double x);
double df1(double x);
double df2(double x);

double f1_fi(double x);
double f2_fi(double x);
double df1_fi(double x);
double df2_fi(double x);

void picard(double (*f)(double x), double(*f_fi)(double x), double(*df_fi)(double x), double x);

void bisekcja(double (*f)(double x), double x1, double x2);

void newton(double (*f)(double x), double(*df)(double x), double x);

void siecznych(double(*f)(double x), double x1, double x2);

fstream plik;
int main()
{

    plik.open("wynikic3.txt", ios::out);
    if (plik.good() != true){
        cout << "Błąd otwacia pliku" << endl;
        return 1;
    }

    //cout << scientific;
    cout.precision(20);
    plik.precision(20);
    cout << scientific;
    plik << scientific;
    cout << "Metoda Picarda: " << endl << endl;
    plik << "Metoda Picarda: " << endl << endl;
    cout << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    plik << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    picard(f1, f1_fi, df1_fi, 50);
    cout <<endl<< "tan(2.0 * x) - x - 1.0:" << endl;
    plik << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    picard(f2, f2_fi, df2_fi, 0.5);
    cout << endl;
    plik << endl;

    cout << "Metoda bisekcji: " << endl << endl;
    plik << "Metoda bisekcji: " << endl << endl;
    cout << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    plik << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    bisekcja(f1,-10,150);
    cout <<  endl<<"tan(2.0 * x) - x - 1.0:" << endl;
    plik << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    bisekcja(f2, -2, -1.9);
    cout << endl;
    plik << endl;

    cout << "Metoda Newtona: " << endl << endl;
    plik << "Metoda Newtona: " << endl << endl;
    cout << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    plik << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    newton(f1, df1, 7);
    cout << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    plik << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    newton(f2, df2, -1);
    cout << endl;
    plik << endl;
    
    cout << "Metoda siecznych: " << endl << endl;
    plik << "Metoda siecznych: " << endl << endl;
    cout << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    plik << "sin((x / 4.0)) * sin(x / 4.0) - x:" << endl;
    siecznych(f1, 4, 6);
    cout << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    plik << endl << "tan(2.0 * x) - x - 1.0:" << endl;
    siecznych(f2, 3, 4);
    cout << endl;
    plik << endl;

    plik.close();

    return 0;
}

double f1(double x) {
    return sin((x / 4.0)) * sin(x / 4.0) - x; //tutaj dodałem 2 aby było inne miesjce zerowe
}
double f2(double x) {
    return tan(2.0 * x) - x - 1.0;
}

double df1(double x) {
    return (1.0 / 4.0) * (sin(x / 2.0)) - 1;
}
double df2(double x) {
    return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double f1_fi(double x) {
    return sin((x / 4.0)) * sin(x / 4.0);//tutaj dodałem 2 aby było inne miesjce zerowe
}
double f2_fi(double x) {
    return tan(2.0 * x) - 1.0;
}

double df1_fi(double x) {
    return 1.0 / 4.0 * sin(x / 2.0);
}
double df2_fi(double x) {
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

void picard(double (*f)(double x), double(*f_fi)(double x), double(*df_fi)(double x), double x) {

    if (fabs(df_fi(x)) > 1) {
        cout << "Funckja rozbiezna " << endl;
        return;
    }

    int i = 0;
    double estymator = 1;
    double reziduum = fabs(f_fi(x));
    double xn1 = x;
    while (i < ITER && estymator >= TOLX && reziduum >= TOLF) {
        xn1 = f_fi(xn1);

        estymator = fabs(xn1 - x);
        cout <<"Iteracja: "<<i<< " x: " << x << " f(x): " << f(x) << " estymator: " << estymator;
        plik <<"Iteracja: " << i << " x: " << x << " f(x): " << f(x) << " estymator: " << estymator;

        x = xn1;
        reziduum = fabs(f(x));

        cout<< " Reziduum: " << reziduum << endl;
        plik << " Reziduum: " << reziduum << endl;
        i++;
    }

}

void bisekcja(double (*f)(double x), double x1, double x2) {
    double a = x1;
    double b = x2;
    double c = (a + b) / 2.0;
    double xc = f(c);
    double xa, xb;

    int i = 0;

    double estymator = fabs((b - a) / 2);
    double reziduum = fabs(f((a + b) / 2.0));
    if ((f(a) > 0 && f(b) > 0) || (f(a) < 0 && f(b) < 0)) {
        cout << "f(a) i f(b) sa tego samego znaku..." << endl;
        return;
    }
    while (i < ITER && estymator >= TOLX && reziduum >= TOLF) {
        c = (a + b) / 2.0;
        xa = f(a);
        xb = f(b);
        xc = f(c);

        if (xa < 0 && xc > 0) {
            b = c;
        }
        else if (xa > 0 && xc < 0) {
            b = c;
        }
        else if (xc < 0 && xb > 0)
        {
            a = c;
        }
        else if (xc > 0 && xb < 0)
        {
            a = c;
        }

        estymator = fabs((b - a) / 2.0);
        reziduum = fabs(xc);
        cout <<"Iteracja: "<<i<< " x: " << c << " f(x): " << xc << " estymator: " << estymator << " Reziduum: " << reziduum << endl;
        plik << "Iteracja: " << i << " x: " << c << " f(x): " << xc << " estymator: " << estymator << " Reziduum: " << reziduum << endl;
        i++;
    }

}

void newton(double (*f)(double x), double(*df)(double x),double x) {
    
    int i = 0;
    double estymator = fabs(x - (f(x) / df(x)));
    double reziduum = fabs(f(x - (f(x) / df(x))));
    double xn = x;

    while (i < ITER && estymator >= TOLX && reziduum >= TOLF) {
        if (df(x)==0)
            continue;

        xn = x - (f(x) / df(x));
        estymator = fabs(xn - x);    

        cout << "Iteracja: " << i << " x: " << x << " f(x): " << f(x) << " estymator: " << estymator;
        plik << "Iteracja: " << i << " x: " << x << " f(x): " << f(x) << " estymator: " << estymator;
        x = xn;
        reziduum = fabs(f(x));
        cout << " Reziduum: " << reziduum << endl;
        plik << " Reziduum: " << reziduum << endl;
        i++;
    }

}

void siecznych(double(*f)(double x), double x1, double x2) {
    int i = 0;
    double estymator = fabs(x1-x2);
    double reziduum = fabs(f(x1 - x2));
    double x3 = x1 - x2;

    while (i < ITER && estymator >= TOLX && reziduum >= TOLF) {
        if ((f(x2) - f(x1)) == 0 || (x2 - x1) == 0)
            continue;
        x3 = x2 - (f(x2) / ((f(x2) - f(x1)) / (x2 - x1)));
        estymator = fabs(x2 - x3);
        cout << "Iteracja: " << i << " x: " << x3 << " f(x): " << f(x3) << " estymator: " << estymator;
        plik << "Iteracja: " << i << " x: " << x3 << " f(x): " << f(x3) << " estymator: " << estymator;
        x1 = x2;
        x2 = x3;

        reziduum = fabs(f(x3));
        cout << " Reziduum: " << reziduum << endl;
        plik << " Reziduum: " << reziduum << endl;
        i++;
    }

}

