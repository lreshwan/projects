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
    //parsers_.clear();
    //file.clear();
    //set.clear();
}

// To be completed
SearchEng::~SearchEng()
{
    std::map<std::string, PageParser*> :: iterator i;
    for(i = parsers_.begin(); i != parsers_.end(); ++i){
        delete i->second;
    }

    std::map<std::string, WebPage*> :: iterator j;
    for(j = file.begin(); j != file.end(); ++j){
        delete j->second;
    }
    
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

    //check for errors
    string ext = extract_extension(filename);

    if(parsers_.end() == parsers_.find(ext)){
        throw std::logic_error("No parser for the given filetype.");
    }

    WebPage* temp;
    std::set<std::string> outGoingLinks;
    std::set<std::string> storedTerms;
    ifstream inputFile(filename);

    if(inputFile.fail()){
        throw::invalid_argument("This page does not exist.");
    }

    if(file.find(filename) != file.end()){
        temp = file.find(filename)->second;
    }
    else{
        temp = new WebPage(filename);
        file.insert(make_pair(filename, temp));
    }

    parsers_.find(ext)->second->parse(inputFile, storedTerms, outGoingLinks);

    temp->all_terms(storedTerms);

    //read in page and set incoming and outgoing links
    WebPage* temp2;
    StringSet::iterator i;
    for(i = outGoingLinks.begin(); i != outGoingLinks.end(); ++i){
        if(file.find(*i) != file.end()){
            temp2 = file.at(*i);
        }
        else{
            temp2 = new WebPage(*i);
            file.insert(make_pair(*i, temp2));
        }
        temp2->add_incoming_link(temp);
        temp->add_outgoing_link(temp2);
    }
    
    //read in page and deal with the terms and set them
    for(i = storedTerms.begin(); i != storedTerms.end(); ++i){
        if(set.find(*i) == set.end()){
            
            WebPageSet holderSet;
            holderSet.insert(temp);
            set[*i] = holderSet;
        }
        else{

            set[*i].insert(temp);

        }
    }


    

    

}


// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    if(file.end() != file.find(page_name)){
        return file.find(page_name)->second;
    }
    else{
        return NULL;
    }
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    //check for errors
    string ext = extract_extension(page_name);
    if(file.end() == file.find(page_name)){
        throw std::invalid_argument("File doesn't exist.");
    }
    else if(parsers_.end() == parsers_.find(ext)){
        throw std::logic_error("No parser for the given filetype.");
    }
    ifstream inputFile(page_name);
    if(inputFile.fail()){
        throw::invalid_argument("This page does not exist.");
    }

    //display the page
    ostr << parsers_.find(ext)->second->display_text(inputFile);
    inputFile.close();

}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{

    WebPageSet tempSet;
    
    //search through set for the terms
    for(int i = 0; i < (int)terms.size(); i++){
        if(set.find(terms[i]) != set.end()){
            if(tempSet.empty() == false){
                tempSet = combiner->combine(tempSet, set.find(terms[i])->second);
            }
            else{
                tempSet = set.find(terms[i])->second;
                
            }
        }
    }
    return tempSet;
}

// Add private helper function implementations here

