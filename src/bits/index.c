#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// given two integers "a" and "b", compute their sum and difference using bitwise operators: &, |, ^, etc. 
uint32_t* ComputeSumAndDifference(uint16_t a, uint16_t b) {
    uint16_t aCopy = a, bCopy = b;
    uint32_t* sumAndDifference = (uint32_t*) malloc(2 * sizeof(uint32_t));
    uint32_t carry, sum = 0, difference = 0;
    while(b) {
        sum = a ^ b;
        carry = a & b;
        a = sum;
        b = carry << 1;
    }
    sumAndDifference[0] = a;
    
    a = aCopy, b = bCopy;
     while(b) {
        difference = a ^ b;
        carry = (~a) & b;
        a = difference;
        b = carry << 1;
    }
    sumAndDifference[1] = a;
    
    return sumAndDifference;
}

uint8_t PackTwoNumbers (uint8_t a, uint8_t b) {
    if(a > 15 || b > 15) {
        printf("The numbers should be below 15!\n");
        return '\0';
    }
    uint8_t package = 0;
    package = a;
    package = package << 4;
    package = package | b;

    return package;
}

uint8_t* UnpackNumbers (uint8_t package) {
    uint8_t* numbers = (uint8_t*) malloc(2 * sizeof(uint8_t));
    uint8_t packageCopy = package;

    // if the package is: 0101 1110 => the first number is 0000 0101
    // move 0101 1110 four bits to the right => 0000 0101 
    package = package >> 4;
    numbers[0] = package;
    
    package = packageCopy;

    // if the package is: 0101 1110 => the second number is 0000 1110
    // move 0101 1110 four bits to the left => 1110 0000
    package = package << 4;
    // move 1110 0000 four bits to the right => 0000 1110
    package = package >> 4;
    numbers[1] = package;

    return numbers;
}

char FindSign (int n) {
    
}

int main () {
    uint32_t* sumAndDifference = ComputeSumAndDifference(100, 50);
    
    printf("%d %d\n", sumAndDifference[0], sumAndDifference[1]); // should print 150 and 50

    uint8_t packedNumber = PackTwoNumbers(9, 15);
    if(packedNumber == '\0') return 0;
    
    printf("The package is: %hu\n", packedNumber);

    uint8_t* numbers = UnpackNumbers(packedNumber);
    printf("The first number was: %hu\n The second number was: %hu\n", numbers[0], numbers[1]);
}