#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <deque>

using namespace std;

map<deque<string>, vector<string>> dictionary;
vector<deque<string>> prefixes;

int textLength = 1000, K = 2;

void print (deque<string> d){

    for (const auto &i : d)
        cout << i << " ";

}

int main(){

    freopen ("../res/sourceText.txt", "r", stdin);
    freopen ("../out/generatedText.txt", "w", stdout);

    string s, prev;
    deque<string> prefix, prevPrefix;

    while (cin >> s) {

        if (prefix.size() >= K)
            prefix.pop_front();

        prefix.push_back(s);

        if (!prevPrefix.empty())
            dictionary[prevPrefix].push_back(s);

        if (!prefix.empty())
            prefixes.push_back(prefix);

        if (!prev.empty())
            prevPrefix = prefix;

        prev = s;

    }

    srand(time(nullptr));
    auto randNum = rand() % prefixes.size();

    prefix = prefixes[randNum];

    print(prefix);

    while (--textLength){

        while (dictionary[prefix].empty()){
            randNum = rand() % prefixes.size();
            prefix = prefixes[randNum];
        }

        auto words = dictionary[prefix];
        randNum = rand() % words.size();

        cout << words[randNum] << " ";
        if (ispunct(words[randNum].back()))
            cout << "\n";

        prefix.pop_front();
        prefix.push_back(words[randNum]);

    }

    return 0;

}