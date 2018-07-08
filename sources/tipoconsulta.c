#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/tipoconsulta.h"

// Insere um nodo na lista, organizado por 
TipoConsulta *inicializa_nodo_consulta(){
	TipoConsulta *consulta = (TipoConsulta*)malloc(sizeof(TipoConsulta));
	consulta->frequencia = 0;
	consulta->termos = NULL;
	consulta->prox = NULL;
	consulta->ant = NULL;
	return consulta;
}