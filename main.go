package main

func main() {}

func UsedSlots(s string, startPositions []int, endPositions []int) []int {
	ret := make([]int, len(startPositions))

	for slot := range parser(s) {
		for i := 0; i < len(startPositions); i++ {
			if startPositions[i] >= slot.end || startPositions[i] > slot.start {
				continue
			}
			if endPositions[i] < slot.end {
				continue
			}

			ret[i] += slot.items
		}
	}

	return ret
}

type slotInfo struct {
	start int // index of starting '|' for this slot (1-based)
	end   int // index of ending '|' for this slot
	items int // number of '*'s in this slot
}

// Parse input string into slots and send each slot over the returned channel
// Only returns slots that have a beginning and ending '|'
func parser(s string) <-chan slotInfo {
	ch := make(chan slotInfo)

	go func() {
		var prev, nr int

		for i := 0; i < len(s); i++ {
			switch s[i] {
			case '|':
				if prev > 0 { // we have a complete slot
					ch <- slotInfo{start: prev, end: i + 1, items: nr}
				}
				nr = 0
				prev = i + 1

			case '*':
				nr++
			}
		}

		close(ch)
	}()

	return ch
}
