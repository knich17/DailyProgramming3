#include <stdio.h>	//fscan, printf etc
#include <time.h>	//for random seed
#include <stdlib.h>
#include <string.h>	//strcpy etc
#include <math.h> 	//floor
#include <ctype.h> 	//toupper

int numWords;
int wordLength;

int inWordlist(char wordlist[numWords][wordLength+1], char* word);
void convertStringUpper(char* str);

int main() {
	srand(time(NULL));

	//Print Welcome Message
	printf("\n------------------------------------------\n   Welcome to the Fallout Hacking Game!\n------------------------------------------\n");

	//Main game loop
	int keepPlaying = 1;
	while(keepPlaying) {

		//Ask for difficulty
		int difficulty;
		printf("\nDifficulty (1-5)? ");
		scanf("%d", &difficulty);
		if(difficulty < 1 || difficulty > 5) {
			perror("Bad Difficulty");
			return 1;
		}

		//1=(5,6), 2=(7,8), 3=(9,10), 4=(11,12), 5=(13,14,15)
		numWords = 5+2*(difficulty-1)+(rand()%2)+(floor(difficulty/5)*(rand()%2));
		//1=(4,5), 2=(6,7), 3=(8,9), 4=(10,11), 5=(12,13,14,15)
		wordLength= 4+2*(difficulty-1)+(rand()%2)+(floor(difficulty/5)*(rand()%4));

		//Gather words
		FILE *ptr_file;
		char buf[1000];
		char words[numWords][wordLength+1];

		ptr_file =fopen("enable1.txt","r");
		if (!ptr_file) {
			perror("Dictionary not found");
			return 1;
		}

		printf("\n");
		for (int i = 0; i < numWords; i++) {	//for each needed word
			memset(&buf, 0, sizeof(buf));
			strcpy(words[i], "");
			while(strlen(words[i]) <= 0) {		//while a word hasn't been found
				while(fgets(buf,1000, ptr_file)!=NULL) {	//while we haven't reached the end of the file
					//copy word into wordlist if it's correct length, randomly chosen, and has not been chosen before
					if (strlen(buf) == wordLength+2 && rand() % 20000 <= 1) {	

						if(!inWordlist(words, buf)) {
							strcpy(words[i], buf);
							words[i][wordLength] = 0; //remove trailing line end
							break;
						}
					}
				}
				rewind(ptr_file); //didn't pick any, restart.
			}
			convertStringUpper(words[i]);
			printf("%s\n",words[i]);
		}
		fclose(ptr_file);
		printf("\n");

		//pick magic word
		int magicWordIndex = rand()%numWords;

		//Loop to get and check guesses
		int guesses = 4;
		while(guesses > 0) {
			printf("Guess (%d left)? ", guesses);
			char guess[1000];
			scanf("%s", &guess);
			convertStringUpper(guess);
			if (inWordlist(words, guess)) { //if the word was valid
				//sum number of correct letters
				int numCorrect = 0;
				for(int i = 0; i < wordLength; i++) {
					if(words[magicWordIndex][i] == guess[i])
						numCorrect++;
				}
				//print numCorrect, - a guess and win/lose game if applicable
				printf("%d/%d correct\n", numCorrect, wordLength);
				if(numCorrect == wordLength) {
					printf("\nYou win!\n");
					break;
				} else {
					guesses--;
					if(guesses == 0) {
						printf("\nYou loose! The correct answer was '%s'\n", words[magicWordIndex]);
						//break;
					}
				}
			} else {
				printf("Guess not one of the options!\n");
			}
		}

		//ask if the user want's to play again, update loop variable if not
		printf("Play again (y/n)? ");
		char playAgainChar;
		scanf(" %c", &playAgainChar);
		if(toupper(playAgainChar) != 'Y')
			keepPlaying = 0;
	}

	return 0;
}

//given an array of strings and a word, returns 1 if the word is in the array
int inWordlist(char wordlist[numWords][wordLength+1], char* word) {
	for(int i = 0; i < numWords; i++) {
		//printf("|%s-%s|\n", word, wordlist[i]);
		int wordsMatch = 1;
		for(int j = 0; j < wordLength; j++) {
			if(word[j] != wordlist[i][j]) wordsMatch = 0;
		}
		if(wordsMatch) return 1;
		//if(strcmp(wordlist[i], word) == 0) return 1;
	}
	return 0;
}

//updates each char in a string to be uppercase
void convertStringUpper(char* str) {
	for(int i = 0; i < strlen(str); i++) {
		str[i] = toupper(str[i]);
	}
}
