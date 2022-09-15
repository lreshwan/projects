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

    // Complete your code below
    bool openingBracket = false;
    bool needNext = true;
    string searchTerm = "";
    string linkTerm = "";
    char c = istr.get();

    //parses through terms getting links and search terms and adding them to allSearchableTerms and allSearchableLinks
    while(!istr.fail()){
        if(!isalnum(c)){
            if(searchTerm != ""){
                searchTerm = conv_to_lower(searchTerm);
                allSearchableTerms.insert(searchTerm);
            }
            searchTerm = "";
            if(c == '['){
                openingBracket = true;
            }
            else if(c == ']' && openingBracket){
                c = istr.get();
                if(c == '('){
                    c = istr.get();
                    while (c != ')')
                    {
                        linkTerm += c;
                        c = istr.get();
                    }
                    if (linkTerm != ""){
                        linkTerm = conv_to_lower(linkTerm);
                        allOutgoingLinks.insert(linkTerm);
                    }
                    linkTerm = "";
                }
                else{
                    needNext = false;
                }
            }
        }
        else{
            searchTerm += c;
        }
        if(needNext){
            c = istr.get();
        }
        else{
            needNext = true;
        }
        
    }
    if(searchTerm != "")
    {
        searchTerm = conv_to_lower(searchTerm);
        allSearchableTerms.insert(searchTerm);
    }
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    std::string retval;

    char c = istr.get();

    // Continue reading from the file until input fails.
    //prints everything but the links
    while (!istr.fail()) {
        if(c == ']' ){
            retval += c;
            c = istr.get();
            if(istr.fail()){
                break;
            }
            if(c == '('){
                while(c != ')' && !istr.fail()){
                    c = istr.get();
                }
                c = istr.get();
                if(istr.fail()){
                    break;
                }
            }
        }
        retval += c;
        c = istr.get();
    }
    return retval;

}


