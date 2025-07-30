#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

//Funcion de operaciones matematicas


double suma(double a, double b){
    return a + b;

}

// resta
double resta (double a, double b){
    return a - b;
}

//multiplicacion
double multiplicacion(double a, double b){
    return a * b;
}

//division
double division(double a, double b){
    if (b=0){

        throw runtime_error("Divide en 0");

    }
    return a/b;
}

//potencias 
double potencia(double a, double b){

    return pow(a,b);

}


//modulos 
double modulo(double a, double b){
    if (b=0){
        throw runtime_error("No se puede dividir en 0");

    }

    return fmod(a,b);
}



//validar si una cadena es de 8 bits

bool esValidaInstruccion(const string& instruccion){
    if (instruccion.length() != 8 ){
        return false;

    }

    for (char c: instruccion){
        if (c != '0' && c != '1'){
            return false;
        }
    }    
    return true;
}

// Función para extraer bits usando operadores de desplazamiento y AND
int extraerBits(const string& instruccion, int inicio, int cantidad) {
    int valor = 0;
    
    // Convertir la cadena binaria a entero
    for (int i = 0; i < 8; i++) {
        if (instruccion[i] == '1') {
            valor |= (1 << (7 - i));
        }
    }
    
    // Extraer los bits específicos
    int mascara = (1 << cantidad) - 1;  // Crear máscara de 'cantidad' bits
    return (valor >> inicio) & mascara;
}

// Función principal de decodificación
void decodificarInstruccion(const string& instruccion, int numeroInstruccion) {
    cout << "\n→ Instrucción " << numeroInstruccion << ": " << instruccion << endl;
    
    // Validar instrucción
    if (!esValidaInstruccion(instruccion)) {
        cout << "→ Error: Instrucción inválida (debe tener 8 bits con solo 0s y 1s)" << endl;
        return;
    }
    
    // Extraer componentes usando big endian (bits 7-6, 5-4, 3-2, 1-0)
    int opcode = extraerBits(instruccion, 6, 2);    // bits 7-6
    int mod = extraerBits(instruccion, 4, 2);       // bits 5-4
    int operandoA = extraerBits(instruccion, 2, 2); // bits 3-2
    int operandoB = extraerBits(instruccion, 0, 2); // bits 1-0
    
    // Mostrar decodificación
    string nombreOpcode[] = {"Suma", "Resta", "Multiplicación", "División"};
    string nombreMod[] = {"Directa", "Potencia", "Módulo", "Invertir"};
    
    cout << "OPCODE: " << instruccion.substr(0, 2) << " (" << nombreOpcode[opcode] << ")" << endl;
    cout << "MOD: " << instruccion.substr(2, 2) << " (" << nombreMod[mod] << ")" << endl;
    cout << "A: " << instruccion.substr(4, 2) << " (" << operandoA << ")" << endl;
    cout << "B: " << instruccion.substr(6, 2) << " (" << operandoB << ")" << endl;
    
    // Aplicar MOD 11 (invertir operandos)
    if (mod == 3) { // MOD = 11
        int temp = operandoA;
        operandoA = operandoB;
        operandoB = temp;
        cout << "→ Operandos invertidos: A=" << operandoA << ", B=" << operandoB << endl;
    }
    
    try {
        double resultado = 0;
        
        // Procesar según MOD
        switch (mod) {
            case 0: // Operación directa
                switch (opcode) {
                    case 0: resultado = suma(operandoA, operandoB); break;
                    case 1: resultado = resta(operandoA, operandoB); break;
                    case 2: resultado = multiplicacion(operandoA, operandoB); break;
                    case 3: resultado = division(operandoA, operandoB); break;
                }
                break;
                
            case 1: // Potencia (A^B)
                resultado = potencia(operandoA, operandoB);
                break;
                
            case 2: // A mod B
                resultado = modulo(operandoA, operandoB);
                break;
                
            case 3: // Invertir operandos (ya se aplicó arriba)
                switch (opcode) {
                    case 0: resultado = suma(operandoA, operandoB); break;
                    case 1: resultado = resta(operandoA, operandoB); break;
                    case 2: resultado = multiplicacion(operandoA, operandoB); break;
                    case 3: resultado = division(operandoA, operandoB); break;
                }
                break;
        }
        
        cout << "→ Resultado: " << resultado << endl;
        
    } catch (const runtime_error& e) {
        cout << "→ Error: " << e.what() << " en instrucción " << numeroInstruccion << endl;
    }
}

int main() {
    string entrada;
    
    cout << "=== DECODIFICADOR DE INSTRUCCIONES BINARIAS ===" << endl;
    cout << "Ingrese las instrucciones binarias (separadas por espacios): ";
    getline(cin, entrada);
    
    // Dividir la entrada en instrucciones individuales
    stringstream ss(entrada);
    string instruccion;
    vector<string> instrucciones;
    
    while (ss >> instruccion) {
        instrucciones.push_back(instruccion);
    }
    
    if (instrucciones.size() < 3) {
        cout << "Error: Se requieren mínimo 3 instrucciones." << endl;
        return 1;
    }
    
    // Procesar cada instrucción
    for (size_t i = 0; i < instrucciones.size(); i++) {
        decodificarInstruccion(instrucciones[i], i + 1);
    }
    
    cout << "\n=== PROCESAMIENTO COMPLETADO ===" << endl;
    
    return 0;
}



