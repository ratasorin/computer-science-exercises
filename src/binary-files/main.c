#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct {
    char *filename;
    FILE *file;
} OPENED_FILE;

enum FILE_OPERATIONS {
    OPEN_FILE,
    CLOSE_FILES
};

FILE *operate_file(const enum FILE_OPERATIONS file_operation, const char *filename, const char *mode, char* error_message) {
    static OPENED_FILE* opened_files;
    static uint32_t opened_files_count = 0;

    if(file_operation == OPEN_FILE) {
        uint32_t i = 0;
        while(i < opened_files_count) {
            if(strcmp(opened_files[i].filename, filename) == 0) {
                free(error_message);
                fseek(opened_files[i].file, 0, SEEK_SET);
                return opened_files[i].file;
            }
            i++;
        }

        FILE *file = NULL;

        if((file = fopen(filename, mode)) == NULL) {
            perror("The error by errno");
            fputs(error_message, stderr);
            free(error_message);
            exit(EXIT_FAILURE);
        }

        opened_files = (OPENED_FILE*) realloc(opened_files, sizeof(OPENED_FILE) * (opened_files_count + 1));
        OPENED_FILE f = {filename, file};
        opened_files[opened_files_count] = f;
        opened_files_count++;

        free(error_message);
        return file;
    }

    // This is a message to close all files queued;
    if(file_operation == CLOSE_FILES) {
        for(uint32_t i = 0; i < opened_files_count; i++) {
            if(fclose(opened_files[i].file) != 0) {
                perror("The error by errno");
                fputs(error_message, stderr);
                exit(EXIT_FAILURE);
            }
        }

        free(opened_files);
        free(error_message);
        return NULL;
    }

    return NULL;
}

char *concatenate(uint32_t argc, ...) {
    char *result = NULL;
    uint32_t size = 0;
    va_list ap;

    va_start(ap, argc);

    uint32_t i = 0;
    while(i < argc) {
        char *str = va_arg(ap, char*);
        size += strlen(str) + 1;
        result = realloc(result, sizeof(char) * size);
        strcat(result, str);
        i++;
    }

    return result;
}

void binary_input_to_hex_file (const char* input_file_name, const char* output_file_name) {
    FILE *input_file = operate_file(OPEN_FILE, input_file_name, "r", concatenate(3, "Cannot open file: ", input_file_name,  "!\n"));
    FILE *output_file = operate_file(OPEN_FILE, output_file_name, "w", concatenate(3, "Cannot write in file: ", output_file_name,  "!\n"));

    int32_t number; 
    while(fread(&number, sizeof(int32_t), 1, input_file) == 1) {
        char hex_number[20];
        sprintf(hex_number, "%x ", number);
        fwrite(hex_number, sizeof(char), strlen(hex_number), output_file);
    }

}

typedef struct {
    int32_t* elements;
    uint64_t size;
} VECTOR;

VECTOR binary_input_to_array (const char* input_file_name) {
    FILE *input_file = operate_file(OPEN_FILE, input_file_name, "r", concatenate(3, "There is no file: ", input_file_name, " in the working directory!\n"));

    const uint8_t CHUNCK = 200;
    uint64_t size = 0;
    int32_t *arr = malloc(CHUNCK * sizeof(int32_t));
    int32_t number; 
    while(fread(&number, sizeof(int32_t), 1, input_file) == 1) {
        if(size && size % CHUNCK == 0) {
            arr = realloc(arr, (CHUNCK + size) * sizeof(int32_t));
            if(arr == NULL) {
                perror("The official error");
                fprintf(stderr, "No memory left for reallocation of integer array!\n");
                exit(EXIT_FAILURE);
            }
        }
        arr[size] = number;
        size++;
    }

    VECTOR v = {arr, size};
    return v;
}

void __attribute__ ((destructor))  dtor() { operate_file(CLOSE_FILES, "", "", malloc(1 * sizeof(char))); }

int main(int argc, char** argv) {
    if(argc != 3) {
        fprintf(stderr, "Incorect number of arguments. Please provide the input file and an output location!\n i.e: ./main integers.bin integers.out\n");
        exit(EXIT_FAILURE);
    }

    const char* input_file_name = argv[1];
    const char* output_file_name = argv[2];

    binary_input_to_hex_file(input_file_name, output_file_name);
    VECTOR v = binary_input_to_array(input_file_name);

    free(v.elements);
    return 0;
}