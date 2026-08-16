#include <iostream>
#include <string>
#include <vector>
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

void ChooseSection()
{
    int num = ReadNumber("Choose what do you want to do? [1 to 6]? ");
    
    switch (num)
    {
    case 1:
        resetScreen();
        MainSection();
        break;
    
    case 2:
        resetScreen();
        PrintTitle(num);
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
    return 0;
}