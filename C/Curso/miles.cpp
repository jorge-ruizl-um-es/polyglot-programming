# include <iostream>
using namespace :: std;
const double m_to_k = 1.609;

double convert(int m) {
    return m*m_to_k;
}

int main() {
    int miles = 1;

    while (miles != 0) {
        cout << "Input distance in miles or 0 to finish: ";
        cin >> miles;
        cout << "\nDistance is " << convert(miles) << " km." << endl;
    }
    cout << endl;

    return 0;
}