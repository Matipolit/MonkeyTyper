#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define clear() printf("\033[H\033[J")

int charCount;
struct winsize w;


bool intInArr( int x, int arr[], int arrSize ){
	for(int i=0; i<arrSize; i++){
		if(arr[i]==x){
			return true;
		}
	}
	return false;
}

int randomInt(int bottomBound, int topBound){
	return(rand() % topBound);
}

void generateRandomInts( int arr[], int size, int bottomBound, int topBound ){
	int num = 0;
	for(int i=0; i<size; i++){
		do{
			num = randomInt(bottomBound, topBound);
		}while(intInArr(num, arr, size));
		arr[i] = num;
	}
}

void initArrMinus( int arr[], int size ){
	for (int i=0; i<size; i++){
		arr[i] = -1;
	}
}

void slice( const char *str, char *result, size_t start, size_t end ) {
    strncpy(result, str + start, end - start);
}

void printColor( char c, char *color ){
	char *setColor = "";
	if(strcmp(color, "red")){
		setColor="\033[0;32m";
	}else if(strcmp(color, "green")){
		setColor = "\033[0;31m";
	}

	printf("%s", setColor);
	putchar(c);
	printf("\033[0m");
}

void prepareForExit(){
	system("/bin/stty echo"); // prints user input
	system("/bin/stty cooked"); // gets user input with enter
	system("clear");
}

void renderText( char *enteredText, char *sourceText, int numberOfEnteredCharacters ){
	system("clear");
	int i;
	for(i = 0; i<numberOfEnteredCharacters; i++){
		if(sourceText[i]==enteredText[i]){
			printColor(enteredText[i], "green");
		}else{
			printColor(sourceText[i], "red");
		}
	}
	while(i<charCount){
		printf("%c", sourceText[i]);
		i++;
	}

}

void renderCursor(int charNum){
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	gotoxy(((charNum+1) % w.ws_col), ((charNum+1) / w.ws_col)+1);
}

void printStats(int wordcount, double time){
	prepareForExit();
	printf("time taken: %f\n", time);
	double wpm = wordcount*(60/time);
	printf("Your average wpm: %.1f\n", wpm);
}



int main( int argc, char *argv[] ){

	if(argc!=2){
		printf("Enter one argument: word count\n");
		return 1;
	}
	
	int wordCount = atoi(argv[1]);
	
	FILE *fptr;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	const int TOTAL_WORDS = 466550;

	char words[wordCount][46];
	int randomInts[wordCount];
	int wordOrder[wordCount];
	charCount=0;

	printf("Number of words: %d\n", wordCount);

	// Terminal size w.ws_row, w.ws_col
  	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	srand(time(NULL));

	initArrMinus(randomInts, wordCount);
	initArrMinus(wordOrder, wordCount);
	generateRandomInts(randomInts, wordCount, 0, TOTAL_WORDS);
	generateRandomInts(wordOrder, wordCount, 0, wordCount);

	int currLine = 0;
	int currWord = 0;


	fptr = fopen("words.txt", "r");
	while((read = getline( &line, &len, fptr )) != -1){
		if(intInArr(currLine, randomInts, wordCount)){
			int length = strlen(line);
			slice(line, words[wordOrder[currWord]], 0, length-1);
			charCount+=length;
			words[wordOrder[currWord]][strlen(line)-1]='\0';
						currWord++;
		}
		currLine++;
	}
	fclose(fptr);

	char joinedWords[charCount];
	char enteredChars[charCount];

	memset( joinedWords, 0, charCount * sizeof(char) );
	memset( enteredChars, 0, charCount * sizeof(char) );
	
	for(int i=0; i<wordCount; i++){
		strcat(joinedWords, words[i]);
		strcat(joinedWords, " ");

	}

	// TYPING INTERFACE

	system("clear");	

	printf("%s", joinedWords);
	
	system("/bin/stty raw"); // gets user input without enter
	system("/bin/stty -echo"); // doesn't print user input

	// entered character
	int entered;
	int charNum = 0;
	int columnNum = 0;
	int rowNum = 0;

	gotoxy(0,0);
	struct timespec begin, end;
	
	// typing loop
	
	while(true){
		entered = getchar();
		switch(entered){
			case 27: {
				prepareForExit();
				return 0;
			}
			case 127: {
				if (charNum>0) {
					enteredChars[charNum]=(char)0;
					charNum--;
					renderText(enteredChars, joinedWords, charNum);
					renderCursor(charNum);
				}
				break;
			}
			default:
				if (charNum>=(charCount-2)) {
					clock_gettime(CLOCK_REALTIME, &end);
					long seconds = end.tv_sec - begin.tv_sec;
					long nanoseconds = end.tv_nsec - begin.tv_nsec;
					double elapsed = seconds + nanoseconds*1e-9;
					printStats(wordCount, elapsed);
					return 0;
				} else {
					if(charNum==1){ clock_gettime(CLOCK_REALTIME, &begin); }
					enteredChars[charNum] = entered;
					charNum++;
					renderText(enteredChars, joinedWords, charNum);
					renderCursor(charNum);
				}
				break;
		}
	}
}
