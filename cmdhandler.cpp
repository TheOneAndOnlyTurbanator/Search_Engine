#include "cmdhandler.h"
#include "util.h"
using namespace std;

// Complete
QuitHandler::QuitHandler()
{

}

// Complete
QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler()
{

}

// Complete
PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// Add code for other handler class implementations below

AndHandler::AndHandler()
{
}
AndHandler::AndHandler(Handler* next)
    : Handler(next)
{
}
OrHandler::OrHandler()
{
}
OrHandler::OrHandler(Handler* next)
    : Handler(next)
{
}
DiffHandler::DiffHandler()
{

}
DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}
OutgoingHandler::OutgoingHandler()
{

}
OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}
IncomingHandler::IncomingHandler()
{

}
IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}




bool AndHandler::canHandle(const std::string& cmd) const{
    return cmd == "AND";
}
bool OrHandler::canHandle(const std::string& cmd) const{
    return cmd == "OR";  
}
bool DiffHandler::canHandle(const std::string& cmd) const{
    return cmd == "DIFF";
}
bool OutgoingHandler::canHandle(const std::string& cmd) const{
    return cmd == "OUTGOING";
}
bool IncomingHandler::canHandle(const std::string& cmd) const{
    return cmd == "INCOMING";
}




Handler::HANDLER_STATUS_T AndHandler:: process(SearchEng* eng, std::istream& instr, std::ostream& ostr){   
    string c;
    AndWebPageSetCombiner combiner;
    WebPageSet combiner2;
    vector<string> array;
    do{
        array.push_back(c);
    }
    while(instr >>c);
    combiner2 = eng->search(array, &combiner);
    display_hits(combiner2, ostr);
    return HANDLER_OK;
}
Handler::HANDLER_STATUS_T OrHandler:: process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string c;
    OrWebPageSetCombiner combiner;
    WebPageSet combiner2;
    vector<string> array;
    do{
        array.push_back(c);
    }
    while(instr >>c);
    combiner2 = eng->search(array, &combiner);
    display_hits(combiner2, ostr);
    return HANDLER_OK;
}
Handler::HANDLER_STATUS_T DiffHandler:: process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string c;
    DiffWebPageSetCombiner combiner;
    WebPageSet combiner2;
    vector<string> array;
    do{
        array.push_back(c);
    }
    while(instr >>c);
    combiner2 = eng->search(array, &combiner);
    display_hits(combiner2, ostr);
    return HANDLER_OK;
}
Handler::HANDLER_STATUS_T OutgoingHandler:: process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string c;
    WebPageSet WebPage_Set1;
    WebPage* strings_1;
    instr>>c;
    if(c==""){
        return HANDLER_ERROR;
    }else{
        strings_1 = eng->retrieve_page(c);
        if(strings_1==NULL){
        return HANDLER_ERROR;
        }else{
            WebPage_Set1 = strings_1->incoming_links();
            display_hits(WebPage_Set1, ostr);
            return HANDLER_OK;
        }
        
    }
    
}
Handler::HANDLER_STATUS_T IncomingHandler:: process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string c;
    WebPageSet WebPage_Set1;
    WebPage* strings_1;
    instr>>c;
    if(c==""){
        return HANDLER_ERROR;
    }else{
        strings_1 = eng->retrieve_page(c);
        if(strings_1==NULL){
        return HANDLER_ERROR;
        }else{
            WebPage_Set1 = strings_1->incoming_links();
            display_hits(WebPage_Set1, ostr);
            return HANDLER_OK;
        }
        
    }
    
}