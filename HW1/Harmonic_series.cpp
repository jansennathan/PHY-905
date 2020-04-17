//************************************************************************ 
//  file: Harmonic_series.cpp  (HW # 1 PHY905 MSU Spring 2020)
//   
// 
//  Program to sum harmonic series either up from 1 or down from N
//   
//
//  Programmer: Nathan Jansen,  jansenn1@msu.edu
//
//  Revision history:
//      03-Feb-2020  (my birthday!)  first version, using order_of_summation1a.cpp and quadratic_equation_2.cpp as references
//									 For loop that sums the Harmonic series	both from 1 to N, and N to 1
//									 Generates an output file with the difference betweem the up and down sum vs N
//									 Made a loop to do the same test but in double precision
//  Notes:
//		  Compile with make -f make_harmonic_series
//
//	Discussion 
//		7-Feb-2020:  
//  	The error looks like a power law in the entirety of the region I plotted. I added a fit and the slope
//  	the slop is one, meaning that it is jumping single orders of magnitude in error. This error is easily explained
//		with round off error. When summing up, each value gets smaller by an order of magnitude, when being added to one in
//		single precision this will just round based on the one so when N is very large it ignores it and will reach a point
// 		where N will no longer be part of the sum, thus giving an upper value on what the computer can calculate,
//  	When summing down however each case is adding larger values, up by an order of magnitude in each case. This allows for 
//		each value to contribute to the sum as there is not much round off. 
//
//*************************************************************************


// include files
#include <iostream>		
#include <iomanip>		
#include <fstream>		
#include <cmath>
using namespace std;		

//*************************************************************************


float sup (int N) // function 
{
	float sum = 0;
	for (int i = 1; i < N ; i++)
	{ 
		sum += 1./i;
	}
	
	return sum;
}

float sdown (int N) //function for down summation
{
	float sum = 0;
	for (int i = 1; i < N ; i++)
	{ 
		sum += 1./(N-i);
	}
	
	return sum;
}


float error (float u, float d)
{
	return fabs ((fabs(u) - fabs(d)) / (fabs(u) + fabs(d))); 
}
main ()
{

float sum_up= 0;      	// Summing up (n= 1 to N) (single precision) 
float sum_down = 0.;     // Summing down (n= N to 1) (single precision) 
float rel_error;
 
	  
	ofstream fplot ("harmonic_series.dat");  // open the plot file stream for single precision
	fplot << "# Summation of harmonic series up and down" << endl
    << endl;  
	
	//fplot << "N                    Difference in Sums" << endl;
	fplot << "# N                    Difference in Sums                Sum Up                  Sum Down" << endl;

	ofstream fplot2 ("harmonic_series_double.dat");  // open the plot file stream for double precision
	fplot2 << "# Summation of harmonic series up and down double precision" << endl
    << endl;  
	
	fplot2 << "# N                    Average Difference                Sum Up                  Sum Down" << endl;


//**********Summing using functions**********

for (int N = 10; N < 1000000000; N *= 10)
{ 
    sum_up = sup(N);
	sum_down = sdown(N);
	rel_error = error (sum_up, sum_down);
	
	fplot << left <<  scientific << setprecision(3)  << setw(18) 
    << log10(N) << "   " << setprecision(18) << log10(rel_error) << "   " << sum_up << "   " << sum_down << endl;
	
	sum_down = 0;
	sum_up = 0;
	rel_error = 0;
}


return (0);
}
