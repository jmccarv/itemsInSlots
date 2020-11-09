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
            ResItemCounts: []int{0,2,2},
        },
        TestCase{
            Shelf: "|***|*|*|***",
            StartIndexes:  []int{2,5,4},
            EndIndexes:    []int{5,8,10},
            ResItemCounts: []int{0,2,2},
        },
    }

    for _, test := range testCases {
        expected := test.ResItemCounts
        got := UsedSlots( test.Shelf, test.StartIndexes, test.EndIndexes)
        if fmt.Sprintf("%v", expected) != fmt.Sprintf("%v", got) {
            t.Errorf("\nExpected: %v\n     Got: %v\n", expected, got)
        }
    }

}

