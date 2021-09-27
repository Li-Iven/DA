#include "BigInteger.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    TBigInteger ZERO(0);

    std::string l, r;
    char op;

    while (std::cin >> l >> r >> op) {
        TBigInteger left(l);
        TBigInteger right(r);

        if (op == '+') {
            std::cout << left + right << "\n";

        } 
        else if (op == '-') {
            if (left < right) {
                std::cout << "Error\n";
            } 
            else {
                std::cout << left - right << "\n";
            }

        } 
        else if (op == '*') {
            std::cout << left * right << "\n";

        } 
        else if (op == '/') {
            if (right == ZERO) {
                std::cout << "Error\n";
            }
            else {
                std::cout << left / right << "\n";
            }

        } 
        else if (op == '^') {
            if (left == ZERO && right == ZERO) {
                std::cout << "Error\n";
            } 
            else {
                std::cout << (left ^ right) << "\n";
            }

        } 
        else if (op == '<') {
            std::cout << (left < right ? "true" : "false") << "\n";

        } 
        else if (op == '>') {
            std::cout << (left > right ? "true" : "false") << "\n";

        } 
        else if (op == '=') {
            std::cout << (left == right ? "true" : "false") << "\n";

        } 
        else {
            std::cout << "Error\n";
        }
    }
}