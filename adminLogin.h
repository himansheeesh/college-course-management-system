#include <iostream>
#include <fstream>
#include <string.h> //strcmp,strcpy etc. in global namespace.
#include <string>   //string,getline,wstring,stoi.
#include <vector>   //begin(),end()
#include <sstream>  //string stream 
#include <algorithm>

using namespace std;

bool checkdate(int d, int m, int y)
{
    if (y < 1000)
    {
        return false;
    }
    if (y > 2030)
    {
        return false;
    }
    if (!(1 <= m && m <= 12))
        return false;
    if (!(1 <= d && d <= 31))
        return false;
    if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
        return false;
    if ((d == 30) && (m == 2))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 != 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 400 == 0))
        return true;
    if ((m == 2) && (d == 29) && (y % 100 == 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 == 0))
        return true;

    return true;
}

const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

int countLeapYearDays(int d[])
{
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}

int countNoOfDays(int date1[], int date2[])
{
    long int dayCount1 = (date1[2] * 365);
    dayCount1 += monthDays[date1[1]];
    dayCount1 += date1[0];
    dayCount1 += countLeapYearDays(date1);
    long int dayCount2 = (date2[2] * 365);
    dayCount2 += monthDays[date2[1]];
    dayCount2 += date2[0];
    dayCount2 += countLeapYearDays(date2);
    return (abs(dayCount1 - dayCount2));
}

bool validateString(string str) {
    bool result = true;
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            cout<<"\n Please enter a string value only."<<endl;
            result = false;
            break;
        }
    }
    return result;
}

int batchID, nod, nop, salary;
string technology, startDate, endDate, venueDetail, month, facultyName;

class admin
{
public:
    void createSchedule() 
    {
        cout << "\n\nBelow are the mandatory details for creating new schedule" << endl;
        cout << "\n1. Batch Id                        2. Course Name" << endl;
        cout << "3. Start Date                      4. End Date" << endl;
        cout << "5. No. of Students                 6. Salary for course"<< endl;

        cout << "\nNow please enter the details below carefully." << endl;

        cout << "Enter the batch id : ";
        cin >> batchID;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cin.ignore();

        cout << "Enter the technology name : ";
        getline(cin, technology);
        
        if (!validateString(technology)) {
            createSchedule();
        }

        cout << "Enter the start date of traning (Use Format {DD-MM-YYYY}) : ";
        getline(cin, startDate);

        string T;
        int arr[3];
        int i = 0, result;

        stringstream X(startDate);
        while (getline(X, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }

        result = checkdate(arr[0], arr[1], arr[2]);
        int date1[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the end date of training (Use Format {DD-MM-YYYY}) : ";
        getline(cin, endDate);

        stringstream Y(endDate);
        while (getline(Y, T, '-'))
        {
            int r = stoi(T);
            arr[i] = r;
            i++;
        }
        result = checkdate(arr[0], arr[1], arr[2]);
        int date2[] = {arr[0], arr[1], arr[2]};
        i = 0;

        if (result == 0)
        {
            cout << "\nOops! you have entered wrong date/format." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        int nod = countNoOfDays(date1,date2);

        cout << "Enter the total number of participants : ";
        cin >> nop;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nOops! wrong input." << endl;
            cout << "\nNow please enter all the details once again for better result." << endl;
            createSchedule();
        }

        cout << "Enter the salary for per day : ";
        cin >> salary;

        ofstream f1("/Users/himan/OneDrive/Desktop/schedule.csv", ios::app);

        f1 << batchID << " " << technology << " " << startDate << " " << endDate << " " << nod << " " << nop << " " << salary << endl;

        cout << "\n New Schedule Has Been Created.\n"
             << endl;

        f1.close();

        string opt;

        cout << "\nDo you want to create another schdedule (yes/no) : ";
        cin >> opt;
 
        if (opt == "yes" || opt == "y" || opt == "YES" || opt == "Y")
        {
            createSchedule();
        }
        else
        {
            adminModules();
        }
    }


    void allotTrainer()   
    {
        string techName;
        int flag = 0;
        cout << "\n Please enter a faculty name : ";
        cin >> facultyName;

        if (!validateString(facultyName)) {
            allotTrainer();
        }

        cout << "\n Please enter a technology name for which you want to assign tariner : ";
        cin >> techName;

        if (!validateString(techName)) {
            allotTrainer();
        }

        ifstream f2("/Users/himan/OneDrive/Desktop/schedule.csv");

        while (f2 >> batchID >> technology >> startDate >> endDate >> nod >> nop >> salary)
        {
            transform(technology.begin(), technology.end(), technology.begin(), ::tolower);
            transform(techName.begin(), techName.end(), techName.begin(), ::tolower);

            ofstream f3("/Users/himan/OneDrive/Desktop/trainerallotment.csv", ios::app);
            if (technology == techName)
            {
                flag = 1;
                f3 << batchID << " " << technology << " " << startDate << " " << endDate << " " << nod  << " " << nop << " "  << salary << " "<< facultyName << endl;
            }

            if(flag == 1){
                ofstream f4("/Users/himan/OneDrive/Desktop/facultylogin.csv", ios::app);
                f4 << facultyName << " " << batchID << " " << technology << endl;
            }
        }

        if (flag == 0)
        {
            cout << "\nTechnology is not found" << endl;
        }

        string opt;
        cout << "\nDo you want to continue with allotment trainer (yes/no) : ";
        cin >> opt;

        if (opt == "yes" || opt == "Y" || opt == "YES")
        {
            allotTrainer();
        }
        else
        {
            cout << "\nTaking you on your dashboard..." << endl;
            adminModules();
        }
    }


    void adminModules()
    {
        cout << "\nHere's your Dashboard \nPlease enter your choice to perform particular tasks" << endl;
        cout << "\n\n--------------------------------------------------------" << endl;
        cout << "\tEnter 1 -> To Create New Schedule" << endl;
        cout << "\tEnter 2 -> To Allot A Trainer" << endl;
        cout << "\tEnter 3 -> To Quit From This Session" << endl;
        cout << "--------------------------------------------------------" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nPlease enter a number!!" << endl;
            adminModules();
        }
        else
        {
            switch (choice)
            {
            case 1:
                createSchedule();
                break;
            case 2:
                allotTrainer();
                break;
            case 3:
                int n;
                cout << "\nWhere you want to move \nPlease choose from below options" << endl;
                cout << "\nChoose 1 -> Go Back To Dashboard \nChoose 2 -> Exit From The System" << endl;

                cout << "\n\nPlease enter your choice here : ",
                    cin >> n;

                if (n == 1)
                {
                    adminModules();
                }
                else if (n == 2)
                {
                    cout << "See you again" << endl;
                    exit(0);
                }
                else
                {
                    cout << "Please choose correct option" << endl;
                    adminModules();
                }
                break;

            default:
                cout << "Please choose valid Option" << endl;
                adminModules();
                break;
            }
        }
    }
};
