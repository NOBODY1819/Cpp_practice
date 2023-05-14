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
                cout << "\n\n Enter Roll No. :--->";
                cin >> roll;
                cout << "\t---- Roll No. Updated ----\n";
                break;

            case 3:
                cout << "\n\n Enter Date Of Birth  :--->";
                cin >> roll;
                cout << "\t---- Date Of Birth Updated ----\n";
                break;

            case 4:
                cout << "\n\n Enter Address :--->";
                cin >> address;
                cout << "\t---- Adress Updated ----\n";
                break;

            case 5:
                cout << "\n\n Enter Branch :--->";
                cin >> branch;
                cout << "\t---- Branch Updated ----\n";
                break;

            case 6:
                cout << "\n\n Enter Semester :--->";
                cin >> sem;
                cout << "\t---- Semested Updated ----\n";
                break;

            case 7:
                cout << "\n\n Enter No. of Subjects :--->";
                cin >> sub;
                cout << "\t---- No. of Subjects Updated ----\n";
                break;

            default:
                cout << "\n\n ------ Invalid Choice ------\n ******** Try again ********\n\n";
                break;
            }
        }
        else
        {

            this->print();
            cout << "\nRecord Deleted\n";
        }

        file.seekg(0);
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

// Course class to represent each record
class Course
{
private:
    // Data members
    string c_name, c_id, c_sem;
    int c_credit;
    float c_fee;
public:// Member functions
    // Constructor to initialize member variables
    Course(string name = "abc", string id = "com-101", string sem = "1st", int credit = 10, float fee = 1000.00)
    {
        c_name = name;
        c_id = id;
        c_sem = sem;
        c_credit = credit;
        c_fee = fee;
    }

    // Function to print the Course record
    void print()
    {
        cout << "Course Name = " << c_name << endl;
        cout << "Course ID = " << c_id << endl;
        cout << "Course Semester = " << c_sem << endl;
        cout << "Course Credits = " << c_credit << endl;
        cout << "Course Fee = " << c_fee << endl;
    }

    // Function to return Course ID
    string r_id()
    {
        return c_id;
    }

    // Function to write the Course record to a file
    void WriteToFile(ofstream &file)
    {
        file << c_name << "," << c_id << "," << c_sem << "," << c_credit << "," << c_fee << endl;
    }

    // Function to read the Course record from a file
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

        // Extrat c_name, c_id, c_sem, c_credit and c_fee from the line

        c_name = line.substr(0, pos1);
        c_id = line.substr(pos1 + 1, pos2 - pos1 - 1);
        c_sem = line.substr(pos2 + 1, pos3 - pos2 - 1);
        c_credit = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        c_fee = stof(line.substr(pos4 + 1));
    }

    // Function to modify/replace record in file
    void modify_record(ifstream &file, int mod)
    {

        string old_line = c_name + "," + c_id + ","+ c_sem+","+to_string(c_credit)+","+to_string(c_fee);
        ofstream t_file("temp.txt");
        if (mod == 1)
        {
            int choice;
            cout << "\n\t--------- Modify Information --------\n";
            cout << "\n\t------> Choose the Index of Details You Want to Update <-------\n";
            cout << " 1. course Name        ===>      " << c_name << "\n";
            cout << " 2. Course ID          ===>      " << c_id << "\n";
            cout << " 3. Course Semester    ===>      " << c_sem << "\n";
            cout << " 4. Course Credits     ===>      " << c_credit << "\n";
            cout << " 5. Course Fee         ===>      " << c_fee << "\n";

            cout << " Enter Your Choice ====> ";
            cin >> choice;
            switch (choice) // switch case to select the choice
            {
            case 1:
                cout << "\n Enter New Course Name :--->";
                cin >> c_name;
                cout << "\t---- Name Updated ----\n";
                break;

            case 2:
                cout << "\n\n Enter New Course Id :--->";
                cin >> c_id;
                cout << "\t---- ID Updated ----\n";
                break;

            case 3:
                cout << "\n\n Enter New Semester  :--->";
                cin >> c_sem;
                cout << "\t---- Semester Updated ----\n";
                break;

            case 4:
                cout << "\n\n Enter New Credits :--->";
                cin >> c_credit;
                cout << "\t---- Credits Updated ----\n";
                break;

            case 5:
                cout << "\n\n Enter New Fee :--->";
                cin >> c_fee;
                cout << "\t---- Fee Updated ----\n";
                break;

            default:
                cout << "\n\n <------> Invalid Choice <------>\n ******** Try again ********\n\n";
                break;
            }
        }
        else
        {

            this->print();
            cout << "\nRecord Deleted\n";
        }

        file.seekg(0);
        while (!file.eof())
        {
            string f_line;
            file>>f_line>>ws;
            
            string New_line = c_name + "," + c_id + ","+ c_sem+","+to_string(c_credit)+","+to_string(c_fee);
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
        remove("courses.txt");
        rename("temp.txt", "courses.txt");
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
    cout << "\n\tEnter Details for course" << endl;
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

// Function to add new course to file
void addCourseRecord()
{
ofstream file("courses.txt", ios_base::app);

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    // Get input from user
    string name;
    string id;
    string sem;
    int credit;
    float fee;
    fflush(stdin);
    cout << "\n\tEnter Details for course" << endl;
    cout << "Enter Course Name: ";
    cin >> name;
    cout << "Enter Course ID: ";
    cin >> id;
    cout << "Enter Course Semester: ";
    cin >> sem;
    cout << "Enter Crouse Credits: ";
    cin >> credit;
    cout << "Enter Course fee: ";
    cin >> fee;

    // Create a new Course object and write it to file
    Course course(name, id, sem, credit, fee);
    course.WriteToFile(file);

    file.close();
}

// Function to search for course in the file
void searchCourseRecord()
{
 ifstream file("courses.txt");

    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    // Get input from user
    string id;
    cout << "Enter Course ID to search : ";
    cin >> id;

    // Read each record from file and check for the Course ID
    Course course;
    bool found = false;
    while (file.good())
    {
        course.readFromFile(file);

        if (file.eof())
            break; // Exit loop if end of file is reached

        if (course.r_id() == id)
        {
            cout << "\n\tCourse record found " << endl;
            course.print();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tCourse record not found" << endl;
    }

    file.close();
}

// Function to Edit Course Record in file
void editCourseRecord(int n)
{
    ifstream file("courses.txt");

    if (!file.is_open())
    {
        cout << "\nError opening file\n";
        return;
    }
   
    // Get input from user
    string id;
    cout << "Enter Course ID to search : ";
    cin >> id;

    // Read each record from file and check for the Course ID
    Course course;
    bool found = false;
    while (file.good())
    {
        course.readFromFile(file);

        if (file.eof())
            break; // Exit loop if end of file is reached

        if (course.r_id() == id)
        {
            course.modify_record(file, n);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n\tCourse record not found" << endl;
    }
}

// Main function to call other functions
int main()
{
    int choice;
    cout << "\n\t<---MAIN MENU--->\nEnter\n1 -> To Enter Student System\n2 -> To Enter Course System\n0 -> Exit\t:";
    cin >> choice;

    if (choice==1)
    {
    
    do
    {
        cout << endl;
        cout<<"<-----STUDENT MENU---->\n";
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
    
    }else if (choice==2)    
    {
        
    do
    {
        cout << endl;
        cout<<"<----COURSE MENU----->\n";
        cout << "1. Add Course record\n2. Search Course record\n3. Edit Course record\n4. Delete Course record\n5. Exit\nEnter choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            // Add student record logic here
            cout << "\nAdding New Course Record\n";
            addCourseRecord();
            break;
        case 2:
            // Search Course record logic here
            cout << "\nSeacrhing for Course\n";
            searchCourseRecord();
            break;
        case 3:
            // Edit student record logic
            editCourseRecord(1);
            break;
        case 4:
            // Delete student record logic
            editCourseRecord(2);
            break;
        case 5:
            cout << "\n-->Exit Program<---\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
            break;
        }
    } while (choice != 5);
    
    }else{
        cout<<"<---INVALID CHOICE---->\n EXIT PROGRAM";
    }
    
    return 0;
}