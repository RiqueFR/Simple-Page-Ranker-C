#ifndef RBT_H
#define RBT_H

typedef struct node RBT;

/**
 * Cria o noh rubro-negra
 * 
 * @param {char* value} string que vai ser o conteudo do noh.
 * @param {int n} numero para identificar se eh vermelho ou preto ( 1 ou 0 ).
 * 
 * @pre nenhum.
 * @post noh RBT criado com o conteudo do value e identificado com o 1 (RED).
 * 
 * @return Noh Arvore Rubro-Negra.
 */
RBT* create_node(char* value, int n);

/**
 * Inserir noh na arvore rubro-negra
 * 
 * @param {RBT* rbt} noh raiz da arvore.
 * @param {char* value} string que vai ser o conteudo do noh.
 * 
 * @pre value inicializado.
 * @post caso a arvore esteja seja null ele cria um noh para ela, caso o value nao esta
 * na arvore ele vai ser adicionado.
 * 
 * @return arvore atualizada.
 */
RBT* RBT_insert(RBT* rbt, char* value);

/**
 * buscar na arvore se ja possui a palavra
 * 
 * @param {RBT* rbt} noh raiz da arvore.
 * @param {char* value} string que vai ser procurado.
 * 
 * @pre value inicializado e rbt nao null.
 * @post caso possua retorna 0 se nao 1
 * 
 * @return arvore atualizada.
 */
int search(RBT* rbt, char* value);

/**
 * verifica se o noh eh vermelho
 * 
 * @param {RBT* rbt} noh da arvore.
 * 
 * @pre rbt nao null.
 * @post caso possua retorna 0 se nao 1
 * 
 * @return arvore atualizada.
 */
int is_red(RBT* rbt);

/*

*/
RBT* rotate_left(RBT* rbt);

/*

*/
RBT* rotate_right(RBT* rbt);

/*

*/
void flip_colors(RBT* rbt);

/*

*/
void imprime_rbt(RBT* rbt);

/*

*/
void RBT_delete(RBT* rbt);

#endif