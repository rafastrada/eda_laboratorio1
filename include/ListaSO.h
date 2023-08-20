#ifndef LISTASO_H
#define LISTASO_H

#include "Envio.h"

// Constantes
#define LISTA_TAM_ARREGLO 300

// Definicion de la lista
typedef struct {
    Envio arreglo[LISTA_TAM_ARREGLO];

    // Indice del ultimo elemento en la lista
    int limite_superior;
} Lista;



// --- LOCALIZAR
int Lista_localizar(Lista *,char []);


// Macro para Lista llena (recibe un puntero a la lista)
#define Lista_estaLlena(L) ((L)->limite_superior >= (LISTA_TAM_ARREGLO - 1))

#endif // LISTASO_H
