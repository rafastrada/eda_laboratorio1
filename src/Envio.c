#include "Envio.h"
#include <string.h>

// Funciones

void Envio_init(Envio *envio) {
    // Inicializa los campos de la estructura ENVIO
    strcpy(envio->codigo_envio,"");
    envio->dni_receptor = ENVIO_DNI_MINIMO;
    envio->dni_remitente = ENVIO_DNI_MINIMO;
    strcpy(envio->domicilio_receptor,"");
    strcpy(envio->fecha_envio,ENVIO_FECHA_MINIMA);
    strcpy(envio->fecha_recepcion,ENVIO_FECHA_MINIMA);
    strcpy(envio->nombre_apellido_receptor,"");
    strcpy(envio->nombre_apellido_remitente,"");
}

void Envio_copiar(Envio *origen,Envio *destino) {
    // Copia los campos de ORIGEN a DESTINO
    strcpy(destino->codigo_envio,origen->codigo_envio);
    destino->dni_receptor = origen->dni_receptor;
    strcpy(destino->nombre_apellido_receptor,origen->nombre_apellido_receptor);
    strcpy(destino->domicilio_receptor,origen->domicilio_receptor);
    destino->dni_remitente = origen->dni_remitente;
    strcpy(destino->nombre_apellido_remitente,origen->nombre_apellido_remitente);
    strcpy(destino->fecha_envio,origen->fecha_envio);
    strcpy(destino->fecha_recepcion,origen->fecha_recepcion);
}
