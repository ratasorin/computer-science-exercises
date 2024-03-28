/*
    1. Se dă o mulțime de numere naturale cu valori de la 0 la 1000.
    Se citesc de la intrare diferite valori în intervalul [0,1000],
    să se utilizeze un vector de octeți
    de dimensiune cât mai mică pentru memorarea elementelor mulțimii.

    example: 1, 7, 15, 10

    encoding the numbers we get:
    7        1  15     10
    |        |  |      |
    [1000_0001; 1000_0010; 0000_0000; ...]
*/

#include <fstream>
#define SET_MAX_LENGTH 1000

// we can encode a set of 8 consecutive numbers on a single unsigned int (e.g: [3, 5] -> 0001_0100)
unsigned int number_encoder_batch8[SET_MAX_LENGTH / 8 + 1];

void set_bit(unsigned int &number, unsigned int poz)
{
    number = number | (1 << poz);
}

unsigned int get_bit(const unsigned int &number, unsigned int poz)
{
    return number & (1 << poz);
}

int main()
{
    std::ifstream input("input-set.txt");
    std::ofstream output("output-numbers.txt");

    unsigned int number;

    while (input >> number)
    {
        unsigned int batch_id = number / 8;
        unsigned int position_inside_batch = number % 8;

        unsigned int batch = number_encoder_batch8[batch_id];
        set_bit(batch, position_inside_batch);
    }

    for (unsigned int batch_id = 0; batch_id < SET_MAX_LENGTH / 8 + 1; batch_id++)
    {
        for (unsigned int position_inside_batch = 0; position_inside_batch < 8; position_inside_batch++)
        {
            unsigned int batch = number_encoder_batch8[batch_id];

            // if the bit inside the batch is true, we have a number stored there
            if (get_bit(batch, position_inside_batch))
            {
                unsigned int number = batch_id * 8 + position_inside_batch;
                output << number << " ";
            }
        }
    }

    input.close();
    output.close();
    return 0;
}
