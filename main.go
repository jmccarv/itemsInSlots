package main

func main() {}

type slotInfo struct {
	start int // index of starting '|' for this slot (1-based)
	end   int // index of ending '|' for this slot
	items int // number of '*'s in this slot
}

func UsedSlots(shelf string, startPositions []int, endPositions []int) []int {
	// Do a bit of sanity checking in case we got mismatched position data
	l := len(startPositions)
	if len(endPositions) < l {
		l = len(endPositions)
	}

	ret := make([]int, l)

	for slot := range parser(shelf) {
		for i := 0; i < l; i++ {
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

// Parse input string into slots and send each slot over the returned channel
// Only returns slots that have a beginning and ending '|' and at least one '*'
func parser(shelf string) <-chan slotInfo {
	ch := make(chan slotInfo)

	go func() {
		var prev, nr int

		for i := 0; i < len(shelf); i++ {
			switch shelf[i] {
			case '|':
				if prev > 0 && nr > 0 {
					// we have a complete slot with at least one item
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
