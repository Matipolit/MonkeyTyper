# MonkeyTyper
A simple Monkeytype CLI clone for measuring typing speed without leaving the terminal.

## Building
If you're using Bash run
```
./build.sh
```
Otherwise use your favourite C compiler.

## Usage
Run
```
./monkeytyper <wordCount>
```
Where ```wordcount``` is the length of the typing test in words. After you type the whole text the elapsed time and WPM speed will be displayed.  
To exit the program at any time press the escape key, **don't kill the program as it will leave your shell unusable by disabling the cursor and typed text.**

## Custom wordlists
Just replace the contents of ```words.txt``` with a wordlist of your choosing, one word per line.
