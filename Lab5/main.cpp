#include <iostream>
#include "SuffixTree.h"

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string firstString, secondString;
    while (std::cin >> firstString >> secondString) {
        firstString += "#";
        secondString += "$";
        std::string text = firstString + secondString;
        TSuffixTree tree(text, firstString.size());
    }
    
    return 0;
}