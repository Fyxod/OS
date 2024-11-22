#include <iostream>
using namespace std;
struct BankAccount
{
    int balance;
};
bool mutexLock = true;
void deposit(BankAccount &account, int amount)
{
    cout << "Deposit thread: Waiting to acquire lock...\n";
    while (!mutexLock)
    {
        
    }
    mutexLock = false;
    cout << "Deposit thread: Lock acquired.\n";
    account.balance += amount;
    cout << "Deposit thread: Deposited " << amount << ". New balance: " << account.balance << endl;
    mutexLock = true;
    cout << "Deposit thread: Lock released.\n";
}
void withdraw(BankAccount &account, int amount)
{
    cout << "Withdraw thread: Waiting to acquire lock...\n";
    while (!mutexLock)
    {
        
    }
    mutexLock = false;
    cout << "Withdraw thread: Lock acquired.\n";
    if (account.balance >= amount)
    {
        account.balance -= amount;
        cout << "Withdraw thread: Withdrawn " << amount << ". New balance: " << account.balance << endl;
    }
    else
    {
        cout << "Withdraw thread: Insufficient funds. Current balance: " << account.balance << endl;
    }
    mutexLock = true;
    cout << "Withdraw thread: Lock released.\n";
}

int main()
{
    BankAccount account = {1000};
    cout << "Main thread: Starting simulated threads...\n";
    deposit(account, 500);
    withdraw(account, 700);
    withdraw(account, 1000);
    cout << "Main thread: Final account balance is " << account.balance << endl;
    return 0;
}