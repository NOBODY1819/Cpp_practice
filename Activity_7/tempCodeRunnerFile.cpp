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
    void input()// Function to input details for course addition
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
    void display()// Display function to display course details
    {
        
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
void search() // Function to show details of course
{
    this->display();
}
public:
    void update() //Function to update course details
    {
        int choice;
        cout << "\n\t--------- Update Information --------\n";
        cout << "\n\t------> Choose the Index of Details You Want to Update <-------\n";
        cout << " 1. Course Name     ===>      " << c_name << "\n";
        cout << " 2. Course ID       ===>      " << c_id << "\n";
        cout << " 3. Course Sem      ===>      " << c_sem << "\n";
        cout << " 4. Course Credits  ===>      " << c_credit << "\n";
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

    int c_delete(int rep, course *c) // Function to delete course record
    {
        *this = c[rep];
        cout << "\n---- Record deleted ----";
        return rep - 1;
    }
};