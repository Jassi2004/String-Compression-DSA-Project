#include <iostream>
#include <cctype>  // For isdigit
using namespace std;

// Optional: Utility function to check if character is alphabetic (Not used in this version)
bool isAlphabet(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

string compressString(const string& s) {
    if (s.empty()) return s;  // Handle empty string

    string compressed = "";
    char curr_char = s[0];
    int count = 1;
    
    // Loop through the string to compress consecutive characters
    for (int i = 1; i < s.length(); i++) {
        if (s[i] != curr_char) {
            compressed += curr_char;
            if (count > 1) {
                compressed += to_string(count);
            }
            curr_char = s[i];
            count = 1;
        } else {
            count++;
        }
    }
    
    // Add the last character and its count
    compressed += curr_char;
    if (count > 1) {
        compressed += to_string(count);
    }

    // Optional: Return original string if compression doesn't save space
    return compressed.length() < s.length() ? compressed : s;
}

string decompressString(const string& s) {
    if (s.empty()) return s;  // Handle empty string

    string decompressed = "";
    char currentChar = s[0];
    int count = 0;

    // Loop through the compressed string to decompress
    for (int i = 1; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            // Handle multi-digit numbers for count
            count = count * 10 + (s[i] - '0');
        } else {
            // Append `count` occurrences of `currentChar`
            decompressed += (count > 0 ? string(count, currentChar) : string(1, currentChar));
            currentChar = s[i];
            count = 0;
        }
    }
    
    // Handle the last character
    decompressed += (count > 0 ? string(count, currentChar) : string(1, currentChar));
    return decompressed;
}

int main() {
    string s;
    cout << "Enter a string to compress: ";
    cin >> s;

    cout << "Input string:        " << s << endl;

    string compressed = compressString(s);
    cout << "Compressed string:   " << compressed << endl;

    string decompressed = decompressString(compressed);
    cout << "Decompressed string: " << decompressed << endl;

    return 0;
}
