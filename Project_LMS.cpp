#include<iostream>
#include<conio.h>
#include<string>
#include<cstring>
#include<fstream>
#include<ctime>
using namespace std;

/* Global Variables, Represent File Names */
string Time;
string bookFile = "Book.txt";
string studentFile = "Student.txt";
string tempFile = "Temp.txt";

/* Structures */
struct Book
{
	string book;
	int quantity;
};

struct Student
{
	string rollNo;
	string name;
	string pTime;
	string pBook;
	string sTime;
	string sBook;
};

/* Prototypes */
void Menu();
void AR_Book();
void A_Book(string);
void U_Book(string, int, int);
void R_Book(string);
void AR_Student();
void A_Student();
void R_Student();
bool U_Student(string, string, int);
void IssueBook();
void ReturnBook();
bool BookValidation(string);
bool StudentValidation(string);
void TimeFunction();

int main ()
{
	TimeFunction();
	int x;
	string ID, pinCode;
	char ch;
	
	Again:
	cout << "Enter ID: ";
	cin >> ID;
	cout << "Enter Password: ";
	
	while (true)
	{	
		ch = _getch();
		x = static_cast<int>(ch);
		if (x == 13)
		break;
		else
		{
			cout << "*";
			pinCode.push_back(ch);
		}	
	}
	
	if (ID == "Admin" && pinCode == "1234")
	Menu();
	else
	{
		system("CLS");
		cout << "Invalid ID or Password" << endl;
		goto Again;
	}
	return 0;
}

void TimeFunction()
{ 
	string str;
	time_t t;
	t = time(0);
	str = ctime(&t);
	
	for (int i = 0; i < 11; i++)
	Time.push_back(str[i]);
}

void Menu()
{
	int chose;
	Again:
	system("CLS");
	cout << "1) Add/Remove a Book" << endl;
	cout << "2) Add/Remove a Student Account" << endl;
	cout << "3) Issue a Book" << endl;
	cout << "4) Returned a Book" << endl;
	cout << "5) Exit" << endl << endl;
	cout << "Enter Your Choice: ";
	cin >> chose;
	
	switch (chose)
	{
		case 1:
			AR_Book();
			goto Again;
			break;
		case 2:
			AR_Student();
			goto Again;
			break;
		case 3:
			IssueBook();
			goto Again;
			break;
		case 4:
			ReturnBook();
			goto Again;
			break;
		case 5:
			exit(0);
			break;
		default:
			system("CLS");
			cout << "Invalid Choice" << endl;
			goto Again;
			break;
	}
}

void AR_Book()
{
	system("CLS");
	string bookName;
	
	int chose;
	Again:
	cout << "1) Add a New Book" << endl;
	cout << "2) Add an Old Book" << endl;
	cout << "3) Remove a Book" << endl;
	cout << endl << "Enter Your Choice: " << endl; 
	cin >> chose;
	
	if (chose == 1 || chose == 2 || chose == 3)
	{
		system("CLS");
		cout << "Enter Book Name: ";
		cin >> bookName;
		
		if (chose == 1)
		A_Book(bookName);
		else if (chose == 2)
		U_Book(bookName, 1, 1);
		else
		R_Book(bookName);
	}
	else
	{
		system("CLS");
		cout << "Invalid choice" << endl;
		goto Again;
	}
}

void A_Book(string bookName)
{
	Book add;
	if (!BookValidation(bookName))
	{
		ofstream fout(bookFile.c_str(), ios::app);
		fout << endl << bookName;
		fout << endl << "1";
		fout.close();
	}
	else
	{
		cout << "Book Already Exist" << endl;
		system("pause");
	}
	
}

void U_Book(string bookName, int num, int check)
{
	int count = 0;
	Book add;
	ifstream fin(bookFile.c_str());
	ofstream fout(tempFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while (!(fin.eof()))
		{
			getline(fin, add.book);
			fin >> add.quantity;
			fin.ignore();
			
			
			if (add.book == bookName)
			{
				
				if (num == -1 && add.quantity == 0)
				{
					cout << "Book is not Available" << endl;
					return;
				}
				if (num == 1 || num == -1)
				add.quantity += num;
				count++;			
			}
		
			fout << endl << add.book;
			fout << endl << add.quantity;
		}
					
		if (check == 1 && count == 0)
		{
			fout << endl << bookName;
			fout << endl << num;			
		}
		if (check == 0 && count == 0)
		cout << "Book is not Available" << endl;
			
		fin.close();
		fout.close();
		remove(bookFile.c_str());
		rename(tempFile.c_str(), bookFile.c_str());
	}
	else
	cout << "File is not opening";
}

void R_Book(string bookName)
{
	Book Remove;
	ifstream fin(bookFile.c_str());
	ofstream fout(tempFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while (!(fin.eof()))
		{
			getline(fin, Remove.book);
			fin >> Remove.quantity;
			fin.ignore();
			if ((Remove.book != bookName))
			{
				fout << endl << Remove.book;
				fout << endl << Remove.quantity;
			}
		}
		fin.close();
		fout.close();
		
		remove(bookFile.c_str());
		rename(tempFile.c_str(),bookFile.c_str());
	}
	else
	cout << "File is not opening";
}

void AR_Student()
{
	system("CLS");	
	int chose;
	Again:
	cout << "1) Add a Student Account" << endl;
	cout << "2) Remove a Student Account" << endl;
	cout << endl << "Enter Your Choice: " << endl;
	cin >> chose;
	
	if (chose == 1 || chose == 2)
	{
		(chose == 1)?
		A_Student():
		R_Student();
	}
	else
	{
		system("CLS");
		cout << "Invalid choice" << endl;
		goto Again;
	}
}

void A_Student()
{
	system("CLS");
	Student add;
	cout << "Student Roll No: ";
	cin >> add.rollNo;
	cout << "Student Name: ";
	cin.ignore();
	getline(cin, add.name);
	add.pTime = add.pBook = add.sTime = add.sBook = "N/A";
	if (!StudentValidation(add.rollNo))
	{
		ofstream fout(studentFile.c_str(), ios::app);
		if (fout.is_open())
		{
			fout << endl << add.rollNo;
			fout << endl << add.name;
			fout << endl << add.pTime;
			fout << endl << add.pBook;
			fout << endl << add.sTime;
			fout << endl << add.sBook;
			fout.close();
		}
		else
		cout << "File is not opening";
	}
	else
	{
		cout << "Student Already Exist" << endl;
		system("pause");	
	}

}

void R_Student()
{
	system("CLS");
	Student Remove;
	string rollNo;
	cout << "Student Roll No: ";
	cin >> rollNo;
	ifstream fin(studentFile.c_str());
	ofstream fout(tempFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while (!(fin.eof()))
		{
			getline(fin, Remove.rollNo);
			getline(fin, Remove.name);
			getline(fin, Remove.pTime);
			getline(fin, Remove.pBook);
			getline(fin, Remove.sTime);
			getline(fin, Remove.sBook);
			if (Remove.rollNo != rollNo)
			{
				fout << endl << Remove.rollNo;
				fout << endl << Remove.name;
				fout << endl << Remove.pTime;
				fout << endl << Remove.pBook;
				fout << endl << Remove.sTime;
				fout << endl << Remove.sBook;
			}
		}
		fin.close();
		fout.close();
		remove(studentFile.c_str());
		rename(tempFile.c_str(),studentFile.c_str());
	}
	else
	{
		cout << "File is not opening";	
		system("pause");
	}	
}

bool U_Student(string rollNo, string bookName, int check)
{
	bool Bool = true;
	int count = 0;
	Student update;
	ifstream fin(studentFile.c_str());
	ofstream fout(tempFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while (!(fin.eof()))
		{
			getline(fin, update.rollNo);
			getline(fin, update.name);
			getline(fin, update.pTime);
			getline(fin, update.pBook);
			getline(fin, update.sTime);
			getline(fin, update.sBook);
			
			if (update.rollNo == rollNo)
			{
				if (check == 1)
				{
					cout << update.rollNo << endl;
					cout << update.name << endl;
					cout << update.pTime << endl;
					cout << update.pBook << endl;
					cout << update.sTime << endl;
					cout << update.sBook << endl;
					system("pause");
										
					if (update.pBook == bookName)
					update.pBook = update.pTime = "N/A";
					if (update.sBook == bookName)
					update.sBook = update.sTime = "N/A";
					count++;
				}
				else
				{
					if (update.pTime == "N/A" && update.pBook == "N/A")
					{
						update.pTime = Time;
						update.pBook = bookName;
						count++;					
					}
					else if (update.sTime == "N/A" && update.sBook == "N/A")
					{
						update.sTime = Time;
						update.sBook = bookName;
						count++;					
					}
				}			
			}
			
			fout << endl << update.rollNo;
			fout << endl << update.name;
			fout << endl << update.pTime;
			fout << endl << update.pBook;
			fout << endl << update.sTime;
			fout << endl << update.sBook;
		}	
		fin.close();
		fout.close();
		remove(studentFile.c_str());
		rename(tempFile.c_str(), studentFile.c_str());
		
		if (count == 0)
		Bool = false;
		
		return Bool;
	}
	else
	cout << "File is not opening";
}

void IssueBook()
{
	system("CLS");
	Book iBook;
	Student iStudent;
	
	cout << "Enter Student ID: ";
	cin >> iStudent.rollNo;
	cout << "Enter Book Name: ";
	cin >> iBook.book;
	
	if (StudentValidation(iStudent.rollNo))
	{
		if (U_Student(iStudent.rollNo, iBook.book, 0))
		{
			if (BookValidation(iBook.book))
			U_Book(iBook.book, -1, 0);
			else
			{
				cout << "Invalid Book" << endl;
				system("pause");
			}
		}
		else
		{
			cout << "You cannot issue more than two books" << endl;
			system("pause");
		}
	}
	else
	{
		cout << "Invalid Roll No" << endl;
		system("pause");
	}
}

void ReturnBook()
{
	system("CLS");
	Book rBook;
	Student rStudent;
	
	cout << "Enter Student ID: ";
	cin >> rStudent.rollNo;
	cout << "Enter Book Name: ";
	cin >> rBook.book;
	
	if (StudentValidation(rStudent.rollNo))
	{
		if (U_Student(rStudent.rollNo, rBook.book, 1))
		{
			if (BookValidation(rBook.book))
			U_Book(rBook.book, 1, 1);
			else
			{
				cout << "Invalid Book" << endl;
				system("pause");
			}
		}		
	}
	else
	{
		cout << "Invalid Roll No" << endl;
		system("pause");
	}
}

bool BookValidation(string bookName)
{
	Book validate;
	ifstream fin(bookFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while(!(fin.eof()))
		{
			getline(fin, validate.book);
			fin >> validate.quantity;
			fin.ignore();
			
			if (validate.book == bookName && validate.quantity != 0)
			{
				fin.close();
				return true;
			}
		}
		fin.close();
		return false;
	}
	else
	cout << "File is not opening" << endl;
}

bool StudentValidation(string rollNo)
{
	Student validate;
	ifstream fin(studentFile.c_str());
	if (fin.is_open())
	{
		fin.ignore();
		while(!(fin.eof()))
		{
			getline(fin, validate.rollNo);
			getline(fin, validate.name);
			getline(fin, validate.pTime);
			getline(fin, validate.pBook);
			getline(fin, validate.sTime);
			getline(fin, validate.sBook);
			
			if (validate.rollNo == rollNo)
			{
				fin.close();
				return true;
			}
		}
		fin.close();
		return false;
	}
	else
	cout << "File is not opening" << endl;
}
