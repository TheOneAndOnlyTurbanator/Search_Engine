#include "md_parser.h"
#include "util.h"
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


#include "md_parser.h"
#include "util.h"

typedef std::vector<std::string> StrVec;
typedef std::vector<std::vector<std::string> > StrVecVec;

// prototype
testing::AssertionResult doMDParseCheck(
    const StrVec& test_patterns,
    const StrVecVec& expected_terms,
    const StrVecVec& expected_outgoing);

// definition
testing::AssertionResult doMDParseCheck(
    const StrVec& test_patterns,
    const StrVecVec& expected_terms,
    const StrVecVec& expected_outgoing)
{
    for(size_t i=0U; i < test_patterns.size(); i++)
    {
        stringstream ss(test_patterns[i]);
        set<string> terms;
        set<string> outgoing;
        MDParser mdp;
        mdp.parse(ss, terms, outgoing);
        for(string t : expected_terms[i])
        {
            bool found = (terms.end() != terms.find(t)) ||
                          (terms.end() != terms.find(conv_to_lower(t)) ||
                          (terms.end() != terms.find(conv_to_upper(t))) );
            if(!found)
            {
              return testing::AssertionFailure() << " Couldn't find " << t << "(or an upper/lower case variation) in your terms";
            }
            terms.erase(t);
            terms.erase(conv_to_lower(t));
            terms.erase(conv_to_upper(t));
        }
        if(0U != terms.size())
        {
            return testing::AssertionFailure() << terms.size() << " additional terms were returned from parsing beyond those expected.";
        }
        for(string t : expected_outgoing[i])
        {
            if(outgoing.end() == outgoing.find(t))
            {
              return testing::AssertionFailure() << " Couldn't find " << t << " in your outgoing links";
            }
            outgoing.erase(t);
        }
        if(0U != outgoing.size())
        {
            return testing::AssertionFailure() << outgoing.size() << " additional outgoing links were returned from parsing beyond those expected.";
        }
    }
    return testing::AssertionSuccess();
}

TEST(Parsers, MdParserSpecialStart)
{
    std::vector<std::string> test_patterns = 
    { "*Computer",
      "science ,104",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"Computer" },
      {"science", "104" }
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {},
      {}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserSpecialEnd)
{
    std::vector<std::string> test_patterns = 
    { "Computer!",
      "science- 104",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"Computer" },
      {"science", "104" }
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {},
      {}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserSpecialMiddle)
{
    std::vector<std::string> test_patterns = 
    { "Computer!Science",
      "104-103",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"Computer", "Science" },
      {"104", "103" }
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {},
      {}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserTextFull)
{
    std::vector<std::string> test_patterns = 
    { "Computer-Science#104*is really,really5times,really#-&great.Correct?",
      "U$SC tAblE CHAIR! ;desk class,room",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"Computer", "Science", "104", "is", "really", "really5times", "great", "Correct" },
      {"U", "SC", "tAblE", "CHAIR", "desk", "class", "room" },
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {},
      {}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserLinksSepStart)
{
    std::vector<std::string> test_patterns = 
    { "[*link1](folder/page.txt)",
      "[link2 !link3](pagea.md)",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"link1"},
      {"link2", "link3"}
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {"folder/page.txt"},
      {"pagea.md"}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserLinksSepEnd)
{
    std::vector<std::string> test_patterns = 
    { "[link1~](folder/page.txt)",
      "[link2^ link3](pagea.md)",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"link1"},
      {"link2", "link3"}
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {"folder/page.txt"},
      {"pagea.md"}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserLinksSepMiddle)
{
    std::vector<std::string> test_patterns = 
    { "[link0~link1](folder/page.txt)",
      "[link2^link3(link4](pagea.md)",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"link0", "link1"},
      {"link2", "link3", "link4"}
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {"folder/page.txt"},
      {"pagea.md"}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MdParserLinksFull)
{
    std::vector<std::string> test_patterns = 
    { "[lInK1](folder/page.txt)",
      "text[link](pagea.md)",
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"lInK1"},
      {"text", "link"}
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {"folder/page.txt"},
      {"pagea.md"}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
}

TEST(Parsers, MDWriteupCornerCases)
{
    std::vector<std::string> test_patterns = 
    { "[empty url afterwards]()",
      "[no closing square bracket",
      "[some text](url-to-nonexistent-file)",
      "[](some-file)"
    };

    std::vector<std::vector<std::string>> expected_terms = 
    { {"empty", "url", "afterwards"},
      {"no", "closing", "square", "bracket"},
      {"some", "text"},
      {}
    };
    std::vector<std::vector<std::string>> expected_outgoing = 
    { {},
      {},
      {"url-to-nonexistent-file"},
      {"some-file"}
    };

    EXPECT_TRUE(doMDParseCheck(test_patterns, expected_terms, expected_outgoing));
 }

