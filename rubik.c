#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <time.h>
#include <string.h>

struct pos_comp {
    uint16_t pc;
    uint16_t oc;
    uint32_t pa;
    uint16_t oa;
};
typedef struct pos_comp pos_comp;

struct pos {
    int pc[8];
    int oc[8];
    int pa[12];
    int oa[12];
};
typedef struct pos pos;

struct pos_comp_and_depth{
    pos_comp *p;
    uint8_t depth;
};
typedef struct pos_comp_and_depth pos_comp_and_depth;

struct pos_and_depth{
    pos *p;
    int depth;
};
typedef struct pos_and_depth pos_and_depth;

struct pos_and_depth_and_moves{
    pos *p;
    int depth;
    int moves[20];
};
typedef struct pos_and_depth_and_moves pos_and_depth_and_moves;

int expo_rapide(int x, int n){
    if (n==0){
        return 1;
    }
    else if (n % 2 == 0){
        int p = expo_rapide(x, n/2);
        return p*p;
    }
    else {
        int p = expo_rapide(x, n/2);
        return x*p*p;
    }
}

int max(int n1, int n2){
    if(n1 >= n2){
        return n1;
    }
    return n2;
}

int min(int n1, int n2){
    if(n1 <= n2){
        return n1;
    }
    return n2;
}

double max_double(double n1, double n2){
    if(n1 >= n2){
        return n1;
    }
    return n2;
}

double min_double(double n1, double n2){
    if(n1 <= n2){
        return n1;
    }
    return n2;
}

void print_array(int *arr, int n){
    for (int i = 0; i < n ; i++){
        printf("arr[%i] = %i\n", i, arr[i]);
    }
    printf("\n");
}

// Copie les n premiers elements de arr1 dans arr2
void array_copy(int *arr1, int *arr2, int n){
    for (int i = 0; i < n ; i++){
        arr2[i] = arr1[i];
    }
}

bool arr_equal(int *arr1, int *arr2, int n){
    for (int j = 0 ; j < n ; j++){
        if (arr1[j] != arr2[j]){
            return false;
        }
    }
    return true;
}

int *arr_concat(int *arr1, int *arr2, int n1, int n2){
    int *res = malloc(sizeof(int)*(n1 + n2));
    for(int i = 0; i < n1; i++){
        res[i] = arr1[i];
    }
    for(int i = 0; i < n2; i++){
        res[i + n1] = arr2[i];
    }
    free(arr1);
    free(arr2);
    return res;
}

int get_ligne(FILE *fptr, int l){
    assert(fptr != NULL);
    rewind(fptr);
    char line[5];
    int cnt = 0;
    while(fgets(line, sizeof(line), fptr)){
        if(cnt == l){
            return atoi(line);
        }
        cnt++;
    }
    assert(false);
    return 0;
}

pos_comp *etat_initial_comp(void){
    pos_comp *ei = malloc(sizeof(pos_comp));
    ei -> pc = 0;
    ei -> pa = 0;
    ei -> oc = 0;
    ei -> oa = 0;
    return ei;
}

pos *etat_initial(void){
    pos *ei = malloc(sizeof(pos));
    for (int i = 0 ; i < 8; i++){
        ei -> pc[i] = i;
        ei -> oc[i] = 0;
    }
    for (int i = 0 ; i < 12; i++){
        ei -> pa[i] = i;
        ei -> oa[i] = 0;
    }
    return ei;
}

int puiss_3[8] = {1, 3, 9, 27, 81, 243, 729, 2187};
int fact[12] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};


int f_oc[8] = {2, 1, 0, 0, 0, 0, 1, 2};
int f_oa[12] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int f_pc[8] = {6, 0, 2, 3, 4, 5, 7, 1};
int f_pa[12] = {3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11};

int f2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int f2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int f2_pc[8] = {7, 6, 2, 3, 4, 5, 1, 0};
int f2_pa[12] = {2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11};

int f3_oc[8] = {2, 1, 0, 0, 0, 0, 1, 2};
int f3_oa[12] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int f3_pc[8] = {1, 7, 2, 3, 4, 5, 0, 6};
int f3_pa[12] = {1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11};

int u_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int u_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int u_pc[8] = {1, 3, 0, 2, 4, 5, 6, 7};
int u_pa[12] = {0, 5, 2, 3, 1, 9, 6, 7, 8, 4, 10, 11};

int u2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int u2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int u2_pc[8] = {3, 2, 1, 0, 4, 5, 6, 7};
int u2_pa[12] = {0, 9, 2, 3, 5, 4, 6, 7, 8, 1, 10, 11};

int u3_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int u3_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int u3_pc[8] = {2, 0, 3, 1, 4, 5, 6, 7};
int u3_pa[12] = {0, 4, 2, 3, 9, 1, 6, 7, 8, 5, 10, 11};

int l_oc[8] = {1, 0, 2, 0, 1, 0, 2, 0};
int l_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int l_pc[8] = {2, 1, 4, 3, 6, 5, 0, 7};
int l_pa[12] = {4, 1, 2, 3, 8, 5, 6, 0, 7, 9, 10, 11};

int l2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int l2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int l2_pc[8] = {4, 1, 6, 3, 0, 5, 2, 7};
int l2_pa[12] = {8, 1, 2, 3, 7, 5, 6, 4, 0, 9, 10, 11};

int l3_oc[8] = {1, 0, 2, 0, 1, 0, 2, 0};
int l3_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int l3_pc[8] = {6, 1, 0, 3, 2, 5, 4, 7};
int l3_pa[12] = {7, 1, 2, 3, 0, 5, 6, 8, 4, 9, 10, 11};

int r_oc[8] = {0, 2, 0, 1, 0, 2, 0, 1};
int r_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int r_pc[8] = {0, 7, 2, 1, 4, 3, 6, 5};
int r_pa[12] = {0, 1, 6, 3, 4, 2, 10, 7, 8, 9, 5, 11};

int r2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int r2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int r2_pc[8] = {0, 5, 2, 7, 4, 1, 6, 3};
int r2_pa[12] = {0, 1, 10, 3, 4, 6, 5, 7, 8, 9, 2, 11};

int r3_oc[8] = {0, 2, 0, 1, 0, 2, 0, 1};
int r3_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int r3_pc[8] = {0, 3, 2, 5, 4, 7, 6, 1};
int r3_pa[12] = {0, 1, 5, 3, 4, 10, 2, 7, 8, 9, 6, 11};

int d_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int d_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d_pc[8] = {0, 1, 2, 3, 5, 7, 4, 6};
int d_pa[12] = {0, 1, 2, 7, 4, 5, 3, 11, 8, 9, 10, 6};

int d2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int d2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d2_pc[8] = {0, 1, 2, 3, 7, 6, 5, 4};
int d2_pa[12] = {0, 1, 2, 11, 4, 5, 7, 6, 8, 9, 10, 3};

int d3_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int d3_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int d3_pc[8] = {0, 1, 2, 3, 6, 4, 7, 5};
int d3_pa[12] = {0, 1, 2, 6, 4, 5, 11, 3, 8, 9, 10, 7};

int b_oc[8] = {0, 0, 1, 2, 2, 1, 0, 0};
int b_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int b_pc[8] = {0, 1, 3, 5, 2, 4, 6, 7};
int b_pa[12] = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8};

int b2_oc[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int b2_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int b2_pc[8] = {0, 1, 5, 4, 3, 2, 6, 7};
int b2_pa[12] = {0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9};

int b3_oc[8] = {0, 0, 1, 2, 2, 1, 0, 0};
int b3_oa[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int b3_pc[8] = {0, 1, 4, 2, 5, 3, 6, 7};
int b3_pa[12] = {0, 1, 2, 3, 4, 5, 6, 7, 11, 8, 9, 10};

// Prend en entrée une position compressée du rk, et un indice correspondant à un coin, et renvoie l'orientation du coin. 
int is_turned_corner_comp (int k, pos_comp *p){
    int div = puiss_3[k];
    return (p -> oc / div) % 3;
}

// Prend en entrée une position compressée du rk, et un indice correspondant à une arête, et renvoie l'orientation de l'arête. 
int is_flipped_edge_comp(int k, pos_comp *p){
    return (p -> oa >> k) % 2;
}

// Renvoie le tableau de l'orientation des coins d'une position compressée du rk donnée en entrée. 
int *pos_comp_to_oc_arr (pos_comp *p){
    int *tab_orientations = malloc(sizeof(int)*8);
    for (int i = 0; i < 8; i++){
        tab_orientations[i] = is_turned_corner_comp(i, p);
    };
    return tab_orientations;
}

// Renvoie le tableau de l'orientation des arêtes d'une position compressée du rk donnée en entrée. 
int *pos_comp_to_oa_arr (pos_comp *p){
    int *tab_orientations = malloc(sizeof(int)*12);
    for (int i = 0; i < 12; i++){
        tab_orientations[i] = is_flipped_edge_comp(i, p);
    };
    return tab_orientations;
}

// Renvoie le tableau de la permutation des coins d'une position compressée du rk donnée en entrée. 
int *pos_comp_to_pc_arr (pos_comp *p){
    int *tab_permutation = malloc(sizeof(int)*8);
    // 1ère étape: reconstituer le code de Lehmer codé par pc
    int lehmer[8];
    int temp = p -> pc;
    for (int i = 0 ; i < 8 ; i++){
        lehmer[i] = temp % (i + 1);
        temp = temp / (i + 1);
    }
    // 2ème étape: reconstituer la permutation codée par le code de Lehmer
    int list[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    for (int i = 7 ; i >= 0  ; i--){
        int j = 7;  // indice tableau
        int k = 0;  // indice liste (sans les -1)
        while (k < lehmer[i] || list[j] == -1){
            if (list[j] != -1){
                k++;
            }
            j--;
        }
        tab_permutation[i] = list[j];
        list[j] = -1;
    }
    return tab_permutation;
}

// Renvoie le tableau de la permutation des arêtes d'une position compressée du rk donnée en entrée
int *pos_comp_to_pa_arr (pos_comp *p){
    int *tab_permutation = malloc(sizeof(int)*12);
    // 1ère étape: reconstituer le code de Lehmer codé par pa
    int lehmer[12];
    int temp = p -> pa;
    for (int i = 0 ; i < 12 ; i++){
        lehmer[i] = temp % (i + 1);
        temp = temp / (i + 1);
    }
    // 2ème étape: reconstituer la permutation codée par le code de Lehmer
    int list[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 11 ; i >= 0  ; i--){
        int j = 11;  // indice tableau
        int k = 0;  // indice liste (sans les -1)
        while (k < lehmer[i] || list[j] == -1){
            if (list[j] != -1){
                k++;
            }
            j--;
        }
        tab_permutation[i] = list[j];
        list[j] = -1;
    }
    return tab_permutation;
}

// Prend en entrée le tableau des orientations des coins d'une position du rk et renvoie sa forme compressée. 
uint16_t oc_arr_to_oc(int *oc_arr){
    uint16_t oc = 0;
    int radix = 1;
    for (int i = 0; i < 8 ; i++){
        oc += oc_arr[i]*radix;
        radix *= 3;
    }
    return oc;
}

// Prend en entrée le tableau des orientations des arêtes d'une position du rk et renvoie sa forme compressée. 
uint16_t oa_arr_to_oa(int *oa_arr){
    uint16_t oa = 0;
    int radix = 1;
    for (int i = 0; i < 12 ; i++){
        oa += oa_arr[i]*radix;
        radix *= 2;
    }
    return oa;
}

// Prend en entrée le tableau de la permutation des coins d'une position du rk et renvoie sa forme compressée. 
uint16_t pc_arr_to_pc(int *pc_arr){
    uint16_t pc = 0;
    // 1ère étape: on génère le code de Lehmer associé à la permutation
    int lehmer[8];
    for (int i = 0; i < 8; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (pc_arr[j] > pc_arr[i]){
                k++;
            }
        }
        lehmer[i] = k;
    }
    // 2ème étape; on compresse le code de Lehmer en numération factorielle
    int fact = 1;
    for (int i = 0; i < 8; i++){
        pc += lehmer[i]*fact;
        fact *= (i+1);
    }
    return pc;
}

// Prend en entrée le tableau de la permutation des arêtes d'une position du rk et renvoie sa forme compressée. 
uint32_t pa_arr_to_pa(int *pa_arr){
    uint32_t pa = 0;
    // 1ère étape: on génère le code de Lehmer associé à la permutation
    int lehmer[12];
    for (int i = 0; i < 12; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (pa_arr[j] > pa_arr[i]){
                k++;
            }
        }
        lehmer[i] = k;
    }
    // 2ème étape: on le compresse en numération factorielle
    int fact = 1;
    for (int i = 0; i < 12; i++){
        pa += lehmer[i]*fact;
        fact *= (i+1);
    }
    return pa;
}

pos_comp *pos_to_pos_comp(pos *p){
    pos_comp *p_comp = malloc(sizeof(pos_comp));
    p_comp -> oc = oc_arr_to_oc(p->oc);
    p_comp -> oa = oa_arr_to_oa(p->oa);
    p_comp -> pc = pc_arr_to_pc(p->pc);
    p_comp -> pa = pa_arr_to_pa(p->pa);
    return p_comp;
}

pos *pos_comp_to_pos(pos_comp *p_comp){
    pos *p = malloc(sizeof(pos));
    array_copy(pos_comp_to_oc_arr(p_comp), p -> oc, 8);
    array_copy(pos_comp_to_oa_arr(p_comp), p -> oa, 12);
    array_copy(pos_comp_to_pc_arr(p_comp), p -> pc, 8);
    array_copy(pos_comp_to_pa_arr(p_comp), p -> pa, 12);
    return p;
}

int corner_encoding_comp(pos_comp *p_comp){
    return 2187*(p_comp->pc) + (p_comp->oc)/3;
}

int corner_encoding(pos *p){
    return 2187*pc_arr_to_pc(p->pc) + (oc_arr_to_oc(p->oc))/3;
}

// Encodage des arêtes pour les bases de motifs de Korf.
// pa[i] (resp. oa[i]) est l'arête (resp. son orientation) présente dans l'emplacement i.
// On encode l'emplacement et l'orientation des arêtes first_edge..first_edge+5 (et non le contenu
// des emplacements 0..5) : seule cette version est compatible avec les mouvements, ce qui garantit
// que la base de motifs donne des distances exactes et donc une heuristique admissible.
int edge_pattern_encoding(int *pa, int *oa, int first_edge){
    int slot_of[12];
    for (int i = 0; i < 12; i++){
        slot_of[pa[i]] = i;
    }
    int pa_encoding = 0;
    int oa_encoding = 0;
    bool assigned[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
    for(int j = 0; j < 6; j++){
        int slot = slot_of[first_edge + j];
        int k = 0;
        for (int l = 0; l < slot; l++){
            if (!assigned[l]){
                k++;
            }
        }
        pa_encoding += (fact[12 - (j+1)]/720)*k;
        assigned[slot] = true;
        oa_encoding += oa[slot] << j;
    }
    return pa_encoding*64 + oa_encoding;
}

int edge_1_encoding_comp(pos_comp *p_comp){
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int *oa_arr = pos_comp_to_oa_arr(p_comp);
    int res = edge_pattern_encoding(pa_arr, oa_arr, 0);
    free(pa_arr);
    free(oa_arr);
    return res;
}

int edge_1_encoding(pos *p){
    return edge_pattern_encoding(p->pa, p->oa, 0);
}

int edge_2_encoding_comp(pos_comp *p_comp){
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int *oa_arr = pos_comp_to_oa_arr(p_comp);
    int res = edge_pattern_encoding(pa_arr, oa_arr, 6);
    free(pa_arr);
    free(oa_arr);
    return res;
}

int edge_2_encoding(pos *p){
    return edge_pattern_encoding(p->pa, p->oa, 6);
}

int phase_1_encoding_comp(pos_comp *p_comp){
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] = 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    return ((p_comp->oc/3)*2048 + (p_comp->oa/2))*495 + udslice;
}

int phase_1_encoding(pos *p){
    int udslice = 0;
    int oc = oc_arr_to_oc(p->oc);
    int oa = oa_arr_to_oa(p->oa);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    return ((oc/3)*2048 + (oa/2))*495 + udslice;
}

int phase_2_encoding_comp(pos_comp *p_comp){
    int other_8_edges = 0;
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int other_8_edges_arr[8];
    int udslice_arr[4];
    int l1 = 0;
    int l2 = 0;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] == 10)){
            udslice_arr[l2] = pa_arr[j];
            l2++;
        }
        else{
            other_8_edges_arr[l1] = pa_arr[j];
            l1++;
        }
    }
    int lehmer_8_edges[8];
    for (int i = 0; i < 8; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (other_8_edges_arr[j] > other_8_edges_arr[i]){
                k++;
            }
        }
        lehmer_8_edges[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 8; i++){
        other_8_edges += lehmer_8_edges[i]*facto;
        facto *= (i+1);
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    return ((other_8_edges*40320) + p_comp->pc)*24 + udslice;
}

int phase_2_encoding(pos *p){
    int other_8_edges = 0;
    int udslice = 0;
    int pc = pc_arr_to_pc(p->pc);
    int other_8_edges_arr[8];
    int udslice_arr[4];
    int l1 = 0;
    int l2 = 0;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            udslice_arr[l2] = p->pa[j];
            l2++;
        }
        else{
            other_8_edges_arr[l1] = p->pa[j];
            l1++;
        }
    }
    int lehmer_8_edges[8];
    for (int i = 0; i < 8; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (other_8_edges_arr[j] > other_8_edges_arr[i]){
                k++;
            }
        }
        lehmer_8_edges[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 8; i++){
        other_8_edges += lehmer_8_edges[i]*facto;
        facto *= (i+1);
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    return ((other_8_edges*40320) + pc)*24 + udslice;
}

int encoding_oc_and_oa_comp(pos_comp *p_comp){
    return (p_comp->oc/3)*2048 + (p_comp->oa)/2;
}

int encoding_oc_and_oa(pos *p){
    int oc = oc_arr_to_oc(p->oc);
    int oa = oa_arr_to_oa(p->oa);
    return (oc/3)*2048 + (oa/2);
}

int encoding_uds_and_oa_comp(pos_comp *p_comp){
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] = 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    free(pa_arr);
    return (p_comp->oa/2)*495 + udslice;
}

int encoding_uds_and_oa(pos *p){
    int udslice = 0;
    int oa = oa_arr_to_oa(p->oa);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    return (oa/2)*495 + udslice;
}

int encoding_uds_and_oc_comp(pos_comp *p_comp){
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] = 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    free(pa_arr);
    return (p_comp->oc/3)*495 + udslice;
}

int encoding_uds_and_oc(pos *p){
    int udslice = 0;
    int oc = oc_arr_to_oc(p->oc);
    int k = -1;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            k++;
        }
        else{
            if(k >= 0){
                udslice += (fact[j])/(fact[k]*fact[j - k]);
            }
        }
    }
    return (oc/3)*495 + udslice;
}

int encoding_8_edges_and_uds_comp(pos_comp *p_comp){
    int other_8_edges = 0;
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int other_8_edges_arr[8];
    int udslice_arr[4];
    int l1 = 0;
    int l2 = 0;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] == 10)){
            udslice_arr[l2] = pa_arr[j];
            l2++;
        }
        else{
            other_8_edges_arr[l1] = pa_arr[j];
            l1++;
        }
    }
    int lehmer_8_edges[8];
    for (int i = 0; i < 8; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (other_8_edges_arr[j] > other_8_edges_arr[i]){
                k++;
            }
        }
        lehmer_8_edges[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 8; i++){
        other_8_edges += lehmer_8_edges[i]*facto;
        facto *= (i+1);
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    free(pa_arr);
    return other_8_edges*24 + udslice;
}

int encoding_8_edges_and_uds(pos *p){
    int other_8_edges = 0;
    int udslice = 0;
    int other_8_edges_arr[8];
    int udslice_arr[4];
    int l1 = 0;
    int l2 = 0;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            udslice_arr[l2] = p->pa[j];
            l2++;
        }
        else{
            other_8_edges_arr[l1] = p->pa[j];
            l1++;
        }
    }
    int lehmer_8_edges[8];
    for (int i = 0; i < 8; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (other_8_edges_arr[j] > other_8_edges_arr[i]){
                k++;
            }
        }
        lehmer_8_edges[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 8; i++){
        other_8_edges += lehmer_8_edges[i]*facto;
        facto *= (i+1);
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    return other_8_edges*24 + udslice;
}

int encoding_pc_and_uds_comp(pos_comp *p_comp){
    int udslice = 0;
    int *pa_arr = pos_comp_to_pa_arr(p_comp);
    int udslice_arr[4];
    int l = 0;
    for(int j = 0; j < 12 ; j++){
        if((pa_arr[j] == 0)||(pa_arr[j] == 2)||(pa_arr[j] == 8)||(pa_arr[j] == 10)){
            udslice_arr[l] = pa_arr[j];
            l++;
        }
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    free(pa_arr);
    return (p_comp->pc)*24 + udslice;
}

int encoding_pc_and_uds(pos *p){
    int udslice = 0;
    int pc = pc_arr_to_pc(p->pc);
    int udslice_arr[4];
    int l = 0;
    for(int j = 0; j < 12 ; j++){
        if((p->pa[j] == 0)||(p->pa[j] == 2)||(p->pa[j] == 8)||(p->pa[j] == 10)){
            udslice_arr[l] = p->pa[j];
            l++;
        }
    }
    int lehmer_udslice[4];
    for (int i = 0; i < 4; i++){
        int k = 0;
        for (int j = 0 ; j < i; j++){
            if (udslice_arr[j] > udslice_arr[i]){
                k++;
            }
        }
        lehmer_udslice[i] = k;
    }
    int facto = 1;
    for (int i = 0; i < 4; i++){
        udslice += lehmer_udslice[i]*facto;
        facto *= (i+1);
    }
    return pc*24 + udslice;
}

int heuristique_1(pos *p, int *pdb_corner, int *pdb_edge_1, int *pdb_edge_2){
    return max(pdb_corner[corner_encoding(p)], max(pdb_edge_1[edge_1_encoding(p)], pdb_edge_2[edge_2_encoding(p)]));
}

int heuristique_1_test(pos *p){
    FILE *pdb_corners = fopen("corner_pdb.txt", "r");
    FILE *pdb_edge_1 = fopen("edge_1_pdb.txt", "r");
    FILE *pdb_edge_2 = fopen("edge_2_pdb.txt", "r");
    return max(get_ligne(pdb_corners, corner_encoding(p)), max(get_ligne(pdb_edge_1, edge_1_encoding(p)), get_ligne(pdb_edge_2, edge_2_encoding(p))));
}

int phase_1_heuristique(pos *p, int *pdb_oc_and_oa, int *pdb_oa_and_uds, int *pdb_oc_and_uds){
    return max(pdb_oc_and_oa[encoding_oc_and_oa(p)], max(pdb_oa_and_uds[encoding_uds_and_oa(p)], pdb_oc_and_uds[encoding_uds_and_oc(p)]));
}

int phase_2_heuristique(pos *p, int *pdb_8_edges_and_uds, int *pdb_pc_and_uds){
    return max(pdb_8_edges_and_uds[encoding_8_edges_and_uds(p)], pdb_pc_and_uds[encoding_pc_and_uds(p)]);
}

// Prend en entrée le tableau des orientations des coins et l'affiche. 
void print_orientations_coins (int *arr){
    printf("Tableau des orientations des coins\n");
    for (int k = 0 ; k < 8 ; k++){
        printf("arr.(%i)=%i\n", k, arr[k]);
    }
    printf("\n");
}

// Prend en entrée le tableau des orientations des arêtes et l'affiche. 
void print_orientations_aretes (int *arr){
    printf("Tableau des orientations des arêtes\n");
    for (int k = 0 ;  k < 12 ; k++){
        printf("arr.(%i)=%i\n", k, arr[k]);
    }
    printf("\n");
}

// Prend en entrée le tableau de la permutations des coins et l'affiche. 
void print_permutation_coins (int *arr){
    printf("Tableau de la permutation des coins\n");
    for (int k = 0 ; k < 8 ; k++){
        printf("arr.(%i)=%i\n", k, arr[k]);
    }
    printf("\n");
}

// Prend en entrée le tableau de la permutation des arêtes et l'affiche. 
void print_permutation_aretes (int *arr){
    printf("Tableau de la permutation des arêtes\n");
    for (int k = 0 ;  k < 12 ; k++){
        printf("arr.(%i)=%i\n", k, arr[k]);
    }
    printf("\n");
}

// Prend en entrée une position du rk et affiche les coordonnées de la position sous forme de tableaux. 
void print_cubie_level (pos *p){
    print_orientations_coins(p->oc);
    print_orientations_aretes(p->oa);
    print_permutation_coins(p->pc);
    print_permutation_aretes(p->pa);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement F. 
void f_comp(pos_comp *pi){
    // On génère les tableaux que représentent les formes compressées
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    // On crée les tableaux qui représentent la position compressée modifiée
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[f_pc[i]] + f_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[f_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[f_pa[i]] + f_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[f_pa[i]];
    }
    // On compresse ces tableaux
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement F2. 
void f2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[f2_pc[i]] + f2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[f2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[f2_pa[i]] + f2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[f2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement F3. 
void f3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[f3_pc[i]] + f3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[f3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[f3_pa[i]] + f3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[f3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement U. 
void u_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[u_pc[i]] + u_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[u_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[u_pa[i]] + u_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[u_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement U2. 
void u2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[u2_pc[i]] + u2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[u2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[u2_pa[i]] + u2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[u2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement U3. 
void u3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[u3_pc[i]] + u3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[u3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[u3_pa[i]] + u3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[u3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement L. 
void l_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[l_pc[i]] + l_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[l_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[l_pa[i]] + l_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[l_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement L2. 
void l2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[l2_pc[i]] + l2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[l2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[l2_pa[i]] + l2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[l2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement L3. 
void l3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[l3_pc[i]] + l3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[l3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[l3_pa[i]] + l3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[l3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement R. 
void r_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[r_pc[i]] + r_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[r_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[r_pa[i]] + r_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[r_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement R2. 
void r2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[r2_pc[i]] + r2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[r2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[r2_pa[i]] + r2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[r2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement R3. 
void r3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[r3_pc[i]] + r3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[r3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[r3_pa[i]] + r3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[r3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement D. 
void d_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[d_pc[i]] + d_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[d_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[d_pa[i]] + d_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[d_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement D2. 
void d2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[d2_pc[i]] + d2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[d2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[d2_pa[i]] + d2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[d2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement D3. 
void d3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[d3_pc[i]] + d3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[d3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[d3_pa[i]] + d3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[d3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement B. 
void b_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[b_pc[i]] + b_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[b_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[b_pa[i]] + b_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[b_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement B2. 
void b2_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[b2_pc[i]] + b2_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[b2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[b2_pa[i]] + b2_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[b2_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position compressée du rk, et lui applique le mouvement B3. 
void b3_comp(pos_comp *pi){
    int *arr_oc_i = pos_comp_to_oc_arr(pi);
    int *arr_oa_i = pos_comp_to_oa_arr(pi);
    int *arr_pc_i = pos_comp_to_pc_arr(pi);
    int *arr_pa_i = pos_comp_to_pa_arr(pi);
    int arr_oc_f[8];
    int arr_oa_f[12];
    int arr_pc_f[8];
    int arr_pa_f[12];
    for (int i = 0; i < 8; i++){
        arr_oc_f[i] = (arr_oc_i[b3_pc[i]] + b3_oc[i]) %3;
        arr_pc_f[i] = arr_pc_i[b3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        arr_oa_f[i] = (arr_oa_i[b3_pa[i]] + b3_oa[i]) %2;
        arr_pa_f[i] = arr_pa_i[b3_pa[i]];
    }
    pi -> oc = oc_arr_to_oc(arr_oc_f);
    pi -> oa = oa_arr_to_oa(arr_oa_f);
    pi -> pc = pc_arr_to_pc(arr_pc_f);
    pi -> pa = pa_arr_to_pa(arr_pa_f);
    free(arr_oc_i);
    free(arr_oa_i);
    free(arr_pc_i);
    free(arr_pa_i);
}

// Prend en entrée une position du rk, et lui applique le mouvement F. 
void f(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[f_pc[i]] + f_oc[i]) %3;
        pc_f[i] = pi->pc[f_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[f_pa[i]] + f_oa[i]) %2;
        pa_f[i] = pi->pa[f_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

void f_corner_test(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int pc_f[8];
    oc_f[0] = (pi->oc[f_pc[0]] + f_oc[0]) %3;
    pc_f[0] = pi->pc[f_pc[0]];
    oc_f[1] = (pi->oc[f_pc[1]] + f_oc[1]) %3;
    pc_f[1] = pi->pc[f_pc[1]];
    oc_f[2] = (pi->oc[f_pc[2]] + f_oc[2]) %3;
    pc_f[2] = pi->pc[f_pc[2]];
    oc_f[3] = (pi->oc[f_pc[3]] + f_oc[3]) %3;
    pc_f[4] = pi->pc[f_pc[4]];
    oc_f[5] = (pi->oc[f_pc[5]] + f_oc[5]) %3;
    pc_f[5] = pi->pc[f_pc[5]];
    oc_f[6] = (pi->oc[f_pc[6]] + f_oc[6]) %3;
    pc_f[6] = pi->pc[f_pc[6]];
    oc_f[7] = (pi->oc[f_pc[7]] + f_oc[7]) %3;
    pc_f[7] = pi->pc[f_pc[7]];
    
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(pc_f, pi->pc, 8);
}

void f2_corner_test(pos *pi){
    // On crée les tableaux qui représentent la position modif2iée
    int oc_f2[8];
    int pc_f2[8];
    oc_f2[0] = (pi->oc[f2_pc[0]] + f2_oc[0]) %3;
    pc_f2[0] = pi->pc[f2_pc[0]];
    oc_f2[1] = (pi->oc[f2_pc[1]] + f2_oc[1]) %3;
    pc_f2[1] = pi->pc[f2_pc[1]];
    oc_f2[2] = (pi->oc[f2_pc[2]] + f2_oc[2]) %3;
    pc_f2[2] = pi->pc[f2_pc[2]];
    oc_f2[3] = (pi->oc[f2_pc[3]] + f2_oc[3]) %3;
    pc_f2[4] = pi->pc[f2_pc[4]];
    oc_f2[5] = (pi->oc[f2_pc[5]] + f2_oc[5]) %3;
    pc_f2[5] = pi->pc[f2_pc[5]];
    oc_f2[6] = (pi->oc[f2_pc[6]] + f2_oc[6]) %3;
    pc_f2[6] = pi->pc[f2_pc[6]];
    oc_f2[7] = (pi->oc[f2_pc[7]] + f2_oc[7]) %3;
    pc_f2[7] = pi->pc[f2_pc[7]];
    
    // On copie ces tableaux
    array_copy(oc_f2, pi->oc, 8);
    array_copy(pc_f2, pi->pc, 8);
}

void f3_corner_test(pos *pi){
    // On crée les tableaux qui représentent la position modif3iée
    int oc_f3[8];
    int pc_f3[8];
    oc_f3[0] = (pi->oc[f3_pc[0]] + f3_oc[0]) %3;
    pc_f3[0] = pi->pc[f3_pc[0]];
    oc_f3[1] = (pi->oc[f3_pc[1]] + f3_oc[1]) %3;
    pc_f3[1] = pi->pc[f3_pc[1]];
    oc_f3[2] = (pi->oc[f3_pc[2]] + f3_oc[2]) %3;
    pc_f3[2] = pi->pc[f3_pc[2]];
    oc_f3[3] = (pi->oc[f3_pc[3]] + f3_oc[3]) %3;
    pc_f3[4] = pi->pc[f3_pc[4]];
    oc_f3[5] = (pi->oc[f3_pc[5]] + f3_oc[5]) %3;
    pc_f3[5] = pi->pc[f3_pc[5]];
    oc_f3[6] = (pi->oc[f3_pc[6]] + f3_oc[6]) %3;
    pc_f3[6] = pi->pc[f3_pc[6]];
    oc_f3[7] = (pi->oc[f3_pc[7]] + f3_oc[7]) %3;
    pc_f3[7] = pi->pc[f3_pc[7]];
    
    // On copie ces tableaux
    array_copy(oc_f3, pi->oc, 8);
    array_copy(pc_f3, pi->pc, 8);
}
void u_corner_test(pos *pi){
    // On crée les tableaux qui représentent la position modiuiée
    int oc_u[8];
    int pc_u[8];
    oc_u[0] = (pi->oc[u_pc[0]] + u_oc[0]) %3;
    pc_u[0] = pi->pc[u_pc[0]];
    oc_u[1] = (pi->oc[u_pc[1]] + u_oc[1]) %3;
    pc_u[1] = pi->pc[u_pc[1]];
    oc_u[2] = (pi->oc[u_pc[2]] + u_oc[2]) %3;
    pc_u[2] = pi->pc[u_pc[2]];
    oc_u[3] = (pi->oc[u_pc[3]] + u_oc[3]) %3;
    pc_u[4] = pi->pc[u_pc[4]];
    oc_u[5] = (pi->oc[u_pc[5]] + u_oc[5]) %3;
    pc_u[5] = pi->pc[u_pc[5]];
    oc_u[6] = (pi->oc[u_pc[6]] + u_oc[6]) %3;
    pc_u[6] = pi->pc[u_pc[6]];
    oc_u[7] = (pi->oc[u_pc[7]] + u_oc[7]) %3;
    pc_u[7] = pi->pc[u_pc[7]];
    
    // On copie ces tableaux
    array_copy(oc_u, pi->oc, 8);
    array_copy(pc_u, pi->pc, 8);
}
void u3_corner_test(pos *pi){
    // On crée les tableau3x qu3i représentent la position modiu3iée
    int oc_u3[8];
    int pc_u3[8];
    oc_u3[0] = (pi->oc[u3_pc[0]] + u3_oc[0]) %3;
    pc_u3[0] = pi->pc[u3_pc[0]];
    oc_u3[1] = (pi->oc[u3_pc[1]] + u3_oc[1]) %3;
    pc_u3[1] = pi->pc[u3_pc[1]];
    oc_u3[2] = (pi->oc[u3_pc[2]] + u3_oc[2]) %3;
    pc_u3[2] = pi->pc[u3_pc[2]];
    oc_u3[3] = (pi->oc[u3_pc[3]] + u3_oc[3]) %3;
    pc_u3[4] = pi->pc[u3_pc[4]];
    oc_u3[5] = (pi->oc[u3_pc[5]] + u3_oc[5]) %3;
    pc_u3[5] = pi->pc[u3_pc[5]];
    oc_u3[6] = (pi->oc[u3_pc[6]] + u3_oc[6]) %3;
    pc_u3[6] = pi->pc[u3_pc[6]];
    oc_u3[7] = (pi->oc[u3_pc[7]] + u3_oc[7]) %3;
    pc_u3[7] = pi->pc[u3_pc[7]];
    
    // On copie ces tableau3x
    array_copy(oc_u3, pi->oc, 8);
    array_copy(pc_u3, pi->pc, 8);
}
void l_corner_test(pos *pi){
    // On crée les tablealx qli représentent la position modiliée
    int oc_l[8];
    int pc_l[8];
    oc_l[0] = (pi->oc[l_pc[0]] + l_oc[0]) %3;
    pc_l[0] = pi->pc[l_pc[0]];
    oc_l[1] = (pi->oc[l_pc[1]] + l_oc[1]) %3;
    pc_l[1] = pi->pc[l_pc[1]];
    oc_l[2] = (pi->oc[l_pc[2]] + l_oc[2]) %3;
    pc_l[2] = pi->pc[l_pc[2]];
    oc_l[3] = (pi->oc[l_pc[3]] + l_oc[3]) %3;
    pc_l[4] = pi->pc[l_pc[4]];
    oc_l[5] = (pi->oc[l_pc[5]] + l_oc[5]) %3;
    pc_l[5] = pi->pc[l_pc[5]];
    oc_l[6] = (pi->oc[l_pc[6]] + l_oc[6]) %3;
    pc_l[6] = pi->pc[l_pc[6]];
    oc_l[7] = (pi->oc[l_pc[7]] + l_oc[7]) %3;
    pc_l[7] = pi->pc[l_pc[7]];
    
    // On copie ces tablealx
    array_copy(oc_l, pi->oc, 8);
    array_copy(pc_l, pi->pc, 8);
}
void l2_corner_test(pos *pi){
    // On crée l2es tabl2eal2x ql2i représentent l2a position modil2iée
    int oc_l2[8];
    int pc_l2[8];
    oc_l2[0] = (pi->oc[l2_pc[0]] + l2_oc[0]) %3;
    pc_l2[0] = pi->pc[l2_pc[0]];
    oc_l2[1] = (pi->oc[l2_pc[1]] + l2_oc[1]) %3;
    pc_l2[1] = pi->pc[l2_pc[1]];
    oc_l2[2] = (pi->oc[l2_pc[2]] + l2_oc[2]) %3;
    pc_l2[2] = pi->pc[l2_pc[2]];
    oc_l2[3] = (pi->oc[l2_pc[3]] + l2_oc[3]) %3;
    pc_l2[4] = pi->pc[l2_pc[4]];
    oc_l2[5] = (pi->oc[l2_pc[5]] + l2_oc[5]) %3;
    pc_l2[5] = pi->pc[l2_pc[5]];
    oc_l2[6] = (pi->oc[l2_pc[6]] + l2_oc[6]) %3;
    pc_l2[6] = pi->pc[l2_pc[6]];
    oc_l2[7] = (pi->oc[l2_pc[7]] + l2_oc[7]) %3;
    pc_l2[7] = pi->pc[l2_pc[7]];
    
    // On copie ces tabl2eal2x
    array_copy(oc_l2, pi->oc, 8);
    array_copy(pc_l2, pi->pc, 8);
}
void l3_corner_test(pos *pi){
    // On crée l3es tabl3eal3x ql3i représentent l3a position modil3iée
    int oc_l3[8];
    int pc_l3[8];
    oc_l3[0] = (pi->oc[l3_pc[0]] + l3_oc[0]) %3;
    pc_l3[0] = pi->pc[l3_pc[0]];
    oc_l3[1] = (pi->oc[l3_pc[1]] + l3_oc[1]) %3;
    pc_l3[1] = pi->pc[l3_pc[1]];
    oc_l3[2] = (pi->oc[l3_pc[2]] + l3_oc[2]) %3;
    pc_l3[2] = pi->pc[l3_pc[2]];
    oc_l3[3] = (pi->oc[l3_pc[3]] + l3_oc[3]) %3;
    pc_l3[4] = pi->pc[l3_pc[4]];
    oc_l3[5] = (pi->oc[l3_pc[5]] + l3_oc[5]) %3;
    pc_l3[5] = pi->pc[l3_pc[5]];
    oc_l3[6] = (pi->oc[l3_pc[6]] + l3_oc[6]) %3;
    pc_l3[6] = pi->pc[l3_pc[6]];
    oc_l3[7] = (pi->oc[l3_pc[7]] + l3_oc[7]) %3;
    pc_l3[7] = pi->pc[l3_pc[7]];
    
    // On copie ces tabl3eal3x
    array_copy(oc_l3, pi->oc, 8);
    array_copy(pc_l3, pi->pc, 8);
}

void b_corner_test(pos *pi){
    // On crée bes tabbeabx qbi représentent ba position modibiée
    int oc_b[8];
    int pc_b[8];
    oc_b[0] = (pi->oc[b_pc[0]] + b_oc[0]) %3;
    pc_b[0] = pi->pc[b_pc[0]];
    oc_b[1] = (pi->oc[b_pc[1]] + b_oc[1]) %3;
    pc_b[1] = pi->pc[b_pc[1]];
    oc_b[2] = (pi->oc[b_pc[2]] + b_oc[2]) %3;
    pc_b[2] = pi->pc[b_pc[2]];
    oc_b[3] = (pi->oc[b_pc[3]] + b_oc[3]) %3;
    pc_b[4] = pi->pc[b_pc[4]];
    oc_b[5] = (pi->oc[b_pc[5]] + b_oc[5]) %3;
    pc_b[5] = pi->pc[b_pc[5]];
    oc_b[6] = (pi->oc[b_pc[6]] + b_oc[6]) %3;
    pc_b[6] = pi->pc[b_pc[6]];
    oc_b[7] = (pi->oc[b_pc[7]] + b_oc[7]) %3;
    pc_b[7] = pi->pc[b_pc[7]];
    
    // On copie ces tabbeabx
    array_copy(oc_b, pi->oc, 8);
    array_copy(pc_b, pi->pc, 8);
}
void b2_corner_test(pos *pi){
    // On crée b2es tab2b2eab2x qb2i représentent b2a position modib2iée
    int oc_b2[8];
    int pc_b2[8];
    oc_b2[0] = (pi->oc[b2_pc[0]] + b2_oc[0]) %3;
    pc_b2[0] = pi->pc[b2_pc[0]];
    oc_b2[1] = (pi->oc[b2_pc[1]] + b2_oc[1]) %3;
    pc_b2[1] = pi->pc[b2_pc[1]];
    oc_b2[2] = (pi->oc[b2_pc[2]] + b2_oc[2]) %3;
    pc_b2[2] = pi->pc[b2_pc[2]];
    oc_b2[3] = (pi->oc[b2_pc[3]] + b2_oc[3]) %3;
    pc_b2[4] = pi->pc[b2_pc[4]];
    oc_b2[5] = (pi->oc[b2_pc[5]] + b2_oc[5]) %3;
    pc_b2[5] = pi->pc[b2_pc[5]];
    oc_b2[6] = (pi->oc[b2_pc[6]] + b2_oc[6]) %3;
    pc_b2[6] = pi->pc[b2_pc[6]];
    oc_b2[7] = (pi->oc[b2_pc[7]] + b2_oc[7]) %3;
    pc_b2[7] = pi->pc[b2_pc[7]];
    
    // On copie ces tab2b2eab2x
    array_copy(oc_b2, pi->oc, 8);
    array_copy(pc_b2, pi->pc, 8);
}
void b3_corner_test(pos *pi){
    // On crée b3es tab3b3eab3x qb3i représentent b3a position modib3iée
    int oc_b3[8];
    int pc_b3[8];
    oc_b3[0] = (pi->oc[b3_pc[0]] + b3_oc[0]) %3;
    pc_b3[0] = pi->pc[b3_pc[0]];
    oc_b3[1] = (pi->oc[b3_pc[1]] + b3_oc[1]) %3;
    pc_b3[1] = pi->pc[b3_pc[1]];
    oc_b3[2] = (pi->oc[b3_pc[2]] + b3_oc[2]) %3;
    pc_b3[2] = pi->pc[b3_pc[2]];
    oc_b3[3] = (pi->oc[b3_pc[3]] + b3_oc[3]) %3;
    pc_b3[4] = pi->pc[b3_pc[4]];
    oc_b3[5] = (pi->oc[b3_pc[5]] + b3_oc[5]) %3;
    pc_b3[5] = pi->pc[b3_pc[5]];
    oc_b3[6] = (pi->oc[b3_pc[6]] + b3_oc[6]) %3;
    pc_b3[6] = pi->pc[b3_pc[6]];
    oc_b3[7] = (pi->oc[b3_pc[7]] + b3_oc[7]) %3;
    pc_b3[7] = pi->pc[b3_pc[7]];
    
    // On copie ces tab3b3eab3x
    array_copy(oc_b3, pi->oc, 8);
    array_copy(pc_b3, pi->pc, 8);
}

void r_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position modiriée
    int oc_r[8];
    int pc_r[8];
    oc_r[0] = (pi->oc[r_pc[0]] + r_oc[0]) %3;
    pc_r[0] = pi->pc[r_pc[0]];
    oc_r[1] = (pi->oc[r_pc[1]] + r_oc[1]) %3;
    pc_r[1] = pi->pc[r_pc[1]];
    oc_r[2] = (pi->oc[r_pc[2]] + r_oc[2]) %3;
    pc_r[2] = pi->pc[r_pc[2]];
    oc_r[3] = (pi->oc[r_pc[3]] + r_oc[3]) %3;
    pc_r[4] = pi->pc[r_pc[4]];
    oc_r[5] = (pi->oc[r_pc[5]] + r_oc[5]) %3;
    pc_r[5] = pi->pc[r_pc[5]];
    oc_r[6] = (pi->oc[r_pc[6]] + r_oc[6]) %3;
    pc_r[6] = pi->pc[r_pc[6]];
    oc_r[7] = (pi->oc[r_pc[7]] + r_oc[7]) %3;
    pc_r[7] = pi->pc[r_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_r, pi->oc, 8);
    array_copy(pc_r, pi->pc, 8);
}

void r2_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position modiriée
    int oc_r2[8];
    int pc_r2[8];
    oc_r2[0] = (pi->oc[r2_pc[0]] + r2_oc[0]) %3;
    pc_r2[0] = pi->pc[r2_pc[0]];
    oc_r2[1] = (pi->oc[r2_pc[1]] + r2_oc[1]) %3;
    pc_r2[1] = pi->pc[r2_pc[1]];
    oc_r2[2] = (pi->oc[r2_pc[2]] + r2_oc[2]) %3;
    pc_r2[2] = pi->pc[r2_pc[2]];
    oc_r2[3] = (pi->oc[r2_pc[3]] + r2_oc[3]) %3;
    pc_r2[4] = pi->pc[r2_pc[4]];
    oc_r2[5] = (pi->oc[r2_pc[5]] + r2_oc[5]) %3;
    pc_r2[5] = pi->pc[r2_pc[5]];
    oc_r2[6] = (pi->oc[r2_pc[6]] + r2_oc[6]) %3;
    pc_r2[6] = pi->pc[r2_pc[6]];
    oc_r2[7] = (pi->oc[r2_pc[7]] + r2_oc[7]) %3;
    pc_r2[7] = pi->pc[r2_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_r2, pi->oc, 8);
    array_copy(pc_r2, pi->pc, 8);
}

void r3_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position modiriée
    int oc_r3[8];
    int pc_r3[8];
    oc_r3[0] = (pi->oc[r3_pc[0]] + r3_oc[0]) %3;
    pc_r3[0] = pi->pc[r3_pc[0]];
    oc_r3[1] = (pi->oc[r3_pc[1]] + r3_oc[1]) %3;
    pc_r3[1] = pi->pc[r3_pc[1]];
    oc_r3[2] = (pi->oc[r3_pc[2]] + r3_oc[2]) %3;
    pc_r3[2] = pi->pc[r3_pc[2]];
    oc_r3[3] = (pi->oc[r3_pc[3]] + r3_oc[3]) %3;
    pc_r3[4] = pi->pc[r3_pc[4]];
    oc_r3[5] = (pi->oc[r3_pc[5]] + r3_oc[5]) %3;
    pc_r3[5] = pi->pc[r3_pc[5]];
    oc_r3[6] = (pi->oc[r3_pc[6]] + r3_oc[6]) %3;
    pc_r3[6] = pi->pc[r3_pc[6]];
    oc_r3[7] = (pi->oc[r3_pc[7]] + r3_oc[7]) %3;
    pc_r3[7] = pi->pc[r3_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_r3, pi->oc, 8);
    array_copy(pc_r3, pi->pc, 8);
}
void d_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position modiriée
    int oc_d[8];
    int pc_d[8];
    oc_d[0] = (pi->oc[d_pc[0]] + d_oc[0]) %3;
    pc_d[0] = pi->pc[d_pc[0]];
    oc_d[1] = (pi->oc[d_pc[1]] + d_oc[1]) %3;
    pc_d[1] = pi->pc[d_pc[1]];
    oc_d[2] = (pi->oc[d_pc[2]] + d_oc[2]) %3;
    pc_d[2] = pi->pc[d_pc[2]];
    oc_d[3] = (pi->oc[d_pc[3]] + d_oc[3]) %3;
    pc_d[4] = pi->pc[d_pc[4]];
    oc_d[5] = (pi->oc[d_pc[5]] + d_oc[5]) %3;
    pc_d[5] = pi->pc[d_pc[5]];
    oc_d[6] = (pi->oc[d_pc[6]] + d_oc[6]) %3;
    pc_d[6] = pi->pc[d_pc[6]];
    oc_d[7] = (pi->oc[d_pc[7]] + d_oc[7]) %3;
    pc_d[7] = pi->pc[d_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_d, pi->oc, 8);
    array_copy(pc_d, pi->pc, 8);
}

void d2_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position mod2iriée
    int oc_d2[8];
    int pc_d2[8];
    oc_d2[0] = (pi->oc[d2_pc[0]] + d2_oc[0]) %3;
    pc_d2[0] = pi->pc[d2_pc[0]];
    oc_d2[1] = (pi->oc[d2_pc[1]] + d2_oc[1]) %3;
    pc_d2[1] = pi->pc[d2_pc[1]];
    oc_d2[2] = (pi->oc[d2_pc[2]] + d2_oc[2]) %3;
    pc_d2[2] = pi->pc[d2_pc[2]];
    oc_d2[3] = (pi->oc[d2_pc[3]] + d2_oc[3]) %3;
    pc_d2[4] = pi->pc[d2_pc[4]];
    oc_d2[5] = (pi->oc[d2_pc[5]] + d2_oc[5]) %3;
    pc_d2[5] = pi->pc[d2_pc[5]];
    oc_d2[6] = (pi->oc[d2_pc[6]] + d2_oc[6]) %3;
    pc_d2[6] = pi->pc[d2_pc[6]];
    oc_d2[7] = (pi->oc[d2_pc[7]] + d2_oc[7]) %3;
    pc_d2[7] = pi->pc[d2_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_d2, pi->oc, 8);
    array_copy(pc_d2, pi->pc, 8);
}

void d3_corner_test(pos *pi){
    // On crée res tarrearx qri représentent ra position mod3iriée
    int oc_d3[8];
    int pc_d3[8];
    oc_d3[0] = (pi->oc[d3_pc[0]] + d3_oc[0]) %3;
    pc_d3[0] = pi->pc[d3_pc[0]];
    oc_d3[1] = (pi->oc[d3_pc[1]] + d3_oc[1]) %3;
    pc_d3[1] = pi->pc[d3_pc[1]];
    oc_d3[2] = (pi->oc[d3_pc[2]] + d3_oc[2]) %3;
    pc_d3[2] = pi->pc[d3_pc[2]];
    oc_d3[3] = (pi->oc[d3_pc[3]] + d3_oc[3]) %3;
    pc_d3[4] = pi->pc[d3_pc[4]];
    oc_d3[5] = (pi->oc[d3_pc[5]] + d3_oc[5]) %3;
    pc_d3[5] = pi->pc[d3_pc[5]];
    oc_d3[6] = (pi->oc[d3_pc[6]] + d3_oc[6]) %3;
    pc_d3[6] = pi->pc[d3_pc[6]];
    oc_d3[7] = (pi->oc[d3_pc[7]] + d3_oc[7]) %3;
    pc_d3[7] = pi->pc[d3_pc[7]];
    
    // On copie ces tarrearx
    array_copy(oc_d3, pi->oc, 8);
    array_copy(pc_d3, pi->pc, 8);
}

void u2_corner_test(pos *pi){
    // On crée les tableaux qui représentent la position modiu2iée
    int oc_u2[8];
    int pc_u2[8];
    oc_u2[0] = (pi->oc[u2_pc[0]] + u2_oc[0]) %3;
    pc_u2[0] = pi->pc[u2_pc[0]];
    oc_u2[1] = (pi->oc[u2_pc[1]] + u2_oc[1]) %3;
    pc_u2[1] = pi->pc[u2_pc[1]];
    oc_u2[2] = (pi->oc[u2_pc[2]] + u2_oc[2]) %3;
    pc_u2[2] = pi->pc[u2_pc[2]];
    oc_u2[3] = (pi->oc[u2_pc[3]] + u2_oc[3]) %3;
    pc_u2[4] = pi->pc[u2_pc[4]];
    oc_u2[5] = (pi->oc[u2_pc[5]] + u2_oc[5]) %3;
    pc_u2[5] = pi->pc[u2_pc[5]];
    oc_u2[6] = (pi->oc[u2_pc[6]] + u2_oc[6]) %3;
    pc_u2[6] = pi->pc[u2_pc[6]];
    oc_u2[7] = (pi->oc[u2_pc[7]] + u2_oc[7]) %3;
    pc_u2[7] = pi->pc[u2_pc[7]];
    
    // On copie ces tableaux
    array_copy(oc_u2, pi->oc, 8);
    array_copy(pc_u2, pi->pc, 8);
}




// Prend en entrée une position du rk, et lui applique le mouvement F2. 
void f2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[f2_pc[i]] + f2_oc[i]) %3;
        pc_f[i] = pi->pc[f2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[f2_pa[i]] + f2_oa[i]) %2;
        pa_f[i] = pi->pa[f2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement F3. 
void f3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[f3_pc[i]] + f3_oc[i]) %3;
        pc_f[i] = pi->pc[f3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[f3_pa[i]] + f3_oa[i]) %2;
        pa_f[i] = pi->pa[f3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement U. 
void u(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[u_pc[i]] + u_oc[i]) %3;
        pc_f[i] = pi->pc[u_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[u_pa[i]] + u_oa[i]) %2;
        pa_f[i] = pi->pa[u_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement U2. 
void u2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[u2_pc[i]] + u2_oc[i]) %3;
        pc_f[i] = pi->pc[u2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[u2_pa[i]] + u2_oa[i]) %2;
        pa_f[i] = pi->pa[u2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement U3. 
void u3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[u3_pc[i]] + u3_oc[i]) %3;
        pc_f[i] = pi->pc[u3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[u3_pa[i]] + u3_oa[i]) %2;
        pa_f[i] = pi->pa[u3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement L. 
void l(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[l_pc[i]] + l_oc[i]) %3;
        pc_f[i] = pi->pc[l_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[l_pa[i]] + l_oa[i]) %2;
        pa_f[i] = pi->pa[l_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement L2. 
void l2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[l2_pc[i]] + l2_oc[i]) %3;
        pc_f[i] = pi->pc[l2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[l2_pa[i]] + l2_oa[i]) %2;
        pa_f[i] = pi->pa[l2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement l3. 
void l3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[l3_pc[i]] + l3_oc[i]) %3;
        pc_f[i] = pi->pc[l3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[l3_pa[i]] + l3_oa[i]) %2;
        pa_f[i] = pi->pa[l3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement R. 
void r(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[r_pc[i]] + r_oc[i]) %3;
        pc_f[i] = pi->pc[r_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[r_pa[i]] + r_oa[i]) %2;
        pa_f[i] = pi->pa[r_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement R2. 
void r2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[r2_pc[i]] + r2_oc[i]) %3;
        pc_f[i] = pi->pc[r2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[r2_pa[i]] + r2_oa[i]) %2;
        pa_f[i] = pi->pa[r2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement R3. 
void r3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[r3_pc[i]] + r3_oc[i]) %3;
        pc_f[i] = pi->pc[r3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[r3_pa[i]] + r3_oa[i]) %2;
        pa_f[i] = pi->pa[r3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement D. 
void d(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[d_pc[i]] + d_oc[i]) %3;
        pc_f[i] = pi->pc[d_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[d_pa[i]] + d_oa[i]) %2;
        pa_f[i] = pi->pa[d_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement D2. 
void d2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[d2_pc[i]] + d2_oc[i]) %3;
        pc_f[i] = pi->pc[d2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[d2_pa[i]] + d2_oa[i]) %2;
        pa_f[i] = pi->pa[d2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement D3. 
void d3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[d3_pc[i]] + d3_oc[i]) %3;
        pc_f[i] = pi->pc[d3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[d3_pa[i]] + d3_oa[i]) %2;
        pa_f[i] = pi->pa[d3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement B. 
void b(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[b_pc[i]] + b_oc[i]) %3;
        pc_f[i] = pi->pc[b_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[b_pa[i]] + b_oa[i]) %2;
        pa_f[i] = pi->pa[b_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement B2. 
void b2(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[b2_pc[i]] + b2_oc[i]) %3;
        pc_f[i] = pi->pc[b2_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[b2_pa[i]] + b2_oa[i]) %2;
        pa_f[i] = pi->pa[b2_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend en entrée une position du rk, et lui applique le mouvement B3. 
void b3(pos *pi){
    // On crée les tableaux qui représentent la position modifiée
    int oc_f[8];
    int oa_f[12];
    int pc_f[8];
    int pa_f[12];
    for (int i = 0; i < 8; i++){
        oc_f[i] = (pi->oc[b3_pc[i]] + b3_oc[i]) %3;
        pc_f[i] = pi->pc[b3_pc[i]];
    }
    for (int i = 0; i < 12; i++){
        oa_f[i] = (pi->oa[b3_pa[i]] + b3_oa[i]) %2;
        pa_f[i] = pi->pa[b3_pa[i]];
    }
    // On copie ces tableaux
    array_copy(oc_f, pi->oc, 8);
    array_copy(oa_f, pi->oa, 12);
    array_copy(pc_f, pi->pc, 8);
    array_copy(pa_f, pi->pa, 12);
}

// Prend une position compressée du rk et lui applique le mouvement k (modifie en place). 
void void_univ_move_comp(pos_comp *p, int k){
    switch (k){
        case 0: f_comp(p); break;
        case 1: f2_comp(p); break;
        case 2: f3_comp(p); break;
        case 3: u_comp(p); break;
        case 4: u2_comp(p); break;
        case 5: u3_comp(p); break;
        case 6: l_comp(p); break;
        case 7: l2_comp(p); break;
        case 8: l3_comp(p); break;
        case 9: r_comp(p); break;
        case 10: r2_comp(p); break;
        case 11: r3_comp(p); break;
        case 12: d_comp(p); break;
        case 13: d2_comp(p); break;
        case 14: d3_comp(p); break;
        case 15: b_comp(p); break;
        case 16: b2_comp(p); break;
        case 17: b3_comp(p); break;
    }
}

// Prend une position du rk et lui applique le mouvement k (modifie en place). 
void void_univ_move(pos *p, int k){
    switch (k){
        case 0: f(p); break;
        case 1: f2(p); break;
        case 2: f3(p); break;
        case 3: u(p); break;
        case 4: u2(p); break;
        case 5: u3(p); break;
        case 6: l(p); break;
        case 7: l2(p); break;
        case 8: l3(p); break;
        case 9: r(p); break;
        case 10: r2(p); break;
        case 11: r3(p); break;
        case 12: d(p); break;
        case 13: d2(p); break;
        case 14: d3(p); break;
        case 15: b(p); break;
        case 16: b2(p); break;
        case 17: b3(p); break;
    }
}

// Prend une position compressée du rk et lui applique n mouvements aléatoires. 
int *shuffle_comp(pos_comp *p, int n){
    int *moves = malloc(sizeof(int)*n);
    for (int i = 0; i < n ; i++){
        int k = rand() % 18;
        moves[i] = k;
        void_univ_move_comp(p, k);
    }
    return moves;
}

// Prend une position compressée du rk et lui applique n mouvements aléatoires. 
int *shuffle(pos *p, int n){
    int *moves = malloc(sizeof(int)*n);
    for (int i = 0; i < n ; i++){
        int k = rand() % 18;
        moves[i] = k;
        void_univ_move(p, k);
    }
    return moves;
}

void apply_shuffle(pos *p, int *moves, int n){
    for(int k = 0; k < n ; k++){
        void_univ_move(p, moves[k]);
    }
}

// Prend une position compressée du rk et lui applique le mouvement k (renvoie une nouvelle structure). 
pos_comp *pos_comp_univ_move(pos_comp *p, int k){
    pos_comp *new_pos_comp = malloc(sizeof(pos_comp));
    *new_pos_comp = *p;
    switch (k){
        case 0: f_comp(new_pos_comp); break;
        case 1: f2_comp(new_pos_comp); break;
        case 2: f3_comp(new_pos_comp); break;
        case 3: u_comp(new_pos_comp); break;
        case 4: u2_comp(new_pos_comp); break;
        case 5: u3_comp(new_pos_comp); break;
        case 6: l_comp(new_pos_comp); break;
        case 7: l2_comp(new_pos_comp); break;
        case 8: l3_comp(new_pos_comp); break;
        case 9: r_comp(new_pos_comp); break;
        case 10: r2_comp(new_pos_comp); break;
        case 11: r3_comp(new_pos_comp); break;
        case 12: d_comp(new_pos_comp); break;
        case 13: d2_comp(new_pos_comp); break;
        case 14: d3_comp(new_pos_comp); break;
        case 15: b_comp(new_pos_comp); break;
        case 16: b2_comp(new_pos_comp); break;
        case 17: b3_comp(new_pos_comp); break;
    }
    return new_pos_comp;
}

// Prend une position du rk et lui applique le mouvement k (renvoie une nouvelle structure). 
pos *pos_univ_move(pos *p, int k){
    pos *new_pos = malloc(sizeof(pos));
    *new_pos = *p;
    switch (k){
        case 0: f(new_pos); break;
        case 1: f2(new_pos); break;
        case 2: f3(new_pos); break;
        case 3: u(new_pos); break;
        case 4: u2(new_pos); break;
        case 5: u3(new_pos); break;
        case 6: l(new_pos); break;
        case 7: l2(new_pos); break;
        case 8: l3(new_pos); break;
        case 9: r(new_pos); break;
        case 10: r2(new_pos); break;
        case 11: r3(new_pos); break;
        case 12: d(new_pos); break;
        case 13: d2(new_pos); break;
        case 14: d3(new_pos); break;
        case 15: b(new_pos); break;
        case 16: b2(new_pos); break;
        case 17: b3(new_pos); break;
    }
    return new_pos;
}
// Prend une position du rk et lui applique le mouvement k (renvoie une nouvelle structure). 
pos *pos_univ_move_corner(pos *p, int k){
    pos *new_pos = malloc(sizeof(pos));
    *new_pos = *p;
    switch (k){
        case 0: f_corner_test(new_pos); break;
        case 1: f2_corner_test(new_pos); break;
        case 2: f3_corner_test(new_pos); break;
        case 3: u_corner_test(new_pos); break;
        case 4: u2_corner_test(new_pos); break;
        case 5: u3_corner_test(new_pos); break;
        case 6: l_corner_test(new_pos); break;
        case 7: l2_corner_test(new_pos); break;
        case 8: l3_corner_test(new_pos); break;
        case 9: r_corner_test(new_pos); break;
        case 10: r2_corner_test(new_pos); break;
        case 11: r3_corner_test(new_pos); break;
        case 12: d_corner_test(new_pos); break;
        case 13: d2_corner_test(new_pos); break;
        case 14: d3_corner_test(new_pos); break;
        case 15: b_corner_test(new_pos); break;
        case 16: b2_corner_test(new_pos); break;
        case 17: b3_corner_test(new_pos); break;
    }
    return new_pos;
}

// Prend en entrée une position du rk où seule la position des coins et des orientations nous importe et trouve en combien de mouvements elle est résoluble par l'algorithme IDDFS. 
int solve_corners_comp(pos_comp *p){
    pos_comp_and_depth *pile = malloc(sizeof(pos_comp_and_depth)*198);
    for (int i = 0 ; i <= 6; i++){
        pile[0].p = malloc(sizeof(pos_comp));
        *pile[0].p = *p;
        pile[0].depth = 0;
        int occupied = 1;
        while(occupied > 0){
            occupied--;
            pos_comp *current_pos_comp = malloc(sizeof(pos_comp));
            *current_pos_comp = *pile[occupied].p;
            int d = pile[occupied].depth;
            free(pile[occupied].p);
            if ((current_pos_comp -> pc == 0)&&(current_pos_comp -> oc == 0)){
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos_comp);
                free(pile);
                return i;
            }
            if (d < i){
                for (int j = 0; j < 18; j++){
                    pile[occupied + j].p = pos_comp_univ_move(current_pos_comp, j);
                    pile[occupied + j].depth = d + 1;
                }
                occupied += 18;
            }
            free(current_pos_comp);
        }
    }
    free(pile);
    return -1;
}

// !!! ne marche pas
// Prend en entrée une position du rk où seule la position des coins et des orientations nous importe et trouve en combien de mouvements elle est résoluble par l'algorithme IDDFS. 
int solve_corners(pos *p){
    pos_and_depth *pile = malloc(sizeof(pos_and_depth)*198);
    int oc_ref[8];
    int pc_ref[8];
    for (int j = 0; j < 8 ; j++){
        oc_ref[j] = 0;
        pc_ref[j] = j;
    }
    for (int i = 0 ; i <= 5; i++){
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        int occupied = 1;
        while(occupied > 0){
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int d = pile[occupied].depth;
            free(pile[occupied].p);
            if ((arr_equal(current_pos -> pc, pc_ref, 8))&&(arr_equal(current_pos -> oc, oc_ref, 8))){
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos);
                free(pile);
                return i;
            }
            if (d < i){
                for (int j = 0; j < 18; j++){
                    pile[occupied + j].p = pos_univ_move(current_pos, j);
                    pile[occupied + j].depth = d + 1;
                }
                occupied += 18;
            }
            free(current_pos);
        }
    }
    free(pile);
    return -1;
}

// !!! ne marche pas
// Prend en entrée une position du rk où seule la position des coins et des orientations nous importe et trouve en combien de mouvements elle est résoluble par l'algorithme IDDFS. 
int solve_corners_test(pos *p){
    pos_and_depth *pile = malloc(sizeof(pos_and_depth)*198);
    int oc_ref[8];
    int pc_ref[8];
    for (int j = 0; j < 8 ; j++){
        oc_ref[j] = 0;
        pc_ref[j] = j;
    }
    for (int i = 0 ; i <= 6; i++){
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        int occupied = 1;
        while(occupied > 0){
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int d = pile[occupied].depth;
            free(pile[occupied].p);
            if ((arr_equal(current_pos -> pc, pc_ref, 8))&&(arr_equal(current_pos -> oc, oc_ref, 8))){
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos);
                free(pile);
                return i;
            }
            if (d < i){
                for (int j = 0; j < 18; j++){
                    pile[occupied + j].p = pos_univ_move_corner(current_pos, j);
                    pile[occupied + j].depth = d + 1;
                }
                occupied += 18;
            }
            free(current_pos);
        }
    }
    free(pile);
    return -1;
}

int *korf_1d1(pos *p, int *length, int *pdb_corner, int *pdb_edge_1, int *pdb_edge_2){
    // clock_t t;
    // t = clock();
    pos_and_depth_and_moves *pile = malloc(sizeof(pos_and_depth_and_moves)*360);
    // t = clock() - t;
    // double time_taken = (((double)t)/CLOCKS_PER_SEC);
    // printf("Chargement des bases de donnees : %f s\n", time_taken);
    // t = clock();
    int oc_ref[8];
    int pc_ref[8];
    int oa_ref[12];
    int pa_ref[12];
    for(int i = 0; i < 8; i++){
        oc_ref[i] = 0;
        pc_ref[i] = i;
    }
    for(int i = 0; i < 12; i++){
        oa_ref[i] = 0;
        pa_ref[i] = i;
    }
    int init_moves[20];
    for (int i = 0; i < 20; i++){
        init_moves[i] = -1;
    }
    // t = clock() - t;
    // time_taken = (((double)t)/CLOCKS_PER_SEC);
    // printf("Initialisation des tableaux : %f s\n", time_taken);
    // t = clock ();
    // int iterations = 0;
    for(int d_max = heuristique_1(p, pdb_corner, pdb_edge_1, pdb_edge_2); d_max <= 20; d_max++){
        // t = clock() - t;
        // time_taken = (((double)t)/CLOCKS_PER_SEC);
        // printf("Initialisation de la boucle : %f s\n", time_taken);
        // iterations++;
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        array_copy(init_moves, pile[0].moves, 20);
        int occupied = 1;
        // int iterations2 = 0;
        while(occupied > 0){
            // iterations2++;
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int current_depth = pile[occupied].depth;
            int *moves = malloc(sizeof(int)*20);
            array_copy(pile[occupied].moves, moves, 20);
            free(pile[occupied].p);
            if((arr_equal(current_pos->oc, oc_ref, 8))&&(arr_equal(current_pos->pc, pc_ref, 8))&&(arr_equal(current_pos->oa, oa_ref, 12))&&(arr_equal(current_pos->pa, pa_ref, 12))){
                *length = current_depth;
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos);
                free(pile);
                // printf("Iterations : %d\n", iterations);
                // printf("Iterations2 : %d\n", iterations2);
                return moves;
            }
            if(current_depth < d_max){
                for(int k = 0; k < 18; k++){
                    pos *exp_pos = pos_univ_move(current_pos, k);
                    if (current_depth + 1 + heuristique_1(exp_pos, pdb_corner, pdb_edge_1, pdb_edge_2) <= d_max){
                        pile[occupied].p = exp_pos;
                        pile[occupied].depth = current_depth + 1;
                        array_copy(moves, pile[occupied].moves, 20);
                        pile[occupied].moves[current_depth] = k;
                        occupied++;
                    }
                    else{
                        free(exp_pos);
                    }
                }
            }
            free(moves);
            free(current_pos); 
        }
    }
    free(pile);
    *length = -1;
    // printf("Iterations : %d\n", iterations);
    return NULL;
}

int *korf_1d2(pos *p, int *length, int *pdb_corner, int *pdb_edge_1, int *pdb_edge_2){
    // clock_t t;
    // t = clock();
    pos_and_depth_and_moves *pile = malloc(sizeof(pos_and_depth_and_moves)*360);
    // t = clock() - t;
    // double time_taken = (((double)t)/CLOCKS_PER_SEC);
    // printf("Chargement des bases de donnees : %f s\n", time_taken);
    // t = clock();
    int oc_ref[8];
    int pc_ref[8];
    int oa_ref[12];
    int pa_ref[12];
    for(int i = 0; i < 8; i++){
        oc_ref[i] = 0;
        pc_ref[i] = i;
    }
    for(int i = 0; i < 12; i++){
        oa_ref[i] = 0;
        pa_ref[i] = i;
    }
    int init_moves[20];
    for (int i = 0; i < 20; i++){
        init_moves[i] = -1;
    }
    // t = clock() - t;
    // time_taken = (((double)t)/CLOCKS_PER_SEC);
    // printf("Initialisation des tableaux : %f s\n", time_taken);
    // t = clock ();
    // int iterations = 0;
    for(int d_max = heuristique_1(p, pdb_corner, pdb_edge_1, pdb_edge_2); d_max <= 20; d_max++){
        // t = clock() - t;
        // time_taken = (((double)t)/CLOCKS_PER_SEC);
        // printf("Initialisation de la boucle : %f s\n", time_taken);
        // iterations++;
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        array_copy(init_moves, pile[0].moves, 20);
        int occupied = 1;
        // int iterations2 = 0;
        while(occupied > 0){
            // iterations2++;
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int current_depth = pile[occupied].depth;
            int *moves = malloc(sizeof(int)*20);
            array_copy(pile[occupied].moves, moves, 20);
            free(pile[occupied].p);
            if((arr_equal(current_pos->oc, oc_ref, 8))&&(arr_equal(current_pos->pc, pc_ref, 8))&&(arr_equal(current_pos->oa, oa_ref, 12))&&(arr_equal(current_pos->pa, pa_ref, 12))){
                *length = current_depth;
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos);
                free(pile);
                // printf("Iterations : %d\n", iterations);
                // printf("Iterations2 : %d\n", iterations2);
                return moves;
            }
            if(current_depth < d_max){
                for(int k = 0; k < 18; k++){
                    if((current_depth > 0)&&(moves[current_depth - 1]/3 != k/3)){
                    pos *exp_pos = pos_univ_move(current_pos, k);
                    if (current_depth + 1 + heuristique_1(exp_pos, pdb_corner, pdb_edge_1, pdb_edge_2) <= d_max){
                        pile[occupied].p = exp_pos;
                        pile[occupied].depth = current_depth + 1;
                        array_copy(moves, pile[occupied].moves, 20);
                        pile[occupied].moves[current_depth] = k;
                        occupied++;
                    }
                    else{
                        free(exp_pos);
                    }
                }
                }
            }
            free(moves);
            free(current_pos); 
        }
    }
    free(pile);
    *length = -1;
    // printf("Iterations : %d\n", iterations);
    return NULL;
}

int *kociemba(pos *p, int *length, int *pdb_phase_1_oc_and_oa, int *pdb_phase_1_oa_and_uds, int *pdb_phase_1_oc_and_uds, int *pdb_phase_2_8_edges_and_uds, int *pdb_phase_2_pc_and_uds){
    pos_and_depth_and_moves *pile = malloc(sizeof(pos_and_depth_and_moves)*324);
    int pc_ref[8];
    int pa_ref[12];
    for(int i = 0; i < 8; i++){
        pc_ref[i] = i;
    }
    for(int i = 0; i < 12; i++){
        pa_ref[i] = i;
    }
    int init_moves[30];
    for (int i = 0; i < 30; i++){
        init_moves[i] = -1;
    }
    int *length_phase_1 = malloc(sizeof(int));
    int *length_phase_2 = malloc(sizeof(int));
    int *moves_phase_1 = malloc(sizeof(int)*12);
    int *moves_phase_2 = malloc(sizeof(int)*18);
    pos *intermediate_pos = malloc(sizeof(pos));
    bool flag = false;
    // printf("PHASE 1\n");
    // Phase 1
    for(int d_max = phase_1_heuristique(p, pdb_phase_1_oc_and_oa, pdb_phase_1_oa_and_uds, pdb_phase_1_oc_and_uds); (d_max <= 12)&&(!flag); d_max++){
        // printf("Profondeur: %d\n", d_max);
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        array_copy(init_moves, pile[0].moves, 12);
        int occupied = 1;
        while(occupied > 0){
            // printf("%d\n", occupied);
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int current_depth = pile[occupied].depth;
            int *moves = malloc(sizeof(int)*12);
            array_copy(pile[occupied].moves, moves, 12);
            free(pile[occupied].p);
            fflush(stdout);
            if(phase_1_encoding(current_pos) == 227){
                // printf("G0 -> G1: trouvé !\n");
                printf("Phase 1 depth: %d\n", current_depth);
                *length_phase_1 = current_depth;
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                array_copy(moves, moves_phase_1, current_depth);
                occupied = 0;
                *intermediate_pos = *current_pos;
                flag = true;
            }
            else {
                if(current_depth < d_max){
                for(int k = 0; k < 18; k++){
                    pos *exp_pos = pos_univ_move(current_pos, k);
                    if (current_depth + 1 + phase_1_heuristique(exp_pos, pdb_phase_1_oc_and_oa, pdb_phase_1_oa_and_uds, pdb_phase_1_oc_and_uds) <= d_max){
                        pile[occupied].p = exp_pos;
                        pile[occupied].depth = current_depth + 1;
                        array_copy(moves, pile[occupied].moves, 12);
                        pile[occupied].moves[current_depth] = k;
                        occupied++;
                    }
                    else{
                        free(exp_pos);
                    }
                }
                }
            }
            free(moves);
            free(current_pos); 
        }
    }
    // printf("PHASE 2\n");
    flag = false;
    // Phase 2
    for(int d_max = phase_2_heuristique(intermediate_pos, pdb_phase_2_8_edges_and_uds, pdb_phase_2_pc_and_uds); (d_max <= 18)&&(!flag); d_max++){
        // printf("Profondeur: %d\n", d_max);
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *intermediate_pos;
        pile[0].depth = 0;
        array_copy(init_moves, pile[0].moves, 18);
        int occupied = 1;
        while(occupied > 0){
            // printf("%d\n", occupied);
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int current_depth = pile[occupied].depth;
            int *moves = malloc(sizeof(int)*18);
            array_copy(pile[occupied].moves, moves, 18);
            free(pile[occupied].p);
            // à vérifier (orientations -> ok)
            if(arr_equal(current_pos->pc, pc_ref, 8)&&arr_equal(current_pos->pa, pa_ref, 12)){
                printf("Phase 2 depth: %d\n", current_depth);
                // printf("G1 -> G2: trouvé !\n");
                *length_phase_2 = current_depth;
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                array_copy(moves, moves_phase_2, current_depth);
                occupied = 0;
                flag = true;
            }
            else {
                if(current_depth < d_max){
                for(int k = 0; k < 18; k++){
                    if((k == 1)||(k == 3)||(k == 4)||(k == 5)||(k == 7)||(k == 10)||(k == 12)||(k == 13)||(k == 14)||(k == 16)){
                    pos *exp_pos = pos_univ_move(current_pos, k);
                    if (current_depth + 1 + phase_2_heuristique(exp_pos, pdb_phase_2_8_edges_and_uds, pdb_phase_2_pc_and_uds) <= d_max){
                        pile[occupied].p = exp_pos;
                        pile[occupied].depth = current_depth + 1;
                        array_copy(moves, pile[occupied].moves, 18);
                        pile[occupied].moves[current_depth] = k;
                        occupied++;
                    }
                    else{
                        free(exp_pos);
                    }
                }
                }
            }
            }
            free(moves);
            free(current_pos); 
        }
    }
    *length = *length_phase_1 + *length_phase_2;
    free(intermediate_pos);
    int n1 = *length_phase_1;
    int n2 = *length_phase_2;
    free(length_phase_1);
    free(length_phase_2);
    free(pile);
    return arr_concat(moves_phase_1, moves_phase_2, n1, n2);
}

void gen_pdb_corners(void){
    int total = 88179840;
    int ligne = 2187;
    // int nb_max = 1000000;
    int *pdb_corners = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_corners[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*4);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    // int iterations = 0;
    // assert(false);
    while (debut != fin){
        // iterations++;
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_corners[ligne*current_pos->pc + (current_pos->oc)/3];
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = ligne*exp_pos->pc + (exp_pos->oc)/3;
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_corners[exp_encoding] > current_g + 1) || ((pdb_corners[exp_encoding] == 0)&&(exp_encoding != 0))){
                pdb_corners[exp_encoding] = current_g + 1 < 11 ? current_g + 1 : 11;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite != total*4);
    FILE *fptr = fopen("corner_pdb.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_corners[k]);
    }
    fclose(fptr);
    free(pdb_corners);
    free(pile);
}

void gen_pdb_edges_1(void){
    int total = 42577920;
    // int nb_max = 1000000;
    int *pdb_edges_1 = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_edges_1[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*8);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        assert(capacite <= total);
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        // printf("Iteration %d\nDebut: %d\nFin: %d\n", iterations, debut, fin);
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut = (debut == total - 1)? 0: (debut + 1);
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_edges_1[edge_1_encoding_comp(current_pos)];
        // printf("%d\n", edge_1_encoding_comp(current_pos));
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = edge_1_encoding_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_edges_1[exp_encoding] > current_g + 1) || ((pdb_edges_1[exp_encoding] == 0)&&(exp_encoding != 0))){
                pdb_edges_1[exp_encoding] = current_g + 1 < 10 ? current_g + 1 : 10;
                pile[fin] = *exp_pos;
                fin = (fin == total) ? 1 : (fin + 1);
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("edge_1_pdb.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_edges_1[k]);
    }
    fclose(fptr);
    free(pdb_edges_1);
    free(pile);
}

void gen_pdb_edges_2(void){
    int total = 42577920;
    // int nb_max = 1000000;
    int *pdb_edges_2 = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_edges_2[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*8);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut = (debut == total - 1)? 0: (debut + 1);
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        assert(edge_2_encoding_comp(current_pos) < total);
        int current_g = pdb_edges_2[edge_2_encoding_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            assert(edge_2_encoding_comp(exp_pos) < total);
            int exp_encoding = edge_2_encoding_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_edges_2[exp_encoding] > current_g + 1) || ((pdb_edges_2[exp_encoding] == 0)&&(exp_encoding != 23442432))){
                pdb_edges_2[exp_encoding] = current_g + 1 < 10 ? current_g + 1 : 10;
                pile[fin] = *exp_pos;
                fin = (fin == total) ? 1 : (fin + 1);
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite == 0);
    // printf("%d\n%d\n", capacite, iterations);
    FILE *fptr = fopen("edge_2_pdb.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_edges_2[k]);
    }
    fclose(fptr);
    free(pdb_edges_2);
    free(pile);
}

void gen_pdb_phase_1_oc_and_oa(void){
    int total = 4478976;
    // int nb_max = 1000000;
    int *pdb_oc_and_oa = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_oc_and_oa[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*20);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_oc_and_oa[encoding_oc_and_oa_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = encoding_oc_and_oa_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_oc_and_oa[exp_encoding] > current_g + 1) || ((pdb_oc_and_oa[exp_encoding] == 0)&&(exp_encoding != 0))){
                pdb_oc_and_oa[exp_encoding] = current_g + 1 < 12 ? current_g + 1 : 12;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("pdb_phase_1_oc_and_oa.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_oc_and_oa[k]);
    }
    fclose(fptr);
    free(pdb_oc_and_oa);
    free(pile);
}

void gen_pdb_phase_1_oa_and_uds(void){
    int total = 1013760;
    // int nb_max = 1000000;
    int *pdb_oa_and_uds = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_oa_and_uds[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*20);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_oa_and_uds[encoding_uds_and_oa_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = encoding_uds_and_oa_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_oa_and_uds[exp_encoding] > current_g + 1) || ((pdb_oa_and_uds[exp_encoding] == 0)&&(exp_encoding != 227))){
                pdb_oa_and_uds[exp_encoding] = current_g + 1 < 12 ? current_g + 1 : 12;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("pdb_phase_1_oa_and_uds.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_oa_and_uds[k]);
    }
    fclose(fptr);
    free(pdb_oa_and_uds);
    free(pile);
}

void gen_pdb_phase_1_oc_and_uds(void){
    int total = 1082565;
    // int nb_max = 1000000;
    int *pdb_oc_and_uds = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_oc_and_uds[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*20);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_oc_and_uds[encoding_uds_and_oc_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = encoding_uds_and_oc_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_oc_and_uds[exp_encoding] > current_g + 1) || ((pdb_oc_and_uds[exp_encoding] == 0)&&(exp_encoding != 227))){
                pdb_oc_and_uds[exp_encoding] = current_g + 1 < 12 ? current_g + 1 : 12;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("pdb_phase_1_oc_and_uds.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_oc_and_uds[k]);
    }
    fclose(fptr);
    free(pdb_oc_and_uds);
    free(pile);
}

void gen_pdb_phase_2_8_edges_and_uds(void){
    int total = 967680;
    // int nb_max = 1000000;
    int *pdb_8_edges_and_uds = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_8_edges_and_uds[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*20);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_8_edges_and_uds[encoding_8_edges_and_uds_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            if((j == 1)||(j == 3)||(j == 4)||(j == 5)||(j == 7)||(j == 10)||(j == 12)||(j == 13)||(j == 14)||(j == 16)){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = encoding_8_edges_and_uds_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_8_edges_and_uds[exp_encoding] > current_g + 1) || ((pdb_8_edges_and_uds[exp_encoding] == 0)&&(exp_encoding != 0))){
                pdb_8_edges_and_uds[exp_encoding] = current_g + 1 < 18 ? current_g + 1 : 18;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
            }
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("pdb_phase_2_8_edges_and_uds.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_8_edges_and_uds[k]);
    }
    fclose(fptr);
    free(pdb_8_edges_and_uds);
    free(pile);
}

void gen_pdb_phase_2_pc_and_uds(void){
    int total = 967680;
    // int nb_max = 1000000;
    int *pdb_pc_and_uds = malloc(sizeof(int)*total);
    for (int j = 0 ; j < total; j++){
        pdb_pc_and_uds[j] = 0;
    }
    pos_comp *pile = malloc(sizeof(pos_comp)*total*20);
    pos_comp *p_comp = etat_initial_comp();
    pile[0] = *p_comp;
    free(p_comp);
    int debut = 0;
    int fin = 1;
    int capacite = 1;
    int iterations = 0;
    int j = 1;
    // assert(false);
    while (capacite != 0){
        iterations++;
        if(iterations == j){
            printf("%d\n", j);
            j *= 10;
        }
        pos_comp *current_pos = malloc(sizeof(pos_comp));
        *current_pos = pile[debut];
        debut++;
        capacite--;
        // assert((ligne*current_pos->pc + current_pos->oc < total) && (ligne*current_pos->pc + current_pos->oc >= 0));
        int current_g = pdb_pc_and_uds[encoding_pc_and_uds_comp(current_pos)];
        for (int j = 0 ; j < 18 ; j++){
            if((j == 1)||(j == 3)||(j == 4)||(j == 5)||(j == 7)||(j == 10)||(j == 12)||(j == 13)||(j == 14)||(j == 16)){
            pos_comp *exp_pos = pos_comp_univ_move(current_pos, j);
            int exp_encoding = encoding_pc_and_uds_comp(exp_pos);
            // assert((exp_encoding >= 0)&&(exp_encoding < total));
            if((pdb_pc_and_uds[exp_encoding] > current_g + 1) || ((pdb_pc_and_uds[exp_encoding] == 0)&&(exp_encoding != 0))){
                pdb_pc_and_uds[exp_encoding] = current_g + 1 < 18 ? current_g + 1 : 18;
                pile[fin] = *exp_pos;
                fin++;
                capacite++;
            }
            free(exp_pos);
        }
        }
        free(current_pos);
    }
    assert(capacite == 0);
    FILE *fptr = fopen("pdb_phase_2_pc_and_uds.txt", "w");
    for (int k = 0; k < total ; k++){
        fprintf(fptr, "%d\n", pdb_pc_and_uds[k]);
    }
    fclose(fptr);
    free(pdb_pc_and_uds);
    free(pile);
}

// // Tout est dans le nom... résoud une position compressée du rubik's cube de manière optimale en renvoyant un tableau des mouvements à effectuer par un parcours naïf avec un algo IDDFS. Il prend aussi une profondeur maximale de recherche à ne pas dépasser, et s'il est dépassé il renvoie un tableau qui contient  -1. 
int *solver_naif(pos *p, int *length, int max_depth){
    pos_and_depth_and_moves *pile = malloc(sizeof(pos_and_depth_and_moves)*359);
    int init_moves[20];
    for (int i = 0; i < 20; i++){
        init_moves[i] = -1;
    }
    for (int i = 0 ; i <= max_depth; i++){
        pile[0].p = malloc(sizeof(pos));
        *pile[0].p = *p;
        pile[0].depth = 0;
        array_copy(init_moves, pile[0].moves, 20);
        int occupied = 1;
        while(occupied > 0){
            occupied--;
            pos *current_pos = malloc(sizeof(pos));
            *current_pos = *pile[occupied].p;
            int d = pile[occupied].depth;
            int *moves = malloc(sizeof(int)*20);
            array_copy(pile[occupied].moves, moves, 20);
            free(pile[occupied].p);
            if ((pc_arr_to_pc(current_pos -> pc) == 0)&&(oc_arr_to_oc(current_pos -> oc) == 0)&&(pa_arr_to_pa(current_pos -> pa) == 0)&&(oa_arr_to_oa(current_pos -> oa) == 0)){
                for (int j = 0; j < occupied; j++){
                    free(pile[j].p);
                }
                free(current_pos);
                free(pile);
                *length = i;
                return moves;
            }
            if (d < i){
                for (int j = 0; j < 18; j++){
                    pile[occupied + j].p = pos_univ_move(current_pos, j);
                    pile[occupied + j].depth = d + 1;
                    array_copy(moves, pile[occupied + j].moves, 20);
                    pile[occupied + j].moves[d] = j;
                }
                occupied += 18;
            }
            free(moves);
            free(current_pos);
        }
    }
    free(pile);
    *length = -1;
    return NULL;
}

// Fonction utile à l'affichage graphique du rk. 
int colorie_coin(int c, int o){
    if (c==0){
        if (o==0){
            return 1;
        }
        else if (o==1){
            return 0;
        }
        else{
            return 2;
        }
    }
    else if (c==1){
        if (o==0){
            return 1;
        }
        else if (o==1){
            return 3;
        }
        else{
            return 0;
        }
    }
    else if (c==2){
        if (o==0){
            return 1;
        }
        else if (o==1){
            return 2;
        }
        else{
            return 5;
        }
    }
    else if (c==3){
        if (o==0){
            return 1;
        }
        else if (o==1){
            return 5;
        }
        else{
            return 3;
        }
    }
    else if (c==4){
        if (o==0){
            return 4;
        }
        else if (o==1){
            return 5;
        }
        else{
            return 2;
        }
    }
    else if (c==5){
        if (o==0){
            return 4;
        }
        else if (o==1){
            return 3;
        }
        else{
            return 5;
        }
    }
    else if (c==6){
        if (o==0){
            return 4;
        }
        else if (o==1){
            return 2;
        }
        else{
            return 0;
        }
    }
    else {
        if (o==0){
            return 4;
        }
        else if (o==1){
            return 0;
        }
        else{
            return 3;
        }
    }
}

// Fonction utile à l'affichage graphique du rk. 
int colorie_arete(int a, int o){
    if (a==0){
        if (o==0){
            return 0;
        }
        else{
            return 2;
        }
    }
    else if (a==1){
        if (o==0){
            return 1;
        }
        else {
            return 0;
        }
    }
    else if (a==2){
        if (o==0){
            return 0;
        }
        else{
            return 3;
        }
    }
    else if (a==3){
        if (o==0){
            return 4;
        }
        else{
            return 0;
        }
    }
    else if (a==4){
        if (o==0){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if (a==5){
        if (o==0){
            return 1;
        }
        else{
            return 3;
        }
    }
    else if (a==6){
        if (o==0){
            return 4;
        }
        else {
            return 3;
        }
    }
    else if (a==7){
        if (o==0){
            return 4;
        }
        else{
            return 2;
        }
    }
    else if (a==8){
        if (o==0){
            return 5;
        }
        else{
            return 2;
        }
    }
    else if (a==9){
        if (o==0){
            return 1;
        }
        else{
            return 5;
        }
    }
    else if (a==10){
        if (o==0){
            return 5;
        }
        else{
            return 3;
        }
    }
    else {
        if (o==0){
            return 4;
        }
        else {
            return 5;
        }
    }
}

void print_moves(int *moves, int n){
    for(int k = 0; k < n; k++){
        switch(moves[k]){
            case 0 : printf("F "); break;
            case 1 : printf("F2 "); break;
            case 2 : printf("F3 "); break;
            case 3 : printf("U "); break;
            case 4 : printf("U2 "); break;
            case 5 : printf("U3 "); break;
            case 6 : printf("L "); break;
            case 7 : printf("L2 "); break;
            case 8 : printf("L3 "); break;
            case 9 : printf("R "); break;
            case 10 : printf("R2 "); break;
            case 11 : printf("R3 "); break;
            case 12 : printf("D "); break;
            case 13 : printf("D2 "); break;
            case 14 : printf("D3 "); break;
            case 15 : printf("B "); break;
            case 16 : printf("B2 "); break;
            case 17 : printf("B3 "); break;
    }
    }
    printf("\n");
}

// Fonction utile à l'affichage graphique du rk. 
void print_facelet(int k){
    setlocale(LC_CTYPE, "");
    wchar_t square = 0x25A0;
    switch(k){
        case 0 : printf("\033[1;37m%lc \033[0m", square); break;
        case 1 : printf("\033[1;34m%lc \033[0m", square); break;
        case 2 : printf("\033[1;35m%lc \033[0m", square); break;
        case 3 : printf("\033[1;31m%lc \033[0m", square); break;
        case 4 : printf("\033[1;32m%lc \033[0m", square); break;
        case 5 : printf("\033[1;33m%lc \033[0m", square); break;
    }
}

// Prend en entrée une position compressée du rk et l'affiche. 
void render_comp(pos_comp *p){
    // N° d'une couleur = f, u, l, r, d, b
    int *arr_oc = pos_comp_to_oc_arr(p);
    int *arr_oa = pos_comp_to_oa_arr(p);
    int *arr_pc = pos_comp_to_pc_arr(p);
    int *arr_pa = pos_comp_to_pa_arr(p);
    int facelet_level[54];
    // on colorie les centres...
    facelet_level[4] = 1;
    facelet_level[22] = 2;
    facelet_level[25] = 0;
    facelet_level[28] = 3;
    facelet_level[31] = 5;
    facelet_level[49] = 4;
    // ... puis les coins ...
    facelet_level[0] = colorie_coin(arr_pc[2], (3-arr_oc[2])%3);
    facelet_level[2] = colorie_coin(arr_pc[3], (3-arr_oc[3])%3);
    facelet_level[6] = colorie_coin(arr_pc[0], (3-arr_oc[0])%3);
    facelet_level[8] = colorie_coin(arr_pc[1], (3-arr_oc[1])%3);
    facelet_level[9] = colorie_coin(arr_pc[2], (3-arr_oc[2] + 1)%3);
    facelet_level[11] = colorie_coin(arr_pc[0], (3-arr_oc[0] + 2)%3);
    facelet_level[12] = colorie_coin(arr_pc[0], (3-arr_oc[0] + 1)%3);
    facelet_level[14] = colorie_coin(arr_pc[1], (3-arr_oc[1] + 2)%3);
    facelet_level[15] = colorie_coin(arr_pc[1], (3-arr_oc[1] + 1)%3);
    facelet_level[17] = colorie_coin(arr_pc[3], (3-arr_oc[3] + 2)%3);
    facelet_level[18] = colorie_coin(arr_pc[3], (3-arr_oc[3] + 1)%3);
    facelet_level[20] = colorie_coin(arr_pc[2], (3-arr_oc[2] + 2)%3);
    facelet_level[33] = colorie_coin(arr_pc[4], (3-arr_oc[4] + 2)%3);
    facelet_level[35] = colorie_coin(arr_pc[6], (3-arr_oc[6] + 1)%3);
    facelet_level[36] = colorie_coin(arr_pc[6], (3-arr_oc[6] + 2)%3);
    facelet_level[38] = colorie_coin(arr_pc[7], (3-arr_oc[7] + 1)%3);
    facelet_level[39] = colorie_coin(arr_pc[7], (3-arr_oc[7] + 2)%3);
    facelet_level[41] = colorie_coin(arr_pc[5], (3-arr_oc[5] + 1)%3);
    facelet_level[42] = colorie_coin(arr_pc[5], (3-arr_oc[5] + 2)%3);
    facelet_level[44] = colorie_coin(arr_pc[4], (3-arr_oc[4] + 1)%3);
    facelet_level[45] = colorie_coin(arr_pc[6], (3-arr_oc[6])%3);
    facelet_level[47] = colorie_coin(arr_pc[7], (3-arr_oc[7])%3);
    facelet_level[51] = colorie_coin(arr_pc[4], (3-arr_oc[4])%3);
    facelet_level[53] = colorie_coin(arr_pc[5], (3-arr_oc[5])%3);
    // ... puis les arêtes !
    facelet_level[1] = colorie_arete(arr_pa[9], -arr_oa[9]%3);
    facelet_level[3] = colorie_arete(arr_pa[4], -arr_oa[4]%3);
    facelet_level[5] = colorie_arete(arr_pa[5], -arr_oa[5]%3);
    facelet_level[7] = colorie_arete(arr_pa[1], -arr_oa[1]%3);
    facelet_level[10] = colorie_arete(arr_pa[4], (-arr_oa[4] + 1) %2);
    facelet_level[21] = colorie_arete(arr_pa[8], (-arr_oa[8] + 1)%2);
    facelet_level[23] = colorie_arete(arr_pa[0], (-arr_oa[0] + 1)%2);
    facelet_level[34] = colorie_arete(arr_pa[7], (-arr_oa[7] + 1)%2);
    facelet_level[13] = colorie_arete(arr_pa[1], (-arr_oa[1] + 1)%2);
    facelet_level[24] = colorie_arete(arr_pa[0], -arr_oa[0]%2);
    facelet_level[26] = colorie_arete(arr_pa[2], -arr_oa[2]%2);
    facelet_level[37] = colorie_arete(arr_pa[3], (-arr_oa[3] + 1)%2);
    facelet_level[16] = colorie_arete(arr_pa[5], (-arr_oa[5] + 1)%2);
    facelet_level[27] = colorie_arete(arr_pa[2], (-arr_oa[2] + 1)%2);
    facelet_level[29] = colorie_arete(arr_pa[10], (-arr_oa[10] + 1)%2);
    facelet_level[40] = colorie_arete(arr_pa[6], (-arr_oa[7] + 1)%2);
    facelet_level[19] = colorie_arete(arr_pa[9], (-arr_oa[9] + 1)%2);
    facelet_level[30] = colorie_arete(arr_pa[10], -arr_oa[10]%2);
    facelet_level[32] = colorie_arete(arr_pa[8], -arr_oa[8]%2);
    facelet_level[43] = colorie_arete(arr_pa[11], (-arr_oa[11] + 1)%2);
    facelet_level[46] = colorie_arete(arr_pa[3], -arr_oa[3]%3);
    facelet_level[48] = colorie_arete(arr_pa[7], -arr_oa[7]%3);
    facelet_level[50] = colorie_arete(arr_pa[6], -arr_oa[6]%3);
    facelet_level[52] = colorie_arete(arr_pa[11], -arr_oa[11]%3);
    printf("      ");
    print_facelet(facelet_level[0]);
    print_facelet(facelet_level[1]);
    print_facelet(facelet_level[2]);
    printf("\n");
    printf("      ");
    print_facelet(facelet_level[3]);
    print_facelet(facelet_level[4]);
    print_facelet(facelet_level[5]);
    printf("\n");
    printf("      ");
    print_facelet(facelet_level[6]);
    print_facelet(facelet_level[7]);
    print_facelet(facelet_level[8]);
    printf("\n");
    for (int i = 9; i < 21; i++){
        print_facelet(facelet_level[i]);
    }
    printf("\n");
    for (int i = 21; i < 33; i++){
        print_facelet(facelet_level[i]);
    }
    printf("\n");
    for (int i = 33; i < 45; i++){
        print_facelet(facelet_level[i]);
    }
    printf("\n");
    printf("      ");
    print_facelet(facelet_level[45]);
    print_facelet(facelet_level[46]);
    print_facelet(facelet_level[47]);
    printf("\n");
    printf("      ");
    print_facelet(facelet_level[48]);
    print_facelet(facelet_level[49]);
    print_facelet(facelet_level[50]);
    printf("\n");
    printf("      ");
    print_facelet(facelet_level[51]);
    print_facelet(facelet_level[52]);
    print_facelet(facelet_level[53]);
    printf("\n\n");
    free(arr_oc);
    free(arr_oa);
    free(arr_pc);
    free(arr_pa);
}

// Prend en entrée une position du rk et l'affiche. 
void render(pos *p){
    pos_comp *p_comp = pos_to_pos_comp(p);
    render_comp(p_comp);
    free(p_comp);
}


// ---------------------------------------------------------------------------
// Command-line interface
// ---------------------------------------------------------------------------

#define KOCIEMBA_TABLES 5
#define KORF_TABLES 3

static const char *kociemba_files[KOCIEMBA_TABLES] = {
    "pdb_phase_1_oc_and_oa.txt", "pdb_phase_1_oa_and_uds.txt", "pdb_phase_1_oc_and_uds.txt",
    "pdb_phase_2_8_edges_and_uds.txt", "pdb_phase_2_pc_and_uds.txt"};
static const int kociemba_sizes[KOCIEMBA_TABLES] = {4478976, 1013760, 1082565, 967680, 967680};

static const char *korf_files[KORF_TABLES] = {"corner_pdb.txt", "edge_1_pdb.txt", "edge_2_pdb.txt"};
static const int korf_sizes[KORF_TABLES] = {88179840, 42577920, 42577920};

static void usage(void){
    printf("Usage:\n");
    printf("  ./rubik gen kociemba                      Build Kociemba's 5 pattern databases (~1 min)\n");
    printf("  ./rubik gen korf                          Build Korf's 3 pattern databases (several hours, several GB of RAM)\n");
    printf("  ./rubik solve <kociemba|korf> [len] [seed] Scramble with len random moves, then solve\n");
    printf("  ./rubik bench <kociemba|korf> [n] [len] [seed]  Solve n random scrambles and report statistics\n");
    printf("\nDefault scramble length: 30 for kociemba, 10 for korf. Default seed: current time.\n");
}

static double seconds_since(clock_t start){
    return ((double)(clock() - start)) / CLOCKS_PER_SEC;
}

static int *load_pdb(const char *file, int size){
    FILE *f = fopen(file, "r");
    if (f == NULL){
        fprintf(stderr, "Missing pattern database %s: run './rubik gen ...' first.\n", file);
        exit(1);
    }
    int *table = malloc(sizeof(int) * size);
    for (int k = 0; k < size; k++){
        if (fscanf(f, "%d", &table[k]) != 1){
            fprintf(stderr, "Pattern database %s is incomplete or corrupted.\n", file);
            exit(1);
        }
    }
    fclose(f);
    return table;
}

static bool is_solved(pos *p){
    pos *solved = etat_initial();
    bool res = arr_equal(p->pc, solved->pc, 8) && arr_equal(p->oc, solved->oc, 8)
            && arr_equal(p->pa, solved->pa, 12) && arr_equal(p->oa, solved->oa, 12);
    free(solved);
    return res;
}

static bool is_korf(const char *solver){
    if (strcmp(solver, "korf") == 0) return true;
    if (strcmp(solver, "kociemba") == 0) return false;
    fprintf(stderr, "Unknown solver '%s' (expected 'kociemba' or 'korf').\n", solver);
    exit(1);
}

// Loads the pattern databases of the chosen solver into tables[].
static void load_tables(bool korf, int **tables){
    int n = korf ? KORF_TABLES : KOCIEMBA_TABLES;
    clock_t start = clock();
    printf("Loading pattern databases...\n");
    fflush(stdout);
    for (int i = 0; i < n; i++){
        tables[i] = korf ? load_pdb(korf_files[i], korf_sizes[i])
                         : load_pdb(kociemba_files[i], kociemba_sizes[i]);
    }
    printf("Loaded in %.1f s\n\n", seconds_since(start));
}

static void free_tables(bool korf, int **tables){
    int n = korf ? KORF_TABLES : KOCIEMBA_TABLES;
    for (int i = 0; i < n; i++) free(tables[i]);
}

// Solves p with the chosen solver; returns the move list (or NULL) and sets *length.
static int *run_solver(bool korf, pos *p, int *length, int **t){
    if (korf) return korf_1d1(p, length, t[0], t[1], t[2]);
    return kociemba(p, length, t[0], t[1], t[2], t[3], t[4]);
}

// Applies the solution to a copy of the scrambled cube and checks it is solved.
static bool check_solution(pos *scrambled, int *moves, int length){
    if (moves == NULL || length < 0) return false;
    pos copy = *scrambled;
    apply_shuffle(&copy, moves, length);
    return is_solved(&copy);
}

static int cmd_gen(const char *solver){
    bool korf = is_korf(solver);
    clock_t start = clock();
    if (korf){
        gen_pdb_corners();
        gen_pdb_edges_1();
        gen_pdb_edges_2();
    } else {
        gen_pdb_phase_1_oc_and_oa();
        gen_pdb_phase_1_oa_and_uds();
        gen_pdb_phase_1_oc_and_uds();
        gen_pdb_phase_2_8_edges_and_uds();
        gen_pdb_phase_2_pc_and_uds();
    }
    printf("\n%s pattern databases built in %.1f s\n", korf ? "Korf" : "Kociemba", seconds_since(start));
    return 0;
}

static int cmd_solve(const char *solver, int scramble_length){
    bool korf = is_korf(solver);
    int *tables[KOCIEMBA_TABLES];
    load_tables(korf, tables);

    pos *p = etat_initial();
    int *scramble = shuffle(p, scramble_length);
    printf("Scramble (%d moves): ", scramble_length);
    print_moves(scramble, scramble_length);
    render(p);

    int length = 0;
    clock_t start = clock();
    int *solution = run_solver(korf, p, &length, tables);
    double elapsed = seconds_since(start);

    if (solution == NULL){
        printf("\nNo solution found within the depth limit.\n");
    } else {
        printf("\nSolution (%d moves, %.2f s): ", length, elapsed);
        print_moves(solution, length);
        printf("Verified: %s\n", check_solution(p, solution, length) ? "cube solved" : "NOT solved");
    }
    free(solution);
    free(scramble);
    free(p);
    free_tables(korf, tables);
    return 0;
}

static int cmd_bench(const char *solver, int n, int scramble_length){
    bool korf = is_korf(solver);
    int *tables[KOCIEMBA_TABLES];
    load_tables(korf, tables);

    int solved = 0, total_moves = 0, min_moves = INT_MAX, max_moves = 0;
    double total_time = 0, max_time = 0;
    for (int i = 0; i < n; i++){
        pos *p = etat_initial();
        free(shuffle(p, scramble_length));
        int length = 0;
        clock_t start = clock();
        int *solution = run_solver(korf, p, &length, tables);
        double elapsed = seconds_since(start);
        if (check_solution(p, solution, length)){
            solved++;
            total_moves += length;
            min_moves = min(min_moves, length);
            max_moves = max(max_moves, length);
        }
        total_time += elapsed;
        max_time = max_double(max_time, elapsed);
        free(solution);
        free(p);
    }
    printf("\n%s, %d random scrambles of %d moves\n", korf ? "Korf" : "Kociemba", n, scramble_length);
    printf("  Solved and verified: %d/%d\n", solved, n);
    if (solved > 0){
        printf("  Solution length:     mean %.1f, min %d, max %d moves\n",
               (double)total_moves / solved, min_moves, max_moves);
    }
    printf("  Solving time:        mean %.3f s, max %.3f s\n", total_time / n, max_time);
    free_tables(korf, tables);
    return 0;
}

int main(int argc, char **argv){
    if (argc < 3){
        usage();
        return 1;
    }
    const char *command = argv[1];
    const char *solver = argv[2];
    bool korf = is_korf(solver);
    int default_length = korf ? 10 : 30;

    if (strcmp(command, "gen") == 0){
        return cmd_gen(solver);
    }
    if (strcmp(command, "solve") == 0){
        int scramble_length = argc > 3 ? atoi(argv[3]) : default_length;
        srand(argc > 4 ? (unsigned)atoi(argv[4]) : (unsigned)time(NULL));
        return cmd_solve(solver, scramble_length);
    }
    if (strcmp(command, "bench") == 0){
        int n = argc > 3 ? atoi(argv[3]) : 20;
        int scramble_length = argc > 4 ? atoi(argv[4]) : default_length;
        srand(argc > 5 ? (unsigned)atoi(argv[5]) : (unsigned)time(NULL));
        return cmd_bench(solver, n, scramble_length);
    }
    usage();
    return 1;
}
