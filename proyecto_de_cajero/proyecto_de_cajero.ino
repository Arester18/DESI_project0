#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define buzzer 8

LiquidCrystal_I2C lcd(0x27,16,2);

const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','.','D'}
};
byte pinesFilas[FILAS] = {9,8,7,6};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
String cadena="";
float valor=0;
float monto=0;   


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("Hola");
  lcd.print("Hola");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(TECLA=teclado.getKey()){
    cadena+=TECLA;
    Serial.println(TECLA);
    lcd.print(TECLA);
    if(TECLA=='A'){
      lcd.clear();
      cadena="";
      Serial.println("LLEGO HASTA A");
      break;
    }
  }
  lcd.setCursor(0,0);
  lcd.print(cadena);
  
}
