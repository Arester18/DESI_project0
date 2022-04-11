#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


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


int TRIG = 10;
int ECO = 9;
int DURACION;
int DISTANCIA;

//Monedas
int num_10;
int num_50;
int num_100;
int monto;
int DuracionEntreMonedas = 1000;
int recibe_10;
int recibe_50;
int recibe_100;



Servo servo1; //100
Servo servo2; //50
Servo servo3; //10

int PINSERVO = 2;
int PULSOMIN = 1000;
int PULSOMAX = 2000;

int a = 180;
int b = 180;
int c = 180;

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

  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
  
  servo1.attach(PINSERVO, PULSOMIN, PULSOMAX);
  servo2.attach(PINSERVO, PULSOMIN, PULSOMAX);
  servo3.attach(PINSERVO, PULSOMIN, PULSOMAX);
}

void loop() {

  //ENTRAN LAS MONEDAS
  digitalWrite(TRIG, HIGH); 
  delay(1);	
  digitalWrite(TRIG, LOW);	
  
  DURACION = pulseIn(ECO, HIGH);
  
  DISTANCIA = DURACION / 58.2;
  Serial.println(DISTANCIA);
  if(0<DISTANCIA && DISTANCIA<60){
    num_100++;
    delay(DuracionEntreMonedas);
  }else if(60<DISTANCIA && DISTANCIA<120){
    num_50++;
    delay(DuracionEntreMonedas);
  }else if(120<DISTANCIA && DISTANCIA<180){
    num_10++;
    delay(DuracionEntreMonedas);
  }
  delay(200);


  //Cobra
  // put your main code here, to run repeatedly:
  while(true){
    TECLA=teclado.getKey();
    if (TECLA!=""){
      cadena+=TECLA;
      Serial.println(TECLA);
      lcd.print(TECLA);
      if(TECLA=='A'){
        lcd.clear();
        delay(100);
        cadena="";
        Serial.println("LLEGO HASTA A");
        break;
      }
      TECLA="";
    };
    if (TECLA==D){
      //funcion para calcular el numero de monedas
      func_monedas(cadena);
      delay(50);
      cadena = "";
      Serial.println(recibe_100);
      for (int i = 0; i < recibe_100; i++)
      {
        if(a==180){
          servo1.write(0);
          delay(2000);
          a=0;
        }else{
          servo1.write(180);
          delay(2000);
          a=180;
        }
      }
      Serial.println(recibe_50);
      for (int i = 0; i < recibe_50; i++)
      {
        if(b==180){
          servo1.write(0);
          delay(2000);
          b=0;
        }else{
          servo1.write(180);
          delay(2000);
          b=180;
        }
      }
      Serial.println(recibe_10);
      for (int i = 0; i < recibe_10; i++)
      {
        if(c==180){
          servo2.write(0);
          delay(2000);
          c=0;
        }else{
          servo2.write(180);
          delay(2000);
          c=180;
        }
      }
    }
  }
  lcd.setCursor(0,0);
  lcd.print(cadena);
};

void func_monedas(String cadena){
  int intCadena = toInt(cadena);
  int parteEntera = cadena;
  //parte decimal ->partD
  float partD = cadena - parteEntera;
  recibe_100 = intCadena;
  if (partD<100){
    if(partD>50){
      recibe_50 = 1;
      
    } else{
      recibe_10 = partD / 10; 
    }
  }else{
    Serial.println("Parte decimal fuera de rango");
  }
}


