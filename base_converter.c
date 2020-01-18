/*
* Number base converter
* @Author: Freezing
* @Date: 18/01/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 20

/*
* Checks if number in the string corresponds with it's symbols for the given base
*/
int validateNumber ( char * n, int base )
{
  int value = 0;
  int len = strlen ( n );
  for ( int i = 0; i < len; i++ )
  {
    if ( n[i] == '\0' )
      break;
    // validation for bases 2 - 10
    if ( base <= 10 )
    {
      if ( n[i] < '0' || ( n[i] > '0' + (base - 1) ) )
        return 0;
    }
    // validation for bases 11 - 36
    if ( base > 10 )
    {
      if ( base == 11 )
      {
        if ( n[i] < '0' || ( n[i] > '9' && n[i] != 'A' && n[i] != 'a' ) )
          return 0; 
      }
      else 
      {
        if ( n[i] < '0' || ( n[i] > '9' && 
        ( n[i] < 'A' || ( n[i] > 'A' + (base - 11) &&
        ( n[i] < 'a' || n[i] > 'a' + (base - 11) ) ) ) ) )
          return 0; 
      }
    }
    value += (n[i] - '0');
  }
  // check if number is not zero
  if ( value == 0 )
    return 0;
  return 1;
}
/*
* Function that reads input from user through stdin
*/
int handleInput ( char * n1, int * b1, int * b2 )
{
  printf ( "Write number, it's base and a new base:\n" );
  if ( scanf ( "%20s %d %d", n1, b1, b2 ) != 3
      || *b1 < 2 || *b1 > 36 || *b2 < 2 || *b2 > 36 || ! validateNumber ( n1, *b1 ) )
    return 0; 
}
/*
* Converts given number of base N from string to decimal and stores it into another string
*/
void toDecimal ( char * n, int base, char * converted )
{
  int decimalValue = 0;
  int power = 0;
  int len = strlen ( n ) - 1;
  for ( int i = len; i >= 0; i-- )
  {
    if ( n[i] > '9' )
    {
      if ( n[i] > 'Z' )
        decimalValue += (n[i] - 'a' + 10 ) * pow ( (double) base, (double) power );
      else
        decimalValue += (n[i] - 'A' + 10 ) * pow ( (double) base, (double) power );
    }
    else
    {
      if ( n[i] > 0 )
        decimalValue += (n[i] - '0') * pow ( (double) base, (double) power );
    }
    power++;
  }
  sprintf ( converted, "%d", decimalValue );
}
/*
* Converts decimal base number to base N number
*/
void decimalToBaseN ( char * n1, int base, char * n2 )
{
  char remain [32];
  int remainNum;
  int result;
  int index = 0;
  int n2index = 0;
  sscanf ( n1, "%d", &result );
  while ( result > 0 )
  {
    remainNum = result % base;
    if ( remainNum < 10 )
      remain[index] = remainNum + '0';
    else 
      remain[index] = remainNum + 55;
    result /= base;
    index++;
  }
  for ( int i = index - 1; i >= 0; i-- )
  {
    n2[n2index] = remain[i];
    n2index++;
  }
}
/*
* Wrapper conversion function that uses clean and readable logic
*/
int convertNumbers ( char * n1, char * n2, int b1, int b2 )
{
  char number [MAX_LENGTH];
  if ( b1 == b2 )
    return 0;
  if ( b1 == 10 )
    decimalToBaseN ( n1, b2, n2 );
  else
  {
    toDecimal ( n1, b1, n2 );
    if ( b2 != 10 )
      decimalToBaseN ( n2, b2, n2 );
  }
  return 1;
}
/* Simple void function that prints the results (completely unnecessary, but it was a fun thing to do xd) */
void printResults ( char * n1, char * n2, int b1, int b2 )
{
  printf ( "%s in base %d == %s in base %d", n1, b1, n2, b2 );
}
/* Main function */
int main()
{
    char n1 [MAX_LENGTH+1];
    char n2 [MAX_LENGTH+1];
    int b1, b2, input;
    
    // read input
    input = handleInput ( n1, &b1, &b2 );
    if ( ! input )
    {
      printf ( "Wrong input.\n" );
      return 1;
    }
    
    // number conversion
    if ( ! convertNumbers ( n1, n2, b1, b2 ) )
    {
      printf ( "Conversion failed - both bases are equal.\n" );
      return 2;
    }
    
    // show result
    printResults ( n1, n2, b1, b2 );
    return 0;
}
