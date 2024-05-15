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
void __generate_permutations (list<T> elements, list<T> generated_permutation) {
    if(elements.empty()) { 
        display(generated_permutation);
        return;
    }

    for(auto iterator = elements.begin(); iterator != elements.end();) {
        T current_value = *iterator;
        auto current_iterator = iterator;
        auto next_iterator = ++iterator;

        generated_permutation.push_back(current_value);
        elements.erase(current_iterator);
        
        __generate_permutations(elements, generated_permutation);
        
        generated_permutation.pop_back();
        
        if(next_iterator != elements.end()) elements.insert(next_iterator, current_value);
        iterator = next_iterator;
    }

}

// given a particular set of elements, output all possible permutations
template <typename T>
void generate_permutations (unordered_set<T> input) {
    list<T> elements, generated_permutation;
    for(auto input_element : input) {
        elements.push_front(input_element);
    }

    __generate_permutations(elements, generated_permutation);

}

int main() {
    unordered_set<int> s = {1, 2, 3, 4};
    generate_permutations<int>(s);
}