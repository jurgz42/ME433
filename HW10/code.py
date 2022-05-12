from ulab import numpy as np
import time

x = np.linspace(0, 2*np.pi, 1024)
sin1 = np.sin(x*10)
sin2 = np.sin(x)
sin3 = np.sin(x*20)
a = np.zeros(1024)

for i in range(0,len(x)):
    a[i] = sin1[i] + sin2[i] + sin3[i]
    #rint((a[i],))

A = np.fft.fft(a)

for arr in A:
    for val in arr:
        print((val,))
        time.sleep(0.01)
    break
