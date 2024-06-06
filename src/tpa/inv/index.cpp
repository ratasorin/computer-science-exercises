#include <fstream>
#include <iostream>

std::ifstream fin("inv.in");
std::ofstream fout("inv.out");

int inversions = 0;
int* merge_sort(int* arr, int start, int end) {
    if(start == end) {
        int* a = (int*) malloc(sizeof(int));
        a[0] = arr[start];
        return a;
    }

    int middle = (start + end)/2;
    int *arr1 = merge_sort(arr, start, middle);
    int *arr2 = merge_sort(arr, middle + 1, end);

    int *sorted = (int *) malloc(sizeof(int) * (end - start + 1));

    // we have the two sub-arrays sorted arr1 = [...], arr2 = [...].
    int arr1_start = 0, arr1_end = middle - start, arr2_start = 0, arr2_end = end - (middle + 1);
    int sorted_arr_iterator = 0;

    while(arr1_start <= arr1_end && arr2_start <= arr2_end) {
        if(arr1[arr1_start] <= arr2[arr2_start]) {
            sorted[sorted_arr_iterator] = arr1[arr1_start];
            arr1_start++; sorted_arr_iterator++;
        }

        if(arr1[arr1_start] > arr2[arr2_start]) {
            int remaining_elements_in_arr_1 = arr1_end - arr1_start + 1;
            // arr2[arr2_start] in less than all the numbers left in arr1, so there are "remaining_elements_in_arr_1" more inversions
            inversions = (inversions + remaining_elements_in_arr_1) % 9917;
            sorted[sorted_arr_iterator] = arr2[arr2_start];
            arr2_start++; sorted_arr_iterator++;
        }
    }


    while (arr1_start <= arr1_end) {
        sorted[sorted_arr_iterator] = arr1[arr1_start];
        arr1_start++; sorted_arr_iterator++;
    }

    while (arr2_start <= arr2_end) {
        sorted[sorted_arr_iterator] = arr2[arr2_start];
        arr2_start++; sorted_arr_iterator++;
    }

    free(arr1);
    free(arr2);
    return sorted;
}

int main () {
    int arr_length = 0;
    fin >> arr_length;

    int *arr = (int*) malloc (sizeof(int) * arr_length);

    for (int i = 0; i < arr_length; i++) 
        fin >> arr[i];

    int *sorted = merge_sort(arr, 0, arr_length - 1);
    
    free(arr); free(sorted);
    
    fout << inversions;
}