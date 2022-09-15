#include "equal-paths.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


// You may add any prototypes of helper functions here

int leftHeight(Node* root);
int rightHeight(Node* root);

bool equalPaths(Node * root)
{
    //checks for NULL case
    if(root == NULL){
        return true;
    }
    //if not null, determines if path lengths are equal or not
    else{
        int leftlen = leftHeight(root) - 1;
        int rightlen = rightHeight(root) - 1;

        if(leftlen == 0 && rightlen == 1){
            return true;
        }
        if(leftlen == 1 && rightlen == 0){
            return true;
        }

        //cout << leftlen << " " << rightlen << endl;

        if(leftlen == rightlen){
            return true;
        }
        else{
            return false;
        }
    }

}

//finds the height of the left
int leftHeight(Node* root){
    int height;
    if(root == NULL){
        return 0;
    }

    if(root->left != NULL && root->right != NULL){
        if(root->left->left == NULL && root->right->left != NULL){
            return 1000;
        }
    }
    
    height = leftHeight(root->left) + 1;

    
    return height;
}


//finds height of the right
int rightHeight(Node* root){
    int height;
    if(root == NULL){
        return 0;
    }

    if(root->left != NULL && root->right != NULL){
        if(root->right->right == NULL && root->left->right != NULL){
            height = rightHeight(root->left) + 1;
        }
    }
    
    height = rightHeight(root->right) + 1;

    return height;
}

