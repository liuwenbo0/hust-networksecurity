#ifndef RSA_HH
#define RSA_HH

#include "BigInt.hh"
#include <string>
#include <fstream>

class RSA {
public:
    RSA();

    void generateKeys(const BigInt &p, const BigInt &q, const BigInt &e);
    BigInt gcd(const BigInt &a, const BigInt &b);
    BigInt modInverse(const BigInt &a, const BigInt &m);

    std::string encrypt(const std::string &message, const BigInt &e, const BigInt &n);
    std::string decrypt(const std::string &cipher, const BigInt &d, const BigInt &n);

    void saveKeys(const std::string &pubKeyFile, const std::string &privKeyFile);
    void loadKeys(const std::string &pubKeyFile, const std::string &privKeyFile);
    BigInt getModulus() const;
    BigInt getPublicKey() const;
    BigInt getPrivateKey() const;

private:
    BigInt modulus;
    BigInt publicKey;
    BigInt privateKey;
};

#endif

