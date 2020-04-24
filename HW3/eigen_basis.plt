#  file: eigen_basis.plt 
#
#  Gnuplot plot file for eigen_basis output
#  
#  Programmer:  Nathan Jansen jansenn1@msu.edu
# 
#  Revision history
#   2020-03-29  original version for HW3
#   
#


# set the x and y axis scales (already logs)
set xrange [0:10]
set yrange [0: 0.8]

    
plot "eigen_basis.dat" using ($1):($2) title 'PSI',\
	 "eigen_basis.dat" using ($1):($3) title 'True',\
	 
# output the plot to the file eigen_basis.ps   
set out "eigen_basis.ps"
set term postscript color enhanced
replot
