# Bank Management System Extension 1

This project is a simple **Bank Management System Extension 1** written in C++ that allows users to manage client data, perform transactions such as deposits and withdrawals, and keep track of client balances. The program works by reading and writing client data from a text file (`clients.txt`), providing various menu options for easy interaction.

## Table of Contents
- [Project Information](#Project-Information)
- [Live Demo](#Live-Demo)
- [Features](#features)
- [How It Works](#how-it-works)
- [Project Flow](#Project-Flow)
- [File Structure](#File-Structure)

## Project Information
This C++ simple console-based Bank Management System project was created at the end of the [7th course](https://programmingadvices.com/p/algorithms-and-problem-solving-level-3) from the Roadmap for General Foundation in Programming @ [Programming Advices](https://programmingadvices.com/).

## Live Demo
https://github.com/user-attachments/assets/3c7d853e-f6cb-41c7-8673-db4ab6b6b5e8

## Features
- **Client List:** Display a list of all clients, including account number, pin code, name, phone, and account balance.
- **Add New Client:** Add new client information such as account number, pin code, name, phone, and balance.
- **Delete Client:** Remove a client from the system by account number.
- **Update Client Info:** Modify the details of an existing client.
- **Find Client:** Search for a client by account number and display their details.
- **Data Persistence:** All client information is saved to and retrieved from a file (`clients.txt`).
- **Transaction System**: Perform deposits, withdrawals, and view total balances.
- **File-Based Storage**: Store and retrieve client data from a text file.
- **Simple Menu Interface**: Navigate through different functionalities using the main and transaction menus.

## How It Works
1. **Client Data Storage**: 
   - The system reads and writes client data (account number, pin code, name, phone number, and balance) from a text file (`clients.txt`).
   
2. **Main Menu**:
   - The main menu provides the following options:
     1. Show Client List
     2. Add New Client
     3. Delete Client
     4. Update Client Info
     5. Find Client
     6. Transactions (Deposit, Withdraw, and View Total Balances)
     7. Exit the program

3. **Transactions Menu**:
   - In the transactions menu, users can:
     1. Deposit money into a client account.
     2. Withdraw money from a client account (ensuring balance is sufficient).
     3. View the total balances of all clients in the system.

4. **Client Data Validation**:
   - The system ensures that account numbers are unique and validates the correctness of transactions (e.g., ensuring that withdrawals do not exceed account balances).

## Project Flow
1. **Loading Clients**: 
   - When the program starts, it loads all client data from the `clients.txt` file into a vector.

2. **Main Menu Navigation**:
   - The user can choose from the available main menu options to manage clients or perform transactions.

3. **Client Management**:
   - If the user chooses to add, update, or delete a client, the program interacts with the client data and updates the file accordingly.

4. **Transaction Operations**:
   - For deposits or withdrawals, the program checks the client account's balance and updates it accordingly, saving the changes back to the file.

5. **Ending the Program**:
   - The program will save any modifications made to the client list or balances back to the `clients.txt` file before exiting.

## File Structure
### `project-2-bank-extension.cpp`: The main program file containing the source code for the Bank Management System.
### `clients.txt`: The data file where client information is stored. This file is created automatically when the program runs.
