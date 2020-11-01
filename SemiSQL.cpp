#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>

const std::string DEFAULT_PROMPT_TEXT = "semi_sql";
const std::string DB_TABLE_SEP = "::";
const std::string PROMPT_SEP = "> ";
const std::string DB_EXT = ".db";
const std::string DELIMS = ",;}";

/*
create database               done & refactored
open   database               done & refactored
create table                  done & refactored
show   tables                 done & refactored
select *table                 done & refactored
display table                 done & refactored
select <specific_field>table  done & reafctored
drop   table
drop   column
funcs: add()
       average()
   (?) percentage()
*/

int parse(std::string const&);
void createdb(std::string const&);
void opendb(std::string const&);
void create_table(void);
void show_tables(void);
void select_table(void);
void display_table(void);
void select_field(void);
void print_row(std::vector<std::string> const&);
void get_tables(std::vector<std::string>&);
std::string get_prompt(void);
void tokenize(std::string const&, std::string const&, std::vector<std::string>&);
void database(char*);
void shreadtable(char*, char*);
int linecr(char*, char*);

struct db {
    std::string name;
    std::string* table;
} *currentdb;

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
        << "* Type SELECTFIELD to select a field name." << std::endl
        << "* Type EXIT to exit." << std::endl
        << "********************************************************" << std::endl;

    do {
        std::cout << std::endl << get_prompt();
        if (!getline(std::cin, a)) {
            std::cout << "EXIT" << std::endl;
            break;
        }
    } while (parse(a));

    if (currentdb) {
        if (currentdb->table)
            delete currentdb->table;
        delete currentdb;
    }

    std::cout << "OK, Bye!" << std::endl;
    return 0;
}

int parse(std::string const &a) {
    if (a == "CREATEDB") {
        std::string dbname;
        std::cout << "Enter database name: ";
        getline(std::cin, dbname);
        createdb(dbname);

    } else if (a == "OPENDB") {
        std::string dbname;
        std::cout << "Enter database name: ";
        getline(std::cin, dbname);
        opendb(dbname);

    } else if (a == "CREATETABLE") {
        create_table();

    } else if (a == "OPENTABLE") {
        // TODO: Figure out the purpose of this command
    } else if (a == "DPTABLE") {
        display_table();

    } else if (a == "SHOWTABLES") {
        show_tables();

    } else if (a == "SELECTTABLE") {
        select_table();

    } else if (a == "SELECTFIELD") {
        select_field();

    } else if (a == "EXIT")
        return 0;
    else
        std::cout << "Invalid Command!" << std::endl;

    return 1;
}

void createdb(std::string const &dbname) {
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

void opendb(std::string const &dbname) {
    std::fstream dbfile(dbname + DB_EXT, std::ios::in);

    if (!dbfile) {
        std::cout << "DB not created!" << std::endl;
        return;
    }

    if (currentdb) delete currentdb;
    currentdb = new db;
    currentdb->name = dbname;
    currentdb->table = nullptr;
}

void create_table(void) {
    std::string table_name, cscols, csdata;
    int field_count;

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

    std::vector<std::string> tables;
    get_tables(tables);

    for (size_t i = 0; i < tables.size(); i++) {
        std::cout << tables[i];
        if (i == tables.size() - 1) continue;  // don't print the last comma
        std::cout << ",";
    }
    std::cout << std::endl;
}

void select_table(void) {
    if(!currentdb) {
        std::cout << "NO dB OPENED!!" << std::endl;
        return;
    }

    std::string table_name;

    std::cout << "Enter table name: ";
    getline(std::cin, table_name);

    std::vector<std::string> tables;
    get_tables(tables);

    if (std::find(tables.begin(), tables.end(), table_name) == tables.end()) {
        std::cout << "Table does not exist in database." << std::endl;
        return;
    }

    if (currentdb->table) delete currentdb->table;
    currentdb->table = new std::string(table_name);
}

void display_table(void) {
    if(!currentdb) {
        std::cout << "NO dB OPENED!!" << std::endl;
        return;
    }

    if (!currentdb->table) {
        std::cout << "NO Table SELECTED!!" << std::endl;
        return;
    }

    std::ifstream dbfile(currentdb->name + DB_EXT);
    std::string line;

    // Navigate to the current table
    do {
        getline(dbfile, line);

        if (line[0] == '@') {
            if (line.substr(1, line.size()-2) == *(currentdb->table))
                break;
        }
    } while(!dbfile.eof());

    std::vector<std::string> fields, values;

    // Get the fields and print 'em
    getline(dbfile, line);
    tokenize(line, DELIMS, fields);
    print_row(fields);

    // Get values and print 'em
    do {
        getline(dbfile, line);
        tokenize(line, DELIMS, values);
        print_row(values);
    } while (line.find('}') == std::string::npos);

    dbfile.close();
}

void select_field(void) {
    if(!currentdb) {
        std::cout << "NO dB OPENED!!" << std::endl;
        return;
    }

    if (!currentdb->table) {
        std::cout << "NO Table SELECTED!!" << std::endl;
        return;
    }

    std::ifstream dbfile(currentdb->name + DB_EXT);
    std::string line, field_name;

    std::cout << "Enter field name: ";
    getline(std::cin, field_name);

    // Navigate to the current table
    do {
        getline(dbfile, line);

        if (line[0] == '@') {
            if (line.substr(1, line.size()-2) == *(currentdb->table))
                break;
        }
    } while(!dbfile.eof());

    std::vector<std::string> fields, values;

    // Get the fields
    getline(dbfile, line);
    tokenize(line, DELIMS, fields);

    // Get the index of `field_name` in `fields`
    auto it = std::find(fields.begin(), fields.end(), field_name);
    if (it == fields.end()) {
        std::cout << "Field does not exist!" << std::endl;
        return;
    }
    size_t index = it - fields.begin();

    std::cout << fields[index] << std::endl;

    // Print values corresponding to `field_name`
    do {
        getline(dbfile, line);
        tokenize(line, DELIMS, values);
        std::cout << values[index] << std::endl;
    } while (line.find('}') == std::string::npos);

    dbfile.close();
}

void print_row(std::vector<std::string> const &cols) {
    for (size_t i = 0; i < cols.size(); i++) {
        std::cout << cols[i];
        if (i != cols.size() - 1)
            std::cout << "\t\t";
    }
    std::cout << std::endl;
}

void get_tables(std::vector<std::string> &tables) {
    std::ifstream dbfile(currentdb->name + DB_EXT);
    std::string line;

    do {
        getline(dbfile, line);

        if (line[0] == '@')  // @'s are table name identification markers
            tables.push_back(line.substr(1, line.length()-2));
    } while (!dbfile.eof());

    dbfile.close();
}

std::string get_prompt(void) {
    std::string prompt;

    if (currentdb) {
        prompt = currentdb->name;
        if (currentdb->table)
            prompt += DB_TABLE_SEP + *(currentdb->table);
    } else
        prompt = DEFAULT_PROMPT_TEXT;

    return prompt + PROMPT_SEP;
}

void tokenize(std::string const &str, std::string const &delims,
              std::vector<std::string> &out) {
    size_t start=0;
    size_t end;

    out.clear();
    while ((end = str.find_first_of(delims, start)) != std::string::npos) {
        out.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    // push_back the last element iff it's not empty
    if (start != str.size())
        out.push_back(str.substr(start, str.size() - start));
}
