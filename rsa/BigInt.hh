#pragma once
#include <iostream>
#include <vector>
#include <string>

class BigInt {
public:
    BigInt();
    BigInt(int num);
    BigInt(const std::string &numStr);

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator/(const BigInt &other) const;
    BigInt operator%(const BigInt &other) const;

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;

    BigInt& operator=(const BigInt &other);
    BigInt& operator+=(const BigInt &other);

    BigInt pow(const BigInt &exponent, const BigInt &mod) const;

    std::string toString() const;
    int size();

    friend std::ostream& operator<<(std::ostream &os, const BigInt &num);
    friend std::istream& operator>>(std::istream &is, BigInt &num);

private:
    std::vector<int> digits;
};
