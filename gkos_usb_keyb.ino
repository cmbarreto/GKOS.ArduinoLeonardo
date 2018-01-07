/* Functional Combokey (GKOS) implementation
   Basede on arduino leonardo compatible hardware

This is a working GKOS keypad.
Use a gkos library writen in C 

Based on:
http://gkos.com/gkos/index-gkos-com.html
http://www.gkos.net/gkos-net-index.html
http://gkos.com/gkos/arduino/index.html

*/

#include <Gkos.h>

char* gEntry = "";
char* gLastEntry = "";

//Define variables to act as a mouse
// set pin numbers for the six buttons:
// Must coincide with gkos pins as shown below
const int upButton = 2;
const int downButton = 6;
const int leftButton = 3;
const int rightButton = 5;
const int mouseButton = 4;
const int mouseleftButton = 7;

int range = 5;              // output range of X or Y movement; affects movement speed
int responseDelay = 10;     // response delay of the mouse, in ms
bool myMouseMode = false;            //mouse mode 0 keyboard mode 1 mouse mode



// Initialize Gkos library with pin numbers for keys A to F.
// Digital pins 14...19 are the same as analog pins 0...5
//Pro Micro invertida
//  Gkos gkos(7, 6, 5, 4, 3, 2);

//Pro Micro
Gkos gkos(2, 3, 4, 5, 6, 7);

//Leonardo chiquita
//Gkos gkos(0, 1, 2, 3, 9, 10);

//  Gkos gkos(14, 15, 16, 17, 18, 19);

void setup() {
//  int mmode = (mouseMode(1));
//  Serial.println(mouseMode(2));
  Serial.begin(9600); // Set up Serial library at 9600 bps.
  // Use the Arduino SDE Serial Monitor to view the output!
  // initialize keyboard control:
  Keyboard.begin();
  // initialize mouse control:
  Mouse.begin();
}

void loop() {
    //Serial.println(myMouseMode);
    //Serial.println("loop");
    //if ( (mouseMode(2)) == 0 ) {
    if ( !myMouseMode ) {
        gEntry = gkos.entry(); // Will return empty immediately if no entry
        //if (gEntry != 0){gPrint();}
        if (strcmp(gEntry, "") != 0) {
          gPrint();
          gLastEntry = gEntry;
        }
    } else {
      gMouse();
    };
  // Add your other code here
}

void gPrint() { // Convert commands depending on your application

  /*  if (strcmp(gEntry, "_Enter") == 0){
        //Serial.writeln("");
        Serial.write(10); Serial.write(13); return;
    }
    if (strcmp(gEntry, "_BS") == 0){
        Serial.write(8); return;
    }
    if (strcmp(gEntry, "_Del") == 0){
        Serial.write(127); return;
    }
    if (strcmp(gEntry, "_Tab") == 0){
        Serial.write(9); return;
    }

    // Default
    Serial.write(gEntry);
  */

  //Manejo del mouse
  if (strcmp(gEntry, "_MOUSE_MODE") == 0) {
    //int mmode = (mouseMode(1)); Serial.println(mouseMode(2)); return;
    //Serial.println(gEntry);    
    //Serial.println("gPrint");    
    //Serial.println(myMouseMode);
    myMouseMode = true; delay(responseDelay * 30);
    Keyboard.end(); Mouse.begin();
    Keyboard.releaseAll();
    return;
  }
  
  if (String(gEntry).substring(0, 4) == "_XYM") {
    String stringXY = String(gEntry).substring(4);
    int posComa = stringXY.indexOf(',');
    String strX = stringXY.substring(0, posComa);
    String strY = stringXY.substring(posComa + 1);
    //Keyboard.print(strX);Keyboard.print(":");Keyboard.print(strY);
    // move mouse
    /*if (gLastEntry == gEntry){
       Mouse.move(strX.toInt()*10, strY.toInt()*10);
    } else {
       Mouse.move(strX.toInt(), strY.toInt());
    };
    gLastEntry = gEntry;return;*/
    Mouse.move(strX.toInt(), strY.toInt()); return;
  }

  if (strcmp(gEntry, "_MOUSE_LEFT") == 0) {
    Mouse.click(MOUSE_LEFT); return;
  }

  if (strcmp(gEntry, "_MOUSE_RIGHT") == 0) {
    Mouse.click(MOUSE_RIGHT); return;
  }

  if (strcmp(gEntry, "_MOUSE_SELECT") == 0) {
    if (Mouse.isPressed() == 0) {
      Mouse.press();
    } else {
      Mouse.release();
    };
    return;
  }

  //Teclas especiales a procesar
  //Codigos en arduino-1.0.5/hardware/arduino/cores/arduino/USBAPI.h
  if (strcmp(gEntry, "_Up") == 0) {
    Keyboard.write(KEY_UP_ARROW); return;
  }
  if (strcmp(gEntry, "_Down") == 0) {
    Keyboard.write(KEY_DOWN_ARROW); return;
  }
  if (strcmp(gEntry, "_PgUp") == 0) {
    Keyboard.write(KEY_PAGE_UP); return;
  }
  if (strcmp(gEntry, "_PgDn") == 0) {
    Keyboard.write(KEY_PAGE_DOWN); return;
  }
  if (strcmp(gEntry, "_BS") == 0) {
    //Keyboard.press(KEY_BACKSPACE); Keyboard.release(KEY_BACKSPACE);return;
    Keyboard.write(KEY_BACKSPACE); return;
  }
  if (strcmp(gEntry, "_Left") == 0) {
    Keyboard.write(KEY_LEFT_ARROW); return;
  }
  if (strcmp(gEntry, "_WLeft") == 0) {
    Keyboard.write('#'); return;
  }
  if (strcmp(gEntry, "_Home") == 0) {
    Keyboard.write(KEY_HOME); return;
  }
  if (strcmp(gEntry, "_Right") == 0) {
    Keyboard.write(KEY_RIGHT_ARROW); return;
  }
  if (strcmp(gEntry, "_WRight") == 0) {
    Keyboard.write('#'); return;
  }
  if (strcmp(gEntry, "_End") == 0) {
    Keyboard.write(KEY_END); return;
  }
  if (strcmp(gEntry, "_Enter") == 0) {
    Keyboard.write(KEY_RETURN); return;
  }
  if (strcmp(gEntry, "_Tab") == 0) {
    Keyboard.write(KEY_TAB); return;
  }
  if (strcmp(gEntry, "_Esc") == 0) {
    Keyboard.write(KEY_ESC); return;
  }
  if (strcmp(gEntry, "_Del") == 0) {
    Keyboard.write(KEY_DELETE); return;
  }
  if (strcmp(gEntry, "_Ins") == 0) {
    Keyboard.write(KEY_INSERT); return;
  }
  //Modificadores
  if (strcmp(gEntry, "_Shift") == 0) {
    if (gLastEntry == gEntry) {
      Keyboard.write(KEY_CAPS_LOCK);
      Keyboard.releaseAll();
    }
    else {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    return;

  }
  if (strcmp(gEntry, "_Ctrl") == 0) {
    Keyboard.press(KEY_LEFT_CTRL); return;
  }
  if (strcmp(gEntry, "_Alt") == 0) {
    Keyboard.press(KEY_RIGHT_ALT); return;
  }

  //Para pruebas con otros comandos
  /*  if (strcmp(gEntry, "a") == 0){
       Keyboard.write(gEntry[0]);Keyboard.press(gEntry[0]);
       Keyboard.releaseAll();
       return;
    }
  */

  // Default
  Keyboard.print(gEntry);
  //Keyboard.write(gEntry[0]);
  //int iEntry=int(gEntry); Creo que usando write en lugar de print obedece Ctrl y Alt
  //Keyboard.press(gEntry[0]);
  //Liberar si existen teclas de funcion presionadas
  Keyboard.releaseAll();
}

void gMouse() {  //Para cuando funciona como mouse
  // read the buttons:
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  int clickRightState = digitalRead(mouseButton);
  int clickLeftState = digitalRead(mouseleftButton);

  int totalPress = 0;


  // calculate the movement distance based on the button states:
  int  xDistance = (leftState - rightState) * range;
  int  yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }
  else {
      //If all are pressed change to keyboard mode mouseMode = 0
      totalPress = upState + downState + rightState + leftState + clickRightState + clickLeftState;
      //Serial.println("gMouse");
      //Serial.println(totalPress);
      if (totalPress == 0) {
        myMouseMode = false;
        Mouse.release(MOUSE_ALL);
        delay(responseDelay * 30);
        Keyboard.begin(); Mouse.end();
        return;
      }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
  
  // if the mouse button is pressed:
  if (clickLeftState != HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  //if (clickLeftState == HIGH) {
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (clickRightState != HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  // else the mouse button is not pressed:
  //if (clickRightState == HIGH) {
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }

}


