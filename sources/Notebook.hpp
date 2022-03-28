#pragma once
#include <vector>
#include <map>
#include <string>
#include "Direction.hpp"
/*
    Notebook.hpp.
    Author: Omer Rabin.
*/
using namespace std;

namespace ariel {
    class Notebook {
        vector<vector<vector<char>>> * notebook; // vector 3D represents the notebook
        // indexes of the notebook
        int end_page;
        map<int, int> max_row;

        // int end_col;
        // int end_row;
        //int start_page;
        // int start_col;
        // int start_row;
        int isFirstTime; 
    public:
        Notebook() {
            map<int, int> max_row;
            //start_page=0;
            // start_col=0;
            // start_row=0;
            // end_col=0;
            // end_row=0;
            end_page=0;
            this->notebook = new vector<vector<vector<char>>>('_');
            isFirstTime=0;
        }
        
        ~Notebook(){delete this->notebook;} // destructor
        void write(int page, int row, int col, Direction direction, string message);
        std::string read(int page, int row, int col, Direction direction, int length);
        void erase(int page, int row, int col, Direction direction, int length);
        void show(int page);
    };
}
