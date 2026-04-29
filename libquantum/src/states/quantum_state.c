#include <libquantum.h>

static t_tensr *scaled_ket(const t_tensr *t, const size_t i, const size_t n)
{
    t_tensr *ket;
    t_tensr *ket_s;
    float complex c_f;
    double complex c_d;
    
    ket = basis_ket(i, n, t->dtype);
    if (!ket)
        return (NULL);
    if (t->dtype == DT_C64)
    {
        c_f = ((float complex *)t->data)[i];
        ket_s = tensr_cscale(ket, c_f, NULL);
    }
    else if (t->dtype == DT_C128)
    {
        c_d = ((double complex *)t->data)[i];
        ket_s = tensr_cscale(ket, c_d, NULL);
    }
    tensr_free(ket);
    if (!ket_s)
        return (NULL);
    return (ket_s);
}

t_tensr *quantum_state(const t_tensr *t, t_state state)
{
    size_t  i;
    t_tensr *q_s;
    t_tensr *ket_s;

    if (!t || (t->dtype != DT_C64 && t->dtype != DT_C128))
        return (NULL);
    q_s = tensr_cfull(0.0 + 0.0 * I, t->layout.ndim, t->layout.shape, t->dtype);
    if (!q_s)
        return (NULL);
    i = 0;
    while (i < q_s->size)
    {
        ket_s = scaled_ket(t, i, q_s->size);
        if (!ket_s)
            return (tensr_free(q_s), NULL);
        if (state == STATE_PLUS)
            tensr_add(q_s, ket_s, q_s);
        else if (state == STATE_MINUS)
            tensr_sub(q_s, ket_s, q_s);
        i++;
    }
    return (q_s);
}
