#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <new>
#include <string>
#include <cstring>
#define PRIME_NUMBER 715927

int hash_array(std::vector<int> vec, bool index_makes_different)
{
    int seed = 0, i = 1;
    for (int x : vec)
    {
        if (index_makes_different)
            seed += x * (2 << i);
        else
            seed += x;
        i++;
    }
    return seed;
}

template <typename T>
bool exists(T elem, std::vector<T> elems)
{
    return std::find(elems.begin(), elems.end(), elem) != elems.end();
}

void show_all_combinations(std::vector<std::string> set, bool (*rule)(std::vector<std::string> elems), int required_set_lenght, int current_index = 0, int current_set_lenght = 0, bool index_makes_different = false, std::vector<std::string> partial_solution_stack = {}, int offset = 0)
{
    static std::vector<int> solutions_hashes{};
    static int solution_count = 1;
    if (current_set_lenght > required_set_lenght)
        return;

    int partial_solution_stack_size = partial_solution_stack.size();

    if (partial_solution_stack_size >= 1)
    {
        std::vector<std::string> solution;

        for (int i = offset + 1; i < offset + current_set_lenght; i++)
        {
            solution.push_back(partial_solution_stack[i]);
        }

        if (rule(solution))
        {
            std::vector<int> solution_to_integers{};
            for (std::string elem : solution)
            {
                int hash = std::hash<std::string>()(elem) % PRIME_NUMBER;
                solution_to_integers.push_back(hash);
            }

            auto solution_hash = hash_array(solution_to_integers, index_makes_different);
            if (!exists<int>(solution_hash, solutions_hashes))
            {
                std::cout << solution_count << ". ";
                for (auto elem : solution)
                {
                    std::cout << elem << " ";
                }
                std::cout << std::endl;
                solution_count++;
                solutions_hashes.push_back(solution_hash);
            }
        }
    }

    unsigned int set_size = set.size();
    if (current_index == set_size)
        return;

    if (current_set_lenght == 0)
    {
        partial_solution_stack.push_back(set[current_index]);
    }
    else if (current_set_lenght == 1)
    {
        partial_solution_stack.push_back(partial_solution_stack[0]);
        partial_solution_stack.push_back(set[current_index]);
    }
    else if (current_set_lenght == 2)
    {
        partial_solution_stack.push_back(partial_solution_stack[0]);
        partial_solution_stack.push_back(partial_solution_stack[1]);
        partial_solution_stack.push_back(set[current_index]);
    }
    else
    {
        for (int i = 0; i < current_set_lenght + 1; i++)
        {
            if (i == current_set_lenght)
            {
                partial_solution_stack.push_back(set[current_index]);
            }
            else
            {
                partial_solution_stack.push_back(partial_solution_stack[offset + i]);
            }
        }
    }

    show_all_combinations(set, rule, required_set_lenght, 0, current_set_lenght + 1, index_makes_different, partial_solution_stack, offset + current_set_lenght);

    for (int i = 0; i < current_set_lenght + 1; i++)
        partial_solution_stack.pop_back();

    show_all_combinations(set, rule, required_set_lenght, current_index + 1, current_set_lenght, index_makes_different, partial_solution_stack, offset);
}

// bool rule_for_candies(std::vector<std::string> elems) {
//     if(elems.size() < MIN_SIZE) return false;

//     std::unordered_set<std::string> unique_elems(elems.begin(), elems.end());
//     // There are duplicates!
//     if(unique_elems.size() != elems.size()) return false;

//     // "nu pot fi ?i jeleuri ?i praline"
//     if (exists<std::string>("jeleuri", elems) && exists<std::string>("praline", elems)) return false;

//     return true;
// }

const int N = 18;
bool rule_for_sum(std::vector<std::string> elems)
{
    int sum = 0, max_digit = 0;
    for (auto elem : elems)
    {
        int current_digit = std::stoi(elem);
        sum += current_digit;

        if(current_digit >= max_digit) max_digit = current_digit;
        else return false;
    }

    if (sum == N)
        return true;
    else
        return false;
}

bool rule_for_binary(std::vector<std::string> elems)
{

    std::string last_character = "\0";
    int last_character_occurances = 0;
    for (std::string c : elems)
    {
        if (last_character != "\0" && c == last_character)
        {
            last_character_occurances++;
        }
        else
        {
            last_character = c;
            last_character_occurances = 0;
        }

        if (last_character_occurances > 1)
            return false;
    }

    return true;
}

int main()
{
    // this generates candies
    // std::vector<std::string> set = {"bomboane", "drajeuri", "jeleuri", "praline"};

    // std::vector<std::vector<std::string>> solutions = show_all_combinations(set, rule_for_candies, 4, 0, 0);

    // int i = 1;
    // for(auto solution : solutions) {
    //     std:: cout << i << ". ";
    //     for(auto elem: solution) {
    //          std::cout << elem << " ";
    //     }
    //     i++;
    //     std::cout<<"\n";
    // }

    // this generates prime numbers that sum up to a constant "N"
    std::vector<std::string> set = {"2", "3", "5", "7", "11", "13"};
    show_all_combinations(set, rule_for_sum, 9, 0, 0, true);
    return 0;

    // this generates binary number with a "special property": "au cel mult dou? cifre cu valori egale pe pozi?ii consecutive"
    // std::vector<std::string> set = {"0", "1"};
    // std::vector<std::vector<std::string>> solutions = show_all_combinations(set, rule_for_binary, 6, 0, 0, true);

    // int i = 1;
    // for(auto solution : solutions) {
    //     std:: cout << i << ". ";
    //     for(auto elem: solution) {
    //          std::cout << elem << " ";
    //     }
    //     i++;
    //     std::cout<<"\n";
    // }

    // this generates cats and dogs with the same "special property" as above
    // std::vector<std::string> set = {"C", "P"};
    // std::vector<std::vector<std::string>> solutions = show_all_combinations(set, rule_for_binary, 5, 0, 0, true);

    // int i = 1;
    // for(auto solution : solutions) {
    //     std:: cout << i << ". ";
    //     for(auto elem: solution) {
    //          std::cout << elem << " ";
    //     }
    //     i++;
    //     std::cout<<"\n";
    // }
}