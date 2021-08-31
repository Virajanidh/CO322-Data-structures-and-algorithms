#!/usr/bin/python
import time
import matplotlib.pyplot as plt 
import array

def fib_r(x) :
    if (x <= 2):
        return 1
    return fib_r(x-1) + fib_r(x-2)


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


number1=[]
y1=[]	
z=0	
for z in range(0,41):
	start=time.time()  #get start time
	print ("Fib of " + str(z) + " = " + str(fib_r(z)))
	end =time.time()  # get time after finding the fibonacci number
	time_consume=end-start  # get runtime
	print("end:"+str(end))
	print("start:"+str(start))
	y1.append(time_consume)  # store run time to the array
	number1.append(z) # store number to the array
	
  
plt.plot(number1, y1,label ="recursion")

number2=[]
y2=[]	
z2=0	
for z2 in range(0,41):
    start=time.time() #get start time
    print ("Fib of " + str(z2) + " = " + str(fib_i(z2)))
    end =time.time()  # get time after finding the fibonacci number
    time_consume=end-start  # get runtime
    print("end:"+str(end))
    print("start:"+str(start))
    y2.append(time_consume)# store run time to the array
    number2.append(z2) # store number to the array
	
  
plt.plot(number2, y2, label ="iteration") 




plt.xlabel('Problem size') 
plt.ylabel('runtime /s')  
plt.title('Find Fibonacci number --(python)') 
plt.legend() 

plt.show()



