# Practica 3 Roberto

## INFORME PRÁCTICA 3: Wifi y Bluetooth  
**Autor:** Roberto Dos Ramos  


---

## Wifi

La primera parte de esta práctica consistió en la configuración de un servidor web con la placa ESP32 utilizando el código aportado. Con este se configura la ESP32 con el SSID y contraseña de una red WiFi (en este caso el punto de acceso del móvil), después se inicializa un servidor web en el puerto 80, se define una función que genera una página HTML simple para mostrar en el navegador y después se escribe el código que se encargará de conectar la placa a la red, mostrando por el terminal unos mensajes que nos indiquen lo que está ocurriendo (`try connecting to` cuando empieza a funcionar, `wifi connected successfully`, etc.).

Una vez implementado y cargado en la placa, si se logró conectar a la red, aparecerá el siguiente mensaje por el terminal:

try connecting to 
"RedmiNote7" 
... 
WiFi connected succesfully 
Got IP: 192.168.43.73 
HTTP server started 

Usando la dirección IP generada, cualquier dispositivo que esté conectado a la misma red podrá acceder a la página web generada en nuestro servidor.

---

## Bluetooth (BLE)

Para esta parte de la práctica solo se comprobó el funcionamiento del BLE (Bluetooth Low Energy) en la placa ESP32 mediante el código aportado. En este se genera un servidor de BLE que “pretende” enviar la temperatura a cualquier dispositivo conectado, generando un valor aleatorio entre 20 y 30.

Para conectar el dispositivo se utilizó la aplicación **nRF Connect**.

> Lamentablemente, no se logró que se mostrara la temperatura.


