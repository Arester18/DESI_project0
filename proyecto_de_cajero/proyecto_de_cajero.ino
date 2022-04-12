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
byte pinesFilas[FILAS] = {12,8,7,6};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {5,4,3,2}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
String cadena="";
float valor=0;
float monto=0;   


int TRIG = A1;
int ECO = A0;
int DURACION;
float DISTANCIA;

//Monedas
int num_10;
int num_50;
int num_100;
int DuracionEntreMonedas = 1000;
int recibe_10;
int recibe_50;
int recibe_100;



Servo servo1; //100
Servo servo2; //50
Servo servo3; //10

int PINSERVO_1 = 9;
int PINSERVO_2 = 10;
int PINSERVO_3 = 11;
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
  
  servo1.attach(PINSERVO_1, PULSOMIN, PULSOMAX);
  servo2.attach(PINSERVO_2, PULSOMIN, PULSOMAX);
  servo3.attach(PINSERVO_3, PULSOMIN, PULSOMAX);
}

void loop() {

  //ENTRAN LAS MONEDAS
  digitalWrite(TRIG, HIGH); 
  delay(1);  
  digitalWrite(TRIG, LOW);  
  
  DURACION = pulseIn(ECO, HIGH);
  
  DISTANCIA = DURACION / 58.2;
  if(DISTANCIA<380){
    if(0<DISTANCIA && DISTANCIA<100){
      num_100++;
      delay(DuracionEntreMonedas);
    }else if(100<=DISTANCIA && DISTANCIA<200){
      num_50++;
      delay(DuracionEntreMonedas);
    }else if(200<=DISTANCIA && DISTANCIA<=300){
      num_10++;
      delay(DuracionEntreMonedas);
    }else{
      lcd.setCursor(0,1);
      while(TECLA=teclado.getKey()){
        if (TECLA!='D'){
          cadena+=TECLA;
          Serial.println(TECLA);
        }
        lcd.print(cadena);
        if(TECLA=='A'){
          lcd.clear();
          cadena="";
          Serial.println("LLEGO HASTA A");
          break;
        }
        if (TECLA=='D'){
          //funcion para calcular el numero de monedas
          Serial.print("Se ha presionado D");
          func_monedas(cadena);
          delay(50);
          cadena = "";
          Serial.println("Imprime un sol");
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
          Serial.println("Imprime cincuenta");
          Serial.println(recibe_50);
          for (int i = 0; i < recibe_50; i++)
          {
            if(b==180){
              servo2.write(0);
              delay(2000);
              b=0;
            }else{
              servo2.write(180);
              delay(2000);
              b=180;
            }
          }
          Serial.println("Imprime diecentimom");
          Serial.println(recibe_10);
          for (int i = 0; i < recibe_10; i++)
          {
            if(c==180){
              servo3.write(0);
              delay(2000);
              c=0;
            }else{
              servo3.write(180);
              delay(2000);
              c=180;
            }
          }
        }
      }
    }
  }
  lcd.setCursor(0,0);
  monto=monto_Pantalla(num_100,num_50,num_10);
  lcd.print(monto);
}
float monto_Pantalla(int unsol,int cincuenta,int diez){
  float monto=unsol*1.0+(cincuenta*1.0)/2.0+(diez*1.0)/10.0;
  return monto;
}
void func_monedas(String cadena){
  float intCadena = cadena.toFloat();
  int parteEntera = cadena.toInt();
  //parte decimal ->partD
  float partD = intCadena - parteEntera;
  recibe_100 = parteEntera;
  if (partD>0 && partD<1){
    if(partD>0.5){
      recibe_50 = 1;
      if(partD>=0.9){
        recibe_10 = 4;
      }else if (partD>=0.8){
        recibe_10 = 3;
      }else if (partD>=0.7){
        recibe_10 = 2;
      }else if (partD>=0.6){
        recibe_10 = 1;
      }
    } 
  else{
      recibe_10 = partD * 10; 
  }
  }else{
    Serial.println("Parte decimal fuera de rango");
  }
}

