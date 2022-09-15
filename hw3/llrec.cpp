#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    //if head is NULL, return NULL
    if(head == NULL){
        smaller = NULL;
        larger = NULL;
    }
    //if less than or equal to the pivot, add to smaller list and remove from head
    else if(head->val <= pivot){
        //check to make sure not causing segfault
        if(head->next != NULL){
            if(smaller != NULL && (smaller != head->next || larger != head->next)){
                smaller = NULL;
            }
            llpivot(head->next, smaller, larger, pivot);
            Node* temp = head->next;  
            head->next = smaller;
            smaller = head;
            head = temp; 
            
        }
        else{ 
            head->next = smaller;
            smaller = head;
            head = NULL;
        }
        
    }
    //if bigger than the pivot, add to bigger list and remove from head
    else if(head->val > pivot){
        //check to make sure not causing seg fault
        if(head->next != NULL){
            if(larger != NULL && (smaller != head->next || larger != head->next)){
                larger = NULL;
            }
            llpivot(head->next, smaller, larger, pivot);
            Node* temp = head->next;  
            head->next = larger;
            larger = head;
            head = temp;
        }
        else{ 
            head->next = larger;
            larger = head;
            head = NULL;
        }
    }

}

