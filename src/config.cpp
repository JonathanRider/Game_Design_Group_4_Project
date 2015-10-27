#include "config.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "typeConversion.h"


namespace {
  template<typename T>
  void set_variable(std::map<std::string,std::string> &map, std::string &conf_key, T &var, T (*callback)(std::string &) ) {
    std::map<std::string,std::string>::iterator it;
    if ((it= map.find(conf_key)) != map.end())
      var = callback(it->second);
  }
}


Config::Config(){
  std::string filename = "game.conf";
  read_configfile(filename);

  std::map<std::string,std::string>::iterator it;
  std::string str_tmp;

  //assign the value
  str_tmp = "interface.window.height";
  set_variable(options, str_tmp, appearance.window_height, typeconvert::string2int);
  str_tmp = "interface.window.width";
  set_variable(options, str_tmp, appearance.window_width, typeconvert::string2int);
}

void Config::read_configfile(std::string &filename){
  std::ifstream file;
  file.open (filename.c_str());
  if (!file){ //open error
    return;
  }
  for (std::string line; std::getline(file, line); ) {
       std::istringstream iss(line);
       std::string id, eq, val;

       bool error = false;

       if (!(iss >> id)) {
           error = true;
       }
       else if (id[0] == '#') {
         continue;
       }
       else if (!(iss >> eq >> val >> std::ws) || eq != "=" || iss.get() != EOF) {
         error = true;
       }
       if ( !error){
         options[id] = val;
       }
   }
   file.close();
}
