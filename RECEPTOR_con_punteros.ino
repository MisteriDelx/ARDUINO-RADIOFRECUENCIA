/*
  RECEPTOR O ESTACIÓN BASE
  Lectura de datos por el HC12
*/
#include <SoftwareSerial.h> // Librería para crear puertos virtuales
SoftwareSerial HC12 (10, 11); // pin 10 como (RX) y pin 11 como (TX)
String inputString=""; // cadena para almacenar los datos entrantes
bool entradaCompleta =false;

void setup() {
  inputString.reserve(200);
  Serial.begin(9600);       // inicializa comunicacion serie a 9600 baudios
  while(!Serial){}        // mientras el Serial no tenga datos no hará ninguna acción
  HC12.begin (9600);  // inicializa la comunicación del puerto serie virtual
}

void loop(){
    float temp, presion;  // creamos otras dos variables con otro nombre porque si no el no recibe correctamente los datos de temp y presion
    if (HC12.available()>=8) {  // Comprobamos si se ha recibido suficientes datos (8 bytes para dos números tipo float)
    HC12.readBytes((byte*)&temp, sizeof(temp));  // leemos el dato de 4 bytes y lo almacenamos en la dirección de memoria de la variable temp 
    HC12.readBytes((byte*)&presion, sizeof(presion));  // leemos los 4 bytes siguientes y los almacenamos en la dirección de memoria de la variable presion
    Serial.print("Temperatura:");
    Serial.print(temp);  // mostramos el contenido del puntero temp
    Serial.print(" Presión:");
    Serial.print(presion);
    Serial.println("hPa");
     }
if(entradaCompleta) {
    if(inputString == "ledOn\n"){
      Serial.print("LED activado\n");
      HC12.print("ledOn\n");
    }
    else if(inputString == "ledOff\n"){
      Serial.print("LED desactivado\n");
      HC12.print("ledOff\n");
    }
    else { // Cualquier otro dato recibido
      Serial.println("Esperando comando...");
    }
  inputString = "";
  entradaCompleta = false;
  }
}
void serialEvent() { 
  while (Serial.available()) {
    // Obtener bytes de entrada:
    char inChar = (char)Serial.read();
    // Agregar al String de entrada:
    inputString += inChar;
    // Para saber si el string está completo, se detendrá al recibir
    // el caracter de retorno de línea ENTER \n
    if (inChar == '\n') {
      entradaCompleta = true;
    }
  }
}   


/*
 * el operador & se utiliza para obtener la dirección de memoria de la variable temp,
 * y se le pasa como argumento a la función readBytes. La función lee el número de bytes especificados 
 * por sizeof(temp) (que es el tamaño de la variable temp en bytes) de la comunicación serial y los almacena 
 * en la dirección de memoria que indica el puntero. La dirección de memoria se convierte a un puntero 
 * a byte utilizando un cast explícito a (byte*), para que sea compatible con el tipo de argumento que espera 
 * la función readBytes.
 * En C++, un puntero es una variable que contiene la dirección de memoria de otra variable.
 * Es decir, en lugar de almacenar el valor de una variable, un puntero almacena la dirección 
 * de memoria donde se encuentra esa variable en el espacio de memoria del programa. 
 * Un puntero se declara anteponiendo el operador * al nombre de la variable, 
 * y se inicializa asignándole la dirección de memoria de otra variable o utilizando el 
 * operador & para obtener la dirección de memoria de una variable existente.
 * 
 */
