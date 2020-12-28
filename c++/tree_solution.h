//
//  tree_solution.h
//  section counter
//
//  Created by Austin Ray on 12/5/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef tree_solution_h
#define tree_solution_h

#include <vector>

#include "node.h"
#include "tree_utils.h"

namespace TreeSolution {

void findNodesInBoundary( std::vector<Node*>& nodes, Node* bst, std::size_t start, std::size_t end, Node* prev ){
    if( !bst ) return;
    
    //std::cout << bst->val << std::endl;
    if( bst->val >= start && bst->val < end ) {
        if( bst->val + bst->count < end ) {
            nodes.push_back(bst);
        }
    }

    if( bst->val >= start ) findNodesInBoundary( nodes, bst->left, start, end, bst );
    if( bst->val < end ) findNodesInBoundary( nodes, bst->right, start, end, bst );
    
}

std::size_t solve( Node* bst, std::size_t start, std::size_t end ){
    
    std::vector<Node*> sumNodes;
    sumNodes.reserve( ( end - start ) / 2 );
    
    findNodesInBoundary( sumNodes, bst, start, end, nullptr );
    
    auto acc = [](int total, Node* n2){ return total + n2->count; };
    return std::accumulate(sumNodes.begin(), sumNodes.end(), 0, acc);
}

template<std::size_t N>
struct Solution {

    std::array<std::size_t, N>
    operator()( std::string input
             , std::array<std::size_t,N> startIdxs
             , std::array<std::size_t,N> endIdxs ){
    
        std::array<std::size_t, N> solution;
        
        Node* bst = buildBst(std::move(input));
        //printTree(bst);
        
        if( !bst ) {
            solution.fill(0);
            return solution;
        }
    
        for( std::size_t i=0; i<startIdxs.size(); ++i ){
            auto si = startIdxs.at(i), ei = endIdxs.at(i);
            if ( ei < si ) throw std::invalid_argument("start idx must be le end idx");

            solution[i] = solve(bst, si, ei);
        }
    
        delete bst;
        return solution;
    }
};

} // close TreeSolution namespace


#endif /* tree_solution_h */
