// CT5 — Death tests (SUT: System Under Test)
// -------------------------------------------
// Este ficheiro define 3 funções propositadamente "perigosas" para demonstrar death tests:
//
//  1) UnsafeDivide(a,b)   -> em b==0 escreve uma mensagem em stderr e *abort()* (mata o processo)
//  2) RequireNonNull(p)   -> em p==nullptr escreve em stderr e *abort()*
//  3) MaybeExit(arg)      -> se arg=="--help" escreve "Usage:" e *exit(2)*
//
// Notas importantes para death tests:
//  - Usa sempre *stderr* + fflush antes de abort/exit, para garantir que o texto fica capturado.
//  - Death tests verificam que o processo TERMINA (por sinal, p.ex. SIGABRT, ou por exit(code)) e
//    que a MENSAGEM esperada foi emitida (via regex).
//
// Mantemos tudo num .cpp para o teste poder fazer #include direto.

#include <cstdio>   // fprintf, stderr
#include <cstdlib>  // std::abort, std::exit
#include <string>

namespace bank {

inline void UnsafeDivide(int a, int b) {
    if (b == 0) {
        std::fprintf(stderr, "division by zero\n"); // mensagem que o teste vai procurar
        std::fflush(stderr);                         // garante que sai no pipe capturado
        std::abort();                                // termina via SIGABRT (morte do processo)
    }
    (void)(a / b); // não usamos o resultado; evita warning
}

inline void RequireNonNull(const char* p) {
    if (p == nullptr) {
        std::fprintf(stderr, "null pointer\n");
        std::fflush(stderr);
        std::abort(); // morte por abort
    }
    // normal path: nada a fazer
}

inline int MaybeExit(const std::string& arg) {
    if (arg == "--help") {
        std::fprintf(stderr, "Usage: bank_tool [options]\n");
        std::fflush(stderr);
        std::exit(2); // termina "limpamente" com código 2 (não é abort)
    }
    return 0; // não termina o processo
}

} // namespace bank
