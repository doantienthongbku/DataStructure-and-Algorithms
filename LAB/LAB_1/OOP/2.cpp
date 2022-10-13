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

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        this->center.setX(0.0);
        this->center.setY(0.0);
        this->radius = 0.0;
    }

    Circle(Point center, double radius)
    {
        this->center.setX(center.getX());
        this->center.setY(center.getY());
        this->radius = radius;
    }

    Circle(const Circle &circle)
    {
        this->center = circle.getCenter();
        this->radius = circle.getRadius();
    }
    
    void setCenter(Point point)
    {
        this->center.setX(point.getX());
        this->center.setY(point.getY());
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

    Point getCenter() const
    {
        return this->center;
    }

    double getRadius() const
    {
        return this->radius;
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};


int main() {
    Circle A;
    A.printCircle();

    return 0;
}