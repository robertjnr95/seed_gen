#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>
#include <vector>

// Function to derive a Bitcoin address from a seed phrase
std::string deriveAddressFromSeed(const std::vector<std::string>& seedPhrase);

#endif // CRYPTO_H
