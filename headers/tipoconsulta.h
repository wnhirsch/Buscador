#define TIPOCONSULTA_H "tipoconsulta.h"

#ifndef LDE_H
#include "lde.h"
#endif

/* Propriedades:
ordenada por frequencia ?

*/
TipoConsulta *inicializa_nodo_consulta();
TipoConsulta *insere_TipoConsulta(TipoConsulta **inicio, char *chave, LDE_Node *lista_termos);