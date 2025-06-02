#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Insert at head
Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    return newNode;
}

// Insert at tail
Node* insertAtTail(Node* head, int val) {
    Node* newNode = new Node(val);
    if (!head) return newNode;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Delete node by value
Node* deleteNode(Node* head, int val) {
    if (!head) return nullptr;
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    Node* curr = head;
    while (curr->next && curr->next->data != val)
        curr = curr->next;
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    }
    return head;
}

// Print list
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = nullptr;

    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);

    head = insertAtTail(head, 4);
    head = insertAtTail(head, 5);

    cout << "Initial List: ";
    printList(head);

    head = deleteNode(head, 3);
    cout << "After Deleting 3: ";
    printList(head);

    head = deleteNode(head, 1);
    cout << "After Deleting 1 (Head): ";
    printList(head);

    return 0;
}


// ---- paya --------
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

// ---- wassa --------
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

// ---- xmas --------
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


