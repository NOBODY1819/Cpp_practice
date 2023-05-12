#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;

//Student class to represent each record
class Student{
    public:
    string name;
    int rollno;
    float marks;

    //Constructor to initialize member variables
    Student(string name ="", int rollno =0 , float marks = 0.0 ){
        this ->name = name;
        this->rollno = rollno;
        this ->marks = marks;
    }
    
    //Function to print the student record
    void print(){
        cout<<"Name = "<<name<<endl;
        cout<<"Roll No = "<<rollno<<endl;
        cout<<"Marks = "<<marks<<endl;
    }

    //Function to write the student record to a file
    void WriteToFile(ofstream &file){
        file<<name<<","<<rollno<<","<<marks<<endl;
    }

    //Function to read the student record from a file
    void readFromFile(ifstream &file){
        string line;
        getline(file,line);
        
        //split the line by coma delimiter
        int pos1=line.find(",");
        int pos2 = line.find(",",pos1 + 1);

        //Extrat name, rollno and marks from the line
        name = line.substr(0, pos1);
        rollno = stoi(line.substr(pos1+1,pos2+pos1+1));
        marks= stof(line.substr(pos2+1));
    }
    
};

//Function to add a new student record to file
void addStudentRecord(){
    ofstream file("students.txt",ios::app); // Open file in append mode

    if (!file.is_open())
    {
        cout<<"Error ipening file"<<endl;
        return;
    }

    // Get input from user
    string name;
    int rollno;
    float marks;
    fflush(stdin);
    cout<<" Enter name: ";
    cin>>name;
    getch();
    cout<<" Enter Roll No :";
    cin>>rollno;
    cout<<" Enter Marks : ";
    cin>>marks;

    // Create a new student object and write it to file
    Student student(name,rollno,marks);
    student.WriteToFile(file);
    
    file.close();
    
}

// Function to search for a student record in the file
void searchStudentRecord(){
    ifstream file("students.txt");
    
    if (!file.is_open())
    {
        cout<<"Error opening file"<<endl;
        return;
    }
    
    //Get input from user
    int rollno;
    cout<<"Enter roll no to search : ";
    cin>>rollno;
    
    //Read each record from file and check for the roll no
    Student student;
    bool found = false;
    while (file.good())
    {
        student.readFromFile(file);
        
        if(file.eof()) break; //Exit loop if end of file is reached

        if(student.rollno == rollno){
            cout<< "Student record found "<<endl;
            student.print();
            found = true;
            break;
        }
    }

    if(!found){
        cout<<"Student record not found"<<endl;
    }

    file.close();
}

// Main function to call other functions
int main(){
    int choice;
    
    do
    {
        cout<<endl;
        cout<<"1. Add student record\n2. Search student record\n3. Exit\nEnter choice : ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            //Add student record logic here
            cout<<"\nAdding new student record\n";
            addStudentRecord();
            break;
        case 2:
        // search student record logic here
        cout<<"\nSeacrhing for student\n";
        searchStudentRecord();
        break;
        cout<<"\n-->Exit Program<---\n";
        break;
        default:
        cout<<"\nInvalid choice.\n";
            break;
        }
    } while (choice!=3);

    return 0;    
}