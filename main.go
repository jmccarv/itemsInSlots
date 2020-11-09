package main

import (
    //"fmt"
)

func main(){}

func UsedSlots( s string, startPositions []int, endPositions []int) []int {
    res := make([]int, len(startPositions) )
    shelf := []byte(s)
    for idx := range startPositions {
        // validate sane input
        if endPositions[idx]-startPositions[idx] < 2 {
            continue // res[idx] == 0
        }
        section := shelf[startPositions[idx]-1:endPositions[idx]]
        // Find the last closing slot
        var closedSectionEnd int
        sectionLength := len(section)-1
        for i := sectionLength; i >= 0; i-- {
            if section[i] == '*' {
                continue
            } else {
                closedSectionEnd = i
                break
            }
        }
        // count remaining slots from the beginning
        shelfOpen := false
        for slotIndex, p := range section {
            if slotIndex > closedSectionEnd {
                break
            }
            if !shelfOpen && p == '*' {
                continue
            } else {
                shelfOpen = true
            }
            if p == '*' {
               res[idx]++
            }
        }
    }
    return res
}

