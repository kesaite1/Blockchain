#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include <cstdint>
#include <random>
#include <filesystem>
#include <sstream>

using namespace std;

/*char randomChar(mt19937 &gen) {
    const string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    uniform_int_distribution<> dist(0, (int)chars.size() - 1);
    return chars[dist(gen)];
}*/

string hashToHex(const uint64_t h[4]) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < 4; i++) {
        oss << std::setw(16) << h[i];
    }
    return oss.str();
}

int countDifferentHex(const uint64_t h1[4], const uint64_t h2[4]) {
    std::string s1 = hashToHex(h1);
    std::string s2 = hashToHex(h2);
    int diff = 0;
    for (size_t i = 0; i < s1.size(); i++) {
        if (s1[i] != s2[i]) diff++;
    }
    return diff;
}

string randomString(size_t length) {
    static const string chars =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static mt19937 gen(random_device{}());
    static uniform_int_distribution<> dist(0, chars.size() - 1);

    string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i)
        s += chars[dist(gen)];
    return s;
}

bool hashesEqual(const uint64_t h1[4], const uint64_t h2[4]) {
    for (int i = 0; i < 4; ++i)
        if (h1[i] != h2[i]) return false;
    return true;
}

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

int countDifferentBits(const uint64_t h1[4], const uint64_t h2[4]) {
    int diff = 0;
    for (int i = 0; i < 4; i++) {
        uint64_t x = h1[i] ^ h2[i]; // XOR parodo, kur bitai skiriasi
        diff += __builtin_popcountll(x); // suskaičiuoja 1 bitus
    }
    return diff;
}



int main()
{
    string input, filename = "testiniaiFailai/empty.txt";
    char choice;
    size_t kiek = 0, lengths[] = {10, 100, 500, 1000};
    const int PAIRS = 100000;
    const int LEN = 100;

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

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> charDist(32, 126); // ASCII simboliai

    int minBits = std::numeric_limits<int>::max();
    int maxBits = 0;
    long long sumBits = 0;

    int minHex = std::numeric_limits<int>::max();
    int maxHex = 0;
    long long sumHex = 0;

    for (int i = 0; i < PAIRS; i++) {
        // sugeneruojam atsitiktinį string
        std::string s1;
        s1.reserve(LEN);
        for (int j = 0; j < LEN; j++)
            s1 += static_cast<char>(charDist(gen));

        // kopija su vienu pakeistu simboliu
        std::string s2 = s1;
        int pos = LEN / 2; // keičiam vidurinį
        char newChar;
        do {
            newChar = static_cast<char>(charDist(gen));
        } while (newChar == s1[pos]);
        s2[pos] = newChar;

        uint64_t h1[4], h2[4];
        customHash256(s1, h1);
        customHash256(s2, h2);

        // bitų skirtumas
        int bitDiff = countDifferentBits(h1, h2);
        minBits = std::min(minBits, bitDiff);
        maxBits = std::max(maxBits, bitDiff);
        sumBits += bitDiff;

        // hex skirtumas
        int hexDiff = countDifferentHex(h1, h2);
        minHex = std::min(minHex, hexDiff);
        maxHex = std::max(maxHex, hexDiff);
        sumHex += hexDiff;
    }

    std::cout << "Bit level differences:\n";
    std::cout << "  Min: " << minBits << "\n";
    std::cout << "  Max: " << maxBits << "\n";
    std::cout << "  Avg: " << (double)sumBits / PAIRS << "\n";

    std::cout << "Hex level differences:\n";
    std::cout << "  Min: " << minHex << "\n";
    std::cout << "  Max: " << maxHex << "\n";
    std::cout << "  Avg: " << (double)sumHex / PAIRS << "\n";



    //size_t lengths[] = {10, 100, 500, 1000};

    /*for (size_t len : lengths) {
        size_t collisions = 0;

        for (size_t i = 0; i < 100000; ++i) {
            string s1 = randomString(len);
            string s2 = randomString(len);

            uint64_t h1[4], h2[4];
            customHash256(s1, h1);
            customHash256(s2, h2);

            if (hashesEqual(h1, h2))
                ++collisions;
        }

        cout << "Length " << len << ": " << collisions
                  << " collisions out of 100000 pairs\n";
    }*/

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

