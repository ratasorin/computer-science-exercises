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
        for(int j = i + 1; j < queens.size(); j++) {
            if(abs(queens[j] - queens[i]) == abs(j - i)) return true;
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
    for(int i = 0; i < chess_table_size; i++) {
        bool found_queen = false;
        for(int j = 0; j < chess_table_size; j++) {
            if(queens.at(i) == j && !found_queen) {
                cout << "Q ";
                found_queen = true;
            }
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve_n_queens(int chess_table_size, vector<int> solution, vector<vector<int>>& solutions) {
    if(solution.size() == chess_table_size) {
        display(solution, chess_table_size);
        solutions.push_back(solution);
        return;
    }

    for(int i = 0; i < chess_table_size; i++) {
        solution.push_back(i);
        if(!is_attacking(solution)) {
            solve_n_queens(chess_table_size, solution, solutions);
        }
        solution.pop_back();
    }
}

int main() {
    int chess_table_size = 5;
    vector<int> solution = {};
    vector<vector<int>> solutions = {};
    solve_n_queens(chess_table_size, solution, solutions);

    cout << "SOLUTION COUNT: " << solutions.size() << endl;
}