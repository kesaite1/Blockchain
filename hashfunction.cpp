#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

int main()
{
    string input, filename = "konstitucija.txt";
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

    unsigned char hash[32] = {0};

    for (int i=0; i<input.size(); i++)
    {
        unsigned char c = input[i];
        unsigned char rotated = (c << (i % 8)) | (c >> (8 - (i % 8)));
        hash[i % 32] = (hash[i % 32] + input[i]) % 256;

        int pos = (i * 7 + c) % 32;
        hash[pos] = (hash[pos] ^ rotated);
        hash[(pos + 13) % 32] = (hash[(pos + 13) % 32] + c * 31) % 256;

    }

    cout << "Hash: ";
    for (int i = 0; i < 32; i++) {

    cout << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    cout << endl;
    

    return 0;
}

