//  file: bessel_NJ_2020.cpp 
//
//  Spherical Bessel functions via up and down recursion      
//                                                                     
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//	Revised via: Nathan Jansen 	 jansenn1@msu.edu
//
//  Revision history:
//      02-Jan-2011  new version, for 780.20 Computational Physics
//		14(?)-Jan-2020 completed tasks related to Bessel 1 in activity 2 worksheet
//		03-Feb-2020  Began working on HW, Bessel 2 #3
//
//  Notes:  
//   * compile with:  "g++ -o bessel bessel.cpp"
//   * adapted from: "Projects in Computational Physics" by Landau and Paez  
//             copyrighted by John Wiley and Sons, New York               
//             code copyrighted by RH Landau  
//   * added relative error calculation and output to bessel.cpp
//   * data saved as: x y1 y2 rel_error log10(x) log10(rel_error)
//
//
//
//	Discussion 
//		7-Feb-2020:  From x=0 to x= 10 ( in log log x= 0 to 1) there is a sharp slope downward, nearly m = - 16.  Looking at the .dat file it is an interesting
//		region of the graph because its a linear log log so the error is decreasing logathrimcally as approaches 10.  When the error is unity, it means that the 
//		values are very different and as such the error is large. Looking at the number sin the .dat file the up recursion value is two orders of magnitude
// 		greater than the down recursion. This is likely resulting in significant round off error resulting in up/up and unity for the error value. In the middle region
// 		where 10 < x < 15, the error is the lowest with a near zero slope. This is a region where the numbers produced from the plots are higly similar thus the error is low, however there are 
//  	some points where the error is zero and thus -20 on the log log plot, this is likely due to the fact that the values are so close or equal and subtractive cancelation
//  	is occuring resulting in a zero value. The low error is due to the fact that there is not much difference in the recursions at these values so the numbers are in the 
//  	same order of magnitude.  It is clear from the .dat file that the large error occurs when the values are in the same order of magnitude, thus it is likely that most of 
// 		the additional error is due to round off error.
//
//  
//************************************************************************

// include files
#include <iostream>		// note that .h is omitted
#include <iomanip>		// note that .h is omitted
#include <fstream>		// note that .h is omitted
#include <cmath>
#include <gsl/gsl_sf_bessel.h>  // gsl Bessel special function header file

using namespace std;		// we need this when .h is omitted

// function prototypes 
double down_recursion (double x, int n, int m);	// downward algorithm 
double up_recursion (double x, int n);	        // upward algorithm 
double error (double u, double d);  				// error function
// global constants  
const double xmax = 100.0;	// max of x  
const double xmin = 0.1;	// min of x >0  
const double step = 0.1;	// delta x  
const int order = 10;		// order of Bessel function 
const int start = 50;		// used for downward algorithm 

//********************************************************************
int
main (void)
{
  double ans_down, ans_up;
  double rel_error, log_rel_error;
  double bessel;
  // open an output file stream
  ofstream my_out ("bessel_NJ_2020.dat");

  my_out << "# Spherical Bessel functions via up and down recursion," 
         << " l = " << order << endl;
	 
  my_out << "#   x       jdown(x)      jup(x)         rel. error        ";
  my_out << "  log10(x)    log10(rel.err.)   Bessel GSL Routuine" << endl; 
	 

  // step through different x values
  for (double x = xmin; x <= xmax; x += step)
    {
      ans_down = down_recursion (x, order, start);
      ans_up = up_recursion (x, order);
	  rel_error = error (ans_up, ans_down);
      // Calculation for the absolute value of the relative error between the up and down recursions
	  bessel = gsl_sf_bessel_jl(10, x); // the GSL bessel function
	  
      if (rel_error > 1.e-20)
	{
	  log_rel_error = log10 (rel_error);
	}
      else
	{
	  log_rel_error = -20.;
	}
      my_out << fixed << setprecision (8) << setw (8) << x << " "
	<< scientific << setprecision (8)
	<< setw (13) << ans_down << " "
	<< setw (13) << ans_up << "  "
	<< setw (13) << rel_error << "  "
	<< setw (13) << log10 (x) << "  "
	<< setw (13) << log_rel_error << "  " << setw(13) << bessel
        << endl;
    }
  cout << "data stored in bessel_NJ_2020.dat." << endl;

  // close the output file
  my_out.close ();
  return (0);
}


//------------------------end of main program----------------------- 


// function for relative error

double error (double u, double d)
{
	return fabs (d - u) / (fabs (d) + fabs (u));
}

// function using downward recursion  
double
down_recursion (double x, int n, int m)
{
  double j[start + 2];		// array to store Bessel functions 
  j[m + 1] = j[m] = 1.;		// start with "something" (choose 1 here) 
  for (int k = m; k > 0; k--)
    {
      j[k - 1] = ((2. * (double) k + 1.) / x) * j[k] - j[k + 1];  // recur. rel.
    }
  double scale = ((sin (x)) / x) / j[0];	// scale the result 
  return (j[n] * scale);
}


//------------------------------------------------------------------ 

// function using upward recursion  
double
up_recursion (double x, int n)
{
  double term_three = 0.;
  double term_one = (sin (x)) / x;	// start with lowest order 
  double term_two = (sin (x) - x * cos (x)) / (x * x);	// next order
  for (int k = 1; k < n; k += 1)	// loop for order of function     
    { // recurrence relation
      term_three = ((2.*double(k) + 1.) / x) * term_two - term_one;	       
      term_one = term_two;
      term_two = term_three;
    }
  return (term_three);
}
