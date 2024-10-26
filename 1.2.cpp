#include <iostream>
#include <stack>
#include <cctype>

// 判断字符是否为数字
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// 获取运算符的优先级
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 执行运算
int performOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b!= 0) return a / b;
            else return 0;
    }
    return 0;
}

// 字符串计算器
int stringCalculator(const std::string& expression) {
    std::stack<int> operandStack;
    std::stack<char> operatorStack;

    for (char c : expression) {
        if (isDigit(c)) {
            int operand = c - '0';
            operandStack.push(operand);
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top()!= '(') {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                operandStack.push(performOperation(operand1, operand2, op));
            }
            if (!operatorStack.empty())
                operatorStack.pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(c)) {
                int operand2 = operandStack.top();
                operandStack.pop();
                int operand1 = operandStack.top();
                operandStack.pop();
                char op = operatorStack.top();
                operatorStack.pop();
                operandStack.push(performOperation(operand1, operand2, op));
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        int operand2 = operandStack.top();
        operandStack.pop();
        int operand1 = operandStack.top();
        operandStack.pop();
        char op = operatorStack.top();
        operatorStack.pop();
        operandStack.push(performOperation(operand1, operand2, op));
    }

    return operandStack.top();
}
