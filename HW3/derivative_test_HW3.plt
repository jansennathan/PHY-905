<<<<<<< HEAD
#  file: derivative_test_HW3.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Nathan Jansen jansenn1@msu.edu
# 
#  Revision history
#   2020-03-29  original version for HW3
#   
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using exp(-x)'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:3]
set yrange [-15:10]

# fit the curve
f2(x) = a2*x + b2
f3(x) = a3*x + b3
f4(x) = a4*x + b4

fit [-5:-1] f2(x) "derivative_test_HW3.dat" using ($1):($3) via a2,b2 
fit_title2 = sprintf("%-+4.1f*x %-+4.1f",a2,b2)

fit [-2:-1] f3(x) "derivative_test_HW3.dat" using ($1):($4) via a3,b3 
fit_title3 = sprintf("%-+4.1f*x %-+4.1f",a3,b3)

fit [-1:.3] f4(x) "derivative_test_HW3.dat" using ($1):($5) via a4,b4 
fit_title4 = sprintf("%-+4.1f*x %-+4.1f",a4,b4)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
    
plot "derivative_test_HW3.dat" using ($1):($3) title 'central',\
	 a2*x + b2 title fit_title2,\
	 "derivative_test_HW3.dat" using ($1):($4) title 'ExtrapolationOld',\
	 a3*x + b3 title fit_title3,\
	 "derivative_test_HW3.dat" using ($1):($5) title 'ExtrapolationNew', \
	 a4*x + b4 title fit_title4
	 
# output the plot to the file derivative_test_HW3.ps   
set out "derivative_test_HW3.ps"
set term postscript color enhanced
replot
=======
#  file: derivative_test_HW3.plt 
#
#  Gnuplot plot file for derivative_test output
#  
#  Programmer:  Nathan Jansen jansenn1@msu.edu
# 
#  Revision history
#   2020-03-29  original version for HW3
#   
#

# record the time and date the graph was generated
set timestamp

# titles and labels
set title 'Test of Numerical Derivatives using exp(-x)'
set xlabel 'log10(mesh size)'
set ylabel 'relative error'

# move the legend to a free space
set key left

# set the x and y axis scales (already logs)
set xrange [-10:3]
set yrange [-15:10]

# fit the curve
f2(x) = a2*x + b2
f3(x) = a3*x + b3
f4(x) = a4*x + b4

fit [-5:-1] f2(x) "derivative_test_HW3.dat" using ($1):($3) via a2,b2 
fit_title2 = sprintf("%-+4.1f*x %-+4.1f",a2,b2)

fit [-2:-1] f3(x) "derivative_test_HW3.dat" using ($1):($4) via a3,b3 
fit_title3 = sprintf("%-+4.1f*x %-+4.1f",a3,b3)

fit [-1:.3] f4(x) "derivative_test_HW3.dat" using ($1):($5) via a4,b4 
fit_title4 = sprintf("%-+4.1f*x %-+4.1f",a4,b4)

# set the terminal type to be the screen (which is x11 here)
set term x11

# plot the data as well as the fit, with appropriate titles 
    
plot "derivative_test_HW3.dat" using ($1):($3) title 'central',\
	 a2*x + b2 title fit_title2,\
	 "derivative_test_HW3.dat" using ($1):($4) title 'ExtrapolationOld',\
	 a3*x + b3 title fit_title3,\
	 "derivative_test_HW3.dat" using ($1):($5) title 'ExtrapolationNew', \
	 a4*x + b4 title fit_title4
	 
# output the plot to the file derivative_test_HW3.ps   
set out "derivative_test_HW3.ps"
set term postscript color enhanced
replot
>>>>>>> f1d086ddc506c19182c349c55eb67f400d131adf
