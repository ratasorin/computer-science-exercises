#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("./resources/input.txt");
ofstream fout("./resources/output.txt");

char* convertToBinary(int n) {
    if(n == 0) {
        char c[50] = {""};
        return c;
    }
    char* rest;
    sprintf(rest, "%d", n%2);
    char* binary = convertToBinary(n/2);

    return strcat(binary, rest);
}


int main (void) {
    int n;
    fin >> n;
    char* nToBinary = convertToBinary(n);
    fout << nToBinary;
    return 0;
}