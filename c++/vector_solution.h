//
//  vector_solution.h
//  section counter
//
//  Created by Austin Ray on 12/27/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#ifndef vector_solution_h
#define vector_solution_h

#include <array>
#include <iterator>
#include <tuple>
#include <vector>

namespace VectorSolution {


// isBoundary, boundaryNum, sectionCount, runningSectionCountTotal
using InputData = std::tuple<bool,std::size_t,std::size_t,std::size_t>;

// given the begin and end iterators of a section, fills metadata for section count in corresponding location of section in output
// and returns the section count
std::size_t
fillInputData( std::vector<InputData>& output
             , std::vector<InputData>::iterator begin
             , std::vector<InputData>::iterator end
             , std::size_t currBoundary
             , std::size_t runningSectionTotal ){
    auto sectionCount = end == output.end() ? 0 : std::distance( begin, end ) - 1;
    runningSectionTotal += sectionCount;
    auto count{0};
    while( begin != end ){
        *begin = InputData{!(count++), currBoundary, sectionCount, runningSectionTotal};
        ++begin;
    }
   
    return sectionCount;
}

std::vector<InputData>
buildInputData( const std::string& input ){
    
    if( input.empty()) return std::vector<InputData>();
    
    std::vector<InputData> inputData( input.size() );
    
    auto currBoundaryIt = input.end(), currIt = input.begin();
    std::size_t currBoundary = 0, runningSectionTotal = 0;
    
    while( currIt != input.end() ){
        if( *currIt == '|' ){
            if( currBoundaryIt != input.end() ){
                auto inputBeginIt = inputData.begin(), inputEndIt = inputData.begin();
                std::advance( inputBeginIt, std::distance( input.begin(), currBoundaryIt ) );
                std::advance( inputEndIt, std::distance( input.begin(), currIt ) );
                
                runningSectionTotal += fillInputData( inputData, inputBeginIt, inputEndIt, ++currBoundary, runningSectionTotal );
            }
            currBoundaryIt = currIt;
        }
        else if( *currIt != '*' ) throw std::invalid_argument( "input may only contain '|' or '*'" );
        
        ++currIt;
    }
    auto inputBeginIt = inputData.begin();
    std::advance( inputBeginIt, std::distance( input.begin(), currBoundaryIt ) );
    
    fillInputData( inputData, inputBeginIt, inputData.end(), currBoundary, runningSectionTotal );
    
    return inputData;
}

std::size_t
solve( const std::vector<InputData>& inputData, std::size_t beginIdx, std::size_t endIdx ){
    beginIdx -= 1; endIdx -= 1;
    if( beginIdx < 0 || beginIdx > inputData.size() ||
        endIdx < 0 || endIdx > inputData.size() ) throw std::invalid_argument("invalid begin/end");
    
    bool beginIsBoundary, endIsBoundary;
    std::size_t beginBoundary, endBoundary, beginSectionCount, endSectionCount, beginRunningTotal, endRunningTotal;
    
    std::tie(beginIsBoundary, beginBoundary, beginSectionCount, beginRunningTotal) = inputData[beginIdx];
    std::tie(endIsBoundary, endBoundary, endSectionCount, endRunningTotal) = inputData[endIdx];
    
    std::size_t result = 0;

    if( endBoundary > beginBoundary ){
        result = endRunningTotal - endSectionCount; // section total of every section before end boundary
        result -= ( beginRunningTotal - beginSectionCount ); // subtract total of every section before begin
        if( !beginIsBoundary ) result -= beginSectionCount; // if begin is not on boundary, subtract begin section
    }
    
    return result;
}

template<std::size_t N>
struct Solution {

    std::array<std::size_t, N>
    operator()( std::string input
             , std::array<std::size_t,N> startIdxs
             , std::array<std::size_t,N> endIdxs ){
    
        std::array<std::size_t, N> solution;
        
        auto inputData = buildInputData( input );
        /*
        std::cout << "input: " << input << " metadata: " << std::endl;
        for( auto& data : inputData ){
            std::cout << std::get<0>(data) << ", "
                      << std::get<1>(data) << ", "
                      << std::get<2>(data) << ", "
                      << std::get<3>(data) << std::endl;
        }
        */
        for( std::size_t i=0; i<startIdxs.size(); ++i ){
            auto si = startIdxs.at(i), ei = endIdxs.at(i);
            if ( ei < si ) throw std::invalid_argument("start idx must be le end idx");

            solution[i] = solve(inputData, si, ei);
        }
        
        return solution;
    }
};

} // close namespace VectorSolution

#endif /* vector_solution_h */
