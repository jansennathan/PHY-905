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
//*************************************************************************


// include files
#include <iostream>		
#include <iomanip>		
#include <fstream>		
#include <cmath>
using namespace std;		

//*************************************************************************

float sup (int i) // function 
{
	return 1./i ;
}

float sdown (int i, int imax) //function for down summation
{
	return 1./(imax-i);
}

float error (float u, float d)
{
	return fabs ((fabs(u) - fabs(d)) / (fabs(u) + fabs(d))); 
}
main ()
{
//float denom = 1;         // single precision increment = 1 (integers only)
float sum_up= 0;      	// Summing up (n= 1 to N) (single precision) 
float sum_down = 0.;     // Summing down (n= N to 1) (single precision) 
float rel_error;
//double sum_up_dp= 1;      	// Summing up (n= 1 to N) (double precision) 
//double sum_down_dp = 0.;     // Summing down (n= N to 1) (double precision) 
	  
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
	for (int i = 1; i < N ; i++)
	{ 
		sum_up += sup(i);
		sum_down += sdown(i, N);
	
	}
	rel_error = error (sum_up, sum_down);
	
	fplot << left <<  scientific << setprecision(3)  << setw(18) 
    << log10(N) << "   " << setprecision(18) << log10(rel_error) << "   " << sum_up << "   " << sum_down << endl;
	
	sum_down = 0;
	sum_up = 0;
	rel_error = 0;
}

//******** Summing N time fro n = 1 to N in single precision **************************************************************
	
/*for (float N = 1; N <= 1000000000; N *= 10)
{

	for (int i = 1; i < N ; i++)
	{
	  sum_up += 1./(i+1); // note sum_up starts as one so the sum is contained in this for loop
	  sum_down += 1./(i+1);
	}

	
	sum_down += 1;  // add 1 to the sum from n= N to n = 1
	
	float dif = fabs ((sum_up - sum_down) / (sum_up + sum_down));  // creates a single precision float for the difference of the two values
	fplot << left <<  scientific << setprecision(3)  << setw(18) 
    //<< N << "   " << setprecision(18) << dif << endl; // adds the data produced from loop into the .dat file for plotting 
	<< log10(N) << "   " << setprecision(18) << log10(dif) << "   " << sum_up << "   " << sum_down << endl;
	sum_down = 0; // reset sum_down to zero
	sum_up = 1;  // resets sum_up to 1
	
}*/

//************Out of curiosity I wanted to see the results using double precision******************
	
/*for (double N = 1; N <= 10; N *= 10) // Summing N time fro n = 1 to N
{

	if (N == 1)  // This is for N =1
	{ 
	  sum_up_dp += denom/(2);
	  sum_down_dp += denom/(2);
	}
	else // this is excluding when N = 1 because I couldn't figure out another way
	{
		for (int i = 1; i < N ; i++)
		{
		  sum_up_dp += denom/(i+1); // note sum_up starts as one so the sum is contained in this for loop
		  sum_down_dp += denom/(i+1);
		}
	}
	
	sum_down_dp += 1;  // add 1 to the sum from n= N to n = 1
	
	double dif_dp = fabs ((fabs(sum_up_dp) - fabs(sum_down_dp)) / (fabs(sum_up_dp) + fabs(sum_down_dp)));  // creates a double precision float for the difference of the two values
	fplot2 << left <<  scientific << setprecision(3)  << setw(18) 
    << N << "   " << setprecision(18) << dif_dp << "   " << sum_up_dp << "   " << sum_down_dp << endl; // adds the data produced from loop into the .dat file for plotting 
	
	sum_down_dp = 0; // reset sum_down_dp to zero
	sum_up_dp = 1;  // resets sum_up_dp to 1
	
}*/
	

return (0);
}
