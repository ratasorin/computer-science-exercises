#include <chrono>
#include <fstream>
#include <iostream>

std::ifstream fin("rucsac.in");
std::ofstream fout("rucsac.out");

typedef struct object_t {
    int value, weight;
} object;

int compare_greedy (const void* v1, const void* v2) {
    object_t* object1 = (object_t*) v1;
    object_t* object2 = (object_t*) v2;

    if(object1->value > object2->value) return -1;
    else if(object1->value < object2->value) return 1;
    else {
        if(object1->weight <= object2->weight) return 1;
        else return -1;
    }
}

int max_profit_greedy(object_t* objects, int object_count, int max_weight) {
    int weight = 0, profit = 0;
    
    qsort (objects, object_count, sizeof(object_t), compare_greedy);

    int index = 0;
    while(weight < max_weight) {
        if(weight + objects[index].weight > max_weight) return profit;
        else {
            profit = profit + objects[index].value;
            weight = weight + objects[index].weight;
            index = index + 1;
        }
    }

    return profit;
}

object_t* eliminate_object (object_t* objects, int object_count, int object_index) {
    if(object_index < 0) return objects;

    object_t* new_object_arr = (object_t*) malloc(sizeof(object_t) * (object_count - 1));
    int j = 0;
    for(int i = 0; i < object_count; i++) {
        if(i != object_index) {
            new_object_arr[j] = objects[i];
            j++;
        }
    }

    return new_object_arr;
}

int max_profit_recursion (object_t* objects, int object_count, int max_weight, int used_object_index) {
    if(object_count == 1) {
        if(objects[used_object_index].weight > max_weight) return 0;
        else return objects[used_object_index].value;
    }
    

    object_t* current_objects = eliminate_object(objects, object_count, used_object_index);
    if(used_object_index >= 0) object_count--;

    int max_profit = 0;
    for(int i = 0; i < object_count; i++) {
        if(current_objects[i].weight <= max_weight) {
            int profit = current_objects[i].value + max_profit_recursion(current_objects, object_count, max_weight - current_objects[i].weight, i);
            if (profit > max_profit) max_profit = profit;
        }
    }

    return max_profit;
}

int main()
{
    int test_count = 0;
    fin >> test_count;

    for (int i = 0; i < test_count; i++) {
        int object_count = 0, max_weight = 0;
        fin >> object_count >> max_weight;

        object_t* objects = (object_t*) malloc(sizeof(object_t) * object_count);

        for (int i = 0; i < object_count; i++) 
            fin >> objects[i].weight >> objects[i].value;  

        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;

        int profit_greedy = 0;
        auto start_greedy = high_resolution_clock::now();
        profit_greedy = max_profit_greedy(objects, object_count, max_weight);
        auto finish_greedy = high_resolution_clock::now();
        duration<double, std::milli> ms_greedy = finish_greedy - start_greedy;

        
        int profit_recursion = 0;
        auto start_recursion = high_resolution_clock::now();
        profit_recursion = max_profit_recursion (objects, object_count, max_weight, -1);
        auto finish_recursion = high_resolution_clock::now();
        duration<double, std::milli> ms_recursion = finish_recursion - start_recursion;

        fout << "\n============CURRENT TEST: " << i + 1 << "==================\n";
        fout << "Answer recursive: " << profit_recursion << "\n";
        fout << "Execution time recursive: " << ms_recursion.count() << "ms\n";
        fout << "Answer greedy: " << profit_greedy << '\n';
        fout << "Execution time greedy: " << ms_greedy.count() << "ms\n";
    }
    return 0;
}