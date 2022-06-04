/*
Michael Pacheco 
mpacheco121@cnm.edu
12/5/2020
intro to programming c language 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sort(char sorted_word[][100], int uwrdcount);
int search_word(char linearr[100]);

int main(int argc, char *argv[]){
	
	//takes input for file and searches for it
	char *file_name;
	file_name = argv[1];
	if(argc<=1){
		printf("\nYou need to provide database file name.\n");
		exit(1);
	}
	printf("The file name is: %s\n", argv[1]);
	
	//file open functions
	FILE *aFile;
	aFile = fopen(file_name, "r");
	if (aFile == NULL)
	{
		printf("File failed to open.");
		exit(1);
	}
	//remove punctuation
	//count lines and non unique words 
//	printf("Counting rows and words.\n");
	int wrdcount =0;
	int ccount=0;
	char c;
	
	for (c = getc(aFile); c != EOF; c = getc(aFile)){ 
		if (c == ' ' || c == '\n')
			wrdcount++;
		ccount++;
	}
	printf("Total Number of Words in the File is: %d\n", wrdcount);
	rewind(aFile);
	//remove punctuation not done...

	//read file into content char array
	int i = 0;
	int j;
	char content[wrdcount][100];
	while(fscanf(aFile, "%s", content[i]) != EOF){
		i++;
	}
	rewind(aFile);
	
	//count and copy over only unique words to sorted_word array
	int uwrdcount=0;
	char sorted_word[uwrdcount][100];
	for (i = 0; i < wrdcount; i++){
		for (j = i + 1; j < wrdcount; j++){
			if (strcmp(content[i], content[j]) == 0)
				break;
		}
		if (j == wrdcount){
		strcpy(sorted_word[uwrdcount],content[i]);
		//sorted_word[uwrdcount] = content[i];
        uwrdcount++;
		}	
	}
	printf("The Total Number of Unique Words in the File is: %d\n", uwrdcount);
	
	
	//call sort function
	sort(sorted_word, uwrdcount);

	//create array for search function with fgets
	char linearr[ccount];
	while(fgets(linearr, ccount, aFile))
	
	//call search function
	search_word(linearr);
	
	//close file
	fclose(aFile);
	
	return 0;
}
int sort(char sorted_word[][100], int uwrdcount){
	
	int i,j;
	int ret;
	char temp[uwrdcount][100];

	//sort function
	for (i = 0; i < uwrdcount; i++){
		for (j = 0; j < (uwrdcount-i); j++){
			ret = strcmp(sorted_word[j],sorted_word[j+1]);
			if (ret>0){
				strcpy(temp[0],sorted_word[j]);
				strcpy(sorted_word[j],sorted_word[j+1]);
				strcpy(sorted_word[j+1],temp[0]);
			} 
		}
	}

	//print sorted words vertically

	for(i=0;i<uwrdcount+1;i++){
		printf("%s\n", sorted_word[i]);
	}
	printf("/*\n");
	printf(" *Here are your output of all words from sorted_word[] in ascending order without\n");
	printf(" *duplication, the content of this portion is subject to the input text file.\n");
	printf("*/\n");	
	return 0;
}
int search_word(char linearr[100]){
	
	int search_term_length;
	char wrdkey[40];
	char einput[10] = "EINPUT";

	//while true repeat search loop 
	while(1){
		//ask user for word key and initialize int needed for search function
		printf("\nPlease enter a word to be searched, \"EINPUT\" to exit: ");
		scanf("%s", wrdkey);
		int i=0;
		/*while(wrdkey[i] !='\0'){
			search_term_length++;
			i++;
		}*/
		int j=0,match=0,nlctr=0,matchctr=0;
		if(strcmp(wrdkey,einput)== 0){
			printf("Bye!\n");
			exit(0);
			//break;
		}
		else{
			//search function start
			for(i=0; linearr[i] != '\0'; i++){
				if(linearr[i] == '\n'){
					nlctr++;
				}
				if (linearr[i] == wrdkey[0]){
					j=1;
					match=1;
					while(wrdkey[j] != '\0'){
						if(wrdkey[j] != linearr[i+j]){
							match =0;
							break;
						}
					j++;	
					}
					//match conditions are met, print out line number, line, and carat pointing to key
					matchctr++;
					if(match){
						//printf("\n%d", nlctr);
						int distfromnl = i;
						//word is found on the first line
						if(nlctr ==0){
							printf("\nLine Number 1\n");
							for(distfromnl=0; distfromnl<100; distfromnl++){
								printf("%c", linearr[distfromnl]);
								if(linearr[distfromnl]=='\n')
									break;
							}
							printf("%*c\n",i+1,'^');
						}
						//word is found anywhere else
						if(nlctr!=0){
							printf("\nLine Number %d\n", nlctr);
							while(distfromnl != '\n'){
								distfromnl--;
							}
							int distc = i-distfromnl;
							while(distfromnl != '\n'){
								printf("%c", linearr[distfromnl]);
								distfromnl++;	
							}
							printf("\n%*c\n",distc,'^');						
						}
					}
				}
			}
		}
	}


	return 0;
}
