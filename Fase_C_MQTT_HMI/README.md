# Fase C: Protocolo MQTT, Broker y Visualización Web (HMI)

## 📋 1. Objetivo de la Fase
Aplicar el protocolo de mensajería MQTT para establecer un sistema distribuido, utilizando un broker en la nube para enviar lecturas de sensores y recibir comandos de control de manera bidireccional entre el ESP32 y una interfaz web HMI profesional[cite: 3].

---

## 🛠️ 2. Materiales y Componentes
* Tarjeta de desarrollo ESP32 Dev Module.
* Potenciómetro conectado a la entrada analógica (GPIO 34).
* LED externo con su respectiva resistencia de protección (GPIO 33).
* Servomotor (GPIO 25).
* Red Wi-Fi con conexión a internet.
* Broker MQTT público (ej. `broker.emqx.io`).
* Interfaz HMI web (`index.html`) alojada en una plataforma en la nube (como Netlify o GitHub Pages).

---

## 🔌 3. Conexiones Físicas
1. **Potenciómetro:** Pin central conectado al **GPIO 34** (entrada ADC), extremos a 3.3V y GND.
2. **LED Externo:** Ánodo conectado al **GPIO 33** a través de resistencia, cátodo a GND.
3. **Servomotor:** Señal de control PWM conectada al **GPIO 25**, VCC a 5V y GND común.

---

## 🚀 4. Procedimiento y Paso a Paso

1. **Configuración de Tópicos (Grupo 4):** Definir la estructura jerárquica de tópicos MQTT para evitar interferencias, utilizando canales específicos para el envío del potenciómetro, control del LED, control del servomotor y reporte de su estado.
2. **Carga del Firmware:** Compilar y subir el programa en C++ al ESP32, asegurando la correcta conexión Wi-Fi y la suscripción a los tópicos del broker público.
3. **Despliegue de la Interfaz HMI:** 
   * Asegurar que el archivo `index.html` contenga la lógica de WebSockets para conectarse al broker MQTT.
   * Publicar la página web mediante Netlify o GitHub Pages para obtener un enlace público y permanente accesible desde cualquier dispositivo.
4. **Prueba de Funcionamiento:**
   * Alimentar el ESP32 de forma autónoma (por ejemplo, mediante un adaptador de corriente en un enchufe).
   * Abrir el enlace de la interfaz web HMI desde un teléfono celular o computador.
   * Validar la actualización en tiempo real de los valores del potenciómetro y comprobar la respuesta inmediata de los actuadores (LED y servomotor) al interactuar con los botones de control web.
