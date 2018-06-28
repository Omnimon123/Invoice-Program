//*****************************************************************************************
//  Program Filename   : Soumen_Nath_Invoice
//  Version            : 1.00
//  Author             : Sounmen Nath
//  Purpose            : To demonstrate the ability to crete an invoice program
//  Date               : 2017-01-20
//  Input from         : Keyboard
//  Output to          : Screen
//*****************************************************************************************

//Preprocessor Directives
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Function Declarations
void welcome(); 
void account();
void option();
void review();
string cFile();
string uInputH();
void uInputD();
void cTax(string);
void invoice(string);
void goodbye();

//Global Variables
vector <int> acNum; //vector that stores the account number
vector <string> fName; //vector that stores the filenames
ofstream wFile; //a stream of class ofstream to write to files
ifstream rFile; //a stream of class ifstream to read the contents of the files
string file; //string that stores the contents of this file
int infinite=0; //string that is used to make the program infinite
int userOption; //string that stores th user's option
int aNum=1; //variable that stores the account number that is assigned to new users
char answer; //variable that stores the user's answer
int inNum; //variable that stores the user's invoice number
int aNumber; //variable that stores the user's account number
float subtotal=0; //variable that stores the subtotal
float shipping=0; //variable that stores the user's shipping costs


//Name Constant Definitions
//*****************************************************************************************
// Function Name: main
// Purpose: main function of program
// Inputs to Function: N/A
// Outputs from Function: N/A
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
int main()
{
	system ("color 4d"); //changes the background and text colour
    //variable Declarations
    //variables that store the values that are returned to main
    string temVal;
    string temVal2;
    //Function Body
	do //infinite loop
	{
	    //call on functions in the following order
		welcome();
		account();
		//while the user's option is yes
		while (answer=='y')
		{
		    opt: //the program runs from here when it reaches the goto statement
			option(); //call on this function
			if (userOption==1) //if the user's option is 1 then call on the review function 
			{
				review();
			}
			else if (userOption==2) //if the user's option is 2 then call on the following funcions to create an invoice
			{
				temVal=cFile(); //store the variable that was returned from cFile in temVal
				temVal2=uInputH(); //store the variable that was returned from uInputH in temVal2
				uInputD();
				cTax(temVal2); //pass temVal2 into cTax
				invoice(temVal); //pass temVal into invoice
			}
			else if (userOption==3) //if the user's option is 3 then call on the goodbye function and break the loop
			{
				goodbye();
				break;
			}
		} 
		while (answer == 'n') //while the uer's answer is no call on the following funcions to create an invoice
		{
			temVal=cFile(); 
			temVal2=uInputH();
			uInputD();
			cTax(temVal2);
			invoice(temVal);
			//sets the user's answer to y
			answer='y';
			goto opt; //go to the placed marked as opt
		} 		
	} while (infinite==0);
	
    return 0;
}
//end function main


//Name Constant Definitions
//*****************************************************************************************
// Function Name: welcome
// Purpose: to welcome the user to the program
// Inputs to Function: N/A
// Outputs from Function: N/A
// External Inputs to Function: N/A
// External Outputs from Function: cout
//*****************************************************************************************
void welcome()
{
	cout<<"Hello and welcome to Merivale Books!"<<endl<<endl; //Display the cout statement in quotations
}
//end function welcome


//Name Constant Definitions
//*****************************************************************************************
// Function Name: account
// Purpose: to determne wheter or not the user has an existing account
// Inputs to Function: N/A
// Outputs from Function: return
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
void account()
{
    //display the following statement in quotations
	cout<<"Do you already have an existing account?\nPress y for yes or n for no: ";
	cin>>answer; //accept the user input
	cout<<endl;
	//while the user's answer is not one of the correct letters then he or she will be asked to enter their answer again
	while (answer !='y' && answer !='n')
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter your answer again: ";
		cin>>answer;
		cout<<endl;
	}
	//while the user's answer is not a letter then he or she will be asked to enter their answer again
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter your answer again: ";
		cin>>answer;
		cout<<endl;
	}
	//if the user's answer is yes 
	if (answer =='y')
	{
		cout<<"Please enter your account number: "; //display the statement in quotations
		cin>>aNumber; //accept the uer's input
		cout<<endl;
		//search for the account number that the user entered in the vector that stores all the account numbers
		while (infinite==0)
		{
		    //if the account number is in the vector then diplay the statement in quotations and break the loop
			if (find(acNum.begin(), acNum.end(), aNumber) != acNum.end())
			{
				cout<<"\nWelcome back user "<<aNumber<<endl;
				break;
			}
			//if the account number is not in the vector then ask the user to enter the account number again
			else 
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout<<"Error! Please enter your account number again: ";
				cin>>aNumber;
				cout<<endl;
			}	
		}
			
	}
	else if (answer =='n') //if the user's answer in no
	{
		//the user is assigned an account number
		cout<<"Your account number is "<<aNum<<endl;
		aNum++;
		cout<<"\nPlease enter your account number: "; //the user is asked to enter the account number
		cin>>aNumber;
		cout<<endl;
		//if the user did not enter a number then he or she will be asked to enter the account number again
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter your account number again: ";
			cin>>aNumber;	
			cout<<endl;
		}
		acNum.push_back(aNumber); //the account number is stored in the  acNum vector
	}
}
//end function account


//Name Constant Definitions
//*****************************************************************************************
// Function Name: option
// Purpose: to allow the user to choose one of these options
// Inputs to Function: N/A
// Outputs from Function: N/A
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
void option()
{
	//display the statement in quotations
	cout<<"Options: "<<endl;
	cout<<"Press 1 to view a previous invoice: "<<endl;
	cout<<"Press 2 to create a new invoice: "<<endl;
	cout<<"Press 3 to exit"<<endl;
	cout<<"Please enter one of the options above: ";
	cin>>userOption; //accpet user input
	cout<<endl;	
	//while the user's input is not in the correct range he or she will be asked to enter their option again
	while (userOption<1 || userOption>3)
	{
		cout<<"Error! Please enter your option again: ";
		cin>>userOption;
		cout<<endl;
	}
	//while the user's input is not a letter then he or she will be asked to enter their option again
	while (!cin.good())
	{
		cout<<"Error! Please enter your option again: ";
		cin>>userOption;
		cout<<endl;
	}	
}
//end function option


//Name Constant Definitions
//*****************************************************************************************
// Function Name: review
// Purpose: to allow the user to view a previous invoice
// Inputs to Function: N/A
// Outputs from Function: N/A
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
void review ()
{
	int strike=0; //variable that increases if the user input is not in the fName vector
	int invoiceNum; //variable that stores the invoice number
	string fileName2; //string that stores the file name
	cout<<"Please enter the invoice number (4 Digits) of the invoice you wish to review: "; //display the statements in quotations
	point: //this is the place that the program will run from when it reache the goto statement
	cin>>invoiceNum; //accept user input
	cout<<endl;
	//while the user's input in not a number then he or she will be asked to enter the invoice number again
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter the invoice number again: ";
		goto point; //makes the program run from point
	}
	//while the invoice number is not a four digit number the user will be asked to enter the invoice number again
	while (invoiceNum<1000 || invoiceNum>9999)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter the invoice number again: ";
		goto point; //makes the program run from point
	}
	//the invoice number is added to the filename string
	ostringstream st1;
	st1<<invoiceNum;
	fileName2=st1.str()+".txt";
	for (int j=0; j<fName.size(); j++)
	{
		//if the invoice number that was entered is in the vector that stores all the file names then
		if (fileName2==fName[j])
		{
			rFile.open(fName[j].c_str()); //open the file in read mode
			while (rFile)
			{
				getline (rFile, file); //read the information from this file
				cout<<file<<endl; //display the invoice to the user
			}
			rFile.close(); //close the file
		}
		else //if the invoice number that was entered is not in the vector that stores all the file names then
	    {
			strike++; //increase the value of strike by 1
		}
	}
	if (strike==fName.size()) //if the value of strike is equal to the size of the vector then the user must enter the invoice number again
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter the invoice number again: ";
			goto point; //makes the program run from point
		}
}
//end function review


//Name Constant Definitions
//*****************************************************************************************
// Function Name: cFile
// Purpose: to create a file using the invoice number
// Inputs to Function: N/A
// Outputs from Function: return
// External Inputs to Function: cin
// External Outputs from Function: cout
//*****************************************************************************************
string cFile()
{
	string fileName; //string that stores the filename
	cout<<"Please enter the invoice number (4 Digits): "; //displays the statement in quotations
	cin>>inNum; //accepts the user input
	cout<<endl; 
	//while the invoice number is not a four digit number then the user will be asked to enter the invoice number again
	while (inNum<1000 || inNum>9999)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter the invoice number again: ";
		cin>>inNum;
		cout<<endl;
	}
	//while the invoice number is not a  number  then the user will be asked to enter the invoice number again
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"Error! Please enter the invoice number again: ";
		cin>>inNum;
		cout<<endl;
	}
	//the invoice number is added to the fileName string
	ostringstream st;
	st<<inNum;
	fileName = st.str() + ".txt";
	fName.push_back(fileName); //The file name is stored in the fName vector
	wFile.open(fileName.c_str()); //A file is opened in write mode and its name is the value in the fileName string
	return fileName; //the fileName variable is returned to main
} 
//end function cFile


//Name Constant Definitions
//*****************************************************************************************
// Function Name: uInputH
// Purpose: to accept the user's input and write this information to the file
// Inputs to Function: N/A
// Outputs from Function: return
// External Inputs to Function: cin
// External Outputs from Function: cout, wFile
//*****************************************************************************************
string uInputH()
{
	//Variable Declarations
	//string that stores the province initials
	string initials = "Province\t\tInitials\nAlberta\t\t\tAB\nBrithish Columbia\tBC\nManitoba\t\tMB\nNew Brunswick\t\tNB\nNewfoundland & Labrador\tNL\nNova Scotia\t\tNS\nOntario\t\t\tON\nPrince Edward Island\tPE\nQuebec\t\t\tQC\nSaskatchewan\t\tSK\n";
	string iDate; //sting that stores the invoice date
	string name; //sting that stores the company name
	string address; //sting that stores the user's adress
	string city; //sting that stores the name of the user's city
	string province; //sting that stores the  initials of the user's province
	string pCode; //sting that stores the user's postal code
	string sMethod; //sting that stores the shipping method
	//Function Body
	cin.ignore(); 
	//Displays the following statements in quotations and accepts the user's input
	cout<<"Please enter your name or your company's name: ";
	getline(cin, name);
	cout<<endl;
	cout<<"Please enter the street address: ";
	getline(cin, address);
	cout<<endl;
	cout<<"Please enter the city: ";
	getline(cin, city);
	cout<<endl;
	cout<<initials<<endl;
	cout<<"Please enter the initials of your province: ";
	getline(cin, province);
	cout<<endl;
	//Converts the user's input into uppercase letters if the input was not already in uppercase 
	for (int k=0; k<province.length(); k++)
	{
		province[k] = toupper(province[k]);
	}
	//if the user entered invalid initials then he or she will be asked to enter one of the ten specified initials 
	while (province !="AB" && province !="BC" && province !="MB" && province !="NB" && province !="NL" && province !="NS" && province !="ON" && province !="PE" && province !="QC" && province !="SK")
	{
		cout<<"Error! Please enter the initials of your province again: ";
		getline(cin, province);
		cout<<endl;
	}
	cout<<"Please enter postal code: ";
	getline(cin, pCode);
	cout<<endl;
	cout<<"Please enter the current date: ";
	getline(cin, iDate);
	cout<<endl;
	cout<<"Our shipping methods are:"<<endl;
	cout<<"PC\t\tPriority Courier\t$35.00"<<endl;
	cout<<"XP\t\tExpress Post\t\t$20.00"<<endl;
	cout<<"RP\t\tRegular Post\t\t$10.00"<<endl<<endl;
	cout<<"Please enter the initials of one of the above shipping methods: ";
	getline(cin, sMethod);
	cout<<endl;
	//Converts the user's input into uppercase letters if the input was not already in uppercase 
	for (int l=0; l<sMethod.length(); l++)
	{
		sMethod[l] = toupper(sMethod[l]);
	}
	//if the user entered invalid initials then he or she will be asked to enter one of the ten specified initials 
	while (sMethod!="PC" && sMethod!="XP" && sMethod!="RP")
	{
		cout<<"Error! Please enter the initials of one of the above shipping methods agin: ";
		getline(cin, sMethod);
		cout<<endl;
	}
	//calculates the shpping cost based on the shipping method chosen by the user
	if (sMethod=="PC")
	{
		shipping=35.00;
	}
	else if (sMethod=="XP")
	{
		shipping=20.00;
	}
	else if (sMethod=="RP")
	{
		shipping=10.00;
	}
	//Write the following statements in quotations and the user's input in the following format
	wFile<<"MERIVALE BOOKS LTD."<<endl;
	wFile<<"1775 MERIVALE ROAD, OTTAWA, ON  K2G 1E2"<<endl;
	wFile<<"(613)-224-1807"<<endl<<endl;
	wFile<<"Account Number\t\tInvoice Number\t\tInvoice Date"<<endl;
	//Calculates the tabs needed depending on the size of the user's account number 
	if (sizeof(aNumber)>=16)
	{
		wFile<<aNumber<<"\t";
	}
	else if (sizeof(aNumber)<16 && sizeof(aNumber)>=8)
	{
		wFile<<aNumber<<"\t\t";
	}
	else if (sizeof(aNumber)<8)
	{
		wFile<<aNumber<<"\t\t\t";
	}
	wFile<<inNum<<"\t\t\t"<<iDate<<endl<<endl;
	wFile<<"Sold to:\t\t"<<name<<endl;
	wFile<<"\t\t\t"<<address<<endl;
	wFile<<"\t\t\t"<<city<<", "<<province<<endl;
	wFile<<"\t\t\t"<<pCode<<endl<<endl;
	wFile<<"Item Description\tQuantity\t\tUnit Price\t\tTotal"<<endl;
	return province; //return the province variable to main
}
//end function uInputH



//Name Constant Definitions
//*****************************************************************************************
// Function Name: uInputD
// Purpose: to accept the user's input and write this information to the file
// Inputs to Function: N/A
// Outputs from Function: N/A
// External Inputs to Function: cin
// External Outputs from Function: cout, wFile
//*****************************************************************************************
void uInputD()
{
	string iName; //string that stores the item description (name) that is entered by the user
	float qSold; //variable that stores the quantity of the item that the user wishes to purchase
	float uPrice; //variable that stores the unit price of item that the useer wishes to purchase
	char uOption='y'; //variable that stores the user's option
	do //do the following as t=long as the uOption is equal to y
	{
		float tPrice=0; //variable that stores the total price
		//display the statement in quotations accept the user's input
		cout<<"Please enter the item description (name): ";
		getline(cin, iName);
		cout<<endl;
		cout<<"Please enter the quantity of this item that you wish to purchase: ";
		cin>>qSold;
		cout<<endl;
		//while the user did not enter a number for the quantity then he or she will be asked to enter the quantity again
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter the quantity of this item that you wish to purchase again: ";
			cin>>qSold;
			cout<<endl;
		}
		cout<<"Please enter the unit price for this item: $";
		cin>>uPrice;
		cout<<endl;
		//while the user did not enter a number for the unit price then he or she will be asked to enter the unit price again
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter the unit price for this item again: ";
			cin>>uPrice;
			cout<<endl;
		}
		//calculate the total price and subtotal
		tPrice = qSold * uPrice;
		subtotal+=tPrice;
		//Write the following information in the format below
		wFile<<"----------------\t--------\t\t----------\t\t-----"<<endl;
		//calculates the tabs needed depending on the size of the user's input
		if (iName.length()>=16)
		{
			wFile<<iName<<"\t";
		}
		else if (iName.length()<16 && iName.length()>=8)
		{
			wFile<<iName<<"\t\t";
		}
		else if (iName.length()<8)
		{
			wFile<<iName<<"\t\t\t";
		}
		if (sizeof(qSold)>=16)
		{
			wFile<<qSold<<"\t";
		}
		else if (sizeof(qSold)<16 && sizeof(qSold)>=8)
		{
			wFile<<qSold<<"\t\t";
		}
		else if (sizeof(qSold)<8)
		{
			wFile<<qSold<<"\t\t\t";
		}
		//setprecision makes the information be written with 2 decimal plaes after the number
		if (sizeof(uPrice)>=16)
		{
			wFile<<fixed<<setprecision(2)<<uPrice<<"\t";
		}
		else if (sizeof(uPrice)<16 && sizeof(uPrice)>=8)
		{
			wFile<<fixed<<setprecision(2)<<uPrice<<"\t\t";
		}
		else if (sizeof(uPrice)<8)
		{
			wFile<<fixed<<setprecision(2)<<uPrice<<"\t\t\t";
		}		
		wFile<<fixed<<setprecision(2)<<tPrice<<endl;
		//user chooses whter or not to buy more books
		cout<<"Would like to purchase more books: ";
		cout<<"Press y for yes or n for no"<<endl;
		cout<<"Please enter your option: ";
		cin>>uOption; //accept user input
		cout<<endl;
		//while the user did not enter a one of the correct letters for his or her option then he or she will be asked to enter the option again
		while (uOption!='y' && uOption !='n')
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter your option again: ";
			cin>>uOption;
			cout<<endl;
		}
		//while the user did not enter a letter for his or her option then he or she will be asked to enter the option again
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout<<"Error! Please enter your option again: ";
			cin>>uOption;
			cout<<endl;
		}
		cin.ignore();
	} while (uOption=='y');
}
//end function uInputD


//Name Constant Definitions
//*****************************************************************************************
// Function Name: cTax
// Purpose: to calculate the tax, the subtotal and the total and write them to the file
// Inputs to Function: string
// Outputs from Function: N/A
// External Inputs to Function: cin
// External Outputs from Function: cout, wFile
//*****************************************************************************************
void cTax(string province) //variable that stores the initials of the province enetered by the user
{
	cout<<endl<<endl;
	float total; //variable that stors the total
	float HST=0; //variable that stors the HST
	float GST=0; //variable that stors the GST
	float PST=0; //variable that stors the PST
	float QST=0; //Variable that stors the QST
	float subtotal2 = subtotal + shipping; //variable that stors the subtotal
	//write the specified information in the following format
	wFile<<endl<<"Shipping:\t\t"<<fixed<<setprecision(2)<<shipping<<endl;
	wFile<<"Subtotal:\t\t"<<fixed<<setprecision(2)<<subtotal2<<endl;
	//calculate the tax rate based on the province initials entered by the useer
	if (province=="AB")
	{
		GST=0.05*subtotal2;
	}
	else if (province=="BC")
	{
		GST=0.05*subtotal2;
		PST=0.07*subtotal2;
	}
	else if (province=="MB")
	{
		GST=0.05*subtotal2; 
		PST=0.08*subtotal2;
	}
	else if (province=="NB")
	{
		HST=0.13*subtotal2;
	}
	else if (province=="NL")
	{
		HST=0.13*subtotal2;
	}
	else if (province=="NS")
	{
		HST=0.15*subtotal2;
	}
	else if (province=="ON")
	{
		HST=0.13*subtotal2;
	}
	else if (province=="PE")
	{
		HST=0.14*subtotal2;
	}
	else if (province=="QC")
	{
		GST=0.05*subtotal2;
		QST=0.0975*(GST+subtotal2);
	}
	else if (province=="SK")
	{
		GST=0.05*subtotal2;
		PST=0.05*subtotal2;
	}
	//write the specified information in the following format
	wFile<<"GST:\t\t\t"<<fixed<<setprecision(2)<<GST<<endl;
	wFile<<"PST:\t\t\t"<<fixed<<setprecision(2)<<PST<<endl;
	wFile<<"QST:\t\t\t"<<fixed<<setprecision(2)<<QST<<endl;
	wFile<<"HST:\t\t\t"<<fixed<<setprecision(2)<<HST<<endl;
	total= subtotal2 + GST + PST + QST + HST;
	wFile<<"Total:\t\t\t"<<fixed<<setprecision(2)<<total<<endl<<endl;
	wFile<<"Your pleasure & your business are important to us!"<<endl;
	wFile.close(); //close the file
	//resets the value of the following variables back to 0
	subtotal=0; 
	shipping=0;
}
//ennd function cTax


//Name Constant Definitions
//*****************************************************************************************
// Function Name: invoice
// Purpose: to display the invoice to the user
// Inputs to Function: string
// Outputs from Function: N/A
// External Inputs to Function: cin, rFile
// External Outputs from Function: cout
//*****************************************************************************************
void invoice (string temV) //temporary variable that stores the file name
{
	rFile.open(temV.c_str()); //opens the file in read mode
	//read the information from the file display this information to the user
	while (rFile)
	{
		getline (rFile, file);
		cout<<file<<endl;
	}
	rFile.close(); //close the file
	system("pause"); //make the user press a key to continue
	system("cls"); //clear the screen
}
//end function invoice


//Name Constant Definitions
//*****************************************************************************************
// Function Name: goodbye
// Purpose: to thank the user for shopping at Merivale Books
// Inputs to Function: string
// Outputs from Function: N/A
// External Inputs to Function: cin, rFile
// External Outputs from Function: cout
//*****************************************************************************************
void goodbye()
{
	cout<<endl;
	cout<<"Thank you for shopping at Merivale Books, your number 1 bookstore."<<endl<<endl;
	system("pause");
	system("cls");
}











