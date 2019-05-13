#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <ctime>

using namespace std;

template <int K>
class Prefix{

public:
    vector<string> words;

    Prefix (){
        words.resize(K);
    }

    explicit Prefix (vector<string> words){

        if (words.size() != this->words.size())
            return;

        this->words = words;

    }

    bool operator==(const Prefix & a){

        for (int i = 0; i < K; i++)
            if (a.words[i] != words[i])
                return false;

        return true;

    }

    bool operator!=(const Prefix & a){

        return !(a == (*this));

    }

    bool operator<(const Prefix & a){

        for (int i = 0; i < K; i++)
            if (a.words[i] <= words[i])
                return false;

        return true;

    }

    bool operator<=(const Prefix & a){
        return (*this) < a || (*this) == a;
    }

    bool operator>(const Prefix & a){
        return !((*this) <= a);
    }

    bool operator>=(const Prefix & a){
        return (*this) > a || (*this) == a;
    }

    void print(ostream & out){

        for (const auto &i : words)
            out << i << " ";

    }

};

map<Prefix<2>, vector<string>> dictionary;
vector<Prefix<2>> prefixes;

int main(){

    freopen ("../res/text.txt", "r", stdin);
    freopen ("../out/generatedText.txt", "w", stdout);

    string s, prev;
    vector<string> prefix;

    while (cin >> s) {

        prefix.push_back(s);

        if (!prefixes.empty())
            dictionary[prefixes.back()].push_back(s);

        if (!prev.empty())
            prefixes.push_back(*(new Prefix<2>(prefix)));

        prev = s;

    }

    srand(time(nullptr));
    int g = rand() % prefixes.size();
    Prefix<2> pref = prefixes[g];
    int len = 10;

    pref.print(cout);

    while (len){

        auto cur = dictionary[pref];
        g = rand() % cur.size();
        cout << cur[g] << " ";
        Prefix<2> pref2;
        pref2.words.push_back(pref.words.back());
        pref2.words.push_back(cur[g]);
        pref = pref2;
        len--;

    }

    return 0;

}