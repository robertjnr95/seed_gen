#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <json/json.h>  // You may need to install the JSON library
#include <csv-parser/csv.h>  // You may need to install the CSV library (e.g., `csv-parser`)

// Function to read a plain text file with one word per line
std::vector<std::string> readPlainTextFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    return words;
}

// Function to read a file with space-separated words
std::vector<std::string> readSpaceSeparatedFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
    }
    return words;
}

// Function to read a CSV file
std::vector<std::string> readCSVFile(const std::string& filename) {
    std::vector<std::string> words;
    io::CSVReader<1> csv(filename);
    std::string word;
    while (csv.read_row(word)) {
        words.push_back(word);
    }
    return words;
}

// Function to read a JSON file
std::vector<std::string> readJSONFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    Json::Value root;
    file >> root;
    for (const auto& word : root["words"]) {
        words.push_back(word.asString());
    }
    return words;
}

// Function to determine file format and read accordingly
std::vector<std::string> readWordlist(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file.");
    }

    std::string line;
    std::getline(file, line);
    file.close();

    if (line.find_first_of(",") != std::string::npos) {
        return readCSVFile(filename);
    } else if (line.find_first_of("{") != std::string::npos) {
        return readJSONFile(filename);
    } else if (line.find_first_of(" ") != std::string::npos) {
        return readSpaceSeparatedFile(filename);
    } else {
        return readPlainTextFile(filename);
    }
}

// Function to check if a seed phrase generates the given wallet address
bool checkSeedPhrase(const std::vector<std::string>& seedPhrase, const std::string& walletAddress) {
    std::string derivedAddress = deriveAddressFromSeed(seedPhrase);
    return derivedAddress == walletAddress;
}

// Function to generate all combinations of seed phrases from the wordlist
void generateCombinations(const std::vector<std::string>& wordlist, int seedLength, const std::string& walletAddress) {
    std::vector<std::string> combination(seedLength);

    // Use indices to generate combinations
    std::vector<int> indices(seedLength, 0);
    long long totalCombinations = 1;
    for (int i = 0; i < seedLength; ++i) {
        totalCombinations *= wordlist.size();
    }

    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long lastCount = 0;
    auto lastTime = startTime;

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

        // Update statistics
        ++count;
        if (count % 10000 == 0) { // Update stats every 10,000 combinations
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = now - startTime;
            std::chrono::duration<double> interval = now - lastTime;
            double cps = (count - lastCount) / interval.count(); // Combinations per second
            lastCount = count;
            lastTime = now;

            // ETA Calculation
            double totalTime = elapsed.count();
            double estimatedTotalTime = totalTime * (totalCombinations / count);
            double eta = estimatedTotalTime - totalTime;

            std::cout << std::fixed << std::setprecision(2)
                      << "Processed: " << count << " combinations | "
                      << "Speed: " << cps << " cps | "
                      << "Elapsed Time: " << totalTime << " s | "
                      << "ETA: " << eta << " s\r";
            std::cout.flush();
        }
    }

    std::cout << "No matching seed phrase found." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <wallet_address> <wordlist_file> [seed_length]" << std::endl;
        return 1;
    }

    std::string walletAddress = argv[1];
    std::string wordlistFile = argv[2];
    int seedLength = (argc == 4) ? std::stoi(argv[3]) : 12; // Default seed length to 12 if not provided

    std::vector<std::string> wordlist;

    try {
        wordlist = readWordlist(wordlistFile);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error reading wordlist: " << e.what() << std::endl;
        return 1;
    }

    if (wordlist.size() < seedLength) {
        std::cerr << "Wordlist does not contain enough words for the specified seed length." << std::endl;
        return 1;
    }

    generateCombinations(wordlist, seedLength, walletAddress);

    return 0;
}
