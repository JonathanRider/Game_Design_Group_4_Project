#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace {

}



class Config {

  static Config *singleton;

public:
  static Config *getSingleton(){return singleton;}

};
static Config *config(){
  return Config::getSingleton();
}

#endif
