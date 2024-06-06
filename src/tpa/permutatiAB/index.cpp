#include <iostream>
#include <fstream>

std::ifstream fin("permutariab.in");
std::ofstream fout("permutariab.out");


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

    // we have the two sub-arrays sorted arr1 = [...], arr2 = [...] that we need to interleave in ascending order
    int arr1_start = 0, arr1_end = middle - start, arr2_start = 0, arr2_end = end - (middle + 1);
    int sorted_arr_iterator = 0;

    while(arr1_start <= arr1_end && arr2_start <= arr2_end) {
        if(arr1[arr1_start] < arr2[arr2_start]) {
            sorted[sorted_arr_iterator] = arr1[arr1_start];
            arr1_start++; sorted_arr_iterator++;
        }

        if(arr1[arr1_start] >= arr2[arr2_start]) {
            int remaining_elements_in_arr_1 = (arr1_end - arr1_start) + 1;
            inversions = inversions + remaining_elements_in_arr_1;
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

// quick algorithm explanation: https://www.youtube.com/watch?v=Xpv8nzcEWJQ
int main() {
    int n;
    fin >> n;

    int *occurrence_in_A = (int *) malloc(sizeof(int) * n);
    // reading the elements of A:
    int a;
    for(int i = 0; i < n; i++) {
        fin >> a;
        // based on the described algorithm we want to know what is the index "i" where "a" occurs in "A"
        occurrence_in_A[a - 1] = i;
    }

    int *landing_point = (int *) malloc(sizeof(int) * n);
    // reading the elements of B:
    int b;
    for(int i = 0; i < n; i++) {
        fin >> b;
        // let's say A = [3 1 2 4] and B = [1 2 4 3] => landing_point = [2, 3, 4, 1] because: "1" from B should land on index "2" in A, "2" from B should land on index "3" in A, ...
        // sorting landing_points by merge sort show the "shadow movements" that should be applied on B to reach A.
        landing_point[i] = occurrence_in_A[b - 1];
    }

    merge_sort(landing_point, 0, n - 1);
    fout << inversions;
    // memory cleanup
    free(landing_point); free(occurrence_in_A);
}