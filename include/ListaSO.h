#ifndef LISTASO_H
#define LISTASO_H

#include "Envio.h"

// Constantes
#define LISTA_TAM_ARREGLO 300

// Definicion de la lista
// (el orden de la lista es CRECIENTE)
typedef struct {
    Envio arreglo[LISTA_TAM_ARREGLO];

    // Indice del ultimo elemento en la lista
    // (Si la lista esta vacia, entonces vale -1)
    int limite_superior;
} Lista;

// --- INICIALIZAR
void Lista_init(Lista *);

// --- LOCALIZAR
enum Lista_localizar_retornos {LOCALIZACION_EXITOSA, ERROR_NO_EXISTE};
int Lista_localizar(Lista *,char [], Lista_localizar_retornos *);

// --- ALTA
enum Lista_alta_retornos {ALTA_EXITOSA, ERROR_CODIGO_EXISTENTE, ERROR_LISTA_LLENA};
int Lista_alta(Lista *,Envio);

// --- BAJA
int Lista_baja(Lista *,char []);


// Macro para Lista llena (recibe un puntero a la lista)
#define Lista_estaLlena(L) ((L)->limite_superior >= (LISTA_TAM_ARREGLO - 1))

#endif // LISTASO_H
