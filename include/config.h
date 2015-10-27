#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "constants.h"
#include <map>
#include <string>

namespace config_internal { //this namespace is not supposed to use outside the file
  class Appearance {
  public:
    Appearance():
    window_height(600),window_width(800){}
    int window_height;
    int window_width;
  };
}


class Config {

    std::map<std::string, std::string> options;
    void read_configfile(std::string &filename);
  public:
    Config();
    config_internal::Appearance appearance;
};
#endif
