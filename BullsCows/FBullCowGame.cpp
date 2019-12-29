#pragma once
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor, is called when object is created

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }


int32 FBullCowGame::GetMaxTries() const { //changes difficulty
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[HiddenWord.length()];
}

void FBullCowGame::Reset()
{	
	FString HIDDEN_WORD = "planet";
	HiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	FBullCowGame::bIsGameWon = false;
	return;
}

void FBullCowGame::PrintGameSummary()
{
	if (FBullCowGame::bIsGameWon) {
		std::cout << "YOU WON! You Guessed the word correctly! \n";
	}
	else {
		std::cout << "YOU LOSE. Too bad, better luck next time. \n";
	}
}

FString FBullCowGame::GetHiddenWord()
{
	// TODO create a library of guessable isograms
	// TODO make it so the program picks one of the words at random
	// TODO make it return that word
	return HiddenWord;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if guess isnt isogram 
	{
		return EGuessStatus::Not_Isogram; // TODO write function
	}
	else if (!IsLowercase(Guess)) //if guess contains caps
	{
		return EGuessStatus::Caps_Found; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength())//if guess is the wrong length
	{
		return EGuessStatus::Wrong_Length;
	}
	else //otherwise 
	{
		return EGuessStatus::OK;
	}
	return EGuessStatus::OK; //TODO  make actual error
}


// recieves a VALID guess, increments turn, returns No. Bulls&Cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount; //assuming HiddenWord & Guess have the same length

	// loop through all letters in the guess
	int32 WordLength = HiddenWord.length();
	for (int32 HiddenWordChar = 0; HiddenWordChar < WordLength; HiddenWordChar++) {
		// for each letter, compare against HiddenWord
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++) {
			if (Guess[GuessChar] == HiddenWord[HiddenWordChar]) { // if they match
				if (HiddenWordChar == GuessChar) {	// and in the same place
					BullCowCount.Bulls++; // increment Bulls
				}
				else {
					BullCowCount.Cows++; // must be cow so increment Cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		FBullCowGame::bIsGameWon = true;
	}
	else {
		FBullCowGame::bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 or 1 long letter words as isograms
	

	TMap<char, bool> LetterSeen;//Create map of the alphabet
	for (auto Letter : Word)	//loop for every letter in word
	{
		Letter = tolower(Letter); //handles mixed case
		if (LetterSeen[Letter]) {	//if a letter is in the map
			return false; //Guess isnt an isogram return false
		} else { //otherwise
			LetterSeen[Letter] = true; //it is an isogram and add letter to the map
		}
	}

	return true; // for cases in which  \0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) { //loop for every letter in the word
		if (Letter != tolower(Letter)) {//if a letter is uppercase
			return false; //invalid guess
		}
		else {
			return true;
		}
	}
	return true;
}
