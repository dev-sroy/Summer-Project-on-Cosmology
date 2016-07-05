# -*- coding: utf-8 -*-
"""
Created on Mon Jul  4 19:37:48 2016

@author: sohom
"""

import fftw3
import numpy as np
from scipy.constants import pi
from scipy import signal
import matplotlib.pyplot as plt
T_start = -10     #Beginning Time
T_end = 10      #Ending time
T=T_end-T_start    #Total time
num = 1000       #Number of samples   
inputa=np.zeros(num,dtype=complex)
outputa=np.zeros(num,dtype=complex)
timea =np.linspace(T_start,T_end,num)   #Time domain
sa=np.linspace(0,T,num) #Samples
freqa = 2*pi*sa/T  #Frequency domain
c=0
mean=5
stdev=0.010
'''
for i in list:
    #elt=np.exp(-(i-mean)**2/(2*stdev**2))
    elt=np.sin(i)
    inputa[c]+=elt  
    c+=1
'''
inputa = 2*pi*np.sin(timea)
fft=fftw3.Plan(inputa, outputa, direction='forward', flags=['measure'])
#ifft=fftw3.Plan(outputa, inputa, direction='backward', flags=['measure'])

fftw3.execute(fft)
plt.plot(freqa,abs(outputa))
plt.show()