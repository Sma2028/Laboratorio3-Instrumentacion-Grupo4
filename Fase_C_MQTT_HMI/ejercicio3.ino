/*
 * PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
 * ESP32 + MQTT + HTML + Potenciómetro + LED (Pin 33) + Servo (Pin 25)
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// ------------------------------------------------------
// CREDENCIALES WIFI
// ------------------------------------------------------
const char* ssid = "FLIA ALBARRACIN";
const char* password = "1053860607";

// ------------------------------------------------------
// CONFIGURACIÓN MQTT
// ------------------------------------------------------
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

// ------------------------------------------------------
// TÓPICOS MQTT
// ------------------------------------------------------
const char* topic_potenciometro = "instrumentacion/grupo1/potenciometro";
const char* topic_control_led = "instrumentacion/grupo1/control";
const char* topic_servo = "instrumentacion/grupo1/servo";
const char* topic_servo_estado = "instrumentacion/grupo1/servo/estado";

// ------------------------------------------------------
// PINES (Actualizado Servo al Pin 25)
// ------------------------------------------------------
const int pinLED = 33;             // Pin 33 para tu LED externo
const int pinPotenciometro = 34;   // Entrada analógica
const int pinServo = 25;           // Pin 25 para la señal del servo

// ------------------------------------------------------
// SERVO
// ------------------------------------------------------
Servo servoMotor;
const int anguloMinimo = 0;
const int anguloMaximo = 180;

// ------------------------------------------------------
// CLIENTES WIFI Y MQTT
// ------------------------------------------------------
WiFiClient espClient;
PubSubClient client(espClient);

// ------------------------------------------------------
// VARIABLES DE TIEMPO Y CONTROL
// ------------------------------------------------------
unsigned long tiempoAnteriorMQTT = 0;
const long intervaloMQTT = 1000;    

unsigned long tiempoAnteriorServo = 0;
const long intervaloServo = 30;     

int valorPotActual = 0;
int valorPotReferencia = 0;
int anguloServoActual = 0;
int anguloDesdePot = 0;

const int umbralMovimientoPot = 40;
bool primeraLecturaPot = true;
String ultimoOrigenServo = "Potenciómetro";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.println("--- SISTEMA MQTT INICIADO ---");
  Serial.print("Conectando a la red WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado exitosamente.");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());
}

void publicarEstadoServo() {
  String payload = String(anguloServoActual);
  client.publish(topic_servo_estado, payload.c_str());
}

void publicarPotenciometro() {
  String payload = String(valorPotActual);
  client.publish(topic_potenciometro, payload.c_str());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";
  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  String topicRecibido = String(topic);
  Serial.print("Mensaje en [");
  Serial.print(topicRecibido);
  Serial.print("]: ");
  Serial.println(mensaje);

  // Control del LED
  if (topicRecibido == topic_control_led) {
    if (mensaje == "1") {
      digitalWrite(pinLED, HIGH);
      Serial.println("-> LED ENCENDIDO");
    }
    else if (mensaje == "0") {
      digitalWrite(pinLED, LOW);
      Serial.println("-> LED APAGADO");
    }
  }

  // Control del Servo
  else if (topicRecibido == topic_servo) {
    int anguloWeb = mensaje.toInt();
    anguloWeb = constrain(anguloWeb, anguloMinimo, anguloMaximo);

    servoMotor.write(anguloWeb);
    anguloServoActual = anguloWeb;
    ultimoOrigenServo = "Página web";

    valorPotReferencia = analogRead(pinPotenciometro);

    Serial.print("-> Servo movido desde web a: ");
    Serial.println(anguloServoActual);

    publicarEstadoServo();
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT... ");
    String clientId = "ESP32_Lab_" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("¡Conectado!");
      client.subscribe(topic_control_led);
      client.subscribe(topic_servo);
      publicarPotenciometro();
      publicarEstadoServo();
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" Reintentando en 5s...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  analogReadResolution(12); 

  servoMotor.setPeriodHertz(50);
  servoMotor.attach(pinServo, 500, 2400); // Servo en Pin 25
  servoMotor.write(0);

  anguloServoActual = 0;
  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  valorPotReferencia = analogRead(pinPotenciometro);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long tiempoActual = millis();

  // Lectura del Potenciómetro y control del servo
  if (tiempoActual - tiempoAnteriorServo >= intervaloServo) {
    tiempoAnteriorServo = tiempoActual;

    valorPotActual = analogRead(pinPotenciometro);
    anguloDesdePot = map(valorPotActual, 0, 4095, anguloMinimo, anguloMaximo);
    anguloDesdePot = constrain(anguloDesdePot, anguloMinimo, anguloMaximo);

    bool potSeMovio = abs(valorPotActual - valorPotReferencia) >= umbralMovimientoPot;

    if (primeraLecturaPot || potSeMovio) {
      primeraLecturaPot = false;
      valorPotReferencia = valorPotActual;

      servoMotor.write(anguloDesdePot);
      anguloServoActual = anguloDesdePot;
      ultimoOrigenServo = "Potenciómetro";

      publicarEstadoServo();
    }
  }

  // Publicación periódica
  if (tiempoActual - tiempoAnteriorMQTT >= intervaloMQTT) {
    tiempoAnteriorMQTT = tiempoActual;
    publicarPotenciometro();
    publicarEstadoServo();
  }
}