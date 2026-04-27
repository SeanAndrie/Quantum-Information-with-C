#ifndef LIBQUANTUM_H
# define LIBQUANTUM_H

# include <libtensr.h>

t_tensr *basis_bra(const size_t i, const size_t n, t_dtype dtype);
t_tensr *basis_ket(const size_t i, const size_t n, t_dtype dtype);

#endif
