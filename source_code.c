#include <avr/io.h> 
#include <util/delay.h>

//define for LCD
#define LCD_DPRT PORTC
#define LCD_DDDR DDRC
#define LCD_DPIN PINC
#define LCD_CPRT PORTD
#define LCD_CDDR DDRD
#define LCD_CPIN PIND
#define LCD_RS PD0
#define LCD_RW PD1
#define LCD_EN PD2

//define for Keypad
#define KEY_PRT 	PORTB
#define KEY_DDR		DDRB
#define KEY_PIN		PINB
unsigned char colloc, rowloc;
char data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int i=0,j;

//general code
void delay_us(int a)
{
   _delay_us(a);
}
void delay_ms(int a)
{
   _delay_ms(a);
}


//Code for LCD
void lcdCommand(unsigned char cmnd) 
{
   LCD_DPRT = cmnd;
   LCD_CPRT &= ~ (1<<LCD_RS);
   LCD_CPRT &= ~ (1<<LCD_RW);
   LCD_CPRT |= (1<<LCD_EN);;
   delay_us(1);
   LCD_CPRT &= ~ (1<<LCD_EN);;
   delay_us(100);
}

void lcdData(unsigned char data)
{
   LCD_DPRT = data;
   LCD_CPRT |= (1<<LCD_RS);
   LCD_CPRT &= ~ (1<<LCD_RW);
   LCD_CPRT |= (1<<LCD_EN);
   delay_us(1);
   LCD_CPRT &= ~ (1<<LCD_EN);
   delay_us(100);
}
void lcd_gotoxy(unsigned char x,unsigned char y)
{
   unsigned char firstCharAdr[]={0x80, 0xC0, 0x94, 0xD4};
   lcdCommand(firstCharAdr[ y-1] + x-1);
   delay_us(100);
}
void lcd_print(char *str)
{
   unsigned char i =0;
   while(str[i]!=0)
   {
      lcdData(str[i]);
      i++;
   }
}
void lcd_init()
{
   LCD_DDDR = 0xFF;
   LCD_CDDR = 0xFF;
   
   LCD_CPRT &= ~(1<<LCD_EN);
   delay_ms(2000);
   lcdCommand(0x38);
   lcdCommand(0x0E);
   lcdCommand(0x01);
   delay_us(2000);
   lcdCommand(0x06);
   lcd_gotoxy(1,1);
   lcd_print("Text here: ");
   lcd_gotoxy(1,2);
}

//codeforkeypad				
unsigned char colloc, rowloc;

void l()
{
   int a,b,c = 0;
  
  while(a<150)
  {
  for(a=0;a<150;a++)
  {
   for(b=0;b<1000;b++)
   {
      PORTA = 0x01;
   }
   for(c=0;c<1000;c++)
   {
      PORTA = 0x00;
   }
 }
 
 }
}

void s()
{
   int a,b,c = 0;
  
  while(a<75)
  {
  for(a=0;a<75;a++)
  {
   for(b=0;b<1000;b++)
   {
      PORTA = 0x01;
   }
   for(c=0;c<1000;c++)
   {
      PORTA = 0x00;
   }
   }
   }	
}


void main()
{
   DDRB = 0x0F; //row is input, col is output
   PORTB = 0xFF; //row is high
   DDRA = 0xFF;
   while(1)
   {
      lcd_init();
      for(i=0;i<16;i++)
      {
      while(j!=1)
   {
      
      do
	    {
		KEY_PRT &= 0xF0;      /* mask PORT for column read only */
		asm("NOP");
		colloc = (KEY_PIN & 0xF0); /* read status of column */
	    }while(colloc != 0xF0); 
		
	    do
	    {

		do
		{
	            _delay_ms(20);             /* 20ms key debounce time */
		    colloc = (KEY_PIN & 0xF0); /* read status of column */
		}while(colloc == 0xF0);        /* check for any key press */
			
		_delay_ms (40);	            /* 20 ms key debounce time */
		colloc = (KEY_PIN & 0xF0);
	    }while(colloc == 0xF0);

	KEY_PRT = 0xFE;            /* check for pressed key in 1st row */    
	colloc = KEY_PIN;
	if(colloc == 0xEE) //r1c1
            {
		  lcd_print("A");
		  data[i]='A';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xEE)
		     {
			lcdCommand(0x10);
			lcd_print("B");
			data[i]='B';
			
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xEE)
			   {
			      lcdCommand(0x10);
			      lcd_print("C");
			      data[i]='C';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	       }
	    
	    
	    
	    
	    if(colloc == 0xDE) 
            {
		lcd_print("D");
		 data[i]='D';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xDE)
		     {
			lcdCommand(0x10);
			lcd_print("E");
			data[i]='E';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xDE)
			   {
			      lcdCommand(0x10);
			      lcd_print("F");
			      data[i]='F';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    
	    
	    if(colloc == 0xBE) 
	    {
	       lcd_print("G");
	       data[i]='G';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xBE)
		     {
			lcdCommand(0x10);
			lcd_print("H");
			data[i]='H';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xBE)
			   {
			      lcdCommand(0x10);
			      lcd_print("I");
			      data[i]='I';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    
	    
	KEY_PRT = 0xFD;		/* check for pressed key in 2nd row */
	    colloc = KEY_PIN;
	    if(colloc == 0xED) 
            {
		lcd_print("J");
	       data[i]='J';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3000);
		     colloc = KEY_PIN;  
		     if(colloc == 0xED)
		     {
			lcdCommand(0x10);
			lcd_print("K");
			data[i]='K';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xED)
			   {
			      lcdCommand(0x10);
			      lcd_print("L");
			      data[i]='L';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    if(colloc == 0xDD) 
            {
		lcd_print("M");
	        data[i]='M';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xDD)
		     {
			lcdCommand(0x10);
			lcd_print("N");
			data[i]='N';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xDD)
			   {
			      lcdCommand(0x10);
			      lcd_print("O");
			      data[i]='O';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    if(colloc == 0xBD) 
	    {
	       lcd_print("P");
	       data[i]='P';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xBD)
		     {
			lcdCommand(0x10);
			lcd_print("Q");
			data[i]='Q';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xBD)
			   {
			      lcdCommand(0x10);
			      lcd_print("R");
			      data[i]='R';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    
	 KEY_PRT = 0xFB;		/* check for pressed key in 4nd row */
	    colloc = KEY_PIN;
	    if(colloc == 0xEB) 
            {
		lcd_print("S");
	       data[i]='S';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xEB)
		     {
			lcdCommand(0x10);
			lcd_print("T");
			data[i]='T';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xEB)
			   {
			      lcdCommand(0x10);
			      lcd_print("U");
			      data[i]='U';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    if(colloc == 0xDB) 
            {
		lcd_print("V");
	       data[i]='V';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xDB)
		     {
			lcdCommand(0x10);
			lcd_print("W");
			data[i]='W';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
			   colloc = 0;
			   delay_ms(5000);
			   colloc = KEY_PIN; 
			   if(colloc == 0xDB)
			   {
			      lcdCommand(0x10);
			      lcd_print("X");
			      data[i]='X';
			   }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    if(colloc == 0xBB) 
	    {
	       lcd_print("Y");
	       data[i]='Y';
		  TCNT0 = 0x20;
		  TCCR0 = 0x01;
		  while((TIFR&0x1)==0)
		  {     
		     colloc = 0;
		     delay_ms(3500);
		     colloc = KEY_PIN;  
		     if(colloc == 0xBB)
		     {
			lcdCommand(0x10);
			lcd_print("Z");data[i]='Z';
		     }
		  }
		  TCCR0 = 0;
		  TIFR = 0x1;
		  break;
	    }
	    
	  KEY_PRT = 0xF7;		/* check for pressed key in 5nd row */
	    colloc = KEY_PIN;
	    if(colloc == 0xE7) 
            {
		lcdCommand(0x10);
		lcd_print(" ");
	        data[i-1]=0;
		i-=2;
		lcdCommand(0x10);
	       break;
	    }
	    if(colloc == 0xD7) 
            {
		lcd_print(" ");
	       data[i]=' ';
	       break;
	    }
	    if(colloc == 0xB7) 
	    {
	       while(j!=1)
	       {
	       lcdCommand(0x01);
		  delay_ms(1000);
	       lcd_print("Open ur speaker");
	       
//morse code conv		  
   int ch1=0;
   int ch2=0;
   for(ch1=0;ch1<sizeof data;ch1++)
   {
      if(data[ch1] == 0)
      {
	 delay_ms(1);
      }
      else if(data[ch1] == ' ')
      {
	 delay_ms(300);
      }
      else if(data[ch1] == 'A')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }
      
      else if(data[ch1] == 'B')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }    
      else if(data[ch1] == 'C')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }
      else if(data[ch1] == 'D')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'E')
      {
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'F')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'G')
      {
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'H')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'I')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'J')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'K')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'L')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'M')
      {
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'N')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'O')
      {
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'P')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'Q')
      {
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'R')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'S')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'T')
      {
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'U')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'V')
      {
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'W')
      {
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'X')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'Y')
      {
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(1750);
      }  
       else if(data[ch1] == 'Z')
      {
	 l();
	 delay_ms(500);
	 l();
	 delay_ms(500);
	 s();
	 delay_ms(500);
	 s();
	 delay_ms(1750);
      }
	       i=0;j=1;	      
   } 
	       
	       }
	    
	       break;
	       }  
	 }
      
	 
	 }
      lcdCommand(0x01);
      for(j=0;j<16;j++)
      {
	 data[j]=0;
      }
      j=0;
   }
}

