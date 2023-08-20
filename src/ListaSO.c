#include "ListaSO.h"

void Lista_init(Lista *lista) {
    lista->limite_superior = -1;
}

int Lista_localizar(Lista *lista,char codigo_envio[], Lista_localizar_retornos *exito) {
    // Busca en 'lista' el elemento con el campo 'codigo_envio',
    // si lo encuentra, la funcion devuelve el indice del arreglo,
    // si el elemento no se encuentra en la lista, devuelve la posicion donde deberia encontrarse.

    // Variable de resultado de localizacion
    *exito = ERROR_NO_EXISTE;

    // Contador
    int contador = 0;

    // Mientras no se pase el ultimo elemento y
    // el codigo de envio sea mayor o igual que el de Lista(contador)
    while ((contador <= lista->limite_superior) && strcmp(lista->arreglo[contador]->codigo_envio,codigo_envio) < 0 ) {
        contador++;
    }

    // Si 'contador' supera el ultimo elemento, no se encontro el elemento
    if (contador <= lista->limite_superior) {
        // Si 'codigo_envio' es distinto del de Lista(contador), no se encontro el elemento
        if (strcmp(lista->arreglo[contador]->codigo_envio,codigo_envio) == 0) *exito = LOCALIZACION_EXITOSA;
    }

    return contador;
}


int Lista_alta(Lista *lista, Envio nuevo) {

    // Variable de retorno
    int salida = ERROR_LISTA_LLENA;
    // Variable de exito de localizar
    Lista_localizar_retornos exito_localizar;

    // Comprueba si existe un ENVIO con CODIGO DE ENVIO similar
    // y obtiene la posicion en donde deberia ir el elemento
    int posicion_nuevo = Lista_localizar(lista,nuevo.codigo_envio,&exito_localizar);

    // Se procesa el ALTA
    if (exito_localizar == ERROR_NO_EXISTE) {
        // Si la lista NO esta llena
        if (!Lista_estaLlena(lista)) {
            // Se actualiza el limite superior
            lista->limite_superior++;

            // Se desplazan los elementos hacia la derecha
            for (int i=lista->limite_superior; i > posicion_nuevo; i--) {
                Envio temporal = lista->arreglo[i-1];
                lista->arreglo[i] = temporal;
            }

            // Se agrega el nuevo elemento a la lista
            lista->arreglo[posicion_nuevo] = nuevo;

            // Se actualiza la salida
            salida = ALTA_EXITOSA;
        }
    }
    else salida = ERROR_CODIGO_EXISTENTE;

    return salida;
}


int Lista_baja(Lista *lista,char codigo_envio) {

    int posicion;
    Lista_localizar_retornos exito_localizar;

    // Se captura el resultado de la localizacion y su respectiva
    // posicion para 'codigo_envio'
    posicion = Lista_localizar(lista,codigo_envio,&exito_localizar);

    if (exito_localizar == LOCALIZACION_EXITOSA) {
        for (int i=posicion; i<)
    }

    else return 0;
}
