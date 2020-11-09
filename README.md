
# Count items in closed sections between two indexes

## Description
Given a string of '\*'s and '|', count the items represented by "\*" in **closed** section surrounded of '|' between a start and end index provided in 2 corresponding arrays of start and end positions, returning an array respective of those start and end positions containing the number of items.

## Execution
`go test`

### Should yield
```
          Given: |*|
Start Positions: [1 2]
  End Positions: [3 3]

Expected: [1 0]
     Got: [1 0]

          Given: **|*|*|
Start Positions: [1 3]
  End Positions: [5 7]

Expected: [1 2]
     Got: [1 2]

          Given: ***|*|*|***
Start Positions: [1 4 3]
  End Positions: [4 7 9]

Expected: [0 1 2]
     Got: [0 1 2]

          Given: |***|*|*|***
Start Positions: [2 5 4 3 1]
  End Positions: [5 10 10 11 12]

Expected: [0 2 2 2 5]
     Got: [0 2 2 2 5]

          Given: ||||**|*
Start Positions: [4 4 3]
  End Positions: [6 7 8]

Expected: [0 2 2]
     Got: [0 2 2]

          Given: **||**|*
Start Positions: [4 4 3]
  End Positions: [6 7 8]

Expected: [0 2 2]
     Got: [0 2 2]

PASS
```

