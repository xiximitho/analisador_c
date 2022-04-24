//
// Created by felipe on 4/16/22.
//
#ifndef LEXICO_H
#define LEXICO_H

#include "gtk-4.0/gtk/gtk.h"

void parse(char *str);

bool ehSimbolo(char ch);
bool identificadorValido(char *str);
bool ehOperador(char ch);
bool ehReservada(char *str);
bool ehNumero(char *str);
bool ehEspecial(char ch);
bool ehRelacional(char esquerda, char direita);
bool ehAtribuicao(char esquerda, char direita);
char *subString(const char *baseStr, int l, int r);

#endif //LEXICO_H
