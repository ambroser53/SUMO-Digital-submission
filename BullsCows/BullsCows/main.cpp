/* This is the console executable, that makes use of the FBullCowGame Class
all interation with user takes place here
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string; //to make syntax unreal compatible
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; // instantiate a new game, which 

//entry point of application
int main()
{
	int MaxTries = BCGame.GetMaxTries();


	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain == true);

	return 0;
}


void PrintIntro()
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	
	std::cout << "\n\nWelcome to Bulls and Cows, a Fun Word Game \n";
	std::cout << "    ,           ,\n";
	std::cout << "   /             \\ " << std::endl;
	std::cout << "  ((__-^^-,-^^-__))\n";
	std::cout << "   `-_---' `---_-' \n";
	std::cout << "    <__|o` 'o|__> \n";
	std::cout << "       \  `  / \n";
	std::cout << "        ): :(\n";
	std::cout << "        :o_o: \n\n";
	std::cout << "Can you guess the "; std::cout << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of? \n\n";
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while
	// the game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		// Submit valid guess to the game and recieve counts of Bulls + Cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "  Cows = " << BullCowCount.Cows << "\n\n";
	}

	BCGame.PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// Get Guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "; 
		std::cout << BCGame.GetMaxTries() << " Enter Your Guess : ";
		std::getline(std::cin, Guess);

		// check guess and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Caps_Found:
			std::cout << "Please do not include capital letters in your guess. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter word without repeating letter. \n\n";
			break;
		default:
			//assume Guess is valid
			break;
		}
		
	} while (Status != EGuessStatus::OK); //Keep looping until there's no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
