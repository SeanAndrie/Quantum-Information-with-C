#ifndef LIBQUANTUM_H
# define LIBQUANTUM_H

# include <libtensr.h>

typedef enum e_state
{
    STATE_PLUS,
    STATE_MINUS,
}               t_state;

t_tensr *basis_bra(const size_t i, const size_t n, t_dtype dtype);
t_tensr *basis_ket(const size_t i, const size_t n, t_dtype dtype);

t_tensr *quantum_state(const t_tensr *t, t_state state);

#endif
