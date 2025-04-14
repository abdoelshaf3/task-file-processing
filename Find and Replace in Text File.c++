#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void replaceTextInFile(const string& path, const string& target, const string& replacement) {
    ifstream input(path);
    if (!input.is_open()) {
        cerr << "Failed to open input file." << endl;
        return;
    }

    stringstream ss;
    ss << input.rdbuf();
    string data = ss.str();
    input.close();

    size_t index = 0;
    while ((index = data.find(target, index)) != string::npos) {
        data.replace(index, target.size(), replacement);
        index += replacement.size();
    }

    ofstream output(path);
    if (!output.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    output << data;
    output.close();

    cout << "Text replaced successfully." << endl;
}

int main() {
    string file, wordToFind, wordToInsert;
    cout << "File path: ";
    cin >> file;
    cout << "Word to find: ";
    cin >> wordToFind;
    cout << "Word to insert: ";
    cin >> wordToInsert;

    replaceTextInFile(file, wordToFind, wordToInsert);

return 0;
}
