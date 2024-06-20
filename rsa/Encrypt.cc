// Encrypt.cpp
#include "RSA.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

// Function to split a string into chunks of a specific size
std::vector<std::string> chunkMessage(const std::string& message, int chunkSize) {
    std::vector<std::string> chunks;
    for (size_t i = 0; i < message.size(); i += chunkSize) {
        chunks.push_back(message.substr(i, chunkSize));
    }
    return chunks;
}

int main() {
    RSA rsa;
    std::cout << "Enter your option: [0-1]" << std::endl << "0. Load RSA key from file           1. Generate new RSA key" << std::endl;
    int op;
    std::cin >> op;
    while(op) {
        try {
            std::cout << "Please enter p, q and e!" << std::endl;
            int p, q, e;
            std::cin >> p >> q >> e;
            rsa.generateKeys(BigInt(p), BigInt(q), BigInt(e));
            rsa.saveKeys("public.key", "private.key");
            break;
        }
        catch (const std::exception &ex) {
            std::cerr << "An error occurred: " << ex.what() << std::endl;
            std::cerr << "Please try again." << std::endl;
        }
        catch (...) {
            std::cerr << "An unknown error occurred." << std::endl;
            std::cerr << "Please try again." << std::endl;
        }
    }
    getchar();  // Consume the newline character left by the previous input
    rsa.loadKeys("public.key", "private.key");

    std::string message;
    std::cout << "Enter message to encrypt: ";
    std::getline(std::cin, message);

    // Determine maximum chunk size based on modulus size
    int maxChunkSize = rsa.getModulus().size() - 1;

    // Split the message into chunks
    std::vector<std::string> chunks = chunkMessage(message, maxChunkSize);

    // Encrypt each chunk
    std::string encryptedMessage;
    for (const auto& chunk : chunks) {
        encryptedMessage += rsa.encrypt(chunk, rsa.getPublicKey(), rsa.getModulus()) + " ";
    }

    std::ofstream outFile("encrypted.txt");
    outFile << encryptedMessage;
    outFile.close();

    std::cout << "Message encrypted and saved to encrypted.txt" << std::endl;

    return 0;
}

