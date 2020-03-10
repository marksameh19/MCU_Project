#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "keypad.h"
//#include "BlueTooth.h"
#include "LCD.h"
#define red 0x02
#define blue 0x04
#define green 0x08


void SystemInit(){}

void Portf_init()
{
	uint32_t delay;
	SYSCTL_RCGCGPIO_R = 0x20;
	delay = 1;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_PUR_R = 0x11;
	
}
	
char getfrombluetooth(){char c='x';return c;}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 100 ms
  }
}





void open_the_lock(){
	volatile unsigned long delay;
	int i=0;
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	GPIO_PORTB_DIR_R |= 0x80;    
  GPIO_PORTB_AFSEL_R &= ~0x80; 
  GPIO_PORTB_DEN_R |= 0x80;    
              
                
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTB_AMSEL_R = 0; 
	GPIO_PORTB_DATA_R=0X80;
	
	
	
	
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	GPIO_PORTF_DIR_R |= 0x0E;    
  GPIO_PORTF_AFSEL_R &= ~0x0E; 
  GPIO_PORTF_DEN_R |= 0x0E;    
              
                
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;      

	 while(1){
		for (i=0;i<2;i++){
    GPIO_PORTF_DATA_R = 0x08;        // GREEN LED
    Delay100ms(10);           // delay ~1 sec at 80 MHz
    GPIO_PORTF_DATA_R = 0x00;    
    Delay100ms(10);        }
}
	 }

void close_the_lock(){
		volatile unsigned long delay;
	int i=0;
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	GPIO_PORTB_DIR_R |= 0x80;    
  GPIO_PORTB_AFSEL_R &= ~0x80; 
  GPIO_PORTB_DEN_R |= 0x80;    
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTB_AMSEL_R = 0; 
	GPIO_PORTB_DATA_R=0X00;
	
	
	
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	GPIO_PORTF_DIR_R |= 0x0E;    
  GPIO_PORTF_AFSEL_R &= ~0x0E; 
  GPIO_PORTF_DEN_R |= 0x0E;    
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0FFFF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;

	 while(1){
		for (i=0;i<2;i++){
    GPIO_PORTF_DATA_R = 0x02;        // RED LED
    Delay100ms(10);           // delay ~1 sec at 80 MHz
    GPIO_PORTF_DATA_R = 0x00;
    Delay100ms(10);        }
}
}
int iszero=1;
char pass[5]; //old password
char s[5];int count=0; //keypad string--password counter
int right=1; // flag used in comparing the two strings
char s_b[5];int count_b=0; //bluetooth string--password counter for bluetooth
char c,c_b;// c is for character from keypad--c_b is for character from bluetooth
int change=0;

void change_pass()
{
	if((GPIO_PORTB_DATA_R&0x80)==0x80){
	while(!change)
		{
		c=getfromkeybad();
		if(c!='x')
			{
				switch (c)
				{
					case('0'):if(count!=4){s[count]='0';count++;}break;
					case('1'):if(count!=4){s[count]='1';count++;}break;
					case('2'):if(count!=4){s[count]='2';count++;}break;
					case('3'):if(count!=4){s[count]='3';count++;}break;
					case('4'):if(count!=4){s[count]='4';count++;}break;
					case('5'):if(count!=4){s[count]='5';count++;}break;
					case('6'):if(count!=4){s[count]='6';count++;}break;
					case('7'):if(count!=4){s[count]='7';count++;}break;
					case('8'):if(count!=4){s[count]='8';count++;}break;
					case('9'):if(count!=4){s[count]='9';count++;}break;
					case('c'):while(count!=-1){s[count]=' ';count--;};break;
					case('h'):s[count]=' ';count--;break;
					case('m'):change=1;break;
					case('e'):
						if(count==4)
					{
						count=0;
						while(count!=4)
						{
							if(s[count]!='0')
								iszero=0;
							count++;
						}
					if(!iszero)
					{
						count=0;
					while(count!=4)
					{
						pass[count]=s[count];
						count++;
					}
					count=0;
					change=1;
					iszero=1;
				}
			}
						break;
			}
				while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();}
		}
	}
		change=0;
}
}


void enter_pass()
{
	while(1)
	{
		GPIO_PORTF_DATA_R = red;
	c = getfromkeybad();
	if(c!='x')
		{
			switch (c)
			{
				case('0'):if(count!=4){s[count]='0';count++;}break;
				case('1'):if(count!=4){s[count]='1';count++;}break;
				case('2'):if(count!=4){s[count]='2';count++;}break;
				case('3'):if(count!=4){s[count]='3';count++;}break;
				case('4'):if(count!=4){s[count]='4';count++;}break;
				case('5'):if(count!=4){s[count]='5';count++;}break;
				case('6'):if(count!=4){s[count]='6';count++;}break;
				case('7'):if(count!=4){s[count]='7';count++;}break;
				case('8'):if(count!=4){s[count]='8';count++;}break;
				case('9'):if(count!=4){s[count]='9';count++;}break;
				case('c'):while(count!=-1){s[count]=' ';count--;};break;
				case('h'):s[count]=' ';count--;break;
				case('e'):
					if(count==4)
					{
					count=0;
					while(count!=4)
					{
						if(pass[count]!=s[count])
							right=0;
						count++;
					}
					count=0;
					if(right)
					{open_the_lock();GPIO_PORTF_DATA_R = green;}
					while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();}
					{
						while(c!='m'&&c!='p')
						{
							c = getfromkeybad();
						}
						if(c=='p')close_the_lock();
						if(c=='m')change_pass();
					}
				}
					right=1;
					break;
			}
			while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();} //won't take any input until it gets x;  
		}
	}
}


int main()
{
	Portf_init();
	porTA_init();
	porTB_init();
	GPIO_PORTF_DATA_R = blue;
	count=0;
	while(1)
	{
		c = getfromkeybad();
		//c_b = getfrombluetooth();
		//***********************************keypad
		if(c!='x')
		{
			switch (c)
			{
				case('0'):if(count!=4){s[count]='0';count++;}break;
				case('1'):if(count!=4){s[count]='1';count++;}break;
				case('2'):if(count!=4){s[count]='2';count++;}break;
				case('3'):if(count!=4){s[count]='3';count++;}break;
				case('4'):if(count!=4){s[count]='4';count++;}break;
				case('5'):if(count!=4){s[count]='5';count++;}break;
				case('6'):if(count!=4){s[count]='6';count++;}break;
				case('7'):if(count!=4){s[count]='7';count++;}break;
				case('8'):if(count!=4){s[count]='8';count++;}break;
				case('9'):if(count!=4){s[count]='9';count++;}break;
				case('c'):while(count!=-1){s[count]=' ';count--;}count++;break; //clearing the string
				case('h'):if(count>0){s[count]=' ';count--;}break; //clearing the last bit
				case('e'):
					if(count == 4)
					{
						count=0;
					while(count!=4)
					{
						if(s[count]!='0')
							iszero=0;
						count++;
					}
					count=0;
					if(!iszero)
					{
					while(count!=4)
					{
						pass[count]=s[count];
						count++;
					}
					count=0;
					enter_pass();
				  }
					iszero=1;
				}
					count=0;
					break;
			}
			while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();} //won't take any input until it gets x;  
		}
		
		/*if(c_b!='x')
		{
			switch (c)
			{
				case('0'):if(count_b!=4){s_b[count_b]='0';count_b++;}break;
				case('1'):if(count_b!=4){s_b[count_b]='1';count_b++;}break;
				case('2'):if(count_b!=4){s_b[count_b]='2';count_b++;}break;
				case('3'):if(count_b!=4){s_b[count_b]='3';count_b++;}break;
				case('4'):if(count_b!=4){s_b[count_b]='4';count_b++;}break;
				case('5'):if(count_b!=4){s_b[count_b]='5';count_b++;}break;
				case('6'):if(count_b!=4){s_b[count_b]='6';count_b++;}break;
				case('7'):if(count_b!=4){s_b[count_b]='7';count_b++;}break;
				case('8'):if(count_b!=4){s_b[count_b]='8';count_b++;}break;
				case('9'):if(count_b!=4){s_b[count_b]='9';count_b++;}break;
				case('c'):while(count_b!=-1){s_b[count_b]=' ';count_b--;}count_b++;break; //clearing the string
				case('h'):if(count_b>0){s[count_b]=' ';count_b--;}break; //clearing the last bit
				case('e'):
					if(count_b == 4)
					count_b=0;
					while(count_b!=4)
					{
						pass[count_b]=s[count_b];
						count_b++;
					}
					count_b=0;
					enter_pass();
					break;
			}
			while(c!='x'||c_b!='x'){c = getfromkeybad();c_b = getfrombluetooth();} //won't take any input until it gets x;  
		}*/
	}
}

