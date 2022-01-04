/* ------------------------------------------------------------
 Programmer : Andrew S. Jacobson
 Date : April 16, 2020
 Description : Project 2 - This program performs several functions with
 an array filled with user input. This program
should work with any size array
 ------------------------------------------------------------ */

#include <iostream>
#include <string>
using namespace std;

int getLength(char[]);					//prototypes
void makeLowerCase(char[], int);			//This is a logical order to write and test the functions
bool equals(char[], int, char[], int);
void getLast(char[], int, char[], int);
int countVowels(char[], int);
void removeRepeats(char[], int, char[]);


int main()
{
	char str1[100] = "Man! This %$#& ASSEMBLY stuff is NEAT 12345!",	//These are C-strings
		str2[100] = "Don't look BACK",							//C doesn't have an actual string type
		str3[100] = "Don't look BAC!",							//So it treats char arrays as "strings"
		str4[100] = "Don't look back",		//Declaring them this way puts a terminating 0 at the end
		str5[100] = "Don't look back",
		str6[100] = "aaa   b cccc         d     eeeeee  f",
		str7[100] = "Nothing like programming",
		str8[100];
	int vowels;

	cout << "Test #1 is        : " << getLength(str1) << endl;	//test the getLength() function
	cout << "Test #1 should be : 44" << endl << endl;
    
	makeLowerCase(str1, getLength(str1));						//Test the makeLowerCase() function
	cout << "Test #2 is        : " << str1 << endl;
	cout << "Test #2 should be : man! this %$#& assembly stuff is neat 12345!" << endl << endl;
    
	if (equals(str2, getLength(str2), str3, getLength(str3)))	//Test the equals() function several ways
		cout << "Test #3 failed" << endl << endl;
	else
		cout << "Test #3 passed" << endl << endl;

	if (equals(str2, getLength(str2), str4, getLength(str4)))
		cout << "Test #4 failed" << endl << endl;
	else
		cout << "Test #4 passed" << endl << endl;

	if (equals(str4, getLength(str4), str5, getLength(str5)))
		cout << "Test #5 failed" << endl << endl;
	else
		cout << "Test #5 passed" << endl << endl;
   
	getLast(str7, getLength(str7), str8, 11);					//Test the getLast() function
	cout << "Test #6 is        : " << str8 << endl;
	cout << "Test #6 should be : programming" << endl << endl;
    
	vowels = countVowels(str1, getLength(str1));				//Test the countVowels() function
	cout << "Test #7 is        : " << vowels << endl;
	cout << "Test #7 should be : 8" << endl << endl;
    
	removeRepeats(str6, getLength(str6), str8);					//Test the removeRepeats() function
	cout << "Test #8 is        : " << str8 << endl;
	cout << "Test #8 should be : a b c d e f" << endl << endl;
   
}

/* ------------------------------------------------------------
 getLength
 Description: Gets the length of an string. (or in this case a C-String)
 Receives: A c-string/char array address
 Returns: The length of the string
 Requires: None
 ------------------------------------------------------------ */
int getLength(char text[])
{
    int stringLen = 0;       // Local variable
    __asm {
        mov esi,[text]       // Get the address for manipulation

        lp1:                 // Loop label
            mov al,BYTE PTR [esi]// Get a byte size from the string which is a single char
            cmp al,0             // Is the char equal to zero; the terminated 0
            je L1                // Yes, Jump out of loop
            add [stringLen],1    // No, increment the the length
            add esi,1            // Increment through the string
        jmp lp1              // Jump instruction to loop

        L1:                  // Label to break out of loop
    }
	return stringLen;        // Return the string length
}

/* ------------------------------------------------------------
 makeLowerCase()
 Description: Makes just the upper case letter to lower case
 Receives: A C-string address, the length of the array
 Returns: None
 Requires: getLength has to run first
 ------------------------------------------------------------ */
void makeLowerCase(char text[], int len)  
{
    __asm {
        mov esi, [text]         // Get the address for manipulation
        mov ecx, len            // Set the loop counter to the string length

        lp1:                    // Loop label
            mov al,BYTE PTR [esi]   // Get a byte size from the string which is a single char
            cmp al,65               // Is the char greater than or equal to 65 ('A')
            jae L1                  // Yes, jump for next test
            jmp skip                // No, jump to skip to next element
            L1:
                cmp al,90           // Is the char less than or equal to 90 ('Z')
                jbe L2                  // Yes, jump for computation
                jmp skip                // No, jump to skip to next element since it is not an upper case letter
            L2: 
                or al,00100000b     // OR the char to change the 5th bit to 1 which changes to the lower case
                mov BYTE PTR[esi],al    // Move the new lower case letter in place of the upper case in string
            skip:                   // Skip label
                add esi,1               // Increment through the string
        loop lp1                // Loop instruction to label
    }
}

/* ------------------------------------------------------------
 equals()
 Description: Test to see if two c-strings are exactly the same.
 Receives: Two c-strings and their lengths
 Returns: A boolean if it does not match.
 Requires: getLength has to run first
 ------------------------------------------------------------ */
bool equals(char firstText[], int firstLen, char secondText[], int secondLen)
{
    bool finalBool;             // Local variable for return
    __asm {     
        mov eax,[firstLen]      // Get the first string length
        cmp eax,[secondLen]     // Check if both string lengths are the same
        jne skip                // If not than end function

        mov esi,[firstText]     // Get the first address for manipulation
        mov ecx,[firstLen]      // Set loop counter to the string length
        mov edi,[secondText]    // Get the second address for manipulation

        lp1:                    // Loop label
            mov al,BYTE PTR[esi]    // Get a byte size from the first string which is a single char
            mov ah,BYTE PTR[edi]    // Get a byte size from the second string which is a single char
            cmp al,ah               // Are they not equal
            jne L1                  // Yes, jump to label
            mov [finalBool],0       // It is equal so set to false
            jmp skip                // Skip to next element

            L1:                     // Label if not equal
                mov [finalBool],1       // It is not equal set to true
                jmp skip                // Skip to next element
        
            skip:                   // Skip label
                add esi,1               // Increment through first string
                add edi,1               // Increment through second string
        loop lp1                // Loop instruction
    }
	return finalBool;           // Return the boolean
}

/* ------------------------------------------------------------
getLast()
 Description: Set a string equal to another string of a certain length
 Receives: A filled string and its length, an empty string and the number of chars to get
 Returns: None
 Requires: getLength has to run first
 ------------------------------------------------------------ */
void getLast(char text[], int len, char newT[], int lastNum)
{
    __asm {
        mov eax,[len]       // Get first string length
        cmp eax,[lastNum]   // Check if requested chars is greater than string length
        jb skip             // If it is greater than end function

        sub eax, [lastNum]  // Subtract length with the number requested
        mov esi,[text]      // Get the first address for manipulation
        add esi, eax        // Start the address at the requested point
        mov edi,[newT]      // Get a byte size from the second string which is a single char
        mov ecx,[lastNum]   // Set loop counter based on the requestion amount of chars

        lp1:                // Loop label
            mov eax,[esi]   // Get element value from string
            mov [edi],eax   // Set element value to new string
            add esi,1       // Increment through first string
            add edi,1       // Increment through second string
        loop lp1            // Loop instruction
        skip:               // To skip out
    }
}

/* ------------------------------------------------------------
 countVowels()
 Description: Count the number of vowels
 Receives: String and the length of the string
 Returns: The number vowels in the string
 Requires: getLength has to run first
 ------------------------------------------------------------ */
int countVowels(char text[], int len)
{
    int totalVowel = 0;                     // Local variable 
    int vowels[5] = { 97,101,105,111,117 }; // Array of vowels
    int* Aptr = vowels;                     // Pointer of vowel array
    __asm {
        mov esi,[text]          // Get the address of the string
        mov ecx,[len]           // set the loop counter to the length of the string

        lp1:                    // Outer loop label
            mov al,BYTE PTR [esi]   // Get a byte size from the string which is a single char
            push ecx                // Push the outer loop counter to the stack to save it
            mov ecx,5               // Set the inner loop counter to 5 for vowels array
            mov edi, [Aptr]         // Set edi to the start of the vowels array

            lp2:                    // Inner loop label
                mov bl,[edi]            // Get element of the vowels array
                cmp al,bl               // Is the string char equal to a vowel
                je L1                   // Yes, jump out of loop to label to set total
                add edi, [TYPE vowels]  // Increment through vowel array
            loop lp2                // Inner loop instruction
            jmp L2                  // Jump to skip

            L1:                     // First jump label
                add [totalVowel],1      // Add total vowel count

            L2:                     // Second jump label
                pop ecx                 // Pop the original outer loop counter to ecx
                add esi,1               // Increment through string
        loop lp1                // Outer loop instruction
    }

	return totalVowel;          // Return the vowel count
}

/* ------------------------------------------------------------
 removeRepeats()
 Description: Copies string to a new string leave out repeating chars
 Receives: A string and its length, another string
 Returns: None
 Requires: None
 ------------------------------------------------------------ */
void removeRepeats(char text[], int len, char newT[])
{
    __asm {
        mov esi,[text]              // Get the first address for manipulation
        mov edi,[newT]              // Get the second address for manipulation
        mov ecx,[len]               // Set loop counter to string lengthh

        lp1:                        // Loop label
            mov al,BYTE PTR [esi]       // Get a byte size from the first string which is a single char
            mov bl,BYTE PTR [edi]       // Get a byte size from the second string which is a single char
            cmp al,BYTE PTR [esi + 1]   // Is the first string char equal to the next element char
            je skip                     // If equal then skip to next element
            mov BYTE PTR [edi],al       // If not then move elemennt char to seconnd string
            add edi,1                   // Increment second string
            skip:                       // Jump label to end
                add esi,1                   // Increment through first string
        loop lp1                    // Loop instruction
        mov BYTE PTR[edi],0         // Set terminated 0 at end of string
    }
}
