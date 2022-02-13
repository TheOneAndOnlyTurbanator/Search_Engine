#include "searcheng.h"
#include "combiners.h"

// Complete the necessary code

WebPageSet DiffWebPageSetCombiner :: combine(const WebPageSet& SetA, const WebPageSet& SetB ){
    C.clear();
    std::set<WebPage*>::const_iterator it;
    it = SetA.begin();
    while(it != SetA.end()){
        if(SetB.find(*it) == SetB.end()){
            C.insert(*it);
        }
        ++it;
    }
    return C;
}
WebPageSet OrWebPageSetCombiner :: combine(const WebPageSet& SetA, const WebPageSet& SetB ){
    C.clear();
    std::set<WebPage*>::const_iterator it; 
    std::set<WebPage*>::const_iterator it2;

    it = SetA.begin();
    while(it != SetA.end()){
        C.insert(*it);
        ++it;
    } 
    it2 = SetB.begin();
    while(it2 != SetB.end()){
        C.insert(*it2);
        ++it2;
    }  
    return C;

}
WebPageSet AndWebPageSetCombiner :: combine(const WebPageSet& SetA, const WebPageSet& SetB ){
    C.clear();
    std::set<WebPage*>::const_iterator it;
    it = SetA.begin();
    while(it != SetA.end()){
        if(SetB.find(*it) != SetB.end()){
            C.insert(*it);
        }
        ++it;
    }
    return C;

}