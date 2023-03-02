using namespace std;
#include<iostream>
#include<string.h>

class student
{
    private: char name[20];
    private: int roll;
    private: char dob[15];
    private: char address[20];
    private: char branch[10];
    private: char sem[10];
    private: int sub;

    public: student(){
        strcpy(name,"abc");
        roll = 123;
        strcpy(dob,"01-01-2001");
        strcpy(address,"--home address--");
        strcpy(branch,"--bran.--");
        strcpy(sem,"-sem-");
        sub = 5;        
    }

    public: ~student(){
        cout<<"\tcalling destructor..\n"<<endl;
    }
    
    public: void input(){
        cout<<"\tEnter Details for Student"<<endl;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter DOB(format->DD-MM-YYYY): ";
        cin >> dob;
         cout << "Enter Address: ";
        cin >> address;
         cout << "Enter Branch: ";
        cin >> branch;
         cout << "Enter sem: ";
        cin >> sem;
         cout << "Enter No. of Subjects: ";
        cin >> sub;
    
    }
    public: void display(){
        cout <<"\tInformation for student\n"<<endl;
       if (!strcmp(name,"abc"))
            {
                cout<<"\tDefault Values"<<endl;
            }
        cout<<"Name = "<<name<<endl;
        cout <<"Roll no. = "<<roll<<endl;
        cout <<"D.O.B = "<<dob<<endl;
        cout <<"Address = "<<address<<endl;
        cout <<"Branch = "<<branch<<endl;
        cout <<"Semester = "<<sem<<endl;
        cout <<"No. of Subjects = "<<sub<<endl;
        
     
    };
};

int main(){

    cout<<"\tCreating Object...\n"<<endl;
    student s;
    s.display();
    s.input();
    s.display();
        

    return 0;
}