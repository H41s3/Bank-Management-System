# Bank Account Management System

A console-based C++ project to manage bank accounts, including creating accounts, deposits, withdrawals, balance inquiries, and more.

## Features

- Create accounts (single or joint holder)
- Automatically generate a unique account number for each account
- Deposit and withdraw money
- Check account balance
- Change account PIN
- Close an account
- Admin panel to view total accounts and account details

## Technologies Used

- **C++**: Core programming language used for the project.
- **Standard Libraries**: Utilizes the following C++ libraries:
  - `<iostream>` for input/output operations.
  - `<string>` for handling strings.
  - `<vector>` for managing dynamic arrays.
  - `<cstdlib>` for generating random numbers (used in account number generation).

## How It Works

1. **Account Creation**: Users can create either a savings or current account. Each account is assigned a randomly generated 10-digit account number, which is shown after the account is successfully created. Users can also choose between a single holder or a joint holder account.
   
2. **Account Management**: Once an account is created, users can perform the following operations:
   - **Deposit** money into the account.
   - **Withdraw** money from the account.
   - **Check the account balance**.
   - **Change the account PIN** for security.
   - **Close an account**.
   
3. **Admin Functions**: Admins can view the total number of savings and current accounts as well as detailed account information for all accounts in the system.

## Setup and Installation

### Prerequisites

- You need to have a C++ compiler installed, such as `g++` or `clang`.
- Git (for cloning the repository).
