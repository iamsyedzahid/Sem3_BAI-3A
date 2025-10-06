#include <iostream>
#include <cstdlib>
#include <ctime>
// Function to simulate the guessing game using Direct Recursion
void guessNumber(int target, int currentPlayer, int numPlayers) {
int guess;
std::cout << "Player " << currentPlayer + 1 << ", enter your guess (1-100): ";
if (!(std::cin >> guess)) {
// Handle invalid input (e.g., non-integer)
std::cin.clear();
std::cin.ignore(10000, '\n');
std::cout << "Invalid input. Please enter a number." << std::endl;

guessNumber(target, currentPlayer, numPlayers); // Try again with the same player
return;
}
// Base Case: Correct Guess
if (guess == target) {
std::cout << "\nCongratulations, Player " << currentPlayer + 1 << "! You guessed the
correct number (" << target << ") and won the game!" << std::endl;
return;
}
// Recursive Step: Incorrect Guess
else {
if (guess < target) {
std::cout << "Too Low! Turn passes." << std::endl;
} else {
std::cout << “Too High! Turn passes." << std::endl;
}
int nextPlayer = (currentPlayer + 1) % numPlayers;
// Recursive call for the next turn
guessNumber(target, nextPlayer, numPlayers);
}
}
