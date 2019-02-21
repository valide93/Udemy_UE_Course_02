/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void StartGame();
FText GetValidGuess();
void PrintGameSummary();
void PlayGame();
bool AskToPlayAgain();


FBullCowGame BCGame; // instatiate a new game, which we re-use across plays.

// Entry point for our application.
int main() {
	do {
		StartGame();
		PlayGame();
	} while (AskToPlayAgain());

	return 0; // Exit the application.
}

void StartGame() {
	FString FS_difficulty = "";
	int difficulty = 3;

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";

	std::cout << "Choose the difficulty you want to play.\n";

	// Take the difficulty in input until the user insert a valid guess.
	do {
		if (difficulty < 3 || difficulty > 7) {
			std::cout << "Please, remain in the range.\n";
		}

		std::cout << "3- very easy, 4- easy, 5- medium, 6- hard, 7- very hard: ";
		// After some searching, I found out that it is best to "cin" to take in input the same type of data.
		// At first, I took an integer directly and it skipped the second "cin".
		std::getline(std::cin, FS_difficulty);
		difficulty = std::stoi(FS_difficulty);
	} while (difficulty < 3 || difficulty > 7);

	BCGame.Reset(difficulty);

	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Play a single game to completion
void PlayGame() {
	//BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses.
	
	// Loop until the guesses until the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows.
		std::cout << "Bulls= " << BullCowCount.bulls << std::endl;
		std::cout << "Cows= " << BullCowCount.cows << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}

FText GetValidGuess() {
	int32 CurrentTry = BCGame.GetCurrentTry();
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status; // It is important to start with a value out of our domain.

	// Keep looping until it gets a valid guess.
	do {
		// Get a guess from the player.
		std::cout << "Try " << CurrentTry << " (" << BCGame.GetMaxTries() - CurrentTry + 1 << " left). Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;

		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;

		default:
			// Assuming the guess valid.
			break;
		}

	} while (Status != EGuessStatus::OK);

	return Guess;
}

void PrintGameSummary() {
	std::cout << "\n\n";

	if (BCGame.IsGameWon()) {
		std::cout << "Well Done! You won!\n\n";
	}
	else {
		std::cout << "Better luck next time!\n\n";
	}

	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	std::cout << "\n\n";

	return (Response[0] == 'y') ||
		(Response[0] == 'Y');
}
