#include <stdio.h>
#include <malloc.h>

struct state_func;
struct state;

char alf_in[2][1] = {"0", "1"};
char alf_out[2][1] = {"O","I"};

typedef struct {
    char in;
    char out;
    struct state *next;
} state_func;
typedef struct {
    state_func funcs[2];
} state;

state states[4];

void def_func(state_func *stt_f ,char in, char out, state *next) {
    stt_f->in = in;
    stt_f->out = out;
    stt_f->next = next;
}
void link_states() {
    state_func func0[4], func1[4];
    def_func((&func0[0]),alf_in[0][0],alf_out[0][0],&(states[1]));
    def_func((&func0[1]),alf_in[0][0],alf_out[1][0],&(states[2]));
    def_func((&func0[2]),alf_in[0][0],alf_out[1][0],&(states[3]));
    def_func((&func0[3]),alf_in[0][0],alf_out[0][0],&(states[0]));
    states[0].funcs[0] = func0[0];
    states[1].funcs[0] = func0[1];
    states[2].funcs[0] = func0[2];
    states[3].funcs[0] = func0[3];
    def_func((&func1[0]),alf_in[1][0],alf_out[1][0],&(states[2]));
    def_func((&func1[1]),alf_in[1][0],alf_out[0][0],&(states[3]));
    def_func((&func1[2]),alf_in[1][0],alf_out[1][0],&(states[0]));
    def_func((&func1[3]),alf_in[1][0],alf_out[0][0],&(states[1]));
    states[0].funcs[1] = func1[0];
    states[1].funcs[1] = func1[1];
    states[2].funcs[1] = func1[2];
    states[3].funcs[1] = func1[3];
}

int main() {
    link_states();
    state *stt = &states[0];
    char txt[2] = "11";
    for(int i = 0 ; i < 2; i++) {
        if(txt[i] == stt->funcs[0].in) {
            txt[i] = stt->funcs[0].out;
            stt = stt->funcs[0].next;
        } else if(txt[i] == stt->funcs[1].in) {
            txt[i] = stt->funcs[1].out;
            stt = stt->funcs[1].next;
        } else {
            printf("Entrada inesperada!\n");
        }
    }
    printf("Lendo fita.... \n");
    printf("%s \n",txt);
    printf("Fim da execução.... \n");
    for(int i = 0; i < 4; i++){
        free((&states[i]));
    }
    return 0;
}