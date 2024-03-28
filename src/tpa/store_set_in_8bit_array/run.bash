rm -rf ./dist;
mkdir dist;
gcc -Wall -o ./dist/main ./index.cpp -l stdc++;
./dist/main;