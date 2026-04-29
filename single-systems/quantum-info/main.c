#include <libquantum.h>

int main(void)
{
    t_tensr *s = tensr_from_data(
        (float complex [][1]){
            {(1.0f + 2.0 *I) / 3.0f + 0.0 * I},
            {(-2.0f + 0.0 * I) / 3.0f + 0.0 * I}
        },
        2, (size_t []){2, 1}, DT_C64
    );
    if (!s)
        return (1);
    tensr_print(s);

    t_tensr *s_plus = quantum_state(s, STATE_PLUS);
    if (!s_plus)
        return (1);
    tensr_print(s_plus);
    tensr_free(s_plus);

    t_tensr *s_minus = quantum_state(s, STATE_MINUS);
    if (!s_minus)
        return (1);
    tensr_print(s_minus);
    tensr_free(s_minus);

    t_tensr *s_conj = tensr_conjugate(s, NULL);
    tensr_free(s);
    if (!s_conj)
        return (1);
    t_tensr *s_conj_v = tensr_transpose(s_conj);
    if (!s_conj_v)
        return (tensr_free(s_conj), 1);
    tensr_print(s_conj_v);
    tensr_free(s_conj_v);
    return (0);
}
