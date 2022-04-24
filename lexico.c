//
// Created by felipe on 4/16/22.
//
#include "lexico.h"
#include "string.h"

bool ehSimbolo(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
        ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' ||
        ch == '(' || ch == ')' || ch == ':') {
        return true;
    }
    return false;
}
bool identificadorValido(char *str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' ||
        str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' ||
        str[0] == '8' || str[0] == '9' || ehSimbolo(str[0]) == true) {
        return false;
    } // Se o primeiro caractere da string for digito ou pontuacao o identificador não é valido.
    int i;
    unsigned long len = strlen(str);
    if (len == 1) {
        return true;
    } // Se o tamanho da string = 1 a validação ja foi feita.
    else {
        for (i = 1; i < len;
             i++) // Identificador não pode conter caractere especiais.
        {
            if (ehSimbolo(str[i]) == true) {
                return false;
            }
        }
    }
    return true;
}
bool ehOperador(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' ||
        ch == '<' || ch == '=') {
        return true;
    }
    return false;
}

bool ehEspecial(char ch)
{
    if (ch == '(' || ch == ')') {
        return true;
    }
    return false;
}
bool ehReservada(char *str)
{
    if (strcmp(str, "if") == 0 || strcmp(str, "then") == 0 ||
        strcmp(str, "else") == 0 || strcmp(str, "case") == 0 ||
        strcmp(str, "or") == 0 || strcmp(str, "and") == 0 ||
        strcmp(str, "for") == 0 || strcmp(str, "end") == 0 ||
        strcmp(str, "in") == 0 || strcmp(str, "begin") == 0 ||
        strcmp(str, "float") == 0 || strcmp(str, "double") == 0 ||
        strcmp(str, "int") == 0 || strcmp(str, "long_int") == 0 ||
        strcmp(str, "char") == 0 || strcmp(str, "string") == 0 ||
        strcmp(str, "short_int") == 0 || strcmp(str, "bool") == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool ehNumero(char *str)
{
    int i;
    unsigned long len = strlen(str);
    int ponto = 0;
    int nDecimal = 0;

    if (len == 0) {
        return false;
    }
    for (i = 0; i < len; i++) {
        if (ponto > 1) {
            return false;
        }
        if (nDecimal < 1 && str[i] == '.') {
            return false;
        }
        if (nDecimal <= 1) {
            nDecimal++;
        }
        if (str[i] == '.') {
            i++;
            ponto++;
        }
        // Caso a string passada *str não possuir estes caracteres 0-9 não é
        // considerada numero.
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' &&
            str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' &&
            str[i] != '8' && str[i] != '9') {
            return false;
        }
    }
    return true;
}

char *subString(const char *baseStr, int l, int r)
{
    int i;
    char *str = (char *) malloc(sizeof(char) * (r - l + 2));
    for (i = l; i <= r; i++) {
        str[i - l] = baseStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

//Identifica \n e \t para ser trocado para espaço

bool ehEspaco(char chr)
{
    return (chr == '\n' || chr == '\t');
}

int ehString(char *str)
{
    //0 - Nenhuma aspa dupla, 1 - Somente uma aspa dupla, 2 = Duas aspas duplas (String)
    short sum = 0;
    unsigned long tamanho = strlen(str);
    for (int i = 0; i < tamanho; ++i) {
        if (str[i] == '"')
            sum++;
    }
    return sum;
}
void parse(char *str)
{
    int atual = 0, proximo = 0;
    unsigned long len = strlen(str);
    while (proximo <= len && atual <= proximo) {
        if (ehEspaco(str[proximo])) {
            str[proximo] = ' ';
        }
        // Caso o caractere é um digito ou letra
        if (ehSimbolo(str[proximo]) == false) {
            proximo++;
        }

        if (ehSimbolo(str[proximo]) == true &&
            atual == proximo) // verifica se é um caractere de simbolos
        {
            if (ehRelacional(str[atual], str[proximo + 1])) {
                g_print("%c%c EH RELACIONAL\n", str[atual], str[proximo + 1]);
                proximo = proximo + 2;
                atual = proximo;
            }
            else if (ehAtribuicao(str[atual], str[proximo + 1])) {
                g_print("%c%c EH OPERADOR DE ATRIBUIÇÃO\n", str[atual], str[proximo + 1]);
                proximo = proximo + 2;
                atual = proximo;
            }
            else {
                if (ehOperador(str[proximo]) == true) {
                    g_print("%c EH OPERADOR\n", str[proximo]);
                }

                if (ehEspecial(str[proximo])) {
                    g_print("%c EH CARACTERE ESPECIAL\n", str[proximo]);
                }
                proximo++;
                atual = proximo;
            }
        }
        else if (ehSimbolo(str[proximo]) == true && atual != proximo ||
            (proximo == len
                && atual != proximo)) {
            char *sub = subString(str, atual, proximo - 1);
            // Verifica se a substring é uma palavra reservada, identificador, string ou numero
            if (ehReservada(sub) == true) {
                g_print("%s PALAVRA_RESERVADA\n", sub);
            }
            else if (ehNumero(sub) == true) {
                g_print("%s NUMERO\n", sub);
            }
            else if (ehString(sub) == 2) {
                g_print("%s EH STRING\n", sub);
            }
            else if (identificadorValido(sub) == true &&
                ehString(sub) == 0 &&
                ehReservada(sub) == false &&
                ehSimbolo(str[proximo - 1]) == false) {
                g_print("%s IDENTIFICADOR VALIDO\n", sub);
            }
            else if (identificadorValido(sub) == false &&
                ehString(sub) != 0 || ehString(sub) != 2 &&
                ehReservada(sub) == false &&
                ehSimbolo(str[proximo - 1]) == false) {
                g_print("%s NAO EH UM IDENTIFICADOR VALIDO\n", sub);
            }

            atual = proximo;
        }
    }
}
bool ehRelacional(char esquerda, char direita)
{
    if (esquerda == '<') {
        if (direita == '>') //Diferente
            return true;

        if (direita == '=') //Menor ou Igual
            return true;
    }
    else if (esquerda == '>') {
        if (direita == '=') // Maior ou Igual;
            return true;
    }
    return false;
}

bool ehAtribuicao(char esquerda, char direita)
{
    if (esquerda == ':') {
        if (direita == '=') //Atribuição
            return true;
    }
    return false;
}