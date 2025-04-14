#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string applyCaesar(const string& input, int key, bool encode = true) {
    string output;
    int actualShift = encode ? key : (26 - key);
    for (char ch : input) {
        if (isalpha(ch)) {
            char limit = isupper(ch) ? 'A' : 'a';
            output += (ch - limit + actualShift) % 26 + limit;
        } else {
            output += ch;
        }
    }
    return output;
}

void handleFile(const string& source, const string& destination, int key, bool encodeMode) {
    ifstream inFile(source);
    if (!inFile.is_open()) {
        cerr << "Can't read from: " << source << endl;
        return;
    }

    ofstream outFile(destination);
    if (!outFile.is_open()) {
        cerr << "Can't write to: " << destination << endl;
        return;
    }

    string contentLine;
    while (getline(inFile, contentLine)) {
        string transformed = applyCaesar(contentLine, key, encodeMode);
        outFile << transformed << endl;
        cout << (encodeMode ? "[ENC] " : "[DEC] ") << transformed << endl;
    }

    inFile.close();
    outFile.close();
}

void showDecryptedPreview(const string& encryptedPath, int key) {
    ifstream file(encryptedPath);
    if (!file.is_open()) {
        cerr << "Failed to load file: " << encryptedPath << endl;
        return;
    }

    string line;
    cout << "\nPreview (Decrypted):\n";
    while (getline(file, line)) {
        cout << applyCaesar(line, key, false) << endl;
    }

    file.close();
}

int main() {
    string filePath;
    int shiftValue = 5;

    cout << "Input file path: ";
    cin >> filePath;

    string outputPath = filePath + ".enc";

    handleFile(filePath, outputPath, shiftValue, true);
    showDecryptedPreview(outputPath, shiftValue);

return 0;
}
