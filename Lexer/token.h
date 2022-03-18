#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <string>



class Token
{
private:
     std::string value;
     std::string type;
     int state=0;
public:
    Token();
    bool valid(char c,char type);
    //std::string getnext(char type,char element);
    std::string printToken();
};

bool Token::valid(char c,char type){
    if(type=='n' && state==0 {
        return true;
    }
    return false;
}

std::string Token::printToken(){
    std::string s=(value + "es de tipo"+ type);
    state=0;
    type="";
    return s;
}





#endif