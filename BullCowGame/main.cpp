#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int; 


void printIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

//entry point for our game
int main() 
{
	bool bPlayAgain = false;
	do {
		printIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;
	
}


//introduce the game
void printIntro() 
{
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for guesses while the game is NOT won and tries still remain
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);


		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}


FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		//get a guess from player
		std::cout << "Try " << CurrentTry << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter the word in lowercase.\n";
			break;
		default:
			//assuming the guess satisfies all requirements
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same letter? (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return Response[0] == 'y' || Response[1] == 'Y';
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "CONGRATS!! You Win!!\n\n";
	}
	else {
		std::cout << "Sorry! Better luck next time!\n\n";
	}
}
