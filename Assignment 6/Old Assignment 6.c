/*****************************************************************************************
/*  Title:  Assignment 6
/*  Author:  Stephen Vanderende
/*  Class:  COMP 2717
/*  Date:  02/28/12
/****************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define MAXCHAR 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stackNode
{
	char *sData;
	struct stackNode *pNext;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

StackNodePtr pStack = NULL;

void readFile( void );
void writeFile( void );
void reverse( char *sString );
void push( StackNodePtr *pTop, char *sFileData );
char* pop( StackNodePtr *pTop );

int main( void )
{ 
	readFile();
	writeFile();

   return 0;
}

// Read the data from the input.txt file.
void readFile( void )
{
	FILE *cfPtr; 

   // fopen opens file; exits program if file cannot be opened 
   if ( ( cfPtr = fopen( "input.txt", "r" ) ) == NULL ) 
   {
      printf( "File could not be opened\n" );
   }
   else
   {
	   int iStringLength = 0;
	   char sFileString[ MAXCHAR ];
	   char *pString;
	   
	   fgets( sFileString, MAXCHAR, cfPtr );
	
	   while( !feof( cfPtr ) )
	   {
		   pString = (char*) malloc (sizeof(sFileString));
		   
		   if( pString != NULL )
		   {
			   iStringLength = strlen(sFileString);
			   iStringLength--;
			   sFileString[iStringLength] = '\0';
			   strcpy(pString, sFileString);
			   reverse(pString);
			   push( &pStack, pString);
			   fgets( sFileString, MAXCHAR, cfPtr );
		   }
		   else
		   {
			   printf( "%s not inserted. No memory available.\n", sFileString );
		   }
	   }
   }
   
   fclose( cfPtr ); // fclose closes the read file

}

// Write the reverse string data to the output.txt file.
void writeFile( void )
{
	FILE *cfPtr;

   // fopen opens file. Exit program if unable to create file 
   if ( ( cfPtr = fopen( "output.txt", "w" ) ) == NULL )
   {
      printf( "File could not be opened\n" );
   }
   else
   {
	   while(pStack != NULL)
	   {
		   char *pElement = NULL;
		   pElement = pop(&pStack);
		   printf("%s\n", pElement);
		   fprintf( cfPtr, "%s\n", pElement);
		   free(pElement);
	   }
	   fclose( cfPtr );
   }
}

// Reverse the characters in the string read from the input.txt file.
void reverse( char *sString )
{
	char temp;
	int iCount;
	int iStringLength = strlen(sString);

	for(iCount = 0; iCount < iStringLength/2; iCount++)
	{
		temp = sString[iCount];
		sString[iCount] = sString[iStringLength - iCount - 1];
		sString[iStringLength - iCount - 1] = temp;	
	}
}

// Push the string data on to the stack.
void push( StackNodePtr *pTop, char *sFileData )
{ 
   StackNodePtr pNew;

   pNew = ( StackNodePtr ) malloc( sizeof( StackNode ) );

   if ( pNew != NULL )
   {   
      pNew->sData = sFileData;
      pNew->pNext = *pTop; // insert at top of stack
      *pTop = pNew;
   }
   else
   {
      printf( "%s not inserted. No memory available.\n", &sFileData );
   }
}

// Pop the string data off the stack.
char* pop( StackNodePtr *pTop )
{
	StackNodePtr pTemp;
	char *sPopValue;

    pTemp = *pTop; // attach a pointer to element to be removed
    sPopValue = ( *pTop )->sData; 
    *pTop = ( *pTop )->pNext; // remove at top of stack

	free(pTemp);
    
	return sPopValue;
}
