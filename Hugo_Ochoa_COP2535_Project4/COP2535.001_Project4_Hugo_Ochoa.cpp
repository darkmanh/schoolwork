//Hugo Ochoa
//COP2535.001
/*
Write an C++ OOP program that will use vectors and templates to solve the following problem.

An input file named Pluto.txt is available in the Canvas module for you to peruse.  
It contains words, punctuation, and numbers as digits.

-Read through the input file string values into a string vector and numeric values into a 
 float vector.

-Create one method to count the number of items within each vector:

		<T> count(vector <T> v)

					Display the number of items stored in each array.

-Create one method within the class to search the appropriate vector:

		<T> search(vector <T> v)

-The program will call each template member function twice.  The first call will pass the 
 string vector and the second call will pass the float vector.
-Prompt the user for an input value.  Using only one method to search (see above), search
 the appropriate vector and return the count of times the input value entered by the user 
 is stored within the appropriate vector.
*/

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<vector>
#include<cctype>

using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

/**************** classes *********************/
template <class T>
int count(vector <T> v)
{
	return v.size();
}

template <class T>
int search(vector <T> const& v,T data)
{
	int count = 0;
	for (int i = 0; i < v.size(); i++) {
		if ( v[i] == data)
			count++;
	}
	return count;
}

class fileParser
{
public:
	vector<float> numbers;					//numbers vector
	vector<string> words;					//words vector
	ifstream inputFile;						//input file

	void openFile();						//open the file
	void readFile();						//read the file
	void displayCounts();					//show title and file parsing counts of words and numbers

public:
	void driver();							//order of excecution
};

/****************main*************************/
int main()
{
	fileParser f;

	f.driver();
}

/*************** methods *********************/

//************************************
//* open Pluto.txt file
//************************************
void fileParser::openFile()
{
	using std::cerr;

	inputFile.open("Pluto.txt");	//open the file
	if (!inputFile)					//handle errors
	{
		cerr << "Pluto.txt did not open properly." << endl << endl;
		exit(9898);     //pick some integer value that's not zero to indicate a problem occurred
	}
}

//************************************************
//* read Pluto.txt file and populate the vectors.
//************************************************
void fileParser::readFile()
{
	float n = 0;				//float value read from the file
	string s;				    //string read from the file

	while (!inputFile.eof())		//read the file until eof
	{
		inputFile >> n;
		if (!inputFile)
		{
			inputFile.clear();
			inputFile >> s;
			for (int i = 0; i < s.length(); i++)
			{
				char temp = toupper(s[i]);
				s[i] = temp;
			}
			//cout << s;
			words.push_back(s);			//populate words vector
		}
		else
		{
			cout << n << endl;
			numbers.push_back(n);		//populate words vector
		}
	}
	inputFile.close();
}

//*********************************************************
//* show title and file parsing counts of words and numbers
//*********************************************************
void fileParser::displayCounts()
{
	string val;				//value to search for
	float fval;
	int c = 0;				//number of times value is found

	cout << "Find a Value" << endl << endl;
	cout << "Using the input file, Pluto.txt, the following contains the number of values in each vector." << endl << endl;

	cout << "Total Words:   " << setw(10) << count(words) << endl;
	cout << "Total Numbers: " << setw(10) << count(numbers) << endl;
	cout << endl;

	cout << "Enter a value to search. Type EXIT to quit." << endl << endl;

	do
	{
		c = 0;
		cout << "Enter a value to search: ";
		cin >> fval;
		if (!cin)
		{
			cin.clear();
			cin >> val;
			for (int i = 0; i < val.length(); i++)
			{
				char temp = toupper(val[i]);
				val[i] = temp;
			}
			c += search(words, val);
		}
		else
			c += search(numbers, fval);

		if (val != "EXIT" && val != "exit")
		{
			cout << "The number of times found: ";
			cout << c << endl << endl;
		}
		else
		{
			cout << "End of results." << endl << endl;
		}

	} while (val != "EXIT" && val != "exit");

}

//********************
//* order of execution
//********************
void fileParser::driver()
{
	openFile();
	readFile();
	displayCounts();
}
