import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.TimeUnit;
class task4 {
    static int [][] cost = {{0, 3, 12, 23, 41, 6, 211, 4}, // cost from 0 
			    {0, 0,  2,  4, 34, 4, 12, 43}, // cost from 1 
			    {0, 0,  0,  12, 3, 5, 2,  4}, // cost from 2 
			    {0, 0,  0,  0, 12, 4, 32, 3}, // cost from 3 
			    {0, 0,  0,  0,  0, 4, 3, 12},  // cost from 4
			    {0, 0,  0,  0,  0, 0, 3, 234},  // cost from 5
			    {0, 0,  0,  0,  0, 0, 0, 12},  // cost from 6
			    {0, 0,  0,  0,  0, 0, 0, 0}  // cost from 7 
    };
    static int iMax = 7;
    static int jMax = 7;

    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8;
    static int comp =0;  //variable to count complexity
    
    static Map<String,Integer> costMap = null;    //initialize hashmap for store calculated cost values.

	//key of the hashmap is created with i+j value. and key is turned to string
    public static String indexToKey(int i, int j) {	
		return Integer.toString(i) + Integer.toString(j);
    }

	//initialize the costs by putting cost of nearby stations
    public static Map<String, Integer> initHashMap() {
		Map<String,Integer> costs = new HashMap<String, Integer>();
		for(int i=0; i < jMax-1; i++) {
			String s = indexToKey(i, i+1);  //get the key
			costs.put(s, cost[i][i+1]);  //initialy put cost of nearby stations
		}
		return costs; 
    }
    
    public static int minCostDynamicPro(int i, int j) {
		
		comp++;  //increament complexity count in each function call
		
		//in the first time running initial hashmap is loaded to costMap
		if(costMap == null) costMap = initHashMap(); 
		
		//If it is not the first time function runs then check availability of cost calculation in costMap	
		if(costMap.containsKey(indexToKey(i,j))) 	
		return costMap.get(indexToKey(i,j)); //if available return value using key and end the fucntion call
	

		int min = cost[i][j];
		for(int k = i+1; k < j; k++) {
			int tmp = minCostDynamicPro(i, k) + minCostDynamicPro(k, j);  // do recursive calls to get the cost
			if(min > tmp) min = tmp; 	    
		}
		costMap.put(indexToKey(i,j), min);   //put cost to costMap for future use
		return min;
    }
	
    
    public static void main(String [] args) {
		
		
		//get the cost values from 1 to 7
		for(int l=1; l<jMax; l++) {
			comp = 0;	
			long startTime = System.nanoTime(); //get the start time
			int r = minCostDynamicPro(0,l);  //call the recursive method to get the value
			long endTime = System.nanoTime();  //get the end time
			long duration = (endTime - startTime);  // execution time in nano seconds
			System.out.println("Complexity=" + comp	+ "	cost= "+r+"	runtime:"+duration);
		}
	

    }
}
    