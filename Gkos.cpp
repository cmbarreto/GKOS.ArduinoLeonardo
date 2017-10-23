/*
  Gkos.cpp - Library for reading GKOS keyboard.
  Created by Seppo Tiainen, March 28, 2010.
  Released into the public domain.
*/

// #include <stdio.h>
// #include <string.h>
// #include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Gkos.h"



	// Usage in your sketch:
	// #include <Gkos.h>
	// Gkos gkos(14, 15, 16, 17, 18, 19); // E.g. analog pins 0 to 5 (= digital 14 to 19)
					      // are used for GKOS keys A to F.
	// gkos.entry(); // will return empty if no character entered, else with the character


// Initialize Class Variables //////////////////////////////////////////////////
//estos pines son para representar modos ej. 123abc, SYMB, etc.
uint8_t numPin;
//uint8_t  capsPin;
//uint8_t  fnPin;

// Constructors ////////////////////////////////////////////////////////////////

Gkos::Gkos(uint8_t APin, uint8_t BPin, uint8_t CPin, uint8_t DPin, uint8_t EPin, uint8_t FPin)
{
  //pinMode(pin, OUTPUT); // examples
  //_pin = pin;

  pinMode(APin, INPUT);  // Use the defined pins as digital inputs
  _key_pins[1] = APin;
  pinMode(BPin, INPUT);  
  _key_pins[2] = BPin;
  pinMode(CPin, INPUT);  
  _key_pins[3] = CPin;
  pinMode(DPin, INPUT);  
  _key_pins[4] = DPin;
  pinMode(EPin, INPUT);  
  _key_pins[5] = EPin;
  pinMode(FPin, INPUT);  
  _key_pins[6] = FPin;
  
  //estos pines son para representar modos ej. 123abc, SYMB, etc.
  numPin = 13;  //Lo probamos con 17 el onboard del pro micro en mi gkos es 8, Leonardo es 13;
  //capsPin = 9;
  //fnPin = 10;
  pinMode(numPin, OUTPUT);
  //pinMode(capsPin, OUTPUT); //Caps Look es una tecla de control por lo 
                            //que se gestiona en el sketch arduino
  //pinMode(fnPin, OUTPUT);

  digitalWrite(_key_pins[1], HIGH); // Turn on the 20k pullup resistors
  digitalWrite(_key_pins[2], HIGH);
  digitalWrite(_key_pins[3], HIGH);
  digitalWrite(_key_pins[4], HIGH);
  digitalWrite(_key_pins[5], HIGH);
  digitalWrite(_key_pins[6], HIGH);

  _key_down[1] = 0; // State of GKOS keys.
  _key_down[2] = 0;
  _key_down[3] = 0;
  _key_down[4] = 0;
  _key_down[5] = 0;
  _key_down[6] = 0;

  // Defaults
  _gRef = 0; // Character index within the set (0...63)
  _shifts = 0;
  _time = 0;
  _previousTime = 0;
  _gChord = 0; // GKOS final chord value (0...63) for the character
  _presentChord = 0; // The chord of the keypad at present
  _previousChord = 0;// To compare chord change
  _firstChord = 0;   // First chord of a Chordon, if any
  _firstCounter = 0; // Count to detect a separate first chord in a Chordon
  _autoRepeat = 0;   // Repeat the character if chord pressed long enough (0 or 1)
  _autoCounter = 0;  // Typamatic delay counter (n x 10 ms)
  _gNew = false; // a new character is expected soon because new keys were pressed


}


// Public Methods //////////////////////////////////////////////////////////////

char* Gkos::entry()
{

 char* gOutput[] = {"qwertyui"};

// Store the character tables below in the flash ROM
// Just differing parts are stored to save ROM space

	// GKOS Reference number based on Chord value
const static int _gChord2_gRef[] = {0, 1, 2, 15, 3, 27, 19, 46, 4, 42, 36, 16, 33, 28, 20, 47, 5, 35, 59, 17, 32, 29, 21, 48, 7, 8, 9, 44, 10, 41, 38, 56, 6, 34, 31, 18, 43, 30, 22, 49, 23, 24, 25, 58, 26, 60, 40, 62, 11, 12, 13, 37, 14, 39, 45, 63, 50, 51, 52, 54, 53, 55, 57, 61};
	// Parallel GKOS character sets for lower case, caps, shift (upper case), numbers and symbols
const static char* _gChar[]={"NULL" , "a" , "u" , "c" , "i" , "e" , "r" , "t" , "h" , "g" , "j" , "n" , "\u0027a" , "b" , "k" , "o" , "p" , "f" , "q" , "s" , "w" , "m" , "v" , "l" , "x" , "y" , "z" , "d"  , "\'u"     , "\'e"    , "\'o"   , "." , "," , "!" , "?" , "-" , "\'" , "\\" , "/" , "ñ"    , "ü"      , "\'i", "_Up", "_Down", "_PgUp", "_PgDn", "_BS", "_Left", "_WLeft", "_Home", " ", "_Right", "_WRight", "_End", "_Enter", "_Tab", "_Esc", "_Del", "_Ins", "_Shift", "_SYMB", "_123abc", "_Ctrl", "_Alt" };

// SHFT (Shift): (NULL +) only first 41 may differ from lower case 
const static char* _gSHFT[]={ "NULL" , "A" , "U" , "C" , "I" , "E" , "R" , "T" , "H" , "G" , "J" , "N" , "\'A" , "B" , "K" , "O" , "P" , "F" , "Q" , "S" , "W" , "M" , "V" , "L" , "X" , "Y" , "Z" , "D"  , "\'U"     , "\'E"    , "\'O"   , "." , "," , "¡" , "¿" , "_" , "\'" , "\\" , "/" , "Ñ"    , "Ü"      , "\'I"};

// CAPS: (NULL +) only first 41 characters are different from lower case (_gChar[])
const static char* _gCAPS[]={ "NULL" , "A" , "U" , "C" , "I" , "E" , "R" , "T" , "H" , "G" , "J" , "N" , "\'A" , "B" , "K" , "O" , "P" , "F" , "Q" , "S" , "W" , "M" , "V" , "L" , "X" , "Y" , "Z" , "D"  , "\'U"     , "\'E"    , "\'O"   , "." , "," , "!" , "?" , "-" , "\'" , "\\" , "/" , "Ñ"    , "Ü"      , "\'I"};

// NUMS: (NULL +) only first 41 may differ from lower case
const static char* _gNUMS[]={"NULL" , "1" , "2" , "3" , "4" , "5" , "6" , "0" , "7" , "8" , "9" , "#" , "@" , "½" , "&" , "+" , "%" , "^" , "=" , "*" , "$" , "€" , "£" , "(" , "[" , "<" , "{" , ")"  , "]"     , ">"    , "}"   , "." , "," , "|"  , "~" , "-" , "\'" , "\\" , "/" , "μ"    , " ̈" , "ª"};

const static char* _gSYMB[]={"NULL" , "1" , "2" , "3" , "4" , "5" , "6" , "0" , "7" , "8" , "9" , "#" , "@" , "½" , "&" , "+" , "%" , "^" , "=" , "*" , "$" , "€" , "£" , "(" , "[" , "<" , "{" , ")"  , "]"     , ">"    , "}"   , ":" , ";" , "|"  , "~" , "_" , "\"" , "`"  , "´" , "μ"    , "§"      , "º", "_Up", "_Down", "_PgUp", "_PgDn", "_BS", "_Left", "_WLeft", "_Home", " ", "_Right", "_WRight", "_End", "_Enter", "_Tab", "_Esc", "_Del", "°", "_Shift", "_SYMB", "_123abc", "_Ctrl", "_Alt" };

// MOUSE (Mouse): (NULL +) only first 41 may differ from lower case 
//const static char* _gMUSE[]={"NULL", "_XYM-40,-40", "Mb", "_XYM-40,40", "_XYM40,-40","Me", "_XYM40,40", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "th", "that ", "the ", "of ", ".", ",", "!", "?", "-", "\'", "\\", "/", "and ", "§", "to ", "_Up", "_Down", "_PgUp", "_PgDn", "_BS", "_Left", "_WLeft", "_Home", " ", "_Right", "_WRight", "_End", "_Enter", "_Tab", "_Esc", "_Del", "_Ins", "_Shift", "_SYMB", "_123abc", "_Ctrl", "_Alt" };
const static char* _gMUSE[]={"NULL", "_XYM-15,-15", "_XYM-15,0", "_XYM-15,15", "_XYM15,-15","_XYM15,0", "_XYM15,15", "_XYM50,-50", "_XYM100,-100", "_MOUSE_SLOW", "", "_XYM50,50", "", "", "_XYM100,100", "_XYM-50,-50", "_XYM-100,-100", "", "", "_XYM-50,50", "", "", "_XYM-100,100", "_MOUSE_RIGHT", "_Down", "", "_Up", "_MOUSE_LEFT", "_PgDn", "", "_PgUp", "", "", "", "", "", "", "", "", "", "", "", "_XYM0,-15", "_XYM0,15", "_XYM0,-100", "_XYM0,100", "_XYM-100,0", "_Left", "_WLeft", "_Home", "_XYM100,0", "_Right", "_WRight", "_End", "_MOUSE_LEFT", "", "_MOUSE_RIGHT", "_Del", "_Ins", "_MOUSE_SELECT", "_SYMB", "_123abc", "_Ctrl", "_Alt" };

	// For other native character tables, see gkos.com


  if (gScanKeys() == true){  // (no scope required here)

	// If it is a Chordon, send it here

/*     if (_firstChord != 0){_firstChord = 0; _firstCounter = 0; // TEMP!!!!
			return "-";} // TODO: combine two characters and return directly
*/
        _firstChord = 0; _firstCounter = 0;  // in any case, delete the first char of Chordon

	// Change between Character sets when Shift/CAPS, 123abc or SYMB are pressed

     switch (_gChord)
	{
/*	case 18: // Shift & Caps (2+16)
		_gRef = 59;
		if (_shifts == 1){_shifts = 2; return "";
		} 
		else {
			if (_shifts == 2){_shifts = 0; return "";
			}
			else {
				if (_shifts == 0){ _shifts = 1; return "";
				}
				else {
				     }
			      }
		       }

	break;	
*/		
	case 63: // 123abc (all keys down)
	  switch (_shifts)
	  {
	    case 4: //esta en modo 123abc se quita el modo  y se apaga el led
	      {_shifts = 0; digitalWrite(numPin, LOW);return "";}
	      break;
	    case 16: //esta en modo Mouse
	      {_shifts = 0; return "";}
	      break;
	    default:
	                {
			  switch (_gRef) //De acuerdo a la entrada previa
			                 //(_gref) se obtiene el modo a tomar
			    {
			    case 59:  //Tecla Shift pasamos a modo Mouse
			      {_shifts = 16; return "";}
			      break;
			    case 44:  //Tecla Arriba _Up pasamos a modo F1 F2... F16
			      break;
			    default: //el cambio por defecto es pasar al modo abc123
			      {_shifts = 4;  digitalWrite(numPin, HIGH); return "";}
			      break;
			    }
			}
	  _gRef = 61;
	  break;
	  }
	case 45: // Symb (1+4+8+32=45)
		_gRef = 60;
		if (_shifts == 8){_shifts = 0; return "";} else {_shifts = 8; return "";}
	break;
        } // end of switch
 

	 // 1=Shift, 2=Caps, 4=Nums, 8=Symb, 16=Mouse

	gOutput[0] = ""; // default

	switch (_shifts)
	{
	case 1:
	 // Shift
		_shifts = 0;
		if (_gChord2_gRef[_gChord] <= 41){gOutput[0] = (char*)_gSHFT[_gChord2_gRef[_gChord]];
		} else {gOutput[0] =  (char*)_gChar[_gChord2_gRef[_gChord]];} // partly same as lower case
	break;

	case 4:
	 // 123abc
		if (_gChord2_gRef[_gChord] <= 41){gOutput[0] = (char*)_gNUMS[_gChord2_gRef[_gChord]];
		} else {gOutput[0] =  (char*)_gChar[_gChord2_gRef[_gChord]];} // partly same as lower case
	break;

	case 8:
	// Symb
		_shifts = 0;
		gOutput[0] = (char*)_gSYMB[_gChord2_gRef[_gChord]];
	break;

	case 16:
	// Mouse
		gOutput[0] = (char*)_gMUSE[_gChord2_gRef[_gChord]];
	break;
	
	case 2:
	// Caps	
		if (_gChord2_gRef[_gChord] <= 41){gOutput[0] = (char*)_gCAPS[_gChord2_gRef[_gChord]];
		} else {gOutput[0] =  (char*)_gChar[_gChord2_gRef[_gChord]];} // partly same as lower case
	break;

	default:
	// abc
	gOutput[0] =  (char*)_gChar[_gChord2_gRef[_gChord]]; // default lower case abc

	} // end of switch

	_gRef = (int)_gChord2_gRef[_gChord]; // Set the GKOS Reference for each entry
	return gOutput[0];

  } else return "";

}

int Gkos::reference()
{ // Just the GKOS Reference number will be returned (also for Shift/Caps, Symb and 123abc)

	int i = 0;
	entry();
	i = _gRef;
	_gRef = 0;
	return i;
}

// Private Methods ////////////////////////////////////////////////////////////

bool Gkos::gScanKeys()
{
  // Return empty immediately if 10 ms not elapsed
  _time = millis();
 if ((_time - _previousTime) >= (10 + 64 * _autoRepeat)){ // Only read keypad state every 10 ms

  if (digitalRead(_key_pins[1]) == LOW){_key_down[1] = 1;} else {_key_down[1] = 0;}
  if (digitalRead(_key_pins[2]) == LOW){_key_down[2] = 1;} else {_key_down[2] = 0;}
  if (digitalRead(_key_pins[3]) == LOW){_key_down[3] = 1;} else {_key_down[3] = 0;}
  if (digitalRead(_key_pins[4]) == LOW){_key_down[4] = 1;} else {_key_down[4] = 0;}
  if (digitalRead(_key_pins[5]) == LOW){_key_down[5] = 1;} else {_key_down[5] = 0;}
  if (digitalRead(_key_pins[6]) == LOW){_key_down[6] = 1;} else {_key_down[6] = 0;}
  
  _presentChord = _key_down[1] + _key_down[2] * 2 + _key_down[3] * 4 + _key_down[4] * 8 + _key_down[5] * 16 + _key_down[6] * 32;

  if (_presentChord != 0)
  {
  	_autoCounter = _autoCounter + 1;
  	if (_autoCounter == 100){
    	   	_autoCounter = 99; _autoRepeat = 1;
        } // chord pressed long enough for autorepeat 

	_firstCounter = _firstCounter + 1;
	if (_firstCounter == 26){
       		_firstCounter = 25; if (_firstChord == 0){_firstChord = _presentChord;}
         } // chord pressed long enough to be first chord in Chordon 
  }

  if (_presentChord > _previousChord){
    _gNew = true; _autoCounter = 0; _autoRepeat = 0; _firstCounter = 0;
  } // new key(s) pressed, expect a new character soon

  if (_presentChord < _previousChord){ // key(s) relased
    _autoCounter = 0; _autoRepeat = 0; _firstCounter = 0;
    _gChord = _previousChord;  // the chord before the first release of key(s) is what we are after
    _previousChord = _presentChord;  
    _previousTime = _time;
      if (_gNew == true){
      _gNew = false; // next key releases will no more represent chords for characters
      return true; // a real chord entered!
      } else return false;  // chord already given
  }

  if (_presentChord == 0){_firstChord = 0; 
       _firstCounter = 0;
  } // all keys are up

  _previousChord = _presentChord; // to be able to compare next time
  _previousTime = _time;

     if (_autoRepeat == true){_gChord = _previousChord; _firstCounter = 0; _firstChord = 0;
         return true;} // Autorepeat anyway
         else {return false;
      } // no chord for character

 } else {return false;} // 10 ms not elapsed
  
}

