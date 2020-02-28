//  file: integ_routines_HW2.h
// 
//  Header file for integ_routines_HW2.cpp
//
//
//  Programmer:  Nathan Jansen  jansenn1@msu.edu
//
//  Revision history:
//      18-Feb-2020  original version, for HW2 PHY 905
//
//  
//
//************************************************************************

//  begin: function prototypes 
 
extern double simpsons_rule ( int num_pts, double x_min, double x_max, 
                         double (*integrand) (double x) );    // Simpson's rule function
extern double milne_rule ( int num_pts, double x_min, double x_max, 
                       double (*integrand) (double x) );    // Milne's rule function
  //  end: function prototypes 
