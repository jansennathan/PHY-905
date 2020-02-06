# gnuplot plot file: bessel_NJ_2020.plt
set terminal x11   # terminal type: for a Mac, use "aqua" instead of "x11"
set title 'Relative Difference Up and Down Bessel"
set xlabel 'X'
set ylabel 'Relative error'
set yrange [-18:1]
set pointsize 1.5   # set the size of the plotted points
set key top right    # move the key 
set timestamp	  # turn on a date/time indicator
plot "bessel_NJ_2020.dat" using 1:6 title 'X vx rel Error'
set out "bessel_NJ_2020.ps"	# name of the output postscript file
set terminal postscript	        # switch to postscript mode
replot  		  	# plot to the file