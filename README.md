# MonkeyTyper
A simple Monkeytype CLI clone for measuring typing speed without leaving the terminal.

## Building
If you're using Bash and have GCC installed run
```
./build.sh
```
Otherwise use your favourite C compiler.

## Requirements
This program uses Linux and Bash specific functionality, so it's not expected to work elsewhere.

## Usage
Ensure that the ```words.txt``` file is in the same directory as the program.
Run
```
./monkeytyper <wordCount>
```
Where ```wordcount``` is the length of the typing test in words. After you type the whole text the elapsed time and WPM speed will be displayed.  
To exit the program at any time press the escape key, **don't kill the program as it will leave your shell unusable by disabling the cursor and typed text.**

## TODOs
- [ ] Custom wordlists
- [ ] Accuracy %
