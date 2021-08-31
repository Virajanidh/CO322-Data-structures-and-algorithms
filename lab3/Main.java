import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.lang.*;

public class Main extends HashTableImp {
	
	public Main(int tableSize){
		super(tableSize);
	}
	
	public static void errorMessage(){
		System.out.println("usage:\n java Main (tablesize) (txt file name)");
		System.out.println("example: java Main 30 sample-text1.txt ");
	}
	
    public static void main(String[] args) throws IOException {
		
		
		
		//try{
			int tableSize = Integer.parseInt(args[0]);  // (N)the number ofbuckets. (size of the table)
		//}
		//catch(NumberFormatException e){
			//System.out.println("table size must be a Integer");
		//}
		Main m = new Main(tableSize); 
		
		String s= args[1];   //name of the txt file
        // Open this file.
		try{
			BufferedReader reader = new BufferedReader(new FileReader(s));

			// Read lines from file.
			while (true) {
				String string = reader.readLine();
				if (string == null) {
					break;
				}
				// get only words.

				String[] parts = (string.split("\\W+"));
				
				for (String part : parts) {
					
					m.insert(part.toLowerCase());
				}
				
			}

			reader.close();
		}
		catch(FileNotFoundException e){
			System.out.println("File not found");
			errorMessage();
			System.exit(0);
		}
		catch(IOException e){
			System.out.println("File reading failed");
			errorMessage();
			System.exit(0);
		}
		
		//search key
		Scanner sc =new Scanner(System.in);
		m.getBucketSize(tableSize);
		
				
						
		String key;
		do {
		//get a key from user to search in the table
			System.out.println("Enter the key to search the bucket or enter 'quit' to stop: ");
			key = sc.nextLine();
			if (!key.isEmpty()){  //if key is empty no search
				if(isString(key)){
					System.out.println("Value: "+m.search(key));
				}
				else{
					System.out.println("Enter a word as key or enter 'quit' to stop5");
				}
			}
			else{
				System.out.println("Enter a word or enter 'quit' to exit");
			}
		}
		while(!key.equals("quit"));
	
		
		
    }
	
	//method to check whether the key entered by user is a word or numeric value
	public static boolean isString(String text) {
		try {
			Integer.parseInt(text);
			return false;
		} 
		catch (Exception e) {
			return true;
		}
	}
}