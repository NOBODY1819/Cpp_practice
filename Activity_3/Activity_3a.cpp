using namespace std;
#include<iostream>
#include<string.h>

class student     //Creation of class student
{            // Declaration of Data Members 
    private: char name[20];
             int roll;
             char dob[15];
             char sem[10];
                      
                    //Member functions 
    public: student(){         // Creation of Constructor 
        strcpy(name,"abc");
        roll = 123;
        strcpy(dob,"01-01-2001");
        strcpy(sem,"-sem-");       
    }

    public: ~student(){     //Creation of Destructor
    }
    
    public: void input(){     //Creation of Input function
        cout<<"\tEnter Details for Student"<<endl;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter DOB(format->DD-MM-YYYY): ";
        cin >> dob;
         cout << "Enter sem: ";
        cin >> sem;    
    }
    public: void display(){         //Creation of display function
        cout <<"\tInformation for student\n"<<endl;
       if (!strcmp(name,"abc"))
            {
                cout<<"\tDefault Values"<<endl;
            }
        cout<<"Name = "<<name<<endl;
        cout <<"Roll no. = "<<roll<<endl;
        cout <<"D.O.B = "<<dob<<endl;
        cout <<"Semester = "<<sem<<endl;
    }
    int r_rollno(){
        return roll;
    }
     void update(){

     }
};

int main(){
    student s[10];
    int ch,count=-1;
   cout<<"\t-------MENU-------\nEnter 1 -> For New Entery\n2 -> For Updating\n 3 -> For Display Data\n0 -> Exit\t:";
   cin>>ch;
   switch (ch)
   {
   case 1:
   count++;
    s[count].input();
    break;
   case 2:
   cout<<"Enter roll no. of student to update:";
   
   
   default:
    break;
   }
        

    return 0;
}