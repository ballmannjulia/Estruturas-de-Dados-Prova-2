#include "../include/posfixa.hpp"
#include "../include/pilha.hpp"
#include "../include/fila.hpp"
#include <cctype>  

int posfixa(Fila<char>& entrada) {
  Pilha<int> pilha(entrada.capacidade);

  while (!entrada.esta_vazia()) {
    char token = entrada.desenfileirar();

    if (std::isdigit(token)) {
      pilha.empilhar(token - '0');
    } else {
      if (pilha.esta_vazia()) throw std::runtime_error("Faltam operandos");
      int b = pilha.desempilhar();

      if (pilha.esta_vazia()) throw std::runtime_error("Faltam operandos");
      int a = pilha.desempilhar();

      int resultado;
      switch (token) {
        case '+': resultado = a + b; 
        break;
        case '-': resultado = a - b; 
        break;
        case '*': resultado = a * b; 
        break;
        case '/':
          if (b == 0) throw std::runtime_error("Divisão por zero");
          resultado = a / b;
          break;
        default:
          throw std::runtime_error("Operador inválido");
      }

      pilha.empilhar(resultado);
    }
  }

  if (pilha.esta_vazia()) throw std::runtime_error("Expressão malformada");
  int resultado = pilha.desempilhar();

  if (!pilha.esta_vazia()) throw std::runtime_error("Operandos em excesso");

  return resultado;
}
