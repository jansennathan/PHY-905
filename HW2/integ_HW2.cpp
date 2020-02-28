//  file: integ_HW2.cpp
//
//  This is a test program for basic integration methods.               
//                                                                     
//  Programmer:  Nathan Jansen  jansenn1@msu.edu
//	Worked with:  Kyle Davidson
//
//  Revision history:
//      18-Feb-2020  original version, for HW2 PHY 905
//		24-Feb-2020  altered integration routines and max intervals
//      25-Feb-2020  adding gsl routine
//		27-Feb-2020  altered Milne rule, made gsl print to dat file, did empirical error analysis 
//		28-Feb-2020  Added final comments on error analysis                 
//
//	Comments:
//   compile with make_integ_HW2
//  	
//	Analysis of graphs:
//		Part b:	Region of linear (logrithamic) slopes: Milne = -6.0 (x= 0.75-3.0) Simpsons = -5.9.  This is logical for the Milne rule however unexpected
//		for the Simpsons rule. In the linear region the error should match the order of the truncation of the taylor series. For the Milne
//		there is 5 terms giving N^5, however the rule is that the error propogates as N+1, thus a slope of 6 is exactly what is to be expected 
//		for the Milne rule. I believe this is because I chose a very high order polynomial, generally these methods work the best for polynomials 
//		similar in order to their truncation values, this is why I suspect the simpsons failed. As for round off error I am not sure why it is so 
//  	flat, it should be proportional to the square root of the truncation error but in both cases it is simply zero. I think this means both methods 
//		are still consistent approximations in this region. Finally for the error I chose to do the empirical analysis. The slope of the curve exactly
//		m = 6, which is the truncation error, so this shows it is a reliable method of approximations even when an exact anwser is not known.
//
//		Part c: For both Milne and Simpsons the optimal value is around N = 2800, this is the minima in the relative error functions before the 
//		round off error begins.  As for a more analytic approach you can look at the value of the log plot. We know that doubles are reliable to 10-16
//   	which is exactly where the plot flattens and begins round off. Theoretically based on the session 3 notes the value should be roughly 2511 steps
//		I would consider this to be a pretty good estimate and that the theory is generally in agreement with the practice.
//		
//
//
//************************************************************************

// include files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>


using namespace std;

#include "integ_routines_HW2.h"	

// prototypes for integration routines

double my_integrand (double x);

double my_gsl_integrand (double x, void *params);



const double pi = 3.1415926535897932384626;	// setting an approximate value for pi

//************************************************************************

int
main (void)
{
  // set up the integration specifiction
  const int max_intervals = 1501;	// maximum number of intervals 
  const double lower = 0.0;	// lower limit of integration
  const double upper = 1.0;	// upper limit of integration

  const double answer = 22./7. - pi;	// the "exact" answer of the integral
  double result = 0.;  // approximate answer double

  // open the output file stream
  ofstream Simp_out ("SimpsonsInt.dat");	// save Simpsons data in integral.dat
  ofstream Milne_out ("MilneInt.dat");		// save Milne data in integral.dat
  ofstream gsl_out ("GslInt.dat");	// save gsl data in integral.dat
  ofstream Empirical_out("EmpiricalError.dat"); // save empirical error
  
  Simp_out  << "#  N                                      Simpsons " << endl;
  Simp_out  << "#--------------------------------------------------" << endl;
  
  Milne_out  << "#  N                                      Milne " << endl;
  Milne_out  << "#--------------------------------------------------" << endl;


  // Milne and Simpson's rules both require an odd number of intervals  
  for (int i = 3; i <= max_intervals; i += 2)
  {
    Simp_out  << setw(16) << log10(i) << "  ";

    result = simpsons_rule (i, lower, upper, &my_integrand);  //printing the simpsons error with error value computed simultaneosly
    Simp_out << setprecision(16) << setw(16) << "  " << scientific << log10(fabs(result-answer) + 10e-16);  // addition of 10e-16 to avoid values less than machine precision

    Simp_out  << endl;
  }
 
	Simp_out .close ();

for (int i = 5; i <= max_intervals; i += 4)
  {
    Milne_out  << setw(16) << log10(i) << "  ";

    result = milne_rule (i, lower, upper, &my_integrand); //printing the Milne error with error value computed simultaneosly
    Milne_out  << setprecision(16) << setw(16) << "  " << scientific << log10(fabs(result-answer) + 10e-16);  // addition of 10e-16 to avoid values less than machine precision
	
   Milne_out  << endl;
  }


   Milne_out .close ();

//*********************************************************************************************

  gsl_integration_workspace *work_ptr
    = gsl_integration_workspace_alloc (10000);

  double lower_limit = 0;	/* lower limit a */
  double upper_limit = 1;	/* upper limit b */
  double abs_error = 1.0e-8;	/* to avoid round-off problems */
  double rel_error = 1.0e-8;	/* the result will usually be much better */
  double resultgsl;		/* the result from the integration */
  double error;			/* the estimated error from the integration */

  double alpha = 1.0;		// parameter in integrand
  double expected = 22./7. - pi;	// exact answer

  gsl_function My_function;
  void *params_ptr = &alpha;

  My_function.function = &my_gsl_integrand;
  My_function.params = params_ptr;

  gsl_integration_qags (&My_function, lower_limit, upper_limit,
			abs_error, rel_error, 10000, work_ptr, &resultgsl,
			&error);

    
  int width = 20;  // setw width for output
  gsl_out << "actual error    = " << setw(width) << log10(fabs(result - expected)) << endl;
  gsl_out << "intervals =  " << work_ptr->size << endl;
  cout << "data stored in integral.dat\n";  //printing out that data storage was successful
  
  
  //****************************************************************************************//
  
  // Bonus (Alt) Empirical Error Analysis, I figure since I never know the exact anwser in my research this would be best
  
  //Will be using equation 4.14 from session 4 notes, I will be taking the log so the error should be the slope which is beta
  
 double empirical_max_interval = 1501;  // smaller as I want to use 2N and don't want it any more computationaly expensive

 for (int i = 5; i <= empirical_max_interval; i += 4)
  {
    Empirical_out  << setw(16) << log10(i) << "  ";

    double resultN = milne_rule (i, lower, upper, &my_integrand); //calculating integral at N
	
	double result2N = milne_rule (2*i, lower, upper, &my_integrand); //calculating integral at 2N
	
    Empirical_out  << setprecision(16) << setw(16) << "  " << scientific << log10(fabs((resultN-result2N)/(result2N))+ 10e-16);  // addition of 10e-16 to avoid values less than machine precision
	
	Empirical_out  << setprecision(16) << setw(16) << "  " << scientific << resultN; // Just to check they are calculating it correctly
	Empirical_out  << setprecision(16) << setw(16) << "  " << scientific << result2N;
	
   Empirical_out  << endl;
  }
  
  
  return (0);
}

//************************************************************************

// the function to integrate 

//this was a test function to see if it agreed with others, it was my loop to the dat file that was flawed however, not my function
/*my_integrand (double x)
{
  return ((pow(x-1,2)/pow(x+1,2))); 
}*/

//Declaring my integrand for Milne and Simpsons
double
my_integrand (double x)
{
  return ((pow(x,4)*pow(1-x,4))/(1+pow(x,2)));  // The integral to be evaluated, chosen as it is more complicated and has a cool anwser
}



// Declaring a GSl function

 double my_gsl_integrand (double x, void *params)
 {
	double alpha = *(double *) params; //While it is slightly unnecessary for my function I decided to use a parameter for practice
    return ((pow(x,4)*pow(alpha-x,4))/(alpha + pow(x,2)));
 } 




