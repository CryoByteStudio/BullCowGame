/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind.
*/

#pragma once
#include <string>

// to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

//all values initialized to zero
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
	Not_Lowercase,
	Wrong_Length
};
class FBullCowGame
{
// public methods
public:
	FBullCowGame(); // Constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); // TODO make a more rich return value.
	// counts bulls and cows and increases try number assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);

private:
	// See the constructor FBullCowGame
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsNotNumber(FString) const;
};