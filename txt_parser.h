#ifndef TXT_PARSER_H
#define TXT_PARSER_H

#include <string>
#include <istream>
#include <set>

#include "pageparser.h"

//***** THIS CLASS IS COMPLETED AND NEED NOT BE MODIFIED **********

class TXTParser : public PageParser 
{
public:
    /**
     * See documentation in PageParser class
     */
    void parse(std::istream& istr,
               std::set<std::string>& allSearchableTerms,
               std::set<std::string>& allOutgoingLinks);
    /**
     * See documentation in PageParser class
     */
    std::string display_text(std::istream& istr);

};

#endif
