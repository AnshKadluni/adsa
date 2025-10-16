#include <bits/stdc++.h>

using namespace std;

class Hashmap {
    private:
        string table[26];
    public:
        Hashmap() {
            for (int i = 0; i < 26; i++) table[i] = "never used";
        }

        bool search(string key) {
            char hash = key.back() - 97;

            for (int i = 0; i < 26; ++i) {
                if (table[(hash+i)%26] == key) return true;
                if (table[(hash+i)%26] == "never used") return false;
            }

            return false;
        }
        
        void insert(string key) {
            if (search(key)) return;
            
            int hash = key.back()-97;
            for (int i = 0; i < 26; ++i) {
                if (table[(hash+i)%26] == "never used" || table[(hash+i)%26] == "tombstone") {
                    table[(hash+i)%26] = key;
                    return;
                }
            }
        }

        void deletion(string key) {
            char hash = key.back() - 97;

            for (int i = 0; i < 26; ++i) {
                if (table[(hash+i)%26] == key) {
                    table[(hash+i)%26] = "tombstone";
                }
                if (table[(hash+i)%26] == "never used") return;
            }
        }

        void printTable() {
            for (int i = 0; i < 26; ++i) {
                if (table[i] != "never used" && table[i] != "tombstone") {
                    cout << table[i] << ' ';
                }
            }
            cout << endl;
        }
};

int main(void) {

    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;

    Hashmap H;

    while (ss >> token) {
        char opp = token[0];
        string val = token.substr(1);

        if (opp == 'A') {
            H.insert(val);
        } else {
            H.deletion(val);
        }
    }

    H.printTable();

    return 0;
}