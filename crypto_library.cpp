#include "crypto.h"
#include <bitcoin/bitcoin.hpp>  // You may need to install the Bitcoin library

// Function to derive a Bitcoin address from a seed phrase
std::string deriveAddressFromSeed(const std::vector<std::string>& seedPhrase) {
    // Combine the seed phrase into a single string
    std::string seed;
    for (const auto& word : seedPhrase) {
        seed += word + " ";
    }
    seed = seed.substr(0, seed.size() - 1); // Remove the trailing space

    // Derive the private key from the seed phrase
    bc::ec_secret secret;
    bc::data_chunk seedData = bc::to_chunk(bc::word_list(seed));
    if (!bc::decode_base16(secret, seedData)) {
        return "";  // Failed to decode seed phrase
    }

    // Derive the Bitcoin address from the private key
    bc::wallet::ec_private privateKey(secret, bc::wallet::ec_private::mainnet_p2kh);
    return privateKey.to_payment_address().encoded();
}
