#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int mantysaf = 0;	
	float epsilonf=1.f;	
	while (( epsilonf/2.f + 1.f) > 1.f) {
		epsilonf = epsilonf/2.f;
		mantysaf++;
	}
	cout << "FLOAT:: Mantysa: " << mantysaf << ", epsilon maszynowy: " << epsilonf << endl;

	int mantysad = 0;
	double epislond = 1.0;
	while ((epislond / 2.0 + 1.0) > 1.0) {
		epislond = epislond / 2.0;
		mantysad++;
	}
	cout << "DOUBLE:: Mantysa: " << mantysad << ", epsilon maszynowy: " << epislond << endl;

}