#include "BigInteger.hpp"

TBigInteger ZERO("0");
TBigInteger ONE("1");
TBigInteger TWO("2");

TBigInteger::TBigInteger(int value) {
    if (value == 0) {
        digits.push_back(0);
    } else {
        for (int i = value; i > 0; i /= BASE) {
            digits.push_back(i % BASE);
        }
    }
}

TBigInteger::TBigInteger(const std::string &value) {
    for (int i = value.length(); i > 0; i -= DIGIT_LENGTH) {
        if(i < DIGIT_LENGTH) {
            digits.push_back(atoi(value.substr(0, i).c_str()));
        } 
        else {
            digits.push_back(atoi(value.substr(i - DIGIT_LENGTH, DIGIT_LENGTH).c_str()));;
        }
    }
    RemoveLeadingZeros();
}

void TBigInteger::RemoveLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

int TBigInteger::GetDigit(size_t id) const {
    if (id >= digits.size()) {
        return 0;
    }
    return digits[id];
}

bool TBigInteger::operator<(TBigInteger& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (int i = digits.size() - 1; i > (-1); --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool TBigInteger::operator==(TBigInteger& other) const {
   // так как у нас нет ведущих нулей, то в числах должно быть одинаковое количество цифр (разрядов)
    if (digits.size() != other.digits.size()) {
        return false;
    }

    // если предыдущее усл. не сработало, значит числа одинаковой длины
    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }

    // если не сработали ве пред. усл., значит числа равны
    return true;
}

bool TBigInteger::operator>(TBigInteger& other) const {
    return !(*this < other || *this == other);
}

TBigInteger TBigInteger::operator+(const TBigInteger& other) {
    int flag = 0; // флаг переноса предыдущего разряда
    size_t newSize = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < newSize || flag != 0; ++i) {
        if (i == digits.size()) {
            digits.push_back(0);
        }
        if (i < other.digits.size()) {
            digits[i] += flag + other.digits[i];
        }
        else {
            digits[i] += flag;
        }
        flag = (digits[i] >= BASE);
        if (flag != 0) {
            digits[i] -= BASE;
        }
    }
    return *this;
}

TBigInteger TBigInteger::operator-(const TBigInteger& other) {
    int flag = 0; // флаг переноса предыдущего разряда
    for (size_t i = 0; i < other.digits.size() || flag != 0; ++i) {
        if (i < other.digits.size()) {
            digits[i] -= flag + other.digits[i];
        }
        else {
            digits[i] -= flag;
        }
        flag = (digits[i] < 0);
        if (flag != 0) {
            digits[i] += BASE;
        }
    }
    RemoveLeadingZeros();
    return *this;
}

TBigInteger TBigInteger::operator*(const TBigInteger& other) const {
    int newSize = digits.size() + other.digits.size();
    TBigInteger mult;
    mult.digits.resize(newSize);

    for (int j = 0; j < other.digits.size(); ++j) {
        if (other.digits[j] == 0) {
            continue;
        }
        int flag = 0;
        for (int i = 0; i < digits.size(); ++i) {
            int tmp = GetDigit(i) * other.GetDigit(j) + flag + mult.GetDigit(i + j);
            flag = tmp / BASE;
            mult.digits[i + j] = tmp % BASE;
        }
        if (flag) {
            mult.digits[j + digits.size()] = flag;
        }
    }
    mult.RemoveLeadingZeros();
    return mult;
}

TBigInteger TBigInteger::operator/(const TBigInteger& other) const {
    TBigInteger result, curRank(0);
    result.digits.resize(digits.size());

    for (int i = digits.size() - 1; i >= 0; --i) {
        curRank.digits.insert(curRank.digits.begin(), digits[i]);
        curRank.RemoveLeadingZeros();

        int x = 0;
        int l = 0;
        int r = BASE;
        while (l <= r) {
            int mid = (l + r) / 2;
            TBigInteger tmp = TBigInteger(mid) * other;
            if (!(tmp > curRank)) {
                x = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        result.digits[i] = x;
        curRank = curRank - other * TBigInteger(x);
    }

    result.RemoveLeadingZeros();
    return result;
}

TBigInteger TBigInteger::operator ^(TBigInteger& deg) {
    TBigInteger res(1);
    while (deg > ZERO) {
        if (deg.GetDigit(0) % 2 == 1) {
            res = res * (*this);
            deg = deg - ONE;
        } else {
            (*this) = (*this) * (*this);
            deg = deg / TWO;
        }
    }
    return res;
}

std::ostream &operator<<(std::ostream &os, TBigInteger bi) {
    os << bi.digits.back();
    for (int i = bi.digits.size() - 2; i >= 0; --i) {
        std::cout << std::setfill('0') << std::setw(DIGIT_LENGTH) << bi.digits[i];
    }
    return os;
}