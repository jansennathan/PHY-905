//  file: integ_HW2.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Nathan Jansen  jansenn1@msu.edu
//
//  Revision history:
//      18-Feb-2020  original version, for HW2 PHY 905
//		24-Feb-2020  altered integration routines and max intervals
//                         
//
//	Comments:
//   compile with make_integ_HW2
//  	
//	Analysis of graphs:
//		Region of linear (logrithamic) slopes: 
//
//
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "integ_routines_HW2.h"	// prototypes for integration routines

double my_integrand (double x);


const double pi = 3.1415926535897932384626;	// setting an approximate value for pi

//************************************************************************

int
main ()
{
  // set up the integration specifiction
  const int max_intervals = 10001;	// maximum number of intervals  (I had to use quite a few points before I got roundoff in Milne, this unfortantely runs for awhile)
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 22./7. - pi;	// the "exact" answer of the integral
  double result = 0.;  // approximate answer double

  // open the output file stream
  ofstream integ_HW2_out ("integral.dat");	// save data in integral.dat
  integ_HW2_out  << "#  N                                      Simpsons                                   Milne " << endl;
  integ_HW2_out  << "#--------------------------------------------------------------------------------------------" << endl;

  // Milne and Simpson's rules both require an odd number of intervals  
  for (int i = 2; i <= max_intervals; i += 2)
  {
    integ_HW2_out  << setw(16) << log10(i) << "  ";

    result = simpsons_rule (i, lower, upper, &my_integrand);
    integ_HW2_out << setprecision(16) << setw(16) << "  " << scientific << log10(fabs(result-answer));  //printing the simpsons error with error value computed simultaneosly

    result = milne_rule (i, lower, upper, &my_integrand);
    integ_HW2_out  << setprecision(16) << setw(16) << "  " << scientific << log10(fabs(result-answer));  //printing the simpsons error with error value computed simultaneosly
	

    integ_HW2_out  << endl;
  }

  cout << "data stored in integral.dat\n";  //printing out that data storage was successful
  integ_HW2_out .close ();

  return (0);
}

//************************************************************************

// the function to integrate 
double
my_integrand (double x)
{
  return ((pow(x,4)*pow(1-x,4))/(1+pow(x,2)));  // The integral to be evaluated, chosen as it is more complicated and has a cool anwser
}
