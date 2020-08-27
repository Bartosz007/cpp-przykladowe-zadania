#include "menu.hpp"
#include <regex>

int operator ~(string akcja) {
	smatch wynik;

	regex wzorzec("rm id[[:d:]]{5}");
	if (regex_search(akcja, wynik, wzorzec))
		return 1;

	wzorzec = ("exit$");
	if (regex_search(akcja, wynik, wzorzec))
		return 2;

	wzorzec = ("info id[[:d:]]{5}");
	if (regex_search(akcja, wynik, wzorzec))
		return 3;

	return 0;
}

int menu(string akcja, string w1, string w2, string w3) {//tekst,akcja1,akcja2,wyjscie z menu
	smatch wynik;

	regex wzorzec(w1);
	if (regex_search(akcja, wynik, wzorzec))
		return 1;

	wzorzec = (w2);
	if (regex_search(akcja, wynik, wzorzec))
		return 2;

	wzorzec = (w3);//wyjscie
	if (regex_search(akcja, wynik, wzorzec))
		return 0;

	return 3;
}

int menu(string akcja, string w1, string w2, string w3, string w4) {//tekst,akcja1,akcja2,akcja 3,wyjscie z menu
	smatch wynik;

	regex wzorzec(w1);
	if (regex_search(akcja, wynik, wzorzec))
		return 1;

	wzorzec = (w2);
	if (regex_search(akcja, wynik, wzorzec))
		return 2;

	wzorzec = (w3);
	if (regex_search(akcja, wynik, wzorzec))
		return 3;

	wzorzec = (w4);//wyjscie
	if (regex_search(akcja, wynik, wzorzec))
		return 0;

	return 4;
}
