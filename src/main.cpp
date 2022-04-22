#include <iostream>
#include <string>

#include "banksystem.hpp"

using namespace std;

int main()
{
    BankSystem bank_system;
    int cmd;
    while (true)
    {
        cout << "Select command: \n"
                "1) Open Account\n"
                "2) Print Balance\n"
                "3) Print History\n"
                "4) Deposit\n"
                "5) Withdraw\n"
                "6) Transfer\n"
                "7) Exit\n";
        cin >> cmd;

        if (cmd == 1)
        {
            bank_system.open_account();
        }
        else if (cmd == 2)
        {
            bank_system.print_balance();
        }
        else if (cmd == 3)
        {
            bank_system.print_history();
        }
        else if (cmd == 4)
        {
            bank_system.deposit();
        }
        else if (cmd == 5)
        {
            bank_system.withdraw();
        }
        else if (cmd == 6)
        {
            bank_system.wire_transfer();
        }
        else if (cmd == 7)
        {
            break;
        }
    }
    return 0;
}