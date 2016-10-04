#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE(); //  esto es propio de la librería midi en este caso no necesitamos customizar nada

#define TOTAL_PINS 6

float  buffer_val[TOTAL_PINS];  //  esto podríamos no usarlo pero va, esta construido por si queremos interpolar(fade por ej)
//  entre los valores que tenemos y llegan


int output_pins[] = {3, 5, 6, 9, 10, 11}; //  los pines que vamos a usar de outputs.
//  con esto mapeamos (nota - pin de salida) :
//  siendo que C-2 es la nota con indice 0 por ende va al pin 3, que es el valor 0 del array, o ROJO de la tira 1

void setup() {
  /*  iniciamos el buffer en 0 */
  for (int i = 0; i < TOTAL_PINS; i++)
  {
    buffer_val[i] = 0;
  }
  /*  abrimos los pines  */
  for (int i = 0; i < TOTAL_PINS; i++)
  {
    pinMode(output_pins[i], OUTPUT);
  }
  /*  midi stuff  */
  MIDI.begin();
}

void loop() {

  if (MIDI.read())
  {
    if (MIDI.getData1() < TOTAL_PINS) { //  chequeamos que el indice de nota que recibimos no es mas grande que nuestro buffer, sino crash
      int   midi_index = MIDI.getData1(); //  el indice de la nota (esto dice a que pin va a parar la variable "midi_val"
      float midi_val = map(MIDI.getData2(), 0, 127, 0, 255);  //  velocity  de la nota (esto regula la intensidad de cada color),
                                                              // lo mapeamos de midi (0..127) a color (0..255)
      switch (MIDI.getType()) //  los mensajes midi pueden ser Notas Prendida, Nota Apagada, Control Change,etc. Aca preguntamos eso
      {
        case midi::NoteOn:                    //  Nota encendida, prendemos led. "midi::NoteOn" es una constante que identifica que tipo de mensaje
                                              //  que tenga "midi::" implica que es propio de la librería MIDI, tecnicamente se llaman "namespace"
                                              
          buffer_val[midi_index] = midi_val;  //  guardamos en el buffer el valor
          write_pin(midi_index);              //  lo escribimos
          break;
        case midi::NoteOff:
          buffer_val[midi_index] = 0;         //  lo mismo que en NoteOn
          write_pin(midi_index);
          break;
        default:
          break;
      }
    }
  }
}

void  write_pin(int _index)
{
  //  escribo en el pin dado por el index, el valor dado por el index dentro del buffer
  analogWrite(output_pins[_index], buffer_val[_index]);
}

