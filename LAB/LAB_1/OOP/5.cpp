#include <iostream>
using namespace std;

enum Color
{
    red,
    green,
    blue
};

enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price) {
        this->color = color;
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        this->size = size;
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox() {
        numberOfItems = 0;
    }
    
    int addItem(const CarToy& carToy)
    {
        if (numberOfItems < 5)
        {
            this->toyBox[this->numberOfItems] = new CarToy(carToy);
            this->numberOfItems++;
            return this->numberOfItems;
        }
        return -1;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        if (numberOfItems < 5)
        {
            this->toyBox[this->numberOfItems] = new PuzzleToy(puzzleToy);
            this->numberOfItems++;
            return this->numberOfItems;
        }
        return -1;
    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};


int main() {
    CarToy car(20000,red);
    PuzzleToy puzzle(30000,small);

    ToyBox box;
    box.addItem(car);
    box.addItem(puzzle);
    box.printBox();

    return 0;
}