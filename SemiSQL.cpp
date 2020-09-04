#include<conio.h>
#include<math.h>
#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fstream.h>
#include<DOS.h>
#include<iomanip.h>
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
void syntax(char a[]);
void database(char cj[]);
void createtable(char i[]);
void shreadtable(char gh[], char tt[]);
int linecr(char x[],char j[]);
void main()
{
	clrscr();
	_setcursortype(_NOCURSOR);
	int i=0;
	while(1)
	{
		gotoxy(15,6);
		cout << "\t! READ THIS !";
		gotoxy(15,7);
		if(i==0)
			i++;
		cprintf("********************************************************");
		textcolor(i);
		gotoxy(15,8);
		cprintf("Type CREATEDB to create a database.");
			textcolor(i+1);
		gotoxy(15,9);
		cprintf("Type OPENDB to open the database.");
			textcolor(i+2);
		gotoxy(15,10);
		cprintf("Type CREATETABLE to create the table.");
			textcolor(i+3);
		gotoxy(15,11);
		cprintf("Type OPENTABLE to open the table.");
			textcolor(i+4);
		gotoxy(15,12);
		cprintf("Type DPTABLE to display the table.");
			textcolor(i+5);
		gotoxy(15,13);
		cprintf("Type SHOWTABLES to display the names of all the tables");
			textcolor(i+6);
		gotoxy(15,14);
		cprintf("Type SELECTTABLE to select a specific table.");
			textcolor(i+7);
		gotoxy(15,15);
		cprintf("Type SELECTCOLUMN to select a column name.");
			textcolor(i+8);
		gotoxy(15,16);
		cprintf("Type EXIT to exit.");
		textcolor(i);
		gotoxy(15,17);
		i++;
		cprintf("********************************************************");
		delay(2000);
		if(i  > 5 ) break;
		}
		cout << "\nNow start entering data\n";
	char a[10];
	gets(a);
	syntax(a);
	getch();

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
	strcpy(db,z);	     // to be changed
}
void shreadtable(char db[],char table[])
{
	/*
	user enters tablename ...table comparison done ....check for which column it is
	.....display the subsequent data..of that particular column...
	till it detects another @....
	*/
	char myline[100],line[100],ch;
	cout <<"\n Enter column name\n";
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
			if(k == j)cout << line[i];
			i++;
		}i=0;
		cout << "\n" ;
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
	cout << "\nEnter table name\n";
	gets(a);
	ofstream fout;
	fout.open(db,ios::app|ios::nocreate);
	if(!fout)
		{cout<<"\nNO dB OPENED!!\n";};   //syntax
	fout << "@"<< a << "@\n";
	cout<<"\nEnter column names\n";  		//excess data warning;
	gets(a);
	while(a[i] != '\0')
	{
		if(a[i] == ',') n++;
		i++;
	}
	cout << endl;
	fout << a<< "\n";
	cout <<"\nEnter column data\n";
	i=0;
	do
	{
		maaza:
		k= 0;
		gets(a);
		while(a[i] != '\0')
		{
		if(a[i] == ',') k++;
		if(k > n){ cout <<"\nYou're entering excess data!"
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
	char syn[10],var[10],ch,line[50], line2[50];
	static char db[20],table[30];
	int i=0,k=0;
	fstream infile,tout;
	if(strcmp("CREATEDB",a) == 0) // done
	{
		cout << "\nCREATING" ;
		cout << "\nEnter database name-\n";
		gets(db);
		database(db);
		puts(db);
		infile.open(db,ios::out|ios::noreplace);
		cout << "\nDatabase created!\n";
		gets(syn);
		syntax(syn);
	}
	else if(strcmp("OPENDB",a) ==0) //done
	{
		cout << "\nEnter database name-\n ";
		gets(db);
		database(db);
		tout.open(db,ios::in);
		if(!tout)
		{
			cout << "\nDB not created!\n ";
		}
		else 	cout << "\nDatabase opened!\n";
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
		if(!file) cout << "\nDB not entered!\n";
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
	if(line[i] == ',') {cout << "\t\t"; i++;}
	if(line[i] == '}') goto jojol;
	cout << line[i];
	i++;
	delay(100);
	}
	if(line[i] == ';')cout << ch;
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
			cout << var << ",";
		}
		if(tout.eof()) break;
	}
	tout.close();
	gets(syn);
	syntax(syn);
	}
	if(strcmp("SELECTTABLE",a) == 0)
	{
		cout << "\nEnter table name-\n";
		gets(table);
		gets(syn);
		syntax(syn);
	}
	if(strcmp("SELECTCOLUMN",a) == 0)
	{
		shreadtable(db,table);	//enter any column name and it will display the column name
	}
	if(strcmp("EXIT",a) == 0) exit(1);
	else cout << "\t\t --WRONG SYNTAX!\n";
	gets(syn);
	syntax(syn);
}
