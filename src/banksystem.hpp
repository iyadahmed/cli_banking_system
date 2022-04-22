#ifndef BANKSYSTEM_HPP
#define BANKSYSTEM_HPP

#include <string>
#include <iostream>
#include <unordered_map>

#include "account.hpp"

using namespace std;

class BankSystem
{
public:
    void open_account()
    {
        string name;
        int initial_deposit;
        cout << "Enter new account name" << endl;
        cin >> name;
        cout << "Enter initial deposit in piasters" << endl;
        cin >> initial_deposit;

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

    void deposit()
    {
        string name;
        int amount;
        cout << "Enter account name" << endl;
        cin >> name;
        cout << "Enter deposit amount" << endl;
        cin >> amount;

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

    void withdraw()
    {
        string name;
        int amount;
        cout << "Enter account name" << endl;
        cin >> name;
        cout << "Enter withdraw amount" << endl;
        cin >> amount;

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

    void wire_transfer()
    {
        string source_account_name;
        string target_account_name;
        int amount;

        cout << "Enter source account name" << endl;
        cin >> source_account_name;
        cout << "Enter target account name" << endl;
        cin >> target_account_name;
        cout << "Enter amount" << endl;
        cin >> amount;

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

    void print_balance()
    {
        string name;
        cout << "Enter account name" << endl;
        cin >> name;

        auto account = find_account(name);
        if (account != nullptr)
        {
            cout << "Balance: " << account->compute_balance() << " Piasters" << endl;
        }
    }

    void print_history()
    {
        string name;
        cout << "Enter account name" << endl;
        cin >> name;

        auto account = find_account(name);
        if (account != nullptr)
        {
            account->print_history();
        }
    }

private:
    std::unordered_map<std::string, Account> accounts;
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
};

#endif // BANKSYSTEM_HPP