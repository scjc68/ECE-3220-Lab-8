/* Name: Seth John
   Pawprint: scjc68
   ECE 3220 Lab 6 
   Date: 04/02/2018 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Signal
{
	private:
		
		
		
	public:
		double length;
		double average;
		double max_val;
		double min_val;
		vector<double>rawData;
		vector<double>newData;
		double getaverage();
		double getmax_val();
		double getmin_val();
		Signal(); //default constructor to zero 
		Signal(int filenum);  //constructor
		Signal(string filename); //constructor 
		~Signal(); //destructor
		void get_offset(double offset);
		void get_scale(double scale) throw(int,char);      //specified exception
		void get_center();
		void get_normal();
		void get_stats();
		void save_file(string output);
		void sig_info();
		void operator+(double offset); //decided to use this type of function to manage signals better
		void operator*(double scale);  //this in turn allowed me to use "this->" capabilities 
};

class myClass
{
	private:
	
	public:
	void message() 
	{
		cout << "\nERROR! The length of the files are not the same." << endl;
	}
};

Signal::Signal() // default constructor 
{
	rawData={0};
	newData={0};
	length=0;
	average=0;
	max_val=0;
	min_val=0;
}

Signal::Signal(int filenum) //parametric constructor 
{
	std::ifstream myfile;
	char filename[50];
	double ctrl;
	int i=0;
	length=0;
	string line; 
	int rando=sprintf(filename,"Raw_data_%02d.txt",filenum); //uses file num to open a select file
	myfile.open(filename);
	
	try
	{
		if(!myfile.is_open())
		{
			throw 1;                                          //used to throw integer if file is not open
		}
	}
	catch(int j)
	{
		cout << "ERROR! File could not be opened." << endl;  //used to check if file was opened
		cout << "RE-THROW is being used!" << endl;
		throw;                                               //used to rethrow
	}
	
	myfile >> length;  //reads in correct values
	myfile >> max_val;
	myfile.ignore( 1,'\n');
	
	for(i=0; i<length; i++)
	{
		getline(myfile, line);
		rawData.push_back(atof(line.c_str()));
		newData.push_back(rawData[i]);
		//cout << "Read the data for " << i << " : " << rawData[i] << endl; //error checking 
	}
	
	myfile.close();
	//average=getaverage(); //gets average
	//max_val=getmax_val();
	//min_val=getmin_val();
	
	average = 0;
	// max_val = 0;
	// min_val = 0;
}


Signal::Signal(string filename) //parametric constructor
{
	std::ifstream myfile; //ifstream allows to read in from file
	string line;
	int i=0;
	myfile.open(filename); //opens the file with the name set by the user
	
	try
	{
		if(!myfile.is_open())
		{
			throw 1;                                          //used to throw integer if file is not open
		}
	}
	catch(int j)
	{
		cout << "ERROR! File could not be opened." << endl;  //used to check if file was opened
		cout << "RE-THROW 2 is being used!" << endl;
		throw;                                               //used to rethrow
	}
	
	
	myfile >> length;
	myfile >> max_val;
	myfile.ignore( 1,'\n');
	
	for(i=0; i<length; i++)
	{
		getline(myfile, line);
		rawData.push_back(atof(line.c_str()));
		newData.push_back(rawData[i]);
		//cout << "Read the data for " << i << " : " << rawData[i] << endl; //error checking 
	}
	myfile.close();
	//average=getaverage();
	//max_val=getmax_val();
	//min_val=getmin_val();
	
	average=0;
	// max_val = 0;
	// min_val = 0;
}

void Signal::operator+(double offset)
{
	int i=0;
	for(i=0;i<length;i++)
	{
		newData[i]+=offset; //offset is added to each vector value
	}
}

void Signal::operator*(double scale)
{
	int i=0;
	for(i=0;i<length;i++)
	{
		newData[i]*=scale; //multiply scale by each vector value
	}
}

Signal::~Signal() //destructor 
{
	//delete 
}

double Signal::getaverage() //find the average
{
	average=0.0;
	int i=0;
	for(int i=0;i<length;i++)
	{
		average+=newData[i]; //totals all values in signal
	}
	if(length==0)
	{
		return 0; //in case of empty vector
	}
	else
	{
		return(average/(double)length);
	}
}

double Signal::getmax_val() //gets the signal max value 
{
	max_val=0.0;
	int i=0;
	
	for(i=0; i<length; i++) //compares each current value to the previous lowest value
	{ 
		if(newData[i]>max_val)
		{
			max_val=newData[i];
		}
	}
	return (max_val);
}

double Signal::getmin_val() //gets the signal min value
{
	min_val=getmax_val();
	int i=0;
	
	for(i=0; i<length; i++) //compares each current value to the previous highest value
	{ 
		if(newData[i]<min_val)
		{
			min_val=newData[i];
		}
	}
	return (min_val);
}

void Signal::get_offset(double offset)
{
	if(length==0)
	{
		throw 1;          //throws int if signal is empty 
	}
	
	this->operator+(offset); //use + operator to add offset
	// for(int i = 0; i<length; i++)
	// {
		// cout << "Offset["<< i << "] -> "<< newData[i] << " by " << offset << endl;
		// newData[i] = newData[i] + offset;
	// }
	average=getaverage();
	max_val=getmax_val();
	min_val=getmin_val();
}

void Signal::get_scale(double scale) throw(int,char)
{
	if(length==0)
	{
		throw 1;                      //throws int if signal is empty 
	}
	if(scale==0)
	{
		throw 'a';                    //throws char because you cannot scale by 0
	}
	
	this->operator*(scale); //use * operator to multiply 
	// for(int i = 0; i<length; i++)
	// {
		// cout << "Scaled["<< i << "] -> "<< newData[i] << " by " << scale << endl;
		// newData[i] = newData[i] * scale;
	// }
	average=getaverage();
	max_val=getmax_val();
	min_val=getmin_val();
}

void Signal::get_stats() //gets the current average, max_value, and min_value 
{
	if(length==0)
	{
		throw 1;                       //throws int if signal is empty 
	}
	
	average=getaverage();
	max_val=getmax_val();
	min_val=getmin_val();
	cout << "Average: " << average << endl << "Maximum: " << max_val << endl << "Minimum: " << min_val << endl;
}

void Signal::get_center()
{
	if(length==0)
	{
		throw 1;                       //throws int if signal is empty 
	}
	
	average=getaverage();
	this->operator+((average*(-1))); //subtracts average from each value
	// for(int i = 0; i<length; i++)
	// {
		// newData[i] -= average;
	// }
	max_val=getmax_val();
	min_val=getmin_val();
}

void Signal::get_normal()
{
	if(length==0)
	{
		throw 1;                       //throws int if signal is empty 
	}
	
	average=getaverage();
	this->operator*((1/max_val)); //divides by max_value
	// for(int i = 0; i<length; i++)
	// {
		// newData[i] /= max_val;
	// }
	max_val=getmax_val();
	min_val=getmin_val();
}

void Signal::sig_info() //signal information is showed
{ 
	if(length==0)
	{
		throw 1;                       //throws int if signal is empty 
	}
	
	average=getaverage();
	max_val=getmax_val();
	min_val=getmin_val();
	// int i=0;   //error checking
	// while(i<length)
	// {
		// cout << "DATA[" << i << "] -> " << rawData[i] << " --> " << newData[i] << endl;
		// i++;
	// }
	cout << "Length: " << length << endl << "Average: " << average << endl << "Maximum: " << max_val << endl << "Minimum: " << min_val << endl;
}

void Signal::save_file(string filename)
{
	if(length==0)
	{
		throw 1;                       //throws int if signal is empty 
	}
	
	int i=0;
	std::ofstream myfile; // ofstream allows to write to file	
	myfile.open(filename); 
	if(!myfile.is_open())
	{
		cout << "ERROR! File could not be opened." << endl;
	}
	
	myfile << length; //used to write the length
	myfile << ' '; //used to write a space char
	myfile << max_val; //used to write the max value
	myfile << char(13) << char(10); //used to write a new line
	for(i=0; i<length; i++)
	{
		myfile << newData[i] << char(13) << char(10); //writes the stored value and then a new line after
	}
	myfile.close();
}

Signal operator+(Signal sig1, Signal sig2) //added for non-member function for adding two objects and making a third object
{
	int i=0;
	Signal sig3;
	
	if(sig1.length == 0)
	{
		throw 'a';                         //throw char if signal is empty 
	}
	if(sig1.length!=sig2.length)
	{
		//cout << "/n/n/n myClass is thrown/n/n/n";
		throw myClass();                 //throw myClass object if signal lengths are not the same
	}
	else
	{
		//cout << sig1.length << " and " << sig2.length << endl;
		sig1.getmax_val();
		sig1.getmin_val();
		sig2.getmax_val();
		sig2.getmin_val();
		sig3.newData.clear();
		sig3.length=sig1.length;
		for(i=0; i<sig1.length; i++)
		{
			// cout << sig3.getaverage() << endl;
			// cout << sig3.getmax_val() << endl;
			// cout << sig3.getmin_val() << endl;
			sig3.newData.push_back(sig1.newData[i]+sig2.newData[i]);
			cout << sig3.newData.at(i) << endl;
		}
		
	}
	if(sig1.max_val>sig2.max_val)
	{
		sig3.max_val=sig1.max_val;
	}
	else
	{
		sig3.max_val=sig2.max_val;
	}
	cout << sig3.max_val << " is the signal 3 max value" << endl;
	
	//sig3.average=((sig1.average+sig2.average)/2);
	
	
	//cout << sig3.average << endl;
	// cout << sig3.getaverage() << endl;
	// cout << sig3.getmax_val() << endl;
	// cout << sig3.getmin_val() << endl;
	
	return sig3;
}

int main(int argc, char* argv[])
{
	int filenum=0;
	int i=1, stop=1, option=0;
	Signal sig1, sig2, sig3; // signal pointer 
	double offset=0.0,  scale=0.0;
	string output;
	string filename2;
	
	if(argc==1) //if no command line arguments
	{ 
		Signal zero;
		sig1=zero;
	}
	else
	{
		if((argv[i][0]=='-')&&(argv[i][1]=='n'))
		{
			i++;
			if(argv[i]==NULL) // checks if file num is after the -n 
			{ 
				cout << "ERROR! Needs File Number." << endl;
				return 0;
			}
			
			filenum=std::atoi(argv[i]);
			if(filenum<=0) // checks if file num is not equal to or less than 0
			{ 
				cout << "ERROR! File number cannot be negative." << endl;
				return 0;
			}
			
			try
			{
				Signal sig(filenum);
				sig1=sig;
			}
			catch(int s)
			{
				cout << "ERROR!! File could not be found." << endl;   //used to catch rethrow from constructor
				return 0;
			}
			
			//Signal sig(filenum);
			//Signal sigNumb2(filenum);
			//sig1=sig; // sets the pointer to the address of the signal created 
			//sig2=sigNumb2;
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='f'))
		{
			i++;
			if(argv[i]==NULL) 
			{ 
				cout << "ERROR! Needs File Name." << endl;
				return 0;
			}
			
			try
			{
				string filename(argv[i]); //used to copy input file name into filename variable
				Signal sig(filename); //used to call parametric constructor that handles filename
				sig1=sig; 
			}
			catch(int s)
			{
				cout << "ERROR!! File could not be found." << endl;   //used to catch rethrow from constructor
				return 0;
			}
			
			//string filename(argv[i]); // copies input file name into filename variable
			//Signal sig(filename); // calls parametric constructor that handles filename
			//Signal sigNumb2(filename);
			//sig1=sig; 
			//sig2=sigNumb2;
		}	
		else //checks if wrong command line arguments
		{ 
			cout << "ERROR! Command line inputs were invalid." << endl;
			return 0;
		}
	}
	
	while(stop==1) //reprints menu and new selections
	{ 
		cout << endl << "Please select a action to execute:" << endl
		<< "1.) Offset:" << endl
		<< "2.) Scale:" << endl
		<< "3.) Statistics:" << endl
		<< "4.) Center:" << endl
		<< "5.) Normalize:" << endl
		<< "6.) Signal Info:" << endl
		<< "7.) Save Into File:" << endl
		<< "8.) Add Two Objects:" << endl
		<< "9.) Terminate Program" << endl
		<< "Option:  ";
		
		cin >> option;
		
		switch(option)
		{
			case 1:
				try
				{
					offset=0.0;
					cout << "Please enter a value to offset the signal by: ";
					cin >> offset;
					sig1.get_offset(offset);
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
			
			case 2:
				try
				{
					scale=0.0;
					cout << "Please enter a value to scale the signal by: ";
					cin >> scale;
					sig1.get_scale(scale);
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				catch(...)              //catch all handler is used here to catch char thrown if the scale is 0
				{
					cout << "\nERROR!! You cannot have a scale of 0" << endl;
				}
				break;
			
			case 3:
				try
				{
					cout << "The statistics are ..." << endl;
					sig1.get_stats();
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
			
			case 4:
				try
				{
					cout << "Signal is being centered." << endl;
					sig1.get_center();
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
				
			case 5:
				try
				{
					cout << "Signal is being normalized." << endl;
					sig1.get_normal();
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
			
			case 6:
				try
				{
					cout << "The Signal Information is ..." << endl;
					sig1.sig_info();
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
			
			case 7:
				try
				{
					cout << "Please enter the name you want for the output file:" << endl;
					cin >> output; //reads in string for file name 
					sig1.save_file(output);
				}
				catch(int r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				break;
			
			case 8:
				try
				{
					cout << endl << "If the second file entered does not exist, object 2 will be set to all zeros due to default constructor." << endl;
					cout << "Please enter the name of the file you want to use for object 2: ";
					cin >> filename2;
					Signal sigNumb2(filename2);
					sig2=sigNumb2;
					
					// if(sig2.getmax_val()==0)      // Cannot use this due to default constructor always being set to zero and if file contains all zeros
					// { 
						// cout << "ERROR! There is no file by this name." << endl;
						// break;
					// }
					
					cout << "\nThe result of two objects being added using a non-member function:" << endl;
					sig3=sig1+sig2;
					cout << "Length: " << sig3.length << endl << "Average: " << sig3.getaverage() << endl << "Maximum: " << sig3.max_val << endl 
						 << "Minimum: " << sig3.min_val << endl;
					// sig2.newData.clear();
					// sig3.newData.clear();
				}
				catch(char r)
				{
					cout << "\nERROR!! Operation cannot be performed on an empty signal." << endl;
				}
				catch(myClass &Cat)
				{
					Cat.message();                         //used to call class method that prints error message
				}
				catch(...)
				{
					cout << "\nFile did not exist. Please proceed with a different option." << endl;
				}
				break;
			
			case 9:
				cout << "Program Terminated." << endl;
				return 0;
				break;
			
			default:
				cout << "ERROR! Option does not exist. Please choose from the following options listed." << endl;
				break;
		}
	}
	return 0;
}