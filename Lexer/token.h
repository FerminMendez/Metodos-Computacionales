#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <string>



class Token
{
private:
     std::string value;
     
public:
    Token();
    std::string getnext(std::string file, int* current);
};

std::string Token::getnext(std::string file, int* current){
    std::string sol=" "+file[*current];
    return sol;
}

class Kind
{
public:
    Kind();
    ~Kind();
    int *state;
    virtual char validchar(char c);

};

Kind:: Kind(){
    *state=0;
}
Kind:: ~Kind(){
    delete state;
}

class Number: public Kind
{
public:
    Number();
    char validchar(char c);
};

char Number:: validchar(char c){
    switch (*state)
    {
    case 0:
        if(c==0|| c==1  || c==2){
            *state=1;
            return 'v';
        }
    case 1:
        if(c==0|| c==1  || c==2){
            return 'v';
        }
    return 'f';
}




#endif