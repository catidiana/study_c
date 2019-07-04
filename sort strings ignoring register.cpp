#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string tolowers (string x)
{
    for (char& e :x) {
        e = tolower(e);}
    return x;
}

int main() {

    int N;
    cin  >> N;
    vector<string> v(N);
    for (int i = 0;i<N;i++) {
        cin >> v[i];
    }

    sort (begin(v), end(v), [](string a, string b) {return tolowers(a) < tolowers(b);});

    for(auto c: v) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
