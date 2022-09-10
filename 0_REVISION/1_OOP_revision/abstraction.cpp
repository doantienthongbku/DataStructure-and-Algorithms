#include <iostream>
#include <string>
using namespace std;

// rule of Abstract class: class decides to sign this contract that class will 
//                         need to provide implementation for a method called ask

class AbstractEmployee {
public:
    virtual void AskForPromotion() = 0;
};


class Employee:AbstractEmployee {
private:
    string name;
    string company;
    int age;
public:
    Employee(string name, string company, int age) {
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void IntroduceYourself() {
        cout << "Name - " << name << endl;
        cout << "Company - " << company << endl;
        cout << "Age - " << age << endl;
    }

    void AskForPromotion() {
        if (age > 30) {
            cout << name << " got promoted!" << endl;
        } else {
            cout << name << ", sorry NO promotion for you!" << endl;
        }
    }

    void setName(string name) {
        this->name = name;
    }
    string getName() {
        return name;
    }
    void setCompany(string company) {
        this->company = company;
    }
    string getCompany() {
        return company;
    }
    void setAge(int age) {
        if (age >= 18)
            this->age = age;
    }
    int getAge() {
        return age;
    }
};

int main() {
    Employee employee1 = Employee("John", "Emage", 20);
    Employee employee2 = Employee("Taft", "Emage", 31); 

    employee1.AskForPromotion();
    employee2.AskForPromotion();

    return 0;
}