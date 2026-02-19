// inmplementation of inheritance and polymorphism
#include <iostream>
#include <string.h>
using namespace std;

class course // creation of base class
{
protected: // declaration of protected data to get accesed later by derived class
    string c_name, c_id;
};

class UG : public course
{        // derived class UG
private: // declaration of private data
    string stream, ug_teacher;
    int ug_c_duration;

public:
    void input()
    { // member function for input of data
        cout << "\nEnter course name: ";
        cin >> c_name;
        cout << "Enter course id: ";
        cin >> c_id;
        cout << "Enter stream: ";
        cin >> stream;
        cout << "Enter Teacher Name for course: ";
        cin >> ug_teacher;
        cout << "Enter course duration: ";
        cin >> ug_c_duration;
    }
    void display()
    { // member function for display of data
        cout << "\n\t<----> Under Graduate course <---->";
        cout << "\nCourse name = " << c_name;
        cout << "\nCourse ID = " << c_id;
        cout << "\nStream = " << stream;
        cout << "\nTeacher Name = " << ug_teacher;
        cout << "\nCoures Duration = " << ug_c_duration;
    }
};

class PG : public course
{        // drived class PG
private: // declaration of private data
    string stream, pg_teacher;
    int pg_c_duration;

public:
    void input()
    { // member function for input of data
        cout << "\nEnter course name: ";
        cin >> c_name;
        cout << "Enter course id: ";
        cin >> c_id;
        cout << "Enter stream: ";
        cin >> stream;
        cout << "Enter Teacher Name for course: ";
        cin >> pg_teacher;
        cout << "Enter course duration: ";
        cin >> pg_c_duration;
    }
    void display()
    { // member function for display of data
        cout << "\n\t<----> Post Graduate course <---->";
        cout << "\nCourse name = " << c_name;
        cout << "\nCourse ID = " << c_id;
        cout << "\nStream = " << stream;
        cout << "\nTeacher Name = " << pg_teacher;
        cout << "\nCoures Duration = " << pg_c_duration;
    }
};

class Diploma : public course
{        // derived class Diploma
private: // private data declaration
    string stream, dp_teacher;
    int dp_c_duration;

public:
    void input()
    { // member function for input of data
        cout << "\nEnter course name: ";
        cin >> c_name;
        cout << "Enter course id: ";
        cin >> c_id;
        cout << "Enter stream: ";
        cin >> stream;
        cout << "Enter Teacher Name for course: ";
        cin >> dp_teacher;
        cout << "Enter course duration: ";
        cin >> dp_c_duration;
    }
    void display()
    { // member function for display of data
        cout << "\n\t<----> Diploma course <---->";
        cout << "\nCourse name = " << c_name;
        cout << "\nCourse ID = " << c_id;
        cout << "\nStream = " << stream;
        cout << "\nTeacher Name = " << dp_teacher;
        cout << "\nCoures Duration = " << dp_c_duration;
    }
};

int main()
{
    int choice;
    UG ug1;
    PG pg1;
    Diploma dp1;
    do
    {
        cout << "\n1) UG Course\n2) PG Course\n3) Diploma Course\n0) For Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ug1.input();
            ug1.display();
            break;
        case 2:
            pg1.input();
            pg1.display();
            break;
        case 3:
            dp1.input();
            dp1.display();
            break;
        case 0:
            cout << "Exit Terminal\n";
            break;
        default:
            cout << "Invalid choice! Try again\n";
            break;
        }
    } while (choice != 0);
    return 0;
}