#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const int DIGIT_LENGTH = 4;
const int BASE = 10000;

class TBigInteger {
private:
    std::vector<int> digits;
    void RemoveLeadingZeros();

public:
    TBigInteger(int value = 0);
    TBigInteger(const std::string &value);
    int GetDigit(size_t id) const;
    bool operator<(TBigInteger &other) const;
    bool operator==(TBigInteger &other) const;
    bool operator>(TBigInteger &other) const;
    TBigInteger operator+(const TBigInteger &other);
    TBigInteger operator-(const TBigInteger &other);
    TBigInteger operator*(const TBigInteger &other) const;
    TBigInteger operator/(const TBigInteger &other) const;
    TBigInteger operator^(TBigInteger& other);
    friend std::ostream &operator<<(std::ostream &os, TBigInteger bi);
};
