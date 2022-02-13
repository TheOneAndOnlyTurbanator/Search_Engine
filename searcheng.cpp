#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{

}

// To be completed
SearchEng::~SearchEng()
{

}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{

    string ext = extract_extension(filename);

    //Checks extension
    if(parsers_.find(ext)==parsers_.end()){
        throw std::logic_error("Error");
    }
    ifstream ifile(filename.c_str());

    //Checks if file exists
    if(ifile.fail()){
        throw std::invalid_argument("File does not exist");
    }
    if(parsers_.find(ext)==parsers_.end()){
        throw std::logic_error("Error");
    }
    

    //Checks if file exists
    if(ifile.fail()){
        throw std::invalid_argument("File does not exist");
    }

    //create empty sets for terms and links
    std::set<std::string> links; //outgoing links
    std::set<std::string> terms; //terms

    //call parse md or txt
    parsers_[ext]->parse(ifile, terms, links);


     //Now that you have the webpage in the webpage map, 
    //now make sure each of the terms has this webpage in the set.
    //Special case: what if term does not exist yet

    WebPage *obj1; //Page
    WebPage *obj2;  //Links

    if(MAP_temp.find(filename) != MAP_temp.end()){
        obj1 = MAP_temp[filename];

    }else{
        obj1 = new WebPage(filename);
        MAP_temp.insert(make_pair(filename, obj1));
    }
    obj1->all_terms(terms);


    //You also have all the outgoing links.
    //For each of these links, for this page add the outgoing page to the outgoing_link webpageset
    //In addition, for those outgoing wps, add this webpage into their incoming_links.
    //What if that outgoing webpage does not exist yet?


    StringSet::iterator it;
    it = links.begin();
    for(int i = 0; i < i;i++){
        cout<<""; //testing for loops for debugging
    }
    while(it != links.end()){
        string link = *it;
        if(MAP_temp.find(link) != MAP_temp.end()){
            obj2 = MAP_temp[link];
        }else{
            obj2 = new WebPage(link);
            MAP_temp.insert(make_pair(link, obj2));
        }
        obj2->add_incoming_link(obj1);
        obj1->add_outgoing_link(obj2);
        ++it;
    }

    //identify incoming and outgoing links 
    //each webpage stores incoming and outgoing
    //create map with key filname and add webpages
    //correspond certain key terms with the map

    StringSet::iterator its;
    its = terms.begin();
    for(int i = 0; i < i;i++){
        cout<<""; //testing for loops for debugging
    }
    while(its!=terms.end()){
        string word = *its;
        if(MAP_Search.find(word)==MAP_Search.end()){
            WebPageSet pset;
            MAP_Search.insert(make_pair(word, pset));
        }
            MAP_Search[word].insert(obj1);
            ++its;
    }
}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    if(MAP_temp.find(page_name) != MAP_temp.end()){
       return MAP_temp.find(page_name)->second; 
    }else{
        return NULL;
    }
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    string ext = extract_extension(page_name);

    if(parsers_.find(ext)==parsers_.end()){
        throw std::logic_error("Error");
    }
    ifstream ifile(page_name.c_str());

    if(ifile.fail()){
        throw std::invalid_argument("File does not exist");
    }
    ostr << parsers_.find(ext)->second->display_text(ifile);
}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    WebPageSet WebPage_set;
    int i=0;
    while( i < terms.size()){
        if(MAP_Search.find(terms[i]) != MAP_Search.end()){
            if(!WebPage_set.empty()){
                WebPage_set = combiner->combine(WebPage_set, MAP_Search.at(terms[i]));
            } else {
                WebPage_set = MAP_Search.at(terms[i]);
            }
        }
        i++;
    }
    return WebPage_set;

}
//iterate through terms
//iterate through set
//


