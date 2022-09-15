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
IncomingHandler::IncomingHandler()
{

}

// Complete
IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}

// Complete
Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    instr >> name;

    WebPage* retrieved = eng->retrieve_page(name);

    if(name == ""){
        return HANDLER_ERROR;
    }
    else{
        if(retrieved == NULL){
            return HANDLER_ERROR;
        }
        else{
            display_hits(retrieved->incoming_links(), ostr);
            return HANDLER_OK;
        }
    }
    
}

OutgoingHandler::OutgoingHandler()
{

}

// Complete
OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

// Complete
Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    instr >> name;

    WebPage* retrieved = eng->retrieve_page(name);

    if(name == ""){
        return HANDLER_ERROR;
    }
    else{
        if(retrieved == NULL){
            return HANDLER_ERROR;
        }
        else{
            display_hits(retrieved->outgoing_links(), ostr);
            return HANDLER_OK;
        }
    }
    
}

AndHandler::AndHandler()
{

}

// Complete
AndHandler::AndHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";

}

// Complete
Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    AndWebPageSetCombiner tempCombine;
    string tempString;
    vector<string> tempVector;

    while(instr >> tempString){
        tempVector.push_back(tempString);
    }

    WebPageSet tempSet;

    tempSet = eng->search(tempVector, &tempCombine);

    display_hits(tempSet, ostr);

    return HANDLER_OK;

}

OrHandler::OrHandler()
{

}

// Complete
OrHandler::OrHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";

}

// Complete
Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    OrWebPageSetCombiner tempCombine;
    string tempString;
    vector<string> tempVector;

    while(instr >> tempString){
        tempVector.push_back(tempString);
    }

    WebPageSet tempSet;

    tempSet = eng->search(tempVector, &tempCombine);

    display_hits(tempSet, ostr);

    return HANDLER_OK;

}

DiffHandler::DiffHandler()
{

}

// Complete
DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";

}

// Complete
Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    DiffWebPageSetCombiner tempCombine;
    string tempString;
    vector<string> tempVector;

    while(instr >> tempString){
        tempVector.push_back(tempString);
    }

    WebPageSet tempSet;

    tempSet = eng->search(tempVector, &tempCombine);

    display_hits(tempSet, ostr);

    return HANDLER_OK;

}
