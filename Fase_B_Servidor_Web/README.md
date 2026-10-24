# Fase B: Servidor Web Local Wi-Fi con ESP32

## 📋 1. Objetivo de la Fase
Configurar el microcontrolador ESP32 como un servidor web autónomo dentro de una red Wi-Fi local, permitiendo visualizar datos de sensores y controlar salidas digitales directamente desde el navegador web de cualquier dispositivo conectado a la misma red[cite: 4].

---

## 🛠️ 2. Materiales y Componentes
* Tarjeta de desarrollo ESP32 Dev Module.
* Actuador o indicador (LED externo o integrado).
* Red Wi-Fi local de 2.4 GHz.
* Dispositivo de visualización (Computador o Smartphone conectado a la misma red).

---

## 🔌 3. Conexiones Físicas
1. Conectar el LED indicador al pin digital designado en el ESP32 (junto con su respectiva resistencia de protección).
2. Asegurar la alimentación estable de la placa mediante el puerto USB o fuente externa.

---

## 🚀 4. Procedimiento y Paso a Paso

1. **Configuración de Red:** Modificar en el código fuente los parámetros de conexión (`SSID` y contraseña) para enlazarlo a la red Wi-Fi local.
2. **Cargar el Firmware:** Compilar y subir el programa del servidor web HTTP al ESP32 utilizando Arduino IDE.
3. **Obtención de la Dirección IP:** 
   * Abrir el monitor serial de Arduino IDE con una velocidad de 115200 baudios.
   * Reiniciar el ESP32 y verificar el mensaje de conexión exitosa para anotar la **dirección IP local** asignada (por ejemplo: `192.168.1.X`).
4. **Acceso al Servidor Web:**
   * Conectar un teléfono celular o un computador a la **misma red Wi-Fi** del ESP32.
   * Abrir el navegador web e introducir la dirección IP obtenida en la barra de direcciones.
5. **Control y Visualización:** Interactuar con los botones y campos de la interfaz web local para verificar la respuesta del sistema y el cambio de estado de las salidas en tiempo real.
