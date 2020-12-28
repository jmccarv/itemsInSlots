//
//  tree_utils.h
//  section counter
//
//  Created by Austin Ray on 12/5/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef tree_utils_h
#define tree_utils_h

#include <exception>
#include <iterator>
#include <map>
#include <vector>

#include "node.h"

template<typename Iterable, typename It>
Node* buildTree( Iterable& nodes, It minNode, It maxNode ){
    
    if( minNode == maxNode ){
        return new Node( minNode->val, minNode->count );
    }
    else if ( minNode == nodes.end() )
    {
        throw std::invalid_argument("empty nodes");
    }
    
    auto distance = std::distance( minNode, maxNode );
    auto midpoint = distance / 2;
    auto midNode = minNode;
    
    std::advance(midNode, midpoint);
    
    auto head = new Node(midNode->val, midNode->count);
    
    auto minToMid = std::distance(minNode, midNode);
    if( minToMid <= 1 )
    {
        if( minToMid == 1 ){
            head->left = new Node(minNode->val, minNode->count);
        }
    }
    else{
        auto minMax = midNode;
        head->left = buildTree(nodes, minNode, --minMax);
    }

    auto midToMax = std::distance(midNode, maxNode);
    if( midToMax <= 1 ){
        if( midToMax == 1 ){
            head->right = new Node(maxNode->val, maxNode->count);
        }
    }
    else{
        auto maxMin = midNode;
        head->right = buildTree(nodes, ++maxMin, maxNode);
    }
    return head;
}

Node* buildBst( std::string sections ){

    //auto nodes = buildNodeMap( std::move(sections) );
    std::vector<Node> nodes;
    nodes.reserve( sections.length() / 2 );
    
    Node curr{0, 0};
    for( auto i = 0; i < sections.length();  ++i ){
        if( sections[i] == '|' ){
            if( curr.val ) nodes.push_back( curr ); // section was closed
            curr.val = i+1;
            curr.count = 0;
        }
        else if ( sections[i] == '*' ) ++curr.count;
        else throw std::invalid_argument("sections string must only contain '|' or '*' chars");
    }
    
    if( !curr.val ){ // no boundaries
        return nullptr;
    }
    
    curr.count = 0;
    nodes.push_back(curr);
    
    return buildTree(nodes, nodes.begin(), --nodes.end());
}

void printTree(Node* bst){
    if(!bst) return;
    
    std::vector<std::pair<Node*,std::string>> queue;
    queue.push_back({bst,""});
    
    while(!queue.empty()){
        auto curr = queue.back();
        queue.pop_back();
        std::cout << curr.second << ":" << curr.first->val << "," << curr.first->count << std::endl;
        if( curr.first->left ){
            queue.push_back({curr.first->left, curr.second+"L"});
        }
        if( curr.first->right ){
            queue.push_back({curr.first->right, curr.second+"R"});
        }
    }
}

#endif /* tree_utils_h */
