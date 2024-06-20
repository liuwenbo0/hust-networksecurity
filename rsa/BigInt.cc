#include "BigInt.hh"
#include <algorithm>
#include <stdexcept>
#include <cmath>

BigInt::BigInt() {}

BigInt::BigInt(int num) {
    if (num == 0) {
        digits.push_back(0);
    } else {
        while (num != 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
}

BigInt::BigInt(const std::string &numStr) {
    for (char c : numStr) {
        if (!isdigit(c)) throw std::invalid_argument("Invalid digit in string");
        digits.push_back(c - '0');
    }
    std::reverse(digits.begin(), digits.end());
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result;
    int carry = 0;
    size_t size = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < size || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

BigInt BigInt::operator-(const BigInt &other) const {
    if (*this < other) throw std::invalid_argument("Negative result in BigInt subtraction");

    BigInt result;
    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) diff -= other.digits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

BigInt BigInt::operator*(const BigInt &other) const {
    BigInt result;
    result.digits.resize(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size(); ++j) {
            int product = digits[i] * other.digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = product % 10;
            carry = product / 10;
        }
        result.digits[i + other.digits.size()] += carry;
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

BigInt BigInt::operator/(const BigInt &other) const {
    if (other == BigInt(0)) throw std::invalid_argument("Division by zero");

    BigInt result, remainder;
    result.digits.resize(digits.size());

    for (int i = digits.size() - 1; i >= 0; --i) {
        remainder.digits.insert(remainder.digits.begin(), digits[i]);

        while (remainder.digits.size() > 1 && remainder.digits.back() == 0) {
            remainder.digits.pop_back();
        }

        int quotient_digit = 0;
        while (remainder >= other) {
            remainder = remainder - other;
            ++quotient_digit;
        }

        result.digits[i] = quotient_digit;
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

BigInt BigInt::operator%(const BigInt &other) const {
    if (other == BigInt(0)) throw std::invalid_argument("Modulo by zero");

    BigInt result = *this;

    while (result >= other) {
        result = result - other;
    }

    return result;
}

bool BigInt::operator==(const BigInt &other) const {
    return digits == other.digits;
}

bool BigInt::operator!=(const BigInt &other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt &other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }

    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }

    return false;
}

bool BigInt::operator<(const BigInt &other) const {
    return other > *this;
}

bool BigInt::operator>=(const BigInt &other) const {
    return !(*this < other);
}

bool BigInt::operator<=(const BigInt &other) const {
    return !(*this > other);
}

BigInt& BigInt::operator=(const BigInt &other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

BigInt& BigInt::operator+=(const BigInt &other) {
    *this = *this + other;
    return *this;
}

BigInt BigInt::pow(const BigInt &exponent, const BigInt &mod) const {
    BigInt base = *this;
    BigInt exp = exponent;
    BigInt result = 1;

    while (exp > 0) {
        if (exp.digits[0] % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }

    return result;
}

std::string BigInt::toString() const {
    std::string numStr;
    for (int digit : digits) {
        numStr += (digit + '0');
    }
    std::reverse(numStr.begin(), numStr.end());
    return numStr;
}

int BigInt::size() {
	return digits.size();
}

std::ostream& operator<<(std::ostream &os, const BigInt &num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream &is, BigInt &num) {
    std::string numStr;
    is >> numStr;
    num = BigInt(numStr);
    return is;
}
