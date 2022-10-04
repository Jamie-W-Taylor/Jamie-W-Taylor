#include <stdio.h>
#include <stdlib.h>
//clang main.c -o output
//./output prog1.o
//This is the help function that reads y86 binary code from a file
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize);

int calculateTotalHexValue(unsigned char memory[], int PC);

int calculateRegister1(int memory);

int calculateRegister2(int memory);

//declaring functions

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

int main(int argc, char **argv)
{

  const unsigned int MAX_MEMSIZE = 4096; //changed to a const as shouldn't be changed
  unsigned char memory[MAX_MEMSIZE]; //This array represents the 4KB memory space
  unsigned int PC = 0;               //This is the initial program counter address

  if (argc < 2)
  {
    printf("Usage: please specify a y86 binary program file in the argument.\n");
    return -1;
  }

  unsigned int program_size = loadBinFromFile(argv[1], memory, MAX_MEMSIZE);

  if (program_size == 0)
    return 0;

  while (PC < program_size)
  {
    //printf("\n%02x", memory[PC]);
    
    switch (memory[PC]){
      //displaying the machine code in the correct formated way, only calls each function when necessary inside the printf statement for efficiency and memory management
      //The most common Operation Types should be at the top of he switch statement to make it more efficient. It is unclear which are used the most but halt is called at least once which is why it is first

      case 0x00:
      printf("halt\n");
      break;

      case 0x90:
      printf("ret\n");
      break;

      case 0x20:
      PC+= 1;      
      printf("rrmovl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x30: 
      PC+= 1;
      printf("irmovl $%d, %s \n", calculateTotalHexValue(memory, PC), register_names[calculateRegister2(memory[PC])]);
      PC+=4;  
      break;

      case 0x40:     
      PC+= 1;    
      printf("rmmovl %s, %d(%s)\n", register_names[calculateRegister1(memory[PC])], calculateTotalHexValue(memory, PC), register_names[calculateRegister2(memory[PC])]);
      PC+=4; 
      break;

      case 0x50:
      PC +=1;
      printf("mrmovl %d(%s), %s\n", calculateTotalHexValue(memory, PC), register_names[calculateRegister2(memory[PC])], register_names[calculateRegister1(memory[PC])]);
      PC +=4;
      break;

      case 0x60:     
      PC +=1;
      printf("addl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x62:     
      PC +=1;
      printf("andl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x63:     
      PC +=1;
      printf("xorl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x70:    
      printf("jmp %u\n", calculateTotalHexValue(memory, PC));
      PC+=4;
      break;

      case 0x71:   
      printf("jle %u\n", calculateTotalHexValue(memory, PC)); 
      PC+=4;
      break;

      case 0x73:   
      printf("je %u\n", calculateTotalHexValue(memory, PC));  
      PC+=4;
      break;

      case 0x74:   
      printf("jne %u\n", calculateTotalHexValue(memory, PC)); 
      PC+=4;
      break;

      case 0x80:   
      printf("call %u\n", calculateTotalHexValue(memory, PC)); 
      PC+=4;
      break;

      case 0xA0:     
      PC +=1;
      printf("pushl %s\n", register_names[calculateRegister1(memory[PC])]);
      break;

      case 0xB0:     
      PC +=1;
      printf("popl %s\n", register_names[calculateRegister1(memory[PC])]);
      break;

      //below opcodes aren't in the tests but are in tasks 1 and 2 so i've decided to implement them below

      case 0x10:
      printf("nop\n");
      break;

      case 0x21:
      PC+= 1;      
      printf("cmovle %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x22:
      PC+= 1;      
      printf("cmovl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x23:
      PC+= 1;      
      printf("cmove %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x24:
      PC+= 1;      
      printf("cmovne %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x25:
      PC+= 1;      
      printf("cmovge %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x26:
      PC+= 1;      
      printf("cmovg %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x61:     
      PC +=1;
      printf("subl %s, %s\n", register_names[calculateRegister1(memory[PC])], register_names[calculateRegister2(memory[PC])]);
      break;

      case 0x72:   
      printf("jl %u\n", calculateTotalHexValue(memory, PC));  
      PC+=4;
      break;

      case 0x75:   
      printf("jge %u\n", calculateTotalHexValue(memory, PC));  
      PC+=4;
      break;

      case 0x76:   
      printf("jg %u\n", calculateTotalHexValue(memory, PC));  
      PC+=4;
      break;

      //default:
      //printf("TODO: undisassembled opcode"); //if input is invalid
      //break; removed default statement due to giving outputs that were unndesired
      
    }

    PC++;
    } 

  return 0;
}


/****************************************************************************
N.B. You do not need to modify or work in this function.
Description:
This function reads in a y86 machine bytecode from file and
store them in an unsigned char array.
******************************************************************************/
unsigned int loadBinFromFile(const char *filename, unsigned char memory[], unsigned int memsize)
{
  unsigned int bytes_read = 0;

  unsigned int file_size = 0;

  FILE *pfile = fopen(filename, "rb");

  if (!pfile)
  {
    printf("Unable to load file %s, please check if the path and name are correct.\n", filename);
    return 0;
  }

  fseek(pfile, 0, SEEK_END);
  file_size = ftell(pfile);
  rewind(pfile);

  if (file_size > memsize)
  {
    printf("Program size exceeds memory size of %d.\n", memsize);
    return 0;
  }

  bytes_read = fread(memory, 1, file_size, pfile);

  if (bytes_read != file_size)
  {
    printf("Bytes read does not match the file size.\n");
    return 0;
  }

  fclose(pfile);

  return bytes_read;
}

int calculateTotalHexValue(unsigned char memory[], int PC)
{

    int Total = 0;
    PC+= 1;
    Total = Total + memory[PC] +(memory[PC + 1] << 8) + (memory[PC + 2] << 16) + (memory[PC + 3] << 24);
    return Total;

}

int calculateRegister1(int memory)
{
   return (memory >> 4); //shifts the first byte to the right byte 4 bits
}

int calculateRegister2(int memory)

{

   return memory & 15; //sets second hex value to a variable

}