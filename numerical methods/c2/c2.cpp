#include <iostream>
#include <fstream> 
#include <string>
#include <cmath>

using namespace std;

double szereg_f_exp3(double x,double f) {
	double ret = 1.0;
	int znak = -1;
	double ost = 1;
	int i = 2;
	int licznik = 0;
	while(fabs(f-ret)>1e-16 && i<1000) {
		ost = ost * x / i;
		ret = ret + znak * ost;
		znak = -znak;
		i++;
	}
	cout << "licznik: " << i << endl;
	return ret;
}

double f_exp(double x) {
	return (1.0 - exp(-x)) / x;
}

int main()
{

	string dane;
	int len = 0;
	fstream fs, bladfs, bladfs2;

	fs.open("oneminexp_ref.txt", ios_base::in);
	bladfs.open("blad.txt", ios_base::out);
	bladfs2.open("blad2.txt", ios_base::out);

	if (fs.good() != true && bladfs.good() != true && bladfs2.good() != true) {
		cout << "Dostep do pliku zostal zabroniony!" << endl;
		exit(1);
	}

	cout.precision(20);
	cout.setf(ios::scientific);
	bladfs.precision(20);
	bladfs.setf(ios::scientific);
	bladfs2.precision(20);
	bladfs2.setf(ios::scientific);

	cout << "wczytano dane..." << endl;
	while (!fs.eof()) {

		double lg10, x, f_dokladna;
		fs >> lg10;
		fs >> x;
		fs >> f_dokladna;

		// cout << lg10 << " " << x << " " << wyrexp << " " << endl;

		double f_przyblizona = f_exp(x);

		double b_f_przyblizonej = log10(fabs((f_dokladna - f_przyblizona) / f_dokladna));

		if (isinf(b_f_przyblizonej))
			b_f_przyblizonej = -18;

		bladfs << lg10 << " " << b_f_przyblizonej << endl;//wpisanie błedu do pliku

		double wyr3=1;

		 // cout << x << " " << f_dokladna;
		if (fabs(f_dokladna - f_przyblizona) < 1e-16) {
			wyr3 = log10(fabs((f_dokladna - f_przyblizona) / f_dokladna));
			//  cout << " " << f_przyblizona << endl;
		}
		else
		{
			double szereg = szereg_f_exp3(x,f_dokladna);
			wyr3 = log10(fabs((f_dokladna - szereg) / f_dokladna));
			//cout << " " << szereg << endl;
		}
		if (isinf(wyr3))
			wyr3 = -18;
		bladfs2 << lg10 << " " << wyr3 << endl;


	}

	cout << "zapisano bledy do pliku..." << endl;

	fs.close();
	bladfs.close();
	bladfs2.close();

	return 0;
}
