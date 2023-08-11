/*=============================================================================
| Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Nicholas Donofrio
| Language: c
|
| To Compile: c -> gcc -o Checksum Checksum.c
| 
| To Execute: c -> ./Checksum inputFile.txt 8
|
| Note: All input files are simple 8 bit ASCII input
+=============================================================================*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Global variables
int MAX = 1024;

// Function Prototypes
void printChar(char *str);
unsigned long int calc8bit(char *input);
unsigned long int calc16bit(char *input);
unsigned long int calc32bit(char *input);

// This function will calculate the 8 bit checksum
unsigned long int calc8bit(char *input)
{
  int result = 0;
  
  for (int i = 0; i < strlen(input); i++)
  {
    result += input[i];
  }
  
  return result;
}

// This function will calculate the 16 bit checksum
unsigned long int calc16bit(char *input)
{
  int res16bit = 0;
  
  for (int i = 0; i < strlen(input);)
  {
    res16bit += input[i] << 8;
    res16bit += (input[i + 1]);
    i+=2;
  }

return res16bit;
}

// This function will calculate the 32 bit checksum
unsigned long int calc32bit(char *input)
{
  unsigned long int res32bit = 0;
  
  for (int i = 0; i < strlen(input);)
  {
    res32bit += input[i] << 24;
    res32bit += (input[i + 1]) << 16;
    res32bit += (input[i + 2]) << 8;
    res32bit += (input[i + 3]);
    i+=4;
  }

return res32bit;
}


// This function will print all 80 characters
void printChar(char *str)
{
  // The loop to print string
  for (int i = 0; i < strlen(str); i++)
  {
    // Adds a newline
    if (i % 80 == 0)
    {
      printf("\n");
    }

    // Prints the string
    printf("%c",str[i]);
  }
}


int main(int argc, char **argv)
{
  // Variables
  FILE *inFile;
  char *input, *output, *checksum, c = 'x';

  // Counters for our checksum functions
  unsigned long int res8bit = 0;
  unsigned long int res16bit = 0;
  unsigned long int res32bit = 0;

  // Other counters
  int i = 0; 
  int checksum_size = 0;
   
  // Ensures checksum size is correct
  checksum_size = atoi(argv[2]);

  // Advise the user that the value is incorrect with a message formatted as shown below:
  if (!(checksum_size == 8 || checksum_size == 16 || checksum_size == 32))
  {
    fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
    return -1;
  }
  
  // Opens the input file
  if (!(inFile = fopen(argv[1],"r")))
  {
    fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
    return -1;
  }
  
  // Reads the input file
  input = malloc(sizeof(char) * MAX);
  
  while (fscanf(inFile, "%c", &c) != EOF && i < MAX)
  {
    input[i] = c;
    i++;
  }
  
  input[i] = '\0';
  
  // Close the file
  fclose(inFile);

  // This function will print the checksums correctly
  // 0xff - Prints 2 hex values
  // 0xffff - Prints last 4 hex values
  // 0xfffffff - Prints last 8 hex values
  switch (checksum_size)
  {
    case 8:
    res8bit = calc8bit(input);
    printChar(input);
    printf("\n");
      
    // Use 0xff masking to display only last 2 hex values
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res8bit & 0xff, (int)strlen(input));
    break;
    case 16:
      
    // Pad with a necessary X
    if (strlen(input) % 2)
    {
      strcat(input,"X");
    }
    
    printChar(input);
    printf("\n");
    res16bit = calc16bit(input);
      
    // Use 0xffff masking to display only last 4 hex values
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res16bit & 0xffff, (int)strlen(input));
    break;
    case 32:
      
    // Pad with X
    while (strlen(input) % 4)
    strcat(input,"X");
    printChar(input);
    printf("\n");
    res32bit = calc32bit(input);
      
    // Use 0xffffffff masking to display only last 8 hex values
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res32bit & 0xffffffff, (int)strlen(input));
    break;
  }

return 0;
}
