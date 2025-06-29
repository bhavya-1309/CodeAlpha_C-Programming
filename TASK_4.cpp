#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    double balanceAfterTransaction;
    string date;

    Transaction(string t, double amt, double balance, string d)
        : type(t), amount(amt), balanceAfterTransaction(balance), date(d) {}
};

class Account {
private:
    double balance;
    vector<Transaction> transactions;

public:
    string accountNumber;

    Account(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    void deposit(double amount) {
        balance += amount;
        string date = "2025-06-25";
        transactions.push_back(Transaction("Deposit", amount, balance, date));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        string date = "2025-06-25";
        transactions.push_back(Transaction("Withdraw", amount, balance, date));
        return true;
    }

    bool transfer(Account &toAccount, double amount) {
        if (amount > balance) {
            cout << "Insufficient funds.\n";
            return false;
        }
        withdraw(amount);
        toAccount.deposit(amount);
        string date = "2025-06-25";
        transactions.push_back(Transaction("Transfer Out", amount, balance, date));
        toAccount.transactions.push_back(Transaction("Transfer In", amount, toAccount.balance, date));
        return true;
    }

    void viewTransactions() {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        for (auto &transaction : transactions) {
            cout << transaction.date << " - " << transaction.type << " Amount: " << transaction.amount
                 << ", Balance After: " << transaction.balanceAfterTransaction << endl;
        }
    }

    double getBalance() {
        return balance;
    }
};

class Customer {
private:
    string name;
    string address;
    vector<Account> accounts;

public:
    string customerID;

    Customer(string id, string customerName, string customerAddress) {
        customerID = id;
        name = customerName;
        address = customerAddress;
    }

    void createAccount(string accountNumber, double initialBalance) {
        Account newAccount(accountNumber, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created successfully.\n";
    }

    Account* getAccountByNumber(string accountNumber) {
        for (auto &account : accounts) {
            if (account.accountNumber == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void viewAccountDetails(string accountNumber) {
        Account* account = getAccountByNumber(accountNumber);
        if (account) {
            cout << "Account Number: " << account->accountNumber << "\nBalance: " << account->getBalance() << endl;
            account->viewTransactions();
        } else {
            cout << "Account not found.\n";
        }
    }
};

int main() {
    Customer customer("C001", "John Doe", "123 Main St");

    customer.createAccount("A1001", 5000.00);
    customer.createAccount("A1002", 10000.00);

    Account* account1 = customer.getAccountByNumber("A1001");
    Account* account2 = customer.getAccountByNumber("A1002");

    if (account1) {
        account1->deposit(2000.00);
        account1->withdraw(1000.00);
    }

    if (account2) {
        account2->deposit(3000.00);
    }

    if (account1 && account2) {
        account1->transfer(*account2, 1500.00);
    }

    customer.viewAccountDetails("A1001");
    customer.viewAccountDetails("A1002");

    return 0;
}
