 # values get from java code are plot in a graph using this python code
import matplotlib.pyplot as plt 
import array 

#y1 array has values for iteration function and y2 array has values for recursive function
y1=[3000,700,500,700,700,600,700,700,600,700,700,700,700,700,700,700,800,700,800,800,800,800,900,800,28200,1200,7800,15200,900,800,800,900,900,900,1000,1000,900,17400,900,1000,1000]
y2=[5700,300,300,14900,500,600,800,1000,1500,3900,9100,34200,9200,1700,2400,17800,6800,14600,22400,21800,31000,47500,110300,94500,92900,228200,240300,387200,642000,1033500,1801300,2816200,5070300,7346900,11538300,18778800,32526600,49502200,80955300,129202900,210818000]

x1=[]
x2=[]
for z2 in range(0,41):
	x1.append(z2)
	x2.append(z2)

plt.plot(x2, y2,label ="recursion")
plt.plot(x1, y1, label ="iteration") 
plt.xlabel('Problem size') 
plt.ylabel('runtime /ns') 
plt.title(' Find Fibonacci number --(Java)') 
plt.legend() 
  

plt.show()

