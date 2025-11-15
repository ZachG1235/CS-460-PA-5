/*
 * StringUtils.h belong to Michael Leverington but have been re-written 
 * and repurposed for this project. Leverington urges his students (us) to use
 * the framework he provides in future academic assignments. 
*/

#ifndef STRING_UTILS_H
#define STRING_UTILS_H


// header files
#include "StandardConstants.h"
#include <stdio.h>
#include <stdlib.h> // free, malloc

// function implementations


int compareString( const char *oneStr, const char *otherStr);

/*
Name: concatenateString
Process: appends one string onto another
Function Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void concatenateString( char *destStr, const char *sourceStr);

/*
Name: copyString
Process: copies one string into another, 
         overwriting data in the destination string
Function Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void copyString( char *destStr, const char *sourceStr);

/*
Name: findSubString
Process: linear search for given substring within another string
Function Input/Parameters: c-style source string (char *),
                           c-style source search string (char *)
Function Output/Parameters: none
Function Output/Returned: index of found substring, or
                          SUBSTRING_NOT_FOUND constant
                          if string not found
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
int findSubString(const char *testStr, const char *searchSubStr);

/*
Name: getStringConstrained
Process: captures a string from the input stream
         with various constraints
Function Input/Parameters: input stream (FILE *)
                           clears leading non printable (bool),
                           clears leading space (bool),
                           stops at non printable (bool),
                           stops at specified delimiter (char)
                           Note: consumes delimiter
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: fgetc
*/
bool getStringConstrained(
                          FILE *inStream,
                          bool clearLeadingNonPrintable, 
                          bool clearLeadingSpace,
                          bool stopAtNonPrintable,
                          char delimiter, 
                          char *capturedString
                         );

/*
Name: getStringLength
Process: finds the length of a string
         by counting characters up to the NULL_CHAR character
Function Input/Parameters: c-style string (char *)
Function Output/Parameters: none
Function Output/Returned: length of string (int)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
int getStringLength(const char *testStr);

/*
Name: getStringToDelimiter
Process: captures a string from the input stream
         to a specified delimiter;
         Note: consumes delimiter
Function Input/Parameters: input stream (FILE *)
                           stops at specified delimiter (char)
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringConstrained
*/
bool getStringToDelimiter( 
                           FILE *inStream, 
                           char delimiter, 
                           char *capturedString
                         );

/*
Name: getStringToLineEnd
Process: captures a string from the input stream
         to the end of the line;
Function Input/Parameters: input stream (FILE *)
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringConstrained
*/
bool getStringToLineEnd( 
                           FILE *inStream, 
                           char *capturedString
                         );

/*
Name: getSubString
Process: captures sub string within larger string
         between two inclusive indicies.
         returns empty string if either index is out of range, 
         assumes enough memory in destination string
Function Input/Parameters: c-style string (char *), 
                           start and end indices (int)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: getStringLength, malloc, copyString, free
*/
void getSubString( char *destStr, const char *sourceStr, 
                            int startIndex, int endIndex);

/*
Name: setStrToLowerCase
Process: iterates through string, sets any uppercase letter
         to lowercase; no effect on other letters
Function Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: toLowerCase
*/
void setStrToLowerCase(char *destStr, const char *sourceStr);

/*
Name: toLowerCase
Process: if character is uppercase, sets it to lowercase;
         otherwise returns character unchanged
Function Input/Parameters: test character (char)
Function Output/Parameters: none
Function Output/Returned: character to set to lowercase, if appropriate
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
char toLowerCase(char testChar);


#endif 