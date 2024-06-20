#include "RSA.hh"
#include <iostream>
#include <ctime>

RSA::RSA() = default;

bool isPrime(const BigInt &n) {
    if (n <= BigInt(1)) return false;
    if (n <= BigInt(3)) return true;
    if (n % BigInt(2) == 0 || n % BigInt(3) == 0) return false;
    for (BigInt i = BigInt(5); i * i <= n; i += BigInt(6)) {
        if (n % i == 0 || n % (i + BigInt(2)) == 0) return false;
    }
    return true;
}

void RSA::saveKeys(const std::string &pubKeyFile, const std::string &privKeyFile) {
    std::ofstream pubOut(pubKeyFile);
    pubOut << publicKey << std::endl << modulus;
    pubOut.close();

    std::ofstream privOut(privKeyFile);
    privOut << privateKey << std::endl << modulus;
    privOut.close();
}

void RSA::loadKeys(const std::string &pubKeyFile, const std::string &privKeyFile) {
    std::ifstream pubIn(pubKeyFile);
    pubIn >> publicKey >> modulus;
    pubIn.close();

    std::ifstream privIn(privKeyFile);
    privIn >> privateKey >> modulus;
    privIn.close();
}

void RSA::generateKeys(const BigInt &p, const BigInt &q, const BigInt &e) {
    if (!isPrime(p)) {
        throw std::invalid_argument("p is not a prime number");
    }
    if (!isPrime(q)) {
        throw std::invalid_argument("q is not a prime number");
    }

    modulus = p * q;
    BigInt phi = (p - BigInt(1)) * (q - BigInt(1));

    if (e <= BigInt(1) || e >= phi) {
        throw std::invalid_argument("e must be greater than 1 and less than phi(n)");
    }

    if (gcd(e, phi) != BigInt(1)) {
        throw std::invalid_argument("e is not coprime with phi(n)");
    }

    publicKey = e;
    privateKey = modInverse(publicKey, phi);
}

BigInt RSA::gcd(const BigInt &a, const BigInt &b) {
    if (b == BigInt(0))
        return a;
    else
        return gcd(b, a % b);
}

BigInt RSA::modInverse(const BigInt &a, const BigInt &m) {
    BigInt m0 = m;
    BigInt y = BigInt(0), x = BigInt(1);

    BigInt a_copy = a;
    BigInt m_copy = m;

    if (m == BigInt(1))
        return BigInt(0);

    while (a_copy > BigInt(1)) {
        BigInt q = a_copy / m_copy;
        BigInt t = m_copy;

        m_copy = a_copy % m_copy;
        a_copy = t;
        t = y;

	while(x < q * y) x += m0;
        y = x - q * y;
        
	x = t;
    }

    return x;
}

std::string RSA::encrypt(const std::string &message, const BigInt &e, const BigInt &n) {
    std::string leadingzero;
    for(int i = 0; message[i + 1]; i ++)
	if(message[i] == '0') {
		leadingzero += "0";
		i ++;
	}
	else break;
    BigInt msgInt(message);
    BigInt cipherInt = msgInt.pow(e, n);
    return leadingzero + cipherInt.toString();
}

std::string RSA::decrypt(const std::string &cipher, const BigInt &d, const BigInt &n) {
    std::string leadingzero;
    for(int i = 0; cipher[i + 1]; i ++)
        if(cipher[i] == '0') {
                leadingzero += "0";
                i ++;
        }
        else break;
    BigInt cipherInt(cipher);
    BigInt msgInt = cipherInt.pow(d, n);
    return leadingzero + msgInt.toString();
}

BigInt RSA::getModulus() const {
    return modulus;
}

BigInt RSA::getPublicKey() const {
    return publicKey;
}

BigInt RSA::getPrivateKey() const { 
    return privateKey;
}
