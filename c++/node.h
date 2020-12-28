//
//  node.h
//  section counter
//
//  Created by Austin Ray on 12/5/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef node_h
#define node_h

struct Node{
    int val = -1;
    int count = 0;
    
    Node* left = nullptr;
    Node* right = nullptr;
    
    Node() = default;
    ~Node(){
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
    
    Node(int boundaryStartIdx, int cnt=0){
        val = boundaryStartIdx;
        count = cnt;
    }
    
};


#endif /* node_h */
