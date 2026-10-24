# Fase A: Comunicación Bluetooth con ESP32

## 📋 1. Objetivo de la Fase
Establecer un canal de comunicación inalámbrico bidireccional mediante Bluetooth clásico (Serial Bluetooth) entre el microcontrolador ESP32 y un teléfono inteligente para el envío de datos y el control remoto de actuadores[cite: 5].

---

## 🛠️ 2. Materiales y Componentes
* Tarjeta de desarrollo ESP32 Dev Module.
* LED indicador (externo con resistencia de 220Ω o uso del LED integrado).
* Cables de conexión (jumpers).
* Smartphone con una aplicación de terminal Bluetooth (ej. *Serial Bluetooth Terminal*).

---

## 🔌 3. Conexión Física
1. Conectar el ánodo (pata larga) del LED a través de la resistencia al pin digital configurado en el ESP32.
2. Conectar el cátodo (pata corta) del LED al pin **GND** de la placa.

---

## 🚀 4. Procedimiento y Paso a Paso

1. **Configuración del entorno:** Abrir Arduino IDE, seleccionar la placa ESP32 y asegurar la correcta instalación de la librería de Bluetooth Serial.
2. **Carga del firmware:** Compilar y subir el código correspondiente a la Fase A al ESP32.
3. **Emparejamiento Bluetooth:** 
   * Activar el Bluetooth en el celular y buscar los dispositivos disponibles.
   * Seleccionar y vincular el dispositivo con el nombre asignado (ej. `ESP32_Grupo4_BT`).
4. **Prueba de comunicación:**
   * Abrir la aplicación de terminal Bluetooth en el teléfono y conectarse al ESP32.
   * Enviar el carácter `1` a través de la terminal para verificar el encendido del LED.
   * Enviar el carácter `0` para comprobar el apagado del LED en tiempo real.
