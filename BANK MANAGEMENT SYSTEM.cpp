#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<WINDOWS.H>

using namespace std;

class ACCOUNT
{
 public:
	int account_number;
	char name[50];
	int DEPOSIT_AMOUNTs;
	char type_of_account;
public:
	void CREATE_ACCOUNT();
	void DISPLAY_ACCOUNT() const;
	void MODIFY_ACCOUNT();
	void DEPOSIT_AMOUNT(int);
	void WITHDRAW_AMOUNT(int);
	void ACCOUNT_REPORT() const;
	int DISPLAY_ACCOUNT_NUMBER() const;
	int DISPLAY_ACCOUNT_BALANCE() const;
	char DISPLAY_ACCOUNT_TYPE() const;
};
void ACCOUNT::CREATE_ACCOUNT()
{
	cout<<"\nEnter The ACCOUNT NUMBER. :";
	cin>>account_number;
	cout<<"\n\nEnter The Name of The ACCOUNT Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type_of_account  (Current/Savings) : ";
	cin>>type_of_account;
	type_of_account=toupper(type_of_account);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>DEPOSIT_AMOUNTs;
	cout<<"\n\n\nACCOUNT Created..";
}

void ACCOUNT::DISPLAY_ACCOUNT()const
{
	cout<<"\nACCOUNT Number. : "<<account_number;
	cout<<"\nACCOUNT Holder Name : ";
	cout<<name;
	cout<<"\nType_of_account of ACCOUNT : "<<type_of_account;
	cout<<"\nBalance amount : "<<DEPOSIT_AMOUNTs;
}


void ACCOUNT::MODIFY_ACCOUNT()
{
	cout<<"\nACCOUNT No. : "<<account_number;
	cout<<"\nMODIFY_ACCOUNT_ACCOUNT ACCOUNT Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nMODIFY_ACCOUNT_ACCOUNT Type_of_account of ACCOUNT : ";
	cin>>type_of_account;
	type_of_account=toupper(type_of_account);
	cout<<"\nMODIFY_ACCOUNT_ACCOUNT Balance amount : ";
	cin>>DEPOSIT_AMOUNTs;
}


void ACCOUNT::DEPOSIT_AMOUNT(int x)
{
	DEPOSIT_AMOUNTs+=x;
}

void ACCOUNT::WITHDRAW_AMOUNT(int x)
{
	DEPOSIT_AMOUNTs-=x;
}

void ACCOUNT::ACCOUNT_REPORT() const
{
	cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<" "<<type_of_account<<setw(6)<<DEPOSIT_AMOUNTs<<endl;
}


int ACCOUNT::DISPLAY_ACCOUNT_NUMBER() const
{
	return account_number;
}

int ACCOUNT::DISPLAY_ACCOUNT_BALANCE() const
{
	return DEPOSIT_AMOUNTs;
}

char ACCOUNT::DISPLAY_ACCOUNT_TYPE() const
{
	return type_of_account;
}

void write_ACCOUNT()
{
	ACCOUNT ac;
	ofstream outFile;
	outFile.open("ACCOUNT.dat",ios::binary|ios::app);
	ac.CREATE_ACCOUNT();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
	outFile.close();
}
void display_sp(int n)
{
	ACCOUNT ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("ACCOUNT.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT)))
	{
		if(ac.DISPLAY_ACCOUNT_NUMBER()==n)
		{
			ac.DISPLAY_ACCOUNT();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nACCOUNT number does not exist";
}

void MODIFY_ACCOUNT(int n)
{
	bool found=false;
	ACCOUNT ac;
	fstream File;
	File.open("ACCOUNT.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
		if(ac.DISPLAY_ACCOUNT_NUMBER()==n)
		{
			ac.DISPLAY_ACCOUNT();
			cout<<"\n\nEnter The New Details of ACCOUNT"<<endl;
			ac.MODIFY_ACCOUNT();
			int pos=(-1)*static_cast<int>(sizeof(ACCOUNT));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void delete_ACCOUNT(int n)
{
	ACCOUNT ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("ACCOUNT.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT)))
	{
		if(ac.DISPLAY_ACCOUNT_NUMBER()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
		}
	}
	inFile.close();
	outFile.close();
	remove("ACCOUNT.dat");
	rename("Temp.dat","ACCOUNT.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	ACCOUNT ac;
	ifstream inFile;
	inFile.open("ACCOUNT.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"****************************************************\n";
	cout<<"A/c no.      NAME           Type_of_account  Balance\n";
	cout<<"****************************************************\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT)))
	{
		ac.ACCOUNT_REPORT();
	}
	inFile.close();
}

void DEPOSIT_AMOUNT(int n, int option)
{
	int amt;
	bool found=false;
	ACCOUNT ac;
	fstream File;
	File.open("ACCOUNT.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
		if(ac.DISPLAY_ACCOUNT_NUMBER()==n)
		{
			ac.DISPLAY_ACCOUNT();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT_AMOUNTOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be DEPOSIT";
				cin>>amt;
				ac.DEPOSIT_AMOUNT(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHWITHDRAW_AMOUNT AMOUNT ";
				cout<<"\n\nEnter The amount to be withWITHDRAW_AMOUNT";
				cin>>amt;
				int bal=ac.DISPLAY_ACCOUNT_BALANCE()-amt;
				if((bal<500 && ac.DISPLAY_ACCOUNT_TYPE()=='S') || (bal<1000 && ac.DISPLAY_ACCOUNT_TYPE()=='C'))
					cout<<"Insufficience balance";
				else
					ac.WITHDRAW_AMOUNT(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(ACCOUNT));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void intro()
{
HANDLE hConsole;
 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 {
	SetConsoleTextAttribute(hConsole, 14);

printf(" \n\t \t \t \t \t \t$$$$$$$$$$$$$$$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$$$  $$$$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$$    $$$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$      $$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$        $$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$          $$$$$");
printf(" \n\t \t \t \t \t \t$$$$    BANK    $$$$");
printf(" \n\t \t \t \t \t \t$$$              $$$");
printf(" \n\t \t \t \t \t \t$$                $$");
printf(" \n\t \t \t \t \t \t$    MANAGEMENT    $");
printf(" \n\t \t \t \t \t \t$$                $$");
printf(" \n\t \t \t \t \t \t$$$              $$$");
printf(" \n\t \t \t \t \t \t$$$$   SYSTEM   $$$$");
printf(" \n\t \t \t \t \t \t$$$$$          $$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$        $$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$      $$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$$    $$$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$$$ $$$$$$$$$$");
printf(" \n\t \t \t \t \t \t$$$$$$$$$$$$$$$$$$$$");
}
	cout<<"\n\n\n\nMADE BY : HUSSAIN GHAZALI";
	cout<<"\n\n(17K-3900)  SECTION A";
	cin.get();
}

int main()
{
 HANDLE hConsole;
 hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 {
	SetConsoleTextAttribute(hConsole, 15);
	char ch;
	int num=0;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT_AMOUNT";
		cout<<"\n\n\t03. WITHDRAW_AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_ACCOUNT();
			break;
		case '2':
			cout<<"\n\n\tEnter The ACCOUNT No. : "; cin>>num;
			DEPOSIT_AMOUNT(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The ACCOUNT No. : "; cin>>num;
			DEPOSIT_AMOUNT(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The ACCOUNT No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The ACCOUNT No. : "; cin>>num;
			delete_ACCOUNT(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The ACCOUNT No. : "; cin>>num;
			MODIFY_ACCOUNT(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
} }

