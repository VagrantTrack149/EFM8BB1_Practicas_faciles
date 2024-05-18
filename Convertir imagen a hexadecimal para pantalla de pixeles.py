from PIL import Image

def leer_imagen(ruta):
    # Lee la imagen en blanco y negro
    imagen = Image.open(ruta).convert('L')

    # Reescala la imagen a 84x48 si es necesario
    imagen = imagen.resize((84, 48), resample=Image.LANCZOS)

    return imagen

def intensidad_a_binario(imagen):
    # Transforma los valores de intensidad a 0 o 1
    datos_binarios = [1 if pixel > 128 else 0 for pixel in imagen.getdata()]

    # Convierte la lista de datos binarios a una lista de listas de 8 elementos
    datos_binarios = [datos_binarios[i:i+8] for i in range(0, len(datos_binarios), 8)]

    return datos_binarios

def columnas_a_hexadecimal(columnas):
    # Convierte las columnas de binario a hexadecimal
    datos_hex = [hex(int(''.join(map(str, columna)), 2))[2:] for columna in columnas]

    return datos_hex

def imprimir_datos_hexadecimal(datos_hex):
    # Imprime los datos en el formato solicitado
    for i, dato_hex in enumerate(datos_hex):
          print(f"Reg {i}: 0{dato_hex}H,")

if __name__ == "__main__":
    # Ruta de la imagen
    ruta_imagen = "imagen.jpg"

    # Lee la imagen
    imagen = leer_imagen(ruta_imagen)

    # Transforma los valores de intensidad a 0 o 1
    datos_binarios = intensidad_a_binario(imagen)

    # Procesa las columnas en grupos de 8 datos y las imprime en hexadecimal
    for inicio in range(0, len(datos_binarios[0]), 8):
        fin = inicio + 8
        columnas = [fila[inicio:fin] for fila in datos_binarios]
        datos_hex = columnas_a_hexadecimal(columnas)
        imprimir_datos_hexadecimal(datos_hex)
