#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string clientsFileName = "clients.txt";
enum enMainMenuOptions
{
	showClientList = 1,
	newClient = 2,
	deleteClient = 3,
	updateClientInfo = 4,
	findClient = 5,
	transaction = 6,
	endProgram = 7
};

enum enTransactionsMenuOptions
{
	deposit = 1,
	withdraw = 2,
	totalBalances = 3,
	mainMenu = 4
};

struct stClientData
{
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	double accountBalance = 0;
	bool markForDeletion = false;
	bool markForUpdate = false;
};

void showMainMenuScreen(vector<stClientData>& clients);
void showTransactionsMenuScreen(vector<stClientData>& clients);

string readString(string message)
{
	string userText;
	cout << message;
	getline(cin >> ws, userText);
	return userText;
}

char readCharacter(string message)
{
	char userCharacter;
	do
	{
		cout << message;
		cin >> userCharacter;
	} while (userCharacter != 'Y' && userCharacter != 'y' && userCharacter != 'N' && userCharacter != 'n');
	return userCharacter;
}

short readNumberInRange(string message, short from, short to)
{
	short userNumber = 0;
	do
	{
		cout << message;
		cin >> userNumber;
	} while (userNumber < from || userNumber > to);
	return userNumber;
}

stClientData readClientDataExceptAccountNumber(stClientData client)
{
	cout << "Please Update Client Data:" << endl;
	client.accountNumber = client.accountNumber;
	client.pinCode = readString("\nEnter PinCode ? ");
	client.name = readString("\nEnter Name ? ");
	client.phone = readString("\nEnter Phone ? ");
	cout << "\nEnter Balance ? ";
	cin >> client.accountBalance;
	return client;
}

vector<string> split(string client, string delimiter = "#//#")
{
	vector<string> splitWords;
	string splitWord = "";
	short delimiterPosition = 0;

	while ((delimiterPosition = client.find(delimiter)) != client.npos)
	{
		splitWord = client.substr(0, delimiterPosition);
		if (splitWord != "")
			splitWords.push_back(splitWord);
		client.erase(0, delimiterPosition + delimiter.length());
	}
	if (client != "")
		splitWords.push_back(client);
	return splitWords;
}

stClientData saveVectorToStructure(vector<string> splitWords)
{
	stClientData client;
	client.accountNumber = splitWords[0];
	client.pinCode = splitWords[1];
	client.name = splitWords[2];
	client.phone = splitWords[3];
	client.accountBalance = stod(splitWords[4]);
	return client;
}

vector<stClientData> loadClientsDataFromFile(string fileName)
{
	vector<stClientData> clients;

	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open())
	{
		string client = "";
		while (getline(myFile, client))
		{
			if (client != "")
				clients.push_back(saveVectorToStructure(split(client)));
		}
		myFile.close();
	}
	return clients;
}

void printClientData(stClientData client)
{
	cout << "\nThe Following Are The Client Details :" << endl;
	cout << "\nAccount Number  | " << client.accountNumber;
	cout << "\nPinCode         | " << client.pinCode;
	cout << "\nName            | " << client.name;
	cout << "\nPhone           | " << client.phone;
	cout << "\nAccount Balance | " << client.accountBalance << endl;
}

void printClientListScreenHeader(vector<stClientData> clients)
{
	cout << "\t\t\t\t\tClient List (" << clients.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void printClientListScreenBodyClient(stClientData client)
{
	cout << "| " << left << setw(15) << client.accountNumber;
	cout << "| " << left << setw(10) << client.pinCode;
	cout << "| " << left << setw(40) << client.name;
	cout << "| " << left << setw(12) << client.phone;
	cout << "| " << left << setw(12) << client.accountBalance << endl;
}

void showClientListScreen(vector<stClientData> clients)
{
	printClientListScreenHeader(clients);
	for (stClientData& c : clients)
		printClientListScreenBodyClient(c);
}

void printGeneralHeader(string message)
{
	cout << "=======================================================================================================" << endl;
	cout << "\t\t\t\t\t" << message << endl;
	cout << "=======================================================================================================" << endl;
}

stClientData readNewClient(vector<stClientData>& clients)
{
	stClientData newClient;
	newClient.accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	for (stClientData& c : clients)
	{
		if (c.accountNumber == newClient.accountNumber)
		{
			do
			{
				cout << "\nClient With [" << newClient.accountNumber << "] Already Exists, ";
				newClient.accountNumber = readString("Please Enter Another Account Number ?  ");
			} while (c.accountNumber == newClient.accountNumber);
		}
	}

	newClient.pinCode = readString("\nPlease Enter Your PinCode ?  ");
	newClient.name = readString("\nPlease Enter Your Name ?  ");
	newClient.phone = readString("\nPlease Enter Your Phone ?  ");
	cout << "\nPlease Enter Your Account Balance ?  ";
	cin >> newClient.accountBalance;

	// Refresh clients list
	clients.push_back(newClient);
	return newClient;
}

string convertClientStructureToRecord(stClientData client, string delimiter = "#//#")
{
	string record = "";
	record += client.accountNumber + delimiter;
	record += client.pinCode + delimiter;
	record += client.name + delimiter;
	record += client.phone + delimiter;
	record += to_string(client.accountBalance);
	return record;
}

void saveRecordToFile(string record)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out | ios::app);
	if (myFile.is_open())
	{
		myFile << record << endl;
	}
	myFile.close();
}

void addNewClient(vector<stClientData>& clients)
{
	stClientData client = readNewClient(clients);
	saveRecordToFile(convertClientStructureToRecord(client));
}

void showAddNewClientScreen(vector<stClientData>& clients)
{
	char addAgain = 'Y';
	do
	{
		system("cls");
		printGeneralHeader("Adding New Client Screen");
		cout << "\nAdding New Client :" << endl;
		addNewClient(clients);
		addAgain = readCharacter("\nClient Added Successfully, Do You Want To Add More Clients ? [Y/N] ?  ");
	} while (toupper(addAgain) == 'Y');
}

bool findClientByAccountNumber(string accountNumber, vector<stClientData> clients, stClientData& client)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			client = c;
			return true;
		}
	}
	return false;
}

void markClientForDeletionByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			c.markForDeletion = true;
			break;
		}
	}
}

void saveClientsToFile(vector<stClientData>& clients)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out);
	if (myFile.is_open())
	{
		string client = "";
		for (stClientData& c : clients)
		{
			if (c.markForDeletion == false)
			{
				client = convertClientStructureToRecord(c);
				myFile << client << endl;
			}
		}
		myFile.close();
	}
}

void saveClientsToFileAfterUpdate(vector<stClientData>& clients)
{
	fstream myFile;
	myFile.open(clientsFileName, ios::out);
	if (myFile.is_open())
	{
		string client = "";
		for (stClientData& c : clients)
		{
			if (c.markForUpdate == true)
			{
				c = readClientDataExceptAccountNumber(c);
				client = convertClientStructureToRecord(c);
				break;
			}
		}
		saveClientsToFile(clients);
		myFile.close();
	}
}

void deleteClientByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	stClientData client;
	char deleteAgain = 'N';
	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);

		deleteAgain = readCharacter("\nAre You Sure You Want To Delete Client/ " + client.name + " ? [Y / N] ? ");
		if (toupper(deleteAgain) == 'Y')
		{
			markClientForDeletionByAccountNumber(accountNumber, clients);
			saveClientsToFile(clients);

			// Refresh Clients list
			clients = loadClientsDataFromFile(clientsFileName);
			cout << "\nClient Deleted Successfully!" << endl;
		}
	}
	else
	{
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
	}
}

void showDeleteClientScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Delete Client Screen");
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	deleteClientByAccountNumber(accountNumber, clients);
}

void markClientForUpdateByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	for (stClientData& c : clients)
	{
		if (c.accountNumber == accountNumber)
		{
			c.markForUpdate = true;
			break;
		}
	}
}

void updateClientByAccountNumber(string accountNumber, vector<stClientData>& clients)
{
	stClientData client;
	char updateAgain = 'N';

	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);

		updateAgain = readCharacter("\nAre You Sure You Want To Update Client/ " + client.name + " ? [Y / N] ? ");
		if (toupper(updateAgain) == 'Y')
		{
			markClientForUpdateByAccountNumber(accountNumber, clients);
			saveClientsToFileAfterUpdate(clients);

			cout << "\nClient Updated Successfully!" << endl;
		}
	}
	else
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
}

void showUpdateClientInfoScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Update Client Info Screen");
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	updateClientByAccountNumber(accountNumber, clients);
}

void showFindClientScreen(vector<stClientData>& clients)
{
	stClientData client;
	printGeneralHeader("Find Client Screen");
	string accountNumber = readString("\nPlease Enter Your Account Number ?  ");
	if (findClientByAccountNumber(accountNumber, clients, client))
	{
		printClientData(client);
	}
	else
		cout << "\nClient With Account Number (" << accountNumber << ") Not Found!" << endl;
}

double getDepositOrWithdraw(string message)
{
	double amountOfMoney = 0;
	do
	{
		cout << message;
		cin >> amountOfMoney;
	} while (amountOfMoney <= 0);
	return amountOfMoney;
}

void validateDeposit(vector<stClientData>& clients)
{
	stClientData client;
	char checkTransaction = 'Y';

	string accountNumber = readString("\nPlease Enter Account Number ?  ");
	while (!(findClientByAccountNumber(accountNumber, clients, client)))
	{
		cout << "\nClient With Account Number [" << accountNumber << "] Not Exists." << endl;
		accountNumber = readString("\nPlease Enter Another Account Number ?  ");
	}
	printClientData(client);

	double deposit = getDepositOrWithdraw("\nPlease Enter Deposit Amount ?  ");
	checkTransaction = readCharacter("\nAre You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == client.accountNumber)
			{
				c.accountBalance += deposit;
				client = c;
				break;
			}
		}
	}
	// update File After Deposit
	saveClientsToFile(clients);

	cout << "\nDone Successfully, Your Balance After Deposit = " << client.accountBalance << endl;
}

void validateWithdraw(vector<stClientData>& clients)
{
	stClientData client;
	char checkTransaction = 'Y';

	string accountNumber = readString("\nPlease Enter Account Number ?  ");
	while (!(findClientByAccountNumber(accountNumber, clients, client)))
	{
		cout << "\nClient With Account Number [" << accountNumber << "] Not Exists." << endl;
		accountNumber = readString("\nPlease Enter Another Account Number ?  ");
	}
	printClientData(client);

	double withdraw = getDepositOrWithdraw("\nPlease Enter Withdraw Amount ?  ");
	while (withdraw > client.accountBalance)
	{
		cout << "Amount Exceeds The Balance, You Can Withdraw Up To : " << client.accountBalance << endl;
		withdraw = getDepositOrWithdraw("Please Enter Another Amount ?  ");
	}

	checkTransaction = readCharacter("Are You Sure You Want To Perform This Transaction ? [Y/N] ?  ");
	if (toupper(checkTransaction) == 'Y')
	{
		for (stClientData& c : clients)
		{
			if (c.accountNumber == client.accountNumber)
			{
				c.accountBalance += (withdraw * -1);
				client = c;
				break;
			}
		}
	}
	// Update File After Withdraw
	saveClientsToFile(clients);

	cout << "\nYour Balance After Withdraw = " << client.accountBalance << endl;
}

double getTotalBalances(vector<stClientData> clients)
{
	double totalBalances = 0;
	for (stClientData& c : clients)
	{
		totalBalances += c.accountBalance;
	}
	return totalBalances;
}

void showDepositScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Deposit Screen");
	validateDeposit(clients);
}

void showWithdrawScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Withdraw Screen");
	validateWithdraw(clients);
}

void printTransactionsMenuScreenBody()
{
	cout << "\t\t[1] Deposit." << endl;
	cout << "\t\t[2] Withdraw." << endl;
	cout << "\t\t[3] Total Balances." << endl;
	cout << "\t\t[4] Main Menu." << endl;
	cout << "=======================================================================================================" << endl;
}

void printBalancesListScreenHeader(vector<stClientData> clients)
{
	cout << "\t\t\t\t\tBalances List (" << clients.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Account Balance" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

void printBalancesListScreenBodyClient(stClientData client)
{
	cout << "| " << left << setw(15) << client.accountNumber;
	cout << "| " << left << setw(40) << client.name;
	cout << "| " << left << setw(12) << client.accountBalance << endl;
}

void showTotalBalancesScreen(vector<stClientData> clients)
{
	printBalancesListScreenHeader(clients);
	for (stClientData& c : clients)
		printBalancesListScreenBodyClient(c);
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t\t\t\t\tTotal Balances = " << getTotalBalances(clients) << endl;
}

void goBackToTransactionsMenu(vector<stClientData>& clients)
{
	cout << "\nPress Any Key to go back to The Previous Menu...  ";
	system("pause >nul");
	system("cls");
	showTransactionsMenuScreen(clients);
}

void goBackToMainMenu(vector<stClientData>& clients)
{
	cout << "\nPress Any Key to go back to The Main Menu...  ";
	system("pause >nul");
	system("cls");
	showMainMenuScreen(clients);
}

void performTransactionsMenuScreen(vector<stClientData>& clients)
{
	enTransactionsMenuOptions transactionsOptions = (enTransactionsMenuOptions)readNumberInRange("\nChoose What Do You want To do ? [1 to 4] ?  ", 1, 4);
	switch (transactionsOptions)
	{
	case enTransactionsMenuOptions::deposit:
		system("cls");
		showDepositScreen(clients);
		goBackToTransactionsMenu(clients);
		break;
	case enTransactionsMenuOptions::withdraw:
		system("cls");
		showWithdrawScreen(clients);
		goBackToTransactionsMenu(clients);
		break;
	case enTransactionsMenuOptions::totalBalances:
		system("cls");
		showTotalBalancesScreen(clients);
		goBackToTransactionsMenu(clients);
		break;
	case enTransactionsMenuOptions::mainMenu:
		system("cls");
		goBackToMainMenu(clients);
		break;
	}
}

void showTransactionsMenuScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Transactions Menu Screen");
	printTransactionsMenuScreenBody();
	performTransactionsMenuScreen(clients);
}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

void printMainMenuScreenBody()
{
	cout << "\t\t[1] Show Client List." << endl;
	cout << "\t\t[2] Add New Client." << endl;
	cout << "\t\t[3] Delete Client." << endl;
	cout << "\t\t[4] Update Client Info." << endl;
	cout << "\t\t[5] Find Client." << endl;
	cout << "\t\t[6] Transactions." << endl;
	cout << "\t\t[7] Exit." << endl;
	cout << "=======================================================================================================" << endl;
}

void performMainMenuOptions(vector<stClientData>& clients)
{
	enMainMenuOptions mainMenuOptions = (enMainMenuOptions)readNumberInRange("\nChoose What Do You Want To Do ? [1 to 7] ?  ", 1, 7);
	switch (mainMenuOptions)
	{
	case enMainMenuOptions::showClientList:
		system("cls");
		showClientListScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::newClient:
		system("cls");
		showAddNewClientScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::deleteClient:
		system("cls");
		showDeleteClientScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::updateClientInfo:
		system("cls");
		showUpdateClientInfoScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::findClient:
		system("cls");
		showFindClientScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::transaction:
		system("cls");
		showTransactionsMenuScreen(clients);
		goBackToMainMenu(clients);
		break;
	case enMainMenuOptions::endProgram:
		system("cls");
		ShowEndScreen();
		break;
	default:
		break;
	}
}

void showMainMenuScreen(vector<stClientData>& clients)
{
	printGeneralHeader("Main Menu Screen");
	printMainMenuScreenBody();
	performMainMenuOptions(clients);
}

int main()
{
	vector<stClientData> clients = loadClientsDataFromFile(clientsFileName);
	showMainMenuScreen(clients);
	return 0;
}