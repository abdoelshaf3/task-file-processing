#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdint>

using namespace std;

struct DirectoryEntry {
    char name[8];
    char extension[3];
    uint8_t attributes;
    uint8_t reserved[10];
    uint16_t modifiedTime;
    uint16_t modifiedDate;
    uint16_t clusterStart;
    uint32_t size;
};

void parseRootDirectory(const string& imagePath) {
    ifstream image(imagePath, ios::binary);
    if (!image.is_open()) {
        cerr << "Unable to open disk image!" << endl;
        return;
    }

    const int ROOT_DIR_SECTOR = 19;
    const int ENTRY_COUNT = 224;

    image.seekg(ROOT_DIR_SECTOR * 512);

    vector<DirectoryEntry> dirEntries(ENTRY_COUNT);
    image.read(reinterpret_cast<char*>(dirEntries.data()), ENTRY_COUNT * sizeof(DirectoryEntry));

    cout << left << setw(12) << "Name"
         << setw(5) << "Ext"
         << setw(12) << "Size"
         << setw(10) << "Cluster" << endl;

    cout << string(40, '-') << endl;

    for (const auto& entry : dirEntries) {
        if (entry.name[0] == 0x00) break;
        if (static_cast<uint8_t>(entry.name[0]) == 0xE5) continue;

        cout << setw(12) << entry.name
             << setw(5) << entry.extension
             << setw(12) << entry.size
             << setw(10) << entry.clusterStart << endl;
    }

    image.close();
}

int main() {
    string path;
    cout << "Enter path to FAT12 disk image: ";
    getline(cin, path);

    parseRootDirectory(path);
return 0;
}
