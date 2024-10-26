#include <iostream>
#include <vector>

class Stack {
private:
    std::vector<int> data;
public:
    bool isEmpty() const {
        return data.empty();
    }

    void push(int value) {
        data.push_back(value);
    }

    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }
        int topValue = data.back();
        data.pop_back();
        return topValue;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return data.back();
    }
};
