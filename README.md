# Programación de Estructuras Dinámicas

### Proyecto Final - Ciclo 02/2020

------

## Integrantes 

- Carlos Roberto Ávila Hernandez   [00032420]
 
- Ernesto Briceño Magaña           [00025620]

- Gilberto Eduardo Campos Acevedo  [00229220]
 
- Andrea Eunice Rodríguez Juárez   [00011020]

- Samuel Enrique Vargas Echeverría [00037720]


## Descripción del Proyecto

### Everywhere Airlines

![Logo](https://github.com/00032420/ProyectoFinalPED0220/blob/master/images/logo.jpg)

Se ha creado un sistema de boletería simplificado para una aerolínea ficticia que tiene nexos con 60 ciudades alrededor del mundo, las cuales se pueden visualizar en este mapa: 

![Mapa](https://github.com/00032420/ProyectoFinalPED0220/blob/master/images/mapa.jpg)

El sistema posee las siguientes funcionalidades:

- Calcula la mejor ruta desde San Salvador, El Salvador, hacia la ciudad que el pasajero desee viajar. Las rutas se calculan en base a los vuelos específicos que la aerolinea ofrece. Así mismo, se calcula la mejor ruta de regreso.

- En caso que la aerolínea no ofrezca vuelos directos hacia esa localización, se toman en cuentas todas las escalas necesarias para llegar al destino. Al cliente se le carga monetariamente el costo total de cada boleto, incluyendo todas las escalas de sus viajes de ida y vuelta.

 - Se le da al cliente la opción de registrar cuantas maletas desee con su respectivo peso.
 
- Se encolan a los pasajeros para el ingreso a las respectivas puestas de sus primeros destinos, teniendo prioridad con los que tengan algún tipo de discapacidad o que se encuentren en el grupo de la tercera edad.

- Se calcula el total vendido por boletos.


## Tipos de estructuras utilizadas

Las principales estructuras de datos que se han utilizado son: 

#### Grafo

Se creó [este grafo](http://graphonline.ru/en/?graph=NPvTxAfWDBTwNwpb) ponderado y direccionado que conecta a todas las ciudades con las que la aerolínea tiene nexo. Cada vértice es una ciudad y cada arco es el vuelo que las conecta, el peso de cada arco es la cantidad promedio de minutos que tarda dicho viaje. Dicho peso se utiliza para calcular el costo de viaje. Se usó la matriz de adyacencia para obtener la lista de adyacencia y poder implementar el grafo en el sistema (desde cero) que calcula la mejor ruta en función del tiempo.

#### Arreglos Dinámicos

Se crean arreglos dinamicos usando la libreria `<vector>` para almacenar diferentes tipos de datos como por ejemplo para guardar los clientesy verificar si tienen alguna discapacidad o no, para registrar las maletas de los clientes y para iniciar el abordaje de los pasajeros. 

#### Pilas 

Si el cliente ingresa los datos de su equipaje estos se llevan en una pila haciendo uso de la librería `<stack>` para ser procesados posteriormente. El procesamiento del equipaje posterior a esto está fuera del enfoque del sistema, lo único de lo que guarda es una lista de las pilas que contienen el equipaje que se ha registrado.

#### Colas

Por medio de la librería `<queue>` se crean colas que almacenan todas las posibles rutas que hay disponibles desde un destino a otro. Posteriormente se comparan para sacar la más óptima tanto de ida como de vuelta y se almacenan en el registro del cliente.
