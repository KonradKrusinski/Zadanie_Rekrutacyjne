#include "file.h"

#include<iostream>
#include<stdio.h>

File::File(string givenPath,ResultContainer* container){
    path=givenPath;
    resultContainer=container;
}

void File::run(){

    int words=0,letters=0,emptyLines=0,nonEmptyLines=0;
    ifstream file;
    file.open(path, ifstream::in);
    
    if(!file.is_open()){
        return;
    }

    while(true){

        string line;
        getline(file,line);
        
        if(line.empty()){

            emptyLines++;
            if(file.eof()) break;
            continue;
        }

        nonEmptyLines++;

        bool wordEndedFlag=true;

        for(size_t i = 0; i<line.size(); i++){

            if(line[i]==' ' || line[i]=='\n' || line[i]=='\t'){
                wordEndedFlag=true;
            }else if(wordEndedFlag){
                wordEndedFlag=false;
                words++;
            }

            if(isalpha(line[i])) letters++;
        }

        if(file.eof()) break;
    }
    file.close();

    resultContainer -> addData(words,emptyLines,nonEmptyLines,letters);
}