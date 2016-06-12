import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from scipy.integrate import quad

x_init=np.linspace(0.1,0.5,80)    #Array for values of omega_m
y_init=np.linspace(0.5,0.9,80)    #Array for values of omega_lambda
x=[]
y=[]
z=[]
plot=[]

fig=plt.figure()
ax=fig.add_subplot(111,projection='3d')

for i in x_init:
    for j in y_init:
        intg,err=quad(lambda a:(1/(np.sqrt((i/a)+a**2*j))),0,1)
        age=intg/70
        x.append(i)
        y.append(j)
        z.append(age)


ax.scatter(x,y,z)
plt.show()

