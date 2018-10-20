/* This is the console executable that makes use of the BULLCOW Class.
This acts as the view in a MVC pattern and is responsible for all user interaction.	
For game logic see the FBullCowGame Class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse across plays.

int32 main()
{
	bool Response = false;
	// Play game until player doesnt want to
	do {
		PrintIntro();
		PlayGame();
		Response = AskToPlayAgain();
	} while (Response == 1);

	std::cout << std::endl;
	std::cout << "Thanks for playing :)";

	std::cout << std::endl;
	return 0;// exit game
}



void PrintIntro() 
{
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Bulls represent a letter that is in the correct position.\n";
	std::cout << "Cows represent a letter that is part of the word but in an incorrect position.\n";

	std::cout << std::endl;
	return;
}

//Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "your max tries: "<< MaxTries << std::endl;
	
	// loop asking for guesses while the game is not won.
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		
		// submit valid guess to the game and receive count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// repeat the guess back to the player
		std::cout << "Your guess was " << Guess << std::endl;
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "." << std::endl;
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from a player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Please enter your guess: ";
	
		std::getline(std::cin, Guess);

		// check guess validity
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess cannot have repeating letters for an isogram. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Only enter lowercase letters. \n";
			break;

		default:
			//assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	
	std::cout << "Do you want to play again with another hidden word (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);

	std::cout << std::endl <<std::endl;

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulation!! You Win! \n";
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}
}
