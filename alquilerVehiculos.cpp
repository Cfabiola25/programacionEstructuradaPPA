#include <iostream>
#include <map>
#include <string>

struct Vehiculo {
    std::string marca;
    std::string modelo;
    double tarifaPorHora;
    bool disponible;
};

std::map<std::string, Vehiculo> vehiculos;

void agregarVehiculo() {
    std::string placa, marca, modelo;
    double tarifa;

    std::cout << "Ingrese placa: ";
    std::cin >> placa;

    std::cout << "Ingrese marca: ";
    std::cin >> marca;

    std::cout << "Ingrese modelo: ";
    std::cin >> modelo;

    std::cout << "Ingrese tarifa por hora: ";
    std::cin >> tarifa;

    vehiculos[placa] = {marca, modelo, tarifa, true};

    std::cout << "Vehículo agregado exitosamente.\n";
}

void mostrarTodosLosVehiculos() {
    if (vehiculos.empty()) {
        std::cout << "No hay vehículos registrados.\n";
        return;
    }

    std::cout << "\nLista de todos los vehículos:\n";
    for (const auto& par : vehiculos) {
        std::cout << "Placa: " << par.first
                  << " | Marca: " << par.second.marca
                  << " | Modelo: " << par.second.modelo
                  << " | Tarifa/hora: $" << par.second.tarifaPorHora
                  << " | Estado: " << (par.second.disponible ? "Disponible" : "Ocupado") << "\n";
    }
}


void mostrarDisponibles() {
    std::cout << "\nVehículos disponibles:\n";
    bool hayDisponibles = false;

    for (const auto& par : vehiculos) {
        if (par.second.disponible) {
            hayDisponibles = true;
            std::cout << "Placa: " << par.first
                      << " | Marca: " << par.second.marca
                      << " | Modelo: " << par.second.modelo
                      << " | Tarifa/hora: $" << par.second.tarifaPorHora << "\n";
        }
    }

    if (!hayDisponibles)
        std::cout << "No hay vehículos disponibles actualmente.\n";
}

void alquilarVehiculo() {
    std::cout << "\nVehículos disponibles para alquilar:\n";
    bool hayDisponibles = false;

    for (const auto& par : vehiculos) {
        if (par.second.disponible) {
            hayDisponibles = true;
            std::cout << "Placa: " << par.first
                      << " | Marca: " << par.second.marca
                      << " | Modelo: " << par.second.modelo
                      << " | Tarifa/hora: $" << par.second.tarifaPorHora << "\n";
        }
    }

    if (!hayDisponibles) {
        std::cout << "No hay vehículos disponibles en este momento.\n";
        return;
    }

    std::string placa;
    int horas;

    std::cout << "\nIngrese la placa del vehículo que desea alquilar: ";
    std::cin >> placa;

    auto it = vehiculos.find(placa);

    if (it != vehiculos.end()) {
        if (it->second.disponible) {
            std::cout << "Ingrese el número de horas de alquiler: ";
            std::cin >> horas;

            double total = it->second.tarifaPorHora * horas;
            it->second.disponible = false;

            std::cout << "Vehículo alquilado exitosamente. Costo total: $" << total << "\n";
        } else {
            std::cout << "Ese vehículo ya está alquilado.\n";
        }
    } else {
        std::cout << "Vehículo no encontrado.\n";
    }
}

void eliminarVehiculo() {
    if (vehiculos.empty()) {
        std::cout << "No hay vehículos para eliminar.\n";
        return;
    }

    mostrarTodosLosVehiculos();

    std::string placa;
    std::cout << "\nIngrese la placa del vehículo que desea eliminar: ";
    std::cin >> placa;

    if (vehiculos.erase(placa)) {
        std::cout << "✅ Vehículo eliminado exitosamente.\n";
    } else {
        std::cout << "❌ Vehículo no encontrado.\n";
    }
}


void menuAdministrador() {
    int opcion;
    do {
        std::cout << "\n--- MENÚ ADMINISTRADOR ---\n";
        std::cout << "1. Agregar vehículo\n";
        std::cout << "2. Ver todos los vehículos\n";
        std::cout << "3. Eliminar vehículo\n";
        std::cout << "4. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();                // Limpia el estado de error
            std::cin.ignore(10000, '\n');    // Descarta la entrada incorrecta
            std::cout << "❌ Entrada inválida. Intente nuevamente.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                agregarVehiculo();
            break;
            case 2:
                mostrarTodosLosVehiculos();
            break;
            case 3:
                eliminarVehiculo();
            break;
            case 4:
                std::cout << "Volviendo al menú principal...\n";
            break;
            default:
                std::cout << "⚠ Opción inválida.\n";
        }
    } while (opcion != 4);
}


void menuUsuario() {
    int opcion;
    do {
        std::cout << "\n--- MENÚ USUARIO ---\n";
        std::cout << "1. Ver vehículos disponibles\n";
        std::cout << "2. Alquilar vehículo\n";
        std::cout << "3. Volver al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();                // Limpia el estado de error
            std::cin.ignore(10000, '\n');    // Descarta la entrada incorrecta
            std::cout << "❌ Entrada inválida. Intente nuevamente.\n";
            continue;
        }

        switch (opcion) {
            case 1:
                mostrarDisponibles();
            break;
            case 2:
                alquilarVehiculo();
            break;
            case 3:
                std::cout << "Volviendo al menú principal...\n";
            break;
            default:
                std::cout << "⚠ Opción inválida.\n";
        }
    } while (opcion != 3);
}


int main() {
    int tipo;
    std::string clave;

    do {
        std::cout << "\n=== MENÚ PRINCIPAL ===\n";
        std::cout << "Seleccione el tipo de usuario:\n";
        std::cout << "1. Administrador\n";
        std::cout << "2. Usuario\n";
        std::cout << "3. Salir\n";
        std::cout << "Opción: ";
        std::cin >> tipo;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "❌ Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        switch (tipo) {
            case 1:
                std::cout << "Ingrese la clave de administrador: ";
            std::cin >> clave;
            if (clave == "admin") {
                menuAdministrador();
            } else {
                std::cout << "❌ Clave incorrecta.\n";
            }
            break;

            case 2:
                menuUsuario();
            break;

            case 3:
                std::cout << "👋 Saliendo del sistema.\n";
            break;

            default:
                std::cout << "⚠ Opción no válida. Intente de nuevo.\n";
        }

    } while (tipo != 3);

    return 0;
}