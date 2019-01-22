#include<P18F4550.h>

unsigned int No_of_bits,data_rcd,i;

unsigned char key,UserId1[10],Temp[10],Temp1[10];
unsigned char product[5]={'0','0','0','0','0'};
unsigned char TAGID[5];
unsigned long TagId,code;

unsigned int m,tag,pay,pay1;

void myMsDelay (unsigned int time);
unsigned int delete();
unsigned int add();

#define LCD_DATA LATD
#define rspin LATEbits.LATE1 //Define LEDPin as PORT D Pin 1
#define enpin LATEbits.LATE2 //Define LEDPin as PORT D Pin 1

#define d0pin PORTAbits.RA4 //Define LEDPin as PORT D Pin 1
#define d1pin PORTAbits.RA5  //Define LEDPin as PORT D Pin 1

#define R1 PORTBbits.RB0 
#define R2 PORTBbits.RB1 
#define R3 PORTBbits.RB2 
#define R4 PORTBbits.RB3 

#define C1 PORTBbits.RB4 
#define C2 PORTBbits.RB5 
#define C3 PORTBbits.RB6 
#define C4 PORTBbits.RB7 

char var1[] = "WELCOME"; 
char var2[] = "Maggi Rs.10"; 
char var3[] = "Dairy Milk Rs.20 "; 
char var4[] = "Kurkure Rs.20  "; 
char var5[] = "Pepsi Rs.10    "; 
char var6[] = "Plz Enter Amt:     "; 
char var8[] = "Tag ID:"; 
char var11[] = "Data Send To PC     "; 
char var12[] = "  Shopping Complete     "; 

void TransByte(unsigned char val)
{
   while(PIR1bits.TXIF==0);
   TXREG=val;
}

void delay(unsigned int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
 for(j=0;j<274;j++);
}
void LCD_cmd(unsigned char cmd)
{
 	 LCD_DATA = cmd;
   	 rspin = 0;   	
   	 enpin = 1;
   	 myMsDelay(5);
   	 enpin = 0;
     	myMsDelay(5);
   	 return;
}
void init_LCD(void)
{
	    LCD_cmd(0x38);      // initialization of 16X2 LCD in 8bit mode
    	    myMsDelay(5);

	    LCD_cmd(0x01);      // clear LCD
 	    myMsDelay(5);

  	    LCD_cmd(0x0C);      // display on cursor off
   	    myMsDelay(5);

   	    LCD_cmd(0x80);      // ---8 go to first line and --0 is for 0th position
   	    myMsDelay(5);
   	 
        return;
}
void LCD_write(unsigned char data)
{
  	  LCD_DATA = data;
  	  rspin = 1;  	 
  	  enpin = 1;
   	  myMsDelay(5);
   	  enpin = 0;
  	  myMsDelay(5);
  	  return ;
}
void clear(void)
{
       LCD_cmd(0x01);      // clear LCD
      myMsDelay(5);
}
void LCD_write_string(static char *str)   //store address value of the string in 
{
    int i = 0;
    while (str[i] != 0)
   	 {
     	   LCD_write(str[i]);      // sending data on LCD byte by byte
      	   myMsDelay(5);
        	        i++;
    	}
  	 return;
}
	
void display_string_LCD(static char *pstring1)
{
    	 LCD_write_string(pstring1);
    	 myMsDelay(1);

 	    return;
}


unsigned int add(unsigned char id)
{
switch (id) 
 {      
        case'1': pay=pay+0x0a; break;
        case '2':pay=pay+0x14; break;
        case '3':pay=pay+0x14; break;
        case '4':pay=pay+0x0a; break;
        default:  break;         
 }
}

unsigned int delete(unsigned char id)
{
switch (id) 
 {      
        case'1': pay=pay-0x0a; break;
        case '2':pay=pay-0x14; break;
        case '3':pay=pay-0x14; break;
        case '4':pay=pay-0x0a; break;
        default: break;         
 }
}

unsigned int totalproduct(unsigned char id)
{
switch (id) 
 {      
        case '1':product[0]='1'; break;
        case '2':product[1]='2'; break;
        case '3':product[2]='3'; break;
        case '4':product[3]='4'; break;
        default: break;         
 }
}

unsigned int totalproductd(unsigned char id)
{
switch (id) 
 {      
        case '1':product[0]='0'; break;
        case '2':product[1]='0'; break;
        case '3':product[2]='0'; break;
        case '4':product[3]='0'; break;
        default: break;         
 }
}

void H2B5(unsigned long num,unsigned char loc)
{
	unsigned char i ;   
	for(i = 5 ;i > 0 ; i--)
	{		 
	TAGID[i-1] = ((num % 10) + '0') ;			
	num /= 10 	;		
                }
         LCD_cmd(loc);
         LCD_write(TAGID[0]);
         LCD_write(TAGID[1]);
         LCD_write(TAGID[2]);
         LCD_write(TAGID[3]);
         LCD_write(TAGID[4]);         	
}

unsigned char Get_Key(void)
{
while(1)
{
       PORTB=0xFE;
      delay(50);
      if(C1 == 0)
      {
	    key='1';return key;      
      }
      if(C2 == 0)
      {
         key='2';return key;    
      }
     if(C3 == 0)
      {
	    key='3';return key;    
      }
	if(C4 == 0)
      {
	    key='A';return key;    
      }
PORTB=0xFD;
 delay(50);
      if(C1 == 0)
      {
	    key='4';return key;   
      }
      if(C2 == 0)
      {
         key='5';return key; 
      }
     if(C3 == 0)
      {
	    key='6';return key;   
      }
	if(C4 == 0)
      {
	    key='B';return key;  
      }
      PORTB=0xFB;
     delay(50);
      if(C1 == 0)
      {
	    key='7';return key;   
      }
      if(C2 == 0)
      {
         key='8';return key;  
      }
     if(C3 == 0)
      {
	    key='9';return key;  
      }
	if(C4 == 0)
      {
	    key='C';return key;   
      }
 PORTB=0xF7;
 delay(50);
      if(C1 == 0)
      {
	    key='*';return key;  
      }
      if(C2 == 0)
      {
         key='0';return key;    
      }
     if(C3 == 0)
      {
	    key='#';return key;     
      }
	if(C4 == 0)
      {
	    key='D';return key;   
      }	
  }
  return 0;   	 
}
void H2B(unsigned long num,unsigned char loc)
{
	unsigned char i ;
                 unsigned char Temp[4];
	for(i = 4 ;i > 0 ; i--)
	{		 
	Temp[i-1] = ((num % 10) + '0') ;			
	num /= 10 ;         	
   }
         LCD_cmd(loc);
         LCD_write('T');
         LCD_write('B');
         LCD_write(':');
         LCD_write(Temp[0]);
         LCD_write(Temp[1]);
         LCD_write(Temp[2]);
         LCD_write(Temp[3]);
         Temp1[0]=Temp[0];
         Temp1[1]=Temp[1];Temp1[2]=Temp[2];Temp1[3]=Temp[3];	
}
void main(void)
{     
     
        ADCON1 = 0x0F;        //Configuring the PORTE pins as digital I/O 
        TRISA = 0xf0;  
        TRISD = 0x00;         //Configuring PORTD as output
        TRISE = 0x00;         //Configuring PORTE as output
        TRISB = 0xf0;  
        init_LCD();           // initialization of LCD
       myMsDelay(10);       // delay of 50 mili seconds 	
       INTCON2bits.RBPU=0;
        LATAbits.LATA0 = 0;
        display_string_LCD(var1);
      
        TXSTA = 0x20;
        RCSTA= 0X90;
        SPBRG = 19;         //12 MHz crystal osc BD=9600
        TRISCbits.TRISC7 = 1;
        TRISCbits.TRISC6 = 0;
        INTCONbits.PEIE = 1;
        INTCONbits.GIE = 1;         //Global interrupt enable  
         No_of_bits = 0;
         TagId = 0;  
         data_rcd=0;
          tag==0;    
          clear();
          display_string_LCD(var6);
           LCD_cmd(0x8f);
		for(m=0;m<4;m++)
	                {
	    	UserId1[m]=Get_Key();
	                myMsDelay(200);                       
	 	LCD_write(UserId1[m]);
	     	myMsDelay(200);    
	                }  
  pay1=(((UserId1[0] - '0') * (1000)) +((UserId1[1] - '0')*100)+((UserId1[2]- '0')*10)+((UserId1[3] - '0'))); 
  pay=0x00;
tag=0;
while(1)
{
if(tag==0)
{ 
   while(data_rcd == 0)
   {
    if(d0pin == 0)
     {
      while(d0pin== 0);
      No_of_bits++;
      TagId <<= 1;			
      if(No_of_bits >= 26)
      {
	data_rcd= 1;
       }
   }
    if(d1pin == 0)
     {
      while(d1pin == 0);
      No_of_bits++;
      TagId <<= 1; 
      TagId |= 1;		
      if(No_of_bits >= 26)
      {
	data_rcd = 1;	
       }
     } 
  } 
 if(data_rcd == 1)
	   {
	        LCD_cmd(0x01);
	        code = TagId;
	        TagId = 0;
	         code >>= 1;
	         code &= 0x0000ffff;
	         display_string_LCD(var8);
                         H2B5(code,0xc0);       
                         TagId = 0;
                         No_of_bits = 0;
                         data_rcd=0;tag=1;      
                         myMsDelay(300); 
 switch (TAGID[4]) 
 {      
        case'1':LCD_cmd(0x80); display_string_LCD(var2);
        break;
        case '2':LCD_cmd(0x80); display_string_LCD(var3);
        break;
        case '3':LCD_cmd(0x80); display_string_LCD(var4);
        break;
        case '4':LCD_cmd(0x80); display_string_LCD(var5);  
        default:  break;        
 }
 myMsDelay(500);
  PORTB=0xFE;
 delay(50);
  if(C1 == 0)
      {
tag=1;
TransByte(0x0a);
TransByte(0x0a);
TransByte('T');TransByte('N');TransByte(':');
TransByte('1');
TransByte(0x0d);
TransByte(0x0a);
 for(i=0;i<5;i++)
        {                   
                     TransByte(product[i]);
                     TransByte(0x0d);
	     TransByte(0x0a);myMsDelay(5);
            }   
myMsDelay(100);
TransByte('T');
TransByte('B');
TransByte(':');
TransByte(Temp1[0]);
TransByte(Temp1[1]);
TransByte(Temp1[2]);
TransByte(Temp1[3]);
LATAbits.LATA0 = 1;	
myMsDelay(500);  
 LATAbits.LATA0 = 0;
pay=0x00;	
for(i=0;i<5;i++)
{               
                     product[i]='0';                   
 }   
       clear();
       display_string_LCD(var11);myMsDelay(500);display_string_LCD(var12);
 }  
 else if(C2 == 0)
      {       
         delete(TAGID[4]);
         H2B(pay,0xcc); 
         myMsDelay(500); 
         tag=0;
         totalproductd(TAGID[4]);
      }
	 else
	 {     
		  add(TAGID[4]);
		  tag=0;
                                 H2B(pay,0xcc);
 		myMsDelay(500); 
         		 totalproduct(TAGID[4]);
     }                          
   if(pay>=pay1)
   {
     LATAbits.LATA0 = 1;	myMsDelay(500);  
     LCD_cmd(0x01);
     LCD_cmd(0x80);
     LCD_write('E'); LCD_write('X'); LCD_write('C'); LCD_write('E'); LCD_write('E');LCD_write('D');LCD_write('S');
     LCD_write(' '); LCD_write(' '); LCD_write(' '); LCD_write(' '); LCD_write(' ');LCD_write(' ');LCD_write(' ');
     myMsDelay(200);     
     LATAbits.LATA0 = 0;                 
    }   
}
}
}
}
void myMsDelay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<710;j++);       //Calibrated for 1 ms delay in mplab..
}



