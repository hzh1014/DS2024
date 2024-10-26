#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
int largestRectangleArea(std::vector<int> &heights) {
    int n = heights.size();
    std::vector<int> left(n), right(n);
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        left[i] = st.empty()? -1 : st.top();
        st.push(i);
    }
    while (!st.empty()) {
        st.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        right[i] = st.empty()? n : st.top();
        st.push(i);
    }
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        maxArea = std::max(maxArea, heights[i] * (right[i] - left[i] - 1));
    }
    return maxArea;
}
std::vector<int> generateRandomHeights() {
    int n = rand() % 105 + 1;
    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        heights[i] = rand() % 10000;
    }
    return heights;
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 10; ++i) {
        std::vector<int> heights = generateRandomHeights();
        int area = largestRectangleArea(heights);
        std::cout << "Test " << i + 1 << ": Max area = " << area << std::endl;
    }
    return 0;
}
