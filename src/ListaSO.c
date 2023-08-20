#include "ListaSO.h"


int Lista_localizar(Lista *lista,char codigo_envio[]) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve -1.

    // Contador
    int contador = 0;

    // Mientras no se pase el ultimo elemento y el codigo de envio no coincida
    while ((contador <= lista->limite_superior) && strcmp(lista->arreglo[contador]->codigo_envio,codigo_envio) != 0 ) {
        contador++;
    }

    // Si 'contador' supera el ultimo elemento, no se encontro el elemento
    if (contador > lista->limite_superior) contador = -1;

    return contador;
}
