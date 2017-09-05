#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include "usbLista.h"
#include "usbJson.h"
#include "usbFunctions.h"

void toJson(){

    strcpy(json,"[");

    ElementoLista *elem = NULL;
    for (elem = Lista_Primero(&listaUsb); elem != NULL; elem = Lista_Siguiente(&listaUsb, elem)){
        struct InfoUSB *info = (struct InfoUSB *)elem->objeto;

        /*Creating a json object*/
        json_object * jobj = json_object_new_object();    
        
        /*Creating json strings*/
        json_object *nombre = json_object_new_string(info->nombre);
        json_object *idVendor = json_object_new_string(info->idVendor);
        json_object *idProduct = json_object_new_string(info->idProduct);
        json_object *montaje = json_object_new_string(info->usbDirMount);
        json_object *nodo = json_object_new_string(info->usbNodo);
        /*Form the json object*/
        /*Each of these is like a key value pair*/
        json_object_object_add(jobj,"nombre", nombre);
        json_object_object_add(jobj,"idVendor", idVendor);
        json_object_object_add(jobj,"idProduct", idProduct);
        json_object_object_add(jobj,"montaje", montaje);
        json_object_object_add(jobj,"nodo", nodo);
         /*Now printing the json object*/
        //printf("\n%s",json_object_to_json_string(jobj));
        strcat(json,json_object_to_json_string(jobj));
        if(Lista_Siguiente(&listaUsb, elem)!=NULL) strcat(json,",");
    }   
    strcat(json,"]");
    //printf("--ACT: %s",json);
}

//Devuelve el tipo de solicitud
char *getTipoSolicitud(char *jsonSolicitud){

    json_object * jobj = json_tokener_parse(jsonSolicitud);
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
        case json_type_string: 
            //Devuelve el primer valor que por defecto siempre será 
            //la función de la solicitud
            return (char *)json_object_get_string((json_object *)val);
            //printf ("\n%s-%s\n",json_object_get_string((json_object *)key),
            //                    json_object_get_string((json_object *)val));
            break;
        
        default:
            printf("no es string");
            printf("%s",key);
            break;
        }
    }
    return "";

}

//Devuelve el valor del campo n del JSON que le ingresa
char *getValuePorCampo(char *JSON, int nCampo) {

    int i=1;
    json_object * jobj = json_tokener_parse(JSON);
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
        case json_type_string: 
            //Devuelve el primer valor que por defecto siempre será 
            //la función de la solicitud
            if(i==nCampo) return (char *)json_object_get_string((json_object *)val);
            i++;
            //printf ("\n%s-%s\n",json_object_get_string((json_object *)key),
            //                    json_object_get_string((json_object *)val));
            break;
        
        default:
            printf("no es string");
            printf("%s",key);
            break;
        }
    }
    return "";
}

int getIntPorCampo(char *JSON, int nCampo) {

    int i=1;
    json_object * jobj = json_tokener_parse(JSON);
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_int:
                if(i==nCampo) return json_object_get_int((json_object *)val);
                i++;
                break;
            default: 
                printf("%s",key);
                i++ ;
                break;
        }
    }
    return 0;
}

char *jsonNombrarDipositivosRespuesta(char *solicitudNombrar,int status, char *nombre, char *nodo, char *stErr) {

  json_object * jobj = json_object_new_object();

  json_object *jsonSoli = json_object_new_string(solicitudNombrar);
  json_object *jsonStatus = json_object_new_int(status);
  json_object *jsonNombre = json_object_new_string(nombre);
  json_object *jsonNodo = json_object_new_string(nodo);
  json_object *jsonError = json_object_new_string(stErr);

  json_object_object_add(jobj,"qwqwqw", jsonSoli);
  json_object_object_add(jobj,"status", jsonStatus);
  json_object_object_add(jobj,"nombre", jsonNombre);
  json_object_object_add(jobj,"nodo", jsonNodo);
  json_object_object_add(jobj,"error", jsonError);

  //char retorno[50000] = "";
  //strcpy(retorno,(char *)json_object_to_json_string(jobj));
    
  return (char *)json_object_to_json_string(jobj);

}


char *jsonEscribirRespuesta(char *solicitudEscribir, char *nombre, char * nombreArchivo, int status, char * stErr) {
  
    json_object * jobj = json_object_new_object();

    json_object *jsonSoli = json_object_new_string(solicitudEscribir);
    json_object *jsonNombre = json_object_new_string(nombre);
    json_object *jsonNombreArchivo = json_object_new_string(nombreArchivo);
    json_object *jsonStatus = json_object_new_int(status);
    json_object *jsonError = json_object_new_string(stErr);

    json_object_object_add(jobj,"solicitud", jsonSoli);
    json_object_object_add(jobj,"nombre", jsonNombre);
    json_object_object_add(jobj,"nombre_del_archivo", jsonNombreArchivo);
    json_object_object_add(jobj,"status", jsonStatus);
    json_object_object_add(jobj,"error", jsonError);

    /*Now printing the json object*/
    return (char *)json_object_to_json_string(jobj);

}