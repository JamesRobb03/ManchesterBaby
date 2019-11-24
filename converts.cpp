
#include <bitset>
#include <algorithm> //for reverse()
#include <iostream>

//assuming the binaries are 32 long in manc baby
#define SIZE 32
using namespace std;


//array for binary result in convertToBinary
int binary[SIZE];


//pass in binary array to convert - should be SIZE (32) items long
int convertToDecimal(int binary[])
{

  int decimal = 0;


  for (int i=0; i<SIZE; i++)
  {
    // for each binary number 
    if (binary[i] == 1)
    {
      int equivallent;
      //find the decimal equivallent from position i
      if (i == 0)
      { 
        equivallent = 1;
      }
      else
      {
        //to the power of 
        equivallent = 2 << (i-1);
      }
      if (binary[i] == 1)
      {
        decimal = decimal + equivallent;
      }

    }

  }

  return decimal;

}


//binary converter to store decimal numbers as binary in the global variable for future functions to use
void convertToBinary(int decimal)
{

  //add the remainers to array
  for (int i=0; i<SIZE; i++)
  {
   if (decimal != 0)
   {
    // %2 gets remainder of dividing by 2
    binary[i]=decimal%2;
   
    decimal = decimal /2;
   }
   else
   {
    //add 0 to make up the size
    binary[i]=0;
   }
  }

  //use this to make it read right to left 
  //reverse(binary, binary+SIZE);

}

int main()
{
  //SIZE is defined at top of file

  cout << "Reading from left to right:" << endl << endl;

  //convert to decimal test 

  //32 bits long to match SIZE
  //if want to convert a smaller binary change SIZE constant
  int binaryInput[] = {1,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int decimalOutput = convertToDecimal(binaryInput);

  

  //print results
  for(int i =0; i < SIZE; i ++)
  {
    cout << binaryInput[i];
  }

  cout << " converted to decimal is: " << decimalOutput << endl;


  //convert to binary test
  int decimalInput = 83;
  convertToBinary(decimalInput);


  //print results
  cout << decimalInput << " converted to binary is: ";

  for (int i = 0; i < SIZE; i++)
  {
    cout << binary[i];
  }

  cout << endl;

  return 0;
}