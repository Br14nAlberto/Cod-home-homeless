#include <PF.h>
#fuses XT, NOWDT,PUT, NOLVP, NOPROTECT
#use delay (clock=4000000)
#define use_portb_lcd TRUE
#use standard_io(d)
#include <lcd.c>
#device adc=0


//esta parte hace que cuando la luz natural baje se enciedad la luz
void main()
{
 Set_tris_c(0);                //puerto c como salida

 int16 valor_digital;
 float valor_analogico;
 int luminosidad;
 
 setup_adc_ports(0);         //canal de entrada analogico ANO
 setup_adc(ADC_CLOCK_INTERNAL);//fuente de reloj RC
 
 for (;;)
 {
 set_adc_channel(0);          //habilitacion del canla de la lectura 0
 delay_us(20);                //estabilizacion
 valor_digital=read_adc();    //lectura digital del canal analogico
 valor_analogico=5.0*valor_digital/1024.0; //equivalencia del valor analogico
 
 luminosidad=(100*valor_analogico)/5; //%de luminocidad en LRD
 
 //muentrs de porcentaje e LCD
 if(luminosidad < 41){
  output_high(pin_C0);
   }else{
     output_low(pin_C0);
 }
 
 delay_ms(100);               //retardo hasta la siguiente lectura
 }
}

//esta parte hace que el sensor de humedad funcione
float valor;                        //Declaramos una variable de tipo float llamada "valor"                   
float humedad;                      //Declaramos una variable de tipo float llamada "humedad"
 
 
 void configuracion (void)
{
   set_tris_a(0b00000001);          //Configuramos el pin RA0 de puerto A como entrada
   setup_adc_ports(all_analog);     //Configuramos los pines de puerto A como entradas anal�gicas     
   setup_adc(adc_clock_internal);   //Activamos el reloj interno ADC
   delay_ms(50);                    //Retardo de 50 milisegundos
}
 void main (void)
{
   configuracion();                 //Llamamos a la funci�n de configuraci�n
   while(true)
   {
      set_adc_channel(0);           //Establecemos el canal 0 PIN RA0 como canal Anal�gico
      delay_ms(1);                  //Retardo de 1 milisegundo
      valor=read_adc();             //Guardamos el valor anal�gico digitalizado en la variable "valor"
      humedad=(-0.17*valor)+171.4;  //Usamos esta f�rmula para calcular el porcentaje de humedad
      delay_ms(300);                //Retardo de 300 milisegundos 
   }
}


//esta parte hacer que el sensor de temperatura gire el motor 
float temperatura;

void main()
{

setup_adc_ports(RA0_ANALOG);//entrada del ML35
setup_adc(ADC_CLOCK_INTERNAL);
setup_COUNTERS(RTCC_internal.rtcc_div_1);//marca de divicion
set_adc_channel(0);
//********************************************************

lcd_init();
lcd_gotoxy(5,1);
printf(lcd_putc,"Temperatura");
delay_ms(350);
lcd_init();


while(true)
{
temperatura=(float)read_adc()/2;
//************temperatura en grados centrigrados
lcd_gotoxy(5,1);
print(lcd_putc,"%f",temperatura);
lcd_gotoxy(14,1);
printf(lcd_putc,"Grados");
delay_ms(200);


//********** si la temperatura es mayor que 35
if(temperatura<=500&&temperatura>=35)
   {
   output_high(pin_a1);
   output_high(pin_a2);
   output_low(pin_a3);
   
   
   lcd_gotoxy(5,2);
   printf(lcd_putc,"Disipando Calor");
   delay_ms(200);
   }
//************si la temperatura es correcta o menor que 15   
else{
   output_low(pin_a1);
   output_low(pin_a2);
   output_high(pin_a3);
   
   
   lcd_gotoxy(5,2);
   printf(lcd_putc,"Correcta funcion");
   delay_ms(200);
}
}
} 

