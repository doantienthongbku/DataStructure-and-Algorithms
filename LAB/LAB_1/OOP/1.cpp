#include <bits/stdc++.h>
using namespace std;


class Point
{
private:
    double x, y;

public:
    Point()
    {
        this->x = 0.0;
        this->y = 0.0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        this->y = y;
    }

    double getX() const
    {
        return this->x;
    }

    double getY() const
    {
        return this->y;
    }

    double distanceToPoint(const Point& pointA)
    {
        return sqrt(pow(this->x - pointA.getX(), 2) + pow(this->y - pointA.getY(), 2));
    }
};

int main() {
    Point C(2, 3);
    cout << C.getX() << " " << C.getY() << endl;
    Point A(2, 3);
    Point B(1, 1);
    cout << pow(A.distanceToPoint(B), 2) << endl;

    return 0;
}