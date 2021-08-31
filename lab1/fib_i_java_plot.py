# runtime values get from java iteration function is plotted seperatly
import matplotlib.pyplot as plt 
import array 

y1=[3000,700,500,700,700,600,700,700,600,700,700,700,700,700,700,700,800,700,800,800,800,800,900,800,28200,1200,7800,15200,900,800,800,900,900,900,1000,1000,900,17400,900,1000,1000]

x1=[]
for z2 in range(0,41):
	x1.append(z2)
	
plt.plot(x1, y1) 
plt.xlabel('Problem size') 
plt.ylabel('runtime /ns') 
plt.title(' Find Fibonacci number --iteration method(Java)')  
  

plt.show()
