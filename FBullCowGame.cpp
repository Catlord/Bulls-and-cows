#include "FBullCowGame.h"
#include <map>

#define TMap std::map  // to make syntax unreal friendly

FBullCowGame::FBullCowGame() { Reset(); } // defaut constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,10},{6,15},{7,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	//return MaxTries;
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "place"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a valid guess, incriments turn and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all the letters in the hidden word
	
	for(int32 MWChar = 0; MWChar < WordLength; MWChar++){
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match  then 
			if (Guess[GChar] == MyHiddenWord[MWChar]) {
				if (MWChar == GChar) { //  if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				} else {
					BullCowCount.Cows++; // incriments cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EWordStatus::not_Isogram;
	} else if (!IsLowercase(Guess)) {
		return EWordStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {
		return EWordStatus::wrong_length;
	} else {
		return EWordStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {
			return false; // we dont have an isogram
		} else {
			LetterSeen[Letter] = true;// add the letter
		}
		
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {  // for all letters of the word
		if (!islower(Letter)) {
			return false; // we dont have an isogram
		} else {
			return true;
		}
	}
}
