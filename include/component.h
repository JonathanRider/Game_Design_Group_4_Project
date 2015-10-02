#ifndef _COMPONENT_H
#define _COMPONENT_H_

class component
{
public:
  component(){}
  ~component(){}

  int getType(){return type;} //enum
  void setType(int t){type = t;}


private:
  int type;
};

#endif
