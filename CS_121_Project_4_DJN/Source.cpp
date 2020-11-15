/*
File: Source.cpp
Name: David Niederweis
Date: 11/13/2019
Course: CS121-03 - Computer Science I
Description: Word guessing game. On running, program selects random word from wordlist and user guesses the word letter by letter.
*/

#include <iostream> // for printing and main functionality
#include <fstream> // for importing wordlist
#include <cstdlib> // for generating random number
#include <ctime> // for seeding random number generator with current time
#include <string> // for getting string, and string functions


// set namespace
using namespace std;


// function declarations
int getRandom(int len);
string getDisplayWord(int length);
string replaceWithGuess(string word, int wordLength, char guess, int *misses, string displayWord);


// main functions
int main()
{
	// create input stream for wordlist file
	ifstream wordFile;
	// create const variable to allow array creation
	const int wordListLength = 29;
	string wordList[wordListLength];

	// create variable and pointer for user misses
	int playerMisses = 0;
	int* playerMissesPtr = &playerMisses;
	// create variable and pointer for total user guesses
	int totalGuesses = 0;
	int* totalGuessesPtr = &totalGuesses;


	// seed random function with current time
	srand(time(0));
	// open wordlist file
	wordFile.open("words.txt");


	// if wordlist could not be opened inform user and return with error;
	if (!wordFile)
	{
		cout << "Failed to open wordlist!" << endl;
		return -1;
	}


	// create iterator to insert words from wordlist into word array
	int iterator = 0;
	while (!wordFile.eof())
	{
		// declare empty string variable to hold current word
		string word;
		// get word from file and store in word-variable
		getline(wordFile, word);
		// insert word into wordlist
		wordList[iterator] = word;
		// increment iterator to insert into next index
		iterator++;
	}

	// get random word from list as secret word
	string secretWord = wordList[getRandom(wordListLength)];
	// store secret word length
	int wordLength = secretWord.length();
	// generate "censored" word to display to user
	string displayWord = getDisplayWord(wordLength);
	

	// while the user has not guessed all letters and has not made 6 incorrect guesses, loop
	while (displayWord.find("*") < wordLength && playerMisses < 6)
	{
		// increment total guesses
		*totalGuessesPtr += 1;
		// declare guess variable to store character
		char guess;
		// prompt the user to enter guess
		cout << "Here is your word: " << displayWord << endl;
		cout << "Please type your next guess here: ";
		// get user guess
		cin >> guess;
		// call function to modify display word and store return value in display word
		displayWord = replaceWithGuess(secretWord, wordLength, guess, playerMissesPtr, displayWord);
	}


	// inform user that game has ended
	cout << endl << endl << "############################ GAME OVER ############################" << endl;


	// if user made 6+ mistakes, user lost.
	if (playerMisses >= 6)
	{
		// inform user that they lost
		cout << "You ran out of guesses!" << endl;
		// inform user how many guesses were made and how many mistakes were made
		cout << "You guessed " << *totalGuessesPtr << " times and missed " << *playerMissesPtr << "times." << endl;
		// inform user what the secret word was and and encourage user
		cout << "Your word to guess was: " << secretWord << endl;
		cout << "Thank you for playing. Better luck next time!" << endl;
	}


	// user wins
	else
	{
		// inform user that they won
		cout << "Congratulations!" << endl;
		// inform user what the word was, how many guesses have been made and how many incorrect guesses were made
		cout << "You guessed the word: " << secretWord << ". You took " << *totalGuessesPtr << " guesses and only missed " << *playerMissesPtr << " time(s)." << endl;
	}
	// close wordfile and return 0
	wordFile.close();
	return 0;
}


// return random number in range [0, len)
int getRandom(int len)
{
	return(rand() % len);
};


// create a string of asterics of length len
string getDisplayWord(int len)
{
	string str = "";
	for (int i = 0; i < len; i++)
	{
		str.append("*");
	}
	return str;
}


// function that replaces asterics in display word with correct guesses
string replaceWithGuess(string word, const int wordLength, char guess, int *misses, string displayWord)
{
	// get first index of guess character
	int index = word.find(guess);

	// if index is -1 (not found in string) increment misses and print out new misses
	if (index == -1)
	{
		*misses += 1;
		cout << "Misses: " << *misses << endl;

	}

	// else, user made correct guess
	else {
		// while the index of guess is not -1, replace astrics at index with correct character
		while (index != -1)
			{
				displayWord[index] = guess;
				index = word.find(guess, index + 1);
			}
	}
	// return new display word
	return displayWord;
}