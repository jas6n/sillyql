// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <iostream>
#include <iomanip>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include "TableEntry.h"
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;


static struct option long_options[] = {
    {"help", no_argument, nullptr, 'h' },
    {"quiet", no_argument, nullptr, 'q'},
};


class SillyQL{
public:

SillyQL() : choice{0}, index{0}, quiet_mode{false} {}

void get_commands(int argc, char* argv[]){

    while ((choice = getopt_long(argc, argv, "hq", long_options, &index)) != -1){

        switch(choice){

            case 'h':
                cout << "This program implements a silly QL" << "\n";
                exit(0);
                break;

            case 'q':
                quiet_mode = true;
                break;

        }

    }

}

void run_program(){
    string cmd;


    do {

        if (cin.fail()) {
            cerr << "Error: Reading from cin has failed" << endl;
            exit(1);
        } // if


        cout << "% ";
        cin >> cmd;
    
        // check if comment
        if (cmd[0] == '#'){

            getline(cin, cmd);
            cout << cmd << endl;

        // QUIT command
        } else if (cmd == "QUIT"){

            cout << "Thanks for being silly!\n";

        // CREATE command
        } else if (cmd == "CREATE"){

            create();

        } else if (cmd == "INSERT"){

            insert();
        }

    } while (cmd != "QUIT");

}

// might be inefficient to return a vector but idk how else to do it
// change to creating a vector of table entry types similar to column names vector instead of adding to the data vector
void create(){


    size_t cols;
    string name;
    string hold;

    cin >> name;
    cin >> cols;

    if (shell.find(name) != shell.end()){
        cout << "Error during CREATE: cannot create an already existing table " << name << "\n";
        getline(cin, hold);
        return;

    }

    vector<EntryType> entry_types;


    // add a single TableEntry of the specified type
    for (size_t i = 0; i < cols; ++i){
        cin >> hold;
        if (hold == "double"){

            entry_types.emplace_back(EntryType::Double);

        } else if (hold == "int"){

            entry_types.emplace_back(EntryType::Int);

        } else if (hold == "bool"){

            entry_types.emplace_back(EntryType::Bool);

        } else {

            entry_types.emplace_back(EntryType::String);

        }
    }

    vector<string> labels;
    for (size_t i = 0; i < cols; ++i){
        cin >> hold;

        labels.emplace_back(hold);
    }

    // inserts vectors into the hash tables
    column_names.insert({name, labels});

    column_types.insert({name, entry_types});

    vector<vector<TableEntry>> table;

    table.resize(cols);

    shell.insert({name, table});


    // prints out the column names
    string c;

    if (cols > 1){
        c = "columns";
    } else {
        c = "column";
    }

    cout << "New table " << name << " with " << c << " ";

    for (size_t i = 0; i < cols; ++i){
        cout << column_names[name][i] << " ";
    }

    cout << "created\n";

}




void insert(){


    // get first line
    string hold;
    cin >> hold;
    string name;
    cin >> name;
    size_t rows;
    cin >> rows;
    getline(cin, hold);


    if (shell.find(name) == shell.end()){
        cout << "Error during INSERT: " <<  name << " does not name a table in the database \n";
        for (size_t i = 0; i < rows; ++i){
            getline(cin, hold);
        }
        return;
    }


    size_t pos1 = 0;
    size_t pos2 = 0;


    pos1 = shell[name][0].size();
    // insert into the table
    // why wont it read the last line?
    for (size_t i = 0; i < rows; ++i){
        // vector<TableEntry> v;
        // shell[name].emplace_back(v);
        for (size_t j = 0; j < shell[name].size(); ++j){

            if (cin.fail()) {
                cerr << "Error: Reading from cin has failed" << endl;
                exit(1);
            } 

            switch(column_types[name][j]){

                case EntryType::Bool:
                    cin >> hold;
                    if (hold[0] == 'f'){
                        shell[name][j].emplace_back(false);
                    } else {
                        shell[name][j].emplace_back(true);
                    }
                    break;

                case EntryType::Double:
                    double val1;
                    cin >> val1;
                    shell[name][j].emplace_back(val1);
                    break;

                case EntryType::Int:
                    int val;
                    cin >> val;
                    shell[name][j].emplace_back(val);
                    break;

                case EntryType::String:
                    string val2;
                    cin >> val2;
                    shell[name][j].emplace_back(val2);
                    break;



            }

        }
    }
    pos2 = shell[name][0].size() - 1;

    cout << "Added " << rows << " rows to " << name << " from position " << pos1 << " to " << pos2 << "\n";

}

private:

unordered_map <string, vector<vector<TableEntry>>> shell;
unordered_map <string, vector<string>> column_names;
unordered_map <string, vector<EntryType>> column_types;
int choice;
int index;
bool quiet_mode;


};








int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc,argv);

    //  double val;
    // cin >> val;
    // cout << val << endl;

    SillyQL goofy;
     

    goofy.get_commands(argc, argv);
    goofy.run_program();
    // vector<TableEntry> v; 
    // int i = 3;
    // v.emplace_back(i); 

    return 0;
}

// TODO
// fix double read in