#ifndef _COMPONENT_H
#define _COMPONENT_H_

class component
{
public:
  component(){}
  ~component(){}

  int getType(){return type;} //enum


private:
  int type;
};

#endif
