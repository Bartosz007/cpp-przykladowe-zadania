#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

double rozwiazanie_analityczne(double t) {
    return 1.0 - exp(-10.0 * (t + atan(t)));
}

double bezposrednia_eulera(double y, double krok, double i)
{
    return -(10.0 * i * i + 20.0) / (i * i + 1.0) * (y - 1.0) * krok + y;
}

double posrednia_eulera(double y, double dt, double i)
{
    double deltat = (i + dt);
    double x = (10.0 * deltat * deltat + 20.0) / (deltat * deltat + 1.0);
    return (y + dt * x) / (1 + dt * x);
}

double trapezow(double y, double dt, double i)
{
    double  x, x2;
    double deltat = (i + dt);

    x = (10.0 * i * i + 20.0) / (i * i + 1.0);
    x2 = (10.0 * deltat * deltat + 20.0) / (deltat * deltat + 1.0);

    return ((-dt / 2.0) * (x * (y - 1.0) - x2) + y) / (1.0 + (dt / 2.0) * x2);
}

double blad_bezposrednia_eulera(double dt, int n)
{
    double blad = 0.0, t = dt;
    double y = 0.0;

    for (int i = 0; i < n; i++)
    {
        y = bezposrednia_eulera(y, dt, t); 
        if(fabs(rozwiazanie_analityczne(t) - y) > blad)
            blad = fabs(rozwiazanie_analityczne(t) - y);
        
        t = t + dt;
    }
    return blad;
}

double blad_posrednia_eulera(double dt, int n)
{
    double blad = 0.0, t = dt;
    double y = 0.0;

    for (int i = 0; i < n; i++)
    {
        y = posrednia_eulera(y, dt, t);
        if (fabs(rozwiazanie_analityczne(t) - y) > blad)
            blad = fabs(rozwiazanie_analityczne(t) - y);

        t = t + dt;
    }
    return blad;
}

double blad_trapezow(double dt, int n)
{
    double blad = 0.0, t = dt;
    double y = 0.0;

    for (int i = 0; i < n; i++)
    {
        y = trapezow(y, dt, t);
        if (fabs(rozwiazanie_analityczne(t) - y) > blad)
            blad = fabs(rozwiazanie_analityczne(t) - y);

        t = t + dt;
    }
    return blad;
}



int main()
{
    fstream wyniki_stabilne, wyniki_niestabilne;   

    double bme , pme, pmt;
    double krok = 0.01;

    wyniki_stabilne.open("wyniki_stabilne.txt", ios::out);
    wyniki_stabilne << scientific;
    wyniki_stabilne.precision(15);    
    for (double t = 0; t < 3; t += 0.01)
    {
        bme = 0.0, pme = 0.0, pmt = 0.0;
        for (double i = 0.0; i < t; i = i + krok)
        {
            bme = bezposrednia_eulera(bme, krok, i);
            pme = posrednia_eulera(pme, krok, i);
            pmt = trapezow(pmt, krok, i);
        }
        //plik wyniki_stabilne: t analityczny bezposr_eulera posr_eulera posr_trapezow
        wyniki_stabilne << t << " " << rozwiazanie_analityczne(t) << " " << bme << " " << pme << " " << pmt << endl;
    }
    wyniki_stabilne.close();

    wyniki_niestabilne.open("wyniki_niestabilne.txt", ios::out);
    wyniki_niestabilne << scientific;
    wyniki_niestabilne.precision(15);
    krok = 0.18;
    for (double t = 0; t < 10; t += 0.05)
    {   
        bme = 0.0;
        for (double i = 0.0; i < t; i = i + krok)
        {
            bme = bezposrednia_eulera(bme, krok, i);
        }
        //plik: t analityczny bezposr_eulera_nie_stabilny 
        wyniki_niestabilne << t << " " << rozwiazanie_analityczne(t)<<" "<< bme <<endl;
    }
    wyniki_niestabilne.close();
    

    fstream bledy;
    int n = 100;
    bledy.open("bledy.txt",ios::out);
    bledy << scientific;
    bledy.precision(15);
    for (double dt = 0.01; dt > 1e-16; dt = dt / 1.1)
    {
        bledy << log10(dt) << " " << log10(blad_bezposrednia_eulera(dt, n)) << " " << log10(blad_posrednia_eulera(dt, n)) << " " << log10(blad_trapezow(dt, n)) << endl;
    }
    bledy.close();

    
    cout << "Wykonano obliczenia..." << endl;    
}
