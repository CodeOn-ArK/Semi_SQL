#include <iostream>
#include <iomanip>
#include <fstream>

const std::string DEFAULT_PROMPT_TEXT = "semi_sql";
const std::string PROMPT_SEP = "> ";

/*
create database               done & refactored
open   database               done & refactored
create table                  done
show   tables                 done
select *table                 done
select <specific_column>table done
drop   table
drop   column
funcs: add()
       average()
   (?) percentage()
*/

int parse(std::string);
void createdb(std::string);
void opendb(std::string);
std::string get_prompt();
void database(char*);
void createtable(char*);
void shreadtable(char*, char*);
int linecr(char*, char*);

struct db {
    std::string name;
    // add tables handler
};

struct db* currentdb;

int main(void) {
    std::string a;

    currentdb = nullptr;

    std::cout << "\t! READ THIS !" << std::endl
        << "********************************************************" << std::endl
        << "* Type CREATEDB to create a database." << std::endl
        << "* Type OPENDB to open the database." << std::endl
        << "* Type CREATETABLE to create the table." << std::endl
        << "* Type OPENTABLE to open the table." << std::endl
        << "* Type DPTABLE to display the table." << std::endl
        << "* Type SHOWTABLES to display the names of all the tables" << std::endl
        << "* Type SELECTTABLE to select a specific table." << std::endl
        << "* Type SELECTCOLUMN to select a column name." << std::endl
        << "* Type EXIT to exit." << std::endl
        << "********************************************************" << std::endl;

    do {
        std::cout << std::endl << get_prompt();
        getline(std::cin, a);
    } while (parse(a));

    return 0;
}

int parse(std::string a) {
    if (a == "CREATEDB") {
        std::string dbname;
        std::cout << "Enter database name- ";
        getline(std::cin, dbname);
        createdb(dbname);

    } else if (a == "OPENDB") {
        std::string dbname;
        std::cout << "Enter database name- ";
        getline(std::cin, dbname);
        opendb(dbname);

    } else if (a == "CREATETABLE") {
        // call to create_table(table_name);
    } else if (a == "OPENTABLE") {
        // TODO: Figure out the purpose of this command
    } else if (a == "DPTABLE") {
        // TODO: Figure out what to do here
    } else if (a == "SHOWTABLES") {
        // call to showtables();
    } else if (a == "SELECTTABLE") {
        // input table_name;
        // call to select_table(table_name);
    } else if (a == "SELECTCOLUMN") {
        // input column_name;
        // disp_column(column_name);
    } else if (a == "EXIT")
        return 0;
    else
        std::cout << "Invalid Command!" << std::endl;

    return 1;
}

void createdb(std::string dbname) {
    std::fstream dbfile(dbname, std::ios::in);

    if (dbfile) {
        std::cout << "Database exists!" << std::endl;
        dbfile.close();
        return;
    }

    dbfile.open(dbname, std::ios::out);
    dbfile.close();

    std::cout << "Database created!" << std::endl;
}

void opendb(std::string dbname) {
    std::fstream dbfile(dbname, std::ios::in);

    if (!dbfile) {
        std::cout << "DB not created!" << std::endl;
        return;
    }

    if (currentdb) delete currentdb;
    currentdb = new db;
    currentdb->name = dbname;
}

std::string get_prompt() {
    if (currentdb)
        return currentdb->name + PROMPT_SEP;
    return DEFAULT_PROMPT_TEXT + PROMPT_SEP;
}
void database(std::string db)
{
    // Basically what's happening here:
    // db = '@' + db + '@'

	char z[20];
	int j=strlen(db);
	for (int k=0,a=k+1;k<j,a<=j+1;k++,a++)  // WTF! How's that condition working!?
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
