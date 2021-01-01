#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node
{
    node() {}
    node(string name, int age, string SSN, string gender, string disease, string condition, int date, int month, int year)
    {
        this->name = name;
        this->age = age;
        this->socialSecurityNumber = SSN;
        this->gender = gender;
        this->disease = disease;
        this->condition = condition;
        this->date = date;
        this->month = month;
        this->year = year;
    }
    string name;
    int age;
    string socialSecurityNumber;
    string gender;
    string disease;
    string condition;
    int date, month, year;
    int priority;
    string doctor;
    node *next = nullptr;
    node *prev = nullptr;
};
node *head = nullptr;
node *tail = nullptr;

const int hospitals[4][2] = {{80, 27}, {36, 54}, {60, 67}, {11, 18}};
const int ambulance[] = {0, 0};

void addPatient(node *patient);
string convertToUpperCase(string message)
{
    for (int i = 0; i < message.length(); ++i)
    {
        message[i] = toupper(message[i]);
    }
    return message;
}
bool checkString(string message)
{
    for (int i = 0; i < message.length(); i++)
    {
        if (!isalpha(message[i]))
        {
            return false;
        }
    }
    return true;
}

bool checkStringWithSpaces(string message)
{
    for (int i = 0; i < message.length(); i++)
    {
        if (!(isalpha(message[i]) || isspace(message[i])))
        {
            return false;
        }
    }
    return true;
}

bool checkNumber(string message)
{
    for (int i = 0; i < message.length(); i++)
    {
        if (!isdigit(message[i]))
        {
            return false;
        }
    }
    return true;
}

void addToFile(node *person)
{
    ofstream myFile;
    myFile.open("Patient Record.txt", ios_base::app);
    myFile << person->name + "\n";
    myFile << to_string(person->age) + "\n";
    myFile << person->socialSecurityNumber + "\n";
    myFile << person->gender + "\n";
    myFile << person->disease + "\n";
    myFile << person->condition + "\n";
    myFile << to_string(person->date) + "\n";
    myFile << to_string(person->month) + "\n";
    myFile << to_string(person->year) + "\n";
    myFile.close();
}

void readFromFile()
{
    ifstream myFile;
    myFile.open("Patient Record.txt");
    while (myFile.peek() != EOF)
    {
        node *person = new node;
        getline(myFile, person->name);
        string age, day, month, year;
        getline(myFile, age);
        getline(myFile, person->socialSecurityNumber);
        getline(myFile, person->gender);
        getline(myFile, person->disease);
        getline(myFile, person->condition);
        getline(myFile, day);
        getline(myFile, month);
        getline(myFile, year);
        person->age = stoi(age);
        person->date = stoi(day);
        person->month = stoi(month);
        person->year = stoi(year);
        addPatient(person);
    }
    myFile.close();
}
void removeFromFile(string name)
{
    ofstream myFile1;
    myFile1.open("temp.txt");
    ifstream myFile2;
    myFile2.open("Patient Record.txt");
    while (myFile2.peek() != EOF)
    {
        string line, neglect;
        getline(myFile2, line);
        if (line == convertToUpperCase(name))
        {
            for (int i = 0; i < 8; i++)
            {
                getline(myFile2, neglect);
            }
        }
        else
        {
            myFile1 << line + "\n";
        }
    }
    myFile1.close();
    myFile2.close();
    remove("Patient Record.txt");
    rename("temp.txt", "Patient Record.txt");
}

// void updateFile(string name)
// {
//     node *person = search(name);
//     ofstream myFile1;
//     myFile1.open("temp.txt");
//     ifstream myFile2;
//     myFile2.open("Patient Record.txt");
//     while (myFile2.peek() != EOF)
//     {
//         string line, neglect;
//         getline(myFile2, line);
//         if (line == convertToUpperCase(name))
//         {
//             myFile1 << person->name + "\n";
//             myFile1 << to_string(person->age) + "\n";
//             myFile1 << person->socialSecurityNumber + "\n";
//             myFile1 << person->gender + "\n";
//             myFile1 << person->disease + "\n";
//             myFile1 << person->condition + "\n";
//             myFile1 << to_string(person->date) + "\n";
//             myFile1 << to_string(person->month) + "\n";
//             myFile1 << to_string(person->year) + "\n";
//         }
//         else
//         {
//             myFile1 << line + "\n";
//         }
//     }void updateFile(string name)
// {
//     node *person = search(name);
//     ofstream myFile1;
//     myFile1.open("temp.txt");
//     ifstream myFile2;
//     myFile2.open("Patient Record.txt");
//     while (myFile2.peek() != EOF)
//     {
//         string line, neglect;
//         getline(myFile2, line);
//         if (line == convertToUpperCase(name))
//         {
//             myFile1 << person->name + "\n";
//             myFile1 << to_string(person->age) + "\n";
//             myFile1 << person->socialSecurityNumber + "\n";
//             myFile1 << person->gender + "\n";
//             myFile1 << person->disease + "\n";
//             myFile1 << person->condition + "\n";
//             myFile1 << to_string(person->date) + "\n";
//             myFile1 << to_string(person->month) + "\n";
//             myFile1 << to_string(person->year) + "\n";
//         }
//         else
//         {
//             myFile1 << line + "\n";
//         }
//     }
//     myFile1.close();
//     myFile2.close();
//     remove("Patient Record.txt");
//     rename("temp.txt", "Patient Record.txt");
// }
//     remove("Patient Record.txt");
//     rename("temp.txt", "Patient Record.txt");
// }
void setPriority(node *patient)
{
    if (patient->disease == "COVID-19")
    {
        if (patient->age >= 60)
        {
            if (patient->condition == "SEVERE")
            {
                patient->priority = 1;
            }
            else
            {
                patient->priority = 2;
            }
        }
        else if (patient->age >= 30)
        {
            if (patient->condition == "SEVERE")
            {
                patient->priority = 2;
            }
            else
            {
                patient->priority = 3;
            }
        }
        else
        {
            patient->priority = 3;
        }
    }
    else if (patient->disease == "PNEUMONIA")
    {
        if (patient->age >= 50)
        {
            patient->priority = 3;
        }
        else
        {
            patient->priority = 4;
        }
    }
    else
    {
        patient->priority = 5;
    }
}
void addPatient(node *patient)
{
    setPriority(patient);
    if (head == nullptr && tail == nullptr)
    {
        head = tail = patient;
    }
    else
    {
        int priority = patient->priority;

        node *p = head;
        node *q;
        while (p != nullptr && p->priority <= priority)
        {
            q = p;
            p = p->next;
        }
        if (p == head)
        {
            head->prev = patient;
            patient->next = head;
            head = patient;
        }
        else if (p == nullptr)
        {
            tail->next = patient;
            patient->prev = tail;
            tail = patient;
        }
        else
        {
            q->next = patient;
            p->prev = patient;
            patient->next = p;
            patient->prev = q;
        }
    }
}

void display(node *starting)
{
    int count = 1;
    cout << "\nPatient Record: ";
    while (starting != nullptr)
    {
        cout << "\nPatient " << count << ": ";
        cout << "Name: " << starting->name << "  ";
        cout << "Age: " << starting->age << "  ";
        cout << "SSN: " << starting->socialSecurityNumber << endl;
        cout << "Gender: " << starting->gender << "  ";
        cout << "Disease: " << starting->disease << "  ";
        cout << "Condition: " << starting->condition << "  ";
        cout << "Admit Date: " << starting->date << ", " << starting->month << ", " << starting->year;
        starting = starting->next;
        cout << "\n";
        count++;
    }
    cout << endl;
}

// void dequeue()
// {
//     if (head == nullptr)
//     {
//         cout << "Nothing in queue" << endl;
//     }
//     else if (head == tail)
//     {
//         cout << head->name + " discharged!"
//              << endl;
//         head->condition = "NORMAL";
//         head->disease = "NIL";
//         delete head;
//         head = nullptr;
//         tail = nullptr;
//     }
//     else if (head->next == tail)
//     {
//         cout << head->name + " discharged!"
//              << endl;
//         head->condition = "NORMAL";
//         head->disease = "NIL";
//         node *p = head;
//         head = tail;
//         delete p;
//     }
//     else
//     {
//         cout << head->name + " discharged!"
//              << endl;
//         head->condition = "NORMAL";
//         head->disease = "NIL";
//         node *del = head;
//         head = head->next;
//         head->next->prev = head;
//         delete del;
//     }
// }

node *search(string name)
{
    node *p = head;
    while (p != nullptr)
    {
        if (p->name == convertToUpperCase(name))
        {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}
void removePatient(string name)
{
    node *p = head;
    while (p != nullptr)
    {
        if (p->name == convertToUpperCase(name))
        {
            break;
        }
        p = p->next;
    }
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else if (p == head)
    {
        node *del = head;
        head->next->prev = head->prev;
        head = head->next;
        delete del;
    }
    else if (p == tail)
    {
        node *del = tail;
        tail->prev->next = tail->next;
        tail = tail->prev;
        delete del;
    }
    else
    {
        node *del = p;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete del;
    }
}

void update(string name, string condition)
{
    node *p = head;
    while (p != nullptr)
    {
        if (p->name == convertToUpperCase(name))
        {
            break;
        }
        p = p->next;
    }

    if (p != nullptr)
    {
        condition = convertToUpperCase(condition);
        if (condition == "SEVERE" || condition == "MODERATE" || condition == "MILD" || condition == "NORMAL")
        {
            p->condition = condition;
            if (condition == "NORMAL")
            {
                removePatient(name);
                removeFromFile(name);
            }
            else
            {
                node *q = p;
                removePatient(name);
                addPatient(p);
            }
            cout << "Condition Updated" << endl;
        }
        else
        {
            cout << "Enter Valid Condition (Severe/Moderate/Mild/Normal)" << endl;
        }
    }

    else
    {
        cout << "Patient Not Found" << endl;
    }
}

int main()
{
    //Main Menu
    readFromFile();
    bool infinite_loop = true;
    while (infinite_loop)
    {
        cout << "\nWelcome to Hospital Management System\n"
             << "1. Add Patient\n"
             << "2. View Patients\n"
             << "3. Update Patient Condition\n"
             << "4. Search Patient\n"
             //  << "5. Discharged Patient\n"
             << "5. Ambulance Service\n"
             << "0. EXIT\n"
             << "Choice >> ";
        int choice;
        string choiceTemp;
        cin >> choiceTemp;
        if (checkNumber(choiceTemp))
        {
            choice = stoi(choiceTemp);
        }
        else
        {
            cout << "Please enter digits only" << endl;
        }
        string patient_name;
        int patient_age;
        string p_socialSecurityNumber;
        string p_gender;
        string p_disease;
        string p_condition;
        int p_date, p_month, p_year;
        string ageTemp, dateTemp, monthTemp, yearTemp;
        node *patient;

        int p_x, p_y;
        switch (choice)
        {
        case 1:
            cout << "Enter Patient Name:";
            cin.ignore();
            getline(cin, patient_name);
            if (!checkStringWithSpaces(patient_name) && !patient_name.empty())
            {
                cout << "Invalid Name. Must be String only.";
                break;
            }
            cout << "Enter Patient Age:";
            cin >> ageTemp;
            if (checkNumber(ageTemp))
            {
                patient_age = stoi(ageTemp);
            }
            else
            {
                cout << "Please enter digits only" << endl;
                break;
            }
            cout << "Enter Patient SSN: ";
            cin >> p_socialSecurityNumber;
            if (!(checkNumber(p_socialSecurityNumber))) // TODO: 1. Must add length check
            {
                cout << "Invalid SSN. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Gender (Male/Female): ";
            cin >> p_gender;
            if (!(convertToUpperCase(p_gender) == "MALE" || convertToUpperCase(p_gender) == "FEMALE"))
            {
                cout << "Invalid Gender. Must be Letters only.";
                break;
            }
            cout << "Enter Patient Disease (Covid-19/Pneumonia/Flu): ";
            cin >> p_disease;
            if (!(convertToUpperCase(p_disease) == "COVID-19" || convertToUpperCase(p_disease) == "PNEUMONIA" || convertToUpperCase(p_disease) == "FLU"))
            {
                cout << "The disease is not cured here. We cure COVID-19/PNEUMONIA/FLU only.";
                break;
            }
            cout << "Enter Patient Condition (Severe/Moderate/Mild): ";
            cin >> p_condition;
            if (!(convertToUpperCase(p_condition) == "SEVERE" || convertToUpperCase(p_condition) == "MODERATE" || convertToUpperCase(p_condition) == "MILD"))
            {
                cout << "Invalid Condition. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Admit Date: ";
            cin >> p_date;
            // if (checkNumber(dateTemp))
            // {
            //     p_date = stoi(dateTemp);
            // }
            // else
            // {
            //     cout << "Please enter digits only" << endl;
            //     break;
            // }
            if (!(p_date <= 31 && p_date >= 1))
            {
                cout << "Invalid Date. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Admit Month: ";
            cin >> p_month;
            // if (checkNumber(monthTemp))
            // {
            //     p_month = stoi(monthTemp);
            // }
            // else
            // {
            //     cout << "Please enter digits only" << endl;
            //     break;
            // }
            if (!(p_month >= 1 && p_month <= 12))
            {
                cout << "Invalid Month. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Admit Year: ";
            cin >> p_year;
            // if (checkNumber(yearTemp))
            // {
            //     p_year = stoi(yearTemp);
            // }
            // else
            // {
            //     cout << "Please enter digits only" << endl;
            //     break;
            // }
            if (!(p_year >= 2019 && p_year <= 2020))
            {
                cout << "Invalid Year. Must be Digits only.";
                break;
            }
            patient = new node(convertToUpperCase(patient_name), patient_age, convertToUpperCase(p_socialSecurityNumber), convertToUpperCase(p_gender), convertToUpperCase(p_disease), convertToUpperCase(p_condition), p_date, p_month, p_year);
            addPatient(patient);
            addToFile(patient);
            break;
        case 2:
            display(head);
            break;
        case 3:
            cout << "Enter Patient Name: ";
            cin >> patient_name;
            cout << "Enter Patient Condition: ";
            cin >> p_condition;
            update(patient_name, p_condition);
            break;
        case 4:
            cout << "Enter Patient Name: ";
            cin >> patient_name;
            search(patient_name);
            break;
            // case 5:
            //     cout << "Highest Priority Patient Dequeued: ";
            //     dequeue();
            //     break;
            // case 0:
            infinite_loop = false;
            break;
            // case 5:
            //     cout << "Welcome to Ambulance Service" << endl;
            //     cout << "Enter X Co-ordinate (1-100): ";
            //     cin >> p_x;
            //     cout << "Enter Y Co-ordinate (1-100): ";
            //     cin >> p_y;

        default:
            cout << "Invalid Command Entered!";
            break;
        }
    }
}
