#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

//
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
// Add any initializers here
    : node_(node), list_(list)
{
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    //if the nodes are equal return true
    if(this->node_ == rhs.node_){
        return true;
    }
    else{
        return false;
    }
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    //if the token is valid return true
    if (this->isValid()){
        return true;
    }
    else{
        return false;
    }
    
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    //throws logic error if the node is a nullptr, returns message otherwise
    if(this->node_ == nullptr){
        throw std::logic_error("Token references an invalid message");
    }
    return node_->msg_;
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    //throws logic error if the node is a nullptr, return message otherwise
    if(this->node_ == nullptr){
        throw std::logic_error("Token references an invalid message");
    }
    return node_->msg_;
}

// To be completed - must adhere to any requirements in the .h file
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

//
// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList()
// Add any initializers here
:heads_(1, nullptr), tail_(nullptr)
{
    this->labels_.push_back("all");
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    clear();
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    MsgNode* temp = heads_[0];

    //deletes each node
    if(temp != nullptr){
        while(temp->next_[0] != nullptr){
            temp = temp->next_[0];
            delete temp->prev_[0];
        }
        heads_[0] = nullptr;
        tail_ = nullptr;
        delete temp;
    }  
    
}

//
// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    return !heads_[0];
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

//
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    MsgNode* n1 = new MsgNode(msg);

    //if tail is a nullptr, no messages in all, add message as the head and tail
    if(this->tail_ == nullptr){
        this->heads_[0] = n1;
        this->tail_ = n1;
    }
    //if tail isnt a nullptr, attaches to back of "all" label 
    else{
        n1->next_[0] = nullptr;
        n1->prev_[0] = tail_;
        this->tail_->next_[0] = n1;
        this->tail_ = n1;
    }

    return MsgToken(n1, this);
    
}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    if(!token.isValid()){
        return;
    }
    
    else{
        //runs unlabel on all labels but all to remove node but not from all label
        for(size_t i = 1; i < labels_.size(); i++){
            LabelType temp = labels_[i];
            unlabel(token, temp);
        }


        MsgNode* tempNext = token.node_->next_[0];
        MsgNode* tempPrev = token.node_->prev_[0];

        //removes the node from the all label
        if(tempPrev != nullptr){
            tempPrev->next_[0] = tempNext;
            tempNext->prev_[0] = tempPrev;
        }
        else{
            heads_[0] = tempNext;
        }
    //deletes node
    delete token.node_;
    }

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    if(label == "all"){
        return;
    }
    //first case, new label, therefore add new label to back of label array
    //also add new head ptr to heads for new label bc new head of list
    size_t index = findLabelIndex(label);
    if(index == INVALID_LABEL){
        this->labels_.push_back(label);//ask which is correct(this or using this-> instead of token.)
        this->heads_.push_back(token.node_);
        token.node_->next_.resize(heads_.size(), nullptr);
        token.node_->prev_.resize(heads_.size(), nullptr);
        token.node_->labelled_.resize(heads_.size(), false);
        token.node_->labelled_[labels_.size()-1] = true;
    }
    //not new label
    else{
        //resizes vector if neccesary and changes labelled_ vector to be true at that index
        if(index > (token.node_->labelled_.size()-1)){
            token.node_->labelled_.resize(index + 1, false);
            token.node_->prev_.resize(index + 1, nullptr);
            token.node_->next_.resize(index + 1, nullptr);
            token.node_->labelled_[index] = true;
        }
        else{
            token.node_->labelled_[index] = true;
        }
        
        MsgNode* temp = token.node_->prev_[0];

        //looks backwards for node before it in given label and properly configures next and prev pointers for the nodes
        while(temp != nullptr){
            if((temp->labelled_.size() >= (index+1))
                && (temp->labelled_[index] == true)){
                temp->next_[index] = token.node_;
                token.node_->prev_[index] = temp;
                break;
            }
            else{
                temp = temp->prev_[0];
            }
        }
        if(temp == nullptr){
            this->heads_[index] = token.node_;
        }
        MsgNode* temp2 = token.node_->next_[0];

        //looks forwards for node before it in given label and properly configures next and prev pointers for the nodes
        while(temp2 != nullptr){
            if((temp2->labelled_.size() >= (index+1))
                && (temp2->labelled_[index] == true)){
                temp2->prev_[index] = token.node_;
                token.node_->next_[index] = temp2;
                break;
            }
            else{
                temp2 = temp2->next_[0];
            }
        }
        

        
        
    }
        
}

//seg fault somewhere
// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    size_t index = findLabelIndex(label);
    if(index==INVALID_LABEL){
        throw std::out_of_range("Non-Existent Label Provided");
    }
    if(label == "all"){
        return;
    }
    //properly resizes the vectors
    if(token.node_->labelled_.size() < index+1){
        token.node_->labelled_.resize(index, false);
        token.node_->next_.resize(index, nullptr);
        token.node_->prev_.resize(index, nullptr);
    }
    //returns nothing if not a part of the label
    if(token && token.node_->labelled_[index]==false){
        return;
    }
    else{
        MsgNode* tempPrev = token.node_->prev_[index];
        MsgNode* tempNext = token.node_->next_[index];

        //sets the nodes before and after in the label to point to eachother as the node in the middle was removed
        if(tempPrev != nullptr)
            tempPrev->next_[index] = tempNext;
        else
            heads_[index] = tempNext;
        if(tempNext != nullptr)
            tempNext->prev_[index] = tempPrev;

        //resizes vectors and sets proper data for the unlabeled node
        size_t i = index;
        while(token.node_->labelled_[i] == false){
            if(token.node_->labelled_[i-1] == true){
                token.node_->labelled_.resize(i);
                token.node_->next_.resize(i);
                token.node_->prev_.resize(i);
                break;
            }
            else{
                i--;
            }
        }
    }
}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{
    //looks in the index given and goes through each node adding to the iterator, stopping at the given index
    size_t position = this->getLabelIndex(label);
    MsgNode* n = this->heads_[position];
    size_t i = 0;
    while(n != nullptr){
        if(i == index){
            return MsgToken(n, this);
        }
        n = n->next_[position];
        i++;
    }
    //if not enough nodes for the index given, returns end()
    return end();
    
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

//
// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    //finds label index, returns invalid label if not
    size_t temp = 0;
    while(label != labels_[temp] && temp < labels_.size()){
        temp++;
    }
    if(temp >= labels_.size()){
        return INVALID_LABEL;
    }
    else{
        return temp;
    }

}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


