#  file: wave_error.plt 
#
#  Gnuplot plot file for eigen_basis output
#  
#  Programmer:  Nathan Jansen jansenn1@msu.edu
# 
#  Revision history
#   2020-04-17  original version for HW3
#   
#


    
plot "wave_error.dat" using ($1):($2) title 'PSI',\
	

	 
# output the plot to the file wave_error.ps   
set out "wave_error.ps"
set term postscript color enhanced
replot
