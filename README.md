# Exact Cover Problem Solver (Algorithm X)

A C implementation of an **Exact Cover Problem** solver inspired by Donald Knuth's **Algorithm X**. The program uses backtracking to find all valid combinations of sub-sets that cover the entire domain without overlap, applying a custom bitmask filter to the output.

## Problem Description
Given a domain $S = \{1, \dots, d\}$ and a family $P$ of subsets represented as matrix rows $W_1, \dots, W_n$:
* An **Exact Cover** is a sub-collection $Q \subseteq P$ such that every element in $S$ is covered by **exactly one** subset in $Q$.
* Non-underscore characters (`_`) in matrix rows represent the presence of an element at that index.
* A filter mask row $F$ controls which columns are retained (`+`) or discarded (`-`) in the final output string.

Despite the NP-complete nature of the Exact Cover problem, backtracking via Algorithm X offers high efficiency for discrete puzzles and constraint satisfaction problems.

## Features
* **C23 Standard Compliance:** Built with modern C practices and strict compiler checks.
* **Deterministic Output:** Generates all valid exact cover permutations.
* **Memory Safe:** Designed with strict stack protection, zero memory leaks, and bounds checking.
* **Zero Variable-Length Arrays (VLA):** Conforms to high-reliability software standards.

## Input / Output Format

### Input
1. **First Line ($F$):** Filter mask containing `+` (keep column) and `-` (strip column).
2. **Subsequent Lines ($W_1 \dots W_n$):** Subset candidate rows containing arbitrary characters (where `_` represents an uncovered position).

### Output
Filtered string solutions for each discovered exact cover, terminated by newlines.

