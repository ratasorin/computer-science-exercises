#include <fstream>
#include <iostream>
#include <math.h>

std::ifstream fin("arbint.in");
std::ofstream fout("arbint.out");

int* read(int &vector_size, int &operation_count)
{
    fin >> vector_size >> operation_count;
    int* vector = (int*) malloc(sizeof(int) * (vector_size + 1));
    for(int i = 1; i <= vector_size; i++)
        fin >> vector[i];

    return vector;
}


// recursively build a binary tree by considering a node at position i, its "left" is at 2*i, its "right" at 2*i+1, and the value of the node: tree[i] = max_value({ v[left], v[left+1], ..., v[right-1], v[right] }), where "v" is the input vector
void build_binary_tree (int* tree, const int* vector, int node, int left, int right)
{
    if(left == right) {
        tree[node] = vector[left];
        return;
    }

    int middle = (left+right)/2;
    build_binary_tree(tree, vector, 2*node, left, middle);
    build_binary_tree(tree, vector, 2*node+1, middle + 1, right);
    tree[node] = std::max(tree[2*node],tree[2*node+1]);
}

// we want to find the highest value: v[i] where a < i < b. To achieve this we need to look for an interval in the tree such that [a, b] ⊆ [left_ans, right_ans] ([a, b] encloses [left_ans, right_ans])
// because we know that the highest value: v[j] where left_ans < j < right_ans is v[start], where "start" is the "father" of left_ans, right_ans 
int find_max_between_a_b (const int* tree, int start_index, int left_ans, int right_ans, int a, int b)
{
    // this means [a, b] > [ans_left, ans_right] or [a, b] < [ans_left, ans_right]
    // in either case no overlap can occur
    if(a > right_ans || b < left_ans)
        return -1;

    // the stop condition: [a, b] ⊆ [left_ans, right_ans]
    if(a <= left_ans && b >= right_ans) {
        return tree[start_index];
    }

    int middle=(left_ans + right_ans)/2;
    return std::max(find_max_between_a_b(tree, 2*start_index, left_ans, middle, a, b), find_max_between_a_b(tree, 2*start_index + 1, middle + 1, right_ans, a, b));
}

void update_tree (int* tree, int start, int left,int right, int pos, int val) {
    if(left==right) {
        tree[start]=val;
        return;
    }

    int middle = (left + right)/2;
    if(pos <= middle)
        update_tree(tree, 2*start, left, middle, pos, val);
    else
        update_tree(tree, 2*start + 1, middle + 1, right, pos, val);
    tree[start]=std::max(tree[2*start],tree[2*start+1]);
}
int main()
{
    int vector_size = 0, operation_count = 0;
    int *vector= read(vector_size, operation_count);
    
    int binary_tree_levels = std::log2(vector_size) + 1;
       
    int *tree = (int*) malloc(sizeof(int) * ((2 << binary_tree_levels) + 1));

    build_binary_tree(tree, vector, 1, 1, vector_size);

    for(int i = 1; i <= operation_count; i++) {
        int op_type, a, b;
        fin >> op_type >> a >> b;
        if(op_type == 0)
            fout << find_max_between_a_b(tree, 1, 1, vector_size, a, b) << '\n';
        else
            update_tree(tree, 1, 1, vector_size, a, b);
    }
    return 0;
}