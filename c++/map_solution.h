//
//  map_solution.h
//  section counter
//
//  Created by Austin Ray on 12/5/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef map_solution_h
#define map_solution_h

#include <cmath>
#include <iterator>
#include <map>
#include <string>

#include "map_utils.h"

namespace MapSolution {

enum class Direction { Forward = 1, Backward = -1, Stop = 0 };

template<typename Map, typename Compare>
typename Map::const_iterator closest( const Map& map, typename Map::mapped_type val, Compare compare ){
    if( map.empty() ) return map.end();
    
    auto end = map.end();
    auto result = end--;
    
    auto current = map.begin();
    auto prev = current, next = current;
    
    auto dist = ( std::distance(current, end) + 1 ) / 2; // ensure distance of 1 advances
    do {
        prev = current;
        std::advance(current, dist);
        next = current;
        
        auto resultCandidate = compare(current->first, val);
        if( resultCandidate.first ) {
            result = current;
        }
        else if ( !compare(val, current->first).first ) {
            result = current;
            break; // found boundary
        }
        
        dist = ( std::abs(dist) + 1 ) / 2 * static_cast<int>(resultCandidate.second);
        std::advance(next, dist);
      
    } while( next != prev && current != map.begin() && current != map.end() );
    
    return result;
}

std::size_t solve(const std::map<int,int>& sectionMap, std::size_t si, std::size_t ei ){
    if( sectionMap.empty() ) return 0;
    
    auto startFn = [](auto node, auto val){
        if( node < val ) return std::make_pair(false, Direction::Forward);
        return std::make_pair(true, Direction::Backward);
    };
    auto beginIt = closest( sectionMap, si, startFn);
    
    auto endFn = [](auto node, auto val){
        if( node < val ) return std::make_pair(true, Direction::Forward);
        return std::make_pair(false, Direction::Backward);
    };
    auto endIt = closest( sectionMap, ei, endFn );
    
    if( beginIt->first >= ei || endIt->first <= si ) return 0;
    
    return std::accumulate( beginIt, endIt, 0, [](int total, auto it){ return total + it.second; });
}

template<std::size_t N>
struct Solution {
    
    std::array<std::size_t, N>
    operator ()( std::string input
             , std::array<std::size_t,N> startIdxs
             , std::array<std::size_t,N> endIdxs ) {
        auto nodes = buildNodeMap( std::move(input) );
   
        std::array<std::size_t, N> solution;
        for( std::size_t i=0; i<startIdxs.size(); ++i ){
            auto si = startIdxs.at(i), ei = endIdxs.at(i);
            if ( ei < si ){
                throw std::invalid_argument("start idx must be le end idx");
            }
            
            solution[i] = solve(nodes, si, ei);
        }
        return solution;
    }
};

} // close MapSolution namespace

#endif /* map_solution_h */
