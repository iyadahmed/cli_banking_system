#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

struct Transaction
{
    int amount;
    char *time_str;
};

class Account
{
private:
    std::vector<Transaction> transactions;

public:
    Account() = default;
    Account(int initial_deposit)
    {
        // Getting current time https://stackoverflow.com/a/27856440/8094047
        auto time = chrono::system_clock::now();
        auto timet = std::chrono::system_clock::to_time_t(time);
        transactions.push_back({initial_deposit, ctime(&timet)});
    }
    int compute_balance()
    {
        int balance = 0;
        for (auto t : transactions)
        {
            balance += t.amount;
        }
        return balance;
    }

    /* Amount can be negative, returns true on success, false on failure */
    bool add_transaction(int amount)
    {
        if ((amount + compute_balance()) < 0)
        {
            cout << "Insufficient balance" << endl;
            return false;
        }
        auto time = chrono::system_clock::now();
        auto timet = std::chrono::system_clock::to_time_t(time);
        transactions.push_back({amount, ctime(&timet)});
        return true;
    }

    void print_history()
    {
        for (auto t : transactions)
        {
            cout << "Amount: " << t.amount << " Piasters"
                 << ", Time: " << t.time_str << endl;
        }
    }
};

class BankSystem
{
public:
    void open_account(string name, int initial_deposit)
    {
        auto account = accounts.find(name);
        if (account == accounts.end())
        {
            accounts[name] = Account(initial_deposit);
        }
        else
        {
            cout << "ERROR: account \"" << name << "\" already exists" << endl;
        }
    }

    Account *find_account(string name)
    {
        auto account = accounts.find(name);
        if (account == accounts.end())
        {
            cout << "ERROR: Account \"" << name << "\" not found" << endl;
            return nullptr;
        }
        return &account->second;
    }

    void deposit(string name, int amount)
    {
        if (amount < 0)
        {
            cout << "Cannot deposit negative amount" << endl;
            return;
        }
        auto account = find_account(name);
        if (account != nullptr)
        {
            account->add_transaction(amount);
        }
    }

    void withdraw(string name, int amount)
    {
        if (amount < 0)
        {
            cout << "Cannot withdraw negative amount" << endl;
            return;
        }
        auto account = find_account(name);
        if (account != nullptr)
        {
            account->add_transaction(-amount);
        }
    }

    void wire_transfer(string source_account_name, string target_account_name,
                       int amount)
    {
        if (amount < 0)
        {
            cout << "Cannot wire transfer a negative amount" << endl;
            return;
        }
        auto source_account = find_account(source_account_name);
        auto target_account = find_account(target_account_name);
        if (source_account == nullptr || target_account == nullptr)
        {
            return;
        }
        if (source_account->add_transaction(-amount))
        {
            target_account->add_transaction(amount);
        }
    }

    void print_balance(string name)
    {
        auto account = find_account(name);
        if (account != nullptr)
        {
            cout << "Balance: " << account->compute_balance() << " Piasters" << endl;
        }
    }

    void print_history(string name)
    {
        auto account = find_account(name);
        if (account != nullptr)
        {
            account->print_history();
        }
    }

private:
    std::unordered_map<std::string, Account> accounts;
};

int main()
{
    BankSystem bank_system;
    bool exit = false;
    int cmd;
    while (true)
    {
        cout << "Select command: \n"
                "1) Open Account\n"
                "2) Print Balance\n"
                "3) Print History\n"
                "4) Withdraw\n"
                "5) Transfer\n"
                "6) Exit\n";
        cin >> cmd;

        string account_name;
        cout << "Enter account name" << endl;
        cin >> account_name;

        if (cmd == 1)
        {
            int initial_deposit;
            cout << "Enter initial deposit in piasters" << endl;
            cin >> initial_deposit;
            bank_system.open_account(account_name, initial_deposit);
        }
        else if (cmd == 2)
        {
            bank_system.print_balance(account_name);
        }
        else if (cmd == 3)
        {
            bank_system.print_history(account_name);
        }
        else if (cmd == 4)
        {
            int amount;
            cout << "Enter amount to withdraw" << endl;
            cin >> amount;
            bank_system.withdraw(account_name, amount);
        }
        else if (cmd == 5)
        {
            string target_account_name;
            cout << "Enter target account name" << endl;
            cin >> target_account_name;
            int amount;
            cout << "Enter amount to transfer" << endl;
            cin >> amount;
            bank_system.wire_transfer(account_name, target_account_name, amount);
        }
        else if (cmd == 6)
        {
            exit = true;
        }
    }
    return 0;
}