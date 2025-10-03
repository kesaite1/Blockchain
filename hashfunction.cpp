#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include <cstdint>
#include <random>
#include <filesystem>

using namespace std;

/*char randomChar(mt19937 &gen) {
    const string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    uniform_int_distribution<> dist(0, (int)chars.size() - 1);
    return chars[dist(gen)];
}*/

static inline uint64_t rotl(uint64_t x, unsigned r) {
    return (x << r) | (x >> (64 - r));
}

void customHash256(const string& input, uint64_t out[4]) {
    
    out[0] = 0x123;
    out[1] = 0x0FEDCBA987654321;
    out[2] = 0xAAAAAAAA55555555;
    out[3] = 0xFFFFFFFF00000000;

    for (size_t i = 0; i < input.size(); i++) {
        uint64_t c = (unsigned char)input[i];
        size_t lane = i % 4; 

        
        out[lane] ^= c * 0x100000001b3ULL;  
        out[lane] = rotl(out[lane], (int)((i * 7) % 64));
        out[lane] *= 0xff51afd7ed558ccdULL;
        out[lane] ^= (out[lane] >> 32);

        
        size_t other = (lane + 1) % 4;
        out[other] ^= rotl(c + out[lane], (int)((i * 13) % 64));
        out[other] *= 0x9e3779b97f4a7c15ULL;
    }

    
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
    string input, filename = "testiniaiFailai/random1.txt";
    char choice;
    size_t kiek = 0;

   /* // Generatorius
    random_device rd;
    mt19937 gen(rd());

    {
        ofstream out("testiniaiFailai/random1.txt");
        for (int i = 0; i < 1100; i++) {
            out << randomChar(gen);
        }
    }

    string randomText;
    randomText.reserve(1100);
    for (int i = 0; i < 1100; i++) {
        randomText.push_back(randomChar(gen));
    }

    {
        ofstream("testiniaiFailai/random2.txt") << randomText;
    }

    // Modifikuojam vidurinį simbolį
    int mid = (int)randomText.size() / 2;
    if (randomText[mid] != 'X')
        randomText[mid] = 'X';
    else
        randomText[mid] = 'Y';

    {
        ofstream("testiniaiFailai/random2_mod.txt") << randomText;
    }*/

    cout << "Do you want to read from a file (f) or input manually (m)?";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'm') {
        
        cout << "Write the input: ";
        getline(cin, input);
    } else if (choice == 'f')
    {

        ifstream fd (filename);   
       
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

