// CT5 — Death tests com GoogleTest
// ---------------------------------
// O que é um death test?
//   - Um teste que valida que uma chamada TERMINA o processo (por crash/abort) ou por exit()
//     e que uma MENSAGEM esperada foi escrita (regex).
//
// Macros principais:
//   - EXPECT_DEATH(statement, regex)  -> espera que *statement* mate o processo (ex.: abort())
//   - ASSERT_DEATH(statement, regex)  -> igual, mas "fatal" (termina o teste à primeira falha)
//   - EXPECT_EXIT(statement, predicate, regex) -> espera que termine por *exit(code)* e valida o código
//       • predicate típico: ::testing::ExitedWithCode(N)
//
// Dicas práticas:
//   - A regex é aplicada ao *stderr* (e stdout). Usa mensagens simples sem caracteres especiais,
//     ou escapa-os. Ex.: "division by zero".
//   - Garante que escreves e *fflush(stderr)* antes de abort/exit.
//   - Em POSIX, abort() costuma enviar SIGABRT; não dependemos do sinal, só da morte e mensagem.
//
// Para o exercício, incluímos o .cpp do SUT diretamente (sem header):
#include <gtest/gtest.h>
#include "../../src/Exercises/CT5_death.cpp"

// 1) EXPECT_DEATH — valida que a função termina o processo (abort) e emite a mensagem esperada.
//
// Aqui, UnsafeDivide(1,0) escreve "division by zero" e chama std::abort().
TEST(Death, DivisionByZero_ABORTs) {
    // A regex "division by zero" deve aparecer na saída capturada (stderr)
    EXPECT_DEATH(bank::UnsafeDivide(1, 0), "division by zero");
}

// 2) ASSERT_DEATH — igual ao EXPECT_DEATH, mas falha "fatal" (termina este teste imediatamente).
//
// RequireNonNull(nullptr) escreve "null pointer" e chama std::abort().
TEST(Death, NullPointer_ABORTs_FATAL) {
    ASSERT_DEATH(bank::RequireNonNull(nullptr), "null pointer");
    // Qualquer linha aqui NÃO será executada se a asserção acima falhar.
}

// 3) EXPECT_EXIT — quando a função termina por exit(code) (não por abort/crash).
//
// MaybeExit("--help") imprime "Usage:" e faz exit(2). Verificamos o *código de saída*
// e também a mensagem via regex.
TEST(Death, Help_ExitsWithCode2_AndPrintsUsage) {
    EXPECT_EXIT(
        bank::MaybeExit("--help"),
        ::testing::ExitedWithCode(2),  // predicado sobre o código de saída
        "Usage:"                       // regex que deve aparecer em stderr
    );
}

// 4) Caminhos "seguros" NÃO devem ser colocados numa macro DEATH/EXIT.
//    Em vez disso, chamamos normalmente para mostrar contraste.
//
// Este teste não é um death test; serve só para reforçar a diferença.
TEST(Death, SafePaths_DoNotDie) {
    // Não deve terminar o processo:
    bank::UnsafeDivide(4, 2);              // ok
    bank::RequireNonNull("nonnull");       // ok
    EXPECT_EQ(bank::MaybeExit("run"), 0);  // ok, sem exit()
}

// Observações:
//  - Em ambientes com sanitizers/TSAN, death tests podem precisar do estilo "threadsafe":
//      ::testing::FLAGS_gtest_death_test_style = "threadsafe";
//    Coloca isso em main() de testes se necessário.
//  - Em Windows puro, sinais comportam-se de forma diferente; em WSL/Linux está ok.
//  - Death tests criam um processo filho para isolar a morte; por isso são mais "pesados".
