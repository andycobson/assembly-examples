/* ------------------------------------------------------------
 Programmer : Andrew S. Jacobson
 Date : April 30, 2020
 Description : This program performs several functions with
an array of Student records. This program
should work with any size array
 ------------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

const int ARRAY_SIZE = 12;                      //there are 12 records in the file
const int NAME_SIZE = 25;                       //all names are < 25 chars

struct Student
{
	char studentName[NAME_SIZE];
	unsigned int test1, test2, test3, test4;
	float average;
	bool passing;
};

void getData(Student[]);                        //loads the array with data from file
void print(Student[], Student);                 //show results
void findAverages(Student[]);                   //gets each student's avg based on 4 tests
void determinePassing(Student[]);               //passing is an average >= 60
void getHighestStudent(Student[], Student&);   //finds student with highest average

int main()
{
	Student theClass[ARRAY_SIZE];
	Student highest = { {"Nobody"}, 0,0,0,0,0,0 };   //this strucure will hold top student's info

	getData(theClass);
	findAverages(theClass);
	determinePassing(theClass);
	getHighestStudent(theClass, highest);       //NOTE: highest is a REFERENCE parameter!
	print(theClass, highest);
}
void getData(Student theClass[])
{
	ifstream infile;
	char temp[NAME_SIZE];                        //temporary array to read in names

	infile.open("student_data.txt");
	if (infile)
	{
		for (int x = 0; x < ARRAY_SIZE; x++)
		{
			infile.getline(temp, NAME_SIZE);       //workaround to read in array of chars
			strcpy(theClass[x].studentName, temp); //  instead of a string
			infile >> theClass[x].test1;
			infile >> theClass[x].test2;
			infile >> theClass[x].test3;
			infile >> theClass[x].test4;
			infile.ignore();
		}
		infile.close();
	}
	else
		cout << "Error opening file" << endl;
}

/* ------------------------------------------------------------
 print
 Description: Prints out the array of students and info, along with the
	top students info.
 Receives: The theClass array and the highest student struct.
 Returns: None.
 Requires: The getData function to run properly.
 ------------------------------------------------------------ */
void print(Student theClass[], Student bestStudent)
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << fixed;
		cout << "Name	: " << theClass[i].studentName << endl;
		cout << "Test1	: " << theClass[i].test1 << endl;
		cout << "Test2	: " << theClass[i].test2 << endl;
		cout << "Test3	: " << theClass[i].test3 << endl;
		cout << "Test4	: " << theClass[i].test4 << endl;
		cout << setprecision(2) << "Avg	: " << theClass[i].average << endl;
		if (theClass[i].passing) {
			cout << "Passing	: " << "yes\n" << endl;
		}
		else {
			cout << "Passing	: " << "no\n" << endl;
		}
	}

	cout << "Student with the highest average:" << endl;
	cout << fixed;
	cout << "Name	: " << bestStudent.studentName << endl;
	cout << "Test1	: " << bestStudent.test1 << endl;
	cout << "Test2	: " << bestStudent.test2 << endl;
	cout << "Test3	: " << bestStudent.test3 << endl;
	cout << "Test4	: " << bestStudent.test4 << endl;
	cout << setprecision(2) << "Avg	: " << bestStudent.average << endl;
	if (bestStudent.passing) {
		cout << "Passing	: " << "yes\n" << endl;
	}
	else {
		cout << "Passing	: " << "no\n" << endl;
	}
}

/* ------------------------------------------------------------
 findAverages
 Description: Calculates the averages of the 4 test grade attributes of
	all students in array. Then sets the average attribute to the result.
 Receives: The theClass array.
 Returns: None; manipulates
 Requires: getData to run okay.
 ------------------------------------------------------------ */
void findAverages(Student theClass[]) {
	int total;
	int divisor = 4;
	__asm {
		mov esi, theClass				// Offset to the class array; base
		mov ecx, ARRAY_SIZE				// Set loop counter to number of elements in array
		mov edi, 0						// Set index to 0
		lp1:							// Loop label
			mov [total], 0				// Set the total variable to 0 for reuse
			mov eax, [esi + edi].test1	// Get the test1 value from student element
			add [total], eax			// Add test1 value to total
			mov eax, [esi + edi].test2	// Get the test2 value from student element
			add [total], eax			// Add test1 value to tota2
			mov eax, [esi + edi].test3	// Get the test3 value from student element
			add [total], eax			// Add test1 value to tota3
			mov eax, [esi + edi].test4	// Get the test4 value from student element
			add [total], eax			// Add test1 value to tota4

			finit						// Initialize fps
			fild total					// Integer load the total of the test scores
			fidiv[divisor]				// Integer load and divide by 4 to get average
			fstp [esi + edi].average	// Store and pop the result to the elements average
			add edi, [TYPE theClass] * 13	// Index 52 bytes, the size of each struct
		loop lp1						// Loop instruction
	}
}

/* ------------------------------------------------------------
 determinPassing
 Description: Assigns a bool attribute based on the average if the
	student is passing or not.
 Receives: The theClass array
 Returns: No return; Manipulates
 Requires: Requires average to bew calculated already.
 ------------------------------------------------------------ */
void determinePassing(Student theClass[]) {
	double var = 60.0;
	__asm {
		mov esi, theClass				// Offset to the class array; base
		mov ecx, ARRAY_SIZE				// Set loop counter to number of elements in array
		mov edi, 0						// Set index to 0
		lp1:							// Loop label
			finit						// Initialize fps
			fld [var]					// Load the value 60.0
			fld [esi + edi].average		// Load the average from student struct
			fcomi ST(0), ST(1)			// Is average less than 60?
			jb L1						// Yes, jump to label
			mov [esi + edi].passing, 1	// No, average is greater than or equal to 60; true is set
			jmp skip					// Jump to end
			L1:							// Here to set passing to false
			mov [esi + edi].passing, 0	// Average is less than 60 so false is set
			skip:						// Reach end
			fstp ST(0)					// Pop to clear fps
			fstp ST(0)					// Pop to clear fps
			add edi, [TYPE theClass] * 13 // Index 52 bytes, the size of each struct
		loop lp1						// Loop instruction

	}
}

/* ------------------------------------------------------------
 getHighestStudent
 Description: Finds and assigns the student with the top average from
	the theClass array.
 Receives: The theClass array and reference to highest struct.
 Returns: None; manipulates
 Requires: All previous functions to have ran first.
 ------------------------------------------------------------ */
void getHighestStudent(Student theClass[], Student& highest) {
	__asm {
		mov esi, [theClass]				// Offset to the class array; base
		mov edi, highest				// Offset to the highest student struct
		mov ebx, 0						// Index for string name
		mov ecx, 3						// Loop counter to get all 12 bytes
		lp1:							// First loop label
			mov eax, DWORD PTR[esi + ebx]// Get a dword size from first struct
			mov DWORD PTR[edi + ebx], eax// Copy to highest 
			add ebx, 4					// Next 4 bytes
		loop lp1						// loop instruction
		mov eax, [esi].test1			// Get the test1 value from first element obj to highest
		mov[edi].test1, eax				// Copy test1 value to highest student
		mov eax, [esi].test2			// Get the test2 value from first element obj to highest
		mov[edi].test2, eax				// Copy test2 value to highest student
		mov eax, [esi].test3			// Get the test3 value from first element obj to highest
		mov[edi].test3, eax				// Copy test3 value to highest student
		mov eax, [esi].test4			// Get the test4 value from first element obj to highest
		mov[edi].test4, eax				// Copy test4 value to highest student
		mov eax, [esi].average			// Get the average value from first element obj to highest
		mov[edi].average, eax			// Copy average value to highest student
		mov al, [esi].passing			// Get the passing value from first element obj to highest
		mov[edi].passing, al			// Copy passing value to highest student

		mov ebx,0						// Set index to 0
		mov ecx, ARRAY_SIZE				// Set loop counter to number of elements in array
		lp2:							// Second loop label
			push ecx					// Hold loop counter in stack
			fld [edi].average			// Load the highest students average for comparison
			fld [esi + ebx].average		// Load the current element student average for comparison
			fcomi ST(0), ST(1)			// Is the current student's average greater than the highest
			jb L1						// No, jump to skip
			push ebx					// Yes continue; hold ebx
			mov edx, esi				// Get esi address
			add edx, ebx				// Add index
			mov ebx, 0					// Set index to 0
			mov ecx, 3					// Loop counter to get all 12 bytes

			lp3:						// Third loop label
				mov eax, DWORD PTR[edx + ebx]// Get a dword size from first struct
				mov DWORD PTR[edi + ebx], eax// Copy to highest
				add ebx, 4				// Next 4 bytes
			loop lp3					// loop instruction
			pop ebx						// Set ebx back

			mov eax, [esi + ebx].test1	// Get the test1 value from current element obj to highest
			mov[edi].test1, eax			// Copy test1 value to highest student
			mov eax, [esi + ebx].test2	// Get the test2 value from current element obj to highest
			mov[edi].test2, eax			// Copy test2 value to highest student
			mov eax, [esi + ebx].test3	// Get the test3 value from current element obj to highest
			mov[edi].test3, eax			// Copy test3 value to highest student
			mov eax, [esi + ebx].test4	// Get the test4 value from current element obj to highest
			mov[edi].test4, eax			// Copy test4 value to highest student
			mov eax, [esi + ebx].average// Get the average value from current element obj to highest
			mov[edi].average, eax		// Copy average value to highest student
			mov al, [esi + ebx].passing	// Get the passing value from current element obj to highest
			mov[edi].passing, al		// Copy passing value to highest student

			L1:							//Jump label if not greater
			pop ecx						// Set ecx back
			fstp ST(0)					// Clear fps
			fstp ST(0)					// Clear fps
			add ebx, [TYPE theClass] * 13 // Index 52 bytes, the size of each struct
		loop lp2						// Second loop instruction
	}
}