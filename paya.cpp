#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int toSec(const string& t) {
    return stoi(t.substr(0, 2)) * 3600 + stoi(t.substr(3, 2)) * 60 + stoi(t.substr(6, 2));
}

string toStr(int s) {
    int h = s / 3600;
    int m = (s % 3600) / 60;
    int sec = s % 60;
    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", h, m, sec);
    return string(buf);
}

int main() {
    int n;
    cin >> n;
    vector<string> timeStrs(n);
    vector<int> timeSecs(n);

    for (int i = 0; i < n; ++i) {
        cin >> timeStrs[i];
        timeSecs[i] = toSec(timeStrs[i]);
    }

    sort(timeSecs.begin(), timeSecs.end());

    int minDiff = 86400;
    vector<pair<int, int>> minPairs;

    // Check adjacent pairs
    for (int i = 1; i < n; ++i) {
        int diff = timeSecs[i] - timeSecs[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
            minPairs = {{timeSecs[i - 1], timeSecs[i]}};
        } else if (diff == minDiff) {
            minPairs.emplace_back(timeSecs[i - 1], timeSecs[i]);
        }
    }

    // Wrap-around: last and first
    int wrapDiff = (86400 - timeSecs[n - 1]) + timeSecs[0];
    if (wrapDiff < minDiff) {
        minDiff = wrapDiff;
        minPairs = {{timeSecs[n - 1], timeSecs[0]}};
    } else if (wrapDiff == minDiff) {
        minPairs.emplace_back(timeSecs[n - 1], timeSecs[0]);
    }

    // Convert to string and sort by start time
    vector<pair<string, string>> result;
    for (auto& p : minPairs) {
        result.push_back({toStr(p.first), toStr(p.second)});
    }

    sort(result.begin(), result.end());

    for (auto& p : result) {
        cout << p.first << "->" << p.second << endl;
    }

    return 0;
}