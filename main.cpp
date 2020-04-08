#include "mbed.h"
Serial pc( USBTX, USBRX );
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
AnalogOut Aout(DAC0_OUT);// analog out put to generate Sinwave
AnalogIn Ain(A0);
char table[21] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF,0x00};

int sample = 500;
int i;
float ADCdata[500];
int flag = 0;//when maximum happened
int hundred;//print the frenquency
int ten;
int ten_unit;
int unit;
float adc;
int main()
{
    for (i = 0; i < sample; i++){
        adc =Ain;
        pc.printf("%1.3f\r\n", adc);
            wait(1./sample);
		}

    for (i = 0; i < sample; i++){
		ADCdata[i] = Ain;
       
        //pc.printf("%1.3f\r\n", ADCdata[i]);
		wait(1./sample);
		}

        flag=0;
		for (i = 0; i < sample; i++){
			if((ADCdata[i]<ADCdata[i-1])&&(ADCdata[i]<ADCdata[i+1])){
				flag =flag+1;//when maximum happened
			}
            
            wait(1./sample);
		}
    //pc.printf("%d\r\n", flag); 

    while(1){
		
        //output another sine wave to AnalogOut Pin with the f
        
 


		//flag is the frequency of the sinwave
		hundred = flag/100;
		ten_unit= flag%100;
		ten 	= ten_unit/10;
		unit	= ten_unit%10;

		if( Switch == 0 ){
			greenLED = 1;
			redLED = 0;

             
			switch(hundred){
				
                case 0: display = table[0];wait(1);break;
                case 1: display = table[1];wait(1);break;
                case 2: display = table[2];wait(1);break; 
                case 3: display = table[3];wait(1);break; 
                case 4: display = table[4];wait(1);break; 
                case 5: display = table[5];wait(1);break; 
                case 6: display = table[6];wait(1);break; 
                case 7: display = table[7];wait(1);break; 
                case 8: display = table[8];wait(1);break; 
                case 9: display = table[9];wait(1);break;  
                
            }
            
			switch(ten){
				case 0: display = table[0];wait(1);break;
                case 1: display = table[1];wait(1);break;
                case 2: display = table[2];wait(1);break; 
                case 3: display = table[3];wait(1);break; 
                case 4: display = table[4];wait(1);break; 
                case 5: display = table[5];wait(1);break; 
                case 6: display = table[6];wait(1);break; 
                case 7: display = table[7];wait(1);break; 
                case 8: display = table[8];wait(1);break; 
                case 9: display = table[9];wait(1);break;  
			}
            
            
			switch(unit){
				case 0: display = table[10];wait(1);break;
                case 1: display = table[11];wait(1);break;
                case 2: display = table[12];wait(1);break; 
                case 3: display = table[13];wait(1);break; 
                case 4: display = table[14];wait(1);break; 
                case 5: display = table[15];wait(1);break; 
                case 6: display = table[16];wait(1);break; 
                case 7: display = table[17];wait(1);break; 
                case 8: display = table[18];wait(1);break; 
                case 9: display = table[19];wait(1);break;  
			}
            
		}
		else{
		  redLED = 1;
		  greenLED = 0;
		  display = 0x00;// turn off all LED;


            float tmp  =((1/flag)/40);
            for (float i = 0; i <2; i=i+0.05){
                Aout = 0.5+0.5*sin(i*3.14159);
                //Aout = Aout;
                wait(1./flag/40);
            }

		}

           /*
        for (i = 0; i < sample; i++){
            //Aout =ADCdata[i];
            Aout =Ain;
            wait(1./sample);
		}
        */
	}
}