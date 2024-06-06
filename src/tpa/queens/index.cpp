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
            if((abs(queens[j] - queens[i]) / abs(j - i)) == 1) return true;
        }
    }
    return false;
}

bool is_attacking (const vector<int>& queens) {
    // the queens are attacking each other on row
    if(attacking_on_row(queens)) return true;

    // the queens are attacking each other on diagonal 
    if(attacking_on_diag(queens)) return true;
    
    return false;
}

void display(vector<int> queens, int chess_table_size) {
    for(auto q : queens) cout << q + 1 << " ";
    cout << endl;
    for(int i = 0; i < chess_table_size; i++) {
        bool found_queen = false;
        for(int j = 0; j < chess_table_size; j++) {
            if(queens.at(j) == i && !found_queen) {
                cout << "Q ";
                found_queen = true;
            }
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve_n_queens(int chess_table_size, vector<int> current_solution, vector<vector<int>>& all_solutions) {
    cout << current_solution.size() << endl;
    if(current_solution.size() == chess_table_size) {
        display(current_solution, chess_table_size);
        all_solutions.push_back(current_solution);
        return;
    }
    
    for(int i = 0; i < chess_table_size; i++) {
        current_solution.push_back(i);
        solve_n_queens(chess_table_size, current_solution, all_solutions);
        current_solution.pop_back();
    }
}

int main() {
    int chess_table_size = 4;
    vector<vector<int>> all_solutions = {};
    vector<int> solution = {};
    solve_n_queens(chess_table_size, solution, all_solutions);
}