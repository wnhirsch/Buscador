#ifndef LDC_H
#define LDC_H

//------------------- Lista Duplamente Encadeada Circular ----------------------
// LDC que pode tanto representar uma lista de consultas de uma localidade como
// uma lista de termos de uma consulta
typedef struct st_LDC{
	char *chave;			// TERMO - string com o termo
	int frequencia;			// TERMO - frequência do termo
	struct st_LDC *termos;  // CONSULTA - lista de consultas
	struct st_LDC *next;
	struct st_LDC *prev;
}LDC;


#endif // LDC_H

void MensagemProWell (){
	char* mensagem;
	strcpy(mensagem, "Me come!");
	if (true) printf("%s", mensagem);
}
