mkdir -p dist
if ! test -f dist/integers.bin; then
    wget http://staff.cs.upt.ro/~valy/pt/integers.bin -P ./dist
fi
gcc -Wall -o ./dist/main main.c
./dist/main ./dist/integers.bin ./dist/integers.out