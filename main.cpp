#include <iostream>
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
    else if (patient->disease == "CANCER")
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

void dequeue()
{
    if (head == nullptr)
    {
        cout << "Nothing in queue" << endl;
    }
    else if (head == tail)
    {
        cout << head->name + " discharged!"
             << endl;
        head->condition = "NORMAL";
        head->disease = "NIL";
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else if (head->next == tail)
    {
        cout << head->name + " discharged!"
             << endl;
        head->condition = "NORMAL";
        head->disease = "NIL";
        node *p = head;
        head = tail;
        delete p;
    }
    else
    {
        cout << head->name + " discharged!"
             << endl;
        head->condition = "NORMAL";
        head->disease = "NIL";
        node *del = head;
        head = head->next;
        head->next->prev = head;
        delete del;
    }
}

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
                removePatient(p->name);
            }
            else
            {
                node *q = p;
                setPriority(p);
                addPatient(p);
                removePatient(q->name);
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
    bool infinite_loop = true;
    while (infinite_loop)
    {
        cout << "\nWelcome to Hospital Management System\n"
             << "1. Add Patient\n"
             << "2. View Patients\n"
             << "3. Update Patient\n"
             << "4. Search Patient\n"
             << "5. Discharged Patient\n"
             << "0. EXIT\n"
             << "Choice >> ";
        int choice;
        cin >> choice;
        string patient_name;
        int patient_age;
        string p_socialSecurityNumber;
        string p_gender;
        string p_disease;
        string p_condition;
        int p_date, p_month, p_year;
        node *patient;
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
            cin >> patient_age;
            if (!checkNumber(to_string(patient_age)))
            {
                cout << "Invalid Age. Must be Digits only.";
                break;
            }
            cout << "Enter Patient SSN: ";
            cin >> p_socialSecurityNumber;
            if (!checkNumber(p_socialSecurityNumber))
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
            cout << "Enter Patient Disease (Covid-19/Cancer/Flu): ";
            cin >> p_disease;
            if (!(convertToUpperCase(p_disease) == "COVID-19" || convertToUpperCase(p_disease) == "CANCER" || convertToUpperCase(p_disease) == "FLU"))
            {
                cout << "The disease is not cured here. We cure COVID-19/CANCER/FLU only.";
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
            if (!(checkNumber(to_string(p_date)) && p_date <= 31 && p_date >= 1))
            {
                cout << "Invalid Date. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Admit Month: ";
            cin >> p_month;
            if (!(checkNumber(to_string(p_month)) && p_month >= 1 && p_month <= 12))
            {
                cout << "Invalid Month. Must be Digits only.";
                break;
            }
            cout << "Enter Patient Admit Year: ";
            cin >> p_year;
            if (!(checkNumber(to_string(p_year)) && p_year >= 2019 && p_year <= 2020))
            {
                cout << "Invalid Year. Must be Digits only.";
                break;
            }
            patient = new node(patient_name, patient_age, p_socialSecurityNumber, p_gender, p_disease, p_condition, p_date, p_month, p_year);
            addPatient(patient);
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
        case 5:
            cout << "Highest Priority Patient Dequeued: ";
            dequeue();
            break;
        case 0:
            infinite_loop = false;
            break;
        default:
            cout << "Invalid Command Entered!";
            break;
        }
    }
}
