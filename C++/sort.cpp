# include <iostream>
# include <iterator>
# include <fstream>
# include <algorithm>
# include <vector>
using namespace std;

int main() {
    ifstream word_file("word.txt");
    istream_iterator<string> start(word_file), end;
    vector<string> words(start, end);

    cout << " \n\nwords as read:\n";
    for (auto w : words) {
        cout << w << "\t";
    }
    sort(words.begin(), words.end());
    cout << " \n\nwords as sorted:\n";
    for (auto w : words) {
        cout << w << "\t";
    }
    cout << "\n\n";

    for (auto w = words.begin(); w != words.end(); w++) {
        cout << "Word " << *w << " spotted ";
        auto old = *w;
        int count = 1;
        while (*(++w) == old) {
            count++;
            old = *w;
        }
        cout << count << " times" << endl;
        --w;
    }
}