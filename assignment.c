
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
//structure used to access the twitter options 
struct tweet
{
	int id;
	char  created_at[51];
	char text[141];
	char user[21];
};
//alias definition for structure
typedef struct tweet Tweet;
int Create(Tweet *ptrtweet, char user[50], int i);
void Display(const Tweet u[], int i);
void Save(const Tweet u[], int i, const char *filename);
int Load(Tweet *ptrload, const char *filename);
void Search(Tweet *ptrtweet, char word[], int i);
//this functions gives access to simple twitter options and access all the function accordingly
int main(void)
{
	Tweet u[141];	//to store the entered data in the structure datatype
	int done = 0;	//exit condition
	int option, i=0;	//option for entered choice and i as a counter
	char user[50];	//stores the user name
	u[i].id = 1000;	//first id to be set and then increases by  
	char filename[50];	//stores the entered filename
	char word[20];	//stores the entered word to be searched
	int k;	
	printf("Welcome to simple twitter\n");
	printf("-------------------------\n");
	printf("Enter the  user name:");	//prompts the user to enter username
	scanf("%[^\n]s",user);			//scans the name
	printf("Welcome %s, let's start tweeting\n", user);
	do	//this loop runs till the exit condition doesn't turns to be 1
	{
		printf("1. Create a new tweet\n2. Search tweets\n3. Display tweets\n4. Save tweets to file\n5. Load tweets from file\n6. Exit\n");	//interactive menu
		printf("Enter the choice: ");	//asks the user to enter choice
		scanf("%d", &option);		
		switch (option)	//switch condition to go to case according to the choice and get the output
		{
			case 1:	k = Create(&u[i], user, i);	//allows the user to create a tweet	
					i++;			
					(u[i].id)=((u[i-1].id)+1);	//increases the tweet id by 1
				if(k==1)
					i--;
				break;
			case 2: printf("Enter the word you want to search:");	//asks the user to enter the word to be found
				scanf("%s",word);
				Search(u,word,i);	//access the function to search the word
				break;	
			case 3: Display(u, i);	//displays the entered or loaded tweets
				break;
			case 4:printf("Enter a file name:");	//prompts the user to enter a filename
			       scanf("%s", filename);
			       Save(u,i,filename);		//saves the tweets in the file
			       printf("%d tweet(s) saved in file %s\n", i, filename);
			       break;
			case 5:printf("Please enter a filename:");	//asks the user to enter the filename from which the teets are to be loaded 
			       scanf("%s", filename);
			       i =  Load(u,filename);			//loads the tweet and gives back the number of tweets loaded
			       (u[i].id)=((u[i-1].id)+1);		//generates the id in continuation
			       break;
			case 6: done = 1;				//exit condition
		}
	}while(done != 1);
	printf("Good Byee!!\n");
} 
/*This function creats new tweets 
Input: takes the pointer pointing to the arrya and the username
Output: the entered tweet with id, time and the username
*/
int Create(Tweet *ptrtweet, char user[50], int i)
{
	struct tm *local;	//for UTC time
	time_t t;
	t = time(NULL);
	local = gmtime(&t);
	if(i<5)
	{
		printf("\nEnter the text: ");	//prompts the user to enter the tweet text
		getchar();			//gets the character
		scanf("%[^\n]s",ptrtweet-> text);
		sprintf(ptrtweet->created_at,"%s",asctime(localtime(&t)));	//prints the generated time int the structure variable
		sprintf(ptrtweet->user,"%s",user);				//stores the username into the structure variable
		printf("\nNew tweet created:");	
		printf("\nid:%d",ptrtweet->id);
		printf("\t\tcreated at: %s by %s\n", ptrtweet->created_at/*asctime(local)*/, ptrtweet->user);	//prints the tweet
		printf("%s\n", ptrtweet->text);
		return 0;
	}
	else
	{
		printf("Array Full!!\n");
		return 1;
	}
}
/*Display the created and loaded tweets
Input: Takes the array of structure datatype as well as the number of tweets generated
Output: It prints all the created tweets
*/
void Display(const Tweet u[], int i)
{
	int k;	//used as a counter
	printf("Displaying all %d tweets:\n", i);
	for(k=0;k<i;k++)	//used to print all the created tweets
	{
		printf("id:%d\tcreated at:%s by %s\n%s\n", u[k].id,u[k].created_at,u[k].user,u[k].text);
	}
}
/*This program saves the created tweets into a file
Input:it takes the array as well as the filename
Output: it saves the creates into a file
*/
void Save(const Tweet u[], int i, const char *filename)
{
	FILE *fp;	//file pointer
	int k;		//used as a counter
	fp = fopen(filename,"w");	//opens the file for writing
	if(fp==NULL)	//error condition
	{
		printf("error");
	}
	for(k=0;k<i;k++)	//prints as many times as the loop runs
	{
		fprintf(fp,"%d\n%s%s\n%s\n", u[k].id,u[k].created_at,u[k].user,u[k].text);
	}
}
/*This function loads the tweets into an array from the file 
Input: It takes the pointer to the array and the filename 
Output: It loads the content of the file into the array
*/
int Load(Tweet *ptrload,const char *filename)
{
	FILE *fn;	//file pointer
	fn = fopen(filename,"r");	//opens the file for reading
	int k=0;	//used as a counter
	char text[20];	//temperory variable to store the scanned id 
	if(fn!=NULL)	//condition if the fill is empty
	{
		while(!feof(fn))	//runs till the end of file
		{
			fgets(text,sizeof(text),fn);	//scans the id and store it in text
			(ptrload+k)->id = atoi(text);	//change the text to the number and store it in arrsy
			fgets((ptrload+k)->created_at,sizeof((ptrload+k)->created_at),fn);	//scans the rest of the data and stores it in the array
			fgets((ptrload+k)->user,sizeof((ptrload+k)->user),fn);
			fgets((ptrload+k)->text,sizeof((ptrload+k)->text),fn);
			++k;
		}
	         printf("%d tweet(s) loaded from file %s\n", (k-1), filename);
		fclose(fn);	//closes the file
	}
	return (k-1);	//returns the number of tweets loaded
}
/*This function goes through all the created and loaded tweets and displays all the tweets containing the entered word
Input: the pointer to the array , the word to be searched and the maximum number of tweets in the array
Output: The tweets containing that word
*/
void Search(Tweet *ptrtweet, char word[], int i)
{
	char *temp;	//temperory variable to store the tweet containing that word
	int k,j=0;	//counters
	for(k=0;k<(i);k++)	//goes through all tweets
	{	
		temp = strstr((ptrtweet+k)->text,word);	//finds the word in the tweets if its there
		if(temp!=NULL)
		{
			printf("Found Match:\n");
			j++;
			printf("id:%d\tCreated at:%s by %s\n%s\n",(ptrtweet+k)->id,(ptrtweet+k)->created_at,(ptrtweet+k)->user,(ptrtweet+k)->text);	//prints that tweet
		}
	}
	printf("Found %d tweets matching the criteria!\n",j);
}
