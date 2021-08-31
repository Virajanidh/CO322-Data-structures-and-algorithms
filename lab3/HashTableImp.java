/*********************************************
 
	* CO322: Data structures and algorithms
 
	* Implementation of the hashTable
 *********************************************/
 
 // three functions are implemented for hash function. To get those methods 
 //follow the instructions in line 51 and 97
 public class HashTableImp implements HashTable{
	 
	private static class Node {
		int value=0;
		String key;
		Node next;  //Pointer to next node in the list;
	}
	
	
	public Node[] table;  		//initialize hash table                            
	                   
   
	public HashTableImp(int buckets) {
		
		if(buckets <= 0){
			throw new IllegalArgumentException("Only Positive Numbers and no Letters for table size");
		}
      	table = new Node[buckets];
	}
   

   
    //calculate the hash code
    //Modular hashing works for long keys such as strings 
    //we simply treat them as huge integers. 
    //below computes a modular hash function for a String s, where R is a small prime integer (Java uses 31)
    //hash = ( hash + s.charAt(i)) % M
    private int hashfun(String key) {
	    int hash = 0;
	    for (int i = 0; i < key.length(); i++){
		   hash = ( hash + ((key.charAt(i)))*(int)Math.pow(128,(key.length()-1-i)))%(table.length);		   
	    }	   
	    return (hash%(table.length));   
    }
   
	public void insert(String key) {  
		//if key is null can not store.check it 
		assert key != null : "The key must not null";
		Node node1=null;
    
		//First calculate Hash code for the key and get bucket number
		/************************************************************
		change here to get a different Hash function
		
		int bucketNo = hashfun(key); // modified method
		int bucketNo = divFun(key);  // for division method
		int bucketNo = multiFun(key,0.618033);// for multiplication method
		
		************************************************************/
		
		int bucketNo = hashfun(key); 
		//int bucketNo = divFun(key); 
		//int bucketNo = multiFun(key,0.618033); 
      
		 //Traversing the linked list
		try{
			node1= table[bucketNo];
		}catch(ArrayIndexOutOfBoundsException e) {
			System.out.println("Error in finding Bucket Number");
		}
        
		//check whether the given bucket number is already exists.
		//if exists no need to get new bucket only increase the value by 1
		while (node1!= null){

			if (node1.key.equals(key)){
				node1.value++;
				break;   
			}
			node1 = node1.next;  //point to next node
		}
      
		//if given bucket Number does not exists create new node
		if(node1==null) {
			Node newNode = new Node();
			newNode.key  = key;
			newNode.value++;  //initialy value is defined as 0.So increase by 1
			newNode.next    = table[bucketNo];
			table[bucketNo] = newNode;
			
		}
	}

//when user prompt a key string, search it inside the buckets
//if it exists return value else return 0
	public int search(String key) { 

		/************************************************************
		
		change here to get a different Hash function
		
		int bucketNo = hashfun(key); // modified method
		int bucketNo = divFun(key);  // for division method
		int bucketNo = multiFun(key,0.618033);// for multiplication method
		
		************************************************************/	
		int bucketNo = hashfun(key);
		//int bucketNo = divFun(key); 
		//int bucketNo = multiFun(key,0.618033);
		Node node2 = table[bucketNo];
		while (node2 != null){                 
			if (node2.key.equals(key))return node2.value;	//return value as Bucket number  exists
			node2 = node2.next;
		}
		return 0;  
    }

 
   
//details about the hash table is in this method.
//this includes with total nodes ,average number of nodes in a bucket and deviation
	public void getBucketSize(int tableSize)  {
		int h=0,total = 0,j=0;
		
		while(j<tableSize){ 		
			int count=0;
			Node node3 = table[j];
			while(node3 != null) {		 
				node3 = node3.next;
				count++;
			}
			j++;
			h=(int) Math.pow(count,2) +h;
			System.out.println("index : "+(j)+"--> "+count+"  nodes");
			//System.out.println(count);
			total+=count;
	    }	   
		double avg = (double)(total/(double)tableSize);
		double var = (double)(h/tableSize) - (double)(Math.pow(avg, 2));
		System.out.println("Total entries :"+total+"\nAverage number of entries in a bucket : "+avg);
		System.out.println("Standard Deviation : "+Math.sqrt(var));
	}
	
	//get ascii value of a String
	public int getASCII(String word){
		int  sum =0;
		for(int j=0;j< word.length();j++){
			sum+= ((int)word.charAt(j))*(Math.pow(128,(word.length()-1-j)));
		}
		return sum;
	}
	//Division method
	public int divFun(String s){
		int key = getASCII(s);
		return(key%table.length);
		
	}
	//multiplication method
	//h(k)=n( K.A mod 1)
	public int multiFun(String s, double valueA){
		double k = valueA;
		int key = getASCII(s);
		return (int) (table.length * (k * key % 1));
	}  
	
}
 
 
