A small program demonstrating how deterministic functions over a finite state
space can be lifted into matrix form, and how those matrices compose to
represent probabilistic (stochastic) operations.

---

## Core idea

A deterministic function `f : {0, …, n-1} → {0, …, n-1}` maps every basis
state to exactly one output state. `create_matrix` turns such a function into
an `n × n` matrix using the outer-product decomposition:

```
M = Σᵢ |f(i)⟩⟨i|
```

Each term `|f(i)⟩⟨i|` is an `n × n` rank-1 matrix (a ket times a bra).
Summing over all `i` assembles the full operation matrix.  Multiplying `M`
against any probability (column) vector then correctly propagates each state's
probability mass to its image under `f`.

---

## Deterministic functions

| Function | Mapping | Resulting matrix |
|---|---|---|
| `f_identity` | `i → i` | Identity matrix `I` |
| `f_setzero` | `i → 0` | All probability collapses to state 0 |
| `f_setone` | `i → 1` | All probability collapses to state 1 |
| `f_not` | `0 → 1, 1 → 0` | Swap rows — the NOT / bit-flip gate (`n = 2` only) |

Pass any of these (or your own) into `create_matrix` to get the corresponding
permutation / projection matrix.

`f_not` is the only function restricted to `n = 2`. It uses the index mapping
`1 - i` to flip 0 ↔ 1, producing the matrix:

```
M_NOT = | 0  1 |
        | 1  0 |
```

Unlike `f_setzero` and `f_setone`, `f_not` is invertible — applying it twice
returns the identity. Its matrix is its own inverse (`M_NOT² = I`).

---

## Stochastic matrix construction

The `main` function demonstrates how to build a **stochastic matrix** by
mixing deterministic ones. It constructs:

```
M_f = (1/2) · M_identity + (1/2) · M_setzero
```

This represents a probabilistic operation that, with probability ½, does
nothing, and with probability ½, resets the state to 0. Column `j` of the
result gives the output distribution when the input is definitely in state
`j` — as required for a valid stochastic matrix (each column sums to 1).

The program then checks that `M_f` matches a hand-written reference state
matrix using an epsilon comparison, confirming the construction is correct.

---

## Key functions

| Function | Description |
|---|---|
| `create_matrix(n, dtype, f)` | Build an `n × n` matrix from deterministic function `f` via outer-product decomposition |
| `basis_ket(i, n, dtype)` | Column vector `\|i⟩` — the `i`-th standard basis vector |
| `basis_bra(i, n, dtype)` | Row vector `⟨i\|` — the `i`-th standard basis covector |
| `tensr_mul(ket, bra, out)` | Outer product (matrix multiply of column × row) |
| `tensr_scale(m, s, out)` | Scalar multiplication |
| `tensr_add(a, b, out)` | Element-wise addition |
| `tensr_equal_eps(a, b, eps)` | Approximate equality check |

---

## Limitations

- Complex dtypes (`DT_C64`, `DT_C128`) are not supported by `create_matrix`.
  Extending to complex spaces would require conjugate-transposing the bra
  (Hermitian adjoint) rather than a plain transpose.
- The program currently hard-codes `n = 2` (a single bit). `create_matrix`
  is generic in `n`, so any finite state space size works.
