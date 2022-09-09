#include <iostream>
#include <string>
using namespace std;


class Employee {
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
    employee1.IntroduceYourself();

    Employee employee2 = Employee("Taft", "Emage", 21); 
    employee2.IntroduceYourself();

    employee1.setAge(15);
    cout << employee1.getName() << " is " << employee1.getAge() << " years old" << endl;

    return 0;
}