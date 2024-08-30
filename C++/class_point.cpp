# include <iostream>
using namespace std;

class point {
    public:
        // constructor:
        point(double x=0, double y=0): x(x), y(y) {}
        //point() {x = y = 0;}

        // methods:
        double getx(void) {return x;}
        double gety(void) {return y;}
        void setx(double nx) {x = nx;}
        void sety(double ny) {y = ny;}

        friend point operator+ (const point& p1, const point& p2);
        friend ostream& operator<< (ostream& out, const point& p);

    private:
        // attributes
        double x, y;
};

point operator+ (const point& p1, const point& p2) {
    point sum = {p1.x + p2.x, p1.y + p2.y};
    return sum;
}

ostream& operator<< (ostream& out, const point& p) {
    out << "( " << p.x << ", " << p.y << " )" << endl;
    return out;
}

int main() {
    point p1(1.0, 2.0);
    point p2(3.0, 4.0);
    point sum = p1 + p2;
    cout << sum << endl;
    return 0;
}