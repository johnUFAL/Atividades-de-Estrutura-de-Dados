#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct No { union { double n; char op; } dado; struct No *prox; } No;
typedef struct { No *topo; } Pilha;

void empilha(Pilha *p, int tipo, double num, char op) {
    No *novo = (No*)malloc(sizeof(No));
    if(tipo) novo->dado.op = op; else novo->dado.n = num;
    novo->prox = p->topo; p->topo = novo;
}

double desempilha_num(Pilha *p) {
    No *temp = p->topo; double n = temp->dado.n;
    p->topo = temp->prox; free(temp); return n;
}

char desempilha_op(Pilha *p) {
    No *temp = p->topo; char op = temp->dado.op;
    p->topo = temp->prox; free(temp); return op;
}

int precedencia(char op) {
    return (op=='^'||op=='s')?4:(op=='*'||
            op=='/')?3:(op=='+'||op=='-')?2:0;
}

double opera(char op, double a, double b) {
    return op=='+'?a+b:op=='-'?a-b:op=='*'?a*b:
           op=='/'?a/b:op=='^'?pow(a,b):sqrt(b);
}

double calcula(const char *expr) {
    Pilha nums = {0}, ops = {0};
    for(int i=0; expr[i]; i++) {
        if(expr[i]==' ') continue;
        if(isdigit(expr[i])) {
            double n; sscanf(expr+i, "%lf", &n);
            empilha(&nums, 0, n, 0);
            while(isdigit(expr[i])||expr[i]=='.')i++; i--;
        } else if(strncmp(expr+i,"sqrt",4)==0) {
            empilha(&ops, 1, 0, 's'); i+=3;
        } else if(expr[i]=='*'&& expr[i+1]=='*') {
            empilha(&ops, 1, 0, '^'); i++;
        } else if(expr[i]=='(') {
            empilha(&ops, 1, 0, '(');
        } else if(expr[i]==')') {
            while(ops.topo && ops.topo->dado.op!='(') {
                char op = desempilha_op(&ops);
                double b = desempilha_num(&nums);
                double a = op=='s'?0:desempilha_num(&nums);
                empilha(&nums, 0, opera(op,a,b), 0);
            }
            if(ops.topo && ops.topo->dado.op=='(') desempilha_op(&ops);
        } else if(strchr("+-*/^",expr[i])) {
            while(ops.topo && precedencia(ops.topo->dado.op)>=precedencia(expr[i])) {
                char op = desempilha_op(&ops);
                double b = desempilha_num(&nums);
                double a = op=='s'?0:desempilha_num(&nums);
                empilha(&nums, 0, opera(op,a,b), 0);
            }
            empilha(&ops, 1, 0, expr[i]);
        }
    }
    while(ops.topo) {
        char op = desempilha_op(&ops);
        double b = desempilha_num(&nums);
        double a = op=='s'?0:desempilha_num(&nums);
        empilha(&nums, 0, opera(op,a,b), 0);
    }
    return nums.topo ? desempilha_num(&nums) : 0;
}
