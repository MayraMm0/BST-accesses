# BST-accesses
**Activity 3.4 - Access Analysis with Binary Search Trees**

**Description**
This application analyzes server access logs using a Binary Search Tree (BST) data structure to identify IP addresses with the highest number of accesses. The program processes log files sorted by IP and enables detection of suspicious access patterns.

**Objective**
Implement a BST where:
Key: Number of accesses
Value: IP address

The program must identify the top 5 IPs with the highest number of accesses, which is useful for detecting potential attacks or anomalous network behavior.

**Input**
The program receives a text file with logs sorted by IP in the following format:
Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest
Oct 9 10:33:15 423.2.230.77:6166 Failed password for illegal user admin
Oct 9 11:45:02 192.168.1.100:5500 Accepted password for user john

```This file is the result of the **previous Integrative Activity**.```

## Functionality

### 1. Reading and Processing
- Opens the input file with logs sorted by IP
- Counts the number of accesses for each unique IP address
- Stores the data in a BST with the structure: `(number_of_accesses, IP_address)`

### 2. Identification of IPs with Most Accesses
- Uses the BST to find the 5 IPs with the highest number of accesses
- Displays results sorted from highest to lowest

## Project Structure
```
.
├── main.cpp                 # Main program
├── BST.h                    # Binary Search Tree implementation
├── sorted_logs.txt          # Input file (result from previous activity)
├── ReflexAct3.4.pdf        # Reflection document
└── README.md               # This file
```
------------------------------------------------------------------
**Actividad 3.4 - Análisis de Accesos con Binary Search Trees**
**Descripción**
Esta aplicación analiza logs de accesos a servidores utilizando una estructura de datos Binary Search Tree (BST) para identificar las direcciones IP con mayor número de accesos. El programa procesa archivos de logs ordenados por IP y permite detectar patrones de acceso sospechosos.

**Objetivo**
Implementar un BST donde:
Llave: Número de accesos
Valor: Dirección IP

El programa debe identificar las 5 IPs con mayor cantidad de accesos, lo cual es útil para detectar posibles ataques o comportamientos anómalos en la red.

**Entrada**
El programa recibe un archivo de texto con logs ordenados por IP en el siguiente formato:
Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest
Oct 9 10:33:15 423.2.230.77:6166 Failed password for illegal user admin
Oct 9 11:45:02 192.168.1.100:5500 Accepted password for user john

```Este archivo es el resultado de la **Actividad Integradora anterior**.```

## Funcionalidad

### 1. Lectura y Procesamiento
- Abre el archivo de entrada con logs ordenados por IP
- Cuenta el número de accesos por cada dirección IP única
- Almacena los datos en un BST con la estructura: `(número_accesos, dirección_IP)`

### 2. Identificación de IPs con Más Accesos
- Utiliza el BST para encontrar las 5 IPs con mayor número de accesos
- Muestra los resultados ordenados de mayor a menor

## Estructura del Proyecto
```
.
├── main.cpp                 # Programa principal
├── BST.h                    # Implementación del Binary Search Tree
├── logs_ordenados.txt       # Archivo de entrada (resultado actividad anterior)
├── ReflexAct3.4.pdf        # Documento de reflexión
└── README.md               # Este archivo
