#include <libquantum.h>

t_tensr *f_setone(const size_t i, const size_t n, t_dtype dtype)
{
    (void)i;
    return (basis_ket(1, n, dtype));
}

t_tensr *f_not(const size_t i, const size_t n, t_dtype dtype)
{
    if (n != 2)
        return (NULL);
    return (basis_ket(1 - i, n, dtype));
}

t_tensr *f_setzero(const size_t i, const size_t n, t_dtype dtype)
{
    (void)i;
    return (basis_ket(0, n, dtype));
}

t_tensr *f_identity(const size_t i, const size_t n, t_dtype dtype)
{
    return (basis_ket(i, n, dtype));
}

t_tensr *create_matrix(const size_t n, t_dtype dtype, t_tensr *(*f)(const size_t i, const size_t n, t_dtype dtype))
{
    size_t  i;
    t_tensr *mat;
    t_tensr *ket;
    t_tensr *bra;
    t_tensr *entry;

    if (n == 0 || dtype == DT_C64 || dtype == DT_C128)
        return (NULL);
    mat = tensr_full(0.0, 2, (size_t[]){n, n}, dtype);
    if (!mat)
        return (NULL);
    ft_printf("\n");
    i = 0;
    while (i < n)
    {
        /*
         * We can view row vectors and column vectors as matrices, and
         * perform the matrix multiplication \ket{b}\ket{a}:
        */
        ket = f(i, n, dtype);
        bra = basis_bra(i, n, dtype);
        entry = tensr_mul(ket, bra, NULL);

        ft_printf("i_%d:\n", i + 1);
        tensr_free(ket);
        tensr_free(bra);

        tensr_print(entry);

        tensr_add(mat, entry, mat);
        tensr_free(entry);
        i++;
    }
    return (mat);
}

int main(void)
{
    // Play around with the other functions
    t_tensr *mat = create_matrix(2, DT_F32, f_identity);
    if (!mat)
        return (1);
    tensr_info("matrix", mat);
    tensr_free(mat);

    ft_printf("\n------\n");
    
    // Probabilistic Operations and Stochastic Matrices
    t_tensr *state = tensr_from_data(
        (float [][2]){
            {1.0f, 1.0f/2.0f},
            {0.0f, 1.0f/2.0f},
        },
        2, (size_t[]){2, 2}, DT_F32
    );
    if (!state)
        return (1);
    t_tensr *m_1 = create_matrix(2, state->dtype, f_identity);
    if (!m_1)
        return (tensr_free(state), 1);
    t_tensr *s_1 = tensr_scale(m_1, 1.0/2.0, NULL);
    tensr_free(m_1);
    if (!s_1)
        return (tensr_free(state), 1);
    t_tensr *m_2 = create_matrix(2, state->dtype, f_setzero);
    if (!m_2)
    {
        tensr_free(s_1);
        tensr_free(state);
        return (1);
    }
    t_tensr *s_2 = tensr_scale(m_2, 1.0/2.0, NULL);
    tensr_free(m_2);
    if (!s_2)
    {
        tensr_free(s_1);
        tensr_free(state);
        return (1);
    }
    t_tensr *m_f = tensr_add(s_1, s_2, NULL);
    tensr_free(s_1);
    tensr_free(s_2);
    if (!m_f)
        return (tensr_free(state), 1);
    tensr_print(m_f);

    if (tensr_equal_eps(state, m_f, 1e-4f))
        ft_printf("\nMatrix State Operation and Final Matrix are equal\n");
    tensr_free(m_f);
    tensr_free(state);
    return (0);
}
