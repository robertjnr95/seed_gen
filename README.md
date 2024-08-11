**_Seed Phrase Wallet Address Checker_**

**Overview**
This project is a C++ implementation that checks if a given seed phrase can generate a specified Bitcoin wallet address. It takes a wordlist and a target wallet address as input, and optionally allows the user to specify the length of the seed phrase. The program uses cryptographic standards such as BIP-39, BIP-32, and BIP-44 to derive the wallet address from the seed phrase.

**Features**
Seed Phrase Verification: Checks if a seed phrase from a wordlist matches a specified Bitcoin wallet address.
Configurable Seed Length: Allows users to specify the length of the seed phrase (e.g., 12, 15, 18, 21, or 24 words).
Support for Standard Cryptographic Libraries: Integrates with popular cryptographic libraries to handle seed phrase derivation and address generation.

**Dependencies**
C++11 or later: The code is written in C++11 standard, so you'll need a compiler that supports this version or later.
Cryptographic Library: The code uses a cryptographic library (e.g., OpenSSL, Crypto++, or libbitcoin) to handle the implementation of BIP-39, BIP-32, and BIP-44 standards.
Boost Libraries: (Optional) Boost libraries may be required for additional functionality.

**Installation**
Clone the Repository:

git clone https://github.com/roberjnr95/seed-checker.git
cd seed-checker

Install Dependencies:

Install any required libraries (e.g., OpenSSL, Boost).
On Ubuntu, you can install them with:

sudo apt-get install libssl-dev libboost-all-dev

#Build the Project:
Compile the code using make:

make

This will create an executable file named seed_checker.

**Usage**
To use the program, run the seed_checker executable with the following command-line arguments:

./seed_checker <wordlist.txt> <wallet_address> [seed_length]

wordlist.txt: A text file containing a list of words to be used as potential seed phrases.
wallet_address: The target Bitcoin wallet address you want to check against.
seed_length: (Optional) The length of the seed phrase (default is 12).

Example:
./seed_checker wordlist.txt 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa 12

This command will check if any 12-word seed phrase generated from the words in wordlist.txt matches the Bitcoin wallet address 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa.

**Project Structure**-
main.cpp: The main file containing the entry point for the program.
crypto_library.cpp: Contains functions related to seed phrase derivation and address generation.
Makefile: The build configuration file to compile the project.
README.md: This documentation file.

**Contributing**
Contributions are welcome! If you have suggestions or improvements, feel free to fork the repository and submit a pull request.
