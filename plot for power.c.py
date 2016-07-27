# -*- coding: utf-8 -*-
"""
Created on Wed Jul  6 11:29:43 2016

@author: sohom
"""

import numpy as np
import matplotlib.pyplot as plt
bias_abs=[]
crosspower_abs=[]
bias_new1=[]
bias_new2=[]
crosscoeff_abs=[]
f='3dpower_matter_dm_037.dat'
crosspower = np.genfromtxt(f,delimiter=' ', usecols=(4,5))
crosspower=zip(*crosspower)
crosscoeff = np.genfromtxt(f,delimiter=' ',usecols=(6,7))
crosscoeff=zip(*crosscoeff)
for i in range(len(crosscoeff[0])):
    crosscoeff_abs.append(np.sqrt(crosscoeff[0][i]**2+crosscoeff[1][i]**2))
bias = np.genfromtxt(f, delimiter=' ', usecols=(8,9))
bias = zip(*bias)
powerspec_1 = np.genfromtxt(f,delimiter=' ',usecols=(2))
powerspec_2 = np.genfromtxt(f,delimiter=' ',usecols=(3))
w_scale = np.genfromtxt(f,delimiter=' ',usecols=(0))
w_scalekms=np.genfromtxt(f,delimiter=' ',usecols=(1))
for i in range(len(crosspower[0])):
    crosspower_abs.append(np.sqrt(crosspower[0][i]**2+crosspower[1][i]**2))

print len(bias[0])
for i in range(len(bias[0])):
    bias_abs.append(np.sqrt(bias[0][i]**2 + bias[1][i]**2))

for i in range(len(crosspower_abs)):
    bias_new1.append(crosspower_abs[i]/powerspec_1[i])
    bias_new2.append(powerspec_2[i]/powerspec_2[i])

#plt.plot(bias_new1,bias_new2)
plt.plot(w_scalekms,powerspec_1)
plt.plot(w_scalekms,powerspec_2)
plt.show()