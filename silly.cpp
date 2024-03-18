// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <iostream>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include "TableEntry.h"
#include <vector>
using namespace std;


static struct option long_options[] = {
    {"help", no_argument, nullptr, 'h' },
    {"quiet", no_argument, nullptr, 'q'},
};


class SillyQL{
public:

SillyQL() : quiet_mode{false}, choice{0}, index{0} {}

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

        }

    } while (cmd != "QUIT");

}

void create(){
    int cols;
    string name;

    cin >> name;
    cout << name << endl;
    cin >> cols;
    cout << cols << endl;


}

private:
bool quiet_mode;
int choice;
int index;

};








int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc,argv);

    SillyQL goofy;

    goofy.get_commands(argc, argv);
    goofy.run_program();

    return 0;
}