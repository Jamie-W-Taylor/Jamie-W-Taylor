#define _GNU_SOURCE//to include the getline function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertStrToByteCode(const char *str, unsigned char inst[], int size);

void initialiseLookupTable(char * lookupTable[]);
//initializing functions

#define SIZE_OF_MAP 256 // defining map size to 255 as this is the max value that can be addressed by a byte in the array
#define UNKNOWN_OP_TYPE "?"

int main(int argc, char **argv)

{

   FILE *pFile = NULL;

   char *line = NULL;

   size_t len = 0;

   size_t read;

 

   if (argc < 2)

   {

      pFile = fopen("./test1.txt", "r");

   }

   else

   {

      pFile = fopen(argv[1], "r");

   }

 

   if (pFile == NULL)

   {

      printf("Error open test file, please make sure they exist.\n");

 
  
      return 0;

   }
   unsigned char instruction[6] = {0, 0, 0, 0, 0, 0};
   char * lookupTable[SIZE_OF_MAP]; //declaring lookuptable
   initialiseLookupTable(lookupTable);//all set outside while loop to increase the efficiency of the program

 while ((read = getline(&line, &len, pFile)) != -1)//changed to read = getline due to being more efficient and faster
  {
    memset(instruction, 0, sizeof(instruction));//using memset to decrease memory usage

    

    convertStrToByteCode(line, instruction, 6); // this function returns an invalid instruction if this is the last line and it not 00 or blank
    // do this once in the app   


    int codeToLookup = instruction[0];
    


    codeToLookup = instruction[0];
    if (lookupTable[codeToLookup] != UNKNOWN_OP_TYPE)
      {

        printf("%s\n", lookupTable[codeToLookup]);

      }
    else

      {

        printf("TODO: undisassembled opcode (%x)\n", codeToLookup);

      }

  }
  

  fclose(pFile);

   if (line)

      free(line);//freeing memory


  return 0;
}

/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function converts a line of machine code read from the text file
into machine byte code.
The machine code is stored in an unsigned char array.
******************************************************************************/
int convertStrToByteCode(const char *str, unsigned char inst[], int size)

{

   int numHexDigits = 0;

   char *endstr;

   //Each instruction should consist of at most 12 hex digits

   numHexDigits = strlen(str) - 1;

   //Convert the string to integer, N.B. this integer is in decimal

   long long value = strtol(str, &endstr, 16);

 

   int numBytes = numHexDigits >> 1;

   int byteCount = numHexDigits >> 1;

 

   while (byteCount > 0)

   {

      unsigned long long mask = 0xFF;

      unsigned long shift = (numBytes - byteCount) << 3;

 

      inst[byteCount - 1] = (value & (mask << shift)) >> shift;

      byteCount--;

   }

 

   //Return the size of the instruction in bytes

   return numHexDigits >> 1;

}

void initialiseLookupTable(char * lookupTable[]) {
  //setting the hexadecimal code equal to a str value which can be printed out when the hex value is the first byte of the instruction
  
  // Initialise the array to all point to the unknown op type so we can detect an invalid op code

    int i = 0;

    for (i = 0; i < SIZE_OF_MAP; i++)

    {

        lookupTable[i] = UNKNOWN_OP_TYPE;

    }
    lookupTable[0x00]="halt";
    lookupTable[0x10]="nop"; 
    lookupTable[0x20]="rrmovl";
    lookupTable[0x21]="cmovle";
    lookupTable[0x22]="cmovl";
    lookupTable[0x23]="cmove";
    lookupTable[0x24]="cmovne";
    lookupTable[0x25]="cmovge";
    lookupTable[0x26]="cmovg";
    lookupTable[0x30]="irmovl";
    lookupTable[0x50]="mrmovl";
    lookupTable[0x40]="rmmovl";
    lookupTable[0x70]="jmp";
    lookupTable[0x71]="jle";
    lookupTable[0x72]="jl";
    lookupTable[0x73]="je";
    lookupTable[0x74]="jne";
    lookupTable[0x75]="jge";
    lookupTable[0x76]="jg";
    lookupTable[0x80]="call"; 
    lookupTable[0x60]="addl";
    lookupTable[0x61]="subl";
    lookupTable[0x62]="andl";
    lookupTable[0x63]="xorl";
    lookupTable[0x90]="ret";
    lookupTable[0xA0]="pushl";
    lookupTable[0xB0]="popl";   
    
}
