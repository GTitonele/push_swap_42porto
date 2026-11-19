*This project has been created as part of the 42 curriculum by gbaccell, elsouza.*

<div align="center">

# 🔢 push_swap

**Sorting integers with two stacks, eleven moves and as few operations as possible.**

![Language](https://img.shields.io/badge/language-C-blue)
![School](https://img.shields.io/badge/school-42%20Porto-black)
![Group](https://img.shields.io/badge/group-2%20learners-green)
![Strategies](https://img.shields.io/badge/strategies-4-orange)

</div>

---

## 📑 Table of Contents

- [Description](#-description)
- [Instructions](#-instructions)
- [The Rules of the Game](#-the-rules-of-the-game)
- [Disorder Metric](#-disorder-metric)
- [Algorithms](#-algorithms)
- [Adaptive Strategy](#-adaptive-strategy)
- [Performance](#-performance)
- [Project Structure](#-project-structure)
- [Contributions](#-contributions)
- [Resources](#-resources)

---

## 📖 Description

`push_swap` is an algorithm project from the 42 Common Core. The program receives a list of integers, loads them into **stack `a`** (with **stack `b`** empty), and prints the **shortest sequence of operations** it can find that leaves `a` sorted in ascending order, with the smallest number on top.

The goal is not just to sort, but to **think about algorithmic complexity in a concrete way**: the cost of each algorithm is measured in the number of push_swap operations it generates, not in CPU time.

The program embeds **four sorting strategies**:

| Strategy | Technique | Complexity (in operations) |
|---|---|---|
| `--simple` | Minimum extraction (selection sort) | **O(n²)** |
| `--medium` | Chunk-based sorting (√n chunks) | **O(n√n)** |
| `--complex` | Binary LSD radix sort | **O(n log n)** |
| `--adaptive` *(default)* | Chooses one of the above based on the measured disorder | depends on the regime |

It also includes a **benchmark mode** (`--bench`) that reports the disorder, the strategy used, its complexity class and the count of every operation.

---

## 🛠 Instructions

### Compilation

```bash
make          # builds libft and then push_swap
make clean    # removes object files
make fclean   # removes object files, libft.a and push_swap
make re       # rebuilds everything from scratch
```

Compiled with `cc -Wall -Wextra -Werror`. The project's `Makefile` builds `libft` with its own `Makefile` and does not relink.

### Usage

```bash
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <numbers...>
```

- The **first number is the top** of stack `a`.
- Numbers can be passed as separate arguments or in a single quoted string: `./push_swap 3 2 1` or `./push_swap "3 2 1"`.
- Flags must come **before** the numbers. Only **one** strategy flag is allowed; `--bench` can be combined with any of them.
- With no arguments, the program prints nothing and gives the prompt back.

### Examples

```bash
# Default (adaptive) strategy
$ ./push_swap 2 1 3 6 5 8

# Force a strategy
$ ./push_swap --simple 5 4 3 2 1

# Count the operations
$ ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

# Verify the result with the provided checker
$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK

# Large random input
$ ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' '); ./push_swap $ARG | ./checker_linux $ARG
OK
```

### Benchmark mode

`--bench` prints the metrics to **stderr** after sorting, so the operations on stdout stay clean and can still be piped to the checker.

```bash
$ ./push_swap --bench $ARG 2>&1 >/dev/null
[bench] disorder: 50.35%
[bench] strategy: Adaptive / O(n log n)
[bench] total_ops: 6784
[bench] sa: 0 sb: 0 ss: 0 pa: 2284 pb: 2284 ra: 2216 rb: 0 rr: 0 rra: 0 rrb: 0 rrr: 0
```

For the adaptive strategy, the name shows the strategy that was **requested** and the complexity shows the class of the strategy that was **actually used**.

### Error handling

The program prints `Error` followed by `\n` on **stderr** when:

- an argument is not a valid integer (`one`, `12a`, `-`, `""`);
- a number is outside the `int` range;
- a number appears more than once;
- an unknown flag is given, or more than one strategy flag is given.

```bash
$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

---

## 🎮 The Rules of the Game

| Operation | Effect |
|---|---|
| `sa` / `sb` | Swap the first two elements of `a` / `b` |
| `ss` | `sa` and `sb` at the same time |
| `pa` / `pb` | Move the top of `b` to `a` / the top of `a` to `b` |
| `ra` / `rb` | Rotate up: the first element becomes the last |
| `rr` | `ra` and `rb` at the same time |
| `rra` / `rrb` | Rotate down: the last element becomes the first |
| `rrr` | `rra` and `rrb` at the same time |

### Data structure

Each stack is a **circular doubly linked list**:

```
          ┌──────────────────────────────────┐
          ▼                                  │
 top → [ 3 ] ⇄ [ 0 ] ⇄ [ 4 ] ⇄ [ 1 ] ⇄ [ 2 ] ─┘
          ▲                              │
          └──── top->previous = bottom ──┘
```

Because the list is circular, `top->previous` is always the bottom element. This makes **`rotate` and `reverse rotate` O(1)**: they only move the `top` pointer. `swap` and `push` only relink a few pointers, so every operation runs in constant time.

---

## 📐 Disorder Metric

Before any move is made, the program measures how far stack `a` is from being sorted:

```
disorder = inversions / total_pairs
```

An **inversion** is any pair `(i, j)` with `i < j` and `a[i] > a[j]`.

- `0` → already sorted
- `1` → sorted in reverse order
- random input → around `0.5`

The computation compares every pair once, so it costs **O(n²) time and O(1) space**. It does not generate any push_swap operation.

---

## 🧠 Algorithms

### Normalization (preparation step)

Before sorting, the values are replaced by their **rank** (0 … n‑1):

```
[ 42, -7, 1000, 3 ]  →  [ 2, 0, 3, 1 ]
```

The relative order does not change, so the generated operations are identical. It removes negative and very large values, which makes chunks easy to define and lets the radix sort work bit by bit. It uses a temporary array (O(n) space) and is not counted as push_swap operations.

### Small inputs (2 to 5 numbers)

For very small stacks, all strategies use dedicated routines:

- **2 numbers**: at most one `sa`.
- **3 numbers**: put the largest at the bottom (`ra` or `rra`), then `sa` if needed. **At most 2 operations** for all 6 permutations.
- **4–5 numbers**: push the one or two smallest to `b`, sort the remaining 3, push them back.

### 1️⃣ Simple — Minimum extraction · O(n²)

An adaptation of **selection sort**:

1. Find the smallest element of `a`.
2. Bring it to the top by the **shortest path** (`ra` if it is in the upper half, `rra` otherwise).
3. `pb` it to stack `b`.
4. Repeat until `a` is empty, then `pa` everything back. The elements return in ascending order.

**Upper bound:** each of the `n` extractions costs at most `n/2` rotations plus one `pb`, and the return costs `n` `pa`:

```
ops ≤ n · (n/2 + 1) + n  =  O(n²)
```

**Space:** O(1) auxiliary (only stack `b`).

### 2️⃣ Medium — Chunk sort · O(n√n)

The ranks `0 … n‑1` are split into ranges of size `k ≈ 2√n`. A counter `i` tracks how many numbers have already been pushed to `b`.

**Phase 1: push by chunks.** For the element on top of `a`:

| Condition | Action | Why |
|---|---|---|
| `top ≤ i` | `pb` + `rb` | very small → goes to the **bottom** of `b` |
| `top ≤ i + k` | `pb` | in the current chunk → stays on **top** of `b` |
| otherwise | `ra` | too big, not its turn yet |

As `i` grows, the accepted range moves forward, so every element is eventually pushed. Stack `b` ends up **almost sorted**, with the largest values near the top.

**Phase 2: push back the maximum.** While `b` is not empty, bring its maximum to the top (shortest path with `rb` / `rrb`) and `pa`.

**Upper bound:**
- Phase 1: there are about `n/k` chunks, and each chunk needs at most one full pass over `a` (≤ `n` rotations). That gives `(n/k) · n = O(n√n)`.
- Phase 2: the maximum of `b` is always within about `k` positions of the top or bottom, so each `pa` costs `O(k)`, which gives `n · k = O(n√n)`.

The factor 2 in `k = 2√n` is a constant, so it reduces the number of operations without changing the complexity class.

**Space:** O(1) auxiliary. √n is computed with an integer loop, without `math.h`.

### 3️⃣ Complex — Binary LSD radix sort · O(n log n)

Works on the normalized ranks, one bit at a time, from the least significant to the most significant:

```
for each bit b in 0 … ⌈log₂ n⌉ − 1:
    repeat |a| times:
        if bit b of top(a) is 0 → pb
        else                    → ra
    while b is not empty → pa
```

The bit is read with `(value >> b) & 1`. Each pass is **stable**: it keeps the order established by the previous bits. After the last bit, the stack is fully sorted.

**Upper bound:** `⌈log₂ n⌉` passes, each with at most `n` (`pb`/`ra`) plus `n` (`pa`):

```
ops ≤ 2n · ⌈log₂ n⌉  =  O(n log n)
```

For 500 numbers: 9 bits, giving **6784 operations**.

**Space:** O(1) auxiliary.

---

## 🎯 Adaptive Strategy

The default strategy measures the disorder first, then picks the method whose complexity fits that regime, as required by the subject:

| Disorder | Method used | Complexity |
|---|---|---|
| `< 0.2` | Simple (minimum extraction) | O(n²) |
| `0.2 ≤ d < 0.5` | Medium (chunks) | O(n√n) |
| `≥ 0.5` | Complex (radix) | O(n log n) |

### Rationale for the thresholds

- **Low disorder (< 0.2):** most elements are already close to their final position. The minimum is almost always near the top, so the rotations per extraction are small and the simple method generates very few operations in practice. Its O(n²) worst case is not reached on this kind of input. *Example: 30 numbers with 11.26% disorder → 65 operations.*
- **Medium disorder (0.2 – 0.5):** the input is partially ordered. Chunks exploit this structure: elements of the same range tend to be close to each other, so fewer `ra` are spent skipping elements.
- **High disorder (≥ 0.5):** the input behaves like random data, or worse. Radix sort guarantees an upper bound of `2n·⌈log₂ n⌉` operations **regardless of the initial order**, which gives a predictable worst case.

The thresholds `0.2` and `0.5` are the ones defined by the subject. They split the range between "almost sorted", "partially sorted" and "random or reversed" input.

> **Note.** In our tests, chunk sort often produces fewer operations than radix sort on random input of this size (≈ 5300 vs 6784 for 500 numbers), because the constant factor of `n√n` is small for `n ≤ 500`. We still use radix sort for high disorder because the subject requires an O(n log n) method in that regime, and because its bound does not depend on the distribution of the input.

---

## 📊 Performance

Measured with random inputs and verified with `checker_linux`:

| Input size | `--simple` | `--medium` | `--complex` | Default (adaptive) | Required to pass |
|---|---|---|---|---|---|
| 3 | ≤ 2 | ≤ 2 | ≤ 2 | ≤ 2 | — |
| 5 | ≤ 12 | ≤ 12 | ≤ 12 | ≤ 12 | — |
| 100 | ~1450 | **~600** | 1084 | 590 – 1084 | < 2000 ✅ |
| 500 | ~32 000 | **~5350** | 6784 | 5290 – 6784 | < 12 000 ✅ |

With the default strategy, both benchmarks are at the **"good"** level (< 1500 / < 8000) and sometimes reach **"excellent"** (< 700 / < 5500) when the measured disorder selects the medium strategy.

Every strategy was tested on sizes 2, 3, 4, 5, 6, 10, 100 and 500: all results were `OK`.

---

## 🗂 Project Structure

```
push_swap/
├── Makefile
├── push_swap.h          # types, enums and prototypes
├── main.c               # program flow
├── parse_flags.c        # --simple, --medium, --complex, --adaptive, --bench
├── parse_args.c         # number validation, overflow and duplicates
├── errors.c             # "Error\n" on stderr + cleanup
├── stack_utils.c        # node creation, insertion, duplicate check, free
├── stack_query.c        # is_sorted, find_min_pos, find_max_pos, get_max
├── primitives.c         # swap, push, rotate, rev_rotate (no output)
├── ops_swap_push.c      # sa, sb, ss, pa, pb
├── ops_rotate.c         # ra, rb, rr
├── ops_rev_rotate.c     # rra, rrb, rrr
├── record.c             # prints each operation and counts it
├── moves.c              # bring_to_top_a / bring_to_top_b (shortest path)
├── disorder.c           # disorder metric
├── index.c              # normalization to ranks 0 … n-1
├── sort_small.c         # 2, 3, 4 and 5 elements
├── sort_simple.c        # O(n²)       minimum extraction
├── sort_medium.c        # O(n√n)      chunk sort
├── sort_complex.c       # O(n log n)  radix sort
├── dispatch.c           # strategy selection and sorting flow
├── bench.c              # --bench output
└── libft/               # our own C library
```

---

## 👥 Contributions

This project was developed by two learners. Both of us took part in the design discussions, reviewed each other's code and are able to explain every part of the project.

### elsouza
- Initial architecture: `push_swap.h`, data types and the circular doubly linked list
- Stack primitives (`swap`, `push`, `rotate`, `rev_rotate`) and the 11 official operations
- Operation recording and counting (`record.c`)
- Argument and flag parsing, input validation and error handling
- Disorder metric (`disorder.c`)
- Base of `main.c` and the stack utilities

### gbaccell
- Normalization (`index.c`)
- Sorting algorithms: small cases, simple (O(n²)), medium (O(n√n)) and complex (O(n log n))
- Movement helpers and stack queries (`moves.c`, `stack_query.c`)
- Strategy dispatch and adaptive logic (`dispatch.c`)
- Benchmark mode (`bench.c`)
- Testing with the checker, performance measurement and this README

---

## 📚 Resources

### References
- [Big O notation — Wikipedia](https://en.wikipedia.org/wiki/Big_O_notation)
- [Inversion (discrete mathematics) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)) — the basis of the disorder metric
- [Selection sort — Wikipedia](https://en.wikipedia.org/wiki/Selection_sort)
- [Bucket sort — Wikipedia](https://en.wikipedia.org/wiki/Bucket_sort) — the idea behind chunk sorting
- [Radix sort — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort)
- [Doubly linked list — Wikipedia](https://en.wikipedia.org/wiki/Doubly_linked_list)
- [Bitwise operations in C — Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)
- The push_swap subject (v1.2) and the `checker_linux` binary provided by 42

### Use of AI

We used **Claude** (Anthropic) as a learning assistant, in line with the AI guidelines of the subject:

- **Organization:** splitting the project into files and functions, setting the order of implementation, and keeping track of what was done and what was left.
- **Help with reasoning:** explanations of concepts we had not used before, such as bitwise operations (`>>` and `&`), traversing a circular list, the idea behind chunk sorting and radix sort, and complexity arguments. Each function was explained with its idea, its steps and an incomplete skeleton, which **we filled in ourselves**. The errors we made were explained to us so that we could fix them and understand why they were wrong.
- **Testing:** running the program against the checker with random inputs of different sizes, every strategy and edge cases (already sorted input, duplicates, invalid arguments, `int` limits), and measuring the number of operations for the benchmarks.

All the code in this repository was written by us. We reviewed it together and can explain and defend every part of it.
