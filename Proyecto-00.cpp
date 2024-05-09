#include <iostream>
#include <locale>
#include <clocale>
#include <conio.h>
#include "PriorityQueue.h" 
#include "TipoUsuario.h"
#include "HeapPriorityQueue.h"
#include "Area.h"
#include "Control.h"
#include "TipoUsuarioClientes.h"
#include <vector>


using namespace std;
using std::string;

#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

extern "C" {
    __declspec(dllimport) int __stdcall SetConsoleCursorPosition(void*, struct COORD);
    __declspec(dllimport) void* __stdcall GetStdHandle(int);
}

// Define COORD structure manually
struct COORD {
    short X;
    short Y;
};

// Define function prototype for gotoxy
void gotoxy(int x, int y);

// Implementation of gotoxy function
void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(-11), coord); // STD_OUTPUT_HANDLE = -11
}

/*
settings
*/
int ticketCounter = 100;
int priorityLvlsUsers = 5;

/*
* listas de administrador para los tipos disponibles
*/
Control* controlPrincipal = new Control();

int menu(const char* titulo, const char* opciones[], int n) {
    int opcionSelect = 1;
    int tecla;
    bool on = true;

    do {
        system("cls");
        gotoxy(5, 3 + opcionSelect); cout << "==>";
        gotoxy(15, 2); cout << titulo;

        for (int i = 0; i < n; i++) {
            gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
        }

        do {
            tecla = _getch();
        } while (tecla != TECLA_ARRIBA && tecla != TECLA_ABAJO && tecla != ENTER);

        switch (tecla) {
        case TECLA_ARRIBA:
            opcionSelect--;
            if (opcionSelect == 0) {
                opcionSelect = n;
            }
            break;
        case TECLA_ABAJO:
            opcionSelect++;
            if (opcionSelect > n) {
                opcionSelect = 1;
            }
            break;
        case ENTER:
            on = false;
            break;
        }

    } while (on);

    return opcionSelect;
}
void agregarTipoUsuario() {
    
    string descripcion;
    int prioridad;

    system("cls");    
    cout << "\n\t\t\Agregar Tipo de Usuario" << endl;
    cout << "\n\tDescripción: ";
    cin.ignore();
    getline(cin, descripcion);
    cout << "\n\tPrioridad: ";
    cin >> prioridad;  

    //Falta agregar validacion para descripcion y prioridad ***************
    
    //insetar el tipo de usuario segun la prioridad
    //TipoUsuario nuevoTipoUsuario = TipoUsuario(descripcion, prioridad);
    try {
        controlPrincipal->agregarTipoUsuarioAdmin(descripcion, prioridad);

        cout << "\n\tUsuario agregado exitosamente!";
        controlPrincipal->getTiposAdmin()->print("Tipos de usuario");
    }
    catch(const std::runtime_error& e){
        cout << e.what();
    }

    
    _getch();
    system("cls");

}
void eliminarTipoUsuario() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = controlPrincipal->getTiposAdmin()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
            TipoUsuario current = controlPrincipal->getTiposAdmin()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i]= descripcion;
            controlPrincipal->getTiposAdmin()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getTiposAdmin()->next();
        }
        controlPrincipal->getTiposAdmin()->remove();
        cout << "\n\n\tUsuario eliminado exitosamente!\n";
        controlPrincipal->getTiposAdmin()->print("Tipos de usuario");
    }
    _getch();
    system("cls");
}
void menuTiposUsuario() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Tipos de Usuario";
    const char* opciones[] = { "Agregar", "Eliminar", "Regresar" };
    int n = 3;

    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarTipoUsuario();
            break;
        case 2:
            eliminarTipoUsuario();
            break;
        case 3:
            on = false;
            break;            
        }
    } while (on);
}
void agregarArea() {
    string descripcion;
    string codigo;
    int cantVentanillas;

    system("cls");
    cout << "\n\t\t\Agregar Área" << endl;
    cout << "\n\tDescripción: ";
    cin.ignore();
    getline(cin, descripcion);
    cout << "\n\tCodigo: ";
    cin >> codigo; //verificar que en la lista de areas no haya una con codigo igual
    cout << "\n\tCantidad de Ventanillas: ";
    cin >> cantVentanillas; 
    try {
        controlPrincipal->agregarArea(descripcion, codigo, cantVentanillas);
        cout << "\n\n\tÁrea agregada exitosamente!";
        controlPrincipal->getAreas()->print("Áreas");
    }
    catch (const std::runtime_error& e) {
        cout << e.what();
    }
    
    
    _getch();
    system("cls");
}
void modificarVentanillasArea() {
    bool on = true;
    int opcion;
    const char* titulo = "Modificar Cantidad de Ventanillas";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay areas cuyas ventanillas puedes modificar :( que triste";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getCodigo().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getCodigo().c_str(), size + 1);
            opciones[i] = codigo;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);

        int cantVentanillas;

        system("cls");
        cout << "\n\tCantidad de Ventanillas Nueva: ";
        cin >> cantVentanillas;

        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        Area& areaToManip = controlPrincipal->getAreas()->getElement();
        try {
            areaToManip.setCantVentanillas(cantVentanillas);
            cout << "\n\n\tArea editada exitosamente!\n";
            controlPrincipal->getAreas()->print("Áreas");
        }
        catch (const std::runtime_error& e) {
            cout << e.what();
        }
        
    }
    _getch();
    system("cls");
}
void eliminarArea() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Tipos de Usuario";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getCodigo().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getCodigo().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        controlPrincipal->getAreas()->remove();
        cout << "\n\n\tUsuario eliminado exitosamente!\n";
        controlPrincipal->getAreas()->print("Áreas");
    }
    _getch();
    system("cls");
}
void menuGestorAreas() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Gestor de Áreas";
    const char* opciones[] = { "Agregar Área","Modificar Cantidad de Ventanillas", "Eliminar", "Regresar" };
    int n = 4;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarArea();
            break;
        case 2:
            modificarVentanillasArea();
            break;
        case 3:
            eliminarArea();
            break;
        case 4:
            on = false;
            break;
        }
    } while (on);
}
void agregarServicio() {
    int opcion;
    string descripcion;
    int prioridad;

    system("cls");
    cout << "\n\t\t\tAgregar Servicio" << endl;
    cout << "\n\tDescripción: ";
    cin.ignore();
    getline(cin,descripcion);
    cout << "\n\tPrioridad: ";
    cin >> prioridad; //verificar que en la lista de areas no haya una con codigo igual
    system("cls");
    const char* titulo = "Área para Agregar";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay áreas para generar servicios";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getAreas()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area& current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }
        Area& areaToManip = controlPrincipal->getAreas()->getElement();
        Area* areaToManipPtr = &areaToManip;
        try {
            controlPrincipal->agregarServicio(descripcion, areaToManipPtr, prioridad);
            cout << "\n\n\tServicio agregado exitosamente!";
            controlPrincipal->getServicios()->print("Servicios");
        }
        catch (const std::runtime_error& e) {
            cout << e.what();
        }
        
    }
    _getch();
    system("cls");
}
void eliminarServicio() {
    bool on = true;
    int opcion;
    const char* titulo = "Eliminar Servicio";
    int n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    system("cls");

    //Si no hay usuario por eliminar muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios para eliminar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        int index = 0;
        controlPrincipal->getServicios()->goToStart();

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getServicios()->goToStart();
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio& current = controlPrincipal->getServicios()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getServicios()->next();
        }

        //crea el menu de eliminar tipos de usuario
        opcion = menu(titulo, opciones, n);
        //una vez el usuario selecciona el tipo de usuario a eliminar se busca
        //en la lista y se elimina
        controlPrincipal->getServicios()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getServicios()->next();
        }
        controlPrincipal->getServicios()->remove();
        cout << "\n\n\tServicio eliminado exitosamente!\n";
        controlPrincipal->getServicios()->print("Servicios");
    }
    _getch();
    system("cls");
}
void reordenarServicio() {
    bool on = true;
    int opcion;
    const char* titulo = "Reordenar Servicios";
    int n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de servicios
    system("cls");

    //Si no hay servicios muesta un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay servicios para reordenar";
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 
        controlPrincipal->getServicios()->goToStart();

        //recorre la lista de tipos de servicios existentes para crear las opciones 
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio& current = controlPrincipal->getServicios()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* codigo = new char[size + 1];
            memcpy(codigo, current.getDescripcion().c_str(), size + 1);
            opciones[i] = codigo;
            controlPrincipal->getServicios()->next();
        }

        //crea el menu de servicios
        opcion = menu(titulo, opciones, n);

        int newPos;

        system("cls");
        cout << "\n\tPosicion que deseas para el servicio seleccionado: ";
        cin >> newPos;

        controlPrincipal->getServicios()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getServicios()->next();
        }
        int posServ = controlPrincipal->getServicios()->getPos();
        controlPrincipal->reordenarServicios(posServ, newPos);
        cout << "\n\n\tLista de servicios editada exitosamente!\n";
        controlPrincipal->getServicios()->print("Servicios");
    }
    _getch();
    system("cls");
}
void menuGestorServicios() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Gestor de Servicios";
    const char* opciones[] = { "Agregar Servicio","Eliminar Servicio", "Reordenar Servicios", "Regresar" };
    int n = 4;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            agregarServicio();
            break;
        case 2:
            eliminarServicio();
            break;
        case 3:
            reordenarServicio();
            break;
        case 4:
            on = false;
            break;
        }
    } while (on);
}
//Elimina los contenidos de todas las colas de prioridad, los tiquetes atendidos en ventanillas y
//los datos de las estadísticas que se hayan registrado hasta el momento
void modoOppenheimer() {    

    //recorre la lista de areas
    controlPrincipal->getAreas()->goToStart();
    for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
        Area& current = controlPrincipal->getAreas()->getElement();
        current.reiniciarArea();
        controlPrincipal->getAreas()->next();
    }

    //recorre la lista de usuarios
    controlPrincipal->getTiposAdmin()->goToStart();
    for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
        TipoUsuario& current = controlPrincipal->getTiposAdmin()->getElement();
        current.reiniciarUsuario();
        controlPrincipal->getTiposAdmin()->next();
    }

    //recorre la lista de servicios
    controlPrincipal->getServicios()->goToStart();
    for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
        Servicio& current = controlPrincipal->getServicios()->getElement();
        current.reiniciarServicio();
        controlPrincipal->getServicios()->next();
    }

    cout << "\n\n\tColas y estadisticas eliminadas correctamente.";
    _getch();
    
}
void menuAdmin() {
    bool on = true;
    int opcion;
    const char* titulo = "Menu Administrativo";
    const char* opciones[] = { "Gestor de Tipos de Usuarios", "Gestor Areas", "Gestor Servicios", "Modo Oppenheimer", "Regresar"};
    int n = 5;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            menuTiposUsuario();
            break;
        case 2:
            menuGestorAreas();
            break;
        case 3:
            menuGestorServicios();
            break;
        case 4:
            modoOppenheimer();
            break;
        case 5:
            on = false;
            break;
        }
    } while (on);
}
void menuTiquetes() {
    bool on = true;
    int opcion;
    const char* titulo = "Seleccionar usuario";
    int n = controlPrincipal->getTiposAdmin()->getSize(); //obtiene el tamano de la lista de tipos de usuario
    int priorityToGiveUsr;
    int pripriorityToGiveServ;
    Area* area;
    system("cls");

    //Si no hay usuario muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay tipos de usuarios registrados en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de tipos de usuarios existentes para crear las opciones de eliminar
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
            TipoUsuario current = controlPrincipal->getTiposAdmin()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getTiposAdmin()->next();
        }

        //crea el menu de tipos de usuario
        opcion = menu(titulo, opciones, n);
        //se selecciona el tipo de usuario
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getTiposAdmin()->next();
        }

        priorityToGiveUsr = controlPrincipal->getTiposAdmin()->getElement().getPrioridad();
        cout << "\n\n\tUsuario seleccionado exitosamente!\n";


        _getch();
        on = true;
        titulo = "Seleccionar servicio";
        n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de tipos de usuario
        system("cls");

        //Si no hay servicios se muestra un mensaje
        if (n == 0) {
            cout << "\n\n\tNo hay serivcios registrado en el sistema";
            _getch();
        }
        else {
            const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

            //recorre la lista de servicios existentes para crear las opciones 
            controlPrincipal->getServicios()->goToStart();
            for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
                Servicio& current = controlPrincipal->getServicios()->getElement();
                const string::size_type size = current.getDescripcion().size();
                char* codigo = new char[size + 1];
                memcpy(codigo, current.getDescripcion().c_str(), size + 1);
                opciones[i] = codigo;
                controlPrincipal->getServicios()->next();
            }

            //crea el menu de servicios
            opcion = menu(titulo, opciones, n);

            controlPrincipal->getServicios()->goToStart();
            for (int i = 1; i < opcion; ++i) {
                controlPrincipal->getServicios()->next();
            }
            pripriorityToGiveServ = controlPrincipal->getServicios()->getElement().getPrioridad();
            area = controlPrincipal->getServicios()->getElement().getArea();
            controlPrincipal->agregarTiquete(ticketCounter, area, priorityToGiveUsr, pripriorityToGiveServ);
            ticketCounter++;
            controlPrincipal->getServicios()->getElement().agregarTiqueteSolicitado();
            controlPrincipal->getTiposAdmin()->getElement().agregarTiqueteSolicitado();
            cout << "\n\n\tTiquete creado exitosamente!\n";
            area->getTiquetes()->print(); 
            _getch();
        }
    }
}

//revisa el estado actual de las colas por area
void revisarColas() {
    bool on = true;
    int opcion;
    const char* titulo = "Seleccionar Área";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de areas
    system("cls");

    //Si no hay areas muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay áreas registradas en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de areas existentes para crear las opciones
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de areas
        opcion = menu(titulo, opciones, n);
        //se selecciona el area
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }

        cout << "\n\n\tarea seleccionada exitosamente!\n";
        //string areaForExtraction = controlPrincipal->getAreas()->getElement().getCodigo();
        _getch();
        on = true;
        titulo = "Seleccionar Ventanilla";
        n = controlPrincipal->getAreas()->getElement().getVentanillas()->getSize(); //obtiene el tamano de la lista de ventanillas del area
        system("cls");

        //Si no hay servicios se muestra un mensaje
        if (n == 0) {
            cout << "\n\n\tNo hay ventanillas registrada en el �rea";
            _getch();
        }
        else {
            const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

            //recorre la lista de servicios existentes para crear las opciones 
            controlPrincipal->getAreas()->getElement().getVentanillas()->goToStart();
            for (int i = 0; i < controlPrincipal->getAreas()->getElement().getVentanillas()->getSize(); ++i) {
                Ventanilla& current = controlPrincipal->getAreas()->getElement().getVentanillas()->getElement();
                string codigo = "Ningún tiquete ha sido atendido";
                if (current.getCurrentTiquete().getCodigo() != "") {
                    codigo = current.getCurrentTiquete().getCodigo();
                }

                cout << "\n\n\t" << current.getNombre() << ": " << codigo << "\n";
                controlPrincipal->getAreas()->getElement().getVentanillas()->next();
            }

            cout << "\n\n\tEstado de colas\n";
            if (controlPrincipal->getAreas()->getElement().getTiquetes()->isEmpty()) {
                cout << "\n\n\tNo hay tiquetes en la cola de esta área\n";
            }
            else {
                controlPrincipal->getAreas()->getElement().getTiquetes()->print();
            }

            _getch();

        }
    }
}

//atiende un tiquete en una ventanilla por prioridad
void atender() {
    bool on = true;
    int opcion;
    const char* titulo = "Seleccionar Área";
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de areas
    system("cls");

    //Si no hay areas muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay áreas registradas en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de areas existentes para crear las opciones
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area current = controlPrincipal->getAreas()->getElement();
            const string::size_type size = current.getDescripcion().size();
            char* descripcion = new char[size + 1];
            memcpy(descripcion, current.getDescripcion().c_str(), size + 1);
            opciones[i] = descripcion;
            controlPrincipal->getAreas()->next();
        }

        //crea el menu de areas
        opcion = menu(titulo, opciones, n);
        //se selecciona el area
        controlPrincipal->getAreas()->goToStart();
        for (int i = 1; i < opcion; ++i) {
            controlPrincipal->getAreas()->next();
        }

        cout << "\n\n\tárea seleccionada exitosamente!\n";
        //string areaForExtraction = controlPrincipal->getAreas()->getElement().getCodigo();
        _getch();
        on = true;
        titulo = "Seleccionar Ventanilla";
        n = controlPrincipal->getAreas()->getElement().getVentanillas()->getSize(); //obtiene el tamano de la lista de ventanillas del area
        system("cls");

        //Si no hay servicios se muestra un mensaje
        if (n == 0) {
            cout << "\n\n\tNo hay ventanillas registrada en el área";
            _getch();
        }
        else {
            const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

            //recorre la lista de servicios existentes para crear las opciones 
            controlPrincipal->getAreas()->getElement().getVentanillas()->goToStart();
            for (int i = 0; i < controlPrincipal->getAreas()->getElement().getVentanillas()->getSize(); ++i) {
                Ventanilla current = controlPrincipal->getAreas()->getElement().getVentanillas()->getElement();
                const string::size_type size = current.getNombre().size();
                char* descripcion = new char[size + 1];
                memcpy(descripcion, current.getNombre().c_str(), size + 1);
                opciones[i] = descripcion;
                controlPrincipal->getAreas()->getElement().getVentanillas()->next();
            }

            //crea el menu de areas
            opcion = menu(titulo, opciones, n);
            //se selecciona el area
            controlPrincipal->getAreas()->getElement().getVentanillas()->goToStart();
            for (int i = 1; i < opcion; ++i) {
                controlPrincipal->getAreas()->getElement().getVentanillas()->next();
            }

            cout << "\n\n\tVentanilla seleccionada exitosamente!\n";
            _getch();
            system("cls");
            if (controlPrincipal->getAreas()->getElement().getTiquetes()->isEmpty()) {
                cout << "\n\n\tNo hay tiquetes por atender en el área de la ventanilla\n";
            }
            else {
                Area& area = controlPrincipal->getAreas()->getElement();
                area.getVentanillas()->getElement().atenderTiquete(area.getTiquetes()->min());
                cout << "\n\n\tEl tiquete " << area.getTiquetes()->min().getCodigo() << " será atendido en la ventanilla " << area.getVentanillas()->getElement().getNombre();
                area.agregarTiempoEspera(difftime(time(0), area.getTiquetes()->min().getFechaCreacion())); //agrega el tiempo de espera total del tiquete
                area.agregarTiquetesAtendidos(); //incrementa la cantidad de tiquetes atendidos en el area
                area.getTiquetes()->removeMin(); //elimina el tiquete de la cola
            }
            _getch();

        }
    }
}

//muestra la estadistica por area del total de tiquetes dispensados
void tiquetesDispensadosPorArea() {
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de areas
    system("cls");
    cout << "\n\n\tCantidad de tiquetes dispensados por área\n";

    //Si no hay areas muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay áreas registradas en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de areas existentes para crear las opciones
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area current = controlPrincipal->getAreas()->getElement();
            cout << "\n\tÁrea: " << current.getDescripcion() << " Cant. tiquetes: " << current.getTiquetesDispensados();
            controlPrincipal->getAreas()->next();
        }
        _getch();
    }
}

//muestra la estadistica por servicio del total de tiquetes solicitados
void tiquetesSolicitadosPorServicio() {
    int n = controlPrincipal->getServicios()->getSize(); //obtiene el tamano de la lista de servicios
    system("cls");
    cout << "\n\n\tCantidad de tiquetes solicitados por servicio\n";

    //Si no hay servicios muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay servicios registrados en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de servicios existentes para crear las opciones
        controlPrincipal->getServicios()->goToStart();
        for (int i = 0; i < controlPrincipal->getServicios()->getSize(); ++i) {
            Servicio current = controlPrincipal->getServicios()->getElement();
            cout << "\n\tServicio: " << current.getDescripcion() << " Cant. tiquetes: " << current.getTiquetesSolicitados();
            controlPrincipal->getServicios()->next();
        }
        _getch();
    }
}

//muestra la estadistica por usuario del total de tiquetes emitidos
void tiquetesEmitidosPorUsuario() {
    int n = controlPrincipal->getTiposAdmin()->getSize(); //obtiene el tamano de la lista de usuarios
    system("cls");
    cout << "\n\n\tCantidad de tiquetes emitidos por usuario\n";

    //Si no hay usuarios muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay usuarios registrados en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de usuarios existentes para crear las opciones
        controlPrincipal->getTiposAdmin()->goToStart();
        for (int i = 0; i < controlPrincipal->getTiposAdmin()->getSize(); ++i) {
            TipoUsuario current = controlPrincipal->getTiposAdmin()->getElement();            
            cout << "\n\tTipo de usuario: " << current.getDescripcion() << " Cant. tiquetes: " << current.getTiquetesSolicitados();
            controlPrincipal->getTiposAdmin()->next();
        }
        _getch();
    }
}

//muestra la estadistica por area del promedio de tiempo de espera de los tiquetes atendidos
void tiempoEsperaPorArea() {
    int n = controlPrincipal->getAreas()->getSize(); //obtiene el tamano de la lista de areas
    system("cls");
    cout << "\n\n\tTiempo promedio de espera por área\n";

    //Si no hay areas muestra un mensaje
    if (n == 0) {
        cout << "\n\n\tNo hay áreas registradas en el sistema.";
        _getch();
    }
    else {
        const char* opciones[100]; //Cambiar este valor fijo si fuera posible******** 

        //recorre la lista de areas existentes para crear las opciones
        controlPrincipal->getAreas()->goToStart();
        for (int i = 0; i < controlPrincipal->getAreas()->getSize(); ++i) {
            Area current = controlPrincipal->getAreas()->getElement();
            cout << "\n\tÁrea: " << current.getDescripcion() << " Tiempo promedio de espera: " << current.getTiempoPromedioEspera() << " segundos";
            controlPrincipal->getAreas()->next();
        }
        _getch();
    }
}

//menu de estadisticas
void estadisticas() {
    bool on = true;
    int opcion;
    const char* titulo = "Estadísticas";
    const char* opciones[] = { "Tiempo de espera por área", "Tiquetes dispensados por área", "Tiquetes solicitados por servicio", "Tiquetes emitidos por usuario", "Regresar" };
    int n = 5;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            tiempoEsperaPorArea();
            break;
        case 2:
            tiquetesDispensadosPorArea();
            break;
        case 3:
            tiquetesSolicitadosPorServicio();
            break;
        case 4:
            tiquetesEmitidosPorUsuario();
            break;
        case 5:
            on = false;
            break;
        }

    } while (on);
}

void menuPrincipal() {
   
    bool on = true;
    int opcion;
    const char* titulo = "Menu Principal";
    const char* opciones[] = { "Revisar Colas", "Generar Tiquetes", "Atender", "Modo Administrativo", "Estadisitcas", "Salir" };
    int n = 6;
    do {
        opcion = menu(titulo, opciones, n);

        switch (opcion) {
        case 1:
            revisarColas();
            break;
        case 2:
            menuTiquetes();
            break;
        case 3:
            atender();
            break;
        case 4:
            menuAdmin();
            break;
        case 5:
            estadisticas();
            break;
        case 6:
            on = false;
            break;
        }

    } while (on);
}
int main()
{   
   setlocale(LC_ALL, "en_US.utf8"); // para evitar errores en las tildes
   menuPrincipal();
    //Control cp = Control();
    //cp.agregarTiquete(1, "C", 2, 4);
    //cp.getTiquetes()->print();
    //cp.agregarTiquete(1, "C", 3, 1);
    //cp.agregarTiquete(1, "C", 1, 2);
    //cp.agregarTiquete(1, "C", 1, 1);
    //cp.getTiquetes()->print();
   //poUsuarioClientes clienteP = TipoUsuarioClientes("sd", 5);
   //ut << clienteP.obtenerFechaComoCadena() << endl;
   //cFienteP.obtenerFechaComoCadena();
   return 0;
}