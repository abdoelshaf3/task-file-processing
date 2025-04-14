#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

const size_t CHUNK_SIZE = 4096;

void basicRead(const string& path) {
    ifstream file(path, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    char ch;
    auto start = high_resolution_clock::now();

    while (file.get(ch)) {}

    auto end = high_resolution_clock::now();
    cout << "Read without buffer: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;

    file.close();
}

void bufferedRead(const string& path) {
    ifstream file(path, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<char> buffer(CHUNK_SIZE);
    auto start = high_resolution_clock::now();

    while (file.read(buffer.data(), buffer.size())) {}

    auto end = high_resolution_clock::now();
    cout << "Read with buffer: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms" << endl;

    file.close();
}

int main() {
    string path;
    cout << "Enter file path: ";
    getline(cin, path);

    basicRead(path);
    bufferedRead(path);

return 0;
}
