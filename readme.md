Convierte un Arduino en un device MIDI, permite recibir notas y con esto, manipular luces.
La ventaja de esto es que el músico puede programar sus luces directamente enviando MIDI,sin tener que recurrir a aplicaciones en medio.
Aun hay que conocer un poco de Arduino, pero queda pendiente (a la brevedad estará) armar funciones que lo simplifiquen.

HOWTO

(Tutorial en Ingles, que use como guía: http://morecatlab.akiba.coocan.jp/lab/index.php/aruino/midi-firmware-for-arduino-uno-moco/?lang=en)

Debemos flashear el Arduino para que funcione como MIDI device, hay muchas librerías para lograr esto, particularmente usaremos ModoLufa, que a diferencia de las otras, en las cuales, es necesario reflashear el dispositivo a Arduino o Midi, cada vez que querramos cambiar nuestro funcionamiento. MocoLufa permite que mediante un jumper cambiar de modo Arduino a MIDI. Muy simple y práctico.

Previa

Para esto y para el posterior desarrollo, necesitamos tener un JUMPER. Vienen de varias maneras, una por ejemplo: (http://www.gikfun.co/images/gikfun/EK1120.jpg)

Bajamos MocoLufa:

https://github.com/kuwatay/mocolufa

Para Flashear el Arduino, seguir los siguientes pasos.

https://www.arduino.cc/en/Hacking/DFUProgramming8U2

NOTA
(yo realicé el proceso en OSX, en Windows puede diferir en base a la herramienta para flashear, recomendada por la página de Arduino)

En el tutorial, en el punto "Program the chip", el segundo comando en terminal a ejecutar es:

sudo dfu-programmer atmega16u2 flash Arduino-usbserial-uno.hex

En nuestro caso sería:

sudo dfu-programmer atmega16u2 flash dualMoco.hex

Donde "dualMoco.hex" es el archivo dentro de la carpeta HEX, que bajamos con la librería MocoLufa.

Ahora el código:

Para poder trabajar con MIDI en Arduino precisamos la librería MIDI: http://playground.arduino.cc/Main/MIDILibrary

IMPORTANTE

Para poder programar y cargar nuestro sketch en Arduino, necesitamos poner el Jumper, en los siguientes puertos:
http://morecatlab.akiba.coocan.jp/lab/wp-content/uploads/2013/09/IMGP9378.jpg

El sketch (ArduinoMIDILighthing.ino) de arduino es muy simple, y esta disponible en este repo, está totalmente comentado en español.
Esta pensando en un esquema de tiras RGB, donde la nota con indice 0 (C-2) es usadada como el color rojo de la tira 1 y así en adelante, lo importante ocurre a partir de la linea 37, donde se recibe el Note On o Note Of de Midi. 

Una vez hayamos cargado, lo podemos quitar y esto hace que sea reconocido por el sistema como un device Midi llamado "MocoLufa".

