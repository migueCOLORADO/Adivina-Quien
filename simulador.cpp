#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Estructura para cada sospechoso
struct Sospechoso {
    string nombre;
    string cabello;
    string genero;
    bool anteojos;
    string velloFacial;
    Sospechoso* siguiente;
};

// Clase para manejar la lista enlazada
class ListaSospechosos {
private:
    Sospechoso* cabeza;
    string sospechosoObjetivo;
    int puntaje;
    int intentos;

public:
    // Constructor
    ListaSospechosos() {
        cabeza = nullptr;
        puntaje = 0;
        intentos = 0;
        srand(time(0));
    }

    // Agregar sospechoso al inicio de la lista
    void agregar(string nombre, string cabello, string genero, bool anteojos, string vello) {
        Sospechoso* nuevo = new Sospechoso;
        nuevo->nombre = nombre;
        nuevo->cabello = cabello;
        nuevo->genero = genero;
        nuevo->anteojos = anteojos;
        nuevo->velloFacial = vello;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    // Limpiar toda la lista
    void limpiarLista() {
        while (cabeza != nullptr) {
            Sospechoso* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    // Reiniciar el juego con nuevos sospechosos
    void reiniciarJuego() {
        limpiarLista();
        
        // Agregar sospechosos nuevamente
        agregar("Ana", "Rubio", "Femenino", false, "No tiene");
        agregar("Carlos", "Castano", "Masculino", true, "Barba negra");
        agregar("Sofia", "Negro", "Femenino", false, "No tiene");
        agregar("Diego", "Calvo", "Masculino", false, "Bigote castano");
        agregar("Laura", "Rubio", "Femenino", true, "No tiene");
        agregar("Javier", "Pelirrojo", "Masculino", true, "Barba pelirroja");
        agregar("Maria", "Castano", "Femenino", false, "No tiene");
        agregar("Pablo", "Negro", "Masculino", true, "Barba negra");
        agregar("Elena", "Pelirrojo", "Femenino", false, "No tiene");
        agregar("Miguel", "Rubio", "Masculino", false, "Barba rubia");
        
        seleccionarObjetivo();
        cout << "\n=== NUEVA RONDA INICIADA ===" << endl;
        cout << "Nuevo sospechoso objetivo seleccionado!" << endl;
    }

    // Seleccionar sospechoso objetivo aleatoriamente
    void seleccionarObjetivo() {
        int total = contar();
        if (total == 0) return;
        
        int posicionAleatoria = rand() % total;
        Sospechoso* actual = cabeza;
        
        for (int i = 0; i < posicionAleatoria; i++) {
            actual = actual->siguiente;
        }
        
        sospechosoObjetivo = actual->nombre;
        cout << "\nSospechoso objetivo seleccionado secretamente!" << endl;
        cout << "Pista: El agente doble esta en la lista..." << endl;
    }

    // Mostrar todos los sospechosos
    void mostrarTodos() {
        Sospechoso* actual = cabeza;
        int contador = 1;
        
        cout << "\n=== SOSPECHOSOS RESTANTES ===" << endl;
        while (actual != nullptr) {
            cout << contador << ". " << actual->nombre 
                 << " - Cabello: " << actual->cabello
                 << " - Genero: " << actual->genero
                 << " - Anteojos: " << (actual->anteojos ? "Si" : "No")
                 << " - Vello: " << actual->velloFacial << endl;
            actual = actual->siguiente;
            contador++;
        }
        cout << "Total: " << (contador-1) << " sospechosos" << endl;
    }

    // Verificar si el sospechoso objetivo sigue en la lista
    bool objetivoEnLista() {
        Sospechoso* actual = cabeza;
        while (actual != nullptr) {
            if (actual->nombre == sospechosoObjetivo) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    // Adivinar directamente el sospechoso (NO termina el juego)
    void adivinarSospechoso(string nombre) {
        intentos++;
        
        if (nombre == sospechosoObjetivo) {
            cout << "\nCORRECTO! " << nombre << " es el agente doble!" << endl;
            cout << "Has ganado esta ronda!" << endl;
            puntaje += 10;
            cout << "Puntaje actual: " << puntaje << " puntos" << endl;
            cout << "Intentos en esta ronda: " << intentos << endl;
            
            // Reiniciar para nueva ronda
            intentos = 0;
            reiniciarJuego();
        } else {
            cout << "\nIncorrecto! " << nombre << " no es el agente doble." << endl;
            cout << "Sigue intentando! Puedes usar filtros o adivinar de nuevo." << endl;
            cout << "Intentos fallidos: " << intentos << endl;
        }
    }

    // Filtrar por género
    void filtrarPorGenero(string genero) {
        Sospechoso* actual = cabeza;
        Sospechoso* anterior = nullptr;
        int eliminados = 0;

        while (actual != nullptr) {
            if (actual->genero != genero) {
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                Sospechoso* temp = actual;
                actual = actual->siguiente;
                delete temp;
                eliminados++;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        
        cout << "Eliminados " << eliminados << " sospechosos que no son " << genero << endl;
        
        // Verificar si eliminamos al objetivo
        if (!objetivoEnLista()) {
            cout << "Oh no! Eliminaste al agente doble de la lista." << endl;
            cout << "El agente doble era: " << sospechosoObjetivo << endl;
            cout << "Iniciando nueva ronda..." << endl;
            intentos = 0;
            reiniciarJuego();
        }
    }

    // Filtrar por anteojos
    void filtrarPorAnteojos(bool tieneAnteojos) {
        Sospechoso* actual = cabeza;
        Sospechoso* anterior = nullptr;
        int eliminados = 0;

        while (actual != nullptr) {
            if (actual->anteojos != tieneAnteojos) {
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                Sospechoso* temp = actual;
                actual = actual->siguiente;
                delete temp;
                eliminados++;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        
        string mensaje = tieneAnteojos ? "usan anteojos" : "no usan anteojos";
        cout << "Eliminados " << eliminados << " sospechosos que " << mensaje << endl;
        
        if (!objetivoEnLista()) {
            cout << "Oh no! Eliminaste al agente doble de la lista." << endl;
            cout << "El agente doble era: " << sospechosoObjetivo << endl;
            cout << "Iniciando nueva ronda..." << endl;
            intentos = 0;
            reiniciarJuego();
        }
    }

    // Filtrar por color de cabello
    void filtrarPorCabello(string cabello) {
        Sospechoso* actual = cabeza;
        Sospechoso* anterior = nullptr;
        int eliminados = 0;

        while (actual != nullptr) {
            if (actual->cabello != cabello) {
                if (anterior == nullptr) {
                    cabeza = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                Sospechoso* temp = actual;
                actual = actual->siguiente;
                delete temp;
                eliminados++;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        
        cout << "Eliminados " << eliminados << " sospechosos que no tienen cabello " << cabello << endl;
        
        if (!objetivoEnLista()) {
            cout << "Oh no! Eliminaste al agente doble de la lista." << endl;
            cout << "El agente doble era: " << sospechosoObjetivo << endl;
            cout << "Iniciando nueva ronda..." << endl;
            intentos = 0;
            reiniciarJuego();
        }
    }

    // Contar sospechosos restantes
    int contar() {
        int count = 0;
        Sospechoso* actual = cabeza;
        while (actual != nullptr) {
            count++;
            actual = actual->siguiente;
        }
        return count;
    }

    // Mostrar estadísticas
    void mostrarEstadisticas() {
        cout << "\n=== ESTADISTICAS ===" << endl;
        cout << "Puntaje total: " << puntaje << " puntos" << endl;
        cout << "Intentos en ronda actual: " << intentos << endl;
        cout << "Sospechosos restantes: " << contar() << endl;
    }

    // Verificar si solo queda un sospechoso
    bool soloQuedaUno() {
        return contar() == 1 && objetivoEnLista();
    }

    // Destructor
    ~ListaSospechosos() {
        limpiarLista();
    }
};

int main() {
    ListaSospechosos lista;
    
    cout << "Bienvenido al juego del Agente Doble!" << endl;
    cout << "Tu mision: Encontrar al agente doble haciendo preguntas" << endl;
    cout << "Puedes adivinarlo directamente o usar filtros" << endl;
    cout << "Si aciertas, inicias nueva ronda. Si fallas, sigues jugando!" << endl;
    
    // Inicializar juego
    lista.reiniciarJuego();
    
    int opcion;
    do {
        if (lista.soloQuedaUno()) {
            cout << "\nFELICIDADES! Solo queda un sospechoso:" << endl;
            lista.mostrarTodos();
            cout << "Has encontrado al agente doble automaticamente!" << endl;
            cout << "Iniciando nueva ronda..." << endl;
            lista.reiniciarJuego();
            continue;
        }
        
        cout << "\n=== MENU ===" << endl;
        cout << "1. Ver sospechosos restantes" << endl;
        cout << "2. Filtrar por genero" << endl;
        cout << "3. Filtrar por anteojos" << endl;
        cout << "4. Filtrar por color de cabello" << endl;
        cout << "5. ADIVINAR SOSPECHOSO" << endl;
        cout << "6. Ver estadisticas" << endl;
        cout << "7. Nueva ronda manual" << endl;
        cout << "8. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                lista.mostrarTodos();
                break;
                
            case 2: {
                string genero;
                cout << "Es Masculino o Femenino? ";
                cin >> genero;
                lista.filtrarPorGenero(genero);
                break;
            }
            
            case 3: {
                char respuesta;
                cout << "Usa anteojos? (s/n): ";
                cin >> respuesta;
                bool anteojos = (respuesta == 's' || respuesta == 'S');
                lista.filtrarPorAnteojos(anteojos);
                break;
            }
            
            case 4: {
                string cabello;
                cout << "Color de cabello (Rubio/Castano/Negro/Pelirrojo/Calvo): ";
                cin >> cabello;
                lista.filtrarPorCabello(cabello);
                break;
            }
            
            case 5: {
                string nombre;
                cout << "Quien crees que es el agente doble? ";
                cin >> nombre;
                lista.adivinarSospechoso(nombre);
                break;
            }
            
            case 6:
                lista.mostrarEstadisticas();
                break;
                
            case 7:
                cout << "Iniciando nueva ronda..." << endl;
                lista.reiniciarJuego();
                break;
            
            case 8:
                cout << "Gracias por jugar!" << endl;
                lista.mostrarEstadisticas();
                break;
                
            default:
                cout << "Opcion no valida." << endl;
        }
        
    } while (opcion != 8);
    
    return 0;
}