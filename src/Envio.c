#include "Envio.h"

// Funciones

void Envio_init(Envio *envio) {
    // Inicializa los campos de la estructura ENVIO
    envio->codigo_envio = "";
    envio->dni_receptor = ENVIO_DNI_MINIMO;
    envio->dni_remitente = ENVIO_DNI_MINIMO;
    envio->domicilio_receptor = "";
    envio->fecha_envio = ENVIO_FECHA_MINIMA;
    envio->fecha_recepcion = ENVIO_FECHA_MINIMA;
    envio->nombre_apellido_receptor = "";
    envio->nombre_apellido_remitente = "";
}

// OBSERVADORES
// ------------------------------------------------------
char* Envio_get_codigo_envio(Envio *envio) {
    // Devuelve el campo CODIGO DE ENVIO
    return envio->codigo_envio;
}

unsigned int Envio_get_dni_receptor(Envio *envio) {
    // Devuelve el campo DNI del RECEPTOR
    return envio->dni_receptor;
}

char* Envio_get_nombre_apellido_receptor(Envio *envio) {
    // Devuelve el campo NOMBRE y APELLIDO del RECEPTOR
    return envio->nombre_apellido_receptor;
}

char* Envio_get_domicilio_receptor(Envio *envio) {
    // Devuelve el campo DOMICILIO del RECEPTOR
    return envio->domicilio_receptor;
}

unsigned int Envio_get_dni_remitente(Envio *envio) {
    // Devuelve el campo DNI del REMITENTE
    return envio->dni_remitente;
}

char* Envio_get_nombre_apellido_remitente(Envio *envio) {
    // Devuelve el campo NOMBRE y APELLIDO del REMITENTE
    return envio->nombre_apellido_remitente;
}

char* Envio_get_fecha_envio(Envio *envio) {
    // Devuelve el campo FECHA de ENVIO
    return envio->fecha_envio;
}

char* Envio_get_fecha_recepcion(Envio *envio) {
    // Devuelve el campo FECHA de RECEPCION
    return envio->fecha_recepcion;
}
