/*-----------------------------------------------------------
 Programmer : Andrew S. Jacobson
 Date : February 27, 2020
 Description : This program performs several functions with
	an array filled with user input. This program
	should work with any size array.
-------------------------------------------------------------*/

#include <iostream>
using namespace std;

const unsigned int ARRAY_SIZE = 6; // Declare global constant value ARRAY_SIZE

void getNums(unsigned int[]); //prototype
void printNums(unsigned int[]); //prototype
int getAverage(unsigned int[]); //prototype
void add100(unsigned int[]); //prototype
void rotateNums(unsigned int[]); //prototype

int main() {
	unsigned int nums[ARRAY_SIZE], average; //Initialize array of nums and variable average
	
	getNums(nums);
	average = getAverage(nums);
	printNums(nums);
	cout << endl << "Average is " << average << endl;
	add100(nums);
	average = getAverage(nums);
	printNums(nums);
	cout << endl << "Average is " << average << endl;
	rotateNums(nums);
	printNums(nums);
}

/* ------------------------------------------------------------
 This function allows the user to enter values for the array
 ------------------------------------------------------------ */
void getNums(unsigned int nums[])
{
	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << "Enter element " << i << " of the array:";
		cin >> nums[i];
	}
}

/* ------------------------------------------------------------
 This function allows the user to print the values of the array
 ------------------------------------------------------------ */
void printNums(unsigned int nums[])
{
	cout << "Printing array..." << endl;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		cout << nums[i] << " ";
	}
}

/* -------------------------------------------------------------------------------
 This function allows the user get back the average of the values fromo the array
 --------------------------------------------------------------------------------- */
int getAverage(unsigned int nums[])
{
	unsigned int average = 0;

	__asm
	{
		mov ecx, ARRAY_SIZE //set ecx register from the array size
		mov esi, [nums] // Address of first element in array moved to esi register

		lp1: //label for loop instruction
			mov eax, [esi] // Dereference the address and move value to the eax register
			add esi, [TYPE nums] // Move the address up the number of BTYEs to get the next element
			add [average], eax // Add the element value to the average variable
			loop lp1 // loop instruction

		mov ebx, 0 // Set ebx register to 0 for a counter
		mov eax, [average] // Hold the sumation of the array 

		bot: // Label for jump instruction
			sub eax, ARRAY_SIZE // Division using subtraction, Total of sumation being subtracted by the array size
			jc top // jump carry flag, jump label
 			inc ebx // increment ebx register value for average
			jmp bot // jump instruction for loop

		top: // Label for jc instruction
			mov [average], ebx // move the final average value into the average variable

	}
	return average;
}

/* -----------------------------------------------------
 This function will add 100 to each element of the array
 ------------------------------------------------------- */
void add100(unsigned int nums[])
{
	__asm
	{
	mov ecx, ARRAY_SIZE // Set ecx register counter by the array size
	mov esi, [nums]	// Address of first element in array moved to esi register
	lp1 : //label for loop instruction
		mov eax, [esi] // Dereference the address and move value to the eax register
		add eax, 100 // Add 100 to the dereferenced value in the eax register
		mov [esi], eax // move value in eax register to esi 
		mov [nums], esi // Move value to nums element address
		add esi, [TYPE nums] // Add to get to next element in nums array
		loop lp1 // Loop instruction
	}
}

/* -------------------------------------------------------------------------------------------
 This function will modify the array contents by moving each element to the index on its right
 --------------------------------------------------------------------------------------------- */
void rotateNums(unsigned int nums[])
{
	__asm
	{
		mov esi, [nums] // Address of first element in array moved to esi register
		mov ecx, ARRAY_SIZE // Set ecx register counter by the array size
		mov eax, [esi] // Hold the first element place holder

		lp1 :
			mov edx, [esi] // Move the dereferenced value to the edx register
			mov [esi], eax // move the element to the array element address
			mov eax, edx // Switch the values held inn the registers
			add esi, [TYPE nums] // Add Bytes to the array address to get to the next element
			loop lp1 // Loop instruction to label
	
		mov esi, [nums] //Move array of first element to esi register
		mov [esi], eax // Move last array value to the first array address
	}
}
