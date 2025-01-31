#inlude <16f887.h>
#device adc= 10
#fuses XT, NOWDT
#uses delay(clock=4000000)
#define use_portb_lcd TRUE
#include <lcd.c>

//esta parte hace que cuando la luz natural baje se enciedad la luz
void main()
{
 Set_tris_c(0);                //puerto c como salida

 int16 valor_digital;
 float valor_analogico;
 int luminosidad;
 
 setup_adc_ports(AN2);           //canal de entrada analogico ANO
 setup_adc(ADC_CLOCK_INTERNAL);  //fuente de reloj RC
 
 //lcd_init();                     //inicializa el lcd
 //lcd_putc('\f');                 //limpia la pantalla
 
 for (;;)
 {
 set_adc_channel(0);          //habilitacion del canla de la lectura 0
 delay_us(20);                //estabilizacion
 valor_digital=read_adc();    //lectura digital del canal analogico
 valor_analogico=5.0*valor_digital/1024.0; //equivalencia del valor analogico
 
 luminosidad=(100*valor_analogico)/5; //%de luminocidad en LRD
 
 //muentrs de porcentaje e LCD
 //lcd_gotoxy(1,1);
 //printf(lcd_putc, "Luz de lab");
 //lcd_gotoxy(1,2);
 //printf(lcd_putc,"Lumenz %3.0d%%",luminocidad);
 
 
 if(luminosidad < 41){
  output_high(pin_C1);
   }else{
     output_low(pin_C1);
 }
 
 delay_ms(100);               //retardo hasta la siguiente lectura
 }
}
