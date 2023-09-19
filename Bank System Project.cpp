#include <iostream>
#include <fstream> //file manipulation
#include <cstring> // to use string operations
#include <cstdlib> //needed for exit()
#include <chrono>  //needed to find system time
#include <cmath> 
#include<iomanip> 
using namespace std;
struct new_acc
{
  char first_name[20], last_name[15],account_no[20],id[15];
  float deposit; 
} acc;
char choice,new_acc_no[20],new_id[5];
float amount;
double initial_deposit(){
  a:
  cout << "Enter the amount of money you want to deposit: ";
  int min = 25;    //threshold money
  cin >> acc.deposit;
  if (acc.deposit < min)
  {
    cout << "You can't deposit below minimum amount.\nTry again.\n";
    goto a;
  }
  else
    return acc.deposit;
}
void open_create_file(ofstream &ofile) // to avoid repeatedly writing multiple lines of code.
{
  ofile.open("projectFile.txt", ios::app); 
  if (ofile.fail())
  {
    cout << "Error: File couldn't be opened. "  << endl;
    exit(1);
  }
}
void createAccount(ofstream &user_file)
{
  open_create_file(user_file);
  do
  { cout << "Enter the first name: ";
     cin.ignore();
    cin.getline(acc.first_name,30);
     cout << "Enter last name: ";
     cin >> acc.last_name;
    cout << "Enter the account number: "; 
    cin>>acc.account_no;
    cout << "Enter the ID: ";
    cin >> acc.id;
    user_file << acc.account_no  <<"   " << acc.first_name <<"   " << acc.last_name << "   " 
    <<acc.id<<"   " << initial_deposit()<< endl;
    cout << "Your account has been created successfully! Thank you!\n";
    cout << "Do you want to create another account?\n Enter '1' for yes and any other key for no.\n";
    cin >> choice;
  } while (choice == '1');
  user_file.close();
}
void open_file1(ifstream &projectFile, ofstream &temp) {
  temp.open("temp.txt",ios::out); //temporary file for writing and projectFile for reading.
  if (temp.fail())                      
  {
    cout << "Error: Failed to open the file." << endl;
    exit(1);
  }
  projectFile.open("projectFile.txt", ios::in);
  if (projectFile.fail())
  {
    cout << "Error: Failed to open the file. " << endl;
    exit(1);
  }
}
void open_file2(ifstream &temp, ofstream &projectFile) 
{
  projectFile.open("projectFile.txt",ios::out);  //projectFile for writing and temp for reading function
  if (projectFile.fail()) 
  {
    cout << "Error: Failed to open the file " << endl;
    exit(1);
  }
  temp.open("temp.txt", ios::in);
  if (temp.fail()){
    cout << "Error: Failed to open the file " << endl;
    exit(1);
  }
  }
void deposit_withdraw(ifstream &ifile, ofstream &ofile){
  open_file1(ifile, ofile);
  cout << "Enter your account number\n";
  cin >> new_acc_no;
  while (ifile >> acc.account_no >> acc.first_name>> acc.last_name >> acc.id >> acc.deposit) {
    if (strncmp(acc.account_no, new_acc_no, strlen(new_acc_no)) == 0) {
    d:
      cout << "Enter '1' to deposit or '2' to Withdraw: \n";
      cin >> choice;
      if (choice == '1'){
        cout << "Enter the amount of money you want to deposit\n";
        cin >> amount;
        acc.deposit += amount;
        cout<< "Deposit is done successfully\n";
      }
      else if (choice == '2'){
        z:
        cout<<"Enter the ID of your account: ";
        cin>>new_id;
         if (strncmp(acc.id, new_id, strlen(new_id)) == 0){
        c:
        cout << "Enter the amount of money you want to withdraw\n";
        cin >> amount;
        if (amount > acc.deposit){
          cout << "Insufficient balance to withdraw. Try again.\n";
          goto c;
        }
        else
        {
          acc.deposit -= amount;
          cout<<"Withdrawal is done successfully!\n";
        }
      }
      else{
      cout << "The ID is not correct. Try again.\n";
      goto z;
      }
       }
      else{
        cout << "Invalid input. Try again.\n";
        goto d; 
        }
    }
    ofile << acc.account_no <<"  "<< acc.first_name << "  " << acc.last_name << "  " << acc.id << "  " << acc.deposit << endl;
  }
  ifile.close();
  ofile.close();
  // to copy the files from temp.txt to project.txt
  open_file2(ifile,ofile); //reverse projectFile and temp file.
  while (ifile >> acc.account_no >>acc.first_name  >> acc.last_name >> acc.id >> acc.deposit) {
    ofile << acc.account_no << "  " << acc.first_name << "  " <<acc.last_name << "  "<< acc.id
     << "  "<< acc.deposit << endl;
  }
  ifile.close();
  ofile.close();
  remove("temp.txt"); // unnecessary to store temp file anymore.
}
void interest_calculator(ifstream &ifile, ofstream &ofile)
{
  auto start = chrono::system_clock::now();
  cout << "Enter account number\n";
  cin >> new_acc_no;
  open_file1(ifile,ofile); 
  double interest, rate = 0.07, time; // we assume the CBE's interest rate amount. We can also enter manually.
  while (ifile >> acc.account_no >>acc.first_name >> acc.last_name >> acc.id >> acc.deposit){
    if (strncmp(acc.account_no, new_acc_no, strlen(new_acc_no)) == 0){
      auto end = chrono::system_clock::now();
      auto duration = end - start;
      time = (double)(1000*duration.count() % 9); // it assumes the system delay time as the time of the deposit.
      interest = acc.deposit * pow(1 + rate, time);
      acc.deposit += interest;
      cout << "The interest you find within "<< time<<" years is " <<interest << endl;
    }
    ofile << acc.account_no << "  "<< acc.first_name << "  " << acc.last_name << "  "<< acc.id << "  " << acc.deposit << endl;
  }
  ifile.close();
  ofile.close();
  // to copy the files from temp.txt to project.txt
  open_file2(ifile,ofile);
  while (ifile >> acc.account_no >> acc.first_name >> acc.last_name >> acc.id >> acc.deposit){
    ofile << acc.account_no <<"  " <<acc.first_name << "  " << acc.last_name <<"  "<<acc.id<< "  " <<acc.deposit << endl;
  }
  ifile.close();
  ofile.close();
  remove("temp.txt");// no need to store this file anymore.
}
void transfer_money_to_account(ifstream &ifile,ofstream& ofile){
  open_file1(ifile,ofile);
cout << "Enter your account number: ";
cin >> new_acc_no;
while (ifile >> acc.account_no >> acc.first_name >> acc.last_name >> acc.id >> acc.deposit)
{
if (strncmp (acc.account_no, new_acc_no, strlen(new_acc_no)) == 0){
d:
cout << "Enter the amount of money you want to transfer: ";
cin >> amount;
if(amount > acc.deposit)
{
cout << "You don't have enough money to transfer this amount. Try again." << endl;
goto d;
}
else
acc.deposit -= amount;
}
 ofile << acc.account_no << "  " << acc.first_name << "  " << acc.last_name << "  " << acc.id << " " << acc.deposit << endl;
}
ofile.close();
ifile.close();
//to copy
open_file2(ifile,ofile);
while(ifile >> acc.account_no >> acc.first_name >>acc.last_name >> acc.id >> acc.deposit){
ofile << acc.account_no << "  " << acc.first_name << "  " << acc.last_name << "  " << acc.id<< "  " << acc.deposit << endl;
}
ofile.close();
ifile.close();
remove("temp.txt"); //again, unnecessary to store temp.
//for the second account
open_file1(ifile,ofile);
cout << "Enter the account number you want to transfer to: ";
cin >> new_acc_no;
while (ifile >> acc.account_no >> acc.first_name >> acc.last_name >> acc.id >> acc.deposit)
{
if (strncmp (acc.account_no, new_acc_no, strlen(new_acc_no))==0)
    {
  acc.deposit += amount;
}
 ofile << acc.account_no << "  " << acc.first_name << "  " << acc.last_name << "  " << acc.id << "  "<< acc.deposit << endl;
}
 ofile.close();
 ifile.close();
 // To copy the changes from temporary file to the main file
 open_file2(ifile,ofile);
while (ifile >> acc.account_no >> acc.first_name >>acc.last_name >>acc.id >> acc.deposit){
   ofile << acc.account_no << "  " << acc.first_name << "  " << acc.last_name << "  " << acc.id << "  "<< acc.deposit << endl;
}
ifile.close();
ofile.close();
remove("temp.txt");
cout << "Transaction done successfully!"<<endl;
}
void display_accountInfo(ifstream &ifile)
{
  ifile.open("projectFile.txt");
  if (ifile.fail())
  {
    cout << "Error performing request. Try again.\n";
    exit(1);
  }
  cout << "Enter account number\n";
  cin >> new_acc_no;
  while (ifile >> acc.account_no >> acc.first_name >> acc.last_name >> acc.id >> acc.deposit)
  {
    if (strncmp(acc.account_no, new_acc_no, strlen(new_acc_no)) == 0)
    {
      cout << "Account:     " << acc.account_no << "\nFirst name:  " << acc.first_name << "\nLast Name: " << acc.last_name 
      << "\nID:\t     " << acc.id << "\nBalance:    " << acc.deposit << endl;
    }
  }
  ifile.close();
}
int main()
{ int choice;
  ifstream i_file;
  ofstream o_file;
  do{
    cout << "\n\n*********  Bank System Menu:    *******\n\n";
    cout << "1. Create Account\n"<<"2. Deposit or Withdraw\n"<< "3.Calculate Interest\n" << "4.Transfer Money\n"<<
        "5. Display Account Balance\n"<< "6. Exit" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
      createAccount(o_file);
      break;
    case 2:
      deposit_withdraw(i_file, o_file);
      break;
    case 3:
     interest_calculator(i_file, o_file);
      break;
    case 4:
      transfer_money_to_account(i_file,o_file);
      break;
    case 5:
      display_accountInfo(i_file);
      break;
    case 6:
      cout << "Exiting the program. Thank you for using our bank!" << endl;
      return 0;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 6);
  return 0;
}