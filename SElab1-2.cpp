#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// All the keywords (Tatall is 32)
string keyword[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
					"else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
					"return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
					"union", "unsigned", "void", "volatile", "while"};

int main()
{
	string file; // The file you want to check	
	
	// Get the right file needed to check
	for(;;)
	{
		cout << "Enter the file you want to check,\n"
		 << "which should be a CPP file and in the same folder as this file.\n ";
		cin >> file;
		
		// Check the path of the file
		ifstream inFile;
		inFile.open(file.c_str(), ios::in);
		if(!inFile)
		{
        	cout << "\nWrong Path!\nPlease re-enter the path of the file.\n";
		}
		else break;
	}
	
	// Open the file
	ifstream inFile1, inFile2, inFile3, inFile4;
	inFile1.open(file.c_str(), ios::in);
	inFile2.open(file.c_str(), ios::in);
	inFile3.open(file.c_str(), ios::in);
	inFile4.open(file.c_str(), ios::in);
	
	
	int level = 0; // Different levels of requirements (1~4)
	cout << "What level of requirements (1~4) do you want to check?\n";
	cin >> level;
	
	
    string str;
	int total = 32, totalNum = 0;
	int count[total] = {0}; 
	
	// Level1
	while(getline(inFile1, str))
	{
		for(int i = 0; i < total; i++)
		{
			int pos;
			for(;;)
			{
				if(str.find(keyword[i]) != -1)
				{
					if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
					else
					{
						pos = str.find(keyword[i]);
						count[i]++;
						str = str.substr(pos + keyword[i].length(), str.length() - pos - keyword[i].length());
						// Delete the found keywords to avoid double counting later.
					}
				} 
				else break;
			}	
		}
	}
	
	for(int j = 0; j < total; j++)
	{
		if(count[j] != 0)
		{
			totalNum += count[j]; // Accumulate the total number of all keywords.
		}
	}
	
	int num[4] = {25, 2, 15, 9};
	// keyword[25] = switch, keyword[2] = case, keyword[15] = if, keyword[9] = else
	int caseNum[count[num[0]]] = {0}; // The case number of the one 'switch' structure.
	int x = -1; // Use of the number of 'switch' structure.
	
	// Level2
	while(getline(inFile2, str))
	{
		for(;;)
		{
			if(str.find(keyword[num[0]]) != -1) // Find the 'switch' keyword.
			{
				if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
				else
				{
					x++;
					break;
				}
			}
			if(str.find(keyword[num[1]]) != -1) // Find the 'case' keyword.
			{
				if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
				else
				{
					caseNum[x]++;
					break;
				}
			}
			else break;
		}	
	}
	
	string elif = "else if";
	int y = 0; // Use for the number of 'if' structure
	
	//Level3
	while(getline(inFile3, str))
	{
		int pos;
		for(;;)
		{
			if(str.find(elif) != -1) // Find the 'else if' keyword.
			{
				pos = str.find(elif);
				//cout << "Find else if!\n";
				str = str.substr(pos + elif.length(), str.length() - pos - elif.length());
				// Delete the found keywords to avoid double counting later.
			}
			if(str.find(keyword[num[2]]) != -1) //Find the 'if' keyword.
			{
				if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
				else{
					y++;
					//cout << "Find if!\n";
					break;
				}
			}
			else break;
		}
	}
	//cout << endl;
	
	//cout << "The number of if " << y << endl << endl;
	int judging[y] = {0}, ifelNum = 0, ifelifelNum = 0;
	int z = -1;
	
	//Level4
	while(getline(inFile4, str))
	{
		for(;;)
		{
			//cout << "time" << z << endl;
			if(str.find(elif) != -1) // Find the 'else if' keyword.
			{
				if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
				else
				{
					judging[z]++;
					//cout << "Find else if!\n";
					break;
				} 
			}
			if(str.find(keyword[num[2]]) != -1) // Find the 'if' keyword.
			{
				if(str.find("//") != -1) break; // If the keyword is in the comment, ignore it.
				else
				{
					z++;
					//cout << "Find if!\n";
					break;
				}
			}
			else break;
		}
	}
	
	// The judging of the Level3 and Level4.
	for(int k = 0; k < y; k++)
	{
		if(judging[k] == 0)
			ifelNum++; // The number of 'if else' structure. Level3
		else
			ifelifelNum++; // The number of 'if, else if, else' structure. Level4
	}
	
	// The results of 4 levels.
	for(int l = 1; l < level + 1; l++)
	{
		switch(l)
		{
		case 1:
			cout << "\nLEVEL1\n"; 
			cout << "Total num is: " << totalNum << endl;
			for(int m = 0; m < total; m++)
			{	
				if(count[m]!=0)
					cout << keyword[m] << " num: " << count[m] << endl;
			}
			break;
			
		case 2:
			cout << "\nLEVEL2\n"; 
			cout << "The number of 'switch' structure is: " << count[num[0]] << endl;
			for(int m = 0; m < count[num[0]]; m++)
				cout << "The case numbers in the No."<< (m+1) << " 'switch' structure: " << caseNum[m] << endl;
			break;
			
		case 3:
			cout << "\nLEVEL3\n";
			cout << "The number of 'if else' structure: " << ifelNum << endl;
			break;
			
		case 4:
			cout << "\nLEVEL4\n";
			cout << "The number of 'if, else if, else' structure: " << ifelifelNum << endl;
			break;
			
		default:
			cout << "None Keyword!\n";
		}
	}
	
	inFile1.close();
	inFile2.close();
	inFile3.close();
	inFile4.close();
    return 0;
}
