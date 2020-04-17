# gnuplot plot file: harmonic_series.plt
set terminal x11   # terminal type: for a Mac, use "aqua" instead of "x11"
set title 'Harmonic Series Summation Difference Single Precision"
set xlabel 'N (max summation index)'
set ylabel 'Average'


set pointsize 1.5   # set the size of the plotted points
set key top right    # move the key 
set timestamp	  # turn on a date/time indicator

# fit the curve
f1(x) = a1*x + b1
fit [1:8] f1(x) "harmonic_series.dat" using ($1):($2) via a1,b1 
fit_title = sprintf("%-+4.1f*x %-+4.1f",a1,b1)

plot "harmonic_series.dat" using 1:2 title 'N vs Average',\
	a1*x + b1 title fit_title

set out "harmonic_series.ps"	# name of the output postscript file
set terminal postscript	        # switch to postscript mode
replot  		  	# plot to the file