#ifndef _TYPECONVERSION_H_
#define _TYPECONVERSION_H_

#include <string>
namespace typeconvert {
    float string2float(std::string &s);
    int string2int(std::string &s);
    std::string int2string(int i);
}
#endif
