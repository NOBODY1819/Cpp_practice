using namespace std;
#include<iostream>
#include<string.h>

class course
{
    private: char c_name[20];
    private: char c_id[10];
    private: char c_sem[10];
    private: int c_credit;
    private: float c_fee;

    public: course(){
        strcpy(c_name,"abc");
        strcpy(c_id,"COM-401");
        strcpy(c_sem,"--sem--");
        c_credit=10;
        c_fee=999.99;       
    }

    public: ~course(){
        cout<<"\tcalling destructor..\n"<<endl;
    }
    
    public: void input(){
        
         cout<<"\tEnter Details for Course"<<endl;
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
    public: void diaplay(){
    
        cout <<"\tInformation of Course:"<<endl;
            if (strcmp(c_name,"abc")==0)
            {
                cout<<"\tDefault Values\n"<<endl;
            }
        cout<<"Course name = "<<c_name<<endl;
        cout <<"Course ID = "<<c_id<<endl;
        cout <<"Coirse sem = "<<c_sem<<endl;
        cout <<"Course credits = "<<c_credit<<endl;
        cout <<"Course fee = "<<c_fee<<endl;        
     
    };
};

int main(){

    cout<<"\tCreating Object...\n"<<endl;
    course c1;
    c1.diaplay();
    c1.input();
    c1.diaplay();
        

    return 0;
}