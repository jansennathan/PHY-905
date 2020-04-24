#  file: wave_error.plt 
#
#  Gnuplot plot file for eigen_basis output
#  
#  Programmer:  Nathan Jansen jansenn1@msu.edu
# 
#  Revision history
#   2020-04-17  original version for HW3
#	2020-04-24	revised to include ranges rather than global
#   


# set the x and y axis scales (already logs)
set xrange [0:35]
set yrange [0:200]
    
plot "wave_error.dat" using ($1):($2) title 'PSI low',\
	 "wave_error.dat" using ($1):($3) title 'PSI mid',\
	 "wave_error.dat" using ($1):($4) title 'PSI high',\
	 
# output the plot to the file wave_error.ps   
set out "wave_error.ps"
set term postscript color enhanced
replot
