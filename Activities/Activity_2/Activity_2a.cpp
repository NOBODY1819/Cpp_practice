using namespace std;
#include <iostream>
#include <string.h>

class student // Creation of class named student
/*Main feature of Oops is data hiding which refers to restricting access to data members of a class.
This is to prevent other functions and classes from tampering with the class data.
Declaring the data members of student class are hidden using private keyword*/
{
private:
    char name[20];
    int roll; // Declaration of Data Members as private to protect the data in them from outside the class
    char dob[15];
    char sem[10];

    // Member functions as public to access them outside the class
public:
    student()
    { // Creation of Constructor
       cout<<"Calling constructor of student....";
    }

public:
    ~student()
    { // Creation of Destructor
        cout << "\tcalling destructor of student..\n"
             << endl;
    }

public:
    void input()
    { // Creation of Input function
        cout << "\n\tEnter Details for Student" << endl;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter DOB(format->DD-MM-YYYY): ";
        cin >> dob;
        cout << "Enter sem: ";
        cin >> sem;
    }

public:
    void display()
    { // Creation of display function
    cout<<"\n\tInformation of student\n";
        cout << "Name = " << name << endl;
        cout << "Roll no. = " << roll << endl;
        cout << "D.O.B = " << dob << endl;
        cout << "Semester = " << sem << endl;
    }
};

class course     //Creation of class course
{              // Declaration of Data Members
    private: char c_name[20];
    private: char c_id[10];
    private: char c_sem[10];
    private: int c_credit;
    private: float c_fee;

            //Member functions
    public: course(){        // Creation of Constructor
       cout<<"Calling constructor of course...";      
    }

    public: ~course(){      //Creation of Destructor
        cout<<"\tcalling destructor of course...\n"<<endl;
    }
    
    public: void input(){
                            //Creation of Input function
         cout<<"\n\tEnter Details for Course"<<endl;
        cout << "Enter Course name: ";
        cin >> c_name;
        cout << "Enter Course ID: ";
        cin >> c_id;
        cout << "Enter Course Sem: ";
        cin >> c_sem;
         cout << "Enter Course Credits: ";
        cin >> c_credit;
         cout << "Enter Course Fee: ";
        cin >> c_fee;    
    }
    public: void display(){
            //Creation of display function
            cout<<"\n\tInformation of course\n";
        cout<<"Course name = "<<c_name<<endl;
        cout <<"Course ID = "<<c_id<<endl;
        cout <<"Course sem = "<<c_sem<<endl;
        cout <<"Course credits = "<<c_credit<<endl;
        cout <<"Course fee = "<<c_fee<<endl;        
     
    };
};

int main()
{

    student s;   // Creating object of class
     // calling member functions for object of class student
    s.input();
    s.display();
    course c1;  //Creating object of class
   //calling member functions for object of class course
    c1.input();
    c1.display();
        

    return 0;
}