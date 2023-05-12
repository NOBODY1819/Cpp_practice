#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

// Student class to represent each record
class Student
{
private:
    string name;
    int roll;
    string dob;
    string address;
    string branch;
    string sem;
    int sub;
    // Member functions
public:
    // Constructor to initialize member variables
    Student(string s_name = "", int rollno = 0, string dob = "01-01-2000", string address = "---", string branch = "branch", string sem = "1st", int sub = 5)
    {
        name = s_name;
        roll = rollno;
        this->dob = dob;
        this->address = address;
        this->branch = branch;
        this->sem = sem;
        this->sub = sub;
    }

    // Function to print the student record
    void print()
    {
        cout << "Name = " << name << endl;
        cout << "Roll No = " << roll << endl;
        cout << "Date of Birth = " << dob << endl;
        cout << "Date of Birth = " << dob << endl;
        cout << "Address = " << address << endl;
        cout << "Semester = " << sem << endl;
        cout << "No. of Subjects = " << sub << endl;
    }

    void search() // Search function to search student records
    {
        cout << "\n\tInformation for student\n";
        cout << "Name = " << name << endl;
        cout << "Roll no. = " << roll << endl;
        cout << "D.O.B = " << dob << endl;
        cout << "Address = " << address << endl;
        cout << "Branch = " << branch << endl;
        cout << "Semester = " << sem << endl;
        cout << "No. of Subjects = " << sub << endl;
    }

    int r_rollno() // Function to return rollno
    {
        return roll;
    }

    // Function to write the student record to a file
    void WriteToFile(ofstream &file)
    {
        file << name << "," << roll << "," << dob << "," << address << "," << branch << "," << sem << "," << sub << endl;
    }

    // Function to read the student record from a file
    void readFromFile(ifstream &file)
    {
        string line;
        getline(file, line);

        // split the line by coma delimiter
        int pos1 = line.find(",");
        int pos2 = line.find(",", pos1 + 1);
        int pos3 = line.find(",", pos1 + pos2 + 1);
        int pos4 = line.find(",", pos1 + pos2 + pos3 + 1);
        int pos5 = line.find(",", pos1 + pos2 + pos3 + pos4 + 1);
        int pos6 = line.find(",", pos1 + pos2 + pos3 + pos4 + pos5 + 1);
        int pos7 = line.find(",", pos1 + pos2 + pos3 + pos4 + pos5 + pos6 + 1);

        // Extrat name, rollno, dob, address, branch, sem and sub from the line
        name = line.substr(0, pos1);
        roll = stoi(line.substr(pos1 + 1, pos2 + pos1 + 1));
        dob = stof(line.substr(pos2 + 1));
    }
};

// Function to add a new student record to file
void addStudentRecord()
{
    ofstream file("students.txt");

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    // Get input from user
    string name;
    int roll;
    string dob;
    string address;
    string branch;
    string sem;
    int sub;
    fflush(stdin);
    cout << " Enter name: ";
    cin >> name;
    cout << "\n\tEnter Details for Student" << endl;
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

    // Create a new student object and write it to file
    Student student(name, roll, dob, address, branch, sem, sub);
    student.WriteToFile(file);

    file.close();
}

// Function to search for a student record in the file
void searchStudentRecord()
{
    ifstream file("students.txt");

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    // Get input from user
    int rollno;
    cout << "Enter roll no to search : ";
    cin >> rollno;

    // Read each record from file and check for the roll no
    Student student;
    bool found = false;
    while (file.good())
    {
        student.readFromFile(file);

        if (file.eof())
            break; // Exit loop if end of file is reached

        if (student.r_rollno() == rollno)
        {
            cout << "Student record found " << endl;
            student.print();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student record not found" << endl;
    }

    file.close();
}

// Main function to call other functions
int main()
{
    int choice;

    do
    {
        cout << endl;
        cout << "1. Add student record\n2. Search student record\n3. Exit\nEnter choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // Add student record logic here
            cout << "\nAdding new student record\n";
            addStudentRecord();
            break;
        case 2:
            // search student record logic here
            cout << "\nSeacrhing for student\n";
            searchStudentRecord();
            break;
            cout << "\n-->Exit Program<---\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}