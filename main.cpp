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
void dischargeNormal(string name)
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
        cout << "Patient " << convertToUpperCase(name) << " is Discharged!" << endl;
    }
    else if (p == head)
    {
        node *del = head;
        head->next->prev = head->prev;
        head = head->next;
        delete del;
        cout << "Patient " << convertToUpperCase(name) << " is Discharged!" << endl;
    }
    else if (p == tail)
    {
        node *del = tail;
        tail->prev->next = tail->next;
        tail = tail->prev;
        delete del;
        cout << "Patient " << convertToUpperCase(name) << " is Discharged!" << endl;
    }
    else
    {
        node *del = p;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete del;
        cout << "Patient " << convertToUpperCase(name) << " is Discharged!" << endl;
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
                dischargeNormal(name);
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
    addPatient("Bukhari", 60, "1234567890123", "Male", "Covid-19", "SEVERE", 3, 7, 2020);
    addPatient("Umair", 18, "1234567890123", "Male", "Covid-19", "MODERATE", 3, 7, 2020);
    addPatient("Rana", 18, "1234567890123", "Male", "FLU", "SEVERE", 3, 7, 2020);
    addPatient("Hashaam", 60, "1234567890123", "Male", "Covid-19", "MODERATE", 3, 7, 2020);
    addPatient("Saad", 18, "1234567890123", "Male", "Covid-19", "MODERATE", 3, 7, 2020);
    addPatient("Channar", 30, "1234567890123", "Male", "Covid-19", "SEVERE", 3, 7, 2020);

    display(head);

    node *searched = search("Abdullah");
    if (searched != nullptr)
        cout << searched->name << endl;
    else
        cout << "Patient Not found" << endl;

    update("Rana", "NORMAL");
    display(head);
    //update("Bukhari", "noraml");
    //display(head);
}
