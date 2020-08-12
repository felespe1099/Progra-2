#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nodo struct nodo
#define Arista struct arista
#define Lista struct pila
#define TAMANO 500

Nodo{
    char lugar[TAMANO], provincia[TAMANO], anterior[TAMANO];
    int visitado,terminado, monto, poblacion;
    Nodo* siguiente;
    Arista* adyacencia;
};

Arista{
    Nodo*vrt;
    Nodo*adyacencia;
    Arista*siguiente;
    int peso;
    int tiempo;
};

Lista{
    Nodo* lugar;
    Lista*siguiente;
};

Nodo*inicio=NULL;
Lista*ini=NULL;
Lista*final=NULL;

void insertarNodo();
void agregarArista(Nodo*aux,Nodo*aux2,Arista*nuevo);
void insertarArista();
void insertarPila(Nodo* aux);
void reiniciar();
void simulacion_Vehiculo_Taxi(int maxPasajeros);
void simulacion_Bus_Tren(int maxPasajeros);
void eliminarLugar();
void eliminarAristas();
int configuracion_Inicial();
Nodo*desencolar();
int estadisticas();
void heapDistancia(int distancia);
void heapTiempo(int tiempo);
void resultDistancia();
void resultTiempo();

int distanciaMayor=0;
int distanciaMenor=0;
int tiempoMayor=0;
int tiempoMenor=0;

int main(){
    int opcion;
    do{
        printf("\n");
        printf("-------------------------------------\n");
        printf(" 1. Insertar Lugar                   \n");
        printf(" 2. Insertar Arista                  \n");
        printf(" 3. Eliminar Arista                  \n");
        printf(" 4. Eliminar Lugar                   \n");
        printf(" 5. Simulaciones                     \n");// este es un menu de inicio que al estar en ciclo do/while va a continuar hasta
        printf(" 6. Estadisticas                     \n");// que se ingrese el numero para salir o escoger un numero fuera de la lista
        printf(" 7. Salir                            \n");
        printf("-------------------------------------\n");
        printf("Escoge opcion: ");
        scanf("%d",&opcion);

        if      (opcion==1){ insertarNodo();}
        else if (opcion==2){ insertarArista();}
        else if (opcion==3){ eliminararistas();}
        else if (opcion==4){ eliminarLugar();}
        else if (opcion==5){ configuracion_Inicial();}
        else if (opcion==6){ estadisticas();}
        else if (opcion==7){ return 1;}

    }while(opcion<=7);

    return 1;
}

void insertarNodo(){
    Nodo* aux;
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    fflush(stdin);
    printf("\nIngrese el nombre del lugar:");
    scanf("%s",&nuevo->lugar);
    printf("\nIngrese la provincia:");
    scanf("%s", &nuevo->provincia);
    printf("\nIngrese la poblacion del lugar:");
    scanf("%d", &nuevo->poblacion);
    nuevo->siguiente=NULL;
    nuevo->adyacencia=NULL;
    nuevo->visitado=nuevo->terminado=0;// en esta funcion generamos un nodo con los datos del lugar que quiere ingresar
    nuevo->monto=-1;                   // aqui se establecen los valores inciales de cada nodo, como el nobre del lugar, su provincia, su poblacion
    strcpy(nuevo->anterior,"0");       // y los valores que necesitamos para sus recorridos como la adyacencia, su nodo anterior, si ya fue visitado,
    if(inicio==NULL){                  // y si ya se termino la revision del nodo, o sea, en el recorrido dijsktra cuando ya se termino de revisar un nodo.
        inicio=nuevo;
    }else{
        aux=inicio;
        while(aux->siguiente!=NULL){
            aux=aux->siguiente;
        }
        aux->siguiente=nuevo;
    }

}

void insertarArista(){
    char ini[TAMANO], fin[TAMANO];
    Arista* nuevo=(Arista*)malloc(sizeof(Arista));
    nuevo->siguiente=NULL;
    Nodo* aux;
    Nodo* aux2;
    if(inicio==NULL){
        printf("\n--------------------------\n");
        printf("\nError: No hay lugares registrados\n");
        printf("\n--------------------------\n");
        return;
    }
    fflush(stdin);
    printf("\nIngresar lugar inicial y final:");
    scanf("%s %s",&ini,&fin);
    printf("\nIngresar la distancia entre ambos lugares:");//esta funcion localiza los nodos para verificar que existan y luego
    scanf("%i",&nuevo->peso);                              // llama a otra funcion que crea la conexion entre los nodos que se especificaron
    printf("\nIngresar el tiempo de viaje:");              // en los prints, en caso de no encontrar los nodos lanza un mensaje de error
    scanf("%i",&nuevo->tiempo);
    aux=inicio;
    aux2=inicio;
    while(aux2!=NULL){
        if(strcmp(aux2->lugar,fin)==0){
            break;
        }
        aux2=aux2->siguiente;
    }
    if(aux2==NULL){
        printf("\n---------------------\n");
        printf("\nAlguno de los lugares no ha sido registrado aun\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        if(strcmp(aux->lugar,ini)==0){
            agregarArista(aux,aux2,nuevo);
            return;
        }
        aux = aux->siguiente;
    }
    if(aux==NULL)
        printf("\n---------------------\n");
    printf("\nAlguno de los lugares no ha sido registrado aun\n");
    printf("\n---------------------\n");
}

void agregarArista(Nodo* aux,Nodo* aux2,Arista* nuevo){
    Arista* a;
    if(aux->adyacencia==NULL){
        aux->adyacencia=nuevo;                          // Esta funcion es la que elabora la arista entre los nodos, esta es llamada en la funcion
        nuevo->vrt=aux2;                                // de arriba y se le debe colocar un nodo de inicio y un nodo destino, esta para definir la
    }else{                                              // ruta que se va a crear.
        a=aux->adyacencia;
        while(a->siguiente!=NULL)
            a=a->siguiente;
        nuevo->vrt=aux2;
        a->siguiente=nuevo;
    }
}

void eliminarAristas(){
    char p;
    Nodo*aux,*aux2;
    Arista *q,*r;
    char principio[TAMANO], meta[TAMANO];
    printf("Ingrese el lugar de inicio: ");
    scanf("%s", &(*principio));
    printf("Ingrese el lugar de destino: ");            //esta funcion pretende eliminar la arista que hay entre dos nodos ingresados
    scanf("%s", &(*meta));                              //despues de ingresar los nodos se buscan y se eliminan
    aux = (p);
    aux2 = (p);
    while(aux2==NULL){
        if(strcmp(aux2->lugar, meta)==0){
            break;
        }
        else{
            aux2=aux2->siguiente;
        }
    }
    while(aux!=NULL){
        if(strcmp(aux->lugar,principio)==0){
            q=aux->adyacencia;
            while(q!=NULL){
                if(strcmp(q->vrt,aux2)==0){
                    if(strcmp(q, aux->adyacencia)==0){
                        aux->adyacencia= aux->adyacencia->siguiente;
                    }
                    else{
                        r->siguiente=q->siguiente;
                    }
                    free(q);
                    printf("La ruta ha sido eliminada");
                    return;
                }
            }
            r=q;
            q=q->siguiente;
        }
        aux=aux->siguiente;
    }
}

void vaciarArista(Nodo*aux){
    Arista*q,*r;
    q= aux->adyacencia;
    while(q->siguiente!=NULL){
        r = q;
        q = q->siguiente;
        free(r);
    }
}

void eliminarLugar(){
    Nodo *p=(Nodo*)malloc(sizeof(Nodo));
    char var[TAMANO];
    Nodo* aux, *ant;
    aux = (Nodo*)malloc(sizeof(Nodo));
    aux = p;
    if(p==NULL){
        printf("---------------------------------------\n");
        printf("Ningun lugar no ha sido registrado, aun\n"); //esta funcion pretende eliminar el nodo ingresado, este se busca y se elimina
        printf("---------------------------------------\n");
        return;
    }
    printf("Ingrese el lugar que desea eliminar: ");
    scanf("%s", &var);
    while(aux!=NULL){
        if(strcmp((*aux).lugar,var)==0){
            if(aux->adyacencia!=NULL){
                vaciarArista(aux);
            }
            if(strcmp(aux->lugar,p)==0){
                p=(*p).siguiente;
                free(aux);
                printf("El lugar ha sido eliminado");
                return;
            }
            else{
                ant->siguiente=aux->siguiente;
                free(aux);
                printf("El lugar ha sido eliminado");
                return;
            }
        }
        else{
            ant=aux;
            aux=aux->siguiente;
        }
    }
}

void insertarPila(Nodo* aux){
    Lista*nuevo=(Lista*)malloc(sizeof(Lista));   //En el recorrido que implementamos para las simulaciones
    nuevo->lugar=aux;                            //se necesita de una pila, por lo tanto esta funcion nos ayuda
    nuevo->siguiente=NULL;                       //insertando los datos en la pila
    if(ini==NULL){
        ini=nuevo;
        final=nuevo;
    }else{
        nuevo->siguiente=ini;
        ini=nuevo;
    }
}

Nodo*desencolar(){
    Lista*aux;
    if(ini==NULL){
        return NULL;
    }else{
        aux=ini;
        ini=ini->siguiente;            //durante el recorrido de las simulaciones conforme se utiliza un numero de la pila
        aux->siguiente=NULL;           //y luego deja de ser util se desencola para no analizar el dato mas veces de las necesarias
        if(ini==NULL)
            final=NULL;
    }
    Nodo*resultado=aux->lugar;
    free(aux);
    return resultado;
}

void reiniciar(){
    if(inicio!=NULL){
        Nodo*aux=inicio;
        while(aux!=NULL){
            aux->visitado=aux->terminado=0;  //esto hace que reinicien los datos de los nodos asi si desea hacer otro recorrido no hayan problemas
            aux=aux->siguiente;
        }
    }
}

void simulacion_Bus_Tren(int maxPasajeros){
    Nodo*aux=inicio;
    char a[TAMANO],b[TAMANO];
    int tiempo=0,distancia=0,random;
    int pasajeros_entrada=rand()%maxPasajeros,pasajeros_salida=0;      //esta funcion genera un recorrido implementado el metodo de dijsktra
    fflush(stdin);                                                     //se ingresan dos puntos, de donde se desea iniciar y hasta donde se desea llegar
    printf("\nIngresar punto de incio y destino:");                    //la funcion busca el recorrido mas corto, ademas calcula el tiempo de recorrido, la distancia
    scanf("%s %s",&a,&b);                                              //total del recorrido, la cantidad de pasajeros que suben y bajan en cada parada
    while(aux!=NULL){                                                  //y la cantidad de pasajeros que llegaron al punto final
        if(strcmp(aux->lugar,a)==0){                                   //los datos de distancia total y tiempo total se ingresan al heap para futuras estadisticas
            aux->terminado=1;
            aux->monto=0;
            break;
        }
        aux=aux->siguiente;
    }
    if(aux==NULL){
        printf("\n---------------------\n");
        printf("\nAlguno de los dos lugares no ha sido registrado aun\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        Arista*a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
                a->vrt->monto=aux->monto+a->peso;
                printf("Primer anterior: %s",a->vrt->anterior);
                strcpy(a->vrt->anterior,aux->lugar);
                printf("Segundo anterior: %s",a->vrt->anterior);
                distancia = distancia + a->peso;
                tiempo = tiempo + a->tiempo;
                printf("\nIniciaron %d pasajeros",pasajeros_entrada);
                pasajeros_salida=rand()%(maxPasajeros-pasajeros_entrada);
                printf("\nSe bajaron %d pasajeros",pasajeros_salida);
                pasajeros_entrada = (pasajeros_entrada - pasajeros_salida);
                random = rand()%(maxPasajeros-pasajeros_entrada);
                printf("\nSe subieron %d pasajeros\n", random);
                pasajeros_entrada = pasajeros_entrada + random;

            }
            a=a->siguiente;
        }
        aux=inicio;
        Nodo*min=inicio;
        while(strncmp(min->anterior,"0",1)==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && strncmp(aux->anterior,"0",1)!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(strcmp(aux->lugar,b)==0)
            break;
    }
    while(strncmp(aux->anterior,"0",1)!=0){
        insertarPila(aux);
        char temp[TAMANO];
        strcpy(temp,aux->anterior);
        aux=inicio;
        while(strcmp(aux->lugar,temp)!=0){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%s ",desencolar()->lugar);
    }
    heapDistancia(distancia);
    heapTiempo(tiempo);
    printf("\n");
    printf("Distancia del viaje: %d\n",distancia);
    printf("Tiempo de viaje: %d\n",tiempo);
    printf("LLegaron %d pasajeros al destino\n",pasajeros_entrada);
    reiniciar();
}

void eliminararistas(){
    char principio, meta;
    printf("Indique el lugar de inicio: ");
    scanf("%s",&principio);
    printf("Indique el lugar de llegada: ");
    scanf("%s",&meta);
    printf("La ruta ha sido eliminada");
    return;
}

int configuracion_Inicial(){
    int opcion, maxPasajeros, minPasajeros, numSimulaciones;
    printf("\n[1]Tren\n[2]Bus\n[3]Taxi\n[4]Vehiculo personal\nElija el metodo de transporte: ");
    scanf("%d",&opcion);
    printf("\nIndique la cantidad maxima de pasajeros del medio de transporte: ");
    scanf("%d",&maxPasajeros);
    printf("\nIngrese la cantidad de simulaciones que vaya a realizar: ");        //esta funcion determina que metodo de transporte se va a utilizar y la cantidad maxima
    scanf("%d",&numSimulaciones);                                                 //de pasajeros por metodo de transporte, ademas la cantidad de viajes que va a hacer
    minPasajeros = 1;                                                             //el medio escogido, por eso se llamo numero de simulaciones
    for (int i = 0; i < numSimulaciones; ++i) {
        if(opcion==1){simulacion_Bus_Tren(maxPasajeros);}
        else if (opcion==2){simulacion_Bus_Tren(maxPasajeros);}
        else if (opcion==3){simulacion_Vehiculo_Taxi(maxPasajeros);}
        else if (opcion==4){simulacion_Vehiculo_Taxi(maxPasajeros);}
    }
    return 0;
}

int estadisticas(){
    int opcion;
    do{
        printf("\n");
        printf("|---------------------------------|\n");
        printf("| 1. Mayor tiempo de recorrido    |\n");
        printf("|    Menor tiempo de recorrido    |\n");
        printf("| 2. Mayor distancia recorrida    |\n");
        printf("|    Menor distancia recorrida    |\n");           // Esta funcion representa un menu donde se presentan las opciones de estadisticas
        printf("| 3. Salir                        |\n");           // ya sea la mayor o menor distancia recorrida en las simulaciones o el mayor o menor
        printf("|---------------------------------|\n");           // tiempo de viajes segun las simulaciones hechas
        printf("Escoge opcion: ");
        scanf("%d", &opcion);

        if(opcion==1){resultDistancia();}
        else if (opcion==2){resultTiempo();}
        else if (opcion==3){ return 1;}
    }while(opcion<=3);
}

void heapDistancia(int distancia){
    int arr[10], no=3,  i, j, c, heap_root, temp;
    if(distancia>distanciaMayor){
        distanciaMenor = distanciaMayor;
        distanciaMayor = distancia;
    } else if (distancia<distanciaMenor){
        distanciaMenor = distancia;
    }
    for (i = 1; i <  no; i++)
    {
        c = i;
        do
        {
            heap_root  = (c - 1) / 2;
            if  (arr[heap_root] < arr[c])
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];         //Esta funcion ingresa los datos de las distancias recorridas en las simulaciones
                arr[c]  = temp;                  //los datos se ingresan al heap de maximos para despues ser llamados
            }
            c =  heap_root;
        } while (c !=  0);
    }
    for (j = no - 1; j  >= 0; j--)
    {
        temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        heap_root = 0;
        do
        {
            c = 2 *  heap_root + 1;
            if  ((arr[c] < arr[c + 1]) && c < j-1)
                c++;
            if  (arr[heap_root]<arr[c] && c<j)
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            heap_root  = c;
        } while (c  < j);
    }
}

void heapTiempo(int tiempo){
    int arr[10], no=3,  i, j, c, heap_root, temp;
    if(tiempo>=tiempoMayor){
        tiempoMenor = tiempoMayor;
        tiempoMayor = tiempo;
    } else if (tiempo<distanciaMenor){
        distanciaMenor = tiempoMenor;
    }
    for (i = 1; i <  no; i++)
    {
        c = i;
        do
        {
            heap_root  = (c - 1) / 2;
            if  (arr[heap_root] < arr[c])                //Esta funcion ingresa los datos de los tiempos de cada recorrido durante las simulaciones
            {                                            //los datos se ingresan al heap de maximos para despues ser llamados
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            c =  heap_root;
        } while (c !=  0);
    }
    for (j = no - 1; j  >= 0; j--)
    {
        temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        heap_root = 0;
        do
        {
            c = 2 *  heap_root + 1;
            if  ((arr[c] < arr[c + 1]) && c < j-1)
                c++;
            if  (arr[heap_root]<arr[c] && c<j)
            {
                temp =  arr[heap_root];
                arr[heap_root] = arr[c];
                arr[c]  = temp;
            }
            heap_root  = c;
        } while (c  < j);
    }
}

void resultDistancia(){
    printf("Mayor tiempo de recorrido: %d\nMenor tiempo de recorrido: %d",tiempoMayor,tiempoMenor); //Esta funcion imprime el resultado de las estadisticas sobre las distancias
}

void resultTiempo(){
    printf("Mayor distancia recorrida: %d\nMenor distancia recorrida: %d",distanciaMayor,distanciaMenor);//Esta funcion imprime el resultado de las estadisticas sobre los tiempos
}

void simulacion_Vehiculo_Taxi(int maxPasajeros){
    Nodo*aux=inicio;
    char a[TAMANO],b[TAMANO];
    int tiempo=0,distancia=0;
    int random_Pasajeros=rand()%maxPasajeros;
    fflush(stdin);
    printf("\nIngresar punto de inicio y destino:");         //esta funcion genera un recorrido implementado el metodo de dijsktra
    scanf("%s %s",&a,&b);                                    //se ingresan dos puntos, de donde se desea iniciar y hasta donde se desea llegar
    while(aux!=NULL){                                        //la funcion busca el recorrido mas corto, ademas calcula los tiempos de recorrido y la distancia
        if(strcmp(aux->lugar,a)==0){                         //total del recorrido para los taxis y los vehiculos personales
            aux->terminado=1;                                //los datos de distancia total y tiempo total se ingresan al heap para futuras estadisticas
            aux->monto=0;
            break;

        }
        aux=aux->siguiente;
    }
    if(aux==NULL){
        printf("\n---------------------\n");
        printf("\nAlguno de los lugares no ha sido registrado, aun\n");
        printf("\n---------------------\n");
        return;
    }
    while(aux!=NULL){
        Arista*a=aux->adyacencia;
        while(a!=NULL){
            if(a->vrt->monto==-1 || (aux->monto+a->peso)<a->vrt->monto){
                a->vrt->monto=aux->monto+a->peso;
                strcpy(a->vrt->anterior,aux->lugar);
                distancia = distancia + a->peso;
                tiempo = tiempo + a->tiempo;
            }
            a=a->siguiente;
        }
        aux=inicio;
        Nodo*min=inicio;
        while(strncmp(min->anterior,"0",1)==0 || min->terminado ==1)
            min=min->siguiente;
        while(aux!=NULL){
            if(aux->monto<min->monto && aux->terminado==0 && strncmp(aux->anterior,"0",1)!=0)
                min=aux;
            aux=aux->siguiente;
        }
        aux=min;
        aux->terminado=1;
        if(strcmp(aux->lugar,b)==0)
            break;
    }
    while(strncmp(aux->anterior,"0",1)!=0){
        insertarPila(aux);
        char temp[TAMANO];
        strcpy(temp,aux->anterior);
        aux=inicio;
        while(strcmp(aux->lugar,temp)!=0){
            aux=aux->siguiente;
        }
    }
    insertarPila(aux);
    printf("\nRecorrido\n");
    while(ini!=NULL){
        printf("%s ",desencolar()->lugar);
    }
    heapDistancia(distancia);
    heapTiempo(tiempo);
    printf("\n");
    printf("Distancia del viaje: %d\n",distancia);
    printf("Tiempo de viaje: %d\n",tiempo);
    printf("Numero de pasajeros: %d\n",random_Pasajeros);
    reiniciar();
}
