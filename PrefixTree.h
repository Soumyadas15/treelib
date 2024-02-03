#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Trie {
private:
    struct Node {
        map<T, int> children;
        int prefixCount;
        int wordCount;
        Node() : prefixCount(0), wordCount(0) {}
    };
    vector<Node> nodes;

public:
    Trie() {
        nodes.emplace_back();
    }
    void clear() {
        nodes.clear();
        nodes.emplace_back(); 
    }
    void add(const vector<T>& word) {
        int currentNode = 0;
        for (const T& ch : word) {
            if (nodes[currentNode].children.find(ch) == nodes[currentNode].children.end()) {
                nodes[currentNode].children[ch] = nodes.size();
                nodes.emplace_back();
            }
            currentNode = nodes[currentNode].children[ch];
            nodes[currentNode].prefixCount++;
        }
        nodes[currentNode].wordCount++;
    }

    int prefixCount(const vector<T>& prefix) {
        int currentNode = 0;
        for (const T& ch : prefix) {
            if (nodes[currentNode].children.find(ch) == nodes[currentNode].children.end()) return 0;
            currentNode = nodes[currentNode].children[ch];
        }
        return nodes[currentNode].prefixCount;
    }
};