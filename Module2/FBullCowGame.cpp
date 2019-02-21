#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
// We use "define" because "using" would be more complicated. It would needed parameters.
#define TMap std::map


FBullCowGame::FBullCowGame() { Reset(); }
FBullCowGame::FBullCowGame(int32 difficulty) { Reset(difficulty); }

int32 FBullCowGame::GetCurrentTry()			const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon()				const {	return bGameIsWon; }


int32 FBullCowGame::GetHiddenWordLength()	const {
	return MyHiddenWord.length();
}


int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,3}, {5,4}, {6,5}, {4,5} }; // "{}" Initialize the map.
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram, return an error TODO write function wether is an isogram or not.
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) { // if the guess isn't all lowercase, return an error TODO write function wether or not is lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { // if the guess length is wrong, return an error.
		return EGuessStatus::Wrong_Length;
	}
	else { // otherwise, return OK
		return EGuessStatus::OK;
	}

}

void FBullCowGame::Reset() {
	constexpr int32 DEFAULT_DIFFICULTY = 5;

	Reset(DEFAULT_DIFFICULTY);

	return;
}

void FBullCowGame::Reset(int32 difficulty) {
	TMap<int32, FString> HiddenWords{ {3,"and"}, {4,"same"}, {5,"plane"}, {6,"daemon"}, {7,"backlit"} }; // "{}" Initialize the map.

	MyHiddenWord = HiddenWords[difficulty]; // This must be an isogram.
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

// Receives a VALID guess, increments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// Loop through all letters in the hidden word.
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the hidden word.
		for (int32 GWChar = 0; GWChar < WordLength; GWChar++) {
			// if they match
			if (Guess[GWChar] == MyHiddenWord[MHWChar]) {
				// if they're in the same place.
				if (MHWChar == GWChar) {
					// increments bulls
					BullCowCount.bulls++;
				}
				else {
					// increments cows if not
					BullCowCount.cows++;
				}
			}
		}
	}
	
	if (BullCowCount.bulls == WordLength) {
		bGameIsWon = true;
	}

	return BullCowCount;
}

// Check if the guess is an isogram.
bool FBullCowGame::IsIsogram(FString Word) const {
	bool isIsogram = true;
	// Treat 0 and 1 letter words as isograms.
	if (Word.length() > 1) {
		// setup our map
		TMap<char, bool> LetterSeen;
		// Loop through all the letters of the word...
		//for (int WChar = 0; WChar < Word.length(); WChar++) {

		// his way (foreach)
		//for (auto Letter : Word) {
		//	Letter = tolower(Letter);
		//	// ... if the letter is in the map
		//	if (LetterSeen[Letter]) {
		//		// ... we do NOT have an isogram
		//		return false;
		//	}
		//	// ... otherwise
		//	else {
		//		// ... add the letter to the map as seen
		//		LetterSeen[Letter] = true;
		//	}
		//}

		// my way (while loop with iterators)
		auto Letter = Word.begin();

		while (Letter != Word.end() && isIsogram) {
			*Letter = tolower(*Letter);
			// ... if the letter is in the map
			if (LetterSeen[*Letter]) {
				// ... we do NOT have an isogram
				isIsogram = false;
			}
			// ... otherwise
			else {
				// ... add the letter to the map as seen
				LetterSeen[*Letter] = true;
			}

			Letter++;
		}
	}
	// 
	return isIsogram;
}

// Check the word is made up of just lower case letters.
bool FBullCowGame::IsLowerCase(FString Word) const {
	bool isLowerCase = true;

	// Treat 0 length string.
	if (Word.length() > 0) {
		// Loop through the letters of the word...
		auto Letter = Word.begin();
		while (Letter != Word.end() && isLowerCase) {
			// ...if the letter is not lower case
			if (!islower(*Letter)) {
				isLowerCase = false;
			}
			Letter++;
		}
	}

	return isLowerCase;
}

//bool FBullCowGame::islower(char Letter) const {
//	bool isLower = false;
//
//	if (Letter >= 'a' && Letter <= 'z') {
//		isLower = true;
//	}
//
//	return isLower;
//}
