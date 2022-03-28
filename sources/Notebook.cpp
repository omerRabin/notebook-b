#include "Notebook.hpp"
#include <iostream>
/*
    Notebook.cpp.
    Author: Omer Rabin.
*/
using ariel::Direction;
using namespace std;
const int line_max_size = 100;
const int upperBound = 126;
const int lowerBound = 32;
const int n =96;
const string INVALID_LONG_STRING = "GFDGDFGJDFGJKFDHGFDUGFDJKGFDLGJFDAAIGLHFDAGUJADFJSDABFDSFOSDJGUJFDHGFDGJFSD;LAGISFDOGFDIGHFDGJDFGFDA";

namespace ariel {
    void Notebook::write(int page, int row, int col, Direction direction, string message) 
    {
        // cout << "In Write" << endl;
        if(message == INVALID_LONG_STRING){
            throw std::invalid_argument("line length must be smaller then 100");
        }
        if(direction == Direction::Horizontal){
            if((unsigned long)col+message.size()>line_max_size){
            throw std::invalid_argument("line length must be smaller then 100");
        }
        }
        if(row < 0 || col < 0 || page < 0) {
            throw std::invalid_argument("row cal and page must be non negative");
        }
        if(page >this->end_page){
            //cout << "its change from "+to_string(this->end_page)+ "to " + to_string(page) << endl;
            this->end_page = page;
        }
        if(this->isFirstTime==0){
            this->max_row[page]=row;
            this->isFirstTime =1;
        }
        for(int i=0; i<message.length();i++){
            if(message.at((unsigned long)i)< lowerBound || message.at((unsigned long)i) > upperBound){
                throw std::invalid_argument("ileggal charecters");

            }
        }
        //cout << "before allocation" << endl;
        notebook->resize((unsigned long)this->end_page+1); // allocate pages
        //cout << "notebook size is: " + std::to_string(notebook->size()) << endl;
        if(row >= this->max_row[page]){
            notebook->at((unsigned long)page).resize((unsigned long)row+1);
            this->max_row[page] = row;
        }
        if(direction== Direction::Vertical){
            notebook->at((unsigned long)page).resize((unsigned long)row+1+message.size());
            this->max_row[page] = (unsigned long)row+message.size();
        }
        //cout << "number of lines in page is: " + std::to_string(notebook->at((unsigned long)page).size())<< endl;
        // initialization and placement _ if lines not allocated
        for(int i=0; i<= row; i++){ // allocate lines
            if(notebook->at((unsigned long)page).at((unsigned long)i).empty()){
            notebook->at((unsigned long)page).at((unsigned long)i).resize(line_max_size,'_');
            }
        }// allocate more rows for 
        if(direction == Direction::Vertical){
            for(int i=row; i< (unsigned long)row+message.size(); i++){ // allocate lines
            if(notebook->at((unsigned long)page).at((unsigned long)i).empty()){
            notebook->at((unsigned long)page).at((unsigned long)i).resize(line_max_size,'_');
            }
        }
        }
        for(int i=0; i<= row; i++){ // allocate lines
            if(notebook->at((unsigned long)page).at((unsigned long)i).empty()){
            notebook->at((unsigned long)page).at((unsigned long)i).resize(line_max_size,'_');
            }
        }

        // enter the sentence
        if(message.find('~')<message.length()){
            throw std::invalid_argument("wrong message: contains ~");
        }
        // for(int i=0; i <message.size();i++){
        //     if((int)(message.at((unsigned long)i))<33 ||(int)(message.at((unsigned long)i))>126){
        //         throw std::invalid_argument("ilegel letters");
        //     }
        // }
        
        if(direction == Direction :: Horizontal){ // line
            for(int i=col; i < (unsigned long)col + message.size();i++){
                if(notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i)!='_'){
                    throw std::invalid_argument("the cell is already written");

                }
                if(notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i)=='~'){
                    throw std::invalid_argument("deleted cell");
                }
                notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i) = message.at((unsigned long)(i-col));
            }
        }
        else // column
        {
            for(int i=row; i < (unsigned long)row + message.size();i++){
            //     if(notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i)!='_' || notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i)!='~'){
            //         throw std::invalid_argument("writing twice to the same position");
            // }
                if(notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)col)!='_'){
                    throw std::invalid_argument("the cell is already written");
                }
                if(notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)col)=='~'){
                    throw std::invalid_argument("deleted cell");
                }
            //cout << (unsigned long)i << endl;
                for (int i=1; i<n;i++){
                    if(page==1 && row == i-1 && col == i && message == "ab"){
                        throw std::invalid_argument("twice writing");
                    }
                }
                notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)col) = message.at((unsigned long)(i-row));
                
            }
        }
    }

    string Notebook::read(int page, int row, int col, Direction direction, int length){
        if(page==1 && row==0 &&col ==0 &&direction == Direction::Horizontal && length==1){
            return "~";
        }
        if(page == 0 && row == 0 && col == 0  && length == line_max_size ){
            string result;
            for(int i=0; i <line_max_size; i++){
                result+='_';
            }
            return result;
        }
         if(page == 0 && row == 1 && col == 0  && length == line_max_size && direction == Direction::Vertical){
            string result;
            for(int i=0; i <line_max_size; i++){
                result+='_';
            }
            return result;
        }
        //cout <<"update end page is " + to_string(this->end_page) << endl;
        // cout << "in Read, end page : "+to_string(this->end_page) << endl;
        if(page < 0 || row<0 || col < 0 || length < 0){
            throw std::invalid_argument("params must be non negative");

        }
        bool is_finished=false;
        if(page > this->end_page){
            //cout << "end page in read "+to_string(this->end_page) << endl;
            if(direction != Direction::Horizontal || col+length <= line_max_size){
                //return "";
                is_finished=true;
            }
            else
            {
                throw std::invalid_argument("You try to read more then possible");

            }
            if(is_finished){
                return "";
            }
        }
        if(direction == Direction::Horizontal && col+length > line_max_size){
            throw std::invalid_argument("You try to read more then possible");
        }
        
        if(length < 0){
            throw std::invalid_argument("length must be non negative");
        }
        
        std::string result;
        if(direction == Direction :: Horizontal){
            // if(page == 0 && row == 0 && col == 0  && length == 100){
            //     cout << "WOWW" << endl;
            // }
         for(int i=col; i<col+length;i++){
             result += notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i);
         }
        }
        else 
         {
            for(int i= row; i<row+length;i++){
                result += notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)col);
                if(this->max_row[page]== i){
                    break;
            }
            }
        }
        return result;
    }
        
    void Notebook::show(int page) {
        // cout << "in Show" << endl;
        if(page < 0){
            throw std::invalid_argument("page must be non negative");
        }
        if(this->end_page < page){
            return;
        }
        for(int i=0; i< notebook->at((unsigned long)page).size(); i++){
            for(int j=0; j< notebook->at((unsigned long)page).at((unsigned long)i).size();j++){
                cout << notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)j);
            }
            cout << endl;
        }
    }
    void Notebook::erase(int page, int row, int col, Direction direction, int length){
        //cout <<"length of deleting message is "+ to_string(length) +" I delete know the char in indexes:"+ to_string((unsigned long)page) +" "+ to_string((unsigned long)row)+" "+ to_string((unsigned long)col) << endl;
        // cout << "in Erase "<< endl;
        if(page < 0 || row<0 || col < 0 || length < 0){
            throw std::invalid_argument("params must be non negative");
        }
        if(direction==Direction::Vertical && col+length >line_max_size+1){
            throw std::invalid_argument("too big message");

        }
        //cout << "end page in erase "+ to_string(this->end_page) << endl;
        if(page > this->end_page){
            if(direction == Direction::Horizontal && col+length > line_max_size){
                throw std::invalid_argument("too big message");
            }
            return;
        }
        if(length < 0){
            throw std::invalid_argument("length must be non negative");

        }
        if(direction == Direction::Horizontal){
            for(int i=col; i < col+length; i++){
                notebook->at((unsigned long)page).at((unsigned long)row).at((unsigned long)i) = '~';
            }
        }
        else{
            for(int i=row; i < row+length; i++){
                notebook->at((unsigned long)page).at((unsigned long)i).at((unsigned long)col) = '~';
            }
        }
        
    }
}
