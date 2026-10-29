#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
using namespace std;
const string ClientsFileName = "Clients.txt";
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client);
sClient ReadNewClient(vector<sClient> vClients)
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    while (FindClientByAccountNumber(Client.AccountNumber, vClients, Client))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exist. Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ReadAccountNumber()
{
    string AnotherAccount = "";
    cout << "Enter another account number? ";
    cin >> AnotherAccount;
    return AnotherAccount;
}

void PrintHeader(string Line)
{
    cout << "---------------------------------------------\n";
    cout << "\t\t" << Line << "\n";
    cout << "---------------------------------------------\n";
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); /* erase() until
        positon and move to next word. */
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")

{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")

{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector<sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

// I designed Show client functions

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient(vector<sClient> vClients)
{

    sClient Client;
    Client = ReadNewClient(vClients);
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddClients(vector<sClient> &vClients)
{

    char AddMore = 'Y';
    do
    {
        system("cls");
        PrintHeader("Add New Client");
        cout << "Adding New Client:\n\n";
        AddNewClient(vClients);
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";

        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');

    vClients = LoadCleintsDataFromFile(ClientsFileName);
}

// I designed add new client functions

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------------\n";
    cout << "Accout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance << "\n";
    cout << "-----------------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    for (sClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintHeader("Delete Client");
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

            SaveCleintsDataToFile(ClientsFileName, vClients);
            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

        return false;
    }

    return false;
}

// I designed delete client functions

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintHeader("Update Client");
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n? ";

        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

        return false;
    }

    return false;
}

// I designed update client functions

void ShowMainMenu()
{
    cout << "=============================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "=============================================\n";

    cout << "\t\t[1] Show Client List.\n";
    cout << "\t\t[2] Add New Client.\n";
    cout << "\t\t[3] Delete Client.\n";
    cout << "\t\t[4] Update Client Info.\n";
    cout << "\t\t[5] Find Client.\n";
    cout << "\t\t[6] Transactions.\n";
    cout << "\t\t[7] Exit." << endl;
    cout << "=============================================\n";
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...\n";
    system("pause>0");
    system("cls");
}

int ReadChoice(int from, int to)
{
    int choice;

    do
    {
        cout << "Choose what do you want to do? [" << from << " to " << to << "]? ";
        cin >> choice;

    } while (choice < from || choice > to);

    return choice;
}

//---------------------Transactions----------------------

void ShowTransactionsMenueScreen()
{
    cout << "=============================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "=============================================\n";
    cout << "\t\t[1]Deposite\n";
    cout << "\t\t[2]Withdraw\n";
    cout << "\t\t[3]Total Balance\n";
    cout << "\t\t[4]Main Menue\n";
    cout << "=============================================\n";
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...\n";
    system("pause>0");
    system("cls");
}

double ReadAmount(string message)
{
    double amount;

    cout << message;
    cin >> amount;

    return amount;
}

void Deposit(vector<sClient> &vClients, sClient &Client)
{
    PrintHeader("Deposit Screen");
    char Answer = 'n';
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client) == false)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return;
    }

    PrintClientCard(Client);

    double amount = ReadAmount("Please,Enter Deposite amount: ");
    cout << "\n\nAre you sure you want update this client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        if (amount <= 0)
        {
            cout << "Enter positive amount\n";
            return;
        }

        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += amount;
                Client = C;
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "Doposit successful!\n";
        cout << "New balance = " << Client.AccountBalance << endl;
    }
    else
    {
        cout << "Deposit is not compeleted\n";
    }
}

void Withdraw(vector<sClient> &vClients, sClient &Client)
{
    PrintHeader("Withdraw Screen");
    char Answer = 'n';
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client) == false)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return;
    }

    PrintClientCard(Client);

    double amount = ReadAmount("Please,Enter Withdraw amount: ");
    cout << "\n\nAre you sure you want update this client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        if (Client.AccountBalance < amount || amount <= 0)
        {
            cout << "Not enough balance!\n";
            return;
        }

        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance -= amount;
                Client = C;
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "Withdraw successful!\n";
        cout << "New balance = " << Client.AccountBalance << endl;
    }
    else
    {
        cout << "Withdraw is not compeleted\n";
    }
}

double ShowTotalBalance(vector<sClient> &vClients)
{
    double TotalBalance = 0;
    for (const sClient &C : vClients)
    {
        TotalBalance += C.AccountBalance;
    }
    PrintAllClientsData(vClients);
    cout << "\n\t\t\t Total Balance = ";
    return TotalBalance;
}

void Transactions(vector<sClient> &vClients, sClient &Client)
{
    int number = 0;
    do
    {
        ShowTransactionsMenueScreen();
        number = ReadChoice(1, 4);

        switch (number)
        {
        case 1:
        {
            system("cls");
            Deposit(vClients, Client);
            GoBackToTransactionsMenue();
            break;
        }

        case 2:
        {
            system("cls");
            Withdraw(vClients, Client);
            GoBackToTransactionsMenue();
            break;
        }

        case 3:
        {
            system("cls");
            cout << ShowTotalBalance(vClients) << endl;
            GoBackToTransactionsMenue();
            break;
        }

        case 4:
        {
            system("cls");
            break;
        }

        // extra process to save file from error
        default:
            cout << "Enter a valid choice\n";
            break;
        }

    } while (number != 4);
}

void StartProgram()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    int choice = 0;

    do
    {
        ShowMainMenu();
        choice = ReadChoice(1, 7);

        switch (choice)
        {
        case 1:
        {
            system("cls");
            PrintAllClientsData(vClients);
            GoBackToMainMenue();
            break;
        }

        case 2:
        {
            system("cls");
            AddClients(vClients);
            GoBackToMainMenue();
            break;
        }

        case 3:
        {
            system("cls");
            string AccountNumber = ReadClientAccountNumber();
            DeleteClientByAccountNumber(AccountNumber, vClients);
            GoBackToMainMenue();
            break;
        }

        case 4:
        {
            system("cls");
            string AccountNumber = ReadClientAccountNumber();
            UpdateClientByAccountNumber(AccountNumber, vClients);
            GoBackToMainMenue();
            break;
        }

        case 5:
        {
            system("cls");
            string AccountNumber = ReadClientAccountNumber();
            if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            {
                PrintClientCard(Client);
            }
            else
            {
                cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
            }

            GoBackToMainMenue();
            break;
        }

        case 6:
        {
            system("cls");
            Transactions(vClients, Client);
            break;
        }

        case 7:
        {
            system("cls");
            cout << "-----------------------------------------\n";
            cout << "\t\tProgramm Ends :-)\n";
            cout << "-----------------------------------------\n";
            exit(0);
            break;
        }

        // extra process to save file from error
        default:
            cout << "Enter a number [from 1 to 6]\n";
            break;
        }

    } while (choice != 7);
}

int main()
{

    StartProgram();

    return 0;
}
