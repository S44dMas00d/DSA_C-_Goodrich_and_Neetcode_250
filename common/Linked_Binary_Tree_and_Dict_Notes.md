# `LinkedBinaryTree` + `SearchTreeDict`: a field guide

Two files, read together:

- [`Linked_Binary_Tree.hpp`](Linked_Binary_Tree.hpp) — a general binary tree, node-and-pointer style.
- [`Dict_w_Binary_Search_Tree.hpp`](Dict_w_Binary_Search_Tree.hpp) — a dictionary (key→value store, duplicates allowed)
  built *on top of* that tree, using it as pure "shape," with no knowledge that the tree is ordered.

This doc explains both, in enough depth that you can (a) trust the code, and (b) reuse the *ideas* — not
the code itself — when LeetCode hands you a plain `TreeNode{val,left,right}` and asks you to implement one
piece of BST logic against it.

Both files compiled cleanly as of this writing; see [What was actually broken](#what-was-actually-broken)
for the bugs that were fixed, and [`ch05/Dict_w_Binary_Search_Tree_Test.cpp`](../ch05/Dict_w_Binary_Search_Tree_Test.cpp)
/ [`ch05/Linked_Binary_Tree_Test.cpp`](../ch05/Linked_Binary_Tree_Test.cpp) for runnable, traced examples.

---

## 1. The one idea that explains almost everything: extended binary trees

A normal binary tree node has 0, 1, or 2 children, and you represent "no child" with `nullptr`. Every
algorithm you write then has to special-case `nullptr` constantly:

```cpp
if (root == nullptr) return 0;
if (root->left == nullptr) { ... }
```

Goodrich's book (and this code) makes a different choice: **every node has exactly 0 or 2 children — never
1.** A node that "morally" has no children still gets two children — they just hold no data. These
placeholder nodes are called **external nodes** (or "leaves"); the data-holding nodes are **internal
nodes**. This is sometimes called an *extended* binary tree.

```
      Normal (nullptr) view              Extended (this code's) view

           (30)                                (30)
          /    \                              /    \
       (15)    (40)                        (15)    (40)
       /  \       \                        /   \   /  \
    (10)  (20)   (45)                   (10)  (20)▢   (45)
                                         /  \  /  \    /  \
                                        ▢   ▢▢    ▢  ▢   ▢

  ▢ = "external node" — a real Node in memory, holding a
      default-constructed E, that just represents "empty here"
```

Why bother? Because now **every position in the tree has a well-defined left child, right child, and
parent** — you never dereference a null pointer, and you never need an `if (child == nullptr)` guard before
recursing. `isExternal()` is the *only* check the algorithms need, and it's a single boolean read, not a
null check scattered through every function. That is the entire "why is this so esoteric" answer: the
weirdness buys uniformity. Every operation below — search, insert, erase, in-order successor — is written
once, generically, in terms of "walk to an external node" or "splice out an external node," with no special
casing for 0-child vs 1-child vs 2-child nodes.

The price: roughly double the node count (every internal node still needs its 2 external children kept
around), and a node type that's slightly harder to reason about the first time you see it. That's the
trade-off this repo has made.

Keep this picture in your head for everything that follows — nearly every "why does it do that?" question
below reduces to "because every node has exactly 0 or 2 children."

---

## 2. `Linked_Binary_Tree.hpp`

### 2.1 `Node` and `Position`

```cpp
struct Node {
    E e;
    Node *parent, *left, *right;
};
```

Plain node. `left == nullptr && right == nullptr` *is* the definition of "external" — see `isExternal()`.
Because of the extended-tree invariant, a node's children are always created **in pairs**
(`expandExternal`, below), so you never have to worry about "only one of `left`/`right` is null."

`Position` is a thin wrapper around a raw `Node*`:

```cpp
class Position {
    Node* v;
public:
    E& operator*() const;      // dereference: get at the stored key/value
    E* operator->() const;     // -> so you can write v->key() instead of (*v).key()
    Position left()   const;   // wrap v->left
    Position right()  const;   // wrap v->right
    Position parent() const;   // wrap v->parent
    bool isRoot()     const;   // v->parent == nullptr
    bool isExternal() const;   // v->left == nullptr && v->right == nullptr
    bool isInternal() const;   // !isExternal()
    bool operator==(const Position&) const;
};
```

Why not just hand out `Node*` directly? Two reasons:

1. **Encapsulation** — client code (`SearchTreeDict`) never touches `Node`, `parent`/`left`/`right` pointers,
   or `new`/`delete`. It only calls `.left()`, `.right()`, `.parent()`, `.isExternal()`. If you later swap
   the internal representation (say, an array-backed tree instead of pointers), `Position`'s interface can
   stay identical and nothing above it changes.
2. **Value semantics for a "handle."** A `Position` is small, copyable, comparable — it behaves like an
   iterator into the tree, which is exactly the role it plays inside `SearchTreeDict::Iterator` (§3.5).

This "wrap a pointer in a tiny value-type handle with a clean interface" pattern is the same idea behind
`std::vector<T>::iterator`, so getting comfortable with `Position` here pays off generally.

### 2.2 The structural primitives: `expandExternal` and `removeAboveExternal`

These two functions are the *only* places `Linked_Binary_Tree.hpp` allocates or frees nodes below the
root, and every higher-level operation (BST insert, BST erase) is built entirely out of them. Learn these
two and the rest of `SearchTreeDict` is just "which external node do I expand / remove above."

**`expandExternal(p)`** — turn an external (leaf, empty) node into an internal (data-holding) node, by
giving it two brand-new external children.

```
before:                 after expandExternal(p):
   p (external,             p (now internal — caller will
    holds no data)           setKey/setValue on it next)
                            /  \
                          ext  ext   <- freshly allocated, empty
```

```cpp
void expandExternal(const Position& p) {
    Node* v = p.v;
    v->left  = new Node; v->left->parent  = v;
    v->right = new Node; v->right->parent = v;
    n += 2;
}
```

Note it does **not** touch `v->e` — the caller (e.g. `SearchTreeDict::inserter`) sets the key/value
afterward. `expandExternal` only changes shape.

**`removeAboveExternal(p)`** — the inverse-ish operation: `p` must be external. Delete `p` *and its
parent*, and splice `p`'s sibling into the parent's old spot.

```
before:                          after removeAboveExternal(w):
        gpar                              gpar
         |                                  |
         v                                 sib      <- promoted
       /   \                    (v and w are both deleted)
      w    sib
   (external)
```

```cpp
Position removeAboveExternal(const Position& p) {
    Node* w = p.v;
    Node* v = w->parent;
    Node* sib = (w == v->left ? v->right : v->left);
    // reattach sib where v used to hang
    ... delete w; delete v; n -= 2;
    return Position(sib);
}
```

Why remove *two* nodes at once instead of one? Because of the extended-tree invariant again: you can never
have a node with exactly one child, so "delete a node" always really means "delete a node together with one
of its two children, and let the *other* child take its place." That's precisely what this function does,
and it's the mechanism behind every BST-erase case in §3.4.

### 2.3 `addRoot`, `size`, `empty`, `root`

Unremarkable — `addRoot()` allocates a single external node and makes it `_root` (so a freshly-constructed
tree is one bare node, not `nullptr`; this matters for `SearchTreeDict`'s sentinel trick in §3.2).

### 2.4 Destruction: `destroySubtree`

```cpp
void destroySubtree(Node* v) {
    if (v == nullptr) return;
    destroySubtree(v->left);
    destroySubtree(v->right);
    delete v;
}
```

This is a **postorder** walk (children, then self) — deliberately, not preorder. If you deleted `v` before
recursing into `v->left`/`v->right`, you'd lose the only pointers that let you reach those children at all
— a leak, not a crash (nothing dereferences `v` after it's freed here, but you'd never be able to free the
subtree below it). Postorder is the traversal order where "visit" (`delete`) is safe to do last, once you
no longer need the node for anything else — a generally useful rule of thumb: *whenever visiting a node
destroys or invalidates it, that visit belongs in the postorder slot.*

### 2.5 `preorder` + `positions()`: the visitor-callback pattern

```cpp
void preorder(Node* v, std::function<void(Node*)> func) const {
    if (v == nullptr) return;
    func(v);
    if (v->left)  preorder(v->left, func);
    if (v->right) preorder(v->right, func);
}
```

Instead of hardcoding "collect into a list," `preorder` takes *any* `std::function<void(Node*)>` and calls
it at every node, in preorder (self, then left, then right). `positions()` is just one particular use of
this:

```cpp
std::list<Position> positions() const {
    std::list<Position> posList;
    preorder(_root, [&posList](Node* n) { posList.push_back(Position(n)); });
    return posList;
}
```

...but because it's parameterized over the callback, you can reuse `preorder` for anything else without
touching its body — e.g. counting nodes, summing values, printing, building a different container:

```cpp
int count = 0;
preorder(root_node, [&count](Node*) { ++count; });

int total = 0;
preorder(root_node, [&total](Node* n) { total += n->e; });
```

This is the "ability to pass a function to preorder" mentioned in this repo's commit history — it's the
same idea as `std::for_each`, or a visitor pattern: separate *how you walk* the tree from *what you do* at
each node.

> **Note (`preorder`/`positions` and external nodes):** `preorder` is written for a *general* binary tree
> and visits every `Node*` it finds, including external ones (a fresh `LinkedBinaryTree<int>` with just a
> root has 1 position — the bare root — until you `expandExternal` it). `SearchTreeDict` never calls
> `positions()`/`preorder()` itself; it does its own traversal via `Iterator` (§3.5), which specifically
> knows to treat external nodes as "not real entries." If you ever call `positions()` directly on the tree
> backing a `SearchTreeDict`, you'll see the external placeholder nodes too — that's expected, not a bug.

---

## 3. `Dict_w_Binary_Search_Tree.hpp`

### 3.1 `Entry<K, V>`

Just a key/value pair with getters/setters. This is the `E` template parameter that `LinkedBinaryTree<E>`
gets instantiated with — the tree itself has no idea it's storing entries or that they're ordered; ordering
is entirely `SearchTreeDict`'s business.

### 3.2 The super-root sentinel trick

This is the second "why is it built like *that*?" moment, and it's worth internalizing on its own.

`SearchTreeDict` doesn't use `T.root()` as "the BST root." Instead:

```cpp
SearchTreeDict() : T(), n(0) {
    T.addRoot();
    T.expandExternal(T.root());
}

TPos root() const { return T.root().left(); }   // <-- the *real* BST root
```

```
                 T.root()   <- a permanent dummy/"super-root" node,
                /        \     never holds a real Entry, never removed
   [the actual         (untouched
    BST root]           external node,
       ...               ignored forever)

   SearchTreeDict::root() == T.root().left()
   SearchTreeDict::end()  == Iterator(T.root())   <- the dummy itself
```

Why pay for an extra permanent dummy node? Because it makes the empty-tree and end-of-iteration cases fall
out **for free**, with no special-casing:

- **Empty dictionary:** `T.root().left()` is a fresh external node (no key yet). `begin()` walks left from
  `root()` until external — since `root()` is *already* external, the loop doesn't execute, and `begin()`
  returns `Iterator(v.parent())` = `Iterator(T.root())` = `end()`. So `begin() == end()` on an empty dict,
  automatically, without an `if (empty()) return end();` guard anywhere.
- **`end()` sentinel:** `end()` is a real, stable node (the dummy super-root) that never moves and is never
  deleted — a well-defined "one past the last element" the same way `std::map::end()` is a real sentinel
  node, not `nullptr`.
- **Iterating off the right edge:** see §3.5 — climbing parent pointers from the last (rightmost) real
  entry naturally arrives at the dummy super-root, i.e. at `end()`, with no explicit "am I at the last
  node?" check.

This is the same technique the C++ standard library itself uses internally for `std::map`/`std::set`
(a sentinel/header node that is simultaneously "before begin" and "after end" on a circular structure) —
recognizing it here is transferable.

### 3.3 `finder` — plain recursive BST search

```cpp
TPos finder(const K& k, const TPos& v) {
    if (v.isExternal())      return v;              // not found — landed on a placeholder
    if (k < v->key())        return finder(k, v.left());
    else if (k > v->key())   return finder(k, v.right());
    else                     return v;               // found
}
```

Standard BST search, except "not found" is represented by *landing on an external node* rather than by
`nullptr`. `find(k)` just checks which kind of position `finder` returned:

```cpp
Iterator find(const K& k) {
    TPos v = finder(k, root());
    return v.isExternal() ? end() : Iterator(v);
}
```

O(h) where h is the tree height (§3.6).

### 3.4 `inserter` / `insert`

```cpp
TPos inserter(const K& k, const V& x) {
    TPos v = finder(k, root());
    while (!v.isExternal()) {           // key already present — keep going
        v = finder(k, v.right());       // right subtree, to find *an* empty spot
    }
    T.expandExternal(v);                // v was external; now it's a real node
    v->setKey(k); v->setValue(x);
    n++;
    return v;
}
```

The `while` loop is not a bug — it's a deliberate design choice: **this dictionary allows duplicate keys.**
Goodrich's book distinguishes a **Dictionary ADT** (this one — multiple entries may share a key, like
`std::multimap`) from a **Map ADT** (unique keys, like `std::map`). If `finder` lands on an existing entry
with an equal key, `inserter` doesn't stop there — it re-searches the right subtree of that entry for a
fresh external spot, so the new entry ends up somewhere in the "equal keys" region of the tree, without
overwriting the old one. If you wanted `std::map`-style unique-key semantics instead, you'd drop the loop
and either overwrite `v`'s value in place or throw when `finder` returns an internal node.

Where does the new node come from? `expandExternal(v)` — v (found empty spot) becomes internal, with two
fresh external children. This is the *only* place a new key ever enters the structure; it's always attached
by expanding a node that was external.

### 3.5 `eraser` / `erase` — the three deletion cases

`removeAboveExternal` only knows how to do one thing: delete an external node together with its parent. All
of BST deletion reduces to figuring out *which* external node to feed it.

```cpp
TPos eraser(TPos& v) {
    TPos w;
    if (v.left().isExternal())        w = v.left();
    else if (v.right().isExternal())  w = v.right();
    else {
        // both children are real entries -> splice out the in-order successor instead
        w = v.right();
        do { w = w.left(); } while (!w.isExternal());
        TPos u = w.parent();                 // u = in-order successor of v
        v->setKey(u->key()); v->setValue(u->value());  // copy successor's data up into v
    }
    n--;
    return T.removeAboveExternal(w);
}
```

**Case A/B — v has at least one external child.** Then v itself has at most one *real* child, so v can be
removed directly: `w` is v's external child, and `removeAboveExternal(w)` deletes `w` together with its
parent (`v`), promoting v's other (real) child into v's old spot.

```
erase(10) from:            10's left child is external ->
        20                 w = 10.left(); removeAboveExternal(w)
       /                   deletes 10 and that external node,
     (10)                  promotes 10's right (external) child
     /  \                  up into 20's left slot:
   ext  ext
                                 20
                                 /
                               ext
```

**Case C — both children are real entries.** You can't remove v directly (removing it would have to
"choose" which subtree replaces it). Standard BST fix: copy the **in-order successor's** data into `v`
instead of moving `v`, then delete the successor node (which, being the *leftmost* node of `v`'s right
subtree, is guaranteed to have an external left child — i.e. it's a Case A node), by construction.

```
erase(30):                                   the in-order successor of 30 is 40
      30                                      (right subtree's leftmost node —
     /   \                                    here 40 has no left child, so
   20     40                                  40 IS the successor)
   ext,ext ext,ext

   1. copy 40's (key,value) onto node 30's slot
   2. delete 40 by removeAboveExternal(40's external left child)
      -> 40's external *right* child gets promoted into 40's old spot

result:
      40      <- same node object as before, now holding 40's data
     /   \
   20     ext
```

The `do { w = w.left(); } while (!w.isExternal())` loop is exactly "find the leftmost node of the right
subtree": start at `v.right()`, keep descending left until you fall off onto an external node; that
external node's *parent* (`u`) is the successor. Trace it on the bigger tree from the test file
(`50,30,70,20,40,60,80,10`): the in-order successor of `50` is `60` (right subtree is `70`'s subtree;
leftmost node there is `60`, since `70.left() = 60` has an external left child).

`erase(k)` and `erase(iterator)` both just locate the target position and call `eraser` on it — `erase(k)`
throws `NonexistentElement` if the key isn't present (see §5).

### 3.6 `Iterator::operator++` — in-order successor via parent pointers

This is the payoff of keeping parent pointers around, and it's directly the classic "inorder successor in a
BST" algorithm (worth memorizing — it's LeetCode 285, see §6).

```cpp
Iterator& operator++() {
    TPos w = v.right();
    if (w.isInternal()) {
        // has a right subtree -> successor is that subtree's leftmost node
        do { v = w; w = w.left(); } while (w.isInternal());
    } else {
        // no right subtree -> successor is the nearest ancestor
        // for which v is in the *left* subtree
        w = v.parent();
        while (v == w.right()) { v = w; w = w.parent(); }
        v = w;
    }
    return *this;
}
```

Two cases, both visible in the diagram below (tree = `50,30,70,20,40,60,80,10`, then `10` erased so
`20` is a leaf):

```
                 50
               /    \
             30       70
            /  \     /  \
          20   40   60   80
```

- **Node has a right child (e.g. `v = 30`):** descend into `30.right() = 40`, then keep going left while
  possible (`40` has no left child, so we stop immediately) → successor of `30` is `40`.
- **Node has no right child, and is a *left* child of its parent (e.g. `v = 20`):** climb once to the
  parent → successor of `20` is `30`.
- **Node has no right child, and is a *right* child of its parent (e.g. `v = 40`):** the `while (v ==
  w.right())` loop keeps climbing *past* every ancestor for which we're the right child, stopping at the
  first ancestor we're a *left* child of (or, having none, at the dummy super-root). `40` is `30`'s right
  child, so climb past `30`; now `v=30, w=30.parent()=50`; is `30 == 50.right()`? No (`30` is `50`'s left
  child) → stop, successor of `40` is `50`.
- **Rightmost node overall (`v = 80`):** `80` is `70`'s right child → climb past `70`. `70` is `50`'s right
  child → climb past `50`. `50`'s parent is the dummy super-root; `50 == superroot.right()`? No (the
  super-root's right child is its own untouched, permanently-external placeholder — see §3.2) → stop.
  `v` becomes the super-root — i.e. `end()`. **This is why the sentinel super-root exists**: without a real
  node "above" the true root, this climb would run off a `nullptr` parent and need a special check; with
  it, running off the right edge of the tree lands you exactly on `end()`, uniformly, the same way running
  off the right edge of any other subtree lands you on the next ancestor.

`begin()` is the mirror image done once, eagerly: walk left from `root()` until external, then back up one
step to the last real node passed — i.e. the leftmost (smallest-key) entry.

---

## 4. Complexity, and why there's no rebalancing here

Every operation above (`finder`, `inserter`, `eraser`, one `operator++` step) does O(h) work, where `h` is
the tree's height. For a "nice" (balanced) tree `h = O(log n)`, but **nothing in this file keeps the tree
balanced** — insert only ever attaches new nodes at the bottom, so inserting already-sorted keys (`10, 20,
30, 40, ...`) degenerates into a straight line, `h = O(n)`, and every operation becomes linear. That's the
classic plain-BST weak point; Goodrich's book fixes it two chapters later with AVL / red-black / splay
trees, which are subclasses that call the exact same `inserter`/`eraser` primitives and then rebalance
afterward.

That's also what the declared-but-never-defined `TPos restructure(const TPos& v);` is for — it's a
placeholder hook for that future rebalancing step (a trinode restructuring / rotation operation), left
unimplemented here deliberately. It's not a bug that it's unused; plain `SearchTreeDict` just doesn't need
it. If you want to see it filled in, that's the natural next thing to build on top of this file.

---

## 5. What was actually broken (and now isn't)

The header as originally written didn't compile. In case you hit similar issues writing your own
Position/handle classes, here's what was missing and why each one mattered:

| Symptom | Cause | Fix |
|---|---|---|
| `v->key()` etc. wouldn't compile | `Position` had `operator*()` but no `operator->()` | added `E* operator->() const` to `Position` |
| `w.isInternal()` wouldn't compile | `Position` never declared `isInternal()`, only `isExternal()` | added `bool isInternal() const { return !isExternal(); }` |
| `v == p.v`, `v == w.right()` wouldn't compile | `Position` had no `operator==` | added `operator==`/`operator!=` to `Position` |
| `throw NonexistentElement(...)` — undeclared identifier | the exception type was thrown but never defined anywhere | added a small `NonexistentElement : public std::runtime_error` class |
| linker error: `size()`/`empty()` undefined | declared in the `SearchTreeDict` class body, never given a definition | added the two one-line definitions |
| `erase(const Iterator& p)` wouldn't compile | `p` is `const Iterator&`, so `p.v` is a `const TPos`, but `eraser(TPos&)` needs a non-const reference | copy into a local `TPos v = p.v;` first, then call `eraser(v)` |

Everything else — `finder`, `inserter`, `eraser`'s three cases, the sentinel trick, the iterator's
successor logic — was already correct once it compiled; it was verified against traces like the ones in
§3.4/§3.6 and against [`ch05/Dict_w_Binary_Search_Tree_Test.cpp`](../ch05/Dict_w_Binary_Search_Tree_Test.cpp)
under AddressSanitizer/UBSan (insert, find, erase-by-key in all three cases, erase-by-iterator, erase the
root, duplicate keys, draining to empty, erasing a missing key).

**One thing deliberately left alone:** neither `LinkedBinaryTree` nor `SearchTreeDict` defines a copy
constructor or copy-assignment operator, even though both define a destructor (a Rule-of-Three/Five gap).
The compiler-generated copy just copies the raw `Node*` fields, so if you ever write
`SearchTreeDict<E> b = a;`, both `a` and `b` end up with `Node*`s to the *same* nodes, and when either one's
destructor runs it frees memory the other still points at (use-after-free / double-free). Nothing in the
current tests copies these objects, so it wasn't triggered — but avoid copying them by value; pass by
reference. Fixing this properly means writing a real deep-copy (clone the whole node tree, fix up parent
pointers) — worth doing as a follow-up exercise if you want it, but it's a separate, larger change from
"make what's here compile and behave correctly."

---

## 6. Turning this into LeetCode-shaped code

LeetCode almost never gives you `LinkedBinaryTree`/`Position`. It gives you this, with `nullptr` for
"no child":

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    // (usually *no* parent pointer!)
};
```

The algorithms above still apply — you're just translating "landed on an external Position" back into
"pointer is `nullptr`," and, critically, **you usually lose the parent pointer**, which changes how the
successor/iterator logic has to be written. Here's the mapping:

| This repo | Concept | Typical LeetCode shape |
|---|---|---|
| `finder` | BST search | [LC 700](https://leetcode.com/problems/search-in-a-binary-search-tree/) — `search(TreeNode* root, int val)` |
| `inserter` | BST insert | [LC 701](https://leetcode.com/problems/insert-into-a-binary-search-tree/) |
| `eraser` (3 cases) | BST delete | [LC 450](https://leetcode.com/problems/delete-node-in-a-bst/) — the *exact* same 3 cases |
| `Iterator::operator++` | in-order successor | [LC 285](https://leetcode.com/problems/inorder-successor-in-bst/) — but usually **no parent pointer available** |
| repeated `operator++` | controlled/lazy in-order iteration | [LC 173](https://leetcode.com/problems/binary-search-tree-iterator/) |
| in-order traversal in general | sorted order / rank | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/), [LC 230](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) |

### 700 — search (this is `finder`, nullptr-flavored)

```cpp
TreeNode* searchBST(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return val < root->val ? searchBST(root->left, val)
                            : searchBST(root->right, val);
}
```
Directly `finder`, with "return the external Position" replaced by "return `nullptr`."

### 701 — insert (this is `inserter`, minus the duplicate-key loop since LC guarantees unique keys)

```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);        // this *is* expandExternal, inlined
    if (val < root->val) root->left  = insertIntoBST(root->left,  val);
    else                 root->right = insertIntoBST(root->right, val);
    return root;
}
```

### 450 — delete (this is `eraser`, same 3 cases, no successor-copy-into-place trick needed
because here you can just relink pointers and return a *different* node upward)

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val)      { root->left  = deleteNode(root->left,  key); return root; }
    if (key > root->val)      { root->right = deleteNode(root->right, key); return root; }
    // found it
    if (!root->left)  return root->right;   // Case A (mirrors: v.left().isExternal())
    if (!root->right) return root->left;    // Case B (mirrors: v.right().isExternal())
    // Case C: both children real -> splice in the in-order successor
    TreeNode* succ = root->right;
    while (succ->left) succ = succ->left;    // exactly `do { w = w.left(); } while (!w.isExternal())`
    root->val = succ->val;                   // copy successor's data up, same as v->setKey/setValue
    root->right = deleteNode(root->right, succ->val); // then delete the now-duplicated successor
    return root;
}
```
Line up each branch against `eraser` in §3.4 — it's the same three cases, just expressed with `nullptr`
checks and pointer reassignment instead of `isExternal()`/`removeAboveExternal`.

### 285 / 173 — successor **without** a parent pointer

This is the one place the translation isn't line-for-line, because `Iterator::operator++` leans on
`v.parent()`, and LeetCode's `TreeNode` typically doesn't have one. Two standard workarounds:

- **You have the root and a target node, no parent pointers (LC 285):** walk down *from the root*, and keep
  a "best candidate" — every time you go left, the current node is a candidate successor (because you're
  descending into node's left subtree, so this node is bigger than everything below it while still being
  as small as possible above the target):

```cpp
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* succ = nullptr;
    while (root) {
        if (p->val < root->val) { succ = root; root = root->left; }
        else                     root = root->right;
    }
    return succ;
}
```
  (If `p` has a right child, the "leftmost of right subtree" rule from §3.6 is simpler and still applies —
  this root-down version is what you need precisely because you *can't* climb from `p` upward.)

- **You need repeated `next()` calls cheaply (LC 173, "BST Iterator"):** since you can't climb via
  `->parent`, keep your own explicit stack of "ancestors whose right subtree you haven't visited yet" —
  this stack is playing the exact role this repo's parent pointers play for free:

```cpp
class BSTIterator {
    std::stack<TreeNode*> st;
    void pushLeft(TreeNode* n) { while (n) { st.push(n); n = n->left; } }
public:
    BSTIterator(TreeNode* root) { pushLeft(root); }
    bool hasNext() { return !st.empty(); }
    int next() {
        TreeNode* n = st.top(); st.pop();
        pushLeft(n->right);
        return n->val;
    }
};
```
  Compare to `Iterator::operator++`'s two branches: "has an internal right child → descend leftmost" is
  exactly `pushLeft(n->right)`; "no right child → climb via parent" is replaced by "pop the stack," because
  the stack already remembers every ancestor you'd otherwise have had to climb to.

### 98 / 230 — anything that wants "sorted order"

Both are just: do an in-order traversal (left, self, right) and either check monotonicity (98) or count to
k (230). This is precisely what walking the tree via repeated `Iterator::operator++` produces, one entry at
a time, in this repo's dictionary — the connection is: **an in-order traversal *is* "start at `begin()` and
call `operator++` until `end()`."**

---

## 7. Quick reference

- **Extended/full binary tree:** every node has 0 or 2 children; "empty" is a real external node, not
  `nullptr`. This is *why* the whole file looks the way it does (§1).
- **`Position`:** a small copyable/comparable handle around `Node*` — `.left()/.right()/.parent()`,
  `isExternal()/isInternal()`, `operator*`/`operator->`, `operator==` (§2.1).
- **`expandExternal(p)`:** external → internal, by attaching two fresh external children. The only way new
  data enters the tree (§2.2).
- **`removeAboveExternal(p)`:** deletes external `p` and its parent together, promotes the sibling. The
  only way data structurally leaves the tree (§2.2).
- **Super-root sentinel:** `SearchTreeDict`'s real root is `T.root().left()`; `T.root()` itself is a
  permanent dummy that *is* `end()`. Makes empty-tree and end-of-iteration cases automatic (§3.2).
- **Dictionary vs. Map:** this structure allows duplicate keys on purpose (`inserter`'s `while` loop, §3.4).
- **Erase, 3 cases:** left-external → splice directly; right-external → splice directly; both-internal →
  copy in-order successor's data up, then delete the successor (which is guaranteed to be a left-external
  case) (§3.4).
- **In-order successor:** right child exists → leftmost of its right subtree; else → climb parent pointers
  until you were a *left* child of where you stopped (§3.5). Without parent pointers (typical LeetCode
  `TreeNode`), reproduce this with either a root-down walk (§6, LC 285) or an explicit ancestor stack (§6,
  LC 173).
