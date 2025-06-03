//do deepseek
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct no {
    union {
        double numero;
        char operador;
    } dado;
    struct no* prox;
} no;

typedef struct {
    no* topo;
} Pilha;

void criar_pilha(Pilha* p) {
    p->topo = NULL;
}

int vazia(Pilha* p) {
    return p->topo == NULL;
}

void empilhar_numero(Pilha* p, double num) {
    no* novo = (no*)malloc(sizeof(no));
    novo->dado.numero = num;
    novo->prox = p->topo;
    p->topo = novo;
}

void empilhar_operador(Pilha* p, char op) {
    no* novo = (no*)malloc(sizeof(no));
    novo->dado.operador = op;
    novo->prox = p->topo;
    p->topo = novo;
}

double desempilhar_numero(Pilha* p) {
    if (vazia(p)) return 0;
    
    no* temp = p->topo;
    double num = temp->dado.numero;
    p->topo = temp->prox;
    free(temp);
    return num;
}

char desempilhar_operador(Pilha* p) {
    if (vazia(p)) return '\0';
    
    no* temp = p->topo;
    char op = temp->dado.operador;
    p->topo = temp->prox;
    free(temp);
    return op;
}

double topo_numero(Pilha* p) {
    if (vazia(p)) return 0;
    return p->topo->dado.numero;
}

char topo_operador(Pilha* p) {
    if (vazia(p)) return '\0';
    return p->topo->dado.operador;
}

int precedencia(char op) {
    switch(op) {
        case 's': 
        case '^': 
            return 4;
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        default:
            return 0;
    }
}

int eh_operador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 's' || c == '(' || c == ')';
}

double aplicar_operador(char op, double a, double b) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case 's': return sqrt(b); 
        default: return 0;
    }
}

double calcular_expressao(const char* expressao) {
    Pilha numeros;
    Pilha operadores;
    criar_pilha(&numeros);
    criar_pilha(&operadores);
    
    int i = 0;
    while (expressao[i] != '\0') {
        if (expressao[i] == ' ') {
            i++;
            continue;
        }
        
        if (isdigit(expressao[i]) || expressao[i] == '.') {
            char num_str[50];
            int j = 0;
            
            while (isdigit(expressao[i]) || expressao[i] == '.') {
                num_str[j++] = expressao[i++];
            }
            num_str[j] = '\0';
            
            double num = atof(num_str);
            empilhar_numero(&numeros, num);
            continue;
        }
        
        if (eh_operador(expressao[i])) {
            if (strncmp(&expressao[i], "sqrt", 4) == 0) {
                empilhar_operador(&operadores, 's');
                i += 4;
                continue;
            }
            
            if (expressao[i] == '*' && expressao[i+1] == '*') {
                empilhar_operador(&operadores, '^');
                i += 2;
                continue;
            }
            
            if (expressao[i] == '(') {
                empilhar_operador(&operadores, '(');
                i++;
                continue;
            }
            
            if (expressao[i] == ')') {
                while (!vazia(&operadores) && topo_operador(&operadores) != '(') {
                    char op = desempilhar_operador(&operadores);
                    if (op == 's') { 
                        double num = desempilhar_numero(&numeros);
                        empilhar_numero(&numeros, aplicar_operador(op, 0, num));
                    } else {
                        double b = desempilhar_numero(&numeros);
                        double a = desempilhar_numero(&numeros);
                        empilhar_numero(&numeros, aplicar_operador(op, a, b));
                    }
                }
                if (!vazia(&operadores) && topo_operador(&operadores) == '(') {
                    desempilhar_operador(&operadores);
                }
                i++;
                continue;
            }
            
            while (!vazia(&operadores) && precedencia(topo_operador(&operadores)) >= precedencia(expressao[i])) {
                char op = desempilhar_operador(&operadores);
                if (op == 's') { 
                    double num = desempilhar_numero(&numeros);
                    empilhar_numero(&numeros, aplicar_operador(op, 0, num));
                } else {
                    double b = desempilhar_numero(&numeros);
                    double a = desempilhar_numero(&numeros);
                    empilhar_numero(&numeros, aplicar_operador(op, a, b));
                }
            }
            empilhar_operador(&operadores, expressao[i]);
            i++;
            continue;
        }
        
        i++; 
    }
    
    while (!vazia(&operadores)) {
        char op = desempilhar_operador(&operadores);
        if (op == 's') {
            double num = desempilhar_numero(&numeros);
            empilhar_numero(&numeros, aplicar_operador(op, 0, num));
        } else {
            double b = desempilhar_numero(&numeros);
            double a = desempilhar_numero(&numeros);
            empilhar_numero(&numeros, aplicar_operador(op, a, b));
        }
    }
    
    return desempilhar_numero(&numeros);
}

int main() {
    char expressao[100];
    
    printf("Calculadora com Pilhas\n");
    printf("Operadores suportados: + - * / ** (potência) sqrt()\n");
    printf("Digite 'sair' para encerrar\n\n");
    
    while (1) {
        printf("> ");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = '\0'; // Remove newline
        
        if (strcmp(expressao, "sair") == 0) break;
        
        double resultado = calcular_expressao(expressao);
        printf("Resultado: %.2f\n", resultado);
    }
    
    return 0;
}