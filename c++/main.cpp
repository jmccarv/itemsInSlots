//
//  main.cpp
//  section counter
//
//  Created by Austin Ray on 12/3/20.
//  Copyright © 2020 Austin Ray. All rights reserved.
//

#include <iostream>

#include <tuple>
#include <string>
#include <array>
#include <type_traits>
#include <numeric>
#include <chrono>
#include <functional>

#include "map_solution.h"
#include "tree_solution.h"

/*
 * Compile-time input validation
 */
template<typename Tuple>
constexpr void validate_input( const Tuple& input ){
    static_assert(std::tuple_size_v<Tuple> == 3);
    static_assert(std::is_constructible_v<std::string, decltype(std::get<0>(input))>);
    static_assert(std::tuple_size_v<std::tuple_element_t<1, Tuple>> == std::tuple_size_v<std::tuple_element_t<2, Tuple>>);
}

template<template<std::size_t tupSize> class Fn
                , typename Tuple
                , std::size_t tupleSize = std::tuple_size_v<std::tuple_element_t<1, Tuple>>
                >
auto invoke_solution( const Tuple& t ){

    validate_input(t); // arrays are same size
    std::cout << "input: " << std::get<0>(t) << std::endl;
    
    auto begin = std::chrono::system_clock::now();
    auto result = std::apply(Fn<tupleSize>(), t);
    auto end = std::chrono::system_clock::now();
    
    std::cout << "solution wall time: " << std::chrono::duration<double>(end-begin).count() << "s" << std::endl;
    
    
    for( std::size_t i = 0; i < tupleSize; ++i ){
        const auto& starts = std::get<1>(t);
        const auto& ends = std::get<2>(t);
        std::cout << "startIdx, endIdx: count\t\t" << starts[i] << ", "
            << ends[i] << ": " << result[i] << std::endl;
    }
    
    return result;
}

constexpr auto test_input_1(){
    /*                                1111111
                             1234567890123456   */
    
    return std::make_tuple( "**|***|*|*|***|*"
                          , std::array<std::size_t,9>{1,5,5,3,7,3,1,1,1}
                          , std::array<std::size_t,9>{5,10,11,11,11,11,12,15,16}
                          );
}

int main(int argc, const char * argv[]) {
    
    auto input = test_input_1();
    auto mapResult = invoke_solution<MapSolution::Solution>( input );
    auto treeResult = invoke_solution<TreeSolution::Solution>( input );
    auto vectorResult = invoke_solution<VectorSolution::Solution>( input );

    return 0;
}
