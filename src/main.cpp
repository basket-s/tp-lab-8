#include <iostream>
#include <map>
#include <vector>
#include <ctime>

using namespace std;

map<tuple<string, string>, vector<string>> dictionary;
vector<tuple<string, string>> prefixes;

int textLength = 100, K = 2;
type_info type = typeid(tuple<string, string>);

void print (const tuple<string, string> &a){
    cout << get<0>(a) << " " << get<1>(a) << " ";
}

template <typename T>
void createTuple (T a, int k){

    if (k == 0) {
        type = typeid(T);
        return;
    }

    return createTuple (tuple_cat(a, tuple<string>("")), k - 1);

}

int main(){

    freopen ("../res/sourceText.txt", "r", stdin);
    freopen ("../out/generatedText.txt", "w", stdout);

    string s, prev;
    tuple<string, string> prefix, prevPrefix, emptyPrefix;

    while (cin >> s) {

        if (!prev.empty()) {
            prevPrefix = prefix;
            prefix = make_tuple(prev, s);
        }

        if (prevPrefix != emptyPrefix)
            dictionary[prevPrefix].push_back(s);

        if (prefix != emptyPrefix)
            prefixes.push_back(prefix);

        prev = s;

    }

    srand(time(nullptr));
    auto randNum = rand() % prefixes.size();

    prefix = prefixes[randNum];

    print(prefix);

    while (--textLength && !dictionary[prefix].empty()){

        auto words = dictionary[prefix];
        randNum = rand() % words.size();

        cout << words[randNum] << " ";
        if (ispunct(words[randNum].back()))
            cout << "\n";

        prefix = make_tuple(get<1>(prefix), words[randNum]);

    }

    return 0;

}