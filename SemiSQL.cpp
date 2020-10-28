#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

const std::string DEFAULT_PROMPT_TEXT = "semi_sql";
const std::string PROMPT_SEP = "> ";
const std::string DB_EXT = ".db";

/*
create database               done & refactored
open   database               done & refactored
create table                  done & refactored
show   tables                 done & refactored
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
void create_table(void);
void show_tables(void);
std::string get_prompt();
void database(char*);
void shreadtable(char*, char*);
int linecr(char*, char*);

struct db {
    std::string name;
    // TODO: Add tables handler
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
        create_table();

    } else if (a == "OPENTABLE") {
        // TODO: Figure out the purpose of this command
    } else if (a == "DPTABLE") {
        // TODO: Figure out what to do here
    } else if (a == "SHOWTABLES") {
        show_tables();

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
    std::fstream dbfile(dbname + DB_EXT, std::ios::in);

    if (dbfile) {
        std::cout << "Database exists!" << std::endl;
        dbfile.close();
        return;
    }

    dbfile.open(dbname + DB_EXT, std::ios::out);
    dbfile.close();

    std::cout << "Database created!" << std::endl;
}

void opendb(std::string dbname) {
    std::fstream dbfile(dbname + DB_EXT, std::ios::in);

    if (!dbfile) {
        std::cout << "DB not created!" << std::endl;
        return;
    }

    if (currentdb) delete currentdb;
    currentdb = new db;
    currentdb->name = dbname;
}

void create_table(void) {
    std::string table_name, cscols, csdata;
    size_t field_count;

    if(!currentdb) {
        std::cout << "NO dB OPENED!!" << std::endl;
        return;
    }

    std::cout << "Enter table name: ";
    getline(std::cin, table_name);

    std::ofstream fout(currentdb->name + DB_EXT, std::ios::app);

    fout << "@" << table_name << "@" << std::endl;

    std::cout << "Enter column names:" << std::endl;
    getline(std::cin, cscols);
    field_count = std::count(cscols.begin(), cscols.end(), ',') + 1;

    fout << cscols << std::endl;

    std::cout << std::endl << "Enter column data:" << std::endl;
    do {
        bool excess_data;

        do {
            getline(std::cin, csdata);

            excess_data = (std::count(csdata.begin(), csdata.end(), ',') >= field_count);
            if (excess_data)
                std::cout << "You're entering excess data!" << std::endl
                    << "Recheck your data" << std::endl;
        } while (excess_data);

        fout << csdata << std::endl;

    } while (csdata.find('}') == std::string::npos);

    fout.close();
}

void show_tables(void) {
    if(!currentdb) {
        std::cout << "NO dB OPENED!!" << std::endl;
        return;
    }

    std::ifstream dbfile(currentdb->name + DB_EXT);
    char line[100];

    do {
        dbfile.get(line, 100);
        dbfile.get();  // eat trailing newline char

        if (line[0] == '@') {  // @'s are table name identification markers
            std::string table_name(line);
            std::cout << table_name.substr(1, table_name.length()-2) << ",";
        }

    } while (!dbfile.eof());

    std::cout << std::endl;

    dbfile.close();
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
void linecr(char line[])
{
    // Gets rid of first and last characters of line[].
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
    // if (line.substr(1, line2.length()) == line2)
    //     return 1
    // else
    //     return 0
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
