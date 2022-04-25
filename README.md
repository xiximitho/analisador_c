# Análisador Léxico

Projeto de análisador léxico para a matéria de Compiladores, provida pela Unochapecó, curso de Ciência da Computação (2022), professora Viviane Duarte Bonfim.

## Projeto

Este projeto consiste em análisar palavras/caracteres recebidos em uma entrada e então utilizar a tabela criada com cada conjunto de caracteres para retornar os Lexemas/Tokens providos da tabela.

| Token       | Lexema                                                                                                                 |
| ----------- | ---------------------------------------------------------------------------------------------------------------------- |
| Atribuição  | :=                                                                                                                     |
| Aritméticos | +, -, *, /                                                                                                             |
| Relacionais | <, <=, <>, >, >=, =                                                                                                    |
| Especiais   | (, )                                                                                                                   |
| Separadores | , ;                                                                                                                    |
| Reservadas  | begin, end, if, then, else, case, for, in, and, or, const, string, double, float, int, long_int, short_int, bool, char |

Utilizado o sistema de configuração de build CMake na versão 3.22, foi incluido o toolkit GTK4 (*GTK is a free and open-source cross-platform widget toolkit for creating graphical user interfaces.* https://www.gtk.org/). Sendo necessário sua instalação junto ao compilador GCC (https://gcc.gnu.org/) para compilação.

```cmake
cmake_minimum_required(VERSION 3.22)
project(analisador_c C)

set(CMAKE_C_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(analisador_c main.c lexico.h lexico.c)

target_link_libraries(analisador_c ${GTK4_LIBRARIES})
install(TARGETS analisador_c)
```
