#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to calculate minimum number of gifts needed
int minimumGiftsRequired(const vector<int>& scores) {
    int n = scores.size();
    vector<int> gifts(n, 1); // Everyone gets at least 1 gift

    // Left to right
    for (int i = 1; i < n; ++i) {
        if (scores[i] > scores[i - 1]) {
            gifts[i] = gifts[i - 1] + 1;
        }
    }

    // Right to left
    for (int i = n - 2; i >= 0; --i) {
        if (scores[i] > scores[i + 1]) {
            gifts[i] = max(gifts[i], gifts[i + 1] + 1);
        }
    }

    // Sum all gifts
    int total = 0;
    for (int g : gifts) total += g;
    return total;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, a;
        cin >> n >> a;
        vector<int> scores(n);

        for (int i = 0; i < n; ++i) {
            cin >> scores[i];
        }

        int required = minimumGiftsRequired(scores);
        if (required <= a)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}