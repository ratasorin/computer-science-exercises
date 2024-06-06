rm -rf ./dist;
mkdir dist;
g++ -Wall -o ./dist/main.exe ./index.cpp -l stdc++;
./dist/main.exe;