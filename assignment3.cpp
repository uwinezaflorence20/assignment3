#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

std::string selectRandomWord() {
    std::vector<std::string> words = {"apple", "banana", "cherry", "dog", "elephant", "frog", "grape", "honey", "iguana", "jelly","workshop","baby","demon","pathogen","weekhow","kigali","following","tuesday","potato"};
    int randomIndex = std::rand() % words.size();
    return words[randomIndex];
}

std::string displayWord(const std::string& word, const std::set<char>& guessedLetters) {
    std::string display;
    for (char letter : word) {
        if (guessedLetters.count(letter) > 0) {
            display += letter;
        } else {
            display += '-';
        }
    }
    return display;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random number generator

    std::string secretWord = selectRandomWord();
    std::set<char> guessedLetters;
    int warnings = 3;
    int guesses = 6;

    std::cout << "Welcome to Hangman!" << std::endl;
    std::cout << "Guess the secret word one letter at a time." << std::endl;

    while (guesses > 0) {
        std::cout << "\nGuesses left: " << guesses << std::endl;
        std::cout << "Warnings left: " << warnings << std::endl;
        std::cout << "Unused letters: ";
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            if (guessedLetters.count(letter) == 0) {
                std::cout << letter << " ";
            }
        }
        std::cout << std::endl;

        std::string display = displayWord(secretWord, guessedLetters);
        std::cout << "Current progress: " << display << std::endl;

        char guess;
        std::cout << "Enter a letter: ";
        std::cin >> guess;
        guess = std::tolower(guess);

        if (!std::isalpha(guess)) {
            if (warnings > 0) {
                --warnings;
                std::cout << "Invalid input! You have " << warnings << " warnings left." << std::endl;
            } else {
                --guesses;
                std::cout << "Invalid input! You lost a guess. Guesses left: " << guesses << std::endl;
            }
            continue;
        }

        if (guessedLetters.count(guess) > 0) {
            if (warnings > 0) {
                --warnings;
                std::cout << "You've already guessed that letter. You have " << warnings << " warnings left." << std::endl;
            } else {
                --guesses;
                std::cout << "You've already guessed that letter. You lost a guess. Guesses left: " << guesses << std::endl;
            }
            continue;
        }

        guessedLetters.insert(guess);

        if (secretWord.find(guess) != std::string::npos) {
            display = displayWord(secretWord, guessedLetters);
            std::cout << "Good guess: " << display << std::endl;
            if (display == secretWord) {
                int score = guesses * std::set<char>(secretWord.begin(), secretWord.end()).size();
                std::cout << "Congratulations! You won!" << std::endl;
                std::cout << "Your score: " << score << std::endl;
                break;
            }
        } else {
            if (guess == 'a' || guess == 'e' || guess == 'i' || guess == 'o' || guess == 'u') {
                guesses -= 2;
            } else {
                --guesses;
            }
            std::cout << "Incorrect guess. Guesses left: " << guesses << std::endl;
        }
    }

    if (guesses == 0) {
        std::cout << "Sorry, you lost. The secret word was: " << secretWord << std::endl;
    }

    return 0;
}
