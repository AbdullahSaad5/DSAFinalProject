#include <iostream>
#include <string>
using namespace std;
struct node
{
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
void addPatient(string name, int age, string socialSecurityNumber, string gender, string disease, string condition, int day,
                int month, int year)
{
    if (!name.empty() && (age > 0 && age < 100) &&
        (!socialSecurityNumber.empty() && socialSecurityNumber.length() == 13) &&
        (convertToUpperCase(gender) == "MALE" || convertToUpperCase(gender) == "FEMALE") && (convertToUpperCase(disease) == "COVID-19" || convertToUpperCase(disease) == "CANCER" || convertToUpperCase(disease) == "FLU") &&
        (convertToUpperCase(condition) == "SEVERE" || convertToUpperCase(condition) == "MILD" ||
         convertToUpperCase(condition) == "MODERATE") &&
        (day > 0 && day <= 30) && (month > 0 && month <= 12) && year == 2020)
    {
        node *patient = new node;
        patient->name = convertToUpperCase(name);
        patient->age = age;
        patient->socialSecurityNumber = socialSecurityNumber;
        patient->gender = convertToUpperCase(gender);
        patient->disease = convertToUpperCase(disease);
        patient->condition = convertToUpperCase(condition);
        patient->date = day;
        patient->month = month;
        patient->year = year;
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
    else
    {
        cout << "Invalid Info found in the patient's (" + name + ") Description. Please Enter Again!";
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
                addPatient(p->name, p->age, p->socialSecurityNumber, p->gender, p->disease, p->condition, p->date, p->month, p->year);
                removePatient(q->name);
            }
            cout << "Condition Updated" << endl;
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

        switch (choice)
        {
        case 1:

            cout << "Enter Patient Name:";
            cin >> patient_name;
            cout << "Enter Patient Age:";
            cin >> patient_age;
            cout << "Enter Patient SSN: ";
            cin >> p_socialSecurityNumber;
            cout << "Enter Patient Gender: ";
            cin >> p_gender;
            cout << "Enter Patient Disease: ";
            cin >> p_disease;
            cout << "Enter Patient Condition: ";
            cin >> p_condition;
            cout << "Enter Patient Admit Date: ";
            cin >> p_date;
            cout << "Enter Patient Admit Month: ";
            cin >> p_month;
            cout << "Enter Patient Admit Year: ";
            cin >> p_year;
            addPatient(patient_name, patient_age, p_socialSecurityNumber, p_gender, p_disease, p_condition, p_date, p_month, p_year);
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
