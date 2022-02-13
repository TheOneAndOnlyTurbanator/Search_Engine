#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();
     PARSE_STATE_T mode = NORMALTEXT;
     string term = "";
     char c = istr.get();
     while(!istr.fail())
    {
       

        if (mode == NORMALTEXT && c == '[') {
            mode = LINKTEXT;
        }
        else if(mode == LINKTEXT && c == ']'){
            mode = ISLINK;
            if(term !=""){
                allSearchableTerms.insert(term);
                term = "";
            }
            
        }
        else if (mode == ISLINK) {
            if (c == '[') {
                mode = LINKTEXT;
            }
            else if (c == '(') {
                mode = LINKURL;
            }
            
        }
    
       
       
        if (!isalnum(c))
        {

            if(mode == LINKURL && c != ')') {
                if(term != "")
                {
                    term += c;
                }
            }
            else {
            if(term != "")
            {
                
                if(mode == NORMALTEXT || mode == LINKTEXT){
                    term = conv_to_lower(term);
                    
                    allSearchableTerms.insert(term);
                   
                }
                else if(mode == LINKURL){
                    term = conv_to_lower(term);
                    
                    allOutgoingLinks.insert(term);
                    mode = NORMALTEXT;
                    
                }
            }
            term = "";
            }
        }
        else
        {
            term += c;
        }

        c = istr.get();
    }


    if(term != "")
    {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }


}


// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    std::string hello;
    char c = istr.get();
    while(!istr.fail()){
        if(c=='('){
            while(c!=')'){
                c=istr.get();
            }
            c =istr.get();
        }
        else{
            
            hello+=c;
            c = istr.get();
        }
    }
    hello=conv_to_lower(hello);
    return hello;
}


