#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// given two integers "a" and "b", compute their sum and difference using bitwise operators: &, |, ^, etc. 
uint32_t* compute_sum_and_difference(uint16_t a, uint16_t b) {
    uint16_t a_copy = a, b_copy = b;
    uint32_t* sum_and_difference = (uint32_t*) malloc(2 * sizeof(uint32_t));
    uint32_t carry, sum = 0, difference = 0;
    while(b) {
        sum = a ^ b;
        carry = a & b;
        a = sum;
        b = carry << 1;
    }
    sum_and_difference[0] = a;
    
    a = a_copy, b = b_copy;
     while(b) {
        difference = a ^ b;
        carry = (~a) & b;
        a = difference;
        b = carry << 1;
    }
    sum_and_difference[1] = a;
    
    return sum_and_difference;
}

uint8_t pack_two_numbers (uint8_t a, uint8_t b) {
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

uint8_t* unpack_numbers (uint8_t package) {
    uint8_t* numbers = (uint8_t*) malloc(2 * sizeof(uint8_t));
    uint8_t package_copy = package;

    // if the package is: 0101 1110 => the first number is 0000 0101
    // move 0101 1110 four bits to the right => 0000 0101 
    package = package >> 4;
    numbers[0] = package;
    
    package = package_copy;

    // if the package is: 0101 1110 => the second number is 0000 1110
    // move 0101 1110 four bits to the left => 1110 0000
    package = package << 4;
    // move 1110 0000 four bits to the right => 0000 1110
    package = package >> 4;
    numbers[1] = package;

    return numbers;
}

int main () {
    uint32_t* sum_and_difference = compute_sum_and_difference(100, 50);
    
    printf("%d %d\n", sum_and_difference[0], sum_and_difference[1]); // should print 150 and 50

    uint8_t packed_numbers = pack_two_numbers(9, 15);
    if(packed_numbers == '\0') return 0;
    
    printf("The package is: %hu\n", packed_numbers);

    uint8_t* numbers = unpack_numbers(packed_numbers);
    printf("The first number was: %hu\n The second number was: %hu\n", numbers[0], numbers[1]);
}