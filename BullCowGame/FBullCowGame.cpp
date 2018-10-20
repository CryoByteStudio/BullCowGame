#pragma once
#include "FBullCowGame.h"
#include <map>
#include <cstdlib>


// to make more unreal friemdly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() //default constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10},{6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))    // if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if the guess isn't lowercase 
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess is the wrong word length
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsNotNumber(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else // otherwise return ok
	{
		return EGuessStatus::OK;
	}
	return EGuessStatus::OK; 
}

void FBullCowGame::Reset()
{
	TMap<int32, FString> HiddenWord{ {1,"planet"},{2,"cloned"},{3,"crazed"},{4,"beauty"},{5,"cat"},{6,"ate"},{7,"head"},{8,"lead"},{9,"great"},{10,"trick"} };

	MyCurrrentTry = 1;
	MyHiddenWord = HiddenWord[(rand()%10)+1];
	bGameIsWon = false;
	return;
}

// receives a valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrrentTry++;
	FBullCowCount BullCowCount;
	//loop all letters in the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		//compare guest letters against the current hidden word letter
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			//if they match
			if (Guess[GChar] == MyHiddenWord[MHWChar] && GChar==MHWChar)
			{
				//increment bulls if in the same place
				BullCowCount.Bulls++; 
			}	
			//else if 	
			else if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//increment cows if letter is the same
				BullCowCount.Cows++;
			}	
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)	
	{
		bGameIsWon = true; 
	}

	else { bGameIsWon = false; }
	return BullCowCount; 
	
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])// if Letter is in the map
		{
			return false; // we do Not have an Isogram
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen

		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter != tolower(Letter))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool FBullCowGame::IsNotNumber(FString Guess) const
{
	FString Numbers = "1234567890";
	
	for (int32 GChar = 0; GChar < Guess.length(); GChar++ )
	{
		for (int32 NChar = 0; NChar < Numbers.length(); NChar++)
		{
			if (Guess[GChar] == Numbers[NChar])
				{
					return false;
				}
			
		}
	}

}