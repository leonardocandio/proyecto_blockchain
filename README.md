# project-seguidoresdelchamo

## Colaboradores
 - Leonardo Candio
 - Rodo Vilcarromero
 - Angel Tito
 - Luis David Torres

<div align="center">
    <img src="https://media3.giphy.com/media/bTrTnPMPq8UORCrBWG/200w.gif?cid=6c09b9529l07j9dv02wlh5gsjemai76uovjom0jicdx6sf00&rid=200w.gif&ct=g">
</div>


## Introduccion
Las estructuras de datos son esenciales para un manejo adecuado de toda la información con la que se requiera trabajar. En cosecuencia, 
su estudio y aplicación a los diversos problemas del día a día son importantes. En ese sentido, a modo de aplicación de un caso real en el presente proyecto 
se busca implementar una blockchain transaccional, que en conjunto con los conocimientos adquiridos en el curso de Algoritmos y Estructuras de Datos se hará 
indexaciones sobre la información para hacer un manejo eficiente de estos, para ello se hará uso de las estructuras de datos más eficiente dependiendo del caso o criterio
que se requiera.
 
En consecuencia, en el presente proyecto se implementó una aplicación con el lenguaje C++ para la implementación del blockchain  (backend), 
y Vue.js con materialize para el GUI. Con respecto al backend, se creó una API usando la librería CROW implementado en C++ que nos permite enviar los response del backend convertidos al formato json y poder mostrarlos
para la interaccion del usuario.

## Caso de Estudio
La Blockchain funciona como un libro compartido que no puede ser modificado una vez la data es introducida en la estructura de datos, al mismo tiempo su información
es pública, es decir cualquiera puede acceder a estos registros, por otro lado tiene una seguridad que es compartida (todods colaboran para lograr su eficacia) y enlazada donde todos colaboran para corroborar su veracidad, es decir cada block que contiene nuestra estructura tiene su propio hashcode y tambien el del block que le
antecede, esto al estar como una cadena al ser modificado solo uno cambiaria todos los blocks que esten contenidos en este. Nosotros estudiando esto buscamos implementar una blockchain con todos los métodos de seguridad y metodos de acceso y registro contenidos o aptos para esta estructura al mismo tiempo buscamos optimizar y lograr una
buena implementacion de esta estructura logrando la interaccion que brinda la estructura asi como la seguridad a la que esta ligada para este tipo de cazos especializado
al desarrollo de los preocesos de trancsacciones.

## Importacia del Blockchain
La importacia del blockchain esta principalmente dirigída a los entornos en los cuales se trabaja con el manejo de informacion. Pues esta estructura nos permite lograr con mucha mas rapidez y exactitud la informacion que tenemos contenida en ella. El blockchain es ideal para obtener información, proporcionando datos inmediatos, compartidos y completamente transparentes, almacenados en sus blocks a lo qeu sabemos que cada block es inalterable al que sólo tienen acceso los miembros autorizados de la red. Una red de blockchain hace seguimiento de pedidos, pagos, cuentas, datos de producción y mucho más. Además, dado que los usuarios comparten una única fuente información, puede ver todos los datos de una transacción de principio a fin. Lo que genera mayor confianza y eficiencia, y asi lograr un manejo de datos eficiente y eficaz tanto para los que desarrolladores como para los usuarios.

## Explicacion de la estructura de datos
Esta estructura de datos contiene 4 putnos importantes para lograr la eficiencia y eficacia a la hora de interactuar con el dato que contiene.
Estos 4 puntos son:

- **Data block**: Estas transacciones muestran el movimiento de un activo(Información contenida dentro del block). El bloque de datos registra la información que usted elija: quién, qué, cuándo, dónde, cuánto e incluso el estado, como por ejemplo la transaccion de un dinero para la compra de un objeto cualquiera.
- **Block link**: A medida que un activo se mueve, estos bloques forman una cadena de datos. Los bloques confirman, tanto el tiempo exacto como la secuencia de las transacciones, y se unen de forma segura, evitando que se produzcan modificaciones o inserciones entre dos bloques existentes.
- **Block security**: Cada bloque adicional refuerza la verificación del anterior y, por lo tanto, de todo el blockchain. Esto hace que dicha cadena esté a prueba de manipulaciones, lo que conforma la ventaja principal de la inalterabilidad. Esto evita que alguien modifique la cadena y crea un libro mayor distribuido de transacciones, en el que usted y otros miembros de la red puedan confiar.
- **Proof of work**:
    El proof of work que usamos para nuestra Blockchain es un generico el cual itera a travez de una funcion calculando distintos Nonce hasta lograr que los dos ultimos digitos de cada hashcode lleguen a ser 0. Esto pues como lo trabajamos como un size_t no podemos ingresarlos al inicio de la variable.


## Estructuras de datos utilizadas
Como estructura principal y la base de todo el proyecto tenemos un circular array, del cual obtenemos 
toda la informacion tanto para el armado del blockchain como para los metodos de indexacion, 
pues de ahi sacamos la información requerida en cualquiera de nuestras implementaciones. Esta estructura funciona como una rueda la cual cuenta con un front y un back todo esto almacenado en un array y con las ventajas de acceso y de insert dentro de ella pues todo esto se manejaria como O(1), pues tendemos nuestros datos en forma de un circulo facilitando el acceso y teniendo el ahorro de memoria.

### Métodos de indexación

Dentro de los métodos de indexación tenamos el heap, en el cual usamos un maxheap y un minheap.
        
Para estos dos casos tenemos que ambos son arboles binarios completos (semicompletos). Los cuales se rigen de dos formas distintas, pues uno acomoda nuestros registros segun nosotros lo requiramos la informacion requerida en estas.
Ambos son estructuras que van ordenandose de acuredo a sus métodos de ordenamientos heapify-down y heapify-up. En este caso ambos son armados como arboles binarios a travez del array en el cual se mantienen almacenados  no de forma consecuente si no como la estructura lo demanda y como lo rige sus funciones: right, left y parent.

- Minheap (almacena en el root el dato menor)
- Maxheap (almacena en el root el dato mayor)
    
Para estos metodos de indexacion usamos heap para lograr que nuestra busqueda sea O(1) en ambos casos.
