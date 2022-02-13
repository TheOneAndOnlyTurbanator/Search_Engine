#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "txt_parser.h"
#include "util.h"

using namespace std;

// Complete
void TXTParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    // No links are present in a text parser
    allOutgoingLinks.clear();

    // Initialize the current term and link as empty strings.
    string term = "";

    // Get the first character from the file.
    char c = istr.get();

    // Continue reading from the file until input fails.
    while(!istr.fail())
    {
        // Is c a character to split terms?
        if (!isalnum(c))
        {
            // If we have a term to add, convert it to a standard case and add it
            if(term != "")
            {
                term = conv_to_lower(term);
                allSearchableTerms.insert(term);
            }
            term = "";
        }
        // Otherwise we continually add to the end of the current term.
        else
        {
            term += c;
        }

        // Attempt to get another character from the file.
        c = istr.get();
    }
    // Since the last term in the file may not have punctuation, there may be a valid term in
    // the "term" variable, so we need to insert it into the allSearchableTerms set.
    if(term != "")
    {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
}

// Complete
std::string TXTParser::display_text(std::istream& istr)
{
    std::string retval;

    char c = istr.get();

    // Continue reading from the file until input fails.
    while (!istr.fail()) {
        retval += c;
        c = istr.get();
    }
    return retval;
}
