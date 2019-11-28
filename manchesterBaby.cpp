#include <iostream>
#include <string>
#include <stdio.h>
#include<fstream>
#include <sstream>

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
    bool runStatus = true;

    //constructor & deconstructor
    ManchesterBaby(); //james
    ~ManchesterBaby();//james

		int convertToDecimal(int binary[], int size); //skye
		void convertToBinary(int decimal, int binary[]);//skye

		bool load(); //skye

    void display(); //harry

    void incrementCI(); //skye

		void fetch(int); //james
		int decode(int); //james
    int getOperand(int);//james
		int execute(); //harry

		void JMP(int);//skye
		void JRP(); //skye
		void LDN(int); //james
		void STO(int); //skye
		void SUB(); 
		void CMP(); 
		void STP(); //james
};

ManchesterBaby::ManchesterBaby(){
	cout<<"Creating Manchester Baby."<<endl;
	//init arrays

  //create store
	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			Store[i][j] = 0;
		}
	}

  //create Accumulator, ci and pi
	for (int i = 0; i < SIZE; ++i)
	{
		Accumulator[i] = 0;
		CI[i] = 0;
		PI[i] = 0;
	}

	cout<<"Manchester Baby Created and Initialised"<<endl;

}

ManchesterBaby::~ManchesterBaby(){
  cout<<"\nManchester Baby Stopped"<<endl;
}


//load program from file into memory (store)
bool ManchesterBaby::load()
{
  string fileline;
  ifstream file;
  file.open("BabyTest1-MC.txt");

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

      lines++; 
      cout << "Stored: " << fileline << endl;
    
    }
  
    file.close();
    return true;
}

void ManchesterBaby::display()
{

}

int ManchesterBaby::convertToDecimal(int binary[], int size)
{

  int decimal = 0;


  for (int i=0; i<size; i++)
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
    int k = decimal >>i;
    if (k & 1)
    {
      binary[i] = 1;
    }else{
      binary[i] = 0;
    }
  }

  //use this to make it read right to left 
  //reverse(binary, binary+SIZE);

}

void ManchesterBaby::fetch(int address){

  cout<<"Fetching address: "<<address<<endl;
  cout<<"PI: ";
  for (int i = 0; i < SIZE; ++i)
  {
    PI[i] = Store[address][i];
    cout<<PI[i];
  }
  cout<<""<<endl;
}

//returns a number between 0-7. instruction depends on the number.
int ManchesterBaby::decode(int address){
  cout<<"Decoding address: "<<address<<endl;
  int Opcode[] = {PI[13], PI[14], PI[15]};
  int returnOpcode = convertToDecimal(Opcode, 3);
  cout<<"Opcode = "<<returnOpcode<<endl;
  return returnOpcode;

}
//function which gets the operand.
int ManchesterBaby::getOperand(int address){
  cout<<"Getting Operand of address: "<<address<<endl;
  int Operand[] = {PI[0], PI[1], PI[2], PI[3], PI[04]};
  int returnOperand = convertToDecimal(Operand, 5);
  cout<<"Operand = "<<returnOperand<<endl;
  return returnOperand;
}

//needs tested once everything else done 
//STO - store memory address in the store 

void ManchesterBaby::STO(int addressToStore)
{
  cout << "Store accumulator at: " << addressToStore << endl;
  
  cout << "Stored: ";
  //loop through store and assign
  for (int i =0; i < SIZE; i++)
  {
    Store[addressToStore][i] = Accumulator[i];
    cout <<  Store[addressToStore][i];
  }
  cout << endl;
}

//CI = S 
//set CI to content of Store location  
void ManchesterBaby::JMP(int location)
{
  cout<<"JMP - setting CI to content of Store at "<<location<<endl;
 
  for (int i =0; i < SIZE; i++)
  {
    CI[i] = Store[location][i];
  }
  cout<<"CI: ";
  for (int i =0; i < SIZE; i++)
  {
    cout << CI[i];
  }
  cout << endl;

}

//load accumulator with negative form of store content
//uses two compliment to make negative. flips the bits then adds 1.
void ManchesterBaby::LDN(int address){

  cout<<".....USING LDN....."<<endl;
  
  //adds flipped bits to accumulator
  for (int i = 0; i < SIZE; ++i)
  {
    if (Store[address][i] == 1)
    {
      Accumulator[i] = 0;
    }else{
      Accumulator[i] = 1;
    }
  }
  
  //converts accumulator to decimal and then adds one to it.
  int afterFlip = convertToDecimal(Accumulator, SIZE);
  afterFlip++;

  //converts negative decimal value to binary array
  convertToBinary(afterFlip, Accumulator);

  //prints out final accumulator
  cout<<"Accumulator = ";
  for (int i = 0; i < SIZE; ++i)
  {
    cout<<Accumulator[i];
  }
  cout<<""<<endl;
}

//functions which stops the baby from running
void ManchesterBaby::STP()
{
  runStatus = false;
}



int main(int argc, char const *argv[])
{
  ManchesterBaby myBaby;
  myBaby.load();
  for (int i = 0; i < 10; ++i)
  {
    cout<<" "<<endl;
    myBaby.fetch(i);
    myBaby.decode(i);
    myBaby.getOperand(i);
    myBaby.LDN(i);
    cout<<" "<<endl;
  }
  
  return 0;
}
