#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

// Кодирование
void Encoding() {
    // Начальный словарь
   unordered_map<string, int> Dictionary;
    for (int i = 0; i < 26; ++i) {
        string s;
        s.push_back('a' + i);
        Dictionary.insert(pair<string, int>(s, i));
        Dictionary[s] = i;
    }
    Dictionary.insert(pair<string, int>("EOF", 26));

    char c;
    string word;
    while((c = getchar())) {
        string tmp = word;
        word += c;
        if(c == EOF) {
            word = tmp;
            cout << Dictionary[tmp] << "\n";
            break;
        }
        if(Dictionary.count(word) == 0) {
            cout << Dictionary[tmp] << " ";
            int size = Dictionary.size();
            Dictionary.insert(pair<string, int>(word, size));
            word = c;
        }
    }
}

// Декодирование
void Decoding() {
    // Словарь для декодирования
    unordered_map<int, string> CodeDictionary;
    for (int i = 0; i < 26; ++i) {
        string s;
        s.push_back('a' + i);
        CodeDictionary.insert(pair<int, string>(i, s));
        CodeDictionary[i] = s;
    }
    CodeDictionary.insert(pair<int, string>(26, "EOF"));

    int code;
    string pattern;
    while(cin >> code) {
        string tmp = pattern;
        if(CodeDictionary.count(code) != 0) {
            pattern = CodeDictionary[code];

            if(pattern == "EOF") {
                cout << "\n";
                break;
            }

            cout  << pattern;
            if(tmp != "") {
                pattern = tmp + pattern.front();
                int size = CodeDictionary.size();
                CodeDictionary.insert(pair<int, string>(size, pattern));
                pattern = CodeDictionary[code];
            }
        }
        else {
            pattern = tmp + tmp.front();
            int size = CodeDictionary.size();
            CodeDictionary.insert(pair<int, string>(size, pattern));
            cout  << pattern;
        }
    }
}

int main() {

    string command;
    getline(cin, command);
    if(command == "compress") Encoding();
    else if(command == "decompress") Decoding();
    else cout << "Incorrect command!";

    return 0;
}