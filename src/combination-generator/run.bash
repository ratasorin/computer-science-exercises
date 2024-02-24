rm -rf ./dist;
mkdir dist;
gcc -Wall -o ./dist/main ./main.cpp -l stdc++;
./dist/main;