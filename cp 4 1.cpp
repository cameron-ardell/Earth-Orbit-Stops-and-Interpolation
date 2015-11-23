#include <iostream>
#include "nr3.h"
#include "interp_1d.h"

//need to set constant values of To, G, M, and Ro


struct Base_inter{

}


int main() {

	Doub Ro = 1.496*10^11;
	Doub G = 6.673*10^-11;
	Doub M = 1.989*10^30;
	Doub To = ((R^3)/(2*G*M))^0.5;

	//Setting PI
	Doub PI = 3.141596;

	const Doub m;
	cout << "How many values do you want?\n";
	cin >> m;

	//need eta as function of how many values needed, and goes from 0 to 180
	//it stops at 180 since when eta is PI, radius is 0
	Doub etaIncrement = m / 180.0;

	//need radius and time vectors
	VecDoub radius(m), time(m);

	//need seperate iterator for indexing values
	int index = 0;

	for(Doub i = 0.0; i <= 180.0; i +=  etaIncrement){

		//convert eta to radians
		Doub eta = i * 2 * PI /360;

		radius[index] = ;
		time[index] = ;

		index++; 

	}

	return 0;
}