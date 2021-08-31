import java.text.ParseException;
import java.util.concurrent.TimeUnit;
 
public class Fib_java 
{
	public static void main(String[] args) throws ParseException 
	{
		System.out.println("Find FIbonacci numbers --iteration method");
		for(int i=0;i<41;i++){
			long startTime = System.nanoTime(); //get the start time
			fib_i(i); //Measure execution time for iteration method
			long endTime = System.nanoTime();  //get the end time
			long duration = (endTime - startTime);  // execution time in nano seconds
			System.out.print(duration+",");
		}
	
		System.out.println("\nFind FIbonacci numbers --recursive method");
		for(int i=0;i<41;i++){
			long startTime = System.nanoTime();  //get the start time
			fib_r(i); //Measure execution time for recursive method
			long endTime = System.nanoTime();  //get the end time
			long duration = (endTime - startTime);  // execution time in nano seconds
			System.out.print(duration+",");
		}
     
	}
	
	//recursive method
	public static int fib_r(int x) {
		if(x <= 2) return 1;
		return fib_r(x-1) + fib_r(x-2);
    }

	//iteration method
    public static int fib_i(int x) {
		int a=1, b=1, fib=1, i=2;
		while(i<x) {
			fib = a + b;
			a = b;
			b = fib;
			i+=1;
		}
		return fib;
    }
 
} 