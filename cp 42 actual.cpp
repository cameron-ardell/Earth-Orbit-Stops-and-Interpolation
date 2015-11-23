#include <iostream>
#include "nr3.h"
#include "interp_1d.h"
#include "polcoef.h"
#include <string>

using namespace std;

//takes double and returns value based on function given in hw
Doub function(Doub cur_x){
	Doub out = (exp(-1.0*cur_x*cur_x))/(1.0 + 25.0 * cur_x * cur_x);
	return out;
};

//gets x values
VecDoub xValues(Doub size){
	
	//need constant to multiply i by to get x_value
	//since incrementing from -1 to 1
	Doub multiplier =  2.0/(size - 1.0);

	VecDoub x(size);

	//makes x values for function
	for(int i = 0.0; i < (int)size; i++){
		x[i] = i * multiplier - 1;
	}

	return x;
};

//gets y values for exact function
VecDoub yValues(VecDoub x, int size){

	VecDoub y(size);

	for(int i = 0; i < size; i++){
		y[i] = function(x[i]);
	}
	return y;
}


void evaluate(Doub n, string fileName, string coefFile){

	Doub n_interp = n * 10.0;

	//initalize vectors that hold exact x and y values
	VecDoub xx(n), yy(n);
	xx = xValues(n);
	yy = yValues(xx, n);

	//need vectors for error if you ran exact function on number
	//of interpolations, so can calculate true error
	VecDoub xxIE(n_interp), yyIE(n_interp);
	xxIE = xValues(n_interp);
	yyIE = yValues(xxIE, n_interp);

	//need to interpolate business
	//can just switch Rat_interp to Poly_interp any time
	Rat_interp data(xx, yy, (int)n);

	//to access interpolated y values for part a, d, and e
	VecDoub yValueInt(n_interp);
	for(int m = 0; m < (int) n_interp; m++){
		Doub x_cur = xxIE[m];
		yValueInt[m] = data.interp(x_cur);
	}


	ofstream file;
	file.open(fileName.c_str());

	file << "#index   xvalue   yvalue   xvalueInterp   yvalueInterp
	    relative error   exact error\n";

	//calculates error and interpolates, writes all to file
	for(int i = 0; i < (int)n_interp; i++){
		
		//corrects for going out of bounds for exact vector, will give null values
		//after out of range
		Doub xVal = 0.0;
		Doub yVal = 0.0;
		if(i < n){
			xVal = xx[i];
			yVal = yy[i];
		}

		file << i << " " << xVal << " " << yVal << " " << xxIE[i] << " ";
		Doub y = data.interp(xxIE[i]);
		Doub rel_err = data.dy;
		//gets interpolated error - actual error
		Doub absolute_err = abs(y - yyIE[i]);

		file << y << " " << rel_err << " " << absolute_err << endl;
	}

	file.close();

	string coef;
	cout << "Do you want to find coefficients? y/n\n";
	cin >> coef;

	if(coef == "y"){
		//gets coefficients both ways
		VecDoub polcoe_val(n);
    	polcoe(xx, yy, polcoe_val);

    	VecDoub polcof_val(n);
    	polcof(xx, yy, polcof_val);

    	//writes all values to a file
    	ofstream fileTwo;
    	fileTwo.open(coefFile.c_str());

    	fileTwo << "#index   polcoe   polcof\n";
    	for(int s = 0; s < (int)n; s++){
    		fileTwo << s << " " << polcoe_val[s] << " " << polcof_val[s] << endl;
    	}
    	fileTwo.close();
	}

};


int main(){

	//runs code for both values of n
	evaluate(5.0, "RatnFive.dat", "coefFive.dat");
	evaluate(20.0, "RatnTwenty.dat", "coefTwenty.dat");

	return 0;
}