#include <iostream>
#include <string.h>
// define maximum number of patients in a Queue
#define MAXPATIENTS 100
using namespace std;
// define structure for patient data
struct patient
{
    char FirstName[50];
    char LastName[50];
    char ID[20];
};
// define class for Queue
class Queue
{
public:
    Queue(void);
    int AddPatientAtEnd(patient p);
    int AddPatientAtBeginning(patient p);
    patient GetNextPatient(void);
    int RemoveDeadPatient(patient *p);
    void OutputList(void);
    char DepartmentName[50];

private:
    int NumberOfPatients;
    patient List[MAXPATIENTS];
};
// declare member functions for Queue
Queue::Queue()
{
    // constructor
    NumberOfPatients = 0;
}
int Queue::AddPatientAtEnd(patient p)
{
    // adds a normal patient to the end of the Queue.
    // returns 1 if successful, 0 if Queue is full.
    if (NumberOfPatients >= MAXPATIENTS)
    {
        // Queue is full
        return 0;
    }
    // put in new patient
    else
        List[NumberOfPatients] = p;
    NumberOfPatients++;
    return 1;
}
int Queue::AddPatientAtBeginning(patient p)
{
    // adds a critically ill patient to the beginning of the Queue. // returns 1 if successful, 0 if Queue is full.
    int i;
    if (NumberOfPatients >= MAXPATIENTS)
    {
        // Queue is full
        return 0;
    }
    // move all patients one position back in Queue
    for (i = NumberOfPatients - 1; i >= 0; i--)
    {

        List[i + 1] = List[i];
    }
    // put in new patient
    List[0] = p;
    NumberOfPatients++;
    return 1;
}
patient Queue::GetNextPatient(void)
{
    // gets the patient that is first in the Queue.
    // returns patient with no ID if Queue is empty
    int i;
    patient p;
    if (NumberOfPatients == 0)
    {
        // Queue is empty
        strcpy(p.ID, "");
        return p;
    }
    // get first patient
    p = List[0];
    // move all remaining patients one position forward in Queue
    NumberOfPatients--;
    for (i = 0; i < NumberOfPatients; i++)
    {
        List[i] = List[i + 1];
    }
    // return patient
    return p;
}
int Queue::RemoveDeadPatient(patient *p)
{
    // removes a patient from Queue.
    // returns 1 if successful, 0 if patient not found
    int i, j, found = 0;
    // search for patient

    for (i = 0; i < NumberOfPatients; i++)
    {
        if (strcmp(List[i].ID, p->ID) == 0)
        {
            // patient found in Queue
            *p = List[i];
            found = 1;
            // move all following patients one position forward in Queue
            NumberOfPatients--;
            for (j = i; j < NumberOfPatients; j++)
            {
                List[j] = List[j + 1];
            }
        }
    }
    return found;
}
void Queue::OutputList(void)
{
    // lists entire Queue on screen
    int i;
    if (NumberOfPatients == 0)
    {
        cout << "QUEUE is EMPTY !!";
    }
    else
    {
        for (i = 0; i < NumberOfPatients; i++)
        {
            cout << List[i].FirstName << endl;
            cout << List[i].LastName << endl;
            cout << List[i].ID << endl;
            cout << endl;
        }
    }
}
// declare functions used by main:
patient InputPatient(void)
{
    // this function asks user for patient data.
    patient p;
    cout << "\nPlease Enter Data for New Patient\n\nFirst name: ";
    cin.getline(p.FirstName, sizeof(p.FirstName));
    cout << "Last name : ";
    cin.getline(p.LastName, sizeof(p.LastName));
    cout << "Patient ID : ";
    cin.getline(p.ID, sizeof(p.ID));
    // check if data valid
    if (p.FirstName[0] == 0 || p.LastName[0] == 0 || p.ID[0] == 0)
    {
        // rejected
        strcpy(p.ID, "");
        cout << "Error : Data not valid.Operation cancelled.";
    }
    return p;
}

void OutputPatient(patient *p)
{
    // this function outputs patient data to the screen
    if (p == NULL || p->ID[0] == 0)
    {
        cout << " No Patient";
        return;
    }
    else
    {
        cout << "\n\nPatient Data :";
        cout << "\nFirst Name : " << p->FirstName;
        cout << "\nLast Name : " << p->LastName;
        cout << "\nSocial Security Number : " << p->ID << endl;
    }
}
int ReadNumber()
{
    // this function reads an integer number from the keyboard. // it is used because input with cin >> doesn’t work properly!
    char buffer[20];
    cin.getline(buffer, sizeof(buffer));
    return atoi(buffer);
}
void DepartmentMenu(Queue *q)
{

    // this function defines the user interface with menu for one department
    int choice = 0, success;
    patient p;
    while (choice != 6)
    {
        // clear screen
        // print menu
        cout << "\nWelcome to " << q->DepartmentName << " Department";
        cout << "\n\n";

        cout << "Please enter your choice: ";
        cout << "\n\n";

        cout << " 1: Add normal patient";
        cout << "\n";

        cout << " 2: Add critically ill patient";
        cout << "\n";

        cout << " 3: Take out patient for operation";
        cout << "\n";

        cout << " 4: Remove dead patient  from Queue";
        cout << "\n";

        cout << " 5: List Queue";
        cout << "\n";

        cout << " 6: Change department or exit";
        cout << "\n\n";

        // get user choice
        choice = ReadNumber();
        // do indicated action
        switch (choice)
        {
        case 1: // Add normal patient
            p = InputPatient();

            if (p.ID[0])
            {
                success = q->AddPatientAtEnd(p);

                if (success)
                {
                    cout << "Patient Added :";
                }
                else
                {
                    // error
                    cout << "Error: The Queue is full. Cannot Add Patient : ";
                }
                OutputPatient(&p);
            }
            break;
        case 2: // Add critically ill patient
            p = InputPatient();
            if (p.ID[0])
            {
                success = q->AddPatientAtBeginning(p);

                if (success)
                {

                    cout << "Patient added :";
                }
                else
                {
                    // error
                    cout << "Error : The Queue is full.Cannot add patient : ";
                }
                OutputPatient(&p);
            }
            break;
        case 3: // Take out patient for operation
            p = q->GetNextPatient();

            if (p.ID[0])
            {
                cout << "Patient to operate :";
                OutputPatient(&p);
            }
            else
            {
                cout << "There is no patient to operate.";
            }

            break;
        case 4: // Remove dead patient from Queue
            p = InputPatient();
            if (p.ID[0])
            {
                success = q->RemoveDeadPatient(&p);

                if (success)
                {
                    cout << "Patient removed :";
                }
                else
                {
                    // error
                    cout << "Error : Cannot find patient : ";
                }
                OutputPatient(&p);
            }
            break;
        case 5: // List Queue

            q->OutputList();

            break;
        }
    }
}
// main function defining Queues and main menu
int main()
{
    // cout << " 👼 \n\n";

    int i, MenuChoice = 0;
    // define three Queues
    Queue departments[3];
    // set department names
    strcpy(departments[0].DepartmentName, "Heart clinic  ");
    strcpy(departments[1].DepartmentName, "Lung clinic  ");
    strcpy(departments[2].DepartmentName, "Plastic surgery  ");
    while (MenuChoice != 4)
    {
        // clear screen
 
        // print menu
        cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t\t@@                                                                                         @@\n";
        cout << "\t\t@@                                            		                                   @@\n";
        cout << "\t\t@@                                                                     		           @@\n";
        cout << "\t\t@@                                   NAMASTE                                               @@\n";
        cout << "\t\t@@                                                                                         @@\n";
        cout << "\t\t@@                            Welcome to Our Hospital                                      @@\n";
        cout << "\t\t@@                                                                                         @@\n";
        cout << "\t\t@@                                                                                         @@\n";
        cout << "\t\t@@                                                                                         @@\n";
        cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n\n";
        // cout << "\t\t\t  \t\t\t";
        cout << "\n\n";

        for (i = 0; i < 3; i++)
        {
            // write menu item for department i
            cout << "\t\t\t\t\t\t" << (i + 1) << ": " << departments[i].DepartmentName;
            cout << "\n";
        }
        cout << "\t\t\t\t\t\t4: Exit  ";
        cout << "\n\n";
        cout << "\t\t\t\t\t\tPlease enter your choice : ";

        // get user choice
        MenuChoice = ReadNumber();
        // is it a department name?
        if (MenuChoice >= 1 && MenuChoice <= 3)
        {
            // call submenu for department
            // (using pointer arithmetics here:)

            DepartmentMenu(departments + (MenuChoice - 1));
        }
    }
    return 0;
}