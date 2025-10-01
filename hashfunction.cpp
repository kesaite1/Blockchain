#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    string input;
    int sum = 0;
    cout << "Write the input: ";
    getline(cin, input);

    unsigned char hash[32] = {0};

    for (int i=0; i<input.size(); i++)
    {
        hash[i % 32] = (hash[i % 32] + input[i]) % 256;

    }

    cout << "Hash: ";
    for (int i = 0; i < 32; i++) {

    cout << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    cout << endl;
    

    return 0;
}

