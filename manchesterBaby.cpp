#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;


#define SIZE 32

class ManchesterBaby
{

	public:
		//Variables
		int Store[SIZE][SIZE];
		int Accumulator[SIZE];
		int CI[SIZE]; // holds a number which is an address.
		int PI[SIZE]; // holds a number which is an opcode. (plus an operand in soe cases)


		//constructor & deconstructor
		ManchesterBaby();
		~ManchesterBaby();

		int convertToDecimal(int binary[]);
		void convertToBinary(int decimal, int binary[]);

		bool load();

		void display(); //harry

		void getInstructions();
		int fetch();
		int decode();
		int execute();

		void JMP();
		void JRP();
		void LDN();
		void STO(int addressToStore); //skye
		void SUB();
		void CMP();
		void STP();
};

ManchesterBaby::ManchesterBaby(){
	cout<<"Creating Manchester Baby."<<endl;
	//init arrays
	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			Store[i][j] = 0;
		}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		Accumulator[i] = 0;
		CI[i] = 0;
		PI[i] = 0;
	}

	cout<<"Manchester Baby Created and Initialised"<<endl;
}

ManchesterBaby::~ManchesterBaby(){
  cout<<"\n Manchester Baby Stopped"<<endl;
}

//load program from file into memory (store)
bool ManchesterBaby::load()
{
  string fileline;
  ifstream file;
  file.open("assembleroutput.txt");

  if (file.fail())
  {
    //the open failed 
    cout << "ERROR: Could not open the file assembleroutput.txt" << endl;
    return false;
  }

  cout << "Loading program from assembler into memory..." << endl;

   int lines = 0;
      
    //loop through lines of file
    while(getline(file, fileline))
    {

      lines++;  

      // GITHUB Example starts at i = 5 
      // first 5 bits are the OPERAND? But I'm still putting it in the store here
      for(int i=0; i < SIZE; i++)
      {
        char binary = fileline.at(i);
        if(binary=='1')
        {
          Store[lines][i]= 1;
        }
        else
        {
          Store[lines][i]= 0;
        }
      }


      cout << "Stored: " << fileline << endl;
    
    }
	
    file.close();
    return true;
}

void ManchesterBaby::display()
{

}

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
void ManchesterBaby::convertToBinary(int decimal, int binary[])
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

//needs tested once everything else done 
//STO - store memory address in the store 
void ManchesterBaby::STO(int addressToStore)
{
  cout << "Store memory address: " << addressToStore << endl;

  
  cout << "Memory is at address: ";
  //loop through store and assign
  for (int i =0; i < SIZE; i++)
  {
    Store[addressToStore][i] = Accumulator[i];
    //cout <<  Store[addressToStore][i] << endl;
  }

}
