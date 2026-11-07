# Rubik's Cube Solvers: Korf vs Kociemba

Two classic Rubik's Cube solvers written from scratch in C, both guided by **pattern databases**: precomputed tables of exact distances in simplified versions of the puzzle, used as admissible heuristics for search.

- **Korf's algorithm** finds **optimal** solutions (fewest possible moves) with IDA\* search, at the cost of large tables and long searches.
- **Kociemba's two-phase algorithm** finds **near-optimal** solutions in a fraction of a second, with much smaller tables.

Developed during my preparatory classes in Lyon (2023–2024). Code comments and identifiers are in French.

📄 **Full report:** [`reports/report.pdf`](reports/report.pdf) (English translation; French original: [`reports/report_fr.pdf`](reports/report_fr.pdf))

## Results

Kociemba, 100 random 30-move scrambles, all solutions verified by replaying them on the scrambled cube:

| Metric | Value |
|---|---|
| Solved and verified | 100 / 100 |
| Solution length | mean 23.2 moves (min 19, max 26) |
| Solving time | mean 0.39 s (max 2.7 s) |
| Pattern databases | 5 tables, 8.5 million entries, built in ~50 s |

For reference, every position can be solved in at most 20 moves ("God's number"), so Kociemba trades a few extra moves for speed.

## How it works

### Cube model

The cube is represented at the cubie level: the permutation and orientation of the 8 corners and 12 edges. A compressed version (`pos_comp`) packs a position into 80 bits, used to build the pattern databases breadth-first. Moves use the 18 face turns `F U L R D B`, each as a quarter turn, half turn (`X2`) or inverse quarter turn (`X3`, i.e. `X'`).

### Korf's algorithm (optimal)

IDA\* search with the heuristic `h = max(corners, edges_1, edges_2)`, where each term is the exact number of moves needed to solve one part of the cube:

| Pattern database | Encodes | Entries |
|---|---|---:|
| Corners | permutation and orientation of the 8 corners (8!·3⁷) | 88,179,840 |
| Edges 1 | position and orientation of 6 edges (12!/6!·2⁶) | 42,577,920 |
| Edges 2 | position and orientation of the 6 other edges | 42,577,920 |

Since each table gives a lower bound, their maximum is admissible and IDA\* returns an optimal solution. The three tables total about 173 million entries. Building them takes several hours.

### Kociemba's two-phase algorithm (near-optimal)

1. **Phase 1** brings the cube into the subgroup G1 = ⟨U, D, R2, L2, F2, B2⟩, where all corners and edges are oriented and the four middle-layer edges are in the middle layer (at most 12 moves).
2. **Phase 2** solves the cube using only the 10 moves of G1 (at most 18 moves).

Each phase runs its own IDA\* search with its own pattern databases:

| Phase | Pattern database | Entries |
|---|---|---:|
| 1 | corner orientation × edge orientation | 4,478,976 |
| 1 | middle-layer edge positions × edge orientation | 1,013,760 |
| 1 | middle-layer edge positions × corner orientation | 1,082,565 |
| 2 | permutation of the 8 top/bottom edges × middle-layer edges | 967,680 |
| 2 | corner permutation × middle-layer edges | 967,680 |

## Usage

Requires a C compiler (`gcc`) and `make`.

```bash
make

# 1. Build the pattern databases (once)
./rubik gen kociemba     # ~1 minute, ~18 MB on disk
./rubik gen korf         # several hours, several GB of RAM

# 2. Scramble a cube with random moves and solve it
./rubik solve kociemba            # 30-move scramble
./rubik solve korf 10             # 10-move scramble (optimal search grows quickly with depth)

# 3. Benchmark: n random scrambles, with statistics
./rubik bench kociemba 100 30
```

Example output (the scrambled cube is also drawn as a colored net in UTF-8 terminals):

```
Scramble (30 moves): R B U3 D2 R3 B D3 F2 L L2 U3 F2 D2 D F2 L R2 F3 L3 F L3 B3 F F3 L2 U2 F2 F F2 D3
Phase 1 depth: 10
Phase 2 depth: 15

Solution (25 moves, 0.75 s): B R3 B3 D3 F U R3 D2 U3 L3 L2 D3 R2 B2 U R2 U3 B2 U B2 D L2 U3 B2 L2
Verified: cube solved
```

The pattern databases are written as text files in the current directory and are not tracked by git.

## Code structure

Everything is in [`rubik.c`](rubik.c):

| Part | Main functions |
|---|---|
| Cube model and moves | `pos`, `pos_comp`, `f`, `u`, …, `void_univ_move`, `shuffle` |
| Encodings into table indices | `corner_encoding`, `edge_1_encoding`, `encoding_oc_and_oa`, … |
| Pattern database generation (breadth-first search) | `gen_pdb_corners`, `gen_pdb_edges_1`, `gen_pdb_phase_1_*`, `gen_pdb_phase_2_*` |
| Solvers | `korf_1d1` (IDA\*), `kociemba`, `solver_naif` (iterative deepening without heuristic) |
| Display | `render`, `print_moves` |
| Command-line interface | `main`, `cmd_gen`, `cmd_solve`, `cmd_bench` |
