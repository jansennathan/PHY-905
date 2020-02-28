# gnuplot plot file: integral_HW2.plt
set title 'Integral Tests'
set xlabel 'N'
set ylabel 'abs error'
set xrange [0:4]


# move the legend to a free space

set key at graph 0.7, 0.9

# set the size of the plotted points
set pointsize 1.5  


# fit the curve
f1(x) = m1*x + b1
f2(x) = m2*x + b2
f3(x) = m3*x + b3
f4(x) = m4*x + b4
f5(x) = m5*x + b5

fit [.75:2.5] f1(x) "SimpsonsInt.dat" using 1:2 via m1 ,b1			# Simpsons linear
fit_title = sprintf("%-+4.1f*x %-+4.1f",m1,b1)


fit [.75:2.5] f2(x) "MilneInt.dat" using 1:2 via m2 ,b2			#Milne linear fit 
fit_title2 = sprintf("%-+4.1f*x %-+4.1f",m2,b2)

fit [2.5:3] f3(x) "SimpsonsInt.dat" using 1:2 via m3 ,b3			#Simpsons roundoff fit 
fit_title3 = sprintf("%-+4.1f*x %-+4.1f",m3,b3)

fit [2.5:3] f4(x) "MilneInt.dat" using 1:2 via m4 ,b4			# Milne roundoff fit
fit_title4 = sprintf("%-+4.1f*x %-+4.1f",m4,b4)

fit [.5:3] f5(x) "EmpiricalError.dat" using 1:2 via m5 ,b5			# Milne roundoff fit
fit_title5 = sprintf("%-+4.1f*x %-+4.1f",m5,b5)
 
# move the key away from the lines
set key top left    

# turn on a date/time indicator
set timestamp	
  
# set the terminal type to be the screen (which is x11 here)
set term x11

plot "SimpsonsInt.dat" using ($1):($2) title 'Simpsons',\
	m1*x + b1 title fit_title,\
	m3*x + b3 title fit_title3,\
 "MilneInt.dat" using ($1):($2) title 'Milne',\
	m2*x + b2 title fit_title2,\
	m4*x + b4 title fit_title4,\
 "EmpiricalError.dat" using ($1):($2) title 'EmpiricalError',\
	m5*x + b5 title fit_title5
	
set out "integral_HW.ps"	# name of the output postscript file
set terminal postscript	        # switch to postscript mode
# plot to the file
replot	