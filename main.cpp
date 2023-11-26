//  Act 1.3 Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales
//  main.cpp
//
//  Created by  Isabella Valdez and José Manuel García on 20/09/2023.
//

#include "BSTNode.hpp"
#include "Busqueda.hpp"
#include "ConexionesComputadora.hpp"
#include "Ordenamiento.hpp"
#include "RegComun.hpp"
#include "Graph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Stack.hpp" 
#include "Queue.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


// NÚMERO DE REGISTROS
//  Elaborado por: José Manuel García
void numRegistros(const std::vector<RegComun> &bitacora) {
  std::cout << "\tEl número de registros del archivo es: " << bitacora.size()
            << std::endl;
  std::cout << std::endl;
}

// REGISTROS SEGUNDO DÍA
//  Elaborado por: José Manuel García
void registrosDia2(const std::vector<RegComun> &bitacora) {
  std::vector<RegComun> vectorSort =
      Ordenamiento<RegComun>::insercion(bitacora, RegComun::compareDateAsc);
  std::string dateSearch = vectorSort[0].getDate();
  int i = 1;
  for (; dateSearch == vectorSort[i].getDate(); ++i)
    ;
  dateSearch = vectorSort[i].getDate();
  std::cout << "\tEl segundo día es: " << dateSearch << std::endl;

  int recordSecondDay = 0;
  for (; dateSearch == vectorSort[i].getDate(); ++i) {
    ++recordSecondDay;
  }
  std::cout << "\tSe registraron " << recordSecondDay
            << " comunicaciones el segundo día" << std::endl;
  std::cout << std::endl;
}

// PERTENENCIA DE COMPUTADORAS
//  Elaborado por: José Manuel García
void duenoComp(const std::vector<RegComun> &bitacora) {
  std::vector<std::string> nameSearch = {
      "jeffrey.reto.com", "betty.reto.com",    "katherine.reto.com",
      "scott.reto.com",   "benjamin.reto.com", "samuel.reto.com",
      "raymond.reto.com"};
  std::string IpAdress;
  for (int i = 0; i < nameSearch.size(); ++i) {
    std::vector<int> resultName =
        Busqueda<RegComun>::busquedaSecuencial(bitacora, nameSearch[i]);

    if (resultName.empty()) {
      std::cout << "\t" << nameSearch[i] << " NO esta en ningun registro"
                << std::endl;
      std::cout << std::endl;
    } else {
      std::cout << "\t" << nameSearch[i] << " SI se encuentra "
                << resultName.size() << " en el registro" << std::endl;
      std::cout << "\tCon dirección IP: "
                << bitacora[resultName[10]].getipOrigin() << std::endl;
      // elegimos un numero del vector para no imprimir todos los registros
      // donde aparece el nombre
      IpAdress = bitacora[resultName[10]].getipOrigin();
      std::cout << std::endl;
    }
  }
}

// DIRECCIÓN DE RED INTERNA DE LA COMPAÑIA / CORRECCIÓN
//  Elaborado por: José Manuel García
std::string redInterna(const std::vector<RegComun> &bitacora) {
  std::string red = bitacora[15].getipOrigin();
  size_t firstDot = red.find('.');
  size_t secondDot = red.find('.', firstDot);
  std::string firstOct = red.substr(0, firstDot);
  std::string secondOct = red.substr(firstDot + 1, secondDot + 1);
  if (firstOct == "10") {
    size_t thirdDot = red.find('.', red.find('.', red.find('.') + 1) + 1);
    std::string redInterna = red.substr(0, thirdDot + 1);
    std::cout << "Red Interna clase A con dirección: " << redInterna
              << std::endl;
    return redInterna;
    std::cout << std::endl;
  } else if (firstOct == "172" && (secondOct > "15" && secondOct < "32")) {
    size_t thirdDot = red.find('.', red.find('.', red.find('.') + 1) + 1);
    std::string redInterna = red.substr(0, thirdDot + 1);
    std::cout << "Red Interna clase B con dirección: " << redInterna
              << std::endl;
    return redInterna;
    std::cout << std::endl;
  } else if (firstOct == "192" && secondOct == "168") {
    size_t thirdDot = red.find('.', red.find('.', red.find('.') + 1) + 1);
    std::string redInterna = red.substr(0, thirdDot + 1);
    std::cout << "Red Interna clase C con dirección: " << redInterna
              << std::endl;
    return redInterna;
    std::cout << std::endl;
  } else {
    std::cout << "Red interna desconocida" << std::endl;
    return red;
    std::cout << std::endl;
  }
}

// BUSCAR COMPUTADORA
//  Elaborado por: Isabella Valdez Galván
void buscarComputadora(const std::vector<RegComun> &bitacora) {
  std::string nombreBuscado = "server.reto.com";
  bool encontrado = false;
  for (const RegComun &registro : bitacora) {
    if (registro.getNameOrigin() == nombreBuscado) {
      encontrado = true;
      break;
    }
  }
  if (encontrado) {
    std::cout << "\tSe encontró al menos una computadora llamada '"
              << nombreBuscado << "' en los registros." << std::endl;
    std::cout << std::endl;
  } else {
    std::cout << "\tNo se encontró ninguna computadora llamada '"
              << nombreBuscado << "' en los registros." << std::endl;
    std::cout << std::endl;
  }
}

// SERVICIO DE CORREO ELÉCTRONICO UTILIZADO
//  Elaborado por: Isabella Valdez Galván
void servicioCorreo(const std::vector<RegComun> &bitacora) {
  std::vector<std::string> dominios;
  for (const RegComun &registro : bitacora) {
    if (registro.getNameDestiny() != "-") {
      dominios.push_back(registro.getNameDestiny());
    }
  }
  std::sort(dominios.begin(), dominios.end());
  if (dominios.empty()) {
    std::cout << "No hay dominios para analizar." << std::endl;
    return;
  }
  std::string dominioPrevio = dominios[0];
  int countActual = 1;
  int countMax = 1;
  std::string dominioFrecuente = dominioPrevio;
  for (size_t i = 1; i < dominios.size(); ++i) {
    if (dominios[i] == dominioPrevio) {
      countActual++;
      if (countActual > countMax) {
        countMax = countActual;
        dominioFrecuente = dominioPrevio;
      }
    } else {
      countActual = 1;
      dominioPrevio = dominios[i];
    }
  }
  std::cout << "\tEl dominio más repetido es: " << dominioFrecuente << " con "
            << countMax << " repeticiones" << std::endl;
}

// PUERTOS DESTINO MENORES A 1000
//  Elaborado por: Isabella Valdez Galván
void puertosMenores(const std::vector<RegComun> &bitacora) {
  std::set<int> menoresMil;
  for (const RegComun &registro : bitacora) {
    std::string puertoDestinoStr = registro.getDestinyPort();
    // Verificar si  es un número entero
    bool isNumeroEntero = true;
    for (char c : puertoDestinoStr) {
      if (!std::isdigit(c)) {
        isNumeroEntero = false;
        break;
      }
    }
    if (isNumeroEntero) {
      int puertoDestino = std::stoi(puertoDestinoStr);
      if (puertoDestino < 1000) {
        menoresMil.insert(puertoDestino);
      }
    }
  }
  if (!menoresMil.empty()) {
    for (int puerto : menoresMil) {
      std::cout << "\t" << puerto;
      if (puerto == 80) {
        std::cout << "\tProtocolo de Transferencia de Hipertexto." << std::endl;
      }
      if (puerto == 67) {
        std::cout << "\tDynamic Host Configuration Protocol." << std::endl;
      }
      if (puerto == 53) {
        std::cout << "\tDomain Name System." << std::endl;
      }
      if (puerto == 135) {
        std::cout << "\tMicrosoft Remote Procedure Call." << std::endl;
      }
      if (puerto == 443) {
        std::cout << "\tNavegador web." << std::endl;
      }
      if (puerto == 465) {
        std::cout << "\tProtocolo SMTPS." << std::endl;
      }
      if (puerto == 965) {
        std::cout << "\tPC Steam." << std::endl;
      }
      if (puerto == 993) {
        std::cout << "\tIMAP SSL ." << std::endl;
      }
    }
    std::cout << std::endl;
  } else {
    std::cout << "\tNo se encontraron puertos destino menores a 1000"
              << std::endl;
    std::cout << std::endl;
  }
}

// SEGUNDA ENTREGA
void conexionesPorIP(const std::vector<RegComun> &bitacora,
                     std::string redInterna) {
  std::string numberIP;
  std::cout << "\tIngrese el número de IP entre 1 y 150: ";
  std::cin >> numberIP;
  std::string octetoCompleto = redInterna + numberIP;
  std::cout << "\tDirección IP de la computadora: " << octetoCompleto
            << std::endl;

  ConexionesComputadora<RegComun> computadora(octetoCompleto, "");
  computadora.llenarConexiones(bitacora);

  // ULTIMA CONEXION ENTRANTE
  // Elaborado por: José Manuel García
  std::cout
      << "\tDirección IP de la ultima conexion que recibio esta computadora: "
      << computadora.ultimaConexionEntrante();
  std::string ultimaIp = computadora.ultimaConexionEntrante().getipOrigin();
  size_t thirdDotPos =
      ultimaIp.find('.', ultimaIp.find('.', ultimaIp.find('.') + 1) + 1);

  std::string internAdressComputer = ultimaIp.substr(0, thirdDotPos + 1);

  if (internAdressComputer == redInterna) {
    std::cout << "\tLa dirección IP es interna." << std::endl;
  } else {
    std::cout << "\tLa direción IP es externa." << std::endl;
  }

  // TOTAL CONEXIONES SALIENTES
  // Elaborado por: Isabella Valdez Galván
  std::cout << "\tTotal conexiones salientes de la computadora: "
            << computadora.totalConexionesSalientes() << std::endl;

  // TOTAL CONEXIONES ENTRANTES
  // Elaborado por: Isabella Valdez Galván
  std::cout << "\tTotal conexiones entrantes de la computadora: "
            << computadora.totalConexionesEntrantes() << std::endl;

  // TRES CONEXIONES CONSECUTIVAS
  // Elaborado por: José Manuel García
  if (computadora.tresConexionesConsecutivas() != nullptr) {
    std::cout
        << "\tLa computadora tiene 3 conexiones seguidas a: "
        << computadora.tresConexionesConsecutivas()->getInfo().getIpDestiny()
        << std::endl;
  } else {
    std::cout << "La computadora no tiene 3 conexiones seguidas" << std::endl;
    std::cout << std::endl;
  }
}

//TERCERA ENTREGA 
template <class T>
std::map<std::string, int> conexionesPorDia(std::vector<T> &registro,
                                            std::string dia) {
  std::map<std::string, int> conexiones;
  //Vector para guardar los registros del día
  std::vector<T> bitacoraPorFecha;

  for (auto &objeto : registro) {
    if (objeto.getDate() == dia) {
      bitacoraPorFecha.push_back(objeto);
    }
  }

  for (auto &objeto : bitacoraPorFecha) {
    std::string sitio = objeto.getNameDestiny();
    //Únicamente aumenta si el sitio no es - o reto.com
    if (sitio != "-" && sitio.find("reto.com") == std::string::npos) {
      conexiones[sitio]++;
    }
  }
  return conexiones;
}

template <class T>
void top(int n, const std::string &fecha, std::vector<T> &registros) {
  auto conexiones = conexionesPorDia(registros, fecha);

  if (conexiones.empty()) {
    std::cout << "Fecha no valida, intente de nuevo" << std::endl;
  } else {
    //Si hay conexiones, se agrega un nuevo nodo
    BSTNode<std::string, int> * sitiosBST = new BSTNode<std::string, int>();

    // Insertar elementos del map en el BST
    for (auto &par : conexiones) {
      sitiosBST->insertValue(par);
    }
    // Imprimir los top n elementos
    sitiosBST->printTopN(n);
     delete sitiosBST;
  }
}

template <class T, class K>
void sitioEnSubsecuentes(int n, std::vector<T>& fechas, std::vector<K>& registros){
//Vector que almacena los sitios que se encuentren en el "top n" de cada fecha
std::vector<T> sitios;

  for (auto& fecha : fechas) {
    auto conexiones = conexionesPorDia(registros, fecha);
    //BST para almacenar las conexiones del día y ordenarlas
    BSTNode<std::string, int> * sitiosBST = new BSTNode<std::string, int>();

    for (auto &par : conexiones) {
      sitiosBST->insertValue(par);
    }

    auto sitiosTop = sitiosBST->getTopSitios(n);

    for(auto& sitio : sitiosTop){
      sitios.push_back(sitio.first);
    }
    delete sitiosBST;
  }

  //Bucle para revisar si algún sitio aparece en todas las fechas subsecuentes
  int i = 0;
  int j = 1;
  while(i < sitios.size()){
    int count = 0;
    std::string actual = sitios[i];
    int requisito = fechas.size() - j;
    for (auto& element : sitios){
      if (actual == element){
        ++count;
      }
    }
    if (count == requisito){
      std::cout << "Sitios que aparecen un día y subsecuentes: "<< actual <<std::endl;
      break;
    }
    else{
      std::cout<<"No hay ningun sitio que cumpla esta condición"<<std::endl;
      break;
    }
    if (i%n == 0){
      j++;
      sitios.erase(sitios.begin(), sitios.begin()+n);
    }
    i++;
  }
}

template <class T, class K>
void sitioEnTodos(int n, std::vector<T>& fechas, std::vector<K>& registros){
  //Vector para almacenar los sitios que están en el top 'n' de cada fecha
  std::vector<T> sitios;

  //Bucle para iterar sobre cada fecha
  for (auto& fecha : fechas) {
    auto conexiones = conexionesPorDia(registros, fecha);

    // Crea un BST para ordenar las conexiones
    BSTNode<std::string, int> * sitiosBST = new BSTNode<std::string, int>();

    for (auto &par : conexiones) {
      sitiosBST->insertValue(par);
    }

    auto sitiosTop = sitiosBST->getTopSitios(n);

    for(auto& sitio : sitiosTop){
      sitios.push_back(sitio.first);
    }
    delete sitiosBST;
  }
   

  int i = 0;
  int j = 1;
  while(i < sitios.size()){
    int count = 0;
    std::string actual = sitios[i];
    int requisito = fechas.size() - j;
    for (auto& element : sitios){
      if (actual == element){
        ++count;
      }
    }
    if (count >= requisito){
      std::cout << "Sitios que aparecen todos los días: "<< actual <<std::endl;
      break;
    }
    else{
      std::cout<<"Ningun sitio se repite todos los dias"<<std::endl;
      break;
    }
    if (i%n == 0){
      j++;
      sitios.erase(sitios.begin(), sitios.begin()+n);
    }
    i++;
  }
}

template <class T, class K>
int mediaDeConexiones(int topN, const std::vector<T>& fechas, std::vector<K>& registro) {
  int sumaDeConexiones = 0;
  int totalSitios = 0;
  for (auto& fecha : fechas){
    // Mapa de conexiones para la fecha actual 
    auto conexiones = conexionesPorDia(registro, fecha);

    BSTNode<std::string, int> * sitiosBST = new BSTNode<std::string, int>();

    for (auto& par : conexiones){
      sitiosBST->insertValue(par);
    }

    auto topSitios = sitiosBST->getTopSitios(topN);
    totalSitios+=topSitios.size();
    
    for (auto& par : topSitios){
      sumaDeConexiones += par.second;
    }
    delete sitiosBST;
  }
  return sumaDeConexiones / totalSitios;
}


template <class T, class K>
void sitioConMayorFrecuencia(int topN, const std::vector<T>& fechas, std::vector<K>& registro){
  // Mapa para almacenar el sitio con mayor frecuencia por fecha
  std::map<std::string, std::string> sitiosConMayorFrecuencia;

  int media = mediaDeConexiones(topN, fechas, registro);
  std::cout<<"Media de conexiones: "<<media<<std::endl;

  for (auto& fecha : fechas){
    auto conexiones = conexionesPorDia(registro, fecha);

    for (auto& par : conexiones){
      if (par.second > media){
        sitiosConMayorFrecuencia[fecha] = par.first;
      }
    }
  }

  for (auto& sitio : sitiosConMayorFrecuencia){
    std::cout<<sitio.first<<": "<<sitio.second<<std::endl;
  }
}


template <class T, class K>
void conexionesSalientes_V(std::vector<K>& fechas, std::string vertexToSearch, Graph<T,K> * grafoIp){

  auto verticeBuscado = grafoIp->search(vertexToSearch);
    if (verticeBuscado == nullptr){
        std::cout << "No se encontró el vertice" << std::endl;
    }
    else{

    auto vectorEdges = verticeBuscado->getEdges();
    
    std::map<std::string, int> edgesFechas;

    for (auto fecha : fechas){
      for (auto edge : *vectorEdges){
        if (edge->getInfo() == fecha){
          edgesFechas[fecha]++;
         }
       }
     }

     std:: cout << "Conexiones salientes de " << vertexToSearch << " por fecha: " << std::endl;
      for (auto edge : edgesFechas){
        std::cout << edge.first << ": " << edge.second << std::endl;
      }

    std::cout << "Conexiones salientes totales de " << vertexToSearch << ": " << verticeBuscado->getConexionesSalientes() << std::endl;

   }
}

template <class T, class K>
void conexionesEntrantes_V(std::vector<K>& fechas, std::string vertexToSearch, Graph<T,K> * grafoIp){

  auto verticeBuscado = grafoIp->search(vertexToSearch);
    if (verticeBuscado == nullptr){
        std::cout << "No se encontró el vertice" << std::endl;
    }
    else{

    auto vectorEdges = verticeBuscado->getEdgesEntrantes();
    
    std::map<std::string, int> edgesFechas;

    for (auto fecha : fechas){
      for (auto edge : *vectorEdges){
        if (edge->getInfo() == fecha){
          edgesFechas[fecha]++;
         }
       }
     }

     std:: cout << "Conexiones entrantes de " << vertexToSearch << " por fecha: " << std::endl;
      for (auto edge : edgesFechas){
        std::cout << edge.first << ": " << edge.second << std::endl;
      }

    std::cout << "Conexiones entrantes totales de " << vertexToSearch << ": " << verticeBuscado->getConexionesEntrantes() << std::endl;

   }
}

/* Creación de grafo por dia para IP */
/* Conexiones entre ip con red interna solamente*/
template <class T, class K>
void grafoIP(std::vector<T>& bitacora, std::vector<K>& fechas, std::string redInterna, std::string ipVertex){

    /* Crear el grafo */
    Graph<std::string, std::string> * grafoIp = new Graph<std::string, std::string>();

    for (int i = 0; i < bitacora.size() ; i++){

        std::string IpOrigen = bitacora[i].getipOrigin();
        /* Verifica si la conexión pertenece a la red interna */
        if (IpOrigen.find(redInterna) != std::string::npos){

            size_t last_dot = IpOrigen.find_last_of(".");
            std::string IpOrigenSub = IpOrigen.substr(last_dot);
            /* std::cout << "IpOrigenSub: " << IpOrigenSub << std::endl; */

            /* Agrega el Vertex al grafo con validación */
            Vertex<std::string, std::string> * verticeIpOrigen = new Vertex<std::string, std::string>(IpOrigenSub);
            
            /* Validar si el vertex ya existe */
            Vertex<std::string, std::string> * vOrigen = grafoIp->search(verticeIpOrigen);
            if (vOrigen == nullptr){
                vOrigen = verticeIpOrigen;
                grafoIp->addVertex(verticeIpOrigen);
            }
            
            
            /* Search busca si vertex existe o si esta en grafo ?*/

            std::string IpDestino = bitacora[i].getIpDestiny();

            if (IpDestino.find(redInterna) != std::string::npos){
            size_t last_dot = IpDestino.find_last_of(".");
            std::string IpDestinoSub = IpDestino.substr(last_dot);
            /* std::cout << "IpDestinoSub: " << IpDestinoSub << std::endl; */

            Vertex<std::string, std::string> * verticeIpDestino = new Vertex<std::string, std::string>(IpDestinoSub);
                
                /* Validar si el vertex ya existe */
                Vertex<std::string, std::string> * vDestino = grafoIp->search(verticeIpDestino);
                if (vDestino == nullptr){
                    vDestino = verticeIpDestino;
                    grafoIp->addVertex(verticeIpDestino);
                }

            grafoIp->addEdge(vOrigen, vDestino, bitacora[i].getDate());

            }
        }
    }

    /* std::cout << *grafoIp << std::endl; */
    conexionesSalientes_V(fechas, ipVertex, grafoIp);
    grafoIp->maxConexionesSalientes();
    conexionesEntrantes_V(fechas, ipVertex, grafoIp);
    
    delete grafoIp;
}

template <class T, class K>
void grafoSitiosWeb(std::vector<T>& bitacora, std::vector<K>& fechas, std::string sitioRaro, std::string sitioConMasconexiones){

  Graph<std::string, std::string> * grafoSitios = new Graph<std::string, std::string>();

  for (int i = 0; i < bitacora.size() ; i++){
    std::string sitioOrigen = bitacora[i].getNameOrigin();

    if (bitacora[i].getDestinyPort() == "443" || bitacora[i].getDestinyPort() == "80"){

      Vertex<std::string, std::string> * verticeSitioOrigen = new Vertex<std::string, std::string>(sitioOrigen);

      Vertex<std::string, std::string> * vOrigen = grafoSitios->search(verticeSitioOrigen);

      if (vOrigen == nullptr){
        vOrigen = verticeSitioOrigen;
        grafoSitios->addVertex(vOrigen);
      }

      std::string sitioDestino = bitacora[i].getNameDestiny();

      Vertex<std::string, std::string> * verticeSitioDestino = new Vertex<std::string, std::string>(sitioDestino);

      Vertex<std::string, std::string> * vDestino = grafoSitios->search(verticeSitioDestino);

      if (vDestino == nullptr){
        vDestino = verticeSitioDestino;
        grafoSitios->addVertex(vDestino);
      }

      grafoSitios->addEdge(vOrigen, vDestino, bitacora[i].getDate());

    }
  }

  //std::cout << * grafoSitios << std::endl;
  conexionesEntrantes_V(fechas, sitioRaro, grafoSitios);
  conexionesEntrantes_V(fechas, sitioConMasconexiones, grafoSitios);
  conexionesSalientes_V(fechas, sitioConMasconexiones, grafoSitios);

  delete grafoSitios;
}


template <class T>
std::map<std::string, std::string> mapSitiosAndIp(std::vector<T>& bitacora){
  std::map<std::string, std::string> sitiosAndIp;

  for(int i = 0; i < bitacora.size() ; ++i){
    std::string sitioOrigen = bitacora[i].getNameOrigin();
    std::string sitioDestino = bitacora[i].getNameDestiny();

    if(sitioOrigen.find("reto.com") == std::string::npos && sitioOrigen != "-"){
      sitiosAndIp[sitioOrigen] = bitacora[i].getipOrigin();
    }

    if (sitioDestino.find("reto.com") == std::string::npos && sitioDestino != "-"){
      sitiosAndIp[sitioDestino] = bitacora[i].getIpDestiny();
    } 

  }

  /* Imprimir el map para inspección visual */
  for (auto sitio : sitiosAndIp){
    std::cout << sitio.first << ": " << sitio.second << std::endl;
  }

  std::string sitioRaro = "d9m4ssttaj1zte5bldt5.xxx";
  /*Se encunetra la IP del sitio raro en complejidad constante */
  std::cout << "Dirección IP del sitio raro: " << sitiosAndIp[sitioRaro] << std::endl;

  return sitiosAndIp;
}


template <class T, class K>
std::map<K, ConexionesComputadora<T>> mapIpAndObjeto(std::vector<T>& bitacora, K redInterna) {
    std::map<std::string, ConexionesComputadora<T>> ipAndObjeto;

    for (int i = 0; i < bitacora.size() ; ++i){
        std::string ipOrigen = bitacora[i].getipOrigin();
        std::string ipDestino = bitacora[i].getIpDestiny();

        if (ipAndObjeto.find(ipOrigen) == ipAndObjeto.end()) {
            ConexionesComputadora<T> computadoraOrigen(ipOrigen, bitacora[i].getNameOrigin());
            computadoraOrigen.llenarConexiones(bitacora);
            ipAndObjeto[ipOrigen] = computadoraOrigen;
        }

        if (ipAndObjeto.find(ipDestino) == ipAndObjeto.end()) {
            ConexionesComputadora<T> computadoraDestino(ipDestino, bitacora[i].getNameDestiny());
            computadoraDestino.llenarConexiones(bitacora);
            ipAndObjeto[ipDestino] = computadoraDestino;
        }
    }

  /*
    for (auto& ip : ipAndObjeto){
        std::cout << ip.first << ": " << ip.second.totalConexionesSalientes() << std::endl;
    }
    */

   std::map<std::string, ConexionesComputadora<T>> conexionesEntrantes;

   for (auto& ip : ipAndObjeto){
    std::string ip_buscada = ip.first;

    if (ip_buscada.find(redInterna) != std::string::npos){

      if (ip.second.totalConexionesEntrantes() > 0){
        conexionesEntrantes[ip.first] = ip.second;
      }
    }
   }

  std::cout << "Computadoras con más de una conexion entrante pertenecientes a reto.com: " << conexionesEntrantes.size() << std::endl;

  return conexionesEntrantes;
    
}

template <class T, class K>
void mapIpUnicasConexiones(std::vector<T>& bitacora, K redInterna){
  std::map < std::string, ConexionesComputadora<T>> ipAndObjeto;

  for (int i = 0; i < bitacora.size(); ++i){
    std::string ipOrigen = bitacora[i].getipOrigin();
    std::string ipDestino = bitacora[i].getIpDestiny();
    std::string puertoOrigen = bitacora[i].getPortOrigin();
    std::string puertoDestino = bitacora[i].getDestinyPort();

    if ((ipOrigen != "-" && ipOrigen.find(redInterna) == std::string::npos) && (puertoDestino != "67" || puertoDestino != "68")){
      if (ipAndObjeto.find(ipOrigen) == ipAndObjeto.end()){
        ConexionesComputadora<T> computadoraOrigen(ipOrigen, bitacora[i].getNameOrigin());
        computadoraOrigen.llenarConexiones(bitacora);
        ipAndObjeto[ipOrigen] = computadoraOrigen;
      }
    }

    if ((ipDestino != "-" && ipDestino.find(redInterna) == std::string::npos) && (puertoOrigen != "67" || puertoOrigen != "68")){
      if (ipAndObjeto.find(ipDestino) == ipAndObjeto.end()){
        ConexionesComputadora<T> computadoraDestino(ipDestino, bitacora[i].getNameDestiny());
        computadoraDestino.llenarConexiones(bitacora);
        ipAndObjeto[ipDestino] = computadoraDestino;
      }
    }
  }

  std::cout << "Map IP que no pertenecen a reto.com ni servidor DHCP " << std::endl;

  for (auto& ip : ipAndObjeto){
    std::cout << ip.first << ": " << ip.second.totalConexionesEntrantes() << std::endl;
  }

  std::set < std::string > ipUnicas;

  for (int j = 0; j < 6 ; j++){
    Stack<T> * conexionesEntrantes = new Stack<T>();
    conexionesEntrantes = ipAndObjeto.begin()->second.getConexionesEntrantes();

    while (!conexionesEntrantes->empty()){
      auto ip = conexionesEntrantes->top()->getInfo().getipOrigin();
      ipUnicas.insert(ip);
      conexionesEntrantes->pop();
    }

    typename std::map<std::string, ConexionesComputadora<T>> ::iterator it = ipAndObjeto.begin();
    ipAndObjeto.erase(it);
  }
  std::cout << std::endl;
  std::cout << "Ip únicas entrantes a computadoras que no pertenecen a reto.com ni servidor DHCP: " << std::endl;
  for (auto& ip : ipUnicas){
    std::cout << ip << std::endl;
  }

  std::map<std::string, std::string> sitiosAndIpRaro = mapSitiosAndIp(bitacora);

  std::map<K, ConexionesComputadora<T>> conexionesEntrantesSitiosReto = mapIpAndObjeto(bitacora, redInterna);

  for (auto& ip : ipUnicas){
    for (auto& ipReto : conexionesEntrantesSitiosReto){
      if (ip == ipReto.first){
        Queue<T> * conexionesSalientes = new Queue<T>();
        conexionesSalientes = ipReto.second.getConexionesSalientes();
        while (!conexionesSalientes->empty()){
          auto sitio = conexionesSalientes->last()->getInfo().getIpDestiny();
          if (sitiosAndIpRaro.find(sitio) != sitiosAndIpRaro.end()){
            std::cout << "La ip reto: " << ip << " se conecto al sitio:  " << sitiosAndIpRaro[sitio] << std::endl;
          }
          conexionesSalientes->dequeue();
        }
      }
    }
  }
  
}





int main() {
  // Declaración de variables y objetos
  std::vector<RegComun> bitacora;
  std::vector<std::string> variables(8);
  std::string lineContained;
  std::string wordContained;
  std::ifstream fileBitacora;
  std::string red;
  int line = 0;
  std::string dia;
  std::map<std::string, int> conexionesDia;
  std::string fecha;
  std::vector<std::string> fechas;
  std::string sitioT;
  std::string sitioB;
  std::string sitioC;
  std::string ipA;

  // Apertura, lectura y procesamiento del archivo CSV
  fileBitacora.open("equipo12.csv");
  while (std::getline(fileBitacora, lineContained)) {
    std::stringstream ss(lineContained);
    int column = 0;
    while (std::getline(ss, wordContained, ',')) {
      variables[column] = wordContained;
      ++column;
    }
    RegComun recordComunication(variables[0], variables[1], variables[2],variables[3], variables[4], variables[5],variables[6], variables[7]);
    bitacora.push_back(recordComunication);
    ++line;
  }
  fileBitacora.close();

  for (const auto &registro : bitacora) {
    fecha = registro.getDate();
    if (find(fechas.begin(), fechas.end(), fecha) == fechas.end()) {
      fechas.push_back(fecha);
    }
  }
  
  while (true) {
    std::cout << std::endl << std::string(54, '-') << std::endl;
    std::cout << std::string(25, '-') << "MENÚ" <<std::string(25, '-') << std::endl;
    std::cout << "Seleccione una opción:" << std::endl;
    std::cout << "PRIMERA ENTREGA" << std::endl;
    std::cout << "1.  Número de registros" << std::endl;
    std::cout << "2.  Registros segundo día" << std::endl;
    std::cout << "3.  Pertenencia de computadoras" << std::endl;
    std::cout << "4.  Red interna de la compañia" << std::endl;
    std::cout << "5.  Buscar computadora" << std::endl;
    std::cout << "6.  Servicio de correo electrónico" << std::endl;
    std::cout << "7.  Puertos destino menores a 1000" << std::endl;
    std::cout << "\nSEGUNDA ENTREGA" << std::endl;
    std::cout << "8.  Conexiones por IP" << std::endl;
    std::cout << "\nTERCERA ENTREGA" << std::endl;
    std::cout << "9.  Obtener MAP de conexiones por día" << std::endl;
    std::cout << "10. Conexiones por dia seleccionado" << std::endl;
    std::cout << "11. Top 5 sitios con más conexiones por día" << std::endl;
    std::cout << "12. Sitio en el top 5 todos los días " << std::endl;
    std::cout << "13. Sitio que entre al top 5 y permanezca" << std::endl;
    std::cout << "14. Sitio en el top 5 con más trafico que lo normal" << std::endl;
    std::cout << "15. Respuesta pregunta 1 y 2" << std::endl;
    std::cout << "16. Respuesta pregunta 3 y 4" << std::endl;
    std::cout << "17. Salir" << std::endl;
    std::cout << "Opción: ";

    int opcion;
    std::cin >> opcion;
    std::cout << std::endl;
    switch (opcion) {
    case 1:
      numRegistros(bitacora);
      break;
    case 2:
      registrosDia2(bitacora);
      break;
    case 3:
      duenoComp(bitacora);
      break;
    case 4:
      red = redInterna(bitacora);
      break;
    case 5:
      buscarComputadora(bitacora);
      break;
    case 6:
      servicioCorreo(bitacora);
      break;
    case 7:
      puertosMenores(bitacora);
      break;
    case 8:
      conexionesPorIP(bitacora, red);
      break;
    case 9:
      std::cout << "Ingrese el día, en formato DD-MM-AAAA: " << std::endl;
      std::cin >> dia;
      conexionesDia = conexionesPorDia(bitacora, dia);
      std::cout << "Map guardado correctamente" << std::endl;
      break;
    case 10:
      std::cout << "Ingrese el día, en formato DD-MM-AAAA: " << std::endl;
      std::cin >> dia;
      std::cout << "Top 5 sitios con más conexiones "
                << "en: " << dia << std::endl;
      top(5, dia, bitacora);
      break;
    case 11:
      std::cout << "Top 5 sitios con más conexiones por día" << std::endl;

      for (int i = 0; i < fechas.size(); ++i) {
        std::cout << "Fecha: " << fechas[i] << ": " << std::endl;
        std::cout << std::endl;
        top(5, fechas[i], bitacora);
        std::cout << std::endl;
      }
      break;
    case 12:
      sitioEnTodos(5, fechas, bitacora);
      break;
    case 13:
      sitioEnSubsecuentes(5, fechas, bitacora);
      break;
    case 14:
      std::cout << "Sitios con más conexiones de lo normal: " << std::endl;
      sitioConMayorFrecuencia(5, fechas, bitacora);
      break;
    case 15:
      std::cout << "Respuesta pregunta 1 y 2" << std::endl;
      ipA = ".25";
      std::cout << "Dirección IP elegida: 10.222.50" << ipA << std::endl;
      red = redInterna(bitacora);
      grafoIP(bitacora, fechas, red, ipA);
      
      break;
    case 16:
        std::cout << "Respuesta pregunta 3 y4 " << std::endl;
        sitioB = "d9m4ssttaj1zte5bldt5.xxx";
        sitioC = "craigslist.org"; /*verficar este sitio */
        std::cout << "sitio elegido B: " << sitioB << std::endl;
        std::cout << "sitio elegido C: " << sitioC << std::endl;
        grafoSitiosWeb(bitacora, fechas, sitioB, sitioC);
        break;
    
    case 17:
      std::cout << "Map sitios y IP" <<std::endl;
      //mapSitiosAndIp(bitacora, fechas);

      break;
    case 18:
      std::cout << "Map ip y conexiones" <<std::endl;
      red=redInterna(bitacora);
      //mapIpAndObjeto(bitacora, red);
      break;
    case 19:
      std::cout << "Map ip unicas y conexiones" <<std::endl;
      red=redInterna(bitacora);
      mapIpUnicasConexiones(bitacora, red);
      break;
    case 20:
        std::cout << "Adios" << std::endl;
        return 0;
    default:
      std::cout << "Opción no válida." << std::endl;
    }
  }
  return 0;
}


