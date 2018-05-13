/*

Hello de benoit

*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
// namespace est utilisé pour remplacer std
// attention la méthode peut s'averer périlleuse dans le cas d'une transmittion du code

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point of the game
int main() {
	do {
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	return 0; // exit the application
}

// introduce the game
void PrintIntro() {
	std::cout << "\n";
	std::cout << "Welcome to bulls and cows\n";
	std::cout << "  _____\n";
	std::cout << " /     \\\n";
	std::cout << "|   o   |  & MEUUHHH !\n";
	std::cout << " \\ ____/\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " isogram I'm thinking ?\n";
	std::cout << "You will have " << BCGame.GetMaxTries() << " tries to find it, good luck !\n";
	std::cout << std::endl;
	return;
}

// Plays a single game to completion
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// Print number of bull and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

//loop continually until the user give a valid guess
FText GetValidGuess() { 
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " de " << BCGame.GetMaxTries();
		std::cout << " - Enter your guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EWordStatus::wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n";
			break;
		case EWordStatus::not_Isogram:
			std::cout << "Please enter a word without repeating letters, thanks.\n.";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK); // keep looping until there s no error
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n) ?\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Bravo ! Vous avez gagne !\n\n";
	}
	else {
		std::cout << "C'est difficile huh ?\n\n";
	}
}