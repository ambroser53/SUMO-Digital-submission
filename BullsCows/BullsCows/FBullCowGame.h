/* This is the header file to the FBullCowGame Class 
and deals with all calculations and configurations of data
to then be passed on through methods to the main.cpp to be 
present to the player */
#pragma once
#include <string>
#include <iostream>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Caps_Found,
};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;


	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	void PrintGameSummary();
	FString GetHiddenWord();
	FBullCowCount SubmitValidGuess(FString);


private:
	// see constructor for initialisation
	int32 MyCurrentTry;

	FString HiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};