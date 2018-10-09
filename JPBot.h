#include <Arduino.h>

bool INVERTER_M1 = false;
bool INVERTER_M2 = false;
bool debug_flag = false;
volatile int contador_m1 = 0;
volatile int contador_m2 = 0;

volatile int pin_est_m1 = 0 ;
volatile int pin_est_m2 = 0 ;

bool motor_1 = true;
bool motor_2 = true;

int potencia_motor_1 = 255;
int potencia_motor_2 = 255;

int pin_encoder_direita = 0;
int pin_encoder_esquerda = 0;
int pin_motor_1_a = 0;
int pin_motor_1_b = 0;
int pin_motor_2_a = 0;
int pin_motor_2_b = 0;
int pin_led=0;


void reload()
{
  contador_m1 = 0;
  contador_m2 = 0;
  pin_est_m1 = 0;
  pin_est_m2 = 0;
  motor_1 = true;
  motor_2 = true;
}

void esperar_motores(int passos)
{
	reload();
	if(debug_flag)
	{
		Serial.print("Passos: ");
		Serial.println(passos);
		Serial.print("Contador m2 ");
		Serial.println(contador_m1);
	}
	while(motor_1 || motor_2)
	{
		if(contador_m1>= passos*2)
		{
		  motor_1=false;
		  analogWrite(pin_motor_1_a,0);
		  analogWrite(pin_motor_1_b,0);
		}
		
		if(contador_m2>= passos*2)
		{
		  motor_2=false;
		  analogWrite(pin_motor_2_a,0);
		  analogWrite(pin_motor_2_b,0);
		}
	}
}

void contar_m2()
{
  if(digitalRead(pin_encoder_esquerda)==pin_est_m2)
  {
   pin_est_m2= !pin_est_m2;
   contador_m2 ++;
  }
}

void contar_m1()
{
  if(digitalRead(pin_encoder_direita)==pin_est_m1)
  {
   pin_est_m1 = !pin_est_m1;
   contador_m1 ++;
  }
}

void preparar(int encoder_direita,int encoder_esquerda,
	      int motor_1_a,int motor_1_b,
	      int motor_2_a,int motor_2_b,
              int led)
{
	pin_encoder_direita = encoder_direita;
	pin_encoder_esquerda = encoder_esquerda;
	pin_motor_1_a = motor_1_a; 
	pin_motor_1_b = motor_1_b;
	pin_motor_2_a = motor_2_a;
	pin_motor_2_b = motor_2_b;
    pin_led = led;
	pinMode(pin_encoder_direita, INPUT);
	pinMode(pin_encoder_esquerda, INPUT);
	pinMode(pin_motor_1_a, OUTPUT);
	pinMode(pin_motor_1_b, OUTPUT);
	pinMode(pin_motor_2_a, OUTPUT);
	pinMode(pin_motor_2_b, OUTPUT);
    pinMode(pin_led, OUTPUT);
    Serial.begin(9600);
}

void frente()
{
  analogWrite(pin_motor_1_a,INVERTER_M1?0:potencia_motor_1);
  analogWrite(pin_motor_1_b,INVERTER_M1?potencia_motor_1:0);
  analogWrite(pin_motor_2_b,INVERTER_M2?0:potencia_motor_2);
  analogWrite(pin_motor_2_a,INVERTER_M2?potencia_motor_2:0);
}

void direita()
{
  analogWrite(pin_motor_1_a,INVERTER_M1?0:potencia_motor_1);
  analogWrite(pin_motor_1_b,INVERTER_M1?potencia_motor_1:0);        
  analogWrite(pin_motor_2_a,INVERTER_M2?0:potencia_motor_2);
  analogWrite(pin_motor_2_b,INVERTER_M2?potencia_motor_2:0);
	
}

void esquerda()
{
  analogWrite(pin_motor_1_b,INVERTER_M1?0:potencia_motor_1);
  analogWrite(pin_motor_1_a,INVERTER_M1?potencia_motor_1:0);
  analogWrite(pin_motor_2_b,INVERTER_M2?0:potencia_motor_2);
  analogWrite(pin_motor_2_a,INVERTER_M2?potencia_motor_2:0);
}

void re()
{
  analogWrite(pin_motor_1_b,INVERTER_M1?0:potencia_motor_1);
  analogWrite(pin_motor_1_a,INVERTER_M1?potencia_motor_1:0);
  analogWrite(pin_motor_2_a,INVERTER_M2?0:potencia_motor_2);
  analogWrite(pin_motor_2_b,INVERTER_M2?potencia_motor_2:0);
}


void direita_aberta()
{
  analogWrite(pin_motor_1_a,INVERTER_M1?0:potencia_motor_1);
  analogWrite(pin_motor_1_b,INVERTER_M1?potencia_motor_1:0);
  analogWrite(pin_motor_2_b,0);
  analogWrite(pin_motor_2_a,0);
}

void esquerda_aberta()
{
  analogWrite(pin_motor_1_b,0);
  analogWrite(pin_motor_1_a,0);
  analogWrite(pin_motor_2_b,INVERTER_M2?0:potencia_motor_2);
  analogWrite(pin_motor_2_a,INVERTER_M2?potencia_motor_2:0);
}

void parar()
{
  analogWrite(pin_motor_1_b,0);
  analogWrite(pin_motor_1_a,0);
  analogWrite(pin_motor_2_a,0);
  analogWrite(pin_motor_2_b,0);
}

void frente(int passos)
{
  
	frente();
	esperar_motores(passos);
 	
}

void re(int passos)
{
	re();
	esperar_motores(passos);
}

void direita(int passos)
{
	direita();
	esperar_motores(passos);
}

void direita_aberta(int passos)
{
	direita_aberta();
	esperar_motores(passos);
}
void esquerda(int passos)
{
	esquerda();
	esperar_motores(passos);
}

void esquerda_aberta(int passos)
{
	esquerda_aberta();
	esperar_motores(passos);
}

void piscar_led(int tempo)
{
  analogWrite(pin_led,200);
  delay(tempo);
  analogWrite(pin_led,0);
  delay(tempo);
}

void debug_dir_motores()
{
  frente();
  delay(2000);
  parar();
  piscar_led(500);
 
  re();
  delay(2000);
  parar();
  piscar_led(500);
  
  direita_aberta();
  delay(2000);
  parar();
  piscar_led(500);
  
  esquerda_aberta();
  delay(2000);
  parar();
  piscar_led(500);
}


