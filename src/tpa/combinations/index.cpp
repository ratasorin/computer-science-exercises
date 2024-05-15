#include <iostream>
#include <unordered_set>
#include <list>

using namespace std;

template <typename T>
void display (const list<T>& obj) {
    for (auto obj_iterator = obj.begin(); obj_iterator != obj.end(); obj_iterator++) {
        auto element = *obj_iterator;
        cout << element << " ";
    }
    cout << endl;
}

template <typename T>
bool is_sorted (const list<T>& l) {
    T max = l.front();
    for(T elem : l) {
        if(elem >= max) {
            max = elem;
        }
        else return false;
    }
    return true;
}

template <typename T>
void __generate_combinations (list<T> elements, list<T> generated_combination, int n, int k) {
    if(elements.size() == n - k && is_sorted(generated_combination)) { 
        display(generated_combination);
        return;
    }

    for(auto iterator = elements.begin(); iterator != elements.end();) {
        T current_value = *iterator;
        auto current_iterator = iterator;
        auto next_iterator = ++iterator;

        generated_combination.push_back(current_value);
        elements.erase(current_iterator);
        
        __generate_combinations(elements, generated_combination, n, k);
        
        generated_combination.pop_back();
        
        if(next_iterator != elements.end()) elements.insert(next_iterator, current_value);
        iterator = next_iterator;
    }

}

// given a particular set of elements, output all possible combinations of "k" from "n"
template <typename T>
void generate_combinations (unordered_set<T> input, int k) {
    list<T> elements, generated_combination;
    for(auto input_element : input) {
        elements.push_front(input_element);
    }

    __generate_combinations(elements, generated_combination, input.size(), k);

}

int main() {
    unordered_set<int> s = {1, 2, 3, 4};
    int k = 3;
    generate_combinations<int>(s, k);
}