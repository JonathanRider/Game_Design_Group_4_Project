#include "typeConversion.h"
#include <cmath>
#define MAX_DIGITS 20
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
    int string2int(const char *s){
      std::string number = s;
      return string2int(number);
    }
    std::string int2string(int number){
      char char_string[MAX_DIGITS + 1];
      int i;
      bool positive = number >=0?true:false;
      number = std::abs(number);
      int tmp_num = number;
      if (number == 0) {
        return std::string("0");
      }
      for (i = 0; tmp_num > 0; tmp_num /= 10, i++);
      if ( i > MAX_DIGITS ) {
        i = MAX_DIGITS;
      }
      char_string[i] = '\0';
      for (i--; i >= 0 ; number /= 10, i--){
        char_string[i] = number % 10 + 48;
      }
      if (positive)
        return std::string(char_string);
      else
        return "-" + std::string(char_string);
    }
}
