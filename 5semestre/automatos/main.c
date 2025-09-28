// Matheus Gabriel Viana Araujo - 10420444
// Richard Barbosa Sanches - 10420179

#include <stdio.h>

// Final da palavra
#define _FIM_ '\0'

#define _REJEITA_ 0

#define _INTEIRO_ 1
#define _INTEIRO_COM_SINAL_ 2
#define _ERRO_ 3
#define _P_FLUTUANTE_ 4
#define _P_FLUTUANTE_COM_SINAL_ 5

int scanner(char *e) {
    char c;
    q0:
        c = *e; // Não avança o ponteiro, pois é o estado inicial
        if (c == '-' || c == '+')
            goto q8;
        else if (c >= '0' && c <= '9')
            goto q2;
        // Estado não final
        else if (c == _FIM_)
            return (_REJEITA_);
        else
            goto q11;
    q1: // aka int
        c = *++e; // Próxima letra da palavra
        if (c == '0')
            goto q1;
        else if (c >= '1' && c <= '9')
            goto q3;
        else if (c == ',')
            goto q6;
        // Estado não final
        else if (c == _FIM_)
            return (_REJEITA_);
        else
            goto q11;
    q2:
        c = *++e; // Próxima letra da palavra
        if (c >= '0' && c <= '9')
            goto q2;
        else if (c == ',')
            goto q4;
        // Estado final
        else if (c == _FIM_)
            return (_INTEIRO_);
        else
            goto q11;
    q3: // aka float
        c = *++e; // Próxima letra da palavra
        if (c >= '0' && c <= '9')
            goto q3;
        else if (c == ',')
            goto q6;
        // Estado final
        else if (c == _FIM_)
            return (_INTEIRO_COM_SINAL_);
        else
            goto q11;
    q4:
        c = *++e; // Próxima letra da palavra
        if (c == '0')
            goto q4;
        else if (c >= '1' && c <= '9')
            goto q5;
        // Estado não final
        else if (c == _FIM_)
            return (_REJEITA_);
        else
            goto q11;
    q5:
        c = *++e; // Próxima letra da palavra
        if (c >= '1' && c <= '9')
            goto q5;
        else if (c == '0')
            goto q4;
        // Estado final
        else if (c == _FIM_)
            return (_P_FLUTUANTE_);
        else
            goto q11;
    q6: // aka inteiro com sinal
        c = *++e; // Próxima letra da palavra
        if (c == '0')
            goto q6;
        else if (c >= '1' && c <= '9')
            goto q7;
        // Estado não final
        else if (c == _FIM_)
            return (_REJEITA_);
        else
            goto q11;
    q7:
        c = *++e; // Próxima letra da palavra
        if (c >= '1' && c <= '9')
            goto q7;
        else if (c == '0')
            goto q6;
        // Estado final
        else if (c == _FIM_)
            return (_P_FLUTUANTE_COM_SINAL_);
        else
            goto q11;
    q8: // aka float com sinal
        c = *++e; // Próxima letra da palavra
        if (c >= '1' && c <= '9')
            goto q3;
        else if (c == '0')
            goto q1;
        // Estado não final
        else if (c == _FIM_)
            return (_REJEITA_);
        else
            goto q11;
    q9: // aka zero
        if (c >= '1' && c <= '9')
            goto q1;
        else if (c == '0')
            goto q10;
        else if( c == _FIM_)
            return _REJEITA_;
        else 
            goto q11;
    q10:
        if (c == '0')
            goto q10;
        else if (c >= '1' && c <= '9')
            goto q1;
        else if ( c == _FIM_)
            return _REJEITA_;
        else 
            goto q11;
    q11: // aka buraco
        return _REJEITA_;
}

int main() {
    char *nums[] = {"21", "-21", "021", "2.1", "2,1", "+0,34", "05.567", "0005,5678", "-2,1"};
    
    for (int i = 0; i < 9; i++) {
        int r = scanner(nums[i]);
        switch (r) {
            case _INTEIRO_:
            puts("<INTEIRO>");
            break;
            case _INTEIRO_COM_SINAL_:
            puts("<INTEIRO COM SINAL>");
            break;
            case _P_FLUTUANTE_:
            puts("<P. FLUTUANTE>");
            break;
            case _P_FLUTUANTE_COM_SINAL_:
            puts("<P. FLUTUANTE COM SINAL>");
            break;
            case _ERRO_:
            case _REJEITA_:
            default:
            puts("<ERRO>");
            break;
        }
    }
}
