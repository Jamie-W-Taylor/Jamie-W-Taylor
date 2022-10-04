#define _GNU_SOURCE//to include the getline function
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>//used for testing efficiency 

//This is an array of register mnemonics in y86

const char *register_names[] =

    {

        "%eax",

        "%ecx",

        "%edx",

        "%ebx",

        "%esp",

        "%ebp",

        "%esi",

        "%edi",

        "UNKNOWN_REGSITER"};

 

int convertStrToByteCode(const char *str, unsigned char inst[], int size);

void printInstruction(const int OperationType, unsigned char *instruction);// set as const char as value will never change

int calculateTotalHexValue(unsigned char *instruction);

int calculateRegister1(unsigned char *instruction);

int calculateRegister2(unsigned char *instruction);

 

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

 

   //int start = clock(); was used to test efficiency of code

 

   //This unsigned char array stores an instruction read from the file

   //As the largest y86 instruction is 6 bytes, there are 6 unsigned char in the array where

   //each represents a byte.

   unsigned char instruction[6] = {0, 0, 0, 0, 0, 0}; //set outside while loop to increase the efficiency of the program

 

   while ((read = getline(&line, &len, pFile)) != -1)//changed to read = getline due to being more efficient and faster

  {

    memset(instruction, 0, sizeof(instruction));//using memset to decrease memory usage

    int convertedBytes = convertStrToByteCode(line, instruction, 6);

    printInstruction(instruction[0], instruction); // calling convert function with perameters

  }
 

 

   //int end = clock(); used for efficiency of code

 

   fclose(pFile);

   if (line)

      free(line);//freeing memory

 

   //printf("Took: %d", (end - start)); used for efficiency of code

 

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

 

void printInstruction(const int OperationType, unsigned char *instruction)

{ //function is at the bottom of the code for when it's called

 

   switch (OperationType) // used switch statement rather than if and else s it is quicker and more efficient
   //The most common Operation Types should be at the top of he switch statement to make it more efficient. It is unclear which are used the most but halt is called at least once which is why it is first

   {

   case 0x00:

      printf("halt\n");

      break;

   case 0x10:

      printf("nop\n");

      break;

   case 0x90:

      printf("ret\n");

      break;

   //the three case statements above just print out a string depending on the input

   case 0x60:

      printf("addl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x61:

      printf("subl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x62:

      printf("andl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x63:

      printf("xorl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x20:

      printf("rrmovl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x21:

      printf("cmovle %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x22:

      printf("cmovl %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x23:

      printf("cmove %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x24:

      printf("cmovne %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x25:

      printf("cmovge %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

   case 0x26:

      printf("cmovg %s, %s\n", register_names[calculateRegister1(instruction)], register_names[calculateRegister2(instruction)]);

      break;

//the above case statements print out a string and a value from the registar_names array depending on the second byte value

   case 0x30:

      printf("irmovl $%d, %s \n", calculateTotalHexValue(instruction), register_names[calculateRegister2(instruction)]);

      break;

         //the above case statements print out the Total_Hex_Value calculated in the if and else statements earlier and prints it depending on the first byte of the instruction. it also prints out the fourth hex value as a registar names

   case 0x40:

      printf("rmmovl %s, %d(%s)\n", register_names[calculateRegister1(instruction)], calculateTotalHexValue(instruction), register_names[calculateRegister2(instruction)]);

      break;

   //the above case statements prints out the registar names depending on the first hex value then the Total_Hex_Value then finally the registar names again depending on the second hex value

   case 0x50:

      printf("mrmovl %d(%s), %s\n", calculateTotalHexValue(instruction), register_names[calculateRegister2(instruction)], register_names[calculateRegister1(instruction)]);

      break;

   case 0x70:

      printf("jmp %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x71:

      printf("jle %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x72:

      printf("jl %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x73:

      printf("je %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x74:

      printf("jne %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x75:

      printf("jge %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x76:

      printf("jg %u\n", calculateTotalHexValue(instruction));

      break;

   case 0x80:

      printf("call %u\n", calculateTotalHexValue(instruction));

      break;

   //the above case statements print out the Total_Hex_Value calculated in the if and else statements earlier and prints it depending on the first byte of the instruction

   case 0xA0:

      printf("pushl %s\n", register_names[calculateRegister1(instruction)]);

      break;

   case 0xB0:

      printf("popl %s\n", register_names[calculateRegister1(instruction)]);

      break;

      //the above case statements only print out the first hex value of the 2nd byte
   default:

      printf("TODO: undisassembled opcode"); //if input is invalid

   break;

   }

}

 

int calculateTotalHexValue(unsigned char *instruction)

{
  int x = 1; //default set x to 1

   if (instruction[0] == 0x40 | instruction[0] == 0x30 | instruction[0] == 0x50)

   { // if the first byte of the hexadecimal value x is equal to these parameters x = 2

      x = 2;

   }

   return instruction[x] + (instruction[x + 1] << 8) + (instruction[x + 2] << 16) + (instruction[x + 3] << 24);

}

 

int calculateRegister1(unsigned char *instruction)

{

   return (instruction[1] >> 4); //shifts the first byte to the right byte 4 bits

}

 

int calculateRegister2(unsigned char *instruction)

{

   return instruction[1] & 15; //sets second hex value to a variable

}