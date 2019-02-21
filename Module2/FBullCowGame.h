/*
The game logic (no view code or direct user interaction).
The game is a simple guess the word game based on Mastermind.
*/
#pragma once
#include <iostream>

// To make syntax Unreal friendly
using FString		= std::string;
using int32			= int;

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows	= 0;
};


enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	// Constructors
	FBullCowGame();
	FBullCowGame(int32);

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	void Reset(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	// helper functions
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	// it is already implemented in C++
	/*bool islower(char) const;*/

	FString MyHiddenWord;
	int32 MyCurrentTry;
	bool bGameIsWon;
};