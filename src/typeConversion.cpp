#include "typeConversion.h"
namespace typeconvert {
    float string2float(std::string &s){
      float r_val = 0;
      char const *tmp = s.c_str();
      int size = s.size();
      int magnifier = 1;
      int i;
      for(i=0; i < size ; i++){
          if ( tmp[i] == '.') {
            break;
          }
          else {
            r_val = r_val * 10 + tmp[i] - 48;
          }
      }
      for(i++; i< size; i++){
        magnifier *= 10;
        r_val = r_val * 10 + tmp[i] - 48;
      }
      return r_val/ (float) magnifier;
    }
    int string2int(std::string &s) {
      int r_val = 0;
      char const *tmp = s.c_str();
      int size = s.size();
      int i;
      for(i=0; i < size ; i++){
            r_val = r_val * 10 + tmp[i] - 48;
      }
      return r_val;
    }
}
