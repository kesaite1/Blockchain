// measure_hash.cpp
#include <bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

// --- your customHash256 (kept same as you provided) ---
static inline u64 rotl(u64 x, unsigned r) {
    return (x << r) | (x >> (64 - r));
}

void customHash256(const string& input, u64 out[4]) {
    out[0] = 0x123;
    out[1] = 0x0FEDCBA987654321ULL;
    out[2] = 0xAAAAAAAA55555555ULL;
    out[3] = 0xFFFFFFFF00000000ULL;

    for (size_t i = 0; i < input.size(); i++) {
        u64 c = (unsigned char)input[i];
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
            u64 x = out[j];
            x ^= rotl(out[(j+1)%4], j*17 + round*11);
            x *= 0xc2b2ae3d27d4eb4fULL;
            x ^= (x >> 29);
            out[j] = x;
        }
    }
}
// --- end customHash256 ---

int main() {
    const string filename = "testiniaiFailai/konstitucija.txt";
    ios::sync_with_stdio(false);

    // Read all lines
    ifstream fin(filename);
    if (!fin) {
        cerr << "Cannot open file '" << filename << "'. Put it in the program directory.\n";
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();

    if (lines.empty()) {
        cerr << "File has no lines.\n";
        return 1;
    }

    // prepare doubling sequence 1,2,4,... up to lines.size()
    vector<size_t> sizes;
    for (size_t n = 1; n <= lines.size(); n *= 2) sizes.push_back(n);
    if (sizes.back() != lines.size()) sizes.push_back(lines.size()); // ensure final point = total lines

    const int REPEATS = 5; // how many times to repeat each measurement (you can change)
    const string outCsv = "timings.csv";
    ofstream csv(outCsv);
    csv << "lines_count,repeat,elapsed_ms\n";

    cout << "Total lines: " << lines.size() << "\n";
    cout << "Testing sizes: ";
    for (auto s : sizes) cout << s << " ";
    cout << "\nRepeats per size: " << REPEATS << "\n";
    cout << "Writing raw timings to '" << outCsv << "'\n";

    // For each size: build input string (first n lines joined by '\n'), then time customHash256
    for (size_t n : sizes) {
        // Build concatenated input of first n lines (with newline after each original line except maybe last)
        string input;
        // Pre-reserve to speed up
        size_t reserve_hint = 0;
        for (size_t i = 0; i < n; ++i) reserve_hint += lines[i].size() + 1;
        input.reserve(reserve_hint);

        for (size_t i = 0; i < n; ++i) {
            input += lines[i];
            if (i + 1 < n) input += '\n';
        }

        // Warm-up call (optional)
        {
            u64 h[4];
            customHash256(input, h);
        }

        for (int r = 0; r < REPEATS; ++r) {
            auto t0 = chrono::high_resolution_clock::now();
            u64 h[4];
            customHash256(input, h);
            auto t1 = chrono::high_resolution_clock::now();
            double elapsed_ms = chrono::duration<double, milli>(t1 - t0).count();
            csv << n << "," << r << "," << fixed << setprecision(6) << elapsed_ms << "\n";
            cout << "size=" << setw(6) << n << " repeat=" << r << " time=" << elapsed_ms << " ms\n";
        }
    }

    csv.close();
    cout << "Done.\n";
    return 0;
}
