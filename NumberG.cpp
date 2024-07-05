#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int generateRandomNumber(int min, int max) {
return rand() % (max - min + 1) + min;
}

int main() {
srand(static_cast<unsigned int>(time(0)));

const int minNumber = 1;
const int maxNumber = 100;
int secretNumber, guess, attempts = 0;

secretNumber = generateRandomNumber(minNumber, maxNumber);

cout << "Welcome to the Number Guessing Game" << endl;
cout << "Try to guess the secret number between " << minNumber << " and " << maxNumber << "." << endl;

do {
cout << "Enter your guess: ";
cin >> guess;

attempts++;

if (guess == secretNumber) {
cout << "Congratulations! You guessed the correct number in " << attempts << " attempts." << endl;
} else if (guess < secretNumber) {
cout << "Too low. Try again." << endl;
} else {
cout << "Too high. Try again." << endl;
}

} while (guess != secretNumber);

return 0; 
}