//
// Created by felipe on 4/16/22.
//
#ifndef LEXICO_H
#define LEXICO_H

#include "gtk-4.0/gtk/gtk.h"

void parse(gchar *str);

bool ehSimbolo(gchar ch);
bool identificadorValido(gchar *str);
bool ehOperador(gchar ch);
bool ehReservada(gchar *str);
bool ehNumero(gchar *str);
bool ehEspecial(gchar ch);
bool ehRelacional(gchar esquerda, gchar direita);
bool ehAtribuicao(gchar esquerda, gchar direita);
gchar *subString(const gchar *baseStr, int primeiro, int ultimo);

#endif //LEXICO_H
