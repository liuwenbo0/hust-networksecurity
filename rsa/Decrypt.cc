// Decrypt.cpp
#include "RSA.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Function to split a string by a delimiter
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    RSA rsa;
    rsa.loadKeys("public.key", "private.key");

    std::ifstream inFile("encrypted.txt");
    std::string encryptedMessage((std::istreambuf_iterator<char>(inFile)),
                                 std::istreambuf_iterator<char>());

    // Split the encrypted message into chunks
    std::vector<std::string> encryptedChunks = splitString(encryptedMessage, ' ');

    // Decrypt each chunk
    std::string decryptedMessage;
    for (const auto& chunk : encryptedChunks) {
        if (!chunk.empty()) {
            decryptedMessage += rsa.decrypt(chunk, rsa.getPrivateKey(), rsa.getModulus());
        }
    }

    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    return 0;
}

