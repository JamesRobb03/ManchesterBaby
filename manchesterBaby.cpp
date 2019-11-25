#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class ManchesterBaby
{

	public:
		//constructor & deconstructor
		ManchesterBaby();
		~ManchesterBaby();

		void init();
		int convertToDecimal(int binary[]);
		void convertToBinary(int decimal);

		bool load();

		void display();

		void getInstructions();
		int fetch();
		int decode();
		int execute();

		void JMP();
		void JRP();
		void LDN();
		void STO();
		void SUB();
		void CMP();
		void STP();
};

int ManchesterBaby::convertToDecimal(int binary[])
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
void ManchesterBaby::convertToBinary(int decimal)
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
