#include <iostream>
#include <fstream>
#define N 4
#define ITER 100
#define TOLX 1e-16 //estymator błędu
#define TOLF 1e-16 //reziduum

using namespace std;

void wypiszM(double M[N][N], double k, double l);
void wypiszW(double w[N], double k);

void metoda_jakobiego(double A[N][N], double b[N], double x[N]);
void metoda_gs(double A[N][N], double b[N], double x[N]);
void metoda_sor(double A[N][N], double b[N], double x[N],double o);

template<typename T>
T max(T tab[N], int n);

fstream zapis;
int main()
{
	zapis.open("wyniki_lab7.txt", ios::out);

	double A[N][N] = { {100.0,-1.0,2.0,-3.0},{1.0,200.0,-4.0,5.0},{-2.0,4.0,300.0,-6.0},{3.0,-5.0,6.0,400.0} };
	double b[N] = { 116.0,-226.0,912.0,-1174.0 };
	double x[N] = { 2.0, 2.0, 2.0, 2.0 };
	
	cout << scientific;
	cout.precision(16);
	zapis << scientific;
	zapis.precision(16);

	metoda_jakobiego(A, b, x);
	x[0] = 2, x[1] = 2, x[2] = 2, x[3] = 2;
	cout << endl;
	zapis << endl;

	metoda_gs(A, b, x);
	x[0] = 2, x[1] = 2, x[2] = 2, x[3] = 2;
	cout << endl;
	zapis << endl;

	double omega = 1.0 / 2.0;
	metoda_sor(A, b, x, omega);

	zapis.close();
}

void wypiszM(double M[N][N], double k, double l) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < l; j++) {
			cout << M[i][j] << " ";
			zapis << M[i][j] << " ";
		}
		cout << endl;
		zapis << endl;
	}
}

void wypiszW(double w[N], double k) {
	for (int i = 0; i < k; i++) {
		cout <<"x"<<i+1<<": " <<w[i] << " ;";
		zapis << "x" << i + 1 << ": " << w[i] << " ;";
	}
}

template<typename T>
T max(T tab[N], int n) {
	T max = tab[0];
	for (int i = 1; i < n; i++) {
		if (max < tab[i])
			max = tab[i];
	}

	return max;
}

void metoda_jakobiego(double A[N][N], double b[N], double x[N]) {
	cout << "Metoda Jacobiego: " << endl;
	zapis << "Metoda Jacobiego: " << endl;
	int p = 0;
	double estymator[N], reziduum[N] = { 0 }, maxE = 1, maxR = 1;
	double xn[N], s;
	while (p < ITER && maxE >TOLX&& maxR > TOLF)//pętla głowna
	{
		for (int i = 0; i < N; i++) {//obliczanie x
			s = 0.0;

			for (int j = 0; j < N; j++) {
				if (i != j) {
					s = s + x[j] * A[i][j];
				}
			}

			//przy założeniu, że D to macierz diagonalna wzór można przekształcić na następujący (b-(L+U)*x[n-1])/D
			xn[i] = (b[i] - s) / A[i][i];
		}


		for (int i = 0; i < N; i++) {//obliczanie reziduum
			reziduum[i] = 0;
			estymator[i] = fabs(xn[i] - x[i]);

			for (int j = 0; j < N; j++) {
				reziduum[i] = reziduum[i] + A[i][j] * x[j];
			}
			reziduum[i] = fabs(reziduum[i] - b[i]);


			x[i] = xn[i];
		}

		maxE = max(estymator, N);
		maxR = max(reziduum, N);



		cout << "Iteracja " << p <<":"<< endl;
		zapis << "Iteracja " << p << ":" << endl;
		wypiszW(x, N);
		cout << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;
		zapis << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;

		p++;
	}

}

void metoda_gs(double A[N][N], double b[N], double x[N]) {
	cout << "Metoda Gaussa-Seidela" << endl;
	zapis << "Metoda Gaussa-Seidela" << endl;
	int p = 0;
	double estymator[N], reziduum[N] = { 0 }, maxE = 1, maxR = 1;
	double xn, suma ;
	while (p < ITER && maxE >TOLX&& maxR > TOLF)
	{
		for (int i = 0; i < N; i++) {
			suma = 0.0;
			for (int j = 0; j < N; j++) {
				if (i != j) {
					suma = suma + x[j] * A[i][j];
				}
			}

			xn = x[i];
			x[i] = (b[i] - suma) / A[i][i]; //wzór ten sam co do jakobiego, jedynie wartości tablicy x są zmieniane w każej iteracji tej pętli

			estymator[i] = fabs(xn - x[i]);
		}


		for (int i = 0; i < N; i++) {
			reziduum[i] = 0;
			for (int j = 0; j < N; j++) {
				reziduum[i] = reziduum[i] + A[i][j] * x[j];
			}
			reziduum[i] = fabs(reziduum[i] - b[i]);
		}

		maxE = max(estymator, N);
		maxR = max(reziduum, N);


		cout << "Iteracja " << p << ":" << endl;
		zapis << "Iteracja " << p << ":" << endl;
		wypiszW(x, N);
		cout << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;
		zapis << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;


		p++;
	}
}

void metoda_sor(double A[N][N], double b[N], double x[N], double o) {
	cout << "Metoda SOR" << endl;
	zapis << "Metoda SOR" << endl;
	int p = 0;
	double estymator[N], reziduum[N] = { 0 }, maxE = 1, maxR = 1;
	double xn[N], suma = 0;
	double xs[N];
	while (p < ITER && maxE >TOLX&& maxR > TOLF)
	{
		for (int i = 0; i < N; i++) {
			suma = 0.0;
			for (int j = 0; j < N; j++) {
				if (i != j) {
					suma = suma + x[j] * A[i][j];
				}
			}

			xn[i] = x[i];
			x[i] = (1.0 - o) * x[i] + (o * (b[i] - suma) / A[i][i]);
			
			estymator[i] = fabs(xn[i] - x[i]);
		}


		for (int i = 0; i < N; i++) {
			reziduum[i] = 0;
			for (int j = 0; j < N; j++) {
				reziduum[i] = reziduum[i] + A[i][j] * x[j];
			}
			reziduum[i] = fabs(reziduum[i] - b[i]);
		}

		maxE = max(estymator, N);
		maxR = max(reziduum, N);
			   
		cout << "Iteracja " << p << ":" << endl;
		zapis << "Iteracja " << p << ":" << endl;
		wypiszW(x, N);
		cout << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;
		zapis << "reziduum: " << maxR << " ;epsilon: " << maxE << endl;


		p++;
	}
}