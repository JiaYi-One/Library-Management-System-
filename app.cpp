#define _CRT_SECURE_NO_WARNINGS

#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	<iomanip>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);
int menu();

int main() {

	List studList, warningList1, warningList2;
	int choice, disOut, disBook;
	LibStudent foundStudent;
	bool checkInsertBook = false; //true when book.txt is read (Option 4)

	do {

		choice = menu();
		switch (choice) {

		case 1:
			//Q1
			system("cls");
			cout << "READ FILE\n";
			cout << "**************************************************" << endl;

			if (ReadFile("student.txt", &studList))
				cout << studList.size() << " record(s) has been successfully read!\n" << endl;
			else
				cout << "Error when opening the text file!" << endl;
			system("pause");
			break;

		case 2:
			//Q2
			system("cls");
			cout << "DELETE RECORD" << endl;
			cout << "********************************************" << endl;

			char idToDelete[8];//let user to input ID to delete
			cout << "Enter the student ID to delete: ";
			cin >> idToDelete;

			cout << endl;
			DeleteRecord(&studList, idToDelete);
			system("pause");
			break;

		case 3:
			//Q3
			system("cls");
			cout << "SEARCH STUDENT" << endl;
			cout << "*************************************************" << endl;

			char idToSearch[8]; // let user to input ID to search
			cout << "Enter the student's ID to search: ";
			cin >> idToSearch;

			if (SearchStudent(&studList, idToSearch, foundStudent))
				cout << "\nSearch operation successful.\n\n";
			else
				cout << "\nSearch operation unsuccessful.\n\n";

			system("pause");
			break;

		case 4:

			//Q4
			system("cls");
			cout << "INSERT BOOK" << endl;
			cout << "****************************************************" << endl;
			if (checkInsertBook)//to avoid user insert data for more than 1 times, or not the same data will be inserted
				cout << "Book List already inserted!" << endl;
			else 
			{
				if (InsertBook("book.txt", &studList))
				{
					cout << "Books inserted successfully to student list." << endl;
					checkInsertBook = true;
				}
			}
			system("pause");
			break;

		case 5:

			//Q5
			system("cls");
			cout << "DISPLAY OUTPUT" << endl;
			cout << "*****************************************************************************************" << endl;
			if (studList.empty() || !checkInsertBook)
				cout << "Empty list detected!\nPlease undergo Option 1 and Option 4 to read data first!" << endl;
			else
			{
				cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
				cin >> disOut;
				cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
				cin >> disBook;

				Display(&studList, disOut, disBook);
			}
			system("pause");
			break;

		case 6:

			//Q6
			system("cls");
			cout << "STATISTICS TABLE\n";
			cout << "****************************************************************************************************" << endl;
			if (studList.empty() || !checkInsertBook)
				cout << "Empty list detected!\nPlease undergo Option 1 and Option 4 to read data first!" << endl;
			else
			{
				computeAndDisplayStatistics(&studList);
				cout << "\n\n";
			}
			system("pause");
			break;

		case 7:

			//Q7
			system("cls");
			cout << "STUDENT WITH SAME BOOK\n";
			cout << "*****************************************************************************************" << endl;
			if (studList.empty() || !checkInsertBook)
				cout << "Empty list detected!\nPlease undergo Option 1 and Option 4 to read data first!" << endl;
			else
			{
				char findBook[20];
				cout << "Enter Call Num: ";
				cin >> findBook;
				cout << "\n";
				printStuWithSameBook(&studList, findBook);
			}
			system("pause");
			break;

		case 8:

			//Q8
			system("cls");
			cout << "WARNING STUDENT LIST" << endl;
			cout << "***********************************************************************************************************************" << endl;
			if (studList.empty() || !checkInsertBook)
				cout << "Empty list detected!\nPlease undergo Option 1 and Option 4 to read data first!" << endl;
			else
			{
				displayWarnedStudent(&studList, &warningList1, &warningList2);
			}
			system("pause");
			break;

		case 9:

			//EXIT
			system("cls");
			cout << "________________________________________________\n";
			cout << "|                                              |\n";
			cout << "|Thanks for using our system. Have a good day! |\n";
			cout << "|______________________________________________|\n";
		}

	} while (choice != 9);//when choice == 9, exit loop

	cout << "\n\n";
	system("pause");
	return 0;
}

int menu() {
	int choice;

	system("cls");
	cout << "Menu" << endl;
	cout << "-----------------------------------" << endl;
	cout << "1. Read file" << endl;
	cout << "2. Delete record" << endl;
	cout << "3. Search student" << endl;
	cout << "4. Insert book" << endl;
	cout << "5. Display output" << endl;
	cout << "6. Compute and Display Statistics" << endl;
	cout << "7. Student with Same Book" << endl;
	cout << "8. Display Warned Student" << endl;
	cout << "9. Exit" << endl;
	cout << "-----------------------------------" << endl;

	do {
		cout << "Enter your choice (1-9): ";
		cin >> choice;

		// Check if the input is valid
		if (cin.fail()) {
			cout << "\nInvalid input :( \nPlease enter a number from 1 to 9." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		// Check if the input is within the valid range
		if (choice < 1 || choice > 9) {
			cout << "\nInvalid option:(\nPlease enter a number from 1 to 9." << endl;
			continue;
		}

		// Exit the loop if a valid choice is entered
		break;
	} while (true);

	return choice;
}

bool ReadFile(string filename, List* list)
{
	ifstream myFile(filename);
	LibStudent s;

	if (!myFile.is_open())
		return false;
	else
	{
		while (!myFile.eof())
		{
			for (int i = 0; i < 4; i++)//get rid off the front words
				myFile >> s.id;

			for (int i = 0; i < 3; i++)
			{
				char lastname[30];
				myFile >> s.name; //get the first word of the name

				if (i == 2)
				{
					myFile.getline(lastname, 30); //get the rest name 
					strcat(s.name, lastname);
				}
			}
			for (int i = 0; i < 3; i++)
				myFile >> s.course;

			for (int i = 0; i < 4; i++)
				myFile >> s.phone_no;
		
			if (myFile)
			{
				if (list->size() == 0)//direct insert first item into the list because confirm no duplicate will occur
				{
					list->insert(s);
				}
				else //check duplicate
				{
					bool found = false;
					Node* cur = list->head;
					for (int i = 0; i < list->size(); i++)
					{
						if (s.compareName2(cur->item))//will return true if duplicate name found
						{
							found = true;
							break;
						}
						cur = cur->next;
					}
					if (!found)//found = false, when the data is not duplicated, then insert to the list
						list->insert(s);
				}
			}

		}
		myFile.close();
	}
	return true;

}

bool DeleteRecord(List* list, char* id)
{

	if (list->empty()) {
		cout << "Empty list detected!\nPlease undergo Option 1 to read student data first!" << endl;
		return false;
	}
	else
	{
		char idToDelete[8];
		char* id;
		id = &idToDelete[0];
	}

	Node* cur = list->head;
	int current = 1, compare;

	while (cur)
	{

		compare = strcmp(id, cur->item.id);//compare the id user input and id in recorded student list
		if (compare == 0)//when the list student id is same with user input id
		{
			list->remove(current);
			cout << "Student record is deleted successfully. \n\n";
			return true;
		}
		else
		{
			cur = cur->next;
			current++;
		}
	}

	//tranversed the whole list but stud with user input id is still not found
	cout << "This student is not found in record!\n" << endl;
	return false;

}

bool SearchStudent(List* list, char* id, LibStudent& stu)
{
	if (list->empty())
	{
		cout << "Empty list detected!\nPlease undergo Option 1 to read student data first!" << endl;
		return false;
	}
	else
	{
		Node* current = list->head;

		while (current != nullptr) {
			if (strcmp(current->item.id, id) == 0) //when the list student id is same with user input id
			{
				stu = current->item;

				cout << "\nStudent found:";
				stu.print(cout);//print student details

				return true;
			}
			current = current->next;
		}

		//tranversed the whole list but stud with user input id is still not found
		cout << "\nStudent with ID " << id << " not found.\n";
		return false;
	}
}

bool InsertBook(string filename, List* list)
{
	if (list->empty())
	{
		cout << "Empty list detected!\nPlease undergo Option 1 to read student data first!" << endl;
		return false;
	}
	else
	{	
		ifstream bookFile;
		LibStudent stud;
		LibBook book;
		char unwanted_symbol;//to record '/' symbol from text file
		string author;
		bookFile.open(filename);
		if (!bookFile)
		{
			cout << "\n\nCannot open file book.txt\n\n";
			return false;
		}
		else
		{
			while (bookFile >> stud.id)//loop until no data left in txt file
			{
				bookFile >> author;
				for (int i = 0; i < author.length(); i++)
				{
					//to replace '-' to ' '
					if (author[i] == '_')
						author[i] = ' ';
				}

				//to split author
				int pos = 0, author_count = 0;
				for (int i = 0; i < author.length(); i++)
				{
					if (author[i] == '/') //for author in front of '/' symbol case
					{
						book.author[author_count] = new char[20];
						strcpy(book.author[author_count], author.substr(pos, i - pos).c_str());
						pos = i + 1;
						author_count++;
					}
					if (i == author.length() - 1)// for last author and one author case
					{
						book.author[author_count] = new char[20];//initialize
						strcpy(book.author[author_count], author.substr(pos, i - pos + 1).c_str());
						author_count++;
					}
				}

				bookFile >> book.title;
				for (int cha = 0; cha < strlen(book.title); cha++)
				{
					//to replace '-' to ' '
					if (book.title[cha] == '_')
						book.title[cha] = ' ';
				}
				bookFile >> book.publisher;
				for (int cha = 0; cha < strlen(book.publisher); cha++)
				{
					//to replace '-' to ' '
					if (book.publisher[cha] == '_')
						book.publisher[cha] = ' ';
				}
				bookFile >> book.ISBN;
				bookFile >> book.yearPublished;
				bookFile >> book.callNum;

				bookFile >> book.borrow.day;
				bookFile >> unwanted_symbol;
				bookFile >> book.borrow.month;
				bookFile >> unwanted_symbol;
				bookFile >> book.borrow.year;

				bookFile >> book.due.day;
				bookFile >> unwanted_symbol;
				bookFile >> book.due.month;
				bookFile >> unwanted_symbol;
				bookFile >> book.due.year;

				double fine1, fine2, fine3;
				//fine1 is fine for January, fine2 is for February, and fine3 is for March
				//assume that the book.txt will be renew every year so there will be no borrow record from previous year
				if (book.due.month == 3 && book.due.day < 29)
				{
					fine3 = (29 - book.due.day) * 0.50;
					book.fine = fine3;
				}
				else if (book.due.month == 2)
				{
					fine3 = 28 * 0.5;//29-3-2020 not counted as due
					fine2 = (29 - book.due.day) * 0.50;
					book.fine = fine2 + fine3;
				}
				else if (book.due.month == 1)
				{
					fine3 = 28 * 0.5;//29-3-2020 not counted as due
					fine2 = 29 * 0.5;
					fine1 = (31 - book.due.day) * 0.50;
					book.fine = fine1 + fine2 + fine3;
				}
				else { //not over due date yet
					book.fine = 0;
				}
				Node* cur;
				cur = list->head;
				for (int i = 1; i <= list->size(); i++) {

					if (strcmp(stud.id, cur->item.id) == 0) {
						int bookCount = cur->item.totalbook;//initially totalbook = 0

						//assign data into stud_list
						strcpy(cur->item.book[bookCount].title, book.title);
						strcpy(cur->item.book[bookCount].publisher, book.publisher);
						cur->item.book[bookCount].yearPublished = book.yearPublished;
						strcpy(cur->item.book[bookCount].ISBN, book.ISBN);
						strcpy(cur->item.book[bookCount].callNum, book.callNum);

						//assign author
						for (int j = 0; book.author[j] != NULL; j++)
						{
							cur->item.book[bookCount].author[j] = book.author[j];
						}

						//delete author memory for future use
						for (int k = 0; book.author[k] != NULL; k++)
						{
							book.author[author_count] = NULL;
						}

						cur->item.book[bookCount].borrow.day = book.borrow.day;
						cur->item.book[bookCount].borrow.month = book.borrow.month;
						cur->item.book[bookCount].borrow.year = book.borrow.year;
						cur->item.book[bookCount].due.day = book.due.day;
						cur->item.book[bookCount].due.month = book.due.month;
						cur->item.book[bookCount].due.year = book.due.year;
						cur->item.book[bookCount].fine = book.fine;

						cur->item.totalbook++;
						cur->item.calculateTotalFine();
						break;
					}
					else
						cur = cur->next;
				}
			}
		}
		bookFile.close();
		return true;
	}
}

bool Display(List* list, int source, int detail) {

	ofstream outFile;
	LibStudent s;
	LibBook book;
	Node* cur = list->head;

	int index = 1;
	while ((source != 1 && source != 2) || (detail != 1 && detail != 2)) //data validation
	{
		cout << "\nYou have entered an invalid option, please try again" << endl;
		cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
		cin >> source;
		cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
		cin >> detail;
	}
	if (source == 1 && detail == 1) //write to file with booklist
	{

		outFile.open("student_booklist.txt");

		while (cur != nullptr)
		{
			outFile << endl;

			outFile << "STUDENT " << index;
			cur->item.print(outFile);
			outFile << endl;

			outFile << "\nBOOK LIST: " << endl;


			for (int i = 0; i < cur->item.totalbook; i++)
			{
				outFile << "\nBook " << i + 1 << endl;
				cur->item.book[i].print(outFile);
			}

			for (int i = 0; i < 70; i++)
				outFile << "*";
			
			outFile << endl;
			cur = cur->next;
			index++;
		}
		outFile.close();
		cout << "\nSuccessfully display output to student_booklist.txt" << endl << endl;


	}
	else if (source == 1 && detail == 2) //write to file without booklist
	{
		outFile.open("student_info.txt");
		while (cur != nullptr)
		{
			outFile << endl;

			outFile << "STUDENT " << index;
			cur->item.print(outFile); // Call the print function for the current student
			outFile << endl;

			for (int i = 0; i < 70; i++)
				outFile << "*";

			cur = cur->next;
			index++;
		}

		outFile.close();
		cout << "\nSuccessfully display output to student_info.txt" << endl << endl;

	}

	else if (source == 2 && detail == 1) //display to screen with booklist
	{

		while (cur != nullptr) {
			cout << "\n\nSTUDENT " << index;
			cout << "\n\nName: " << cur->item.name;
			cout << "\nId: " << cur->item.id;
			cout << "\nCourse: " << cur->item.course;
			cout << "\nPhone No: " << cur->item.phone_no;
			cout << "\nTotal Fine: RM" << fixed << setprecision(2) << cur->item.total_fine;
			cout << endl;

			cout << "\nBOOK LIST: " << endl;

			for (int i = 0; i < cur->item.totalbook; i++) {
				cout << "\nBook " << i + 1 << endl;
				cout << "\nTitle: " << cur->item.book[i].title;
				cout << "\nAuthor: ";
				for (int j = 0; cur->item.book[i].author[j] != NULL; j++)
					cout << cur->item.book[i].author[j] << '\t';
				cout << "\nPublisher: " << cur->item.book[i].publisher;
				cout << "\nYear Published: " << cur->item.book[i].yearPublished;
				cout << "\nISBN: " << cur->item.book[i].ISBN;

				cout << "\nCall Number: " << cur->item.book[i].callNum;
				cout << "\nBorrow Date: ";
				cout << cur->item.book[i].borrow.day << "/" << cur->item.book[i].borrow.month << "/" << cur->item.book[i].borrow.year;
				cout << "\nDue Date: ";
				cout << cur->item.book[i].due.day << "/" << cur->item.book[i].due.month << "/" << cur->item.book[i].due.year;
				cout << "\nFine: RM" << fixed << setprecision(2) << cur->item.book[i].fine;
				cout << endl;
				cout << "\n\n";
			}

			for (int i = 0; i < 70; i++) 
				cout << "*";

			cur = cur->next;
			index++;
		}
		cout << "\nSuccessfully display output!\n\n" << endl;
	}
	else //display to screen without booklist
	{
		while (cur != nullptr) {
			cout << "\n\nSTUDENT " << index;
			cout << "\n\nName: " << cur->item.name;
			cout << "\nId: " << cur->item.id;
			cout << "\nCourse: " << cur->item.course;
			cout << "\nPhone No: " << cur->item.phone_no;
			cout << "\nTotal Fine: RM" << fixed << setprecision(2) << cur->item.total_fine;
			cout << "\n\n";

			for (int i = 0; i < 70; i++) {
				cout << "*";
			}
			cur = cur->next;
			index++;
		}
		cout << "\nSuccessfully display output!\n\n" << endl;
	}
	return true;
}

bool computeAndDisplayStatistics(List* list) {

	Node* cur = list->head;
	char course[5];
	string courseCode[5] = { "CS","IA","IB","CN","CT" };
	int index, numStud[5], bookBorrowed[5], overdueBook[5]; double overdueFine[5];

	for (int i = 0; i < 5; i++) //initialize
	{
		course[i] = ' ';
		numStud[i] = 0;
		bookBorrowed[i] = 0;
		overdueBook[i] = 0;
		overdueFine[i] = 0.00;
	}

	while (cur != nullptr) {
		
		if (strcmp(cur->item.course, "CS") == 0) {
			strcpy(course, "CS");
			index = 0;
		}
		else if (strcmp(cur->item.course, "IA") == 0) {
			strcpy(course, "IA");
			index = 1;
		}

		else if (strcmp(cur->item.course, "IB") == 0) {
			strcpy(course, "IB");
			index = 2;
		}

		else if (strcmp(cur->item.course, "CN") == 0) {
			strcpy(course, "CN");
			index = 3;
		}

		else if (strcmp(cur->item.course, "CT") == 0) {
			strcpy(course, "CT");
			index = 4;
		}
		
		//to record borrow details for each course
		if (strcmp(cur->item.course, course) == 0)
		{
			for (int i = 0; i < cur->item.totalbook; i++) {
				if (cur->item.book[i].fine > 0) { // Check each book's fine
					overdueBook[index] += 1;
				}
			}
			overdueFine[index] += cur->item.total_fine;
		}
		numStud[index] += 1;
		bookBorrowed[index] += cur->item.totalbook;
		cur = cur->next;
	}
	//display the final table
	cout << left << setw(10) << "Course" << setw(20) << "Number Students" << setw(25) << "Total Books Borrowed" << setw(25) << "Total Overdue Books" << setw(25) << "Total Overdue Fine (RM)" << endl;
	for (int i = 0; i < 5; i++)
		cout << left << setw(18) << courseCode[i] << setw(20) << numStud[i] << setw(25) << bookBorrowed[i] << setw(25) << overdueBook[i] << setw(15) << fixed << setprecision(2) << right << overdueFine[i] << endl;

	return true;
}

bool printStuWithSameBook(List* list, char* callNum)
{
	Node* cur = list->head;


	int sameBook = 0;
	Node* studPos[50]; //Temporary node to store the studnt info with same book

	for (int i = 0; i < 50; i++) 
		studPos[i] = NULL; //initialize the content to null

	while (cur != nullptr) {
		for (int i = 0; i < cur->item.totalbook; i++) {
			if (strcmp(cur->item.book[i].callNum, callNum) == 0) {
				studPos[sameBook] = cur;
				sameBook++;
			}
		}
		cur = cur->next;
	}


	if (sameBook > 0) //more than one student having same book
	{
		cout << "There are " << sameBook << " students that borrow the book with call number " << callNum << " as shown below:" << endl;

		for (int i = 0; i < sameBook; i++) {

			cout << "Student Id = " << studPos[i]->item.id << endl;
			cout << "Name = " << studPos[i]->item.name << endl;
			cout << "Course = " << studPos[i]->item.course << endl;
			cout << "Phone Number = " << studPos[i]->item.phone_no << endl;
			cout << "Borrow Date = " << studPos[i]->item.book->borrow.day << "/"
				<< studPos[i]->item.book->borrow.month << "/"
				<< studPos[i]->item.book->borrow.year << endl;
			cout << "Due Date = " << studPos[i]->item.book->due.day << "/"
				<< studPos[i]->item.book->due.month << "/"
				<< studPos[i]->item.book->due.year << endl;
			cout << endl;
		}
	}
	else 
		cout << "There is no student who borrowed the same book." << endl;

	return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2)
{
	Node* cur = list->head;
	int duebook, dueday, checkalldue;

	//insert warning student to warning list
	while (cur != nullptr)
	{
		//warning case 1
		duebook = 0;//+1 when bookdue >= 10 days
		checkalldue = 0;
		for (int i = 0; i < cur->item.totalbook; i++)
		{
			dueday = 0;//record duedate

			if (cur->item.book[i].due.month == 2)
			{
				dueday += 29 - cur->item.book[i].due.day;//February
				dueday += 28; //March
			}
			else if (cur->item.book[i].due.month == 3 && cur->item.book[i].due.day < 29)
				dueday += 29 - cur->item.book[i].due.day; //March

			if (dueday >= 10)
				duebook++;

			if (cur->item.book[i].fine > 0)
				checkalldue++;
		}

		if (duebook > 2)//more than 2 books that are having >=10 days due
		{
			type1->insert(cur->item);
		}

		if (checkalldue == cur->item.totalbook && cur->item.total_fine > 50)//all books are due and total fine over RM50
		{
			type2->insert(cur->item);
		}
		cur = cur->next;
	}

	//display warning list
	Node* ptr;
	cout << "Which warning list are you willing to display?" << endl;
	cout << "Warning List 1 : Student has more than 2 books that are overdue for >= 10 days " << endl;
	cout << "Warning List 2 : Total fine for a student is more than RM50.00 and every book in the student's book list are overdue " << endl;
	cout << "***********************************************************************************************************************" << endl;
	char w_list;
	cout << "Option (1/2) >> ";
	cin >> w_list;
	while (w_list != '1' && w_list != '2')//data validation
	{
		cout << "Invalid input! Please re-enter your option(1/2) >>" << endl;
		cin >> w_list;
	}

	if (w_list == '1')//warning list 1
	{
		ptr = type1->head;
		if (type1->empty())
		{
			cout << "Warning List 1 is empty!" << endl;
			return true;
		}
	}
	else //warning list 2
	{
		ptr = type2->head;
		if (type2->empty())
		{
			cout << "Warning list 2 is empty!" << endl;
			return true;
		}
	}
	system("cls");
	//print out the warning list
	cout << "WARNING LIST " << w_list << endl;
	int index = 1;
	while (ptr != nullptr)
	{
		cout << "***************************************************************************************" << endl;
		cout << "STUDENT " << index << endl;
		cout << "***************************************************************************************" << endl;
		cout << "Name: " << ptr->item.name;
		cout << "\nId: " << ptr->item.id;
		cout << "\nCourse: " << ptr->item.course;
		cout << "\nPhone No: " << ptr->item.phone_no;
		cout << "\nTotal Fine: RM" << fixed << setprecision(2) << ptr->item.total_fine << endl << endl;
		cout << "***************************************************************************************" << endl;
		cout << "BOOK LIST: " << endl;
		cout << "***************************************************************************************" << endl;

		for (int i = 0; i < ptr->item.totalbook; i++)
		{
			cout << "Book " << i + 1 << endl;
			cout << "\nTitle: " << ptr->item.book[i].title;
			cout << "\nAuthor: ";
			for (int j = 0; ptr->item.book[i].author[j] != NULL; j++)//print all the borrowed book for current student
				cout << ptr->item.book[i].author[j] << '\t';
			cout << "\nPublisher: " << ptr->item.book[i].publisher;
			cout << "\nYear Published: " << ptr->item.book[i].yearPublished;
			cout << "\nISBN: " << ptr->item.book[i].ISBN;

			cout << "\nCall Number: " << ptr->item.book[i].callNum;
			cout << "\nBorrow Date: ";
			cout << ptr->item.book[i].borrow.day << "/" << ptr->item.book[i].borrow.month << "/" << ptr->item.book[i].borrow.year;
			cout << "\nDue Date: ";
			cout << ptr->item.book[i].due.day << "/" << ptr->item.book[i].due.month << "/" << ptr->item.book[i].due.year;
			cout << "\nFine: RM" << fixed << setprecision(2) << ptr->item.book[i].fine << "\n\n";
		}

		ptr = ptr->next;
		index++;//go to next student
	}

	cout << "***************************************************************************************" << endl;
	cout << " _____________________________________" << endl;
	cout << "|                                    |" << endl;
	cout << "|Successfully display Warning List " << w_list << "!|" << endl;
	cout << "|____________________________________|" << endl << endl;

	//empty the warning list for next time function call
	while (type1->head != nullptr)
		type1->remove(1);
	while (type2->head != nullptr)
		type2->remove(1);
	return true;

}