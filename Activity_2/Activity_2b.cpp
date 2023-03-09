using namespace std;
#include<iostream>
#include<string.h>

class student     //Creation of class student
{            // Declaration of Data Members
    private: char name[20];
             int roll;
             char dob[15];
             char address[20];
             char branch[10];
             char sem[5];
             int sub;
                    
                    //Member functions
    public: student(char n[],int r,char d[],char adr[],char br[],char sm[],int sb){   // Creation of Parameterised Constructor
        strcpy(name,n);
        roll = r;
        strcpy(dob,d);
        strcpy(address,adr);
        strcpy(branch,br);
        strcpy(sem,sm);
        sub = sb;        
    }

    public: ~student(){     //Creation of Destructor
        cout<<"\tcalling destructor..\n"<<endl;
    }
    
    public: void display(){         //Creation of display function
        cout <<"\n\tInformation for student\n";
        cout<<"Name = "<<name<<endl;
        cout <<"Roll no. = "<<roll<<endl;
        cout <<"D.O.B = "<<dob<<endl;
        cout <<"Address = "<<address<<endl;
        cout <<"Branch = "<<branch<<endl;
        cout <<"Semester = "<<sem<<endl;
        cout <<"No. of Subjects = "<<sub<<endl;
        
    }
};

int main(){

             char name[20];
             int roll,sub;
             char dob[15];
             char address[20],branch[10],sem[10];             

    cout<<"\n\tEnter Details for Student"<<endl;
        cout << "Enter name: "; cin >> name;
        cout << "Enter roll no: "; cin >> roll;
        cout << "Enter DOB(format->DD-MM-YYYY): "; cin >> dob;
         cout << "Enter Address: "; cin >> address;
         cout << "Enter Branch: "; cin >> branch;
         cout << "Enter sem: "; cin >> sem;
         cout << "Enter No. of Subjects: "; cin >> sub;
    
    student s(name,roll,dob,address,branch,sem,sub); //Creating object of class and addding values
    s.display(); //calling member functions

    return 0;
}