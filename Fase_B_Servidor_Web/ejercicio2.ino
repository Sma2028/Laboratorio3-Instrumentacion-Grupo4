/*
- PRÁCTICA DE INSTRUMENTACIÓN: COMUNICACIÓN INDUSTRIAL
- Ejercicio 4 - Fase B: Servidor Web WiFi Local (Interfaz Mejorada) */
#include <WiFi.h>

// --- CREDENCIALES DE RED WIFI ---
const char* ssid     = "Galaxy A51 C60D";
const char* password = "ounh2987";

// Configurar el servidor web en el puerto 80 (estándar HTTP)
WiFiServer server(80);

// --- DEFINICIÓN DE PINES ---
const int pinLED = 33;            // Pin 33 para tu LED externo
const int pinPotenciometro = 34;  // Pin análogo de solo entrada

// Variable para almacenar el estado del LED
String estadoLED = "APAGADO";

void setup() {
  Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW); // Asegurar que inicie apagado

  // 1. Conexión a la red WiFi
  Serial.print("Conectando a la red: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Bucle de espera hasta que se establezca la conexión
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n¡Conexión WiFi exitosa!");
  
  // 2. Iniciar el servidor web
  server.begin();
  
  // Mostrar la dirección IP asignada al ESP32
  Serial.print("Servidor Web iniciado. Para acceder, abre un navegador y escribe esta IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Verificar si algún cliente (navegador web) se ha conectado
  WiFiClient client = server.available();

  if (client) {
    Serial.println("¡Nuevo cliente conectado!");
    String peticionHTTP = "";
    
    // Leer los datos enviados por el cliente
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        peticionHTTP += c;
        
        // Si la petición HTTP termina (con un salto de línea doble)
        if (c == '\n' && peticionHTTP.endsWith("\r\n\r\n")) {
          
          // --- LÓGICA DE CONTROL (Análisis de la URL) ---
          if (peticionHTTP.indexOf("GET /LED=ON") >= 0) {
            Serial.println("Comando Web: Encender LED");
            estadoLED = "ENCENDIDO";
            digitalWrite(pinLED, HIGH);
          } 
          else if (peticionHTTP.indexOf("GET /LED=OFF") >= 0) {
            Serial.println("Comando Web: Apagar LED");
            estadoLED = "APAGADO";
            digitalWrite(pinLED, LOW);
          }

          // --- LECTURA DEL SENSOR ---
          int valorPot = analogRead(pinPotenciometro);

          // --- CONSTRUCCIÓN DE LA PÁGINA WEB (HTML/CSS Moderno) ---
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          
          client.println("<!DOCTYPE html><html lang='es'>");
          client.println("<head><meta charset='UTF-8'><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<title>Panel ESP32 - Industrial</title>");
          // Refrescar la página automáticamente cada 3 segundos para actualizar el potenciómetro
          client.println("<meta http-equiv=\"refresh\" content=\"3\">"); 
          client.println("<style>");
          client.println("body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%); margin: 0; padding: 20px; display: flex; justify-content: center; align-items: center; min-height: 90vh; }");
          client.println(".card { background: white; padding: 30px; border-radius: 16px; box-shadow: 0 10px 30px rgba(0,0,0,0.12); width: 100%; max-width: 380px; text-align: center; }");
          client.println("h1 { color: #2c3e50; font-size: 22px; margin-bottom: 20px; font-weight: 600; }");
          client.println(".sensor-box { background: #f8f9fa; border: 1px solid #e9ecef; padding: 15px; border-radius: 12px; margin-bottom: 20px; }");
          client.println(".sensor-title { font-size: 14px; color: #6c75d0; text-transform: uppercase; letter-spacing: 1px; margin-bottom: 5px; }");
          client.println(".sensor-value { color: #007bff; font-weight: bold; font-size: 28px; }");
          client.println(".status-box { font-size: 15px; margin-bottom: 20px; color: #495057; font-weight: 500; }");
          client.println(".btn-container { display: flex; gap: 10px; justify-content: center; }");
          client.println(".boton { background-color: #28a745; border: none; color: white; padding: 12px 20px; font-size: 15px; cursor: pointer; border-radius: 10px; font-weight: 600; transition: all 0.2s ease; flex: 1; text-decoration: none; box-shadow: 0 4px 6px rgba(40, 167, 69, 0.2); }");
          client.println(".boton:hover { transform: translateY(-2px); opacity: 0.95; }");
          client.println(".boton-off { background-color: #dc3545; box-shadow: 0 4px 6px rgba(220, 53, 69, 0.2); }");
          client.println("</style></head>");
          client.println("<body>");
          client.println("<div class=\"card\">");
          client.println("<h1>Panel de Control ESP32</h1>");
          
          // Caja de Telemetría del Potenciómetro
          client.println("<div class=\"sensor-box\">");
          client.println("<div class=\"sensor-title\">Lectura Potenciómetro (ADC)</div>");
          client.println("<div class=\"sensor-value\">" + String(valorPot) + "</div>");
          client.println("</div>");
          
          // Estado actual del LED
          client.println("<div class=\"status-box\">Estado LED: <span style=\"color:" + String(estadoLED == "ENCENDIDO" ? "#28a745" : "#dc3545") + "; font-weight:bold;\">" + estadoLED + "</span></div>");
          
          // Botones de Control
          client.println("<div class=\"btn-container\">");
          client.println("<a href=\"/LED=ON\" class=\"boton\">ENCENDER</a>");
          client.println("<a href=\"/LED=OFF\" class=\"boton boton-off\">APAGAR</a>");
          client.println("</div>");
          
          client.println("</div>");
          client.println("</body></html>");
          
          client.println();
          break; 
        }
      }
    }
    client.stop();
    Serial.println("Cliente desconectado.\n");
  }
}