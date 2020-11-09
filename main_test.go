package main

import (
    "testing"
    "fmt"
)

type TestCase struct {
    Shelf string
    StartIndexes []int
    EndIndexes []int
    ResItemCounts []int
}

func Test_UsedSlots( t *testing.T ){
    testCases := []TestCase {
        TestCase{
            Shelf: "|*|",
            StartIndexes:  []int{1,2},
            EndIndexes:    []int{3,3},
            ResItemCounts: []int{1,0},
        },
        TestCase{
            Shelf: "**|*|*|",
            StartIndexes:  []int{1,3},
            EndIndexes:    []int{5,7},
            ResItemCounts: []int{1,2},
        },
        TestCase{
            Shelf: "***|*|*|***",
            StartIndexes:  []int{1,4,3},
            EndIndexes:    []int{4,7,9},
            ResItemCounts: []int{0,1,2},
        },
        TestCase{
            Shelf: "|***|*|*|***",
            StartIndexes:  []int{2, 5, 4, 3, 1},
            EndIndexes:    []int{5,10,10,11,12},
            ResItemCounts: []int{0, 2, 2, 2, 5},
        },
        TestCase{
            Shelf: "||||**|*",
            StartIndexes:  []int{4,4,3},
            EndIndexes:    []int{6,7,8},
            ResItemCounts: []int{0,2,2},
        },
        TestCase{
            Shelf: "**||**|*",
            StartIndexes:  []int{4,4,3},
            EndIndexes:    []int{6,7,8},
            ResItemCounts: []int{0,2,2},
        },
    }

    for _, test := range testCases {
        expected := test.ResItemCounts
        got := UsedSlots( test.Shelf, test.StartIndexes, test.EndIndexes)
        fmt.Printf("          Given: %v\n", test.Shelf)
        fmt.Printf("Start Positions: %v\n", test.StartIndexes )
        fmt.Printf("  End Positions: %v\n", test.EndIndexes )
        fmt.Printf("\nExpected: %v\n     Got: %v\n\n", expected, got)
        if fmt.Sprintf("%v", expected) != fmt.Sprintf("%v", got) {
            t.Errorf("Results didn't match!\n")
        }
    }

}

