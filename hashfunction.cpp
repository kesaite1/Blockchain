#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include <cstdint>

using namespace std;

static inline uint64_t rotl(uint64_t x, unsigned r) {
    return (x << r) | (x >> (64 - r));
}

void customHash256(const string& input, uint64_t out[4]) {
    // initialize 4 lanes with different seeds
    out[0] = 0x243f6a8885a308d3ULL;
    out[1] = 0x13198a2e03707344ULL;
    out[2] = 0xa4093822299f31d0ULL;
    out[3] = 0x082efa98ec4e6c89ULL;

    for (size_t i = 0; i < input.size(); i++) {
        uint64_t c = (unsigned char)input[i];
        size_t lane = i % 4; // base lane

        // basic lane update
        out[lane] ^= c * 0x100000001b3ULL;  
        out[lane] = rotl(out[lane], (int)((i * 7) % 64));
        out[lane] *= 0xff51afd7ed558ccdULL;
        out[lane] ^= (out[lane] >> 32);

        // cross-lane mixing: affect the next lane too
        size_t other = (lane + 1) % 4;
        out[other] ^= rotl(c + out[lane], (int)((i * 13) % 64));
        out[other] *= 0x9e3779b97f4a7c15ULL;
    }

    // Final avalanche: mix all lanes together
    for (int round = 0; round < 4; ++round) {
        for (int j = 0; j < 4; ++j) {
            uint64_t x = out[j];
            x ^= rotl(out[(j+1)%4], j*17 + round*11);
            x *= 0xc2b2ae3d27d4eb4fULL;
            x ^= (x >> 29);
            out[j] = x;
        }
    }
}


int main()
{
    string input, filename = "text2.txt";
    char choice;
    cout << "Do you want to read from a file (f) or input manually (m)?";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'm') {
        
        cout << "Write the input: ";
        getline(cin, input);
    } else if (choice == 'f')
    {

        ifstream fd (filename);   
       //string content;
    string line;
    while (getline(fd, line)) {      
        input += line + "\n";        
    }

    fd.close();       
        
    }

    uint64_t hash[4];
    customHash256(input, hash);
    
    cout << "Hash: ";
    cout << hex << setfill('0');
    for (int i = 0; i < 4; i++) {
        cout << setw(16) << hash[i];
    }
    cout << endl;

    

    return 0;
}

