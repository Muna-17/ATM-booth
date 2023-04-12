#include <iostream>
#include<fstream>
#include <string>
using namespace std;
float balance=10000;
ofstream outfile;
ifstream infile;
class ATMBooth
{
protected:

    char selectB;
    float withdraw,deposit;

public:

    void checkBalance()
    {
        do
        {

            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tYour Current Account Balance: "<<balance<<endl;
            cout<<"\tDo you Want to Check Balance Again(y/n)?";
            cin>>selectB;
            outfile << "Balance is  :"<< balance << endl;
        }
        while(selectB=='y'||selectB=='Y');
        outfile.close();
    }
    void withdrawMoney()
    {
        do
        {
            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tEnter Amount to Withdraw Money: ";
            cin>>withdraw;
            if (balance>withdraw)
            {
                balance=balance-withdraw;
                cout<<"\tYour Current Balance after Withdraw is: "<<balance<<endl;
                outfile << "After withdraw balance is  :"<< balance << endl;
            }
            else
            {
                cout<<"\tNot Sufficient Balance. Your Current Balance: "<<balance<<endl;
            }
            cout<<"\tDo you Want to Withdraw Money Again(y/n)?";
            cin>>selectB;

        }
        while(selectB=='y'||selectB=='Y');
        outfile.close();

    }
    void depositMoney()
    {
        do
        {
            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tEnter Amount to Deposit Money: ";
            cin>>deposit;
            balance=balance+deposit;
            cout<<"\tYour Current Balance after Deposit Money: "<<balance<<endl;
            outfile << "After deposit balance is  :"<< balance << endl;

            cout<<"\tDo you Want to Deposit Money Again(y/n)?";
            cin>>selectB;

        }
        while(selectB=='y'||selectB=='Y');
        outfile.close();

    }
};
class Loan : public ATMBooth
{
protected:
    float l;
    char loan_try;
public:
    void loan()
    {
        do
        {
            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tEnter the Amount of Loan you Want: ";
            cin>>l;
            if (l<balance)
            {
                cout<<"\tYour Demanding Loan of "<<l<<"/= is Successful"<<endl;

                balance = balance+l;
                cout<<"\tYour Current Balance after Deposit Money: "<<balance<<endl;

                outfile <<"Your loan money is :"<< l <<endl;
            }
            else
            {
                cout<<"\tSorry, Your Demanding Loan cannot be Processed."<<endl;
            }
            cout<<"\tDo you want to try for Loan again?(y/n) ";
            cin>>loan_try;
        }
        while(loan_try=='y'||loan_try=='Y');
        outfile.close();
    }
    void callBaseL()
    {
        ATMBooth :: checkBalance();
        ATMBooth :: withdrawMoney();
        ATMBooth :: depositMoney();
    }
};
class Bill : public ATMBooth
{
protected:
    float bill;
    char bill_try;
public:
    void payBill()
    {
        do
        {
            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tEnter amount of bill: ";
            cin>>bill;
            if (bill<balance)
            {
                balance=balance-bill;
                cout<<"\tBill is Successfully Deposited. Your Current Balance is: "<<balance<<endl;
                outfile << "After paying bill balance is  :"<< balance << endl;
            }
            else
            {
                cout<<"\tNot Sufficient Balance"<<endl;
            }
            cout<<"\tDo you want to pay bill again?(y/n) ";
            cin>>bill_try;
        }
        while(bill_try=='y'||bill_try=='Y');
        outfile.close();

    }
    void callBaseB()
    {
        ATMBooth :: checkBalance();
        ATMBooth :: withdrawMoney();
        ATMBooth :: depositMoney();
    }
};
class Transfer : public ATMBooth
{
protected:
    float trans_money;
    string number,account,password;
    char trans_try;
public:
    void moneyTransfer()
    {

        do
        {
            outfile.open("file.txt",ios::out|ios::in|ios::app);
            cout<<"\tEnter Account No. of Transaction :";
            cin>>number;
            cout<<"\tEnter Transaction Money: ";
            cin>>trans_money;


            ifstream file("account.txt");
            while(file >> account >> password)
            {

                if (number!=account)
                {
                    cout<<"\n\t";
                }

                else
                {
                    if(trans_money<balance)
                    {
                        balance=balance-trans_money;
                        cout<<"\n\tTransaction successful.";
                        cout<<"\n\t"<<trans_money<<" is transfered to the Account No: "<<number;
                        cout<<"\n\tYour current Balance is: "<<balance<<endl;
                        outfile<<"\n";
                        outfile<<"Your transacting Account No. is :"<<number<<endl;
                        outfile <<"After Transaction your Balance is :"<< balance <<endl;
                    }
                    else
                    {
                        cout<<"\n\tNot Sufficient Balance "<<endl;
                    }
                }
            }
            cout<<"\n\tDo you want to transfer money again?(y/n) ";
            cin>>trans_try;
        }
        while(trans_try=='y'||trans_try=='Y');
        outfile.close();
        //infile.open("file.txt");
        //infile>>number;
        // cout<< number<<endl;
        outfile.open("file.txt",ios::out|ios::in|ios::app);
        outfile<<trans_money<<" is transfered to the account no."<<number<<endl;
        infile.close();
        outfile.close();
    }
    void callBaset()
    {
        ATMBooth :: checkBalance();
        ATMBooth :: withdrawMoney();
        ATMBooth :: depositMoney();
    }
} ;

class LOAN_BILL : public Loan, public Bill
{
public:
    void loan_bill()
    {
        Loan :: callBaseL();
        Loan :: loan();
        Bill :: payBill();
    }
};

class ALL : public LOAN_BILL, public Transfer
{
public:
    void all()
    {
        LOAN_BILL :: loan_bill();
        Transfer :: moneyTransfer();
    }
};

int main()
{
    ATMBooth obj1;
    Loan objL;
    Bill objB;
    Transfer objT;
    LOAN_BILL objLB;
    ALL obja;
    string a,p, account, password;
    int option;
    char choice;
    float balance;
    cout<<"                                                         WELCOME                 "<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;


    while(1)
    {
        cout<<"Please enter account number : ";
        cin>>a;
        cout<<"Please enter password       : ";
        cin>>p;

        ifstream file("account.txt");
        while(file >> account >> password)

            if (a!=account || p!=password)
            {
                cout<<"\n";
            }
            else
            {
                while(1)

                {
                    cout<<"\n\tPlease, Select ATM Transactions"<<endl;
                    cout<<"\n\t[1] Balance"<<endl;
                    cout<<"\t[2] Withdraw"<<endl;
                    cout<<"\t[3] Deposit"<<endl;
                    cout<<"\t[4] Loan"<<endl;
                    cout<<"\t[5] Pay Bill"<<endl;
                    cout<<"\t[6] Transfer Money"<<endl;
                    cout<<"\t[7] Exit"<<endl;
                    cout<<"\n\tEnter option: ";
                    cin>>option;
                    do
                    {
                        if(option>7)
                        {
                            cout<<"\n\tInvalid. \n";
                            cout<<" \tDo you want to back to the main menu?(y/n):";
                            cin>>choice;
                            if(choice=='y'||choice=='Y')
                            {
                                cout<<"\n\tPlease, Select ATM Transactions"<<endl;
                                cout<<"\n\t[1] Balance"<<endl;
                                cout<<"\t[2] Withdraw"<<endl;
                                cout<<"\t[3] Deposit"<<endl;
                                cout<<"\t[4] Loan"<<endl;
                                cout<<"\t[5] Pay Bill"<<endl;
                                cout<<"\t[6] Transfer Money"<<endl;
                                cout<<"\t[7] Exit"<<endl;
                                cout<<"\n\tEnter option: ";
                                cin>>option;
                                switch(option)
                                {
                                case 1:
                                    obj1.checkBalance();
                                    continue;
                                case 2:
                                    obj1.withdrawMoney();
                                    break;
                                case 3:
                                    obj1.depositMoney();
                                    continue;
                                case 4:
                                    objL.loan();

                                    break;
                                case 5:
                                    objB.payBill();
                                    break;
                                case 6:
                                    objT.moneyTransfer();
                                    break;
                                case 7:
                                    cout<<"\n\n\tExiting.........."<<endl<<endl;
                                    return 0;
                                default:
                                    cout<<"\n\tInvalid. \n";
                                }
                            }

                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            switch(option)
                            {
                            case 1:
                                obj1.checkBalance();
                                continue;
                            case 2:
                                obj1.withdrawMoney();
                                break;
                            case 3:
                                obj1.depositMoney();
                                continue;
                            case 4:
                                objL.loan();

                                break;
                            case 5:
                                objB.payBill();
                                break;
                            case 6:
                                objT.moneyTransfer();
                                break;
                            case 7:
                                cout<<"\n\n\tExiting.........."<<endl<<endl;
                                return 0;
                            default:
                                cout<<"\n\tInvalid. \n";
                            }
                        }
                    }
                    while (option > 7);
                }
            }
    }
    return 0;
}
