/*
the game logic (no view code or direct user interaction
the game is a simple guess the word game
*/

#pragma once
#include <string>

// to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	// public par defaut
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid_Status,
	OK,
	not_Isogram,
	wrong_length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialization 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
