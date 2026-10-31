#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientFileName = "Clients.txt";

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

double ReadDoubleNumber(string message)
{
    double num;
    cout<< message;
    cin>> num;

    return num;
}

double ReadDoubleNumber(string message, double From, double To)
{
    double num;
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
    double AccountBalance = 0;
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
    MyFile.open(FileName, ios::in); // read mode
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
    cout<< "------------------------------------------------";
    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nPinCode : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout<< "\n------------------------------------------------\n";
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
        for(stClient& C : vClient)
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

void AddNewClients()
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
    MyFile.open(FileName, ios::out); // overwrite

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
        cout << "\n\nAre you sure you want delete client? n/y? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveClientsDataToFile(ClientFileName, vClient);

            //Refresh Clients
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
        cout << "\n\nAre you sure you want update this client info? n/y? ";
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

bool ChangeClientAccountBalance(enTransactionSection Section, double Amount, stClient& Client)
{
    char Answer = 'n';
    
    cout << "\n\n\nAre you sure you want to perform this transaction? n/y? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        if (Section == enTransactionSection::Deposit)
        {
            Client.AccountBalance += abs(Amount);
        }
        else if (Section == enTransactionSection::Withdraw)
        {
            Client.AccountBalance -= abs(Amount);
        }
        
        cout << "\n\n Transaction performed Successfully. New Balance is: " << Client.AccountBalance <<endl;
        return true;
    }
    else
        cout << "\n\n No transaction was performed. \n";
    return false;
}

bool UpdateClientTransactionByAccountNumber(enTransactionSection Section, double Amount, string AccountNumber, vector<stClient>& vClient)
{
    stClient Client;

    if (Section == enTransactionSection::Deposit || Section == enTransactionSection::Withdraw)
    {
        for (stClient& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                if(ChangeClientAccountBalance(Section, Amount, C))
                {
                    SaveClientsDataToFile(ClientFileName, vClient);
                    return true;
                }    
            }
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
    
    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber  = ReadClientAccountNumber();    

    while (!(FindClientByAccountNumber(AccountNumber, Client, vClient)))
    {
        cout<< "\nClient with Account Number [" << AccountNumber << "] does not exist.\n " <<endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
            
    double Amount = ReadDoubleNumber("\nPlease enter deposit amount? ");
    
    UpdateClientTransactionByAccountNumber(Section, Amount, AccountNumber, vClient);
}

void WithdrawSection(enTransactionSection Section)
{
    PrintScreenTitle("Withdraw Screen");
    
    vector<stClient> vClient = LoadClientsDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber  = ReadClientAccountNumber();    

    while (!(FindClientByAccountNumber(AccountNumber, Client, vClient)))
    {
        cout<< "\nClient with Account Number [" << AccountNumber << "] does not exist.\n " <<endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
            
    double Amount = ReadDoubleNumber("\nPlease enter withdrawal amount? ");

    while (abs(Amount) > Client.AccountBalance)
    {
        cout<< "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << '\n';
        Amount = ReadDoubleNumber("Please enter another amount? ");
    }

    UpdateClientTransactionByAccountNumber(Section, Amount, AccountNumber, vClient);
}

/*double TotalBalances(vector<stClient>& vClient)
{
    double TotalSum = 0;
    
    for(stClient& C : vClient)
        {
            TotalSum += C.AccountBalance;
        }

    return TotalSum;    
}
*/

void PrintClientRecordBalanceLine(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
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

    double TotalBalances = 0;

    if (vClient.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!\n";
    else
    {
        for(stClient& Client : vClient)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    } 

    cout << "\n---------------------------------------------------------";
    cout << "-------------------------------------------";

    cout << "\n\n\t\t\t\tTotal Balances = " << TotalBalances;

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

void AddNewClientsSection()
{
    PrintScreenTitle("Add New Client Screen");
    AddNewClients();
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

void FindClientSection()
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
        //ShowTransactionsMenu
        resetScreen();
        ShowTransactionMenu();
        Section = (enTransactionSection)ReadNumber("Choose what do you want to do? [1 to 4]? ", 1, 4);
        
        //PerfromTranactionsMenuOption(enTransactionsMenuOptions TransactionMenuOption)
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
            AddNewClientsSection();
            break;
        
        case enMainSection::Delete:
            DeleteSection();
            break;
        
        case enMainSection::UpdateInfo:
            UpdateInfoSection();
            break;
        
        case enMainSection::Find:
            FindClientSection();
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
        //ShowMainMenu
        resetScreen();
        ShowMainMenu();
        Section = (enMainSection)ReadNumber("Choose what do you want to do? [1 to 7]? ", 1, 7);
        
        // PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
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