/* Test your Gkos with the Serial Monitor of the Arduino IDE

This is a simple test to check that your GKOS keypad is
working, by showing on serial monitor the text you type.

*/

#include <Gkos.h>

  char* gEntry = ""; 

// Initialize Gkos library with pin numbers for keys A to F.
// Digital pins 14...19 are the same as analog pins 0...5
  Gkos gkos(7, 6, 5, 4, 3, 2);
//  Gkos gkos(2, 3, 4, 5, 6, 7);
//  Gkos gkos(14, 15, 16, 17, 18, 19);

void setup(){

  Serial.begin(9600); // Set up Serial library at 9600 bps.
  // Use the Arduino SDE Serial Monitor to view the output! 
  // initialize keyboard control:
  Keyboard.begin();  

}

void loop(){

  gEntry = gkos.entry(); // Will return empty immediately if no entry
  //if (gEntry != 0){gPrint();}
  if (strcmp(gEntry, "") != 0){gPrint();}

  // Add your other code here

}

void gPrint(){ // Convert commands depending on your application
  
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

//Teclas especiales a procesar
  if (strcmp(gEntry, "_Up") == 0){
     Keyboard.write(KEY_UP_ARROW);return;
  }
  if (strcmp(gEntry, "_Down") == 0){
     Keyboard.write(KEY_DOWN_ARROW);return;
  }
  if (strcmp(gEntry, "_PgUp") == 0){
     Keyboard.write(KEY_PAGE_UP);return;
  }
  if (strcmp(gEntry, "_PgDn") == 0){
     Keyboard.write(KEY_PAGE_DOWN);return;
  }
  if (strcmp(gEntry, "_BS") == 0){
      //Keyboard.press(KEY_BACKSPACE); Keyboard.release(KEY_BACKSPACE);return;
     Keyboard.write(KEY_BACKSPACE);return;
  }
  if (strcmp(gEntry, "_Left") == 0){
     Keyboard.write(KEY_LEFT_ARROW);return;
  }
  if (strcmp(gEntry, "_WLeft") == 0){
     Keyboard.write('#');return;
  }
  if (strcmp(gEntry, "_Home") == 0){
     Keyboard.write(KEY_HOME);return;
  }
  if (strcmp(gEntry, "_Right") == 0){
     Keyboard.write(KEY_RIGHT_ARROW);return;
  }
  if (strcmp(gEntry, "_WRight") == 0){
     Keyboard.write('#');return;
  }
  if (strcmp(gEntry, "_End") == 0){
     Keyboard.write(KEY_END);return;
  }
  if (strcmp(gEntry, "_Enter") == 0){
     Keyboard.write(KEY_RETURN);return;
  }
  if (strcmp(gEntry, "_Tab") == 0){
     Keyboard.write(KEY_TAB);return;
  }
  if (strcmp(gEntry, "_Esc") == 0){
     Keyboard.write(KEY_ESC);return;
  }
  if (strcmp(gEntry, "_Del") == 0){
     Keyboard.write(KEY_DELETE);return;
  }
  if (strcmp(gEntry, "_Ins") == 0){
     Keyboard.write(KEY_INSERT);return;
  }
//Modificadores
/*  if (strcmp(gEntry, "_Shift") == 0){
     Keyboard.write(KEY_LEFT_SHIFT);return;
  }
*/
  if (strcmp(gEntry, "_Ctrl") == 0){
     Keyboard.press(KEY_LEFT_CTRL);return;
  }
  if (strcmp(gEntry, "_Alt") == 0){
     Keyboard.press(KEY_RIGHT_ALT);return;
  }

//Para pruebas con otros comandos
/*  if (strcmp(gEntry, "a") == 0){
     Keyboard.write(gEntry[0]);Keyboard.press(gEntry[0]);
     Keyboard.releaseAll();
     return;
  }
*/

  // Default 
  //Keyboard.print(gEntry); 
  //Keyboard.write(gEntry[0]); 
  //int iEntry=int(gEntry); Creo que usando write en lugar de print obedece Ctrl y Alt
  Keyboard.press(gEntry[0]);
  //Liberar si existen teclas de funcion presionadas
  Keyboard.releaseAll();
}
