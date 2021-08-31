/*
Registration number : E/16/086
name				: A.L.V.H.Dharmathilaka

Part1

In this lab implement a Trie data structure in C to store a dictionary of
English words, and use it to quickly retrieve words for an text auto-complete application.

compile : gcc part1.c -o part1
run		: part1 <text file name>
		example : 	part1 wordfile1000.txt
					part1 wordfile10000.txt
					part1 wordfile70000.txt

------------------------------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>

//intialize a variable to store the number of nodes in oder to calculate the memory space
int count=0;  
//initialize a variable to count number of suggestions for one word
int suggestionCount=0;

//structure of the trie node
typedef struct trienode{
	struct trienode *child[26];  //there are 26 characters in the alphabet 
	bool end; //to double circle the record in tree
	char c ;  //to store the letter
}TrieNode;

//return the index according to the alphabetical order
int getIndex(char ch){
	
	if( ch >= 'a' && ch <= 'z' ){
		return ch-'a'; 
    }
	else if(ch >= 'A' && ch < 'Z'){
		return tolower(ch)-'a';    //take all to lowercase letters
    }
	else{  //if symbols are included
		return -1;
    }
	
}

//creating the node
TrieNode* createNode(){
	
	TrieNode* newNode = (TrieNode*)malloc( sizeof(TrieNode) );  //create storage for new node
	newNode->c = '#';
	newNode->end=false;
	
	
	//initialize the child array with null
	int i=0;
	while(i<26){
		newNode -> child[i] = NULL ;
		i++;
	} 
	
	return newNode;
	
}


//insert words to the array
void insertWord( TrieNode* root , char* word ){
	
	int i;
    TrieNode* newNode2 = root;  ///start from the root
	
    for( i=0;i<strlen(word)-1;i++){
		
		int Index = getIndex(word[i]);  //get the index according to the alphabetical order
		if(Index > -1){
		//store element in empty node
			if(!(newNode2->child[Index])){
			
				newNode2-> child[Index] = createNode();
				newNode2-> child[Index]-> c = word[i];  //store the new letter

			}
			newNode2 = newNode2 ->child[Index];  //go to next node
		}
    }
    newNode2 -> end = true;  //round the node as from root to that node is a complete word
    count ++;  //count the nodes
}


//search a word prefix
TrieNode* searchNodes(TrieNode* root,char* word){
    
    TrieNode* cur_Node = root;  //start from root
	
	//find the word by going to node by node until a null node
    for(int j=0;j<strlen(word);j++){
		
        int Index = getIndex(word[j]);
		if(cur_Node!=NULL){
			cur_Node = cur_Node -> child[Index];
		}
		
    }
    return cur_Node;
}


//print a short list of suggestions
int printSuggetions(TrieNode* sug_Node,char buffer[],int size){
	
    int i;
	
	//if the word exists print it 
    if(sug_Node -> end)
    {
        for(i=0;i<size;i++)
        {
            printf("%c",(buffer[i]));
        }
        printf("\n");
		suggestionCount++;  //increment the count of suggestions
		
    }
	//get matching words
    for(i=0;i<26;i++)
    {
        if(sug_Node->child[i]!=NULL)
        {
            buffer[size] = sug_Node -> child[i] -> c;
			//call again the printSuggetions to print the word
            printSuggetions(sug_Node -> child[i],buffer,size+1);
        }
    }
	
	return suggestionCount;  //return the suggestions count for one word 
}


//main method------------------------------------------------------------------------------------------



int main(int argc, char *argv[]){
	
	//file name must be given as commandline argument
	if(argc!=2){
		printf("run in following format : %s <filename>",argv[0]);
		exit(-1);
	}
    char txt[100];
    
	
	FILE *fp = fopen(argv[1],"r");  //pointer to open the file
	char word[100];
	TrieNode* root;
    if (fp == NULL){  //Error handling in file opening
        printf("File opening failed.Enter a .txt file");
        exit(1);
    }
	else{
    root = createNode();
    root -> c = '/';
	
    clock_t beginInsert = clock(); //measure the time before insertion
    while(1){
		
        fgets(word,100,fp);
        insertWord(root, word  );
		if(feof(fp)) break;
		
    }
    clock_t endInsert = clock();  //measure the time after insertion
	
    double timeSpent = (double)(endInsert-beginInsert) / CLOCKS_PER_SEC;  //get the time in seconds
    printf("Time taken to store the dictionary:  %.6f s\n",timeSpent);
	
    fclose(fp);  //close the file
	}
	
	//print the memory usage to store file data
	printf("Memory space usage: %d Bytes\n------------------------------------\n",sizeof(*(root))*count);
	
	int i=0;
	
	//this loop will terminate only if user terminate it or incorrect prefix is entered.
    while(1)
    {
		
        printf("Enter word: "); //prompt user to enter a world
        scanf("%s",&txt[i]);
		if (!(txt[i] >= 'a' && txt[i] <= 'z') && !(txt[i] >= 'A' && txt[i] <= 'Z')){
			printf("symbols and digits are not allowed ");
			break;
		} 
        char s[100];
        strcpy(s,txt); //returns s with the copied string from txt .
		
		//get the suggestedNode
        TrieNode* sug_Node = searchNodes( root , s);
       
        //if suggestions are found print them else inform it to the user.
		if(sug_Node!=NULL){
			
			//print the suggestions  and measure time to print the suggestions
			printf("\nSuggested Words\n**************\n");
			clock_t beginFind = clock();
			int sug_count=printSuggetions(sug_Node,s,strlen(s));
			clock_t endFind = clock();
		
			double findTime = (double)(endFind-beginFind) / CLOCKS_PER_SEC;
			printf("Time taken to print a list of suggestions for chosen word prefixes :  %.6f s\n",findTime);
			printf("\n");
			printf("Number of suggestions : %d\n ",sug_count);
			sug_count = 0;
			suggestionCount=0;
			
		}
		else{
			printf("No suggestions\n**************\n");
		}
    }
	
    return 0;
	
}