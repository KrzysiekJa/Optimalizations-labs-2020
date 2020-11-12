import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('fivethirtyeight')



file1 = pd.read_csv("tout.csv", sep=';', decimal=',') # for files
file2 = pd.read_csv("yout.csv", sep=';', decimal=',')

x = file1.iloc[:,0]
y1, y2 = file2.iloc[:,0], file2.iloc[:,1]

plt.plot(x, y1, linewidth=1, label='Predkość [m/s]') #plotting
plt.plot(x, y2, linewidth=1, label='Przyspieszenie [m2/s]')
plt.xlabel("Czas [s]")
plt.legend(loc='best')

plt.show()