#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

string ReadString(string message)
{
    string word;
    cout<< message;
    cin>> word;

    return word;
}

int ReadNumber(string message)
{
    int num;
    cout<< message;
    cin>> num;

    return num;
}

int ReadNumber(string message, int From, int To)
{
    int num;
    do
    {
        cout<< message;
        cin>> num;
    
    } while (num < From || num > To);

    return num;
}

void resetScreen()
{
    system("cls");
    system("color 0F");
}

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

stClient ReadNewClient(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout<< "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout<< "Enter Name? ";
    getline(cin, Client.Name);

    cout<< "Enter Phone Number? ";
    getline(cin, Client.Phone);

    cout<< "Enter Account Balance? ";
    cin>> Client.AccountBalance;

    return Client;
}

vector<string> SplitString(string DataLine, string Delimiter)
{
    vector<string> vString;
    string word = "";
    short position = 0;

    while ((position = DataLine.find(Delimiter)) != string::npos)
    {
        word = DataLine.substr(0, position);
        if (word != "")
        {
            vString.push_back(word);
            //DataLine.erase(0, position + Delimiter.length());
        }

        DataLine.erase(0, position + Delimiter.length());
    }

    if (DataLine != "")
    {
        vString.push_back(DataLine);
    }
    
    return vString;
}

stClient ConvertLineToRecord(string DataLine, string Delimiter = "#//#")
{
    stClient Client;
    vector<string> vString = SplitString(DataLine, Delimiter);

    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stod(vString[4]);
    
    return Client;
}

string ConvertRecordToLine(stClient Client, string Separator = "#//#")
{
    string Line = "";

    Line += Client.AccountNumber + Separator;
    Line += Client.PinCode + Separator;
    Line += Client.Name + Separator;
    Line += Client.Phone + Separator;
    Line += to_string(Client.AccountBalance);

    return Line;
}

const string ClientFileName = "Client.txt";
void AddDataLineToFile(stClient Client, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile<< ConvertRecordToLine(Client) <<endl;
        MyFile.close();
    }    
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient> vClient;
    
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }
        MyFile.close();
    }

    return vClient;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details : \n";
    cout<< "------------------------------------------------" <<endl;
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "PinCode : " << Client.PinCode << endl;
    cout << "Name : " << Client.Name << endl;
    cout << "Phone : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout<< "------------------------------------------------\n" <<endl;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintAllClientsRecord(vector<stClient>& vClient)
{
    cout << "\n\t\t\t\t Client List (" << vClient.size() << ") Client(s).";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code ";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    for(stClient C : vClient)
    {
        PrintClientRecord(C);
        cout << endl;
    }

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

}

bool IsClientExists(string AccountNumber, vector<stClient>& vClient)
{
    for (stClient& c : vClient)
    {
        if (c.AccountNumber == AccountNumber)
        return true;
    }
    
    return false;
}

void AddNewClient(vector<stClient>& vClient)
{    
    stClient NewClient;
    string AccountNumber;

    cout<< "\nEnter Account Number? ";
    getline(cin >> ws, AccountNumber);

    while (IsClientExists(AccountNumber, vClient))
    {
        cout << "Client with [" << AccountNumber << "] already exists, ";
        AccountNumber = ReadString("Enter another Account Number? ");
    }

    NewClient = ReadNewClient(AccountNumber);
    AddDataLineToFile(NewClient, ClientFileName);
    
}

void AddClients(vector<stClient>& vClient)
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding new Client:\n\n";
        AddNewClient(vClient);

        cout<< "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin>> AddMore;
    } while (toupper(AddMore) == 'Y');
    
}

bool FindClientByAccountNumber(string AccountNumber, stClient& Client, vector<stClient>& vClient)
{
    for (stClient& c : vClient)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClient C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }

    return vClient;
}

bool DeleteClientByAccountNumber(vector<stClient>& vClient)
{
    stClient Client;
    string AccountNumber = ReadString("\nPlease Enter Account Number? ");
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);
        cout << "\nAre you sure you want delete client? n/y? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveClientsDataToFile(ClientFileName, vClient);

            vClient = LoadClientsDataFromFile(ClientFileName);

            cout << "\n\n Client Deleted Successfully. \n";
            return true;
        }
    }
    else
        cout<< "\nClient with Account Number [" << AccountNumber << "] is not found!" <<endl;

    return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;
    
    cout<< "\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout<< "Enter Name? ";
    getline(cin, Client.Name);

    cout<< "Enter Phone Number? ";
    getline(cin, Client.Phone);

    cout<< "Enter Account Balance? ";
    cin>> Client.AccountBalance;
    
    return Client;
}

bool UpdateClientByAccountNumber(vector<stClient>& vClient)
{
    stClient Client;
    char Answer = 'n';
    string AccountNumber;

    cout<< "\nEnter Account Number? ";
    getline(cin >> ws, AccountNumber);

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);
        cout << "\nAre you sure you want update this client info? n/y? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (stClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientFileName, vClient);

            vClient = LoadClientsDataFromFile(ClientFileName);

            cout << "\n\n Client Info Updated Successfully. \n";
            return true;
        }
    }
    else
        cout<< "\nClient with Account Number [" << AccountNumber << "] is not found!" <<endl;

    return false;
}

void FindClient(vector<stClient>& vClient)
{
    stClient Client;
    string AccountNumber;
    
    cout<< "\nEnter Account Number? ";
    getline(cin >> ws, AccountNumber);

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);
    }
    else
        cout<< "\nClient with Account Number [" << AccountNumber << "] is not found!" <<endl;
}

enum enSection { Main = 0, ShowList = 1, AddNew = 2, Delete = 3, UpdateInfo = 4, Find = 5, Exit = 6 };



void PrintScreenTitle(string Title)
{
    cout << "================================================\n";
    cout << "\t\t" << Title << '\n';
    cout << "================================================\n";
}

void ShowMainMenu()
{
    PrintScreenTitle("Main Menu Screen");

    cout<< "\t[1] Show Client List." <<endl;
    cout<< "\t[2] Add New Client." <<endl;
    cout<< "\t[3] Delete Client." <<endl;
    cout<< "\t[4] Update Client Info." <<endl;
    cout<< "\t[5] Find Client." <<endl;
    cout<< "\t[6] Exit." <<endl;
    cout<< "================================================" <<endl;
}

void ShowListSection()
{
    PrintScreenTitle("Show Client List Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    PrintAllClientsRecord(vClient);
}

void AddNewSection()
{
    PrintScreenTitle("Add New Client Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    AddClients(vClient);
}

void DeleteSection()
{
    PrintScreenTitle("Delete Client Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    DeleteClientByAccountNumber(vClient);
}

void UpdateInfoSection()
{
    PrintScreenTitle("Update Client Info Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    UpdateClientByAccountNumber(vClient);
}

void FindSection()
{
    PrintScreenTitle("Find Client Screen");

    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    FindClient(vClient);
}

void ExitSection()
{
    PrintScreenTitle("Program Ends :-)");
}

enSection ReadSectionChoice()
{
    short num = ReadNumber("Choose what do you want to do? [1 to 6]? ", 1, 6);
    return enSection (num);
}

void GetSection(enSection Section)
{
    switch (Section)
    {
        case enSection::ShowList:
            ShowListSection();
            break;
        
        case enSection::AddNew:
            AddNewSection();
            break;
        
        case enSection::Delete:
            DeleteSection();
            break;
        
        case enSection::UpdateInfo:
            UpdateInfoSection();
            break;
        
        case enSection::Find:
            FindSection();
            break;
        
        case enSection::Exit:
            ExitSection();
            break;
    }
}

void startTheBankProject()
{
    enSection Section;
    do
    {
        resetScreen();

        ShowMainMenu();
        Section = ReadSectionChoice();
        GetSection(Section);

        if(Section != enSection::Exit)
        {
            cout << "\n\nPress any Key to go back to main menu... ";
            cin.ignore();
            cin.get();
        }

    } while (Section != enSection::Exit);
    
}




int main()
{
    startTheBankProject();
    return 0;
}