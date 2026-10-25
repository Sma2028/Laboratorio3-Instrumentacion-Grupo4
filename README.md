# 🏭 Laboratorio de Instrumentación Industrial - Grupo 4

Repositorio oficial que recopila el desarrollo, los códigos fuente, las configuraciones y la documentación técnica correspondiente al laboratorio de instrumentación industrial de la **Universidad Nacional de Colombia**.

---

## 👥 Integrantes y Datos Generales
* **Estudiante:** Sofía Marín Albarracín, Carlos Andres Ceron Nogera, Kevin Alexander Ordoñez Arcos
* **Institución:** Universidad Nacional de Colombia
* **Grupo de Trabajo:** Grupo 4

---

## 🎯 Objetivo General del Proyecto
Comprender, implementar y validar interfaces de comunicación inalámbrica y protocolos industriales en sistemas embebidos, integrando microcontroladores ESP32 con sensores, actuadores y plataformas en la nube para el monitoreo y control remoto en tiempo real[cite: 3].

---

## 📂 Estructura General del Repositorio

El proyecto se encuentra organizado en fases modulares que reflejan el avance de la práctica:

* **`/Fase_A_Bluetooth`**: 
  * Implementación de la comunicación inalámbrica por Bluetooth Serial (Bluetooth Clásico) entre el ESP32 y un dispositivo móvil.
  * Control de un indicador LED mediante comandos enviados desde una terminal en el smartphone.

* **`/Fase_B_Servidor_Web`**: 
  * Configuración del microcontrolador ESP32 como un servidor web autónomo dentro de una red Wi-Fi local.
  * Visualización de estados y control de salidas directamente desde un navegador web conectado a la misma red local.

* **`/Fase_C_MQTT_HMI`**: 
  * Implementación de un sistema distribuido basado en el protocolo MQTT utilizando un broker público en la nube (`broker.emqx.io`).
  * Integración de hardware metrológico y de control: potenciómetro (entrada analógica GPIO 34), LED externo (GPIO 33) y servomotor (GPIO 25).
  * Interfaz HMI web profesional (`index.html`) alojada en la nube (Netlify / GitHub Pages) para la supervisión y gestión bidireccional a distancia.

* **`/.vscode/`**: 
  * Carpeta de configuración del entorno de desarrollo para asegurar la consistencia en la compilación y las propiedades del código en C++.

---

## 🌐 Enlaces de Acceso Web (HMI Remota)
* **Panel de Control HMI (Fase C):** https://gilded-banoffee-69c306.netlify.app

---

## 🛠️ Resumen de Tecnologías y Herramientas
* **Hardware:** Tarjeta ESP32 Dev Module, Potenciómetro, LED con resistencia de protección, Servomotor, fuente de alimentación autónoma.
* **Software y Entornos:** Arduino IDE, Visual Studio Code.
* **Librerías Principales:** `WiFi`, `BluetoothSerial`, `PubSubClient`, `ESP32Servo`.
* **Protocolos de Red:** HTTP, WebSockets, MQTT.
