#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientFileName = "Client.txt";

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

void PrintScreenTitle(string Title)
{
    cout << "\n================================================\n";
    cout << "\t\t" << Title << '\n';
    cout << "================================================\n";
}

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    int AccountBalance = 0;
    bool MarkForDelete = false;
};

string ReadClientAccountNumber()
{
    string AccountNumber;
    cout<< "\nEnter Account Number? ";
    getline(cin >> ws, AccountNumber);
    
    return AccountNumber;
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
    Client.AccountBalance = stoi(vString[4]);
    
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

bool IsClientExists(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }
    return false;
//OR
/* Not the best option


    vector<stClient> vClient = LoadClientsDataFromFile(FileName);
    for (stClient& c : vClient)
    {
        if (c.AccountNumber == AccountNumber)
        return true;
    }
    
    return false;
*/
}

void AddDataLineToFile(string FileName, string strDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile<< strDataLine <<endl;
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

    if (vClient.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!\n";
    else
    {
        for(stClient C : vClient)
        {
            PrintClientRecord(C);
            cout << endl;
        }
    } 

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------";

}

stClient ReadNewClient()
{
    stClient Client;

    Client.AccountNumber = ReadClientAccountNumber();

    while (IsClientExists(Client.AccountNumber, ClientFileName))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exists, ";
        Client.AccountNumber = ReadClientAccountNumber();
    }

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

void AddNewClient()
{    
    stClient NewClient = ReadNewClient();
    AddDataLineToFile(ClientFileName, ConvertRecordToLine(NewClient));
    
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding new Client:\n\n";
        AddNewClient();

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

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;
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

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;
    char Answer = 'n';

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

            cout << "\n\n Client Info Updated Successfully. \n";
            return true;
        }
    }
    else
        cout<< "\nClient with Account Number [" << AccountNumber << "] is not found!" <<endl;

    return false;
}

void FindClient(string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, Client, vClient))
        PrintClientCard(Client);
    else
        cout<< "\nClient with Account Number [" << AccountNumber << "] is not found!" <<endl;
}

enum enTransactionSection { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };

int DepositAmount(stClient& Client)
{
    char Answer = 'n';
    int Amount = ReadNumber("Please enter deposit amount? ");
    
    cout << "\n\n\nAre you sure you want to perform this transaction? n/y? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        cout << "\n\n Transaction performed Successfully. \n";
       return Client.AccountBalance + abs(Amount); 
    }
    else
    {
        cout << "\n\n No transaction was performed. \n";
        return Client.AccountBalance;
    }
}

int WithdrawAmount(stClient& Client)
{
    char Answer = 'n';
    int Amount = ReadNumber("Please enter withdraw amount? ");

    while (Amount > Client.AccountBalance)
    {
        cout<< "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << '\n';
        Amount = ReadNumber("Please enter another amount? ");
    }

    cout << "\n\n\nAre you sure you want to perform this transaction? n/y? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        cout << "\n\n Transaction performed Successfully. \n";
       return Client.AccountBalance - abs(Amount); 
    }
    else
    {
        cout << "\n\n No transaction was performed. \n";
        return Client.AccountBalance;
    }
}

stClient ChangeClientAccountBalance(enTransactionSection Section, stClient& Client)
{
    if (Section == enTransactionSection::Deposit)
    {
        Client.AccountBalance = DepositAmount(Client);
    }
    else if (Section == enTransactionSection::Withdraw)
    {
        Client.AccountBalance = WithdrawAmount(Client);
    }
    
    return Client;
}

bool UpdateClientTransactionByAccountNumber(enTransactionSection Section, string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;

    if (Section != enTransactionSection::TotalBalance && enTransactionSection::MainMenu)
    {
        if (FindClientByAccountNumber(AccountNumber, Client, vClient))
        {
            PrintClientCard(Client);
            for (stClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    ChangeClientAccountBalance(Section, C);
                }
            }
            
            SaveClientsDataToFile(ClientFileName, vClient);

            return true;
        }
    }
    return false;
}

void ShowTransactionMenu()
{
    PrintScreenTitle("Transactions Menu Screen");

    cout<< "\t[1] Deposit." <<endl;
    cout<< "\t[2] Withdraw." <<endl;
    cout<< "\t[3] Total Balance." <<endl;
    cout<< "\t[4] Main Menu." <<endl;
    cout<< "================================================" <<endl;
}

void DepositSection(enTransactionSection Section)
{
    PrintScreenTitle("Deposit Screen");
    string AccountNumber  = ReadClientAccountNumber();

    while (!(IsClientExists(AccountNumber, ClientFileName)))
    {
        cout<< "\nClient with Account Number [" << AccountNumber << "] does not exist.\n " <<endl;
        AccountNumber = ReadClientAccountNumber();
    }

    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);

    UpdateClientTransactionByAccountNumber(Section, AccountNumber, vClient);
}

void WithdrawSection(enTransactionSection Section)
{
    PrintScreenTitle("Withdraw Screen");
    string AccountNumber  = ReadClientAccountNumber();

    while (!(IsClientExists(AccountNumber, ClientFileName)))
    {
        cout<< "\nClient with Account Number [" << AccountNumber << "] does not exist.\n " <<endl;
        AccountNumber = ReadClientAccountNumber();
    }

    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);

    UpdateClientTransactionByAccountNumber(Section, AccountNumber, vClient);
}

int TotalBalances(vector<stClient>& vClient)
{
    int TotalSum = 0;
    
    for(stClient& C : vClient)
        {
            TotalSum += C.AccountBalance;
        }

    return TotalSum;    
}

void TotalBalanceSection()
{
    PrintScreenTitle("Total Balance Screen");

    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);

    cout << "\n\t\t\t\t Balances List (" << vClient.size() << ") Client(s).";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------\n" << endl;

    if (vClient.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!\n";
    else
    {
        for(stClient C : vClient)
        {
            cout << "| " << left << setw(15) << C.AccountNumber;
            cout << "| " << left << setw(30) << C.Name;
            cout << "| " << left << setw(12) << C.AccountBalance;;
            cout << endl;
        }
    } 

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------";

    cout << "\n\n\t\t\t\tTotal Balances = " << TotalBalances(vClient);

}

void GoBackToMainMenu()
{
    cout << "\n\nPress any Key to go back to main menu... ";
            cin.ignore();
            cin.get();

    //OR
/*  cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowMainMenu();
*/
}

void GetTransactionSection(enTransactionSection Section)
{
    switch (Section)
    {
        case enTransactionSection::Deposit:
            DepositSection(Section);
            break;
        
        case enTransactionSection::Withdraw:
            WithdrawSection(Section);
            break;
        
        case enTransactionSection::TotalBalance:
            TotalBalanceSection();
            break;
        
        case enTransactionSection::MainMenu:
            break;
    }
}

void GoBackToTransactionMenu()
{
    cout << "\n\nPress any Key to go back to Transactions menu... ";
            cin.ignore();
            cin.get();
}

enum enMainSection { ShowList = 1, AddNew = 2, Delete = 3, UpdateInfo = 4, Find = 5, Transactions = 6, Exit = 7 };

void ShowMainMenu()
{
    PrintScreenTitle("Main Menu Screen");

    cout<< "\t[1] Show Client List." <<endl;
    cout<< "\t[2] Add New Client." <<endl;
    cout<< "\t[3] Delete Client." <<endl;
    cout<< "\t[4] Update Client Info." <<endl;
    cout<< "\t[5] Find Client." <<endl;
    cout<< "\t[6] Transactions." <<endl;
    cout<< "\t[7] Exit." <<endl;
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
    AddClients();
}

void DeleteSection()
{
    PrintScreenTitle("Delete Client Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClient);
}

void UpdateInfoSection()
{
    PrintScreenTitle("Update Client Info Screen");

    vector <stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClient);
}

void FindSection()
{
    PrintScreenTitle("Find Client Screen");

    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    FindClient(AccountNumber, vClient);
}

void TransactionSection()
{
    enTransactionSection Section;
    
    do
    {
        resetScreen();
        ShowTransactionMenu();
        Section = (enTransactionSection)ReadNumber("Choose what do you want to do? [1 to 4]? ", 1, 4);
        

        resetScreen();
        GetTransactionSection(Section);
        
        if(Section != enTransactionSection::MainMenu)
            GoBackToTransactionMenu();

    } while (Section != enTransactionSection::MainMenu);

}

void ExitSection()
{
    PrintScreenTitle("Program Ends :-)");
}

void GetMainSection(enMainSection Section)
{
    switch (Section)
    {
        case enMainSection::ShowList:
            ShowListSection();
            break;
        
        case enMainSection::AddNew:
            AddNewSection();
            break;
        
        case enMainSection::Delete:
            DeleteSection();
            break;
        
        case enMainSection::UpdateInfo:
            UpdateInfoSection();
            break;
        
        case enMainSection::Find:
            FindSection();
            break;
        
        case enMainSection::Transactions:
            TransactionSection();
            break;

        case enMainSection::Exit:
            ExitSection();
            break;
    }
}

void startTheBankProject()
{
    enMainSection Section;
    do
    {
        resetScreen();
        ShowMainMenu();
        Section = (enMainSection)ReadNumber("Choose what do you want to do? [1 to 7]? ", 1, 7);
        
        //reset if not transaction
        resetScreen();
        GetMainSection(Section);

        if(Section != enMainSection::Exit && Section != enMainSection::Transactions)
            GoBackToMainMenu();

    } while (Section != enMainSection::Exit);
    
}

int main()
{
    startTheBankProject();
    return 0;
}