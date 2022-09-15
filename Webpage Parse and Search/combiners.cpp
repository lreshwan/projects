#include "searcheng.h"
#include "combiners.h"

// Complete the necessary code
WebPageSet AndWebPageSetCombiner :: combine(const WebPageSet& setA, const WebPageSet& setB){
    combinedSet.clear();
    std::set<WebPage*>::iterator i;

    //find intersections in values and then add to combined set
    for(i = setB.begin(); i != setB.end(); ++i){
        if(setA.find(*i) != setA.end()){
            combinedSet.insert(*i);
        }
    }
    return combinedSet;
}

WebPageSet OrWebPageSetCombiner :: combine(const WebPageSet& setA, const WebPageSet& setB){
    combinedSet.clear();
    std::set<WebPage*>::iterator i;

    //add all webpages in setA to combined webpage set 
    for(i = setA.begin(); i != setA.end(); ++i){
        combinedSet.insert(*i);
    }

    //add all webpages in setB to combined webpage set
    for(i = setB.begin(); i != setB.end(); ++i){
        combinedSet.insert(*i);
    }
    return combinedSet;
}

WebPageSet DiffWebPageSetCombiner :: combine(const WebPageSet& setA, const WebPageSet& setB){
    combinedSet.clear();
    std::set<WebPage*>::iterator i;

    //finds all webpages that do not intersect and adds to combined set
    for(i = setA.begin(); i != setA.end(); ++i){
        if(setB.find(*i) == setB.end()){
            combinedSet.insert(*i);
        }
    }
    return combinedSet;
}