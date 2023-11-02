#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

const int STIRNG_MAX_SIZE = 20;

ofstream fout ("resources/output.txt");
ifstream fin ("resources/input.txt");


int main() {
    string x, y;
    fin >> x >> y;

    array<array<int, STIRNG_MAX_SIZE>, STIRNG_MAX_SIZE> lcs = {};

    int xLenght = x.length(), yLenght = y.length();

    for(int i = 0; i < xLenght; i++) {
        for(int j = 0; j < yLenght; j++) {
            if(i == 0 || j == 0) {
                if(x[i] == y[j]) lcs[i][j] = 1;
            }

            if(i != 0 && j != 0) {
                if(x[i] == y[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
            }
        }
    }

    fout << lcs[xLenght - 1][yLenght - 1];

    return 0;
}