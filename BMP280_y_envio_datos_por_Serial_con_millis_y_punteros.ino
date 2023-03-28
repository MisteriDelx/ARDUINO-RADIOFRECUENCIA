


/*
  EMISOR O CANSAT
  Lectura de la temperatura y presión y envío de los datos por el HC12
*/

#include <Wire.h>   // incluye librería de bus I2C que gestiona los pines SDA y SCL para el sensor bmp280
//#include <Adafruit_Sensor.h>  // incluye librerias para sensor BMP280
#include <Adafruit_BMP280.h>  // librerías para el sensor bmp280 de temperatura y presión
#include <SoftwareSerial.h> // librería para crear un puerto virtual distinto al de los pines 0 RX y 1 TX

//Definir los pines del HC-12
// puerto serie virtual 10 RX y 11 TX
//El pin TX del HC12 irá conectado al pin 10 de arduino que hará de RX de arduino
Adafruit



_BMP280 bmp;    // crea objeto con nombre bmp
SoftwareSerial HC12 (10, 11); 

float P0;    // variable para almacenar valor de presion atmosferica inicial
        // y presion actual como referencia para altitud relativa respecto de la altura cero de la base
unsigned long previousMillis=0; //variable para almacenar el tiempo del último envío
const long interval=1100; //intervalo de tiempo entre cada envío de datos por el HC12


void setup() {
  Serial.begin(9600);       // inicializa comunicacion serie a 9600 bps
  //Serial.setTimeout(50);
  HC12.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
  //Serial.println("Iniciando:");     // texto de inicio
  if ( !bmp.begin(0x76) ) {       // si falla la comunicacion con el sensor mostrar
    Serial.println("BMP280 no encontrado !"); // texto en caso de que el sensor no esté funcionando
    while (1);          // detener flujo del programa mediante bucle infinito
  }
  P0 = bmp.readPressure()/100;      // almacena en P0 el valor actual de presion
}                                  // en hectopascales para calculo de altitud relativa

void loop() {
  unsigned long actual=millis();  //Obtenemos el tiempo actual
  if (actual-previousMillis>=interval){  // Comprobamos si ha pasado el intervalo de tiempo desde el último envío
  previousMillis=actual; // actualizamos el tiempo del último envío
  float temp = bmp.readTemperature();    // almacena en variable el valor de temperatura
  float presion = bmp.readPressure()/100;   // almacena en variable el valor de presion divido
  float altitud=bmp.readAltitude(P0);
            // por 100, en formato float, para covertirlo a hectopascales
  Serial.print("Temperatura: ");    // muestra texto
  Serial.print (temp);     // muestra el valor por el monitor serie
  Serial.print(" ºC Presión atmosférica:");        // muestra letra C indicando grados centigrados
  Serial.print(presion);       // muestra valor de la variable
  Serial.print("hPa ");     // muestra texto hPa indicando hectopascales
  Serial.print("Altitud");
  Serial.print(altitud);
  Serial.println(m)

  HC12.write ((byte*)&temp, sizeof(temp));  //Enviamos el puntero de la variable temperatura y el tamaño de la variable
                                            //a través del HC-12. En este  caso el tamaño será 2 bytes ya que es de tipo float
  HC12.write ((byte*)&presion, sizeof(presion));  //Enviamos la presion a través del HC-12
  HC12.write ((byte*)&altitud, sizeof(altitud));
   
  } 
}
    
