// info450savemore2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <cstdio>
#include <string.h>
using namespace std;

class SaveMore {

protected:
	char AccountNumber[50];
	double balance;
	char type[50];

public:
	SaveMore(char Anumber[50], double Abalance);
	virtual int deposit(double value);
	virtual void display();
	

};

SaveMore::SaveMore(char Anumber[50], double Abalance) {

	strcpy_s(AccountNumber, Anumber);

	balance = Abalance;
}

void SaveMore::display() {

	printf("Account Number is :%s\n", AccountNumber);

	printf("Balance Account :%.2f\n", balance);

	printf("Type Account :%s\n\n", type);
}

int SaveMore::deposit(double value) {
	balance = balance + value;
	return 0;
}

class savings : public SaveMore {

public:

	savings(char Anumber[50], double Abalance);

	int withdraw(double value);

	virtual void interest();
};

savings::savings(char Anumber[50], double Abalance) : SaveMore(Anumber, Abalance) {

	strcpy_s(AccountNumber, Anumber);

	balance = Abalance;

	strcpy_s(type, "Saving Account");
}

int savings::withdraw(double value) {

	if (balance - value - 2.0 < 0) {

		return -1;
	}
	else {
		balance = balance - value;

		return 0;
	}
}

void savings::interest() {

	if (balance <= 10000) {												//Balances under $10,000 earn 1% APR interest
		balance = balance + balance * 0.01;
	}
	else {																//Balances  >= $10,000 earn 2% APR
		balance = balance + balance * 0.02;
	}
}


class checking_account : public SaveMore {

public:
	checking_account(char Anumber[100], double Abalance);
	int withdraw(double value);
	virtual int order_checks();
};

checking_account::checking_account(char Anumber[100], double Abalance) : SaveMore(Anumber, Abalance) {

	strcpy_s(AccountNumber, Anumber);

	balance = Abalance;

	strcpy_s(type, "Checking Account");
}

int checking_account::withdraw(double value) {

	if (balance - value - 5.00 < 0) {

		return -1;
	}

	else {

		if (balance<500) {										//If the checking account balance drops below $500 a fee of 
			balance = balance - value - 5.00;				//$5.00 is deducted from the balance
		}

		else {
			balance = balance - value;
		}

		return 0;
	}

}

int checking_account::order_checks() {

	if (balance - 15 - 5.00 < 0) {							//Checking accounts have the capability to order checks for $15, deducted directly from the balance.

		return -1;
	}

	else {

		if (balance<500) {
			balance = balance - 15 - 5.00;
		}

		else {
			balance = balance - 15;
		}

		return 0;
	}
}


class certificate_deposit : public SaveMore {
private:
	int term;
public:
	certificate_deposit(char Anumber[100], double Abalance, int Adate);

	int earlyWithdraw(double value);

	virtual void interest();

	virtual void display();
};

certificate_deposit::certificate_deposit(char Anumber[100], double Abalance, int Aterm) : SaveMore(Anumber, Abalance) {

	strcpy_s(AccountNumber, Anumber);

	balance = Abalance;

	strcpy_s(type, "Certificate of Deposit");

	term = Aterm;

}


int certificate_deposit::earlyWithdraw(double value) {

	if (balance - value - balance*0.10 < 0) {								//earns 10% with a 5 year term and 5% for anything less
		return -1;
	}
	else {

		balance = balance - value - balance*0.10;
		return 0;
	}

}


void certificate_deposit::display() {

	printf("Account Number is :%s\n", AccountNumber);

	printf("Balance is :%.2f\n", balance);

	printf("Type of Account is :%s\n", type);

	printf("Term is :%d\n\n", term);
}

void certificate_deposit::interest() {
	if (term<5) {
		balance = balance + balance*0.10;
	}
	else {
		balance = balance + balance*0.05;
	}
}

int main()
{

	savings Account1("12345678", 10000);							//Create a new savings account  with a 10K opening balance
	checking_account Account2("987654321", 600);					//Create a new checking account with a 6K opening balance
	certificate_deposit Account3("24680246", 10000, 3);				//Create a new CD account  with a 3 year term and a 10K opening balance

	Account1.display();												//shows information about saving account
	Account2.display();												//shows information about checking account
	Account3.display();												//shows information about certificate of deposit

	Account1.interest();											//calculate monthly interest for the savings account
	Account3.interest();											//calculate  the monthly interest for the CD account 
	Account2.order_checks();										//order checks for the checking account (-$15)

	Account1.display();												//shows information about saving account
	Account2.display();												//shows information about checking account
	Account3.display();												//shows information about certificate of deposit

	Account2.withdraw(200);											//withdraw $200 from checking
	Account1.withdraw(1000);										//withdraw $1000 from Savings
	Account3.earlyWithdraw(2000);									//perform an early withdrawal of $2000 from the CD account


	Account1.display();												//shows information about saving account
	Account2.display();												//shows information about checking account
	Account3.display();												//shows information about certificate of deposit

	return 0;
}