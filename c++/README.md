# Solutions
These types of problems typically require building a data structure that facilitate quick lookup over the multiple inputs.

Both approaches I have taken utlize binary search; one in an Ordered Map and one in a BST.

Each solution leverages a `Node` object, defined in `node.h`.

```C++

struct Node {
    int val; // Starting Index ( 1-based index ) of boundary
    int count; // Number of items in *closed* section, 0 if unclosed
    
    // For the tree solution:
    Node* left = nullptr; // Node whose val is < this node
    Node* right = nullptr; // Node whose val is > this node
}
```

#### Building and running
These solutions were built with clang's gnu++17 compiler. Checkout godbolt.org if you don't want to build yourself.

## Map Solution
Builds an Ordered map with a `index -> count` where `index` represents the beginning of the boundary and `count` represents the number of '*' in the section. `count` will be 0 if the section is not closed.

Input: `**|***|*|*|***|*`
Map:

```
3 -> 3
7 -> 1
9 -> 1
11 -> 3
15 -> 0
```

The map will be built once, and then for each input,  a binary search will be performed for the start index and the end index.

For the start index, the search will return the `min(key)` such that `start Index <= key <= end Index`.

For the end index, the search will return the `max(key)` such that `start Index <= key <= Index`. 

The nodes between the iterators will be traversed, summing the counts.


## Tree Solution
Underlying the map is a tree anyways. Created my own Tree once, and then perform BST to locate nodes satisfying conditions above.

I expected better runtimes as the overhead is lower.

Input: `**|***|*|*|***|*`
Tree:

```
   9,1
  /   \
3,3   11,3
  \      \
   7,1   15,0
```

### Further Enhancements
This approach can be optimized with memoization, eliminating the need to do a complete traversal.

The `Node` struct can be expanded to include the sum of its children. If the 'next' node to traverse and the current node both satisfy the conditions above, then the left or right child's sum of the next node can be used ( depending on which subtree 'next' is on ) and that subtree does not have to be traversed.

The 'next' node's count may need to be included, and the root node may need to have both subtrees traversed.
