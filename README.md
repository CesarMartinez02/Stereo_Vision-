# Stereo Vision Demo – OpenCV 4.12.0

Este proyecto es un ejemplo básico de visión estéreo usando C++ y OpenCV 4.12.  
Carga dos imágenes estéreo, calcula el mapa de disparidad.

---

## Archivos necesarios

- `code.cpp` → Código fuente principal.
- `left.jpeg` → Imagen izquierda.
- `right.jpeg` → Imagen derecha.

Colocar las dos imágenes en la misma carpeta del proyecto.

---

## Compilación

Compila en Linux:

```bash
g++ code.cpp -o stereo_demo $(pkg-config --cflags --libs opencv4)
```
Preferiblemente:

```bash
g++ code.cpp -o stereo_demo pkg-config --cflags opencv4 \
-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_imgcodecs
```
EJecución:

```bash
./stereo_demo
```
