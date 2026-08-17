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

void resetScreen()
{
    system("cls");
    system("color 0F");
}

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    int AccountBalance;
};

stClient ReadNewClient()
{
    stClient Client;

    cout<< "\nEnter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    cout<< "Enter PinCode? ";
    getline(cin, Client.PinCode);

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
    MyFile.open(ClientFileName, ios::in);
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

void PrintClientRecord(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintAllClientsRecord(vector<stClient> vClient)
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

void AddNewClient()
{
    stClient Client = ReadNewClient();
    AddDataLineToFile(Client, ClientFileName);
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {
        AddNewClient();
        cout<< "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin>> AddMore;
    } while (toupper(AddMore) == 'Y');
    
}

enum enSection { Main = 0, ShowList = 1, AddNew = 2, Delete = 3, UpdateInfo = 4, Find = 5, Exit = 6 };

enSection NumberToEnSection(int num)
{
    switch (num)
    {
    case 1:
        return enSection::ShowList;
    
    case 2:
        return enSection::AddNew;
    
    case 3:
        return enSection::Delete;
    
    case 4:
        return enSection::UpdateInfo;
    
    case 5:
        return enSection::Find;
    
    case 6:
        return enSection::Exit;
    
    default:
        return enSection::Main;
    }
}

void PrintTitle(int num = 0)
{
    enSection section = NumberToEnSection(num);

    switch (section)
    {
    case 0:
        cout<< "================================================" <<endl;
        cout << "\t\tMain Menu Screen" <<endl;
        cout<< "================================================" <<endl;
        break;

    case 1:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tShow Client List Screen" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;   
       
    case 2:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tAdd New Screen" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;

    case 3:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tDelete Client Screen" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;  
        
    case 4:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tUpdate Client Info Screen" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;

    case 5:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tFind Client Screen" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;   
       
    case 6:
        cout<< "------------------------------------------------" <<endl;
        cout << "\t\tProgram Ends :-)" <<endl;
        cout<< "------------------------------------------------" <<endl;
        break;

    default:
        cout<< "================================================" <<endl;
        cout << "\t\tMain Menu Screen" <<endl;
        cout<< "================================================" <<endl;
        break;
    }
}

void PrintSections()
{
    cout<< "\t[1] Show Client List." <<endl;
    cout<< "\t[2] Add New Client." <<endl;
    cout<< "\t[3] Delete Client." <<endl;
    cout<< "\t[4] Update Client Info." <<endl;
    cout<< "\t[5] Find Client." <<endl;
    cout<< "\t[6] Exit." <<endl;
    cout<< "================================================" <<endl;
}

void ChooseSection();

void MainSection()
{
    PrintTitle();
    PrintSections();
    ChooseSection();
}

void ShowListSection()
{
    char key = '`';
    if (key == '`')
    {
        vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
        PrintAllClientsRecord(vClient);
        cout<< "Press any key to go back to Main Menu...";
        cin>> key;
    }
    MainSection();
}

void AddNewSection()
{
    AddClients();
}

void DeleteSection()
{}

void UpdateInfoSection()
{}

void FindSection()
{}

void ExitSection(int num)
{
    PrintTitle(num);
}

void ChooseSection()
{
    int num = ReadNumber("Choose what do you want to do? [1 to 6]? ");
    
    switch (num)
    {
    case 1:
        resetScreen();
        ShowListSection();
        break;
    
    case 2:
        resetScreen();
        PrintTitle(num);
        AddNewSection();
        break;
    
    case 3:
        resetScreen();
        PrintTitle(num);
        break;
    
    case 4:
        resetScreen();
        PrintTitle(num);
        break;
    
    case 5:
        resetScreen();
        PrintTitle(num);
        break;
    
    case 6:
        resetScreen();
        PrintTitle(num);
        break;
    
    default:
        resetScreen();
        MainSection();
        break;
    }
}


int main()
{
    MainSection();
    return 0;
}