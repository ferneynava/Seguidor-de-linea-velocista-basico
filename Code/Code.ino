//Componentes:
//   - 1 Arduino UNO
//   - 2 Motores DC
//   - 1 Puente H L298N
//   - 3 Sensores infrarrojos (QRE1113)
//   - 3 Resistencias de 220 ohmios
//   - Cables de conexión y protoboard
//
//   Conexiones:
//   
//      Arduino UNO           L298N              Sensores infrarrojos 
//      
//      5V --------------- VCC (5V)            Cada uno de los sensores:
//      GND -------------- GND                - Patilla 1 a GND
//      A0 --------------- IN1                - Patilla 2 a A0, A1 y A2 respectivamente
//      A1 --------------- IN2
//      A2 --------------- IN3
//      6 ----------------- OUT1               Motores DC:
//      5 ----------------- OUT2               - Terminal negativo a GND del protoboard
//      9 ----------------- ENA                - Terminal positivo a VCC del protoboard
//      10 ---------------- ENB                - Terminal positivo a VIN del L298N

      
// Seguidor de línea velocista - Código de programación

// Definición de pines
int motor_izquierdo = 6;
int motor_derecho = 5;
int sensor_izquierdo = A0;
int sensor_central = A1;
int sensor_derecho = A2;

// Variables para almacenar los valores de los sensores
int valor_sensor_izquierdo = 0;
int valor_sensor_central = 0;
int valor_sensor_derecho = 0;

// Variables para el control de la velocidad de los motores
int velocidad_base = 100;
int velocidad_adicional = 20;

void setup() {
  pinMode(motor_izquierdo, OUTPUT);
  pinMode(motor_derecho, OUTPUT);
  pinMode(sensor_izquierdo, INPUT);
  pinMode(sensor_central, INPUT);
  pinMode(sensor_derecho, INPUT);
}

void loop() {
  // Lectura de los sensores
  valor_sensor_izquierdo = analogRead(sensor_izquierdo);
  valor_sensor_central = analogRead(sensor_central);
  valor_sensor_derecho = analogRead(sensor_derecho);

  // Cálculo de la desviación de la línea
  int desviacion = valor_sensor_central - ((valor_sensor_izquierdo + valor_sensor_derecho) / 2);

  // Ajuste de la velocidad de los motores
  int velocidad_izquierdo = velocidad_base - (desviacion / 2) - velocidad_adicional;
  int velocidad_derecho = velocidad_base + (desviacion / 2) + velocidad_adicional;

  // Limitación de la velocidad mínima y máxima
  velocidad_izquierdo = constrain(velocidad_izquierdo, 0, 255);
  velocidad_derecho = constrain(velocidad_derecho, 0, 255);

  // Control de los motores
  analogWrite(motor_izquierdo, velocidad_izquierdo);
  analogWrite(motor_derecho, velocidad_derecho);
}
//Este código utiliza tres sensores infrarrojos para detectar una línea negra sobre un fondo blanco y ajusta la velocidad de dos motores DC para seguir la línea.
//La velocidad de los motores se ajusta en función de la desviación de la línea detectada por los sensores y de una velocidad base y adicional predefinida.
