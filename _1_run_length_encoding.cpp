#include <iostream>
#include <string>

using namespace std;

string compressString(const string& s) {
    if (s.empty()) {
        return s; // Handle empty string
    }

    string compressed = "";
    char currentChar = s[0];
    int count = 1;

    for (int i = 1; i < s.length(); ++i) {
        if (s[i] != currentChar) {
            compressed += currentChar + to_string(count);
            currentChar = s[i];
            count = 1;
        } else {
            count++;
        }
    }

    compressed += currentChar + to_string(count);
    return compressed;
}

string decompressString(const string& s) {
    if (s.empty()) {
        return s; // Handle empty string
    }

    string decompressed = "";
    char currentChar = s[0];
    int count = 0;

    for (int i = 1; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            count = count * 10 + (s[i] - '0');
        } else {
            decompressed += string(count, currentChar);
            currentChar = s[i];
            count = 0;
        }
    }

    decompressed += string(count, currentChar);
    return decompressed;
}

int main() {
    string inputString;
    cout << "Enter a string: ";
    getline(cin, inputString);

    string compressedString = compressString(inputString);
    cout << "Compressed string: " << compressedString << endl;

    string decompressedString = decompressString(compressedString);
    cout << "Decompressed string: " << decompressedString << endl;

    return 0;
}