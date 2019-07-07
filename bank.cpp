
#include<fstream>   //file handling
#include<stdio.h>     //standard i/o operations
#include<cstdlib>    //random() function
#include<conio.h>     //clrscr() function
#include<string.h>
#include<iostream>
#include<time.h>
using namespace std;

#define code 1234

//class used
class bank
{
 int acno;
 char name[20], email[40], addr[50]; 
 float prev_amt, change, final_amt;
 char trans_type;

 public:
 void input()
 {
  cout<<"Account number: "<<acno;
  cout<<"\nEnter name of the customer :";
  cin>>name;
  //gets(name);
  cout<<"Enter address of the customer: ";
  cin>>addr;
  //gets(addr);
  cout<<"Enter email of the customer: ";
  cin>>email;
  //gets(email);
  cout<<"Enter initial amount: ";
  cin>>final_amt;
  prev_amt=final_amt;
  trans_type='N';
 }

 void display()
 {  cout<<"\nAccount number: "<<acno;
    cout<<"\nName: "<<name;
    cout<<"\nAddress: "<<addr;
    cout<<"\nEmail: "<<email;
    cout<<"\nAmount: "<<final_amt;
 }

 void display_transaction(){
 	cout<<acno<<"\t"<<prev_amt<<"\t"<<change<<"\t"<<trans_type<<"\t"<<final_amt;
 	cout<<endl;
 }

 void set_acno()
 {   
 	//randomize();
 	srand(time(0));
    //acno=100+random(1001);
    acno=100+rand();
  }

 void deposit(float x){
 	change=x;
 	prev_amt=final_amt;
 	final_amt=prev_amt+x; 
 	trans_type='D';	
 }

 void withdraw(float x){
 	change=x;
 	prev_amt=final_amt;
 	final_amt=prev_amt-x;
 	trans_type='W';
 }

 int ret_acno()      //to return account no.
 { return acno; }

 float ret_amt()       //to return amount in account
 { return final_amt; }

 char* ret_name()
 { return name;}
};

//global declaration

fstream fil,file;
bank B;

//function to write in the file

void create_acc()
{
fil.open("master.dat",ios::out|ios::app|ios::binary);
B.set_acno();
B.input();
fil.write((char*)&B,sizeof B);
fil.close();
}

//function to modify a record

void modify()
{
int search;
char flag='n';
cout<<"Enter account no. you want to modify: ";
cin>>search;
fil.open("master.dat",ios::out|ios::in|ios::ate|ios::binary);
fil.seekg(0);
while(fil.read((char*)&B,sizeof B))
{ if(B.ret_acno()==search)
	{
	 int pos=(-1)*static_cast<int>(sizeof(B));
	 fil.seekp(pos,ios::cur);
	 //fil.seekp(fil.tellg()-sizeof(B),ios::beg);
	 B.input();
	 fil.write((char*)&B,sizeof B);
	 flag='y';
	 break;
	}
}
if(flag=='n')
cout<<"Account not found";
fil.close();
}

//function to deposit in an account

void DEPOSIT()
{
int search;
float dep;
cout<<"Enter account no.: ";
cin>>search;
cout<<"Enter the amount you want to deposit: ";
cin>>dep;
fil.open("master.dat",ios::out|ios::in|ios::ate|ios::binary);
fil.seekg(0);
file.open("transaction.dat",ios::out|ios::in|ios::app|ios::binary);
while(fil.read((char*)&B,sizeof B))
{ if(B.ret_acno()==search)
	{
	 B.deposit(dep);
	 break;
	}
	  //file.write((char*)&B, sizeof B);	
}
int pos=(-1)*static_cast<int>(sizeof(B));
fil.seekp(pos,ios::cur);
//fil.seekg(fil.tellg()- sizeof B,ios::beg);
fil.write((char*)&B,sizeof B);
file.write((char*)&B, sizeof B);
fil.close();
file.close();
}

//function to withdraw from an account
void WITHDRAW()
{
int search;
float dep;
cout<<"Enter account no.: ";
cin>>search;
cout<<"Enter the amount you want to withdraw: ";
cin>>dep;
fil.open("master.dat",ios::out|ios::in|ios::ate|ios::binary);
fil.seekg(0);
file.open("transaction.dat",ios::out|ios::in|ios::app|ios::binary);
while(fil.read((char*)&B,sizeof B))
{ if(B.ret_acno()==search)
	{
	 if(B.ret_amt()>dep)
	  {  B.withdraw(dep);
		  break;
	  }
	  //file.write((char*)&B, sizeof B);
	}
}
int pos=(-1)*static_cast<int>(sizeof(B));
fil.seekp(pos,ios::cur);
//fil.seekg(fil.tellg()-sizeof B,ios::beg);
fil.write((char*)&B,sizeof B);
file.write((char*)&B, sizeof B);
fil.close();
file.close();
}


void passbook(){
	int an;
	cout<<"Enter account number: ";
	cin>>an;
	fil.open("transaction.dat",ios::in|ios::binary);
	while(fil.read((char*)&B,sizeof B)){
		if(B.ret_acno()==an){
			B.display_transaction();
		}
	}
	fil.close();
}

//function to display details of all accounts
void output()
{
fil.open("master.dat",ios::in|ios::binary);
fil.seekg(0);
while(fil.read((char*)&B,sizeof B))
{ 
	 B.display();
	 cout<<endl;
}
fil.close();
}


//function to search for a record
void search_accno()
{
int find;
char flag='n';
cout<<"Enter the account number you want to search: ";       
cin>>find;
fil.open("master.dat",ios::in|ios::binary);
fil.seekg(0);
while(fil.read((char*)&B,sizeof B))
{
 if(B.ret_acno()==find)
 {
  B.display();
  flag='y';
  break;
 }
}
if(flag=='n')
cout<<"Account not found";
fil.close();
}


void search_name(){
	char search[25];
	int flag=0;
	cout<<"Enter the name you want to search: ";
	cin>>search;
	fil.open("master.dat",ios::in|ios::binary);
	while(fil.read((char*)&B, sizeof B)){
		if(strcmpi(B.ret_name(),search)==0){
			B.display();
			cout<<endl;
			flag=1;
		}
	}
	if(flag==0)
		cout<<"Matching record not found";
	fil.close();
}


void deleterecord(){
	int an;
	cout<<"Enter the account number of the account you want to delete: ";
	cin>>an;
	file.open("master.dat",ios::in);
	fil.open("temp.dat",ios::out);
	while(file.read((char*)&B, sizeof B)){
		if(B.ret_acno()!=an)
			fil.write((char*)&B, sizeof B);
		else{
			cout<<"Details of the account deleted:\n";
			B.display();
		}
	}
	file.close();
	fil.close();
	fil.open("temp.dat",ios::in|ios::binary);
	file.open("master.dat",ios::out|ios::binary);
	while(fil.read((char*)&B, sizeof B)){
		file.write((char*)&B, sizeof B);
	}
	fil.close();
	file.close();
}


//Main function

int main()
{
char pwd[20]="abcde";
char temp[20];
int a;
char ch,choice;
int CH,i;

do
{
	system("cls");	
	cout<<"Enter password: ";
	cin>>temp;
	//gets(temp);
	for(i=0; i<2; i++){
		if(strcmp(temp,pwd)==0){
			cout<<"Access granted";
		do
	 	{
	  	system("cls");
	  	cout<<"**********MENU************";
	 	
	  	cout<<"\n[A] Admin";
	  	cout<<"\n[T] Transaction";
	  	cout<<"\n[Q] Quit";

	  	cout<<"\nEnter your choice: ";
	  	cin>>ch;
	  	if(ch=='a'||ch=='A')
		{
		  cout<<"\n1.Add customer";
		  cout<<"\n2.Display customer";
		  cout<<"\n3.Search customer by account number";
		  cout<<"\n4.Search customer by name";		  
		  cout<<"\n5.Modify info";
		  cout<<"\n6.Close an account";		  
		  cout<<"\n\nEnter your choice";
		  cin>>CH;
		  switch(CH)
		  {
			case 1:create_acc();break;
			case 2:output();break;
			case 3:search_accno();break;
			case 4:search_name();break;
			case 5:modify();break;
			case 6:deleterecord();break;
			default :break;
		  };
		}

	  	else if(ch=='t'||ch=='T')
		{
		  cout<<"\n1.Withdraw";
		  cout<<"\n2.Deposit";
		  cout<<"\n3.Pass Book";
		  cout<<"\n\nEnter your choice: ";
		  cin>>CH;
		  switch(CH)
		  {
			case 1:WITHDRAW();break;
			case 2:DEPOSIT();break;
			case 3:passbook();break;
			default: break;
		  };
		}

	 	else break;
	 	cout<<"\n\nDo you want to continue(y/n)?: ";
	 	cin>>choice;
	 	system("cls");
		}
		while(choice=='y'||choice=='Y');
		
		break;        //not sure
		}

		else{
			cout<<"\nInvalid password. Try again.\n";
			cout<<"\nEnter password: ";
			cin>>temp;
			//gets(temp);
		}
	}
	if(i==2){
		cout<<"\n\nAccess Denied";
		cout<<"\nEnter security code to reset password: ";
		cin>>a;
		if(a==code){
			cout<<"Enter new password: ";
			cin>>temp;
			//gets(temp);
			strcpy(pwd,temp);
		}
		else
			cout<<"System locked";
	}
}
while(a==code&&(ch!='Q'&&ch!='q'));

//return 0;
}

