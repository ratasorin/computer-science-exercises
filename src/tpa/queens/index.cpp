#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool attacking_on_row(vector<int> queens) {
    sort(queens.begin(), queens.end());

    for(int i = 0; i < queens.size() - 1; i++) {
        if(queens[i] == queens[i + 1]) return true;
    }

    return false;
}

bool attacking_on_diag(vector<int> queens) {
    for(int i = 0; i < queens.size(); i++) {
        for(int j = 0; j < queens.size(); j++) {
            if(i == j) continue;
            if(abs((queens[j] - queens[i]) / (j - i)) == 1) return true;
        }
    }
    return false;
}

bool is_attacking (const vector<int>& queens) {
    // the queens are not attacking each other on row
    if(attacking_on_row(queens)) return true;

    // the queens are not attacking each other on diagonal 
    if(attacking_on_diag(queens)) return true;
    
    return false;
}

void display(vector<int> queens, int chess_table_size) {
    for(auto q : queens) cout << q << " ";
    cout << endl;
    // for(int i = 0; i < chess_table_size; i++) {
    //     bool found_queen = false;
    //     for(int j = 0; j < chess_table_size; j++) {
    //         if(queens.at(i) == j && !found_queen) {
    //             cout << "Q ";
    //             found_queen = true;
    //         }
    //         else cout << ". ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
}

void solve_n_queens(int chess_table_size) {
    vector<vector<int>> solutions = {};
    vector<int> current_solution = {};

    for(int i = 0; i < chess_table_size; i++) {
        current_solution.push_back(i);
        
        while(!current_solution.empty()) {
            if(current_solution.size() == chess_table_size) {
                solutions.push_back(current_solution);
                display(current_solution, chess_table_size);
                current_solution = {};
                break;
            }
            

            bool found_solution_on_column = false;
            for(int i = 0; i < chess_table_size && !found_solution_on_column; i++) {
                current_solution.push_back(i);
                display(current_solution, chess_table_size);
                if(!is_attacking(current_solution)) found_solution_on_column = true;
                else current_solution.pop_back();
            }
            
            if(!found_solution_on_column) current_solution.pop_back();
        }
    }
}

int main() {
    int chess_table_size = 8;
    solve_n_queens(chess_table_size);
}