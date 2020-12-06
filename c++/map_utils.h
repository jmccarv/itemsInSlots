//
//  map_utils.h
//  section counter
//
//  Created by Austin Ray on 12/5/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef map_utils_h
#define map_utils_h

#include <map>
#include <string>

// builds a map of all boundaries with their closed counts i.e.
//
// **|***|*|*|***|* =>
//
// 3,3
// 7,1
// 9,1
// 11,3
// 15,0
//
std::map<int, int> buildNodeMap( std::string sections ){
    
    if( sections.empty() ) return std::map<int, int>();
    
    int currBoundary = 0;
    std::map<int, int> nodes;
    bool closedSection = false;
    for( int i=0; i < sections.length(); ++i ){
        if( sections[i] == '|' ){
            currBoundary = i+1;
            closedSection = true;
            nodes.insert({currBoundary, 0});
        }
        else if ( sections[i] == '*' ){
            if ( currBoundary ){
                ++nodes[currBoundary];
                closedSection = false;
            }
        }
        else{
            throw std::invalid_argument("Invalid input: " + sections);
        }
    }
    
    if( !closedSection ) nodes[currBoundary] = 0;
    
    /*
    std::cout << "map: " << std::endl;
    for( auto pair : nodes ){
        std::cout << pair.first << ", " << pair.second << std::endl;
    }
    */
    return nodes;
}

#endif /* map_utils_h */
