#include <iostream>
#include <random>
#include <cstdlib>
#include <limits> // for std::numeric_limits
#include <string>

//1. Adding a complexity layer
enum class Difficulty {
	Easy = 1,	//0
	Medium = 2,	//1
	Hard = 3	//2
};

static int user_random_number(std::mt19937 &rng) {

	bool user_number_range{};
	int min_range{};
	int max_range{};
	const int MAX_VALUE{ 1000 };

	while (true) {
		std::cout << "Would you like to decide the range of the numbers? (1=Yes, 0=No):  ";
		// Checking for user validation
		if (!(std::cin >> user_number_range)) {
			std::cout << "Please enter the number 1 or 0. \n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (!user_number_range) {
			min_range = 1;
			max_range = 100;
		}
		else {
			std::cout << "Enter min and max (max <= " << MAX_VALUE << "): ";
			if (!(std::cin >> min_range >> max_range)) {
				std::cout << "Invalid numbers. Try again. \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			if (min_range > max_range || MAX_VALUE < max_range) {
				std::cout << "Error: Ensure 0 < min < max < " << MAX_VALUE << " \n";
				continue;
			}
		}
		// We have valid min and max numbers
		// Seed the random number generator with random engine.
		std::uniform_int_distribution<int>distribution(min_range, max_range);
		return distribution(rng);
	}

}

static int user_choice_number() {

	int chances{};
	//Chances for the user to guess the number	
	while (true) {
		std::cout << "How many chances would you like? ";
		// Check if input is integer
		if (!(std::cin >> chances)) {
			std::cout << "That is not a valid integer. \n";

			//Clear error flags and discard invalid input
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// flushes the bad input.
		}
		else if (chances < 1 || chances > 5) {
			std::cout << "Error: Please keep your chances between 1 and 5 (included).\n";
		}
		else {
			std::cout << "Chances given: " << chances << "\n";
			break;	// exit loop if input is valid
		}
	}
	return chances;
}


int guessing_game(char start_game, std::mt19937 &rng) {
	int i{ 1 };

	// Function to create the guessing game.
	while (start_game == 'y') {
		// Lets call the user defined random number
		int get_random_number = user_random_number(rng);
		
		// Lets call the user defined chances
		int get_chances = user_choice_number();

		std::cout << "Set the difficulty of the game: \n";
		std::cout << "Easy = 1 \t Medium = 2 \t Hard = 3 \n";

		// Setting the difficulty of the game and modifying chances given
		int difficulty_input{};
		std::cin >> difficulty_input;
		if (difficulty_input >= static_cast<int>(Difficulty::Easy) && difficulty_input <= static_cast<int>(Difficulty::Hard)) {
			Difficulty curr_option = static_cast<Difficulty>(difficulty_input);
			if (curr_option == Difficulty::Medium) {
				get_chances -= 1;
				std::cout << "You have chosen to play on medium mode.Your chances to guess have reduced by 1. \n";
			}
			else if (curr_option == Difficulty::Hard) {
				try
				{
					get_chances -= 2;
					std::cout << "You have chosen to play on hard mode. Your chances to guess have reduced by 2. \n";
					if (get_chances == 0) {
						throw "You need to input a minimum of 3 chances. \n";
					}
				}
				catch (const std::exception& e)
				{
					std::cout << "Caught exception " << e.what();
				}

			}
			else if(curr_option == Difficulty::Easy){
				get_chances += 1;
				std::cout << "You have chosen to play on easy mode. Your chances to guess have increased by 1. \n";
			}
			else {
				get_chances -= 0;
			}
		}

		int guessed_number{0};
		while (get_chances > 0) {
			std::cout << "Enter the number your guess: ";
			// Making sure the number is being added
			if (!(std::cin >> guessed_number)) {
				std::cout << "Please enter a valid number. \n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			// second if conditional - directly ending the game on guessing the number
			if (guessed_number == get_random_number) {
				std::cout << "The number " << guessed_number << " was correct! Congratulations. \n";
				std::cout << "You have won " << i << " double chocolate chip cookie(s) \n";
				++i;
				break;
			}
			// Logic to enhance variability like greater; lesser and reducing chances
			else {
				--get_chances;
				std::cout << " Incorrect guess! You currently have " << get_chances << " chance(s) left. \n";
				if (get_chances == 0) {
					std::cout << "You have run out of chances. Correct number was " << get_random_number <<  "\n";
					break;
				}
				else if (guessed_number > get_random_number) {
					std::cout << "Too high! Try again. \n";
				}
				else {
					std::cout << "Too low!. Try again \n";
				}
			}
		}
		std::cout << "Game over! Would you like to play again? (y/n): ";
		std::cin >> start_game;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	if (start_game == 'n') {
		std::cout << "Too bad! You could have won one or more double chocolate chip cookies. \n";
	}

	return 0;
}




