#   Scattering.py : Soln of Lippmann Schwinger in p space for scattering
#
#   Programmer: Nathan Jansen       jansenn1@msu.edu
#
#   
#   History:
#       11-April-2020: original version
#       17-April-2020: changed to use gaussian integration, added plots
#       20-April-2020: Added wavefunction constructor and plot
#       24-April-2020: Error plotting added
#
#
#
#_________________________________________________________________________

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy.linalg as lina 
import numpy as np
from numpy.polynomial.polynomial import polyfit


np.seterr(divide='ignore', invalid='ignore')  #numpy fails for sin(0)/sin(0) 

#    Defining the gaussian quadrantures for integration
def gauss (npts, job, a, b, x, w) :
    m = i = j = t = t1 = pp = p1 = p2 = p3 = 0.
    eps = 3.E-10
    m = (npts + 1)//2;
    for i in range (1, m+1):
        t = np.cos(np.pi*(float(i)-0.25)/(float(npts) + 0.5))
        t1 = 1
        while ((abs(t-t1)) >= eps):
            p1 = 1. ; p2 = 0. ;
            for j in range (1 , npts +1):
                p3 = p2
                p2 = p1
                p1 =((2*j-1)*t*p2-(j-1)*p3)/j
            pp = npts*(t*p1-p2)/(t*t-1.)
            t1 = t ; t = t1 - p1/pp
        x[i-1] = -t
        x[npts-i] = t
        w[i-1] = 2./((1.-t*t)*pp*pp)
        w[npts-i] = w[i-1]
    for i in range (0 , npts):
        xi = x[i]
        x[i] = (b*xi + b + a + a) / (1. - xi)
        w[i] = w[i]*2.*(a + b)/( (1. - xi)*(1. - xi) )


#*****Constants
ko = 0.02
lambd = 1.5
b = 10.0;

##*********Empty arrays for graphing******
kx = [];               #Energy
y = [];                #sin^2(shift)
yanalytical = [];      #Analytical sin^2(shift)
erh = [];               #Error high peak
erm = [];               # Error saddle
erl = [];               #Error low peak
quadsize = [];          #Gaussian points


#***** Looping over gaussian quadrantures with different number of points***
for l in range (20, 27, 1):
    scale = l/2; M = l+1   ;
    quadsize.append(l)         
    ko = 0.02     
    
    print ("Computing for npts = " + str(l))
        
    #   Blank Matrices for F, R, V and D matrices or vectors
    k = np.zeros((M),float); x = np.zeros((M),float); w = np.zeros((M),float)
    Finv = np.zeros((M,M),float); F = np.zeros((M,M), float); D = np.zeros((M),float)
    V = np.zeros((M), float); Vvec = np.zeros((l+1,1),float)
    
    gauss(l, 2, 0., scale, k, w) #gauss (npts, job, a, b, x, w)
    
    #Constructing the F & R matrices and solving for phase shift
    for m in range(1,901):         
        k[l] = ko
        for i in range (0, l): 
            D[i]=2/np.pi*w[i]*k[i]*k[i]/(k[i]*k[i]-ko*ko) #D
        D[l] = 0.
        for j in range(0,l): 
            D[l]=D[l]+w[j]*ko*ko/(k[j]*k[j]-ko*ko)
        D[l] = D[l]*(-2./np.pi)
        for i in range(0,l+1): # Set up F matrix and V vector
            for j in range(0,l+1):
                pot = -b*b*lambd*np.sin(b*k[i])*np.sin(b*k[j])/(k[i]*b*k[j]*b)
                F[i][j] = pot*D[j] # Form F Matrix
                
                if i==j: F[i][j] = F[i][j] + 1.
            V[i] = pot                              # V Matrix
        for i in range(0,l+1): Vvec[i][0]= V[i]
        Finv = lina.inv(F)                          # Inverting F Matrix
        R = np.dot(Finv, Vvec)                      # Multiplying Matrix 
        RN0 = R[l][0]
        shift = np.arctan(-RN0*ko)
        sin2 = (np.sin(shift))**2
        num = lambd*b*(np.sin(ko*b)**2)                     #num of analytical 
        den = ko*b - (lambd*b*np.sin(ko*b)*np.cos(ko*b))  #denom of analytical 
        shiftAn =(np.arctan(num/den))                     #analytical solution
        sinAn2 = np.sin(shiftAn)**2
        #Grabbing points from peaks and saddles for error analysis
        if ko*ko == 0.19335084531165903: 
            erh.append(np.log(abs((sinAn2-sin2)/sinAn2)))
        if ko*ko == 0.12639596032002032: 
            erm.append(np.log(abs((sinAn2-sin2)/sinAn2)))
        if ko*ko == 0.021585587247483103: 
            erl.append(np.log(abs((sinAn2-sin2)/sinAn2)))
        yanalytical.append(sinAn2)
        y.append(sin2)                                    
        kx.append(ko*ko)                             ##Energy with h=m=1 
        ko = ko + 0.2*np.pi/1000  
                 
#*************************************************************************
    
# Plotting the energy vs sin^2(shift)
fig, p = plt.subplots(figsize=(5, 3))
p.plot(kx[1:900],yanalytical[1:900], color='b')
p.plot(kx[1:900], y[1:900],color='r')
p.plot(kx[1801:2700], y[1801:2700], color='g')
p.plot(kx[3601:4500], y[3601:4500], color='c')
p.plot(kx[5401:6300], y[5401:6300], color='m')
#   Legend
an = mpatches.Patch(color='b', label='Analytical Solution')
n16 = mpatches.Patch(color='r', label='n = 16');
n18 = mpatches.Patch(color='g', label='n = 18')
n20 = mpatches.Patch(color='c', label='n = 20')
n22 = mpatches.Patch(color='m', label='n = 22')
p.legend(bbox_to_anchor=(1.05, 1), handles=[n16, n18, n20, n22, an], loc = 'upper left')
#   Axis and Title
p.set_title(r'Energy dependence on Phase', fontsize=14, fontweight='bold')
p.set_xlabel('Energy', fontsize=14)
p.set_ylabel(r'$sin^2$ ($\delta$)', fontsize=14)
plt.show()


# % Error Plot
[float(i) for i in quadsize]
[float(i) for i in erl]
errorx= np.asarray(quadsize)
errory = np.asarray(erl)
slope, intercept = np.polyfit(errorx, errory, 1)
print(r'The slope of the error fit is', slope)
fig, er = plt.subplots(figsize=(5, 3))
er.scatter(quadsize ,erh, color='b')
er.scatter(quadsize ,erm, color='r')
er.scatter(quadsize ,erl, color='g')
#   Legend
l = mpatches.Patch(color='g', label='k = 0.021')
m = mpatches.Patch(color='r', label='k = 0.126')
h = mpatches.Patch(color='b', label='k = 0.193')
#   Axis and Title
er.legend(bbox_to_anchor=(1.05, 1), handles=[l, m, h], loc = 'upper left')
er.set_title(r'Error vs Number of Points', fontsize=14, fontweight='bold')
er.set_xlabel('Number of points', fontsize=14)
er.set_ylabel('log(Error)', fontsize=14)

er.plot(np.unique(errorx), np.poly1d(np.polyfit(errorx, errory, 1))(np.unique(errorx)))

plt.show()



print("Done")