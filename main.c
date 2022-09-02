#include <stdio.h>
#include <malloc.h>
struct state_func{
    char in;
    char out;
    struct state *next;
};
struct state{
    char *name;
    struct state_func *funcs;
};
struct elemento_contexto {
    int *in;
    int *out;
    int *state;
};

int n_states = 4;
int n_func = 3;

struct state *states;
struct elemento_contexto *ec;

char alf_in[3][1] = {"0", "1","x"};
char alf_out[3][1] = {"A","B", "X"};

void def_func(struct state_func *stt_f ,char in, char out, struct state *next) {
    stt_f->in = in;
    stt_f->out = out;
    stt_f->next = next;
}
void link_states(int n,int n_f,struct elemento_contexto *m) {
    struct state_func func[n_f][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n_f; j++) {
            def_func((&func[j][i]),alf_in[m[i].in[j]][0],alf_out[m[i].out[j]][0],&(states[m[i].state[j]]));
            states[i].funcs[j] = func[j][i];
        }
    }
}

int main() {
    states = malloc(n_states*sizeof (struct state));
    ec = malloc(n_states*sizeof (struct elemento_contexto));
    int out[] = {0,1,2,1,0,2,1,1,2,0,0,2};
    char *names[] = {"q0","q1","q2","q3"};

    for(int i = 0; i < n_states; i++) {
        states[i].name = names[i];
        states[i].funcs = malloc(n_func*sizeof (struct state_func));

        ec[i].in = malloc(n_func*sizeof (int));
        ec[i].out = malloc(n_func*sizeof (int));
        ec[i].state = malloc(n_func*sizeof (int));

        for(int j = 0; j < n_func; j++) {
            ec[i].in[j] = j;
            ec[i].out[j] = out[i*3 + j];
            ec[i].state[j] = i + j + 1 - ((i + j >= n_func)?n_func:0);
        }

    }

    link_states(n_states,n_func,ec);
    struct state *stt = &states[0];
    char txt[5] = "11x00";

    printf("Lendo fita.... \n");
    for(int i = 0 ; i < 5; i++) {
        printf("%s , %c\n",stt->name,txt[i]);
        if(txt[i] == stt->funcs[0].in) {
            txt[i] = stt->funcs[0].out;
            stt = stt->funcs[0].next;
        } else if(txt[i] == stt->funcs[1].in) {
            txt[i] = stt->funcs[1].out;
            stt = stt->funcs[1].next;
        } else if(txt[i] == stt->funcs[2].in) {
            txt[i] = stt->funcs[2].out;
            stt = stt->funcs[2].next;
        } else {
            printf("Entrada inesperada!\n");
        }
    }
    printf("%s \n",txt);
    printf("Fim da execução.... \n");
    for(int i = 0; i < n_states; i++) {
        free(states[i].funcs);
        free(ec[i].in);
        free(ec[i].out);
        free(ec[i].state);
    }
    free(states);
    free(ec);
    return 0;
}