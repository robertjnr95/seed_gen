#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "crypto_library.h"

// Function to check if a seed phrase generates the given wallet address
bool checkSeedPhrase(const std::vector<std::string>& seedPhrase, const std::string& walletAddress) {
    std::string derivedAddress = deriveAddressFromSeed(seedPhrase);
    return derivedAddress == walletAddress;
}

// Function to read the wordlist from a file
std::vector<std::string> readWordlist(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

// Function to generate all combinations of seed phrases from the wordlist
void generateCombinations(const std::vector<std::string>& wordlist, int seedLength, const std::string& walletAddress) {
    std::vector<std::string> combination(seedLength);

    // Use indices to generate combinations
    std::vector<int> indices(seedLength, 0);
    while (true) {
        // Fill the combination vector with words based on current indices
        for (int i = 0; i < seedLength; ++i) {
            combination[i] = wordlist[indices[i]];
        }

        // Check the generated seed phrase
        if (checkSeedPhrase(combination, walletAddress)) {
            std::cout << "Matching seed phrase found: ";
            for (const auto& word : combination) {
                std::cout << word << " ";
            }
            std::cout << std::endl;
            return;
        }

        // Move to the next combination
        int pos = seedLength - 1;
        while (pos >= 0) {
            if (indices[pos] < wordlist.size() - 1) {
                ++indices[pos];
                break;
            } else {
                indices[pos] = 0;
                --pos;
            }
        }
        if (pos < 0) break; // If we finished all combinations
    }

    std::cout << "No matching seed phrase found." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <wordlist.txt> <wallet_address> [seed_length]" << std::endl;
        return 1;
    }

    std::string wordlistFile = argv[1];
    std::string walletAddress = argv[2];
    int seedLength = (argc == 4) ? std::stoi(argv[3]) : 12; // Default seed length to 12 if not provided

    std::vector<std::string> wordlist = readWordlist(wordlistFile);

    if (wordlist.size() < seedLength) {
        std::cerr << "Wordlist does not contain enough words for the specified seed length." << std::endl;
        return 1;
    }

    generateCombinations(wordlist, seedLength, walletAddress);

    return 0;
}
