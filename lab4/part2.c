/*
Registration number : E/16/086
name				: A.L.V.H.Dharmathilaka

Part2

In this lab implement a Trie data structure in C to store a dictionary of
English words, and use it to quickly retrieve words for an text auto-complete application.
for a efficient search and reduce memory usage Prefix tree is implemented. 

compile : gcc part2.c -o part2
run		: part2 <text file name>
		example : 	part2 wordfile1000.txt
					part2 wordfile10000.txt
					part2 wordfile70000.txt

---------------------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

int count=0;  //count the total nodes
int suggestionCount=0;  //count the Number of suggestions for a user prompt word

typedef struct linkedStr{
	
	char letter;
	struct linkedStr *next;
	
}linkedStr;

//structure of the node
typedef struct trienode{
	struct trienode *child[26];  //there are 26 characters in the alphabet 
	bool end; //to mark the end of the word
	linkedStr* linkedStr ;  //in part1 we only add a letter but now it is a word so add it to a node
}TrieNode;

//return the index according to the alphabetical order  (ASCII value)
int getIndex(char ch){
	
	if( ch >= 'a' && ch <= 'z' ){
		return ch-'a'; 
    }
	else if(ch >= 'A' && ch < 'Z'){
		return tolower(ch)-'a';    //take all to lowercase letters
    }
	else{  //if symbols or anr invalid characters are included
		return -1;
    }
	
	
}


//store letters in the linked list
linkedStr* createNewString( char newL ){
	
    linkedStr* newStr = (linkedStr*) malloc(sizeof(linkedStr));
    newStr -> letter = newL;
    newStr -> next = NULL;
	
    return newStr;
}



//creating the node
TrieNode* createNode(){
	
	TrieNode* newNode = (TrieNode*)malloc( sizeof(TrieNode) );  //create storage for new node
	newNode -> linkedStr = NULL;
	newNode -> end = false;   // when creatin a node no word so no need to double round the node in the tree structure
	
	
	//initialize the child array with null
	int i=0;
	while(i<26){
		newNode -> child[i] = NULL ;
		i++;
	} 
	
	return newNode;
	
}


//include the word instead of letter
linkedStr* linkedStrAppend(int inital , int end , char* str ){
	
    linkedStr* current = createNewString(str[inital]);
    linkedStr* newString = NULL;
    linkedStr* string = current;

	//add the remaining part of the word to the node
    for(int i=(inital+1) ; i<end ; i++){
		
        newString = createNewString(str[i]);
        current->next = newString;
        current = current->next;
    }
	
    current = NULL;
	
    return string;
}

/*-------------------------------------------------------------------------------------------
when inserting a node start from root and traverse through the chain 
if the non matching node  found get a new child from their. 
Unlike binary search tree, many child nodes can be added for one node 
-------------------------------------------------------------------------------------------*/
void insertWord(TrieNode* root,char* word){
    
    TrieNode* currentNode = root;
    TrieNode* newNode = NULL;
	TrieNode* pre_Node = NULL;
    linkedStr* cur_Letter;
	linkedStr* pre_Letter = NULL;
    cur_Letter = currentNode->linkedStr;
	
	int i=0;
	
    while(i<strlen(word)){
		
    	int index = getIndex(word[i]);
		
        if(index > -1 ){
			
    	    if(cur_Letter != NULL) {
				//if letters are not equal create a node
				if (cur_Letter->letter != word[i]){
					
					newNode = createNode();
					
					newNode -> linkedStr = linkedStrAppend(i,(strlen(word)-1),word);
					//mark it as complete word end. from root to this point there is a meaningfull word				
                    newNode -> end = true;
    
					linkedStr* newString = pre_Letter->next;
					pre_Letter->next = NULL;
					TrieNode* node2 = createNode();
	
					int index_1 = getIndex(newString->letter);
					node2->linkedStr = currentNode->linkedStr;
					currentNode->linkedStr = newString;
					node2->child[index_1] = currentNode;

					int index_2 = getIndex(node2->linkedStr->letter);
					pre_Node->child[index_2] = node2;
					
					currentNode =node2;
					
					currentNode -> child[index] = newNode;
					
					break;
				}
				else{  //if current letters are equal keep on traversal
                    pre_Letter = cur_Letter;
					cur_Letter = cur_Letter->next;
				}	
				
    	    }
			else{
				 //add a new node to the prefix tree when the null point found
				if(currentNode->child[index] == NULL){
					 
					count++;
					newNode = createNode();
					newNode -> linkedStr = linkedStrAppend(i,(strlen(word)-1),word);
                    newNode -> end = true;
					
					currentNode->child[index] = newNode;
					
					break;
					
				}
				else{
					//if it is not null then it is not the end so keep on traversal
                    pre_Node = currentNode;
                    currentNode = currentNode->child[index];
                    pre_Letter = currentNode->linkedStr;
					cur_Letter = currentNode->linkedStr->next;
					
				}
				
    	    }
        }
		
    	i++;
    }
}



//search the word in the dictionary.
TrieNode* searchNodes(TrieNode* root,char* word){
    
    
    TrieNode* currentNode = root;  //start from the root
    linkedStr* currentLetter = currentNode->linkedStr;  //get the curent letter at trieNode
	int k=1;
	int i=0;
	int lastIndex = strlen(word);  //last index number will be the length of the word
	
    for( i=0 ; i<lastIndex ; i++ ){
		
    	int Index = getIndex(word[i]);
		//if we search in the correct branch the current letter will equal to
		//the corresponding letter in word.Then check the next letter
		//if not go back 
    	if( k && currentLetter != NULL ){
            
			currentLetter = currentLetter->next;
			
    	}
        else if( currentLetter == NULL && k ){  
    	    
			currentNode = currentNode->child[Index];
            if(currentNode != NULL){
    	       currentLetter = currentNode->linkedStr->next;
            }
            else{
               k=0;
            }
			
    	}
        
    }
	
	//to give suggestions after finding the unique branch 
	//that has the word give, its remaining branches and leaves as suggestions
    while(currentLetter != NULL){
    	word[lastIndex] = currentLetter->letter;
    	currentLetter = currentLetter->next;
    	lastIndex++;
    }
    word[lastIndex] = '\0';  //mark the end

    return currentNode;
}


//print a short list of suggestions

int printSuggetions(TrieNode* suggestedNode,int size,char buffer[]){
    
   TrieNode* currentNode = suggestedNode;
    int newSize;

	//if the word exists print it 
    if( currentNode->end ){
		
        for ( int j=0 ; j<size ; j++){
			
            printf("%c",buffer[j]);
        }
        printf("\n");
		suggestionCount++;
    }

    //search for the words that has matching prefix
	int i=0;
	while(i<26){
		
        if(currentNode->child[i]!=NULL){
			
			linkedStr* cur_Letter = currentNode -> child[i] -> linkedStr;
			int size2 =size;
			char* buffer2 =buffer;
			
			while (cur_Letter != NULL){
		
				buffer2[size2] = cur_Letter->letter;
				cur_Letter = cur_Letter->next;
				size2++;
			}
	
			buffer2[size2] = '\0';
			newSize = size2-1;
            printSuggetions( (currentNode->child[i]) , (newSize+1),buffer);
        }
		i++;
    }
	
	return suggestionCount;
}


//main method
int main(int argc, char *argv[]){
	
	int i=0;
	char txt[100];
	char word[100];
	
	//file name must be given as commandline argument
	if(argc!=2){
		printf("run in following format : %s <filename>\n",argv[0]);
		exit(-1);
	}
   
    //file reading and insert values
   
    FILE *fp = fopen(argv[1],"r");  //pointer to open the file
	
    if (fp == NULL){  //Error handling in file opening
        printf("File opening failed. Enter a text file\n");
        exit(1);
    }
	
	//root is a empty node in  tree
    TrieNode* root = createNode(); 
	
    clock_t beginInsert = clock(); //measure the time before insertion
	
	//insert words from the file.loop will end when the file is end
    while(1){
		
        fgets(word,100,fp);
        insertWord(root, word  );
		if(feof(fp)) break;
		
    }
    clock_t endInsert = clock(); //measure the time after insertion
	
    double timeSpent = (double)(endInsert-beginInsert) / CLOCKS_PER_SEC;
    printf("Time taken to store the dictionary: %f s\n",timeSpent);  //get the time in seconds
	
    fclose(fp);  //close the file
	
	//print the memory usage to store file data
	printf("Memory space usage: %d Bytes\n------------------------------------\n",sizeof(*(root))*count);
	
	
	//user prompt to enter the word
	
    while(1){
        printf("Enter word: ");
        scanf("%s",&txt[i]);
		
		if (!(txt[i] >= 'a' && txt[i] <= 'z') && !(txt[i] >= 'A' && txt[i] <= 'Z')){
		
			printf("symbols and digits are not allowed ");
			break;
			
		} 
		
        char s[100];
        strcpy(s,txt); //returns s with the copied string from txt .
		
		//get the suggestedNode
        TrieNode* sug_Node = searchNodes( root , s);
       
        //if suggestions are found print them else inform it.
		if(sug_Node!=NULL){
			
			//print the suggestions and measure time to print the suggestions
			printf("\nSuggested Words\n**************************\n");
			clock_t beginFind = clock();
			int sug_count = printSuggetions(sug_Node,strlen(s),s);
			clock_t endFind = clock();
		
			double findTime = (double)(endFind-beginFind) / CLOCKS_PER_SEC;
			printf("\nTime taken to print a list of suggestions for chosen word prefixes : %f s\n",findTime);
			printf("\n");
			printf("Number of suggestions : %d\n\n ",sug_count);
			sug_count = 0;
			suggestionCount=0;
		}
		else{
			printf("No suggestions\n**************************\n");
		}
    }
    return 0;
}

