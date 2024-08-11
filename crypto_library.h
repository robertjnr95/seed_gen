#ifndef CRYPTO_LIBRARY_H
#define CRYPTO_LIBRARY_H

#include <vector>
#include <string>

// Function to derive a Bitcoin address from a seed phrase
std::string deriveAddressFromSeed(const std::vector<std::string>& seedPhrase);

#endif // CRYPTO_LIBRARY_H
