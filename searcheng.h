#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "pageparser.h"



class WebPageSetCombiner
{
public:
    /**
     * Destructor
     */
    virtual ~WebPageSetCombiner() {}

    /**
     * Combines two sets of webpages into a resulting set based on some strategy
     *
     * @param[in] setA
     *   first set of webpages
     * @param[in] setB
     *   second set of webpages
     * @return set of webpages that results from the combination strategy
     */
    virtual
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB) = 0;
};

/**
 * Provides parsing and indexing of search terms as well as search operations.
 * Provides webpage display and retrieval.
 */
class SearchEng {
public:
    /**
    * Default constructor
    * [TO BE WRITTEN]
    *
    */
    SearchEng();

    /**
     * Destructor
     * [TO BE WRITTEN]
     */
    ~SearchEng();

    /**
     * Register a parser for a particular file extension
     * [COMPLETED]
     *
     * @param[in] extension
     *   File type/extension that should use this parser
     * @param[in] parser
     *   Pointer to the parser
     *  SearchEng will now be responsible for this parser and its deallocation.
     *
     * @throws std::invalid_argument if a parser for that extension already exists 
     */
    void register_parser(const std::string& extension, PageParser* parser);

    /**
     * Reads and parses files specified in the given index file
     * [COMPLETED]
     *
     * @param[in] index_file
     *   Name of the index file containing the list of files to read/parse
     *
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */

    void read_pages_from_index(const std::string& index_file);

    /**
     * Reads (and parses) a single file specified the given filename
     * [TO BE WRITTEN]
     *
     * @param[in] filename
     *   Name of the file to read/parse
     *
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     * @throws std::invalid_argument if the filename doesn't exist
     */
    void read_page(const std::string& filename);

    /**
     * Retrieves the WebPage object for a given page/file
     * [TO BE WRITTEN]
     *
     * @param[in] page_name
     *   Name of page/file to retrieve
     *
     * @return Pointer to the corresponding WebPage object.  Should not be used
     *   to alter or deallocate the object.   
     *   Return NULL is the page doesn't exist.
     */
    WebPage* retrieve_page(const std::string& page_name) const;

    /**
     * Displays the contents of the page/file
     * [TO BE WRITTEN]
     *
     * @param[inout] ostr
     *   Output stream to display the contnents
     * @param[in] page_name
     *   Name of page/file to display
     *
     * @throw std::invalid_argument if the page_name does not exist
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */
    void display_page(std::ostream& ostr, const std::string& page_name) const;

    /**
     * Uses the given search terms and combiner to find the set of webpages
     *  that match the query
     * [TO BE WRITTEN]
     *
     * @param[in] terms
     *   words/terms to search for
     * @param[in] combiner
     *   Combiner object that implements the strategy for combining the
     *   pages that contain each term (i.e. AND, OR, DIFF, etc.)
     *
     * @return Set of webpages matching the query
     */
    WebPageSet search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const;

private:
    /// Data member to associate a parser with a file extension
    std::map<std::string, PageParser*> parsers_;
    //map - key:terms value: set of all webpages of the term
    //map - Key: filename Value: of all webpages

    // Add other private helpers and data members as needed
    //  Consider how you will store
    //    - the webpages that match a particular search term
    //    - Webpage objects and ability to look them up via
    //       their page/filename
    std::map<std::string,WebPageSet>MAP_Search;
    std::map<std::string, WebPage*>MAP_temp;





};

#endif
