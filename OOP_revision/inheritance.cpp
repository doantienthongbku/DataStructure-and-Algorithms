#include <iostream>
#include <string>
using namespace std;


class AbstractEmployee {
public:
    virtual void AskForPromotion() = 0;
};


class Employee:AbstractEmployee {
private:
    string company;
    int age;
protected:
    string name;
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


class Developer:public Employee {
private:
    string favProgramingLanguage;
public:
    Developer(string name, string company, int age, string language):Employee(name, company, age) {
        this->favProgramingLanguage = language;
    }

    void FixBug() {
        cout << name << " fixed bug using " << favProgramingLanguage << endl;
    }
};

class Teacher:public Employee {
private:
    string subject;
public:
    Teacher(string name, string company, int age, string subject):Employee(name, company, age) {
        this->subject = subject;   
    }

    void PrepareLesson() {
        cout << name << " is preparing " << subject << " lesson" << endl;
    }
};

int main() {
    Developer d = Developer("Taft", "Emage", 21, "Python");
    d.FixBug();
    d.AskForPromotion();

    Teacher t = Teacher("Lake", "UIT", 31, "Math");
    t.PrepareLesson();
    t.AskForPromotion();

    return 0;
}