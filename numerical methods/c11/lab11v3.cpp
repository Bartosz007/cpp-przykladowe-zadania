#include "calerf.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

#define ITER 100   // stałe potrzebne do metody Jacobiego
#define TOLX 1e-12 //estymator błędu
#define TOLF 1e-12 //reziduum

using namespace std;
//wartości wynikajace z treści zadania
double lambda_posrednia = 1.0;
double lambda_bezposrednia = 0.4;

double tmin = 0;
double tmax = 1.0;
double b = 0.1;
double D = 1.0;
double a = 8; // z treści zadania a >=6

/*		funkcja zwracająca analityczną wartość równania		*/
double rozwiazanie_analityczne(double x, double t)
{
	return 0.5 * exp(D * t / (b * b) - x / b) * erfc((2 * D * t / b - x) / (2 * sqrt(D * t)));
}


/*		
		funkcje potrzebne do obliczania układów równań liniowych 
*/


/*		funckja wykonjąca algorytm Thomasa- wykorzystana z laboratorium nr 9	*/
void algorytm_Thomasa(double** M, double* b, double* x, int n)
{
	double* l = new double[n];
	double* d = new double[n];
	double* u = new double[n];
	double* b_cp = new double[n];

	for (int i = 0; i < n; i++) {
		l[i] = M[0][i];
		d[i] = M[1][i];
		u[i] = M[2][i];

		b_cp[i] = b[i];
	}


	for (int i = 1; i < n; i++) {
		d[i] = d[i] - l[i - 1] * (u[i - 1] / d[i - 1]);
	}

	for (int i = 1; i < n; i++) {
		b_cp[i] = b_cp[i] - l[i - 1] * b_cp[i - 1] / d[i - 1];
	}

	x[n - 1] = b_cp[n - 1] / d[n - 1];

	for (int i = n - 2; i >= 0; i--) {
		x[i] = (b_cp[i] - u[i] * x[i + 1]) / d[i];
	}

}
double max(double* tab, int n) {
	double max = tab[0];
	for (int i = 1; i < n; i++) {
		if (max < tab[i])
			max = tab[i];
	}

	return max;
}
/*		funckja wykonjąca metodę iteracyjną Jacobiego- wykorzystana z laboratorium nr 7	*/
void metoda_Jakobiego(double** A, double* wb, double* wx, int N) {

	int p = 0;
	double maxE = 1.0, maxR = 1.0, s;
	double* estymator = new double[N];
	double* reziduum = new double[N];
	double* xn = new double[N];

	for (int i = 0; i < N; i++) {
		estymator[i] = 0;
		reziduum[i] = 0;
	}


	while (p < ITER && maxE >TOLX && maxR > TOLF)//pętla głowna
	{
		for (int i = 0; i < N; i++) {//obliczanie x
			s = 0.0;

			for (int j = 0; j < N; j++) {
				if (i != j) {
					s = s + wx[j] * A[i][j];
				}
			}

			//przy założeniu, że D to macierz diagonalna wzór można przekształcić na następujący (b-(L+U)*x[n-1])/D
			xn[i] = (wb[i] - s) / A[i][i];
		}


		for (int i = 0; i < N; i++) {//obliczanie reziduum
			reziduum[i] = 0;
			estymator[i] = fabs(xn[i] - wx[i]);

			for (int j = 0; j < N; j++) {
				reziduum[i] = reziduum[i] + A[i][j] * wx[j];
			}
			reziduum[i] = fabs(reziduum[i] - wb[i]);


			wx[i] = xn[i];
		}

		maxE = max(estymator, N);
		maxR = max(reziduum, N);
		p++;
	}

}

void zapisz_do_pliku(double** siatka, int m, int n, string nazwa) {
	fstream plik;
	plik.open(nazwa, ios::out);
	plik.precision(8);
	plik << scientific;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			plik << siatka[i][j]<<" ";
		}
		plik << endl;
	}


	plik.close();
}


/*
		funkcje wykonujące dyskretyzacje
*/


/*		funkcja wykonująca klasyczną metodę bezpośrednią	*/
void metoda_KlasycznaMetodaBezposrednia(double** siatka, int m, int n, double h) {
	double max;
	double roznica;
	//zmienne startowe
	double dt = (lambda_bezposrednia * h * h) / D;		//lambda = 0.4
	double x = -a;
	//uzupełnianie siatki zerami
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			siatka[i][j] = 0.0;

	//uzupełnienie siatki warunkami początkowymi
	for (int i = 0; i < n; i++)
	{
		if (x < 0) {
			siatka[0][i] = 0.0;
		}
		else {
			siatka[0][i] = exp(-x / b);
		}
		x += h;
	}

	//uzupełnienie siatki warunkami brzegowymi
	for (int j = 0; j < m; j++)
	{
		siatka[j][0] = 0.0;
		siatka[j][n - 1] = 0.0;
	}

	//tablica pomocnicza
	double* pom = new double[n];
	for (int i = 0; i < n; i++) {
		pom[i] = 0.0;
	}

	//pętla obliczająca oraz wstawiająca do tablicy siatka wartości dyskretyzacji
	for (int i = 0; i < m; i++)
	{

		for (int j = 1; j < n - 1; j++) //obliczanie wersa po wersie
		{
			pom[j] = lambda_bezposrednia * siatka[i][j - 1] + (1 - 2 * lambda_bezposrednia) * siatka[i][j] + lambda_bezposrednia * siatka[i][j + 1];
		}


		if (i != m - 1) { //kopiowanie z taliby pomocniczej do siatki, warunek istnieje po to, aby nie wyszło nic po za zasięg
			for (int j = 1; j < n - 1; j++)
			{
				siatka[i + 1][j] = pom[j];
			}
		}		

	}

}
/*		funkcja wykonująca klasyczną metodę Cranka-Nicolson z algorytmem Thomasa	*/
void metoda_CrankNicolson_Thomas(double** siatka, int m, int n, double h) {
	//wartości początkowe - tutaj wkorzystujemy już lambdę = 1
	double dt = lambda_posrednia * h * h / D;	
	double max;
	double roznica;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			siatka[i][j] = 0.0;

	//tworzenie wektorów i macierzy do obliczania układu równań liniowych
	double* wb = new double[n];
	double* wx = new double[n];

	double** A = new double* [3]; // macierz ma rozmiar 3 na N
	for (int i = 0; i < 3; i++) {
		A[i] = new double[n];
	}

	//uzupełnianie macierzy wartościami
	A[0][0] = 0.0;
	A[1][0] = 1.0;
	A[2][0] = 1.0;
	for (int i = 1; i < n - 1; i++)
	{
		A[0][i] = lambda_posrednia / 2.0;	//L
		A[1][i] = -(1.0 + lambda_posrednia);	//D
		A[2][i] = lambda_posrednia / 2.0;	//U
	}

	A[0][n - 1] = 1.0;
	A[1][n - 1] = 1.0;
	A[2][n - 1] = 0.0;
	
	double x = -a;

	//warunki początkowe
	for (int i = 0; i < n; i++)
	{
		if (x < 0) {
			siatka[0][i] = 0.0;
		}
		else {
			siatka[0][i] = exp(-x / b);
		}
		x = x + h;
	}
	//warunki brzegowe
	for (int i = 0; i < m; i++)
	{
		siatka[i][0] = 0.0;
		siatka[i][n - 1] = 0.0;
	}

	//pętla obliczająca oraz wstawiająca do tablicy siatka wartości dyskretyzacji
	for (int i = 0; i < m; i++)
	{
		// stosujemy się do macierzy z wykładu
		wb[0] = 0.0;
		for (int j = 1; j < n - 1; j++)
		{
			wb[j] = -((lambda_posrednia * siatka[i][j - 1]) / 2.0
				+ (1.0 - lambda_posrednia) * siatka[i][j]
				+ (lambda_posrednia * siatka[i][j + 1]) / 2.0);
		}

		wb[n - 1] = 0.0;
		//następnie obliczamy układ równań liniowych
		algorytm_Thomasa(A, wb, wx, n); 

		if (i != m - 1) { //przepisujemy wartości z wektora do siatki
			for (int j = 1; j < n - 1; j++)
			{
				siatka[i + 1][j] = wx[j];
			}
		}
	}
	
}
/*		funkcja wykonująca klasyczną metodę Cranka-Nicolson z iteracyjną metodą Jacobiego	*/
void metoda_CrankNicolson_Jacobi(double** siatka, int m, int n, double h) {
	// wykorzystujemy lambda = 1
	double dt = lambda_posrednia * h * h / D;

	double max;
	double roznica;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			siatka[i][j] = 0.0;


	double* wb = new double[n];
	double* wx = new double[n];
	for (int j = 0; j < n; j++) {
		wb[j] = 0.0;
		wx[j] = 0.0;
	}
	//różnica względem Thomsona jest taka, że ta macierz ma rozmiar N na N
	double** A = new double* [n];
	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
		for (int j = 0; j < n; j++) {
			A[i][j] = 0.0;
		}
	}
	//uzupełnianie macierzy wartościami początkowymi
	A[0][0] = 1.0;
	A[0][1] = 1.0;
	for (int i = 1; i < n - 1; i++)
	{
		A[i][i - 1] = lambda_posrednia / 2.0;	//L
		A[i][i] = -(1.0 + lambda_posrednia);	//D
		A[i][i + 1] = lambda_posrednia / 2.0;	//U
	}
	A[n - 1][n - 1] = 1.0;
	A[n - 1][n - 2] = 1.0;


	double x = -a;

	//warunki początkowe
	for (int i = 0; i < n; i++)
	{
		if (x < 0) {
			siatka[0][i] = 0.0;
		}
		else {
			siatka[0][i] = exp(-x / b);
		}
		x = x + h;
	}
	//warunki brzegowe
	for (int i = 0; i < m; i++)
	{
		siatka[i][0] = 0.0;
		siatka[i][n - 1] = 0.0;
	}



	for (int i = 0; i < m; i++)
	{	

		wb[0] = 0.0;
		for (int j = 1; j < n - 1; j++)
		{
			wb[j] = -((lambda_posrednia * siatka[i][j - 1]) / 2.0
				+ (1.0 - lambda_posrednia) * siatka[i][j]
				+ (lambda_posrednia * siatka[i][j + 1]) / 2.0);
		}

		wb[n - 1] = 0.0;
		//tym razem stosujemy metodę iteracyjną Jacobiego
		metoda_Jakobiego(A, wb, wx, n);
		if (i != m - 1) {
			for (int j = 1; j < n - 1; j++)
			{
				siatka[i + 1][j] = wx[j];
			}
		}
	}
}
/*		funkcja obliczająca wartości analityczne		*/
void metoda_analityczna(double** siatka, int m, int n, double h, double dt){
	//definujemy startowe t i startowe x
	double t = tmin;
	double x;

	for (int i = 0; i < m; i++)//obliczamy wiersz po wierszu kolejne wartości w siatce
	{
		x = -a;
		for (int j = 0; j < n; j++)//obliczamy wyraz po wyrazie po kolejnych wierszach
		{
			siatka[i][j] = rozwiazanie_analityczne(x, t);
			x = x + h;
		}

		t = t + dt;
	}
}


/*
		funkcje realizujące zadania 2 i 3
*/

/*      funkcja wykonująca obliczenia do zadań 2 i 3 metodą bezposrednią			*/			
void metoda_bezposrednia() {

	int n = 400; 
	double h = (a + a) / (n-1);    //w przbliżeniu h = 0.04, dla mniejszych wartości, obliczenia stawały się bardzo czasochłonne i zasobożerne
	double dt = (lambda_bezposrednia * h * h) / D;  //wyliczamy dt ze wzoru, lambda=0.4
	int m = tmax / dt + 1;

	double** kmb;	//przygotowujemy tutaj tablice na wyniki dyskretyzacji
	double** analityczna;	//przygotowujemy tutaj tablice na wyniki analityczne

	//alokjacje pamięci
	analityczna = new double* [m];
	kmb = new double* [m];
	for (int i = 0; i < m; i++)
	{
		analityczna[i] = new double[n];
		kmb[i] = new double[n];
	}

	//wywołujemy obie metody, których efektem będą uzupełnione siatki
	metoda_KlasycznaMetodaBezposrednia(kmb, m, n, h);
	metoda_analityczna(analityczna, m, n, h, dt);
	zapisz_do_pliku(analityczna,m,n,"analityczna.txt");
	zapisz_do_pliku(kmb, m, n, "kmb.txt");

	//			zadanie2
	fstream plik;

	int dm = m / 4;  //dzielimy wysokość macierzy na 4, po to aby wybrać 4 wartości t, dla których sporządzać będziemy wykresy

	double x;
	double t = tmin;

	for (int i = dm,li=0; i < m; i = i + dm, li++) {
		t = t + dt * dm;	//obliczanie kolejnego wiersza macieryz
		x = -a;
		stringstream ss("");
		ss << "zadanie2lb" << li << ".txt";
		plik.open(ss.str(), ios::out);
		plik << "t=" << t << endl;

		//wpisywanie wartości do plików, używamy modulo, aby zmiejszyć liczbę punktów(tylko metoda numeryczna) na wykresie i zwiększyć jego przejrzystość
		for (int j = 0; j < n; j++) {	
			if (j % 3 == 0) {
				plik << x << " " << analityczna[i][j] << " " << kmb[i][j] << endl;
			}
			else {
				plik << x << " " << analityczna[i][j] << endl;
			}
			x = x + h;
		}

		plik.close();
		cout << "Zapisano dane do pliku: " << ss.str() << endl;
	}
	//zadanie 3
	double max;
	double roznica;
	t = tmin;
	plik.open("zadanie3lb.txt", ios::out);
	for (int i = 0; i < m; i++) {
		roznica = 0.0;
		max = 0.0;
		for (int j = 0; j < n; j++) {  //obliczanie największego błędu w każdym wierszu
			roznica = fabs(analityczna[i][j] - kmb[i][j]);
			if (roznica > max) {
				max = roznica;
			}
		}
		plik << t << " " << max << endl;
		t = t + dt;
	}
	plik.close();


	for (int i = 0; i < m; i++) //czyszczenie pamięci
	{
		delete[] analityczna[i];
		delete[] kmb[i];
	}
	delete[] analityczna;
	delete[] kmb;
	cout << "Obliczono metode bezposrednia" << endl;
}

void metody_posrednie() {

	int n = 400;
	double h = (a + a) / (n - 1);
	double dt = (lambda_posrednia * h * h) / D;   //wyliczamy dt ze wzoru, lambda=1
	int m = tmax / dt + 1;

	//przygotowujemy tablice
	double** analityczna;  //na wartości analityczne
	double** cnt;		// na wartości obliczne metodą posrednią Cranka-Nicolson z algorytmem Thomasa
	double** cnj;		// na wartości obliczne metodą posrednią Cranka-Nicolson z metodą iteracyjną Jacobiego
	
	//alokacje pamięci
	cnt = new double* [m];
	cnj = new double* [m];
	analityczna = new double* [m];
	for (int i = 0; i < m; i++)
	{
		analityczna[i] = new double[n];
		cnt[i] = new double[n];
		cnj[i] = new double[n];
	}

	//obliczanie wartości numerycznych i analitycznych
	metoda_CrankNicolson_Thomas(cnt, m, n, h);
	metoda_CrankNicolson_Jacobi(cnj, m, n, h);
	metoda_analityczna(analityczna, m, n, h, dt);

	zapisz_do_pliku(cnt, m, n, "cnt.txt");
	zapisz_do_pliku(cnj, m, n, "cnj.txt");
	/*


							ZADANIE2


	*/


	double t = tmin;
	double dm = m / 4;  //również wybieramy 4 t, dla których kreślone będą wykresy
	double x;

	fstream plik;
	int li = 0;
	for (int i = dm; i < m; i = i + dm, li++) {
		t = t + dt * dm;
		x = -a;
		stringstream ss("");
		ss << "zadanie2lp" << li << ".txt";
		plik.open(ss.str(), ios::out);
		plik << "t=" << t << endl;
		// wpisywanie tych wartości do pliku, również wpisujemy tylko co 3 wyrażenie numeryczne, aby uzyskać lepszą przejżystosć wykresu
		for (int j = 0; j < n; j++) { 
			if (j % 3 == 0) {
				plik << x << " " << analityczna[i][j] << " " << cnt[i][j] << " " << cnj[i][j] << endl;
			}
			else {
				plik << x << " " << analityczna[i][j] << " " << endl;
			}
			x = x + h;
		}

		plik.close();
		cout << "Zapisano dane do pliku: " << ss.str() << endl;
	}


	/*


							ZADANIE3


	*/
	
	t = tmin;
	double max,max2,roznica;
	plik.open("zadanie3lp.txt", ios::out);
	for (int i = 0; i < m; i++) {
		roznica = 0.0;
		max = 0.0;
		max2 = 0.0;
		for (int j = 0; j < n; j++) {  //obliczanie największego błędu w każdym wierszu dla obu tablic
			roznica = fabs(analityczna[i][j] - cnt[i][j]);
			if (roznica > max) {
				max = roznica;
			}
			roznica = fabs(analityczna[i][j] - cnj[i][j]);
			if (roznica > max2) {
				max2 = roznica;
			}
		}
		if (i % 4 == 0) {
			plik << t << " " << max <<" " << max2 <<  endl;
		}
		else {
			plik << t << " " << max << endl;
		}
		t = t + dt;
	}
	plik.close();
	cout << "Obliczono metody posrednie" << endl;


	for (int i = 0; i < m; i++) //czyszczenie pamięci
	{
		delete[] analityczna[i];
		delete[] cnt[i];
		delete[] cnj[i];
	}
	delete[] analityczna;
	delete[] cnt;
	delete[] cnj;
}


/*
		funkcje realizujące zadania 2 i 3
*/

/*		funkcja wykonująca obliczenia do zadania 1 metodą bezpośrednią				*/	
void bledy_bezposrednie() {
	//zmienne potrzebne do prawidłowego działania
	double dt, max, blad;
	int n, m;
	double** analityczna, ** kmb; //tablice na siatki wypełnione wartościami analitycznimi i numerycznymi
	fstream zad1;
	zad1.open("zadanie1lb.txt",ios::out);
	double h = 0.1;

	while(h > 0.005){	//pętla, która iteruje dopóki h>0.005
	
		//obliczanie dt, gdzie lambda = 0.4, oraz rozmiaru siatki
		dt = lambda_bezposrednia * h * h / D;	
		m = tmax / dt;
		n = (a + a) / h;

		//ponieważ h jest zmienna, to rozmiar siatek też się zmienia, więc trzeba je alokować i zwalniać w każdej iteracji
		analityczna = new double* [m];
		for (int i = 0; i < m; i++)
			analityczna[i] = new double[n];

		kmb = new double* [m];
		for (int i = 0; i < m; i++)
			kmb[i] = new double[n];

		//zapełnianie siatek wynikami analitycznymi i numerycznymi
		metoda_analityczna(analityczna, m, n, h, dt);		
		metoda_KlasycznaMetodaBezposrednia(kmb, m, n, h);
		max = 0.0;
		blad = 0;
		for (int i = 0; i < n; i++)//pętla szukająca największego błędu dla tmax - czyli ostatniego wersa siatki
		{
			blad = fabs(kmb[m - 1][i] - analityczna[m - 1][i]);
			if (blad > max) { 
				max = blad;
			}
		}

		//wypisanie w konsoli i wpisywanie błędu do pliku
		cout << log10(h) << " " << log10(max) << endl;
		zad1 << log10(h) << " " << log10(max) << endl;
		
		//zwalnianie pamięci
		for (int i = 0; i < m; i++)
			delete[] analityczna[i];
		delete[] analityczna;


		for (int i = 0; i < m; i++)
			delete[] kmb[i];
		delete[] kmb;

		h = h / 2;
	}
	zad1.close();

	cout << "Wykonano pomiary bledow klasycznej metody bezposredniej" << endl;

}

/*		funkcja wykonująca obliczenia do zadania 1 metodami pośrednimi				*/
void bledy_posrednie() {
	//zmienne potrzebne do prawidłowego działania
	double dt, max;
	int n, m;
	double blad = 0;
	double** analityczna, ** cn;	//tablice na siatki wypełnione wartościami analitycznimi i numerycznymi
	fstream zad1;
	zad1.open("zadanie1lp1.txt", ios::out);

	//obliczanie dt, gdzie lambda = 0.4, oraz rozmiaru siatki
	double h = 0.1;
	while(h > 0.006) {//pętla, która iteruje dopóki h>0.006 - jest mniej wydajna, niż bezpośrednia

		dt = lambda_posrednia * h * h / D; //lambda = 1
		m = tmax / dt;
		n = (a + a) / h;

		//ponieważ h jest zmienna, to rozmiar siatek też się zmienia, więc trzeba je alokować i zwalniać w każdej iteracji
		analityczna = new double* [m];
		for (int i = 0; i < m; i++)
			analityczna[i] = new double[n];

		cn = new double* [m];
		for (int i = 0; i < m; i++) {
			cn[i] = new double[n];
		}


		//zapełnianie siatek wynikami analitycznymi i numerycznymi
		//tutaj jest tylko metoda Cranka-Nicolson z algorytmem Thomasa, żeny nie bylo problemów z brakiem pamięci
		metoda_analityczna(analityczna, m, n, h, dt);
		metoda_CrankNicolson_Thomas(cn, m, n, h);

		max = 0.0;
		blad = 0.0;
		for (int i = 0; i < n; i++)//pętla szukająca największego błędu dla tmax - czyli ostatniego wersa siatki
		{
			blad = fabs(cn[m - 1][i] - analityczna[m - 1][i]);
			if (blad > max) {
				max = blad;
			}
		}

		//wypisanie w konsoli i wpisywanie błędu do pliku
		cout << log10(h) << " " << log10(max) << " " <<  endl;
		zad1 << log10(h) << " " << log10(max) << endl;


		//zwalnianie pamięci
		for (int i = 0; i < m; i++)
			delete[] analityczna[i];
		delete[] analityczna;


		for (int i = 0; i < m; i++)
			delete[] cn[i];
		delete[] cn;

		h = h / 2;

	}
	zad1.close();


	zad1.open("zadanie1lp2.txt", ios::out);
	h = 0.1;
	while (h > 0.008){
		//ponieważ h jest zmienna, to rozmiar siatek też się zmienia, więc trzeba je alokować i zwalniać w każdej iteracji
		dt = lambda_posrednia * h * h / D;  //lambda = 1
		m = tmax / dt;
		n = (a + a) / h;

		//ponieważ h jest zmienna, to rozmiar siatek też się zmienia, więc trzeba je alokować i zwalniać w każdej iteracji
		analityczna = new double* [m];
		for (int i = 0; i < m; i++)
			analityczna[i] = new double[n];

		cn = new double* [m];
		for (int i = 0; i < m; i++) {
			cn[i] = new double[n];
		}


		//zapełnianie siatek wynikami analitycznymi i numerycznymi
		//tutaj jest tylko metoda Cranka-Nicolson z metodą iteracyjną Jacobiego, żeny nie bylo problemów z brakiem pamięci

		metoda_analityczna(analityczna, m, n, h, dt);
		metoda_CrankNicolson_Jacobi(cn, m, n, h);
		max = 0.0;
		blad = 0.0;
		for (int i = 0; i < n; i++)//pętla szukająca największego błędu dla tmax - czyli ostatniego wersa siatki
		{
			blad = fabs(cn[m - 1][i] - analityczna[m - 1][i]);
			if (blad > max) {
				max = blad;
			}
		}

		//wypisanie w konsoli i wpisywanie błędu do pliku
		cout << log10(h) << " " << log10(max) << endl;
		zad1 << log10(h) << " " << log10(max) << endl;


		//zwalnianie pamięci
		for (int i = 0; i < m; i++)
			delete[] analityczna[i];
		delete[] analityczna;


		for (int i = 0; i < m; i++)
			delete[] cn[i];
		delete[] cn;

		h = h / 2;

	}
	zad1.close();

	cout << "Wykonano pomiary bledow metody Cranka-Nicolson z metoda iteracyjna Jacobiego" << endl;
}




int main()
{

	metoda_bezposrednia();
	metody_posrednie();
	//bledy_bezposrednie();
	//bledy_posrednie();


}
