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
        cout << "Address = " << address << endl;
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

        if (file.fail())
            return;

        // split the line by coma delimiter
        int pos1 = line.find(",");
        int pos2 = line.find(",", pos1 + 1);
        int pos3 = line.find(",", pos2 + 1);
        int pos4 = line.find(",", pos3 + 1);
        int pos5 = line.find(",", pos4 + 1);
        int pos6 = line.find(",", pos5 + 1);

        // Extrat name, rollno,   dob,  address,  branch, sem and sub from the line

        name = line.substr(0, pos1);
        roll = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        dob = line.substr(pos2 + 1, pos3 - pos2 - 1);
        address = line.substr(pos3 + 1, pos4 - pos3 - 1);
        branch = line.substr(pos4 + 1, pos5 - pos4 - 1);
        sem = line.substr(pos5 + 1, pos6 - pos5 - 1);
        sub = stoi(line.substr(pos6 + 1));
    }

    // Function to modify/replace record in file
    void modify_record(ifstream &file, int mod)
    {

        string old_line = name + "," + to_string(roll) + "," + dob + "," + address + "," + branch + "," + sem + "," + to_string(sub);
        ofstream t_file("temp.txt");
        if (mod == 1)
        {

            int choice;
            cout << "\n\t--------- Modify Information --------\n";
            cout << "\n\t------> Choose the Index of Details You Want to Update <-------\n";
            cout << " 1. Student Name        ===>      " << name << "\n";
            cout << " 2. Roll No.            ===>      " << roll << "\n";
            cout << " 3. Date Of Birth       ===>      " << dob << "\n";
            cout << " 4. Address             ===>      " << address << "\n";
            cout << " 5. Branch              ===>      " << branch << "\n";
            cout << " 6. Semester            ===>      " << sem << "\n";
            cout << " 7. No. of subjects     ===>      " << sub << "\n";

            cout << " Enter Your Choice ====> ";
            cin >> choice;
            switch (choice) // switch case to select the choice
            {
            case 1:
                cout << "\n Enter Student Name :--->";
                cin >> name;
                cout << "\t---- Name Updated ----\n";
                break;

            case 2:
                cout << "\n Enter Roll No. :--->";
                cin >> roll;
                cout << "\t---- Roll No. Updated ----\n";
                break;

            case 3:
                cout << "\n Enter Date Of Birth  :--->";
                cin >> roll;
                cout << "\t---- Date Of Birth Updated ----\n";
                break;

            case 4:
                cout << "\n Enter Address :--->";
                cin >> address;
                cout << "\t---- Adress Updated ----\n";
                break;

            case 5:
                cout << "\n Enter Branch :--->";
                cin >> branch;
                cout << "\t---- Branch Updated ----\n";
                break;

            case 6:
                cout << "\n Enter Semester :--->";
                cin >> sem;
                cout << "\t---- Semested Updated ----\n";
                break;

            case 7:
                cout << "\n Enter No. of Subjects :--->";
                cin >> sub;
                cout << "\t---- No. of Subjects Updated ----\n";
                break;

            default:
                cout << "\n ------ Invalid Choice ------\n ******** Try again ********\n\n";
                break;
            }
        }
        else
        {

            this->print();
            cout << "\nRecord Deleted\n";
        }

        file.seekg(0); // return file poonter to begining;
        while (!file.eof())
        {
            string f_line;
            file>>f_line>>ws;
            
            string New_line = name + "," + to_string(roll) + "," + dob + "," + address + "," + branch + "," + sem + "," + to_string(sub);
            if (f_line == old_line)
            {
                if (mod == 2)
                {
                    continue;
                }

                t_file << New_line << endl;
            }
            else
            {
                t_file << f_line << endl;
            }
        }
        t_file.close();
        file.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");
    }
};

// Function to add a new student record to file
void addStudentRecord()
{
    ofstream file("students.txt", ios_base::app);

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
            cout << "\n\tStudent record found " << endl;
            student.print();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tStudent record not found" << endl;
    }

    file.close();
}

// Function to Edit student Record in file
void editStudentRecord(int n)
{
    ifstream file("students.txt");

    if (!file.is_open())
    {
        cout << "\nError opening file\n";
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
            student.modify_record(file, n);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tStudent record not found" << endl;
    }
}

// Main function to call other functions
int main()
{
    int choice;

    do
    {
        cout << endl;
        cout << "1. Add student record\n2. Search student record\n3. Edit student record\n4. Delete student record\n5. Exit\nEnter choice : ";
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
        case 3:
            // Edit student record logic
            editStudentRecord(1);
            break;
        case 4:
            // Delete student record logic
            editStudentRecord(2);
            break;
        case 5:
            cout << "\n-->Exit Program<---\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}