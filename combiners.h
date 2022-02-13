#ifndef COMBINERS_H
#define COMBINERS_H

#include "searcheng.h"

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/

class DiffWebPageSetCombiner : public WebPageSetCombiner{
    private:
        WebPageSet C;
    public:
        WebPageSet combine(const WebPageSet& SetA, const WebPageSet& SetB );

};
class OrWebPageSetCombiner : public WebPageSetCombiner{
    private:
        WebPageSet C;
    public:
        WebPageSet combine(const WebPageSet& SetA, const WebPageSet& SetB );

};
class AndWebPageSetCombiner : public WebPageSetCombiner{
    private:
        WebPageSet C;
    public:
        WebPageSet combine(const WebPageSet& SetA, const WebPageSet& SetB );

};
#endif