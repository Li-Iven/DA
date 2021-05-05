#include <iostream>
#include <cstring>
#include <vector>

const unsigned int WORD_SIZE = 17;

struct TWord {
    std::string Word = "";
    unsigned int WordIndex;
    unsigned int LineIndex;

    TWord() = default;
    TWord(std::string &s, unsigned int wi, unsigned int li) {
        Word = s;
        WordIndex = wi;
        LineIndex = li;
    };
    ~TWord() = default;

    const bool operator==(const TWord &rhs) const {
        for (unsigned int i = 0; i < WORD_SIZE; ++i) 
            if (Word[i] != rhs.Word[i])
                return false;
            else return true;
    }
};

std::vector<unsigned int> ZFunction(const std::vector<TWord> &text) {
    unsigned int TextSize = text.size();
    unsigned int left = 0;
    unsigned int right = 0;
    std::vector<unsigned int> result(TextSize);
    for (unsigned int i = 1; i < TextSize; ++i) { // Проходимся по каждому терму
        if (i <= right) { // Индекс с которого можно начать сравнивать
            result[i] = std::min(result[i-left], right - i);
        }
        while ((result[i] + i < TextSize) && (text[result[i]].Word == text[result[i] + i].Word)) {// Наивный подсчет, если result[i] == 0
            ++result[i];
        }
        if (i + result[i] > right) { // Смещение границы самого правого вхождения
            left = i;
            right = result[i] + i;
        }
    }
    return result;
}

void ToLower(char* str) { // Перевод в нижний регистр символа
    if (*str>='A' and *str<='Z') {
        *str -= 'A'-'a';
    }
}

int main() {

    char c;
    std::string word = "";
    unsigned int PatternSize = 0;
    unsigned int WordNumber = 0;
    unsigned int LineNumber = 1;
    std::vector<TWord> text;

    // считывание паттерна
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (word != "") {
                ++WordNumber;
                text.push_back(TWord(word,WordNumber,0));
                ++PatternSize;
                word = "";
            }
            break;
        }
        else if (c == ' ') {
            if (word != "") {
                ++WordNumber;
                text.push_back(TWord(word,WordNumber,0));
                ++PatternSize;
                word = "";
            }
        }
        else {
            ToLower(&c);
            word += c;
        }
    }
    
    if (PatternSize == 0) return 0;

    std::string x = std::string("$");
    text.push_back(TWord(x,0,0));

    WordNumber = 0;

    // считывание текста
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++WordNumber;
            if (word != "") {
                text.push_back(TWord(word,WordNumber,LineNumber));
                word = "";
            }
            ++LineNumber;
            WordNumber = 0;
        }
        else if (c == ' ') {
            if (word != "") {
                ++WordNumber;
                text.push_back(TWord(word,WordNumber,LineNumber));
                word = "";
            }
        }
        else {
            ToLower(&c);
            word +=c;
        }
    }

    std::vector<unsigned int> Result = ZFunction(text);

    for (int i = 0; i < text.size(); i++) {
        if (Result[i] == PatternSize) std::cout << text[i].LineIndex << ", " << text[i].WordIndex << "\n";
    }
    return 0;
}
