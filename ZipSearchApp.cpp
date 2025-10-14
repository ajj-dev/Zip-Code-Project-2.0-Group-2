#include "PrimaryKeyIndex.h"
#include "CSVBuffer.h"
#include "ZipCodeRecord.h"
#include "ZipSearchApp.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

ZipSearchApp::ZipSearchApp(){

}

ZipSearchApp::ZipSearchApp(std::string file){
    fileName = file;
}

void ZipSearchApp::setDataFile(std::string file){
    fileName = file;
}

bool ZipSearchApp::search(int argc, char* argv[]){
    if(argc <= 1) return false; 
    std::vector<int> zips; //zips being searched for
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];// get argument
        if (arg.rfind("-Z", 0) == 0) { //if string argument indicator be found
            int zip = std::stoi(arg.substr(2)); //get zip code
            zips.push_back(zip); //add zip code to list
        }
    }
    CSVBuffer file;
    
    if(!file.openFile(fileName)) return false;

    index.createFromDataFile(file);

    for (const auto& zip : zips){
        //print the zip code
        for (const auto& offset : index.find(zip)){
            //print the memory offsets associated with the zip code
        }
    }
    
}

