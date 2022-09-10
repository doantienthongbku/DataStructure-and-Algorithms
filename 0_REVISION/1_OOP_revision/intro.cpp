#include <iostream>
#include <string>
using namespace std;

/*
3 rule of Constructor:
    - Constructor does not have a return
    - Constructor has the same name of class Name
    - Constructor must be public
*/

class Employee {
public:
    string Name;
    string Company;
    int Age;

    Employee(string name, string company, int age) {
        Name = name;
        Company = company;
        Age = age;
    }

    void IntroduceYourself() {
        cout << "Name - " << Name << endl;
        cout << "Company - " << Company << endl;
        cout << "Age - " << Age << endl;
    }
};

int main() {
    Employee employee1 = Employee("John", "Emage", 20);
    employee1.IntroduceYourself();

    Employee employee2 = Employee("Taft", "Emage", 21); 
    employee2.IntroduceYourself();

    return 0;
}