#include <iostream>
#include <iomanip>

const std::string PROMPT = "semi_sql> ";

/*
create database     done
create table        done
show tables         done
select *table       done
select <specific_column>table done
delete table
delete column
add,average,percentage
*/

int parse(std::string);
void database(char*);
void createtable(char*);
void shreadtable(char*, char*);
int linecr(char*, char*);

int main(void) {
    std::string a;

    std::cout << "Instructions" << std::endl
        << "============" << std::endl
        << "* Type CREATEDB to create a database." << std::endl
        << "* Type OPENDB to open the database." << std::endl
        << "* Type CREATETABLE to create the table." << std::endl
        << "* Type OPENTABLE to open the table." << std::endl
        << "* Type DPTABLE to display the table." << std::endl
        << "* Type SHOWTABLES to display the names of all the tables" << std::endl
        << "* Type SELECTTABLE to select a specific table." << std::endl
        << "* Type SELECTCOLUMN to select a column name." << std::endl
        << "* Type EXIT to exit." << std::endl;

    do {
        std::cout << std::endl << PROMPT;
        getline(std::cin, a);
    } while (parse(a));

    return 0;
}

int parse(std::string a) {
    // This will replace syntax()
    if (a == "EXIT")
        return 0;
    return 1;
}
void database(char db[])
{
	char z[20];
	int j=strlen(db);
	for (int k=0,a=k+1;k<j,a<=j+1;k++,a++)
	{
		z[a]=db[k];
	}
	z[0]='@';
	int i=strlen(db);
	z[i+1]='@';
	z[i+2]='\0';
	strcpy(db,z);	     // to be changed // TODO: figure out what to change
}
void shreadtable(char db[],char table[])
{
	/*
	user enters tablename ...table comparison done ....check for which column it is
	.....display the subsequent data..of that particular column...
	till it detects another @....
	*/
	char myline[100],line[100],ch;
	std::cout <<"\n Enter column name\n";
	gets(myline);
	ifstream file(db);
	while(1)
	{
		file.get(line,100);
		file.get(ch);
		if(linecr(line,table) == 1)
		{
			file.get(line,100);
			file.get(ch);
			break;
		}
	}
	delay(2000);
	int j=0,k=0,n=0,i=0;
	cas:
	k=0;  j=0;
	while(line[i] != ',')
	{
		if(line[i] == ','|| line[i] == ';') break;
		if(line[i] == myline[k])
		{	k++;
			j++;
		} i++;
	}
	if(line[i] == ',' || line[i] == ';') {n++;}
	if(j != strlen(myline)){i++;goto cas;}
	j=n-1;
	while(1)
	{       i=0;
		k=0;
		file.get(line,100);file.get(ch);
		if(line[0] == '}') break;
		while(line[i] != ';')
		{
			if(line[i] == ',')
			{k++;i++;}
			if(k>j || line[i] == ';') break;
			if(k == j)std::cout << line[i];
			i++;
		}i=0;
		std::cout << "\n" ;
		delay(2000);
	}
	file.close();
	gets(line);
	syntax(line);
}
void createtable(char db[])
{
	char a[10];
	int i=0,n=0,k=0;
	std::cout << "\nEnter table name\n";
	gets(a);
	ofstream fout;
	fout.open(db,ios::app|ios::nocreate);
	if(!fout)
		{std::cout<<"\nNO dB OPENED!!\n";};   //syntax
	fout << "@"<< a << "@\n";
	std::cout<<"\nEnter column names\n";  		//excess data warning;
	gets(a);
	while(a[i] != '\0')
	{
		if(a[i] == ',') n++;
		i++;
	}
	std::cout << std::endl;
	fout << a<< "\n";
	std::cout <<"\nEnter column data\n";
	i=0;
	do
	{
		maaza:
		k= 0;
		gets(a);
		while(a[i] != '\0')
		{
		if(a[i] == ',') k++;
		if(k > n){ std::cout <<"\nYou're entering excess data!"
					<< "\n Recheck your data\n"; goto maaza;}
		i++;
		}i=0;
		fout << a;
		while(a[i] != '\0')
		{
			if(a[i] == '}'){fout << '\n' ;goto cas;}
			i++;
		}
		if(a[i] == '\0') fout << '\n';
		i=0;
	}while(1);
	cas:
	fout.close();
	gets(a);
	syntax(a);
}
void linecr(char line[])
{
	char trans[10];
	int n,i=0;
	strcpy(trans,line);
	n = strlen(trans);
	trans[n-1] = '\0';
	while(trans[i] != '\0')
	{
		trans[i] = trans[i+1];
		i++;
	}
	strcpy(line,trans);
}
int linecr(char line[],char line2[])
{

		int j=0,i=0;
				while(line2[i] != '\0')
				{	j++;
					i++;
					if(line2[i] != line[i+1])goto fun;
				}
			fun:
				if(j == strlen(line2))return 1;
				else return 0;
}
void syntax(char a[])
{
    // THIS IS HELL!
	char syn[10],var[10],ch,line[50], line2[50];
	static char db[20],table[30];
	int i=0,k=0;
	fstream infile,tout;
	if(strcmp("CREATEDB",a) == 0) // done
	{
		std::cout << "\nCREATING" ;
		std::cout << "\nEnter database name-\n";
		gets(db);
		database(db);
		puts(db);
		infile.open(db,ios::out|ios::noreplace);
		std::cout << "\nDatabase created!\n";
		gets(syn);
		syntax(syn);
	}
	else if(strcmp("OPENDB",a) ==0) //done
	{
		std::cout << "\nEnter database name-\n ";
		gets(db);
		database(db);
		tout.open(db,ios::in);
		if(!tout)
		{
			std::cout << "\nDB not created!\n ";
		}
		else 	std::cout << "\nDatabase opened!\n";
		tout.close();
		gets(syn);
		syntax(syn);
	}
	if(strcmp("CREATETABLE",a) ==0)
	{
		createtable(db);
	}
	if(strcmp("DPTABLE",a) == 0)
	{
		ifstream file(db);
		if(!file) std::cout << "\nDB not entered!\n";
		while(1)
		{
	while(k != 1)
	{
		file.get(line,100);
		file.get(ch);
		if(line[0] == '@'){k=linecr(line,table);}
	}
	if(k==1 )
	{
		file.get(line,100);
		file.get(ch);
		i=0;
		while(line[i] != ';' )
	{
	if(line[i] == ',') {std::cout << "\t\t"; i++;}
	if(line[i] == '}') goto jojol;
	std::cout << line[i];
	i++;
	delay(100);
	}
	if(line[i] == ';')std::cout << ch;
	delay(1000);
	}
	if(file.eof() ==1) break;
	}
	jojol:
	gets(syn);
	syntax(syn);
	}
	if(strcmp("SHOWTABLES",a) == 0)
	{
		ifstream tout(db,ios::nocreate);
		tout.seekg(0);
		while(1)
		{
		tout.get(var,100); // add variable
		tout.get(ch);
		if(var[0] == '@')
		{	linecr(var);
			std::cout << var << ",";
		}
		if(tout.eof()) break;
	}
	tout.close();
	gets(syn);
	syntax(syn);
	}
	if(strcmp("SELECTTABLE",a) == 0)
	{
		std::cout << "\nEnter table name-\n";
		gets(table);
		gets(syn);
		syntax(syn);
	}
	if(strcmp("SELECTCOLUMN",a) == 0)
	{
		shreadtable(db,table);	//enter any column name and it will display the column name
	}
	if(strcmp("EXIT",a) == 0) exit(1);
	else std::cout << "\t\t --WRONG SYNTAX!\n";
	gets(syn);
	syntax(syn);
}
