#include "pagerank.h"

#include <math.h>
#include <stdio.h>
#define ALPHA 0.85f

static double sum_j_e_in_i(Page* page, Page** pages, double* PR_bef, int size) {
    int i = 0;
    double soma = 0;
    Page* j;
    while (i < size) {
        j = search_link(page, pages, &i, size);
        if (j == NULL) {
            break;
        } else {
            i++;
        }
        int n_links = get_n_links(j);
        if (n_links != 0)
            soma += PR_bef[i - 1] / n_links;
        else
            printf("MACACOOO\n");
    }
    return soma;
}

static double calc_Ek(double* PR, double* PR_bef, int size) {
    double Ek = 0;
    for (int i = 0; i < size; i++) {
        double aux = PR[i] - PR_bef[i];
        Ek += aux * aux;
    }

    Ek = sqrt(Ek);
    return Ek;
}

void calc_PR(Graph* graph, Page** pages) {
    int size = get_n_nodes(graph);
    double PRs[size];
    double PR_bef[size];
    double Ek = 1;

    for (int i = 0; i < size; i++) {
        PR_bef[i] = 1.0 / size;
    }
    while (Ek > 0.000001) {
        for (int i = 0; i < size; i++) {
            PRs[i] = (((1 - ALPHA) / size));
            Page* page = get_page_graph(graph, i);
            int size_links = get_n_links(page);
            if (size_links == 0) {
                PRs[i] += ALPHA * PR_bef[i];
            }
            double aux = sum_j_e_in_i(page, pages, PR_bef, size);
            PRs[i] += ALPHA * aux;
        }
        Ek = calc_Ek(PRs, PR_bef, size);
        for (int i = 0; i < size; i++) {
            PR_bef[i] = PRs[i];
        }
    }
    for (int i = 0; i < size; i++) {
        printf("%.6lf\n", PRs[i]);
    }
}