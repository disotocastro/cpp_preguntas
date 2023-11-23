#include <iostream> // Entrada y Salida de datos
#include <string> // Para usar cadenas de texto
#include <vector>
#include <fstream> // Entrada y salida de datos
#include <cstdlib> // Para usar rand() y srand()
#include <ctime>   // Para usar time()
#include <algorithm> // Para transform()
using namespace std;

/**
 * Short, Int, long = Numeros y numeros grandes enteros
 * String = Letras, muchas letras
 * Char = SOLO 1 letra
 * Bool = Verdadero/Falso
 * Float/Double = Numeros con decimales
 * 
*/

// Void = No retorna nada, solo hace una tarea
void ingresarJugadores() {
    string nombre;
    string cedula; // string porque vamos a recorrer los caracteres de la cedula
    int puntaje = 0;
    char opcion;

    do {
        cout << "Ingrese su nombre: ";
        cin >> nombre;

        cout << "Ingrese su número de cédula: ";
        cin >> cedula;

        // Verificación simple de si la cédula es numérica
        bool cedulaEsNumerica = true;
        for (int i = 0; i < cedula.length(); i++) {
            // Si la cedula no está entre 0 y 9
            if (!(cedula[i] >= '0' && cedula[i] <= '9')) {
                cedulaEsNumerica = false;
                break;
            }
        }

        if (!cedulaEsNumerica) {
            cout << "La cédula debe ser numérica. Intente nuevamente." << endl;
            continue; // Regresa al inicio del bucle
        }

        // Abrir archivo para escribir los datos
        ofstream archivo;
        archivo.open("jugadores.txt", ios::app); // Abrir el archivo
        if (archivo.is_open()) {
            archivo << "Nombre: " << nombre << ", Cédula: " << cedula << ", Puntaje: " << puntaje << "\n";
            archivo.close();
            cout << "Jugador agregado" << endl;
        } else {
            cout << "No se pudo abrir el archivo." << endl;
        }

        // Preguntar si se quiere agregar otro jugador
        cout << "¿Desea agregar otro jugador? (S/N): ";
        cin >> opcion;
    } while (opcion == 'S' || opcion == 's');
}

//Imprime el archivo de texto de jugadores
void reporteJugadores() {
   ifstream archivo("jugadores.txt");
   string linea;

   if (archivo.is_open()) {
      while (getline(archivo, linea)) {
         cout << linea << endl;
      }
      archivo.close();
   } else {
      cout << "No se pudo abrir el archivo." << endl;
   }
}

void jugar() {
   string cedula;
   cout << "¿Quién será el Jugador? Ingrese # de cédula: ";
   cin >> cedula;

   // Verificar si el jugador existe
   // ... (aquí iría la lógica para verificar si la cédula corresponde a un jugador registrado)
   // Por simplicidad, omitiremos esta parte.

   cout << "Jugador " << cedula << " ------> Número de Aciertos: 0" << endl;

   ifstream archivoPreguntas("preguntas.txt");
   vector <string> preguntas;
   string pregunta;

   if (archivoPreguntas.is_open()) {
      while (getline(archivoPreguntas, pregunta)) {
         preguntas.push_back(pregunta);
      }
      archivoPreguntas.close();
   } else {
      cout << "No se pudo abrir el archivo de preguntas." << endl;
      return; // Regresar al menú principal
   }

   // Respuestas correctas en el mismo orden que las preguntas en "preguntas.txt"
   std::vector<std::string> respuestasCorrectas = {
      "tronco", "boca", "ceja", "mejilla", "barbilla", "nariz", "ojos", "oreja", 
      "cabeza", "cuello", "dientes", "frente", "garganta", "lengua", "muelas", 
      "parpados", "pestañas", "pie", "pierna", "rodilla", "tobillo", "cadera", 
      "axila", "ombligo", "femur"
   };

   srand(time(NULL)); // Inicializar la semilla del generador de números aleatorios

   int oportunidadesCambio = 2;
   char opcionCambio;
   int numeroAciertos = 0; // Contador de aciertos

   do {
      int indicePregunta = rand() % preguntas.size();
      cout << "Pregunta: " << preguntas[indicePregunta] << endl;

      if (oportunidadesCambio > 0) {
         cout << "¿Desea cambiar la pregunta? (S/N): ";
         cin >> opcionCambio;
         if (opcionCambio == 'S' || opcionCambio == 's') {
               oportunidadesCambio--;
               continue;
         }
      }

      string respuesta;
      cout << "Ingrese la respuesta (true para verdadero, false para falso): ";
      cin >> respuesta;

      // Convertir la respuesta del usuario a minúsculas para comparación
      transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::tolower);

      // Comprobar si la respuesta es correcta
      bool respuestaCorrecta = (respuesta == respuestasCorrectas[indicePregunta]);
      if (respuestaCorrecta) {
         cout << "¡Respuesta correcta!" << endl;
         numeroAciertos++;
      } else {
         cout << "Respuesta incorrecta." << endl;
      }

      cout << "Número de Aciertos: " << numeroAciertos << endl;

      // Pregunta si quiere continuar jugando
      // ... (Aquí se podría agregar una lógica para continuar o no)

      break;
   } while (true);
}



int main()
{
   bool esta_corriendo = true;
   int opcion;

   while (esta_corriendo)
   {
      cout << "1. Ingresar jugadores" << endl;
      cout << "2. Jugar ¿Qué tanto sabes de las partes del cuerpo?" << endl;
      cout << "3. Reporte de jugadores" << endl;
      cout << "4. Los 10 mejores jugadores" << endl;
      cout << "5. Salir del programa" << endl;
      cout << "Ingrese una opcion: ";

      if (cin >> opcion)
      {
         cin.ignore(); // Limpiar el flujo de entrada

         switch (opcion)
         {
            case 1:
               ingresarJugadores();
               break;
            case 2:
               jugar();
               break;
            case 3:
               reporteJugadores();
               break;
            case 4:
               //top10();
               break;
            case 5:
               std::cout << "Cerrando programa..." << std::endl;
               esta_corriendo = false;
               break;
            default:
               cout << "Opción no válida, intente de nuevo." << endl;
               break;
         }
      }
   }

   return 0;
}
