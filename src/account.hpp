#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <vector>
#include <chrono>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

static string get_current_time_string()
{
    // https://stackoverflow.com/a/27856440/8094047
    auto time = chrono::system_clock::now();
    auto timet = chrono::system_clock::to_time_t(time);
    return string(ctime(&timet));
}

struct Transaction
{
    int amount;
    string time_str;
};

class Account
{
private:
    vector<Transaction> transactions;

public:
    Account() = default; // Keep default constructors, otherwise unordered map will complain
    Account(int initial_deposit)
    {
        add_transaction(initial_deposit);
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
        transactions.push_back({amount, get_current_time_string()});
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

#endif // ACCOUNT_HPP