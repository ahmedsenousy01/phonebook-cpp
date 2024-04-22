#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// global variables
string names[50], phoneNumbers[50];
int namesIndex = 0, phoneNumbersIndex = 0;

// validation

// name should be alphabetic chars only
bool validateName(string name)
{
    for (int i = 0; i < namesIndex; i++)
        if (name == names[i])
            return false;

    for (int i = 0; i < name.size(); i++)
        if (!isalpha(name[i]))
            return false;

    return true;
}

// phone number should be 11 numeric chars only
bool validatePhoneNumber(string phoneNumber)
{
    if (phoneNumber.size() != 11)
        return false;

    for (int i = 0; i < phoneNumbersIndex; i++)
        if (phoneNumber == phoneNumbers[i])
            return false;

    for (int i = 0; i < phoneNumber.size(); i++)
        if (!isdigit(phoneNumber[i]))
            return false;

    return true;
}

// core functions (features)
bool addNewContact(string name, string phoneNumber)
{
    if (!(namesIndex < 49 && validateName(name) && validatePhoneNumber(phoneNumber)))
        return false;

    names[namesIndex] = name;
    namesIndex++;

    phoneNumbers[phoneNumbersIndex] = phoneNumber;
    phoneNumbersIndex++;

    return true;
}

bool modifyContact(string name, string newPhoneNumber)
{
    if (!validatePhoneNumber(newPhoneNumber))
        return false;

    for (int i = 0; i < namesIndex; i++)
        if (names[i] == name)
        {
            phoneNumbers[i] = newPhoneNumber;
            return true;
        }

    return false;
}

bool deleteContact(string name)
{
    for (int i = 0; i < namesIndex; i++)
    {
        if (names[i] == name)
        {
            for (int j = i; j < namesIndex - 1; j++)
            {
                names[j] = names[j + 1];
                phoneNumbers[j] = phoneNumbers[j + 1];
            }
            namesIndex--;
            phoneNumbersIndex--;
            return true;
        }
    }

    return false;
}

string searchForContactByName(string name)
{
    for (int i = 0; i < namesIndex; i++)
    {
        if (names[i] == name)
        {
            return names[i] + " " + phoneNumbers[i];
        }
    }

    return "";
}
string searchForContactByPhoneNumber(string phoneNumber)
{
    for (int i = 0; i < phoneNumbersIndex; i++)
    {
        if (phoneNumbers[i] == phoneNumber)
        {
            return names[i] + " " + phoneNumbers[i];
        }
    }

    return "";
}

void displayPhoneBook()
{
    for (int i = 0; i < namesIndex; i++)
    {
        cout << names[i] << " " << phoneNumbers[i] << endl;
    }
}

void getDataFromTextFiles()
{
    fstream file("data.txt", ios::in);

    string line;
    while (getline(file, line))
    {
        if (line == " & ")
            continue;

        stringstream ss(line);
        string s;
        while (getline(ss, s, '&'))
        {
            names[namesIndex++] = s;
            getline(ss, s, '&');
            phoneNumbers[phoneNumbersIndex++] = s;
        }
    }

    file.close();
}

void saveDataToTextFiles()
{
    fstream file("data.txt", ios::out);

    for (int i = 0; i < namesIndex; i++)
    {
        file << names[i] << "&" << phoneNumbers[i] << '\n';
    }

    file.close();
}

void pauseScreen(string message = "")
{
    cout << endl
         << endl
         << message << endl;
    string s;
    cout << "Press any key then enter to continue...\n";
    cin >> s;
    system("clear");
}

int main()
{
    getDataFromTextFiles();

    string name, phoneNumber;
    int choice;

    while (true)
    {
        cout << "1. Add new contact" << endl;
        cout << "2. Modify contact" << endl;
        cout << "3. Delete contact" << endl;
        cout << "4. Search for contact by name" << endl;
        cout << "5. Search for contact by phone number" << endl;
        cout << "6. Display phone book" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phoneNumber;
            if (addNewContact(name, phoneNumber))
                pauseScreen("Contact added successfully");
            else
                pauseScreen("unknown error, please try again");
            continue;
        }
        case 2:
        {
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter new phone number: ";
            cin >> phoneNumber;
            if (modifyContact(name, phoneNumber))
                pauseScreen("Contact modified successfully");
            else
                pauseScreen("unknown error, please try again");
            continue;
        }
        case 3:
        {
            cout << "Enter name: ";
            cin >> name;
            if (deleteContact(name))
                pauseScreen("Contact deleted successfully");
            else
                pauseScreen("unknown error, please try again");
            continue;
        }
        case 4:
        {
            cout << "Enter name: ";
            cin >> name;
            string contactByName = searchForContactByName(name);
            if (!contactByName.empty())
            {
                cout << contactByName << endl;
                pauseScreen();
            }
            else
                pauseScreen("unknown error, please try again");
            continue;
        }
        case 5:
        {

            cout << "Enter phone number: ";
            cin >> phoneNumber;
            string contactByPhoneNumber = searchForContactByPhoneNumber(phoneNumber);
            if (!contactByPhoneNumber.empty())
            {
                cout << contactByPhoneNumber << endl;
                pauseScreen();
            }
            else
                pauseScreen("unknown error, please try again");
            continue;
        }
        case 6:
        {
            cout << endl
                 << endl
                 << "Phone book : \n\n";
            displayPhoneBook();
            pauseScreen();
            continue;
        }
        case 7:
        {
            saveDataToTextFiles();
            return 0;
            continue;
        }
        default:
        {
            cout << "Invalid choice" << endl;
            pauseScreen();
            continue;
        }
        }
    }
}