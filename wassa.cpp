#include <iostream>
#include <vector>
using namespace std;

int trapRainWater(const vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;

    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int trapped = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            // Water is bounded by leftMax
            if (height[left] >= leftMax)
                leftMax = height[left];
            else
                trapped += leftMax - height[left];
            ++left;
        } else {
            // Water is bounded by rightMax
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                trapped += rightMax - height[right];
            --right;
        }
    }

    return trapped;
}

int main() {
    int n;
    cin >> n;

    vector<int> height(n);
    for (int i = 0; i < n; ++i)
        cin >> height[i];

    cout << trapRainWater(height) << endl;

    return 0;
}