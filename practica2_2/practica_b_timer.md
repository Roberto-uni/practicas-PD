
---

## Práctica B: Interrupción por Timer

En esta segunda parte se implementa una interrupción periódica mediante el uso de un temporizador del ESP32.  
El temporizador se configura para que genere una interrupción cada segundo, utilizando el preescalador y el contador interno del ESP32.

Cada vez que se alcanza el valor programado en el temporizador (1.000.000 µs = 1s), se ejecuta la rutina de interrupción `onTimer()`, que incrementa un contador de forma segura utilizando `portENTER_CRITICAL_ISR` y `portEXIT_CRITICAL_ISR`.

En el bucle principal (`loop()`), se verifica si hay interrupciones pendientes (`interruptCounter > 0`), y si es así, se actualiza el contador total de interrupciones (`totalInterruptCounter`) y se muestra por el monitor serie.

### Salida esperada en el monitor serial:
```
An interrupt has occurred. Total number: 1
An interrupt has occurred. Total number: 2
An interrupt has occurred. Total number: 3
...
```

---
