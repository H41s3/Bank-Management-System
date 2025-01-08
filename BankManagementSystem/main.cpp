#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // for rand()

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"  // Windows uses "cls"
#else
    #define CLEAR "clear"  // UNIX/Linux/Mac uses "clear"
#endif

int total_saving_accounts = 0;
int total_current_accounts = 0;

class account {
public:
    string name_of_account_holder;
    string name_of_joint_account_holder;
    long long int account_number;
    int balance;
    string type_of_account;
    string pin;

    // In case of single holder account
    account(string accholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
        name_of_joint_account_holder = "No Joint Holder in this account";
    }

    // In case of multiple holder account
    account(string accholdername, string jointholdername, int bal, string typeofacc, string pc) {
        account_number = rand() % 100000 + 1000000000;
        name_of_account_holder = accholdername;
        name_of_joint_account_holder = jointholdername;
        balance = bal;
        type_of_account = typeofacc;
        pin = pc;
    }
};

vector<account> accts;

void display_details(long long int accnum) {
    bool acc_exists = false;
    for (auto it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            cout << "\nAccount Number : " << it.account_number;
            cout << "\nAccount Holder Name : " << it.name_of_account_holder;
            cout << "\nJoint Holder Name : " << it.name_of_joint_account_holder;
            cout << "\nBalance in your account : " << it.balance;
            cout << "\nType of Account : " << it.type_of_account;
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.";
        exit(0);
    }
}

bool create_account(vector<account>& accts) {
    system(CLEAR);
    string accholder_name;
    cout << "\nENTER YOUR DETAILS HERE : ";
    cout << "\nName of Account Holder : ";
    cin >> accholder_name;
    string str;
    cout << "\nDo you want to have a joint holder account? Type YES/NO : ";
    cin >> str;
    string joint_holder;
    if (str == "YES") {
        cout << "Enter the name of Joint Holder : ";
        cin >> joint_holder;
    }
    string pin;
    cout << "\nEnter the pin : ";
    cin >> pin;
    string typeofacc;
    int choice;
    cout << "\nEnter the type of account : ";
    cout << "1 - Savings Account\n";
    cout << "2 - Current Account\n";
    cout << "Enter your choice here : ";
    cin >> choice;
    typeofacc = (choice == 1) ? "Savings" : "Current";

    int balance;
    cout << "\nEnter the balance you want to have initially in your account : ";
    cin >> balance;

    // Single holder account logic
    if (str == "NO") {
        account ob(accholder_name, balance, typeofacc, pin);
        accts.push_back(ob);
        if (typeofacc == "Savings")
            total_saving_accounts++;
        else
            total_current_accounts++;
        cout << "\t\t|-----------------------------------------------|\n";
        cout << "\t\t|     ACCOUNT CREATED SUCCESSFULLY!             |\n";
        cout << "\t\t|-----------------------------------------------|\n";
        display_details(ob.account_number);
        return true;
    }

    // Joint holder account logic
    else if (str == "YES") {
        if (typeofacc == "Current" && balance < 10000) {
            cout << "\t\t|-----------------------------------------------|\n";
            cout << "\t\t|     INSUFFICIENT BALANCE                      |\n";
            cout << "\t\t|-----------------------------------------------|\n";
            return false;
        } else {
            account ob(accholder_name, joint_holder, balance, typeofacc, pin);
            accts.push_back(ob);
            if (typeofacc == "Savings")
                total_saving_accounts++;
            else
                total_current_accounts++;
            cout << "\t\t|-----------------------------------------------|\n";
            cout << "\t\t|     ACCOUNT CREATED SUCCESSFULLY!             |\n";
            cout << "\t\t|-----------------------------------------------|\n";
            display_details(ob.account_number);
            return true;
        }
    }

    return false;
}

bool change_pin() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;
    bool acc_exists = false;
    for (auto& it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            string newpin, oldpin;
            cout << "Enter the old pin : ";
            cin >> oldpin;
            if (oldpin == it.pin) {
                cout << "Enter new pin : ";
                cin >> newpin;
                it.pin = newpin;
                display_details(it.account_number);
                return true;
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.";
        return false;
    }
    return false;
}

bool deposit_into_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;
    bool acc_exists = false;
    for (auto& it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            string pinfordepo;
            cout << "Enter the pin : ";
            cin >> pinfordepo;
            if (pinfordepo == it.pin) {
                int deposit_amount;
                cout << "Enter the amount you want to deposit : ";
                cin >> deposit_amount;
                it.balance += deposit_amount;
                cout << "Your Updated details : ";
                display_details(it.account_number);
                return true;
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.";
        return false;
    }
    return false;
}

bool withdraw_from_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;
    bool acc_exists = false;
    for (auto& it : accts) {
        if (it.account_number == accnum) {
            acc_exists = true;
            string pinfordepo;
            cout << "Enter the pin : ";
            cin >> pinfordepo;
            if (pinfordepo == it.pin) {
                int withdrawl_amount;
                cout << "Enter the amount you want to withdraw : ";
                cin >> withdrawl_amount;
                if (it.balance - withdrawl_amount >= 0) {
                    it.balance -= withdrawl_amount;
                    cout << "Your Updated details : ";
                    display_details(it.account_number);
                    return true;
                } else {
                    cout << "Oooopssss!!!! Insufficient Balance";
                    return false;
                }
            } else {
                cout << "Invalid Pin. Try Again";
                return false;
            }
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.";
        return false;
    }
    return false;
}

bool balance_inquiry() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;
    bool acc_exists = false;
    for (auto it : accts) {
        if (it.account_number == accnum) {
            cout << "The balance in your account is : " << it.balance;
            return true;
        }
    }
    if (!acc_exists) {
        cout << "Account doesn't exist with the given Account Number.";
        return false;
    }
    return false;
}

bool close_account() {
    long long int accnum;
    cout << "Enter your account number : ";
    cin >> accnum;
    for (int i = 0; i < accts.size(); i++) {
        if (accts[i].account_number == accnum) {
            accts.erase(accts.begin() + i);
            cout << "Account closed successfully.";
            return true;
        }
    }
    cout << "Account doesn't exist with the given Account Number.";
    return false;
}

bool view_account_details() {
    for (auto it : accts) {
        display_details(it.account_number);
    }
    return true;
}

void admin_menu() {
    int option;
    system(CLEAR);
    cout << "\t\t|-----------------------------------------------|\n";
    cout << "\t\t|   Choose your option:                         |\n";
    cout << "\t\t|-----------------------------------------------|\n";
    cout << "\t\t|     1) View Total Number of Accounts          |\n";
    cout << "\t\t|     2) View Account Details                   |\n";
    cout << "\t\t|     3) Exit                                   |\n";
    cin >> option;
    switch (option) {
    case 1:
        cout << "Total Savings Accounts: " << total_saving_accounts << "\n";
        cout << "Total Current Accounts: " << total_current_accounts << "\n";
        break;
    case 2:
        view_account_details();
        break;
    case 3:
        exit(0);
    }
}

void welcome() {
    system(CLEAR);
    cout << "\t\t|-----------------------------------------------|\n";
    cout << "\t\t|     Welcome to Our Bank                       |\n";
    cout << "\t\t|-----------------------------------------------|\n";
    cout << "\t\t|     Press enter to continue...                |\n";
    cin.get();  // Wait for the user to press "Enter"
}

int main() {
    int choice;
    welcome();
    while (true) {
        system(CLEAR);
        cout << "\t\t|-----------------------------------------------|\n";
        cout << "\t\t|   Choose your option:                         |\n";
        cout << "\t\t|-----------------------------------------------|\n";
        cout << "\t\t|     1) Create Account                         |\n";
        cout << "\t\t|     2) Deposit                                |\n";
        cout << "\t\t|     3) Withdraw                               |\n";
        cout << "\t\t|     4) Balance Inquiry                        |\n";
        cout << "\t\t|     5) Close Account                          |\n";
        cout << "\t\t|     6) Change PIN                             |\n";
        cout << "\t\t|     7) Admin Menu                             |\n";
        cout << "\t\t|     8) Exit                                   |\n";
        cin >> choice;

        switch (choice) {
        case 1:
            create_account(accts);
            break;
        case 2:
            deposit_into_account();
            break;
        case 3:
            withdraw_from_account();
            break;
        case 4:
            balance_inquiry();
            break;
        case 5:
            close_account();
            break;
        case 6:
            change_pin();
            break;
        case 7:
            admin_menu();
            break;
        case 8:
            exit(0);
        default:
            cout << "Invalid choice! Please try again.";
        }
    }
    return 0;
}
