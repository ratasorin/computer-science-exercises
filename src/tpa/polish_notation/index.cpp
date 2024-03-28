#include <fstream>
#include <stack>
#include <cstring>
#include <vector>
#include <iostream>

bool is_variable(char c) {
    return c >='a' && c <='z';
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    char equation[1000];
    input.getline(equation, 1000);

    std::stack <char> temp_operators;
    std::vector <char> polish_notation_equation;
    
    int equation_length = strlen(equation);
    for(int i = 0; i < equation_length; i++) {

        char current_character = equation[i];
        
        std::cout << current_character << "";
        
        if(is_variable(current_character)) {
            polish_notation_equation.push_back(current_character);
        }

        if(current_character == '(') {
            temp_operators.push(current_character);
        }

        if(current_character == ')') {
            while(temp_operators.top() != '(')
            {
                polish_notation_equation.push_back(temp_operators.top());
                temp_operators.pop();
            }
            temp_operators.pop();
        }
        
        // because "*" and "/" have the highest precedence we can chain them forever 
        // for example: if the equation is: a * b * c * d / e => polish notation: abcde/**** (and the operators stack: [****/])
        if(current_character == '*' || current_character == '/') {
            temp_operators.push(current_character);
        }

        // because "+" and "-" have a lower precedence we cannot chain them forever
        // for example: if the equation is: a * b * c * d + e * f + g * h => abcd***ef*+gh*+
        // the steps here would be: 
        // 1. put "*" on the stack => [*, *, *]
        // 2. pop them when seeing "+" and add "+" to the stack => [+], polish_notation: abcd***
        // 3. push another "*" => [+, *]
        // 4. pop them when seeing "+" and add "+" to the stack => [+], polish_notation: abcd***ef*+
        if(current_character == '+' || current_character == '-')
        {
            if(temp_operators.empty())
                temp_operators.push(current_character);
            else {
                while(!temp_operators.empty() && temp_operators.top() != '(')
                {
                    polish_notation_equation.push_back(temp_operators.top());
                    temp_operators.pop();
                }
                temp_operators.push(current_character);
            }
        }
    }

     while(!temp_operators.empty()) {
        polish_notation_equation.push_back(temp_operators.top());
        temp_operators.pop();
    }

    for(auto c : polish_notation_equation) {
        output << c << "";
    }
    
    output << std::endl;

    int polish_text_size = polish_notation_equation.size();
    std::stack <int> variables;

    for(int i = 0; i < polish_text_size; i++) {
        int operand; 

        if(is_variable(polish_notation_equation[i])) {
            input >> operand;
            variables.push(operand);
        }
        else {
            int variable_1 = variables.top();
            variables.pop();

            int variable_2 = variables.top();
            variables.pop();
            
            if(polish_notation_equation[i]=='*') variables.push(variable_1 * variable_2);
            if(polish_notation_equation[i]=='/') variables.push(variable_1 / variable_2);
            if(polish_notation_equation[i]=='+') variables.push(variable_1 + variable_2);
            if(polish_notation_equation[i]=='-') variables.push(variable_1 - variable_2);
        }
    }
    output << variables.top() << " ";
    return 0;
}