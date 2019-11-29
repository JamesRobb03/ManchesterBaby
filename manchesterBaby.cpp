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
		void convertToBinary(int decimal, int binary[]);//james

		bool load(); //skye

    void display(); //harry

    int incrementCI(); //skye

		void fetch(int); //james
		int decode(int); //james
    int getOperand(int);//james
		int execute(int, int); //james

		void JMP(int);//skye
		void JRP(int); //skye
		void LDN(int); //james
		void STO(int); //skye
		void SUB(int);//james 
		void CMP(); //harry
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
  cout << "Store" << endl; 
  cout << "     Operand                                Opcode   " << endl;
  cout << "     ==============|=======================|========|==============================================|" <<  endl;
  cout << "     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 " << endl;

  for(int i = 0; i < 32; i++)
  {
    if((i)<10)
      cout << " " << (i) << "  ";
    else
      cout << " " << (i) << " ";

    for(int c = 0; c < 32; c++)
    {
      if(Store[i][c] == 0)
        cout << " o ";
      else if(Store[i][c] == 1)
        cout << "\x1B[32m X \033[0m";

    }
    cout << endl;
  }
  cout << endl;

  //Accumulator display
  cout << "            Operand                                Opcode   " << endl;
  cout << "            ==============|=======================|========|==============================================|" <<  endl;
  cout << "            1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 " << endl;

  cout << "Accumulator ";
  for(int i = 0; i < 32; i++)
  {
      if(Accumulator[i] == 0)
        cout << " o ";
      else if(Accumulator[i] == 1)
        cout << "\x1B[32m X \033[0m";
  }
  cout << endl;

  cout << "     Operand                                Opcode   " << endl;
  cout << "     ==============|=======================|========|==============================================|" <<  endl;
  cout << "     1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 " << endl;

  cout << " CI ";
  for(int i = 0; i < 32; i++)
  {
      if(CI[i] == 0)
      {
        cout << " o ";
      }
      else if(CI[i] == 1)
      {
        cout << "\x1B[32m X \033[0m";
      }
  }
  cout << endl;

  if(runStatus == true)
  {
    cout << " PI ";
    for(int i = 0; i < 32; i++)
      {
          if(PI[i] == 0)
          {
  
            cout << " o ";
          }
          else if(PI[i] == 1)
          {
  
            cout << "\x1B[32m X \033[0m";
          }
      }
  }
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

int ManchesterBaby::incrementCI(){
  int CIdec = convertToDecimal(CI, SIZE);
  CIdec++;
  convertToBinary(CIdec, CI);
  return CIdec;
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
  if (returnOpcode == 0)
  {
    cout<<"Opcode = JMP"<<endl;
  }
  else if (returnOpcode == 1)
  {
    cout<<"Opcode = JRP"<<endl;
  }
  else if (returnOpcode == 2)
  {
    cout<<"Opcode = LDN"<<endl;
  }
  else if (returnOpcode == 3)
  {
    cout<<"Opcode = STO"<<endl;
  }
  else if (returnOpcode == 4)
  {
    cout<<"Opcode = SUB"<<endl;
  }
  else if (returnOpcode == 5)
  {
    cout<<"Opcode = SUB"<<endl;
  }
  else if (returnOpcode == 6)
  {
    cout<<"Opcode = CMP"<<endl;
  }
  else if (returnOpcode == 7)
  {
    cout<<"Opcode = STP"<<endl;
  }

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

int ManchesterBaby::execute(int opcode, int operand){
  
  if (opcode == 0)
  {
    JMP(operand);
  }
  else if (opcode == 1)
  {
    JRP(operand);
  }
  else if (opcode == 2)
  {
    LDN(operand);
  }
  else if (opcode == 3)
  {
    STO(operand);
  }
  else if (opcode == 4)
  {
    SUB(operand);
  }
  else if (opcode == 5)
  {
    SUB(operand);
  }
  else if (opcode == 6)
  {
    CMP();
  }
  else if (opcode == 7)
  {
    STP();
  }
  return 0;
}
  

//needs tested once everything else done 
//STO - store memory address in the store 

void ManchesterBaby::STO(int addressToStore)
{

  cout<<".....USING STO....."<<endl;
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

//CI = CI + S 
//add the content of the store at specified address to the CI
void ManchesterBaby::JRP(int address)
{
  cout<<".....USING JRP....."<<endl;
  cout<<"CI before = ";
  for (int i =0; i < SIZE; i++)
  {
    cout << CI[i];
  }
  cout << endl;
  cout<<"Store line before = ";
  for (int i =0; i < SIZE; i++)
  {
    cout << Store[address][i];
  }
  cout << endl;

  //to hold the negative values
  int negativeCI[SIZE];
  int negativeS[SIZE];

  int toggledCI;
  int toggledS;

  //result of adding
  int result;

  //check if the MSB (RIGHT bit in this case) is 1 or 0 

  /* 4 cases: CI negative, S negative
              CI negative, S positive
              CI positive, S negative
              CI positive, S positive
  */

  //if 1 the value is negative - need to toggle, add 1
  if (CI[SIZE-1] == 1)
  {
    //toggle
    for(int i=0; i<SIZE; i++)
    {
      if (CI[i] == 1)
      {
        negativeCI[i] = 0;
      }
      else
      {
        negativeCI[i] = 1;
      }
    }
    //add 1
    toggledCI = convertToDecimal(negativeCI, SIZE);
    toggledCI++;

    //check if S is negative 
    if (Store[address][SIZE-1] == 1)
    {
      //toggle
      for(int i=0; i<SIZE; i++)
      {
        if (Store[address][i] == 1)
        {
          negativeS[i] = 0;
        }
        else
        {
          negativeS[i] = 1;
        }
      }
      //add 1
      toggledS = convertToDecimal(negativeS, SIZE);
      toggledS++;

      //add the 2 negatives
      result = -toggledCI - toggledS;

    }
    else //CI negative, S positive
    {
      int decimalS = convertToDecimal(Store[address], SIZE);

      //add negative CI and positive
      result = -toggledCI + decimalS;
    }
  }
  else //CI positive
  {
    int decimalCI = convertToDecimal(CI, SIZE);

    //check if S is negative 
    if (Store[address][SIZE-1] == 1)
    {
      //toggle
      for(int i=0; i<SIZE; i++)
      {
        if (Store[address][i] == 1)
        {
          negativeS[i] = 0;
        }
        else
        {
          negativeS[i] = 1;
        }
      }
      //add 1
      toggledS = convertToDecimal(negativeS, SIZE);
      toggledS++;

      //add the positive CI and negative S
      result = decimalCI - toggledS;
    }
    else //S positive
    {
      int decimalS = convertToDecimal(Store[address], SIZE);

      //add positive CI and S
      result = decimalCI + decimalS;
    }
  }


  //convert result to binary to assign to CI
  //check if result is negative
  if (result < 0)
  {
      int binaryResult[SIZE];
      convertToBinary(result, binaryResult);
      int toggledResult[SIZE];
      //toggle
      for (int i=0; i<SIZE;i++)
      {
        if (binaryResult[i] == 1)
        {
          toggledResult[i] = 0;
        }
        else
        {
          toggledResult[i] = 1;
        }
      }
      //add 1
      int decimalResultToggled = convertToDecimal(toggledResult, SIZE);
      decimalResultToggled++;

      convertToBinary(decimalResultToggled, CI);

  }
  else
  {
    convertToBinary(result, CI);
  }


  cout<<"CI = ";
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

//subtract content of Store location from Accumulator
void ManchesterBaby::SUB(int address){ 
  cout<<".....USING SUB....."<<endl;
  //gets the decimal version of the store value.
  int tempStore[SIZE];

  for (int i = 0; i < SIZE; ++i)
  {
    tempStore[i] = Store[address][i];
  }
  int storeDec = convertToDecimal(tempStore, SIZE);

  //gets the decimal version of the accumulator.
  int AccuDec = convertToDecimal(Accumulator, SIZE);

  //prints out values
  cout<<"STORE VALUE = "<<storeDec<<endl;
  cout<<"ACCUMULATOR VALUE = "<<AccuDec<<endl;
  AccuDec = AccuDec - storeDec;
  cout<<"ACCUMULATOR AFTER SUBTRACTION = ";

  convertToBinary(AccuDec, Accumulator);
  for (int i = 0; i < SIZE; ++i)
  {
    cout<<Accumulator[i];
  }

  cout<<""<<endl;

}

void ManchesterBaby::CMP()
{
  cout<<".....USING CMP....."<<endl;
  int AccuDec = convertToDecimal(Accumulator, SIZE);
  if (AccuDec < 0)
  {
    cout << "CI BEFORE"
    for (int i =0; i < SIZE; i++)
    {
      cout << CI[i];
    }
    int CIdec = convertToDecimal(CI, SIZE);
    CIdec++;
    convertToBinary(CIdec, CI);
    cout << "CI AFTER"
    for (int i =0; i < SIZE; i++)
    {
      cout << CI[i];
    }
  }
  else
  {
    cout <<"CI NOT NEGATIVE"
  }
}

//functions which stops the baby from running
void ManchesterBaby::STP()
{
  cout<<".....STP....."<<endl;
  runStatus = false;
}

int main(int argc, char const *argv[])
{
  ManchesterBaby myBaby;
  myBaby.load();
  while(myBaby.runStatus == true){
    cout<<" "<<endl;
    int index = myBaby.incrementCI();
    myBaby.fetch(index);
    int opcode = myBaby.decode(index);
    int operand = myBaby.getOperand(index);
    myBaby.execute(opcode, operand);
    myBaby.display();
    cin.get();
    
  }

  return 0;
}
