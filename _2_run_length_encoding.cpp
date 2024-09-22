#include <iostream>
#include <string>
#include <chrono>  // To measure time

using namespace std;
using namespace chrono;  // For time functions

// Compress function (Run-Length Encoding)
string compressString(const string& s) {
    if (s.empty()) {
        return s;  // Handle empty string
    }

    string compressed = "";
    char currentChar = s[0];
    int count = 1;

    // Loop through the string to compress
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] != currentChar) {
            compressed += currentChar + to_string(count);
            currentChar = s[i];
            count = 1;
        } else {
            count++;
        }
    }

    // Append the last character and count
    compressed += currentChar + to_string(count);

    return compressed.length() < s.length() ? compressed : s;  // Return original if no compression
}

// Decompress function
string decompressString(const string& s) {
    if (s.empty()) {
        return s;  // Handle empty string
    }

    string decompressed = "";
    char currentChar = s[0];
    int count = 0;

    // Loop through the compressed string to decompress
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

    // Start timing
    auto start = high_resolution_clock::now();

    // Compress the input string
    string compressedString = compressString(inputString);
    cout << "Compressed string: " << compressedString << endl;

    // Decompress the string back to its original form
    string decompressedString = decompressString(compressedString);
    cout << "Decompressed string: " << decompressedString << endl;

    // End timing
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}
