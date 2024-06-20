#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string decryptVigenere(const string& text, const string& key);
string generateKey(const string& text, const string& key);
string readKeyFromFile(const string& filename);

int main() {
    string text;
    string keyFilename = "key.txt";
    string key = readKeyFromFile(keyFilename);

    if (key.empty()) {
        cerr << "Key file is empty or not found." << endl;
        return 1;
    }

    cout << "Enter the ciphertext: ";
    getline(cin, text);
    
    string decryptedText = decryptVigenere(text, key);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}

string generateKey(const string& text, const string& key) {
    string keyGenerated = key;
    while (keyGenerated.length() < text.length()) {
        keyGenerated += key;
    }
    return keyGenerated.substr(0, text.length());
}

string decryptVigenere(const string& text, const string& key) {
    string keyGenerated = generateKey(text, key);
    string plainText = "";
    
    for (size_t i = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char baseKey = isupper(keyGenerated[i]) ? 'A' : 'a';
            plainText += (text[i] -base + baseKey - keyGenerated[i] + 26) % 26 + base;
        } else {
            plainText += text[i];
        }
    }
    return plainText;
}

string readKeyFromFile(const string& filename) {
    ifstream file(filename);
    string key;
    if (file.is_open()) {
        getline(file, key);
        file.close();
    }
    return key;
}

