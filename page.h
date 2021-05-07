#ifndef PAGES_H
#define PAGES_H

typedef struct page Page;

/*Inicializa uma pagina
 * inputs: uma string
 * output: ponteiro para page inicializado
 * pre-condicao: string com o nome da pagina existe
 * pos-condicao: page de retorno existe
 */
Page* init_page(char* nome);

/*Retorna o nome da pagina
 * inputs: page
 * output: uma string
 * pre-condicao: page existe
 * pos-condicao: page não é modificado
 */
char* get_name_page(Page* page);

/*Retorna o Page Rank da pagina
 * inputs: page
 * output: um double
 * pre-condicao: page existe
 * pos-condicao: page não é modificado
 */
double get_page_rank(Page* page);

/*Adiciona o numero de links na pagina
 * inputs: page e um inteiro
 * output: nenhum
 * pre-condicao: page e inteiro existem
 * pos-condicao: page é modificada e o numero de links eh inserido
 */
void set_n_links(Page* page, int n_links);

/*Retorna o numero de links da pagina
 * inputs: page
 * output: um inteiro
 * pre-condicao: page existe
 * pos-condicao: page não é modificado
 */
int get_n_links(Page* page);

/*Insere o Page Rank na pagina
 * inputs: page e um double
 * output: nenhum
 * pre-condicao: page e double existem
 * pos-condicao: page é modificada e page rank eh inserido
 */
void set_page_rank(Page* page, double page_rank);

/*Insere um link na pagina
 * inputs: pages
 * output: nenhum
 * pre-condicao: pages existem
 * pos-condicao: page é modificada e link eh inserido
 */
void insert_page_link(Page* page, Page* link);

/*Busca um link em uma pagina
 * inputs: um page, uma lista de pages e dois inteiros
 * output: um page
 * pre-condicao: pages existem
 * pos-condicao: pages não sao modificadas
 */
Page* search_link(Page* page, Page** pages, int* i, int n_pages);

/*Compara o nome da pagina
 * inputs: void
 * output: int com o valor se iguala ou nao o nome
 * pre-condicao: passar como referencia o tipo pois esta como void
 * pos-condicao: retornar -1 ou 1 ou 0
 */
int compare_page_name(const void* a, const void* b);

/*Compara o nome da pagina
 * inputs: void
 * output: int com o valor se iguala ou nao o rank
 * pre-condicao: passar como referencia o tipo pois esta como void
 * pos-condicao: retornar -1 ou 1 ou 0
 */
int compare_page_rank(const void* a, const void* b);

/*Imprime um page
 * inputs: um page
 * output: nenhum
 * pre-condicao: page existe
 * pos-condicao: page não é modificado
 */
void print_page(Page* page);

/*Libera memória alocada para page
 * inputs: page
 * output: nenhum
 * pre-condicao: page existe
 * pos-condicao: toda a memória alocada para page foi liberada
 */
void destroy_page(Page* page);

Page** verify_query(Page** pages_verified, Page** page, char* consulta, int n_pages, char** stopwords, int stopwords_size, char* dir);

/*Busca uma page em uma lista de pages
 * inputs: uma page, uma lista de pages e dois inteiros
 * output: uma page
 * pre-condicao: pages existem
 * pos-condicao: pages não sao modificadas
 */
Page* find_page(Page** pages, int lo, int hi, char* name_page);

#endif  //PAGES_H