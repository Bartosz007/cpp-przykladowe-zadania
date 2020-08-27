#include <string>
#include "funkcje.hpp"

using namespace std;

string pl(string tekst) {
	int dlugosc = tekst.length();
	int m = 18;
	int kod[] = { -65,-13,-77,-26,-22,-100,-71,-97,-15,-81,-45,-93,-58,-54,-116,-91,-113,-47 };
	char znak[] = { '\276','\242','\210','\206','\251','\230','\245','\253','\344','\275','\340' ,'\235' ,'\217' ,'\250' ,'\227' ,'\244' ,'\215' ,'\343' };

	for (int i = 0; i < tekst.length(); i++) {
		char a = tekst.at(i);

		for (int k = 0; k < m; k++) {
			if (a == char(kod[k])) {
				string s(1, znak[k]);
				tekst.replace(i, 1, s);
			}
		}
	}

	return tekst;
};

int dlugosc(string s) {
	int n = 0;
	int poz = 0;
	int ost = s.rfind(",") + 1;
	while (poz != ost) {
		poz = s.find(",", poz) + 1;
		n++;
	}

	return n + 1;
}
