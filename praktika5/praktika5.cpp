#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

class BankAccount
{
	friend bool transfer(BankAccount& acc1, BankAccount& acc2, double transf);

private:
	int AccountNumber;
	double balance;
	double InterestRate;
	string Password;
public:
	void deposit(double deposit)
	{
		if (deposit > 0)
		{
			this->balance = this->balance + deposit;
			cout << endl << deposit << "Р успешно внесены на счет.\n";
			getBalance();
		}
		else
		{
			cout << "\nСумма взноса должна быть больше 0!\n";
		}
	}

	void withdraw(double withdraw)
	{
		if ((withdraw <= this->balance) && (withdraw > 0))
		{
			this->balance = this->balance - withdraw;
			cout << endl << withdraw << "Р успешно списаны с вашего счета.\n";
			getBalance();
		}
		else if (withdraw <= 0)
		{
			cout << "\nСумма снятия должна быть больше 0!\n";
		}
		else
		{
			cout << "\nНедостаточно средств!\n";
		}

	}

	void getBalance()
	{
		cout << "\nБаланс вашего счета: " << this->balance << "P\n";
	}

	double getInterest()
	{
		double procentes = (this->balance * this->InterestRate) / 12;
		
		return procentes;
	}

	void setInterestRate(double newInterestRate)
	{
		if ((newInterestRate >= 0) && (newInterestRate <= 100))
		{
			this->InterestRate = newInterestRate;
			cout << "\nПроцентная ставка обновлена.\n";
		}
		else if (newInterestRate < 0)
		{
			cout << "\nПроцентная ставка не может быть меньше 0%!\n";
		}
		else if (newInterestRate > 100)
		{
			cout << "\nПроцентная ставка не может быть больше 100%!\n";
		}
	}

	void getAccountNumber()
	{
		cout << "\nНомер вашего аккаунта: " << this->AccountNumber << endl;
	}

	void passwordCheck()
	{
		string passwordInput;

		while (passwordInput != Password)
		{
			cout << "\nВведите пароль: ";
			cin >> passwordInput;

			if (passwordInput != Password)
			{
				cout << "\nНеверный пароль!\n";
			}
			else
			{
				cout << "\n\nВы успешно вошли в " << AccountNumber << " аккаунт.\n\n";
			}
		}
	}

	void passwordChange()
	{
		string oldPassword;
		string newPassword;

		cout << "\nВведите старый пароль: ";
		cin >> oldPassword;

		if (oldPassword == this->Password)
		{
			cout << "\nВведите новый пароль: ";
			cin >> newPassword;
			if (oldPassword == newPassword)
			{
				cout << "\nНовый пароль не может совпадать со старым!\n";
			}
			else
			{
				this->Password = newPassword;
				cout << "\nПароль успешно сменен\n";
			}
		}
		else
		{
			cout << "\nПароли не совпадают!\n";
		}
	}
	
	BankAccount(int AccountNumber, double balance, string Password, double InterestRate = 0)
	{
		this->AccountNumber = AccountNumber;
		this->balance = balance;
		this->Password = Password;
		this->InterestRate = InterestRate;
	}
};

bool transfer(BankAccount& acc1, BankAccount& acc2, double transf)
{
	if ((transf <= acc1.balance) && (transf > 0))
	{
		acc1.balance = acc1.balance - transf;
		acc2.balance = acc2.balance + transf;

		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	
	BankAccount account1 = BankAccount(1,574.50,"12345");
	BankAccount account2 = BankAccount(2, 1250.10 ,"54321");
	vector<BankAccount> accounts;
	accounts.push_back(account1);
	accounts.push_back(account2);

	int counterAcc, oper;

	do
	{
		cout << "Выберите аккаунт:\n1. Аккаунт 1\n2. Аккаунт 2\n3. Выход из программы\n\n";
		cin >> counterAcc;

		if (counterAcc == 3)
		{
			cout << "\nВыход...";
		}
		else if ((counterAcc < 1) || (counterAcc > 3))
		{
			cout << "\nНеверное действие!\n\n";
		}
		else
		{
			accounts[(counterAcc - 1)].passwordCheck();
			do
			{
				cout << "\nВыберите действие:\n1. Положить деньги на счет\n2. Снять деньги со счета\n3. Посмотреть баланс счета\n4. Сумма процентов, заработанная на счете \n5. Обновить процентную ставку\n6. Посмотреть номер аккаунта\n7. Перевод денег\n8. Смена пароля\n9. Вернуться назад\n\n";
				cin >> oper;
				switch (oper)
				{
				case 1:
					double deposit;
					cout << "Введите сумму для вноса: ";
					cin >> deposit;
					accounts[(counterAcc - 1)].deposit(deposit);
					break;
				case 2:
					double withdraw; 
					cout << "Введите сумму для снятия: ";
					cin >> withdraw;
					accounts[(counterAcc - 1)].withdraw(withdraw);
					break;
				case 3:
					accounts[(counterAcc - 1)].getBalance();
					break;
				case 4:
					cout << "\nСумма процентов, заработанная на счете: " << accounts[(counterAcc - 1)].getInterest() << endl; 
					break;
				case 5:
					double newInterestRate;
					cout << "\nВведите новую процентную ставку: ";
					cin >> newInterestRate;
					accounts[(counterAcc - 1)].setInterestRate(newInterestRate);
					break;
				case 6:
					accounts[(counterAcc - 1)].getAccountNumber();
					break;
				case 7:
					int accNum;
					double transfSum;
					bool transfStatus;
					cout << "Выберите аккаунта для перевода: ";
					cin >> accNum;

					if ((accNum > 2) || (accNum < 1))
					{
						cout << "\nАккаунт не существует!\n";
						break;
					}
					else if (accNum == counterAcc)
					{
						cout << "\nНельзя перевести деньги на свой аккаунт!\n";
						break;
					}

					cout << "Введите сумму перевода: ";
					cin >> transfSum;
					
					if (transfer(accounts[(counterAcc - 1)], accounts[(accNum - 1)], transfSum) == false)
					{
						cout << "\nОшибка перевода!\n";
						break;
					}
					else
					{
						cout << "\nПеревод " << transfSum << "P на аккаунт " << accNum << " успешно выполнен.\n";
						accounts[(counterAcc - 1)].getBalance();
					}
					break;
				case 8:
					accounts[(counterAcc - 1)].passwordChange();
					break;
				case 9:
					break;
				default:
					cout << "\nНеверное действие!\n";
					break;
				}
			} while (oper != 9);
		}
	} while (counterAcc != 3);

	return 0;
}