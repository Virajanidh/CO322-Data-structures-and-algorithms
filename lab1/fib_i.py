
import timeit
import matplotlib.pyplot as plt 
import numpy as np 

# find fibonacci number using iterations

def fib_i(x) :
    a = 1
    b = 1
    fib = 1
    i = 2
    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1
        
    return fib
	

	
number=np.array([0])
y=np.array([0])		
for z in range(0,41):
    start=timeit.default_timer() #get start time
    print ("Fib of " + str(z) + " = " + str(fib_i(z)))
    end =timeit.default_timer()  # get time after finding the fibonacci number
    time_consume=end-start  # get runtime
    print("end:"+str(end))
    print("start:"+str(start))
    y=np.append(y,time_consume)# store run time to the array
    number=np.append(number,z) # store number to the array
	
  
plt.plot(number, y) 
plt.xlabel('Problem size') 
plt.ylabel('runtime /s') 
plt.title(' Find Fibonacci number --iteration method (python)') 
  

plt.show()



print("x:"+str(number))
print("\ny:"+str(y))
