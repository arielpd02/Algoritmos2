# TP3 - Implementación

## Cambios en estructura

* En `Lollapatuza` cambiamos `puestosHackeablesPorPersona` para que el significado del último diccLog sea
  `tupla(itPuesto, nat)` en vez de `tupla(puesto, nat)` dado que en ese diccionario, como primer elemento
  de la tupla, necesitamos apuntar de alguna manera al mismo puesto que se encuentra guardado en `puestos`;
  esto porque no queremos modificar una copia del mismo.

## Comentarios

* Simplificamos varios algoritmos utilizando el hecho de que para el `map`, el `operator[]`, si la clave
  no existe, utiliza el constructor default de la clase. Ver: https://cplusplus.com/reference/map/map/operator[]/