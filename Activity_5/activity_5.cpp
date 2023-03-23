using namespace std;
#include <iostream>
#include <string.h>

class student // Creation of class student
{             // Declaration of Data Members
private:
    char name[20];
    int roll;
    char dob[15];
    char address[20];
    char branch[10];
    char sem[10];
    int sub;
    float max_marks = 0, min_marks = 100, m_obtained[8], m_max[8];
    string m_name[8], m_code[8];
    // Member functions
public:
    student()
    {
        // default constructor
    }
    void input()
    { // Creation of input function
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
        for (int i = 0; i < sub; i++)
        {
            cout << "\n\t--Enter details for subject " << i + 1 << " --\n";
            cout << "Enter name :";
            cin >> m_name[i];
            cout << "Enter code :";
            cin >> m_code[i];
            cout << "Enter Maximum marks :";
            cin >> m_max[i];
            cout << "Enter Marks Obtained :";
            cin >> m_obtained[i];
            if (max_marks < m_obtained[i])
            {
                max_marks = m_obtained[i];
            }
            if (min_marks > m_obtained[i])
            {
                min_marks = m_obtained[i];
            }
        }
    }

public:
    ~student()
    { // Creation of Destructor
    }

public:
    void search()
    { // Creation of search function
        cout << "\n\tInformation for student\n";
        cout << "Name = " << name << endl;
        cout << "Roll no. = " << roll << endl;
        cout << "D.O.B = " << dob << endl;
        cout << "Address = " << address << endl;
        cout << "Branch = " << branch << endl;
        cout << "Semester = " << sem << endl;
        cout << "No. of Subjects = " << sub << endl;
        for (int i = 0; i < sub; i++)
        {
            cout << "\n\t--Details for subject " << i + 1 << " --\n";
            cout << "\nName : " << m_name[i];
            cout << "\nCode :" << m_code[i];
            cout << "\nMaximum marks :" << m_max[i];
            cout << "\nMarks Obtained :" << m_obtained[i];
        }
        cout << "\nMaximum Marks Obtained :" << max_marks << endl;
        cout << "Minimum Marks Obtained :" << min_marks << endl;
    }
    int r_rollno()
    {
        return roll;
    }
    void update()
    {
        int choice;
        cout << "\n\t--------- Update Information --------\n";
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
    int r_delete(int rep, student *s)
    {
        *this = s[rep];
        cout << "\n---- Record deleted ----";
        return rep - 1;
    }
    void result()
    {

        float marks = 0, total = 0, percent;
        for (int i = 0; i < sub; i++)
        {
            marks = marks + m_obtained[i];
            total = total + m_max[i];
        }

        percent = (marks / total) * 100;

        cout << "Name = " << name << endl;
        cout << "Roll no. = " << roll << endl;
        cout << "Branch = " << branch << endl;
        cout << "Semester = " << sem << endl;
        cout << "No. of Subjects = " << sub << endl;
        for (int i = 0; i < sub; i++)
        {
            cout << "\n\t--Details for subject " << i + 1 << " --\n";
            cout << "\nName : " << m_name[i];
            cout << "\nCode :" << m_code[i];
            cout << "\nMaximum marks :" << m_max[i];
            cout << "\nMarks Obtained :" << m_obtained[i];
        }
        cout << "\nMaximum Marks Obtained :" << max_marks << endl;
        cout << "Minimum Marks Obtained :" << min_marks << endl;
        cout << "Total Percentage : " << percent << "%\n";
    }
};

class course // Creation of class course
{            // Declaration of Data Members
private:
    string c_name, c_id, c_sem;
    int c_credit;
    float c_fee;

    // Member functions
public:
    course()
    { // Creation of Constructor
    }

public:
    void input()
    {
        cout << "\tEnter Details for Course" << endl;
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

public:
    void display()
    {
        // Creation of display function
        cout << "\tInformation of Course:" << endl;
        cout << "Course name = " << c_name << endl;
        cout << "Course ID = " << c_id << endl;
        cout << "Course sem = " << c_sem << endl;
        cout << "Course credits = " << c_credit << endl;
        cout << "Course fee = " << c_fee << endl;
    }

    string r_id()
    {
        return c_id;
    }

public:
    void update()
    {
        int choice;
        cout << "\n\t--------- Update Information --------\n";
        cout << "\n\t------> Choose the Index of Details You Want to Update <-------\n";
        cout << " 1. Course Name        ===>      " << c_name << "\n";
        cout << " 2. Course ID            ===>      " << c_id << "\n";
        cout << " 3. Course Sem       ===>      " << c_sem << "\n";
        cout << " 4. Course Credits          ===>      " << c_credit << "\n";
        cout << " 5. Course Fee      ===>      " << c_fee << "\n";

        cout << " Enter Your Choice ====> ";
        cin >> choice;
        switch (choice) // switch case to select the choice
        {
        case 1:
            cout << "\n Enter Course Name :--->";
            cin >> c_name;
            cout << "\t---- Name Updated ----\n";
            break;

        case 2:
            cout << "\n\n Enter ID :--->";
            cin >> c_id;
            cout << "\t---- ID Updated ----\n";
            break;

        case 3:
            cout << "\n\n Enter Semester  :--->";
            cin >> c_sem;
            cout << "\t---- Semester Updated ----\n";
            break;

        case 4:
            cout << "\n\n Enter Credits :--->";
            cin >> c_credit;
            cout << "\t---- Credit Updated ----\n";
            break;

        case 5:
            cout << "\n\n Enter Fee :--->";
            cin >> c_fee;
            cout << "\t---- Fee Updated ----\n";
            break;

        default:
            cout << "\n\n ------ Invalid Choice ------\n ******** Try again ********\n\n";
            break;
        }
    }
};

int main()
{
    int ch, count = -1, r_r, num, retr = 0;
    student s[10];

    cout << "\n\t<---MAIN MENU--->\nEnter\n1 -> To Enter Student System\n2 -> To Enter Course System\n0 -> Exit\t:";
    cin >> ch;

    if (ch == 1)
    {
        cout << "Enter no. of students:";
        cin >> num;
        do
        {
            cout << "\n\t<-------STUDENT MENU------->\nEnter\n1 -> For New Entery\n2 -> For Updating\n3 -> For Search Data\n4 -> For Deleting Record\n5 -> For Result\n0 -> Exit\t:";
            cin >> ch;

            switch (ch)
            {
            case 1:
                if (count + 1 == num)
                {
                    cout << "*****Record Full******";
                    break;
                }
                count++;
                s[count].input();
                break;
            case 2:
                if (count == -1)
                {
                    cout << "*****NO data in System******";
                    break;
                }

                cout << "Enter Roll no. of student to update:";
                cin >> r_r;
                for (int i = 0; i <= count; i++)
                {

                    if (r_r == s[i].r_rollno())
                    {
                        s[i].update();
                        goto retr;
                    }
                }
                cout << "***No Record Found with provided Roll No.***\n";
            retr:
                break;

            case 3:
                if (count == -1)
                {
                    cout << "*****NO data in System******";
                    break;
                }
                cout << "Enter Roll no. of student to search :";
                cin >> r_r;
                for (int i = 0; i <= count; i++)
                {

                    if (r_r == s[i].r_rollno())
                    {
                        s[i].search();
                        goto retr;
                    }
                }
                cout << "***No Record Found with provided Roll No.***\n";
                break;
            case 4:
                if (count == -1)
                {
                    cout << "*****NO data in System******";
                    break;
                }
                cout << "Enter Roll no. of student :";
                cin >> r_r;
                for (int i = 0; i <= count; i++)
                {

                    if (r_r == s[i].r_rollno())
                    {
                        count = s[i].r_delete(count, s);
                        goto retr;
                    }
                }
                cout << "***No Record Found with provided Roll No.***\n";
                break;
            case 5:
                if (count == -1)
                {
                    cout << "*****NO data in System******";
                    break;
                }
                cout << "Enter Roll no. of student for result :";
                cin >> r_r;
                for (int i = 0; i <= count; i++)
                {

                    if (r_r == s[i].r_rollno())
                    {
                        s[i].result();
                        goto retr;
                    }
                }
                cout << "***No Record Found with provided Roll No.***\n";
                break;

            case 0:
                cout << "\n---------> Exit Terminal <---------";
                break;

            default:
                cout << "\n------Invalid choice-------\n\t*******Exit*********\n";
                break;
            }
        } while (ch != 0);
    }
    else if (ch == 2)
    {
        string c_name, c_id, c_sem, r_id;
        int c_credit, c_count = -1, c_retr, c_num;
        float c_fee;
        course c[10];
        cout << "Enter number of courses :";
        cin >> c_num;
        do
        {

            cout << "\n\t<-------COURSE MENU------->\nEnter\n1 -> For New Entery\n2 -> For Updating\n3 -> For Search Data\n4 -> For Deleting Record\n0 -> Exit\t:";
            cin >> ch;

           
                switch (ch)
                {
                case 1:
                    if (c_count + 1 == c_num)
                    {
                        cout << "*****Record Full******";
                        break;
                    }
                    c_count++;
                    c[c_count].input();
                    break;
                case 2:
                    if (c_count == -1)
                    {
                        cout << "*****NO data in System******";
                        break;
                    }

                    cout << "Enter Course Id to update:";
                    cin >> r_id;
                    for (int i = 0; i <= c_count; i++)
                    {

                        if (r_id == c[i].r_id())
                        {
                            c[i].update();
                            goto c_retr;
                        }
                    }
                    cout << "***No Record Found with provided Course ID***\n";
                c_retr:
                    break;

                case 3:
                    cout << "FUNCTION UNDER DEVELOPMENT";
                //For searching 
                case 4:
                    cout << "FUNCTION UNDER DEVELOPMENT";
                   //For deleting
                    break;

                case 0:
                    cout << "\n---------> Exit Terminal <---------";
                    break;

                default:
                    cout << "\n------Invalid choice-------\n\t*******Exit*********\n";
                    break;
                }
            
        } while (ch != 0);
    }
    else if (ch == 0)
    {
        cout << "\n---------> Exit Terminal <---------";
    }
    else
    {
        cout << "\n------Invalid choice-------\n\t*******Exit*********\n";
    }

    return 0;
}