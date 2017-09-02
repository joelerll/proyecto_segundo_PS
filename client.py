#!/usr/bin/python3.5

# import argparse
# parser = argparse.ArgumentParser(description='Ayuda client app')
# parser.add_argument('listar_dispositivos', type=str,help='listar todos los dispositivos del usb')
# parser.add_argument('nombrar_dispositivo', type=str,help='darle un nombre a los dispositivos')
# parser.add_argument('leer_archivo', type=str,help='obtener contenido de un archivo')
# parser.add_argument('escribir_archivo', type=str,help='anadir contenido a un archivo del usb')
# args = parser.parse_args()
# print(args.accumulate(args.integers))

import sys
import requests
import json
from tabulate import tabulate
# print ('Argument List:', str(sys.argv))
ayuda = """
		Ejecute para ayuda:
		
		\033[92mpython3 client.py --help\033[0m
	"""

opciones_string = """
Uso: python3 client.py PUERTO [solicitud] [argumentos...]
	
	\033[92mpuerto:\033[0m
		PUERTO                       nombre del puerto en que se esta ejecutando el servidor, Ej: 8888

	\033[92msolicitud:\033[0m
		listar_dispositivos
		nombrar_dispositivo
		leer_archivo
		escribir_archivo
	
	\033[1mArgumentos listar_dispositivos:\033[0m
		Listar todos los dispositivos conectado al pc

		\033[94mEjemplo: python3 client.py 8888 listar_dispositivos\033[0m
	
	\033[1mArgumentos nombrar_dispositivo:\033[0m
		nodo                         nodo del localizacion del usb, Ej: /dev/sdb1
		nombre                       nombre del usb que se desea dar, Ej: mi_usb

		\033[94mEjemplo: python3 client.py 8888 nombrar_dispositivo /dev/sdb1 mi_usb\033[0m

	
	\033[1mArgumento leer_archivo:\033[0m
		nombre                       nombre del usb previamente establecido
		nombre_archivo               nombre del archivo relativa al usb, Ej: mi_archivo.txt  
		
		\033[94mEjemplo: python3 client.py 8888 leer_archivo mi_usb mi_archivo.txt\033[0m
	
	
	\033[1mArgumento escribir_archivo:\033[0m
		nombre 		             nombre del usb previamente establecido
		nombre_archivo               nombre del archivo relativa al usb, Ej: mi_archivo.txt
		tamano_contenido             tamano del contenido que se desea guardar
		contenido                    direccion del archivo que contiene lo que se desea enviar, Ej: /home/user/contenido.txt
		
		\033[94mEjemplo: python3 client.py 8888 escribir_archivo mi_usb mi_archivo.txt 50 /home/user/contenido.txt\033[0m
"""

def listar_dispositivos():
	r = requests.get("http://localhost:{}/listar_dispositivos".format(int(sys.argv[1])), data=None)
	respuesta = json.loads(r.text)
	resp = []
	if (respuesta['status'] == 1):	
		for respuesta in respuesta['dispositivos']:
			tmp = []
			tmp.append( respuesta['nombre'])
			tmp.append( respuesta['montaje'])
			tmp.append( respuesta['id'])
			tmp.append( respuesta['nodo'])
			resp.append(tmp)
		print (tabulate(resp, headers=["nombre","montaje", "id", "nodo"], tablefmt="grid"))
	else:
		print(respuesta['str_error'])

def nombrar_dispositivo():
	if len(sys.argv) == 5:
		req ="{" +  "'nodo': '{}', 'nombre': '{}','solicitud': 'nombrar_dispositivo'".format(sys.argv[3],sys.argv[4]) + "}" 
		r = requests.post("http://localhost:{}/nombrar_dispositivo".format(int(sys.argv[1])), data={"nombrar_dispositivo": req})
		respuesta = json.loads(r.text)
		resp = []
		tmp = []
		tmp.append( respuesta['nombre'])
		tmp.append( respuesta['nodo'])
		resp.append(tmp)
		print (tabulate(resp, headers=["nombre", "nodo"], tablefmt="grid"))
	else:
		print("El numero de argumentos no es valido")
		print(ayuda)

def leer_archivo():
	if len(sys.argv) == 5:
		req ="{" +  "{'nombre_archivo': '{}', 'nombre': '{}','solicitud': 'leer_archivo'}".format(sys.argv[3],sys.argv[4]) + "}"
		r = requests.post("http://localhost:{}/leer_archivo".format(int(sys.argv[1])), data={"leer_archivo": req})
		respuesta = json.loads(r.text)
		print(r.text)
	else:
		print("El numero de argumentos no es valido")
		print(ayuda)

def escribir_archivo():
	# TODO: leer archivo para escribirlo
	if len(sys.argv) == 7:
		req ="{" +  "{'nombre': '{}', 'nombre_archivo': '{}','solicitud': 'escribir_archivo', 'tamano_contenido': {}, 'contenido': '{}'}".format(sys.argv[5],sys.argv[6]) + "}"
		r = requests.post("http://localhost:8888/escribir_archivo".format(int(sys.argv[1])), data={"escribir_archivo": req})
		respuesta = json.loads(r.text)
		print(r.text)
	else:
		print("El numero de argumentos no es valido")
		print(ayuda)

def opciones():
	try:
		r = requests.get("http://localhost:{}".format(int(sys.argv[1])), data=None)
		if (str(sys.argv[2]) == 'listar_dispositivos'):
			listar_dispositivos()
		elif (str(sys.argv[2]) == 'nombrar_dispositivo'):
			nombrar_dispositivo()
		elif (str(sys.argv[2]) == 'leer_archivo'):
			leer_archivo()
		elif (str(sys.argv[2]) == 'escribir_archivo'):
			escribir_archivo()
		else:
			escribir_archivo()
	except:
		print("El server no esta escuchando en este puerto")

def main():
	estado = True
	if (len(sys.argv) > 1):
		if (str(sys.argv[1]) == '--help'):

			print(opciones_string)
		
		if (str(sys.argv[1]) != '--help'):
			try:
				if (len(sys.argv) == 2):
					print("No hay solicitud")
				else:
					opciones()
				pass
			except:
				print("El puerto no es un numero")
	else:
		print (ayuda)

if __name__ == "__main__":
    main()