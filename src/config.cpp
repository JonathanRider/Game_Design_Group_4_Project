#include "config.h"


Config * Config::singleton;

void Config::init(){singleton = new Config();}
