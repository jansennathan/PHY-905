//  file: area._NJ_2020.cpp
//	
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//	Edited by:   Nathan Jansen   jansenn1@msu.edu
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//		28-Jan-2020  finish To Do tasks 1&2 for HW#1 PHY 905
//					 added constant pi with <math.h>, added comparison to a truncated pi using both ratio and difference of areas
//		30-Jan-2020	 Made inline functions
//		 			 Made function for calculation of areas
//					 Loop to create radii (bounded by user input) and add to an output file, then use it as input to generate a .dat with the areas differences and ratios
//					 Added If else loop to disallow negative radii from populating the output file 
//		03-Feb-2020  Fixed ratio function in while loop
//		
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

// include files
#include <iostream>	     // this has the cout, cin definitions
#include <iomanip>		 // manipulators like setprecision
#include <math.h>		 // including the preset pi
#include <fstream>		 // to read and write data as file streams 
using namespace std;     // if omitted, then need std::cout, std::cin 

//*********************************************************************//

const double pi = 3.1415926535897932385;   // define pi as a constant 

// function prototypes

double area_function (double pi, double r);

// To do #3 define an inline square function

inline double Square (double x, double y)
{	
	return x*x;
}

inline double Ratio (double x, double y) 
{
	return x/y;
}


inline double Difference (double x, double y)
{ 
	return abs(x-y);
}

int
main ()
{
  double radius1;    // every variable is declared as int or double or ...
  double radius2;  // adding an extra radius
  double approxPi = 3.14159265359;  		
  
  cout << "Enter the radius of circle 1: ";	// ask for circle 1 radius
  cin >> radius1;							 
  cout << "Enter the radius of circle 2:  "; // ask for circle 2  radius
  cin >> radius2;
  
  cout << " " << endl; // Just so it looks nice in the interface after running 
  

  
  double area1 = M_PI * radius1 * radius1;	    // standard area formula using preset pi
  double area2 = approxPi * radius2 * radius2;  // standard area formula using truncated pi
  double difference = abs(area1 - area2);       // calculating the difference in area
  double ratio = area1/area2; 				    // calculating the ratio of the two circles
  


  //cout << setprecision (18) << M_PI << endl; (this was for testing if M_Pi is actually pi)
  
  
  // To do 1&2******************************************************************//
  
  cout << "To do 1&2:" << endl;
  cout << "Radius 1 = " << setprecision (18) << radius1 << ",  area 1 = " << setprecision (18) << area1 << endl;
  cout << "Radius 2 = " << setprecision (18) << radius2 << ",  area 2 = " << setprecision (18) << area2 << endl;
  cout << "Ratio of radii 1:2 = " << setprecision (18) << ratio << endl; 
  cout << "Difference in area =  " << setprecision (18) << difference << endl; 
  
  
  //To do 3******************************************************************//  
  
  cout << " " << endl;
  cout << "To do 3:" << endl;
  cout << "Radius 1 Squared: " << setprecision (18) << Square(radius1,radius1) << endl; // squaring radii using an inline square function
  cout << "Radius 2 Squared: " << setprecision (18) << Square(radius2,radius2) << endl;
  cout << "Inline ratio 1:2 : " << setprecision (18) << Ratio(area1,area2) << endl; // ratio using an inline function
  cout << "Inline difference: " << setprecision (18) << Difference(area1,area2) << endl; // difference using an inline function
  
  
  //To do 4 ******************************************************************//
  
  double functionarea1 = area_function(M_PI, radius1); // using the area function for radius 1 or 2
  double functionarea2 = area_function(approxPi, radius2);
  
  cout << " " << endl;
  cout << "To do 4:" << endl;
  cout << "Function Area 1: " << setprecision (18) << functionarea1 << endl;
  cout << "Function Area 2: " << setprecision (18) << functionarea2 << endl;


  // To do 5 & 6 ******************************************************************//
  
  double rad_min; // for while loop to generate different radii
  double rad_max;
  cout << "Enter the max radius of circle: ";	// ask for max radius
  cin >> rad_max;
  cout << "Enter the minimum radius of circle:  "; // ask for min radius
  cin >> rad_min;
  

  
  ofstream radius_out ("radius_NJ_2020.dat"); // open the radius output file
  ofstream area_out ("area_NJ_2020.dat"); // open the area output file
  area_out << "  ______Radius______     " << "    _______Area 1________    " << "  _______Area 2________          " << "     _______Ratio________" << "            _______Difference________" << endl;  
  
  
 while (rad_max >= rad_min) // loop to generate a series of radii differing by 1 unit 
 { 
	radius_out << scientific << setprecision (8)
      << rad_max << "   "
	  <<endl;
	rad_max -= 1;
 }
 
 string line;
  ifstream myfile ("radius_NJ_2020.dat"); //Reading output file and using as input for area function
  if (myfile.is_open())
  {
	 
    while ( getline (myfile,line) )
    { 
	  double inputarea = area_function(M_PI, stod (line));
	  double inputarea2 = area_function(approxPi, stod (line));
	  double ratio;
	  stod(line) == 0 ? ratio == 0 //sets ratios to 0 when r = 0
	  : 
	  ratio = Ratio (inputarea, inputarea2);
	  double diff = Difference (inputarea, inputarea2);
	  
	  stod(line) >= 0 ?		//If else statement to filter out negative radii
	     area_out << scientific << setprecision (18)
			<< " " << stod (line) << "   "
			<< inputarea << "   "  // if radius is positive print area to output file
			<< inputarea2 << "           "
			<< ratio << "           "
			<< diff << "           "
			<< endl
	  :
         area_out << scientific << setprecision (18)
			<< stod (line) << "   "
			<< "   negative radius           " << "   " //if raduis is negative print to output file "negative radius"
			<< "negative radius              " << "   "
			<< "   negative radius           " << "   "
			<< "   negative radius           " << "   "
			<< endl;
	
	  //cout << setprecision(18) << inputarea << endl;
    }
    myfile.close();
  }
  return 0;			// "0" for successful completion
}

//*********************************************************************//


//*****To do 4. split the calculation off into a function (subroutine)***********//


double
area_function (double pi, double r)
{ 
  return pi * r * r;
}
