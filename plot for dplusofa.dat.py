# -*- coding: utf-8 -*-
"""
Created on Thu Jul 28 02:39:30 2016

@author: sohom
"""
import numpy as np
import matplotlib.pyplot as plt

f='dplusofa.dat'

a=np.genfromtxt(f,delimiter=' ',usecols=(1))
dplus=np.genfromtxt(f,delimiter=' ',usecols=(2))

plt.plot(a,dplus)
plt.show()