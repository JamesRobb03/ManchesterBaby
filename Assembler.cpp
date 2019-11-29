#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
using namespace std;

class Line{

	private:
		string operandString;
		string opcodeString;
		string binary;
		string label;
		int lineNo;
		int operandInt;
		string opcodeBin;
		string operandBin;
	public:
		//constructor that initiates all the variables
		Line();
		
		//Getters and Setters
		string getBinary();
		void setBinary(string newBin);
		void setOperandBinary(string newOperandBin);
		string getOperandString();
		int getLineNo();
		string getOpcodeString();
		void setOpcodeString(string newOpcodeString);
		string getLabel();
		string getOpcodeBinary();
		string getOperandBinary();
		void setLabel(string newLabel);Line* lineStore[32];
		void setOpcodeBinary(string newOpcodeBin);
		void setLineNo(int newLineNo);
		
		//string splitter
		void stringSplit(string line);
	
		//destructor
		~Line();
	};

Line::Line()
{
	operandString = "";
	opcodeString = "";
	binary = "";
	label = "";
	lineNo = 0;
	operandInt = 0;
	opcodeBin = "";
	operandBin = "";
}

//destructor
Line::~Line(){	}

//getters and setters
string Line::getBinary(){	return binary;}
void Line::setBinary(string newBin){	binary = newBin;}
void Line::setOperandBinary(string newOperandBin){	operandBin = newOperandBin;}
string Line::getOperandString(){	return operandString;}
int Line::getLineNo(){	return lineNo;}
string Line::getOpcodeString(){	return opcodeString;}
void Line::setOpcodeString(string newOpcodeString){	opcodeString = newOpcodeString;}
string Line::getLabel(){	return label;}
void Line::setLabel(string newLabel){	label = newLabel;}
void Line::setOpcodeBinary(string newOpcodeBin){	opcodeBin = newOpcodeBin;}
void Line::setLineNo(int newLineNo){	lineNo = newLineNo;}
string Line::getOpcodeBinary(){	return opcodeBin;}
string Line::getOperandBinary(){	return operandBin;}

//function which splits a string from a parameter into its compenents
void Line::stringSplit(string line)
{
	//State what we are using as the delimiter of the string
	char delimiter(':');
	string smallLine = "";

	if(line[0] !=';')
	{
		line = line.substr(0, line.find(';'));
		//get the label from the string and remove it from the read in line
		if(line[0]!=' ')
		{
			label = line.substr(0, line.find(delimiter));
			line = line.substr(label.size()+1, line.size());
		}

		//remove all spaces from the line and store it in the smallLine var
		for (int i = 0; i < line.size(); i++)
		{
			if(line[i]!=' ')
			{
				smallLine += line[i];
			}
		}

		//read the instruction from smallLine and store in instruct var
		for(int i=0; i<3; i++)
		{
			opcodeString += smallLine[i];
		}

		//remove instruction from smallLine
		smallLine = smallLine.substr(3,line.size());

		//remove the semicolon from the end of the small line
		//this is the operand of the line
		smallLine = smallLine.substr(0, smallLine.size());
		operandString = smallLine.substr(0, line.find(';'));
	}
}

class Assembler
{
	private:
		string file;
		string store[32];
		Line* lineStore[32];

	public:
		//Reads in the code from a specific file name and saves it to array
		void readInCode(string fileName);

		void assemble();

		//constructs binary strings from an instance of line then passes the binary string to the writeToFile function
		void saveBinary(Line* line);

		void writeToFile(string line);

		string reverseString(string rev);

		int intConversion(string in);

		string binaryConversion(signed long dec, int length);

		string padString(string pad);
		//destructor
		~Assembler();
};

void Assembler::assemble()
{

	for(int i=0; i<32; i++)
	{
		//create a new instance of line and fill it with variables from strings taken from store array
		if(store[i].size()>0)
		{
			lineStore[i] = new Line();
			lineStore[i]->setLineNo(i);
			lineStore[i]->stingSplit(store[i]);
		}
	}

	for(int i=0; i<32; i++){
		if(store[i].size()>0)
		{
			saveBinary(lineStore[i]);
		}
	}	
}


/*
	destructor - loops through line store and deletes instances of line
*/
Assembler::~Assembler()
{
	for(int i=0; i<32; i++)
	{
		delete lineStore[i];
	}
}

/*
	open a file from a string parameter, and reads its contents into the store
*/
void Assembler::readInCode(string fileName)
{
	//set up local variables
	char delimiter(';');
	fstream myfile;
	int i=0;
	string line;
	
	//open a file from user parameter
	myfile.open(fileName.c_str(), ios::out | ios::in );
	
	//loop through file, storing the contents of each line to the store
	if (myfile.is_open()){
  		while(getline(myfile, line)){
  			if(line[0]!=';')
  			{
  				line = line.substr(0, line.find(delimiter)+1);
				store[i] = line;
				i++;
			}
    	}
    	
    //close the file
    myfile.close();
  	}
  	
  	//error handling if file does not exist
  	else{
    cout << "Unable to open file" << endl;
  	}
}

string Assembler::padString(string pad)
{
	string newString = "00000000000000000000000000000000";

	//Adds the given string to the 'newString'
	for(int i=0; i<pad.size(); i++){
		newString[32-pad.size()+i] = pad[i];
	}
	return newString;
}

string Assembler::binaryConversion(signed long decimal, int length)
{
	//The string that will be returned to the user
	string myBinary = "";

	//Catches the exception of the desired number being 0
	if(decimal==0){
		for(int i=0; i<length; i++){
			myBinary += '0';
		}
	//if decimal is positive
	}else if(decimal>0){
		int check = 1;
		for(int i=0; i<length; i++){
			if((check&decimal)>=1){
				myBinary = "1"+myBinary;
			}else{
				myBinary = "0"+myBinary; 
			}
			check <<= 1;
		}
		return myBinary;
	//if decimal is negative
	}else if(decimal<0){
		decimal = decimal*(-1);
		decimal--;
		int check = 1;
		for(int i=0; i<31; i++){
			if((check&decimal)>=1){
				myBinary = "1"+myBinary;
			}else{
				myBinary = "0"+myBinary; 
			}
			check <<= 1;
		}

		myBinary = padString(myBinary);

		int i=0;
		while(myBinary[i]=='0'){
			myBinary[i]='1';
			i++;
		}

		for(int j=i; j<32; j++){
			if(myBinary[j]=='0'){
				myBinary[j] = '1';
			}
			else{
				myBinary[j] = '0';
			}
		}

		return myBinary;
	}
}

int Assembler::intConversion(string in)
{
	int x=0;
	stringstream convert(in);
	convert >> x;
	return x;
}

void Assembler::writeToFile(string line)
{
	//declare and open file
	ofstream myfile;
	myfile.open ("AssemblerOutput.txt", ofstream::out | ofstream::app);
	//write to file using parameter
	myfile << line << endl;
	//close file
	myfile.close();
}

string Assembler::reverseString(string rev){
	string temp;
	//Loops through the given string backwards and saves it as a new string
	for(int i=rev.size(); i>0; i--){
		temp += rev[i-1];
	}
	return temp;
}

/*
	get binary strings from an instance of line then pass string to writeToFile
*/
void Assembler::saveBinary(Line* line)
{
	//get binary for instruction
	if(line->getOpcodeString() == "JMP")
	{
		line->setOpcodeBinary("000");
	}
	if(line->getOpcodeString() == "JRP")
	{
		line->setOpcodeBinary("100");
	}
	if(line->getOpcodeString() == "LDN")
	{
		line->setOpcodeBinary("010");
	}
	if(line->getOpcodeString() == "STO")
	{
		line->setOpcodeBinary("110");
	}
	if(line->getOpcodeString() == "SUB")
	{
		line->setOpcodeBinary("001");
	}
	if(line->getOpcodeString() == "CMP")
	{
		line->setOpcodeBinary("110");
	}
	//if STP exit function
	if(line->getOpcodeString() == "STP")
	{
		line->setOpcodeBinary("111");
		line->setBinary("00000000000001110000000000000000");
		writeToFile(line->getBinary());
		cout << line->getBinary() << endl;
		return;

	}
	if(line->getOpcodeString() == "VAR")
	{
		line->setOpcodeBinary("000");
	}

	int operandLineNo = (-1);

	//find operand label equal to variable label of another line
	for(int i=0; i<32; i++)
	{
		if(store[i].size()>0){
			if((line->getOperandString()).compare(lineStore[i]->getLabel())==0)
			{
				//if operand equals label, store the line number of the variable 
				operandLineNo = lineStore[i]->getLineNo();
			}
		}
	}

	//pass line number to the binaryConversion function and reverse the binary string you receive
	if(operandLineNo!=-1){
		line->setOperandBinary(reverseString(binaryConversion(operandLineNo,13)));
	}else{
		operandLineNo = intConversion(line->getOperandString());
		line->setOperandBinary(reverseString(binaryConversion(operandLineNo,13)));
	}

	//create the binary string from the converted components and pass to writeToFile function
	line->setBinary(line->getOperandBinary() + line->getOpcodeBinary() + "0000000000000000");
	cout << line->getBinary() << endl;
	writeToFile(line->getBinary());
}

int main()
{
	//Create new instance of assembler
	Assembler* assembler = new Assembler();
	
	ofstream myfile;
	myfile.open("AssemblerOutput.txt", ofstream::out | ofstream::trunc);
	myfile.close();

 	string input;
 	cout << "Enter assembler file name: ";
 	getline(cin, input);

	//read in code from file to store
	assembler->readInCode(input);
	
	//Assemble file
	assembler->assemble();

	//delete instance of assembler
	delete assembler;
	return 0;
}