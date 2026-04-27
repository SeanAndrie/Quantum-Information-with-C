#include <libquantum.h>

static void assign_value(t_tensr *t, const size_t i, t_dtype dtype)
{
    if (dtype == DT_I32)
        ((int32_t *)t->data)[i] = 1;
    else if (dtype == DT_I64)
        ((int64_t *)t->data)[i] = 1;
    else if (dtype == DT_F32)
        ((float *)t->data)[i] = 1.0f;
    else if (dtype == DT_F64)
        ((double *)t->data)[i] = 1.0;
    else if (dtype == DT_C64)
        ((float complex *)t->data)[i] = 1.0f + 0.0f * I;
    else if (dtype == DT_C128)
        ((double complex *)t->data)[i] = 1.0 + 0.0 * I;
}

t_tensr *basis_bra(const size_t i, const size_t n, t_dtype dtype)
{
    t_tensr *bra;

    if (n == 0 || i >= n || dtype == DT_U8)
        return (NULL);
    if (dtype == DT_C64 || dtype == DT_C128)
        bra = tensr_cfull(0.0 + 0.0 * I, 2, (size_t[]){1, n}, dtype);
    else
        bra = tensr_full(0.0, 2, (size_t[]){1, n}, dtype);
    if (!bra)
        return (NULL);
    assign_value(bra, i, dtype);
    return (bra);
}
