#include<iostream>
#include<fstream>
using namespace std;

class Temp {
public:
    fstream file;
    string bookname, bookid, selectbookname, selectbookid;

    void showbooks();
    void updatebooks();
    void getbooks();
};

class Student : public Temp {
public:
    string searchusers, searchids;
    string studentid, studentname, branch;
    void studentlogin();
    void studentsignup();
} obj1;

class Admin : public Temp {
public:
    int a;
    string searchuser, searchid;
    string adminid, adminname;
    void adminsignup();
    void adminlogin();
} obj2;

void Temp::updatebooks() {
    int n;  // Number of books to update
    cout << "Enter the number of books to update: ";
    cin >> n;
    cin.ignore();  // To ignore the newline character left by cin

    file.open("BookData.txt", ios::out | ios::app);  // Open file in append mode
    if (!file.is_open()) {
        cout << "Error: Could not open or create BookData.txt" << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "Book Name: ";
        getline(cin, bookname);  // Input book name

        cout << "Book ID: ";
        getline(cin, bookid);  // Input book ID

        // Write book details to file
        file << bookname << "*" << bookid << endl;
        cout << "Book '" << bookname << "' with ID '" << bookid << "' has been added to the file." << endl;
    }

    file.close();  // Close the file after writing
    cout << "Book data successfully updated!" << endl;
}

void Temp::showbooks() {
    file.open("BookData.txt", ios::in);  // Open the file in read mode
    if (!file.is_open()) {
        cout << "Error: Could not open BookData.txt" << endl;
        return;
    }

    cout << "\n--- List of Books ---\n";
    while (std::getline(file, bookname, '*') && std::getline(file, bookid, '\n')) {
        cout << "Book Name: " << bookname << "     Book ID: " << bookid << endl;
    }

    file.close();  // Close the file after reading
}

void Temp::getbooks() {
    int n;  // Number of books to get
    cout << "Choose the number of books you want to select: ";
    cin >> n;
    cin.ignore();  // To ignore the newline character left by cin

    for (int i = 0; i < n; i++) {
        cout << "Book Name: ";
        getline(cin, selectbookname);
        cout << "Book ID: ";
        getline(cin, selectbookid);

        bool found = false;
        file.open("BookData.txt", ios::in);
        if (!file.is_open()) {
            cout << "Error: Could not open BookData.txt" << endl;
            return;
        }

        while (std::getline(file, bookname, '*') && std::getline(file, bookid, '\n')) {
            if (selectbookname == bookname && selectbookid == bookid) {
                cout << selectbookname << " is selected." << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Book not found: " << selectbookname << " with ID: " << selectbookid << endl;
        }

        file.close();  // Close the file after reading
    }
}

void Admin::adminsignup() {
    cout << "Enter your Username :: ";
    cin.ignore();
    getline(cin, adminname);
    cout << "\nEnter your Id :: ";
    getline(cin, adminid);

    file.open("AdminloginData.txt", ios::out | ios::app);
    file << adminname << "*" << adminid << endl;
    file.close();
}

void Admin::adminlogin() {
    string securitykey;
    cout << "........login........" << endl;
    cout << "\nEnter your username :: ";
    cin.ignore();
    getline(cin, searchuser);
    cout << "\nEnter your Id :: ";
    getline(cin, searchid);

    file.open("AdminloginData.txt", ios::in);
    getline(file, adminname, '*');
    getline(file, adminid, '\n');

    while (!file.eof()) {
        if (adminname == searchuser && adminid == searchid) {
            cout << "\nSecurity key\n";
            cin >> securitykey;
            if (securitykey == "Tarzen") {
                cout << "\nLogin successful!" << endl;

                // Start a loop for admin actions
                char choice;
                do {
                    cout << "\n1 - Show All Books";
                    cout << "\n2 - Update Books";
                    cout << "\n3 - Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case '1':
                            obj2.showbooks();
                            break;
                        case '2':
                            obj2.updatebooks();
                            break;
                        case '3':
                            cout << "Exiting admin menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Try again." << endl;
                    }
                } while (choice != '3');  // Continue until the admin chooses to exit
            }
            break;
        }
        getline(file, adminname, '*');
        getline(file, adminid, '\n');
    }
    file.close();
}

void Student::studentsignup() {
    cout << "Enter your Username :: ";
    cin.ignore();
    getline(cin, studentname);
    cout << "\nEnter your Id :: ";
    getline(cin, studentid);

    file.open("studentloginData.txt", ios::out | ios::app);
    file << studentname << "*" << studentid << endl;
    file.close();
}

void Student::studentlogin() {
    cout << "........login........" << endl;
    cout << "\nEnter your username :: ";
    cin.ignore();
    getline(cin, searchusers);
    cout << "\nEnter your Id :: ";
    getline(cin, searchids);

    file.open("studentloginData.txt", ios::in);
    getline(file, studentname, '*');
    getline(file, studentid, '\n');

    while (!file.eof()) {
        if (studentname == searchusers && studentid == searchids) {
            cout << "\nLogin successful!" << endl;

            // Start a loop for student actions
            char choice;
            do {
                cout << "\n1 - Show All Books";
                cout << "\n2 - Select Books";
                cout << "\n3 - Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        obj1.showbooks();
                        break;
                    case '2':
                        obj1.getbooks();
                        break;
                    case '3':
                        cout << "Exiting student menu..." << endl;
                        break;
                    default:
                        cout << "Invalid choice! Try again." << endl;
                }
            } while (choice != '3');  // Continue until the student chooses to exit
            return;
        }
        else{
            cout<<"\nInvalid username and password !\n"<<endl;
            break;
        }
        getline(file, studentname, '*');
        getline(file, studentid, '\n');
    }

    file.close();
}

int main() {
    char loginchoice;
    // Use a loop to continuously show the main menu
    do {
        cout << "...Welcome to library management system..." << endl;
        cout << "\n1 - Student signup";
        cout << "\n2 - Admin signup";
        cout << "\n3 - Student login";
        cout << "\n4 - Admin login";
        cout << "\n5 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> loginchoice;

        switch (loginchoice) {
            case '1':
                obj1.studentsignup();
                break;
            case '2':
                obj2.adminsignup();
                break;
            case '3':
                obj1.studentlogin();
                break;
            case '4':
                obj2.adminlogin();
                break;
            case '5':
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (loginchoice != '5');  // Exit the loop when '5' is selected

    return 0;
}
