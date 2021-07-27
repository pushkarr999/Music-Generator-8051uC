#include<reg52.h>
#include <intrins.h>
#include<stdio.h>
#include<stdlib.h>

sbit P3_7 = P3 ^ 7;

sbit rs = P3^0;  //RS pin connected to pin 2 of port 3
sbit rw = P3^1;  // RW pin connected to pin 3 of port 3
sbit e =  P3^2;  //E pin connected to pin 4 of port 3

sbit C4 = P1^0;     // Connecting keypad to Port 1
sbit C3 = P1^1;
sbit C2 = P1^2;
sbit C1 = P1^3;
sbit R4 = P1^4;
sbit R3 = P1^5;
sbit R2 = P1^6;
sbit R1 = P1^7;

sbit switch_library = P2 ^ 4;
sbit switch_metronome = P2 ^ 1;
sbit switch_tanpura = P2 ^ 2;
sbit switch_keyboard = P2 ^ 3;

#define display_port P0      //Data pins connected to port 2 on microcontroller
#define pitch_P		0
#define pitch_C5 64655
#define pitch_Db5 64705
#define pitch_D5 64751
#define pitch_Eb5 64795
#define pitch_E5 64837
#define pitch_F5 64876
#define pitch_Gb5 64913
#define pitch_G5 64948
#define pitch_Ab5 64981
#define pitch_A5 65012
#define pitch_Bb5 65042
#define pitch_B5 65069
#define pitch_C6 65096
#define pitch_Db6 65120
#define pitch_D6 65144
#define pitch_Eb6 65166
#define pitch_E6 65186
#define pitch_F6 65206
#define pitch_Gb6 65225
#define pitch_G6 65242
#define pitch_Ab6 65259
#define pitch_A6 65274
#define pitch_Bb6 65289
#define pitch_B6 65303

#define MelodyPin	P3_7

unsigned int qtrN, wholeN, halfN, eighthN,sixteenN, thirtyTwoN,sixtyFourN,sixN,twelveN,twentyFourN;
unsigned int flag_keyboard=0;
unsigned int index=0,metro=0;
char tempo[3]={0};

void Delay10MC(unsigned char);

void T2ISR(void) interrupt 5 {
	MelodyPin = ~MelodyPin;
	TF2 = 0;
}

void MelodyTempo(int Tempo){
	qtrN = ((60000/Tempo));
	wholeN = qtrN*4;
	halfN = (qtrN*2);
	eighthN = (qtrN/2);
	sixteenN = (qtrN/4);
	thirtyTwoN = (qtrN/8);
	sixtyFourN = (qtrN/16);
	sixN = (wholeN/6);
	twelveN = (wholeN/12);
	twentyFourN = (wholeN/24);
}

void PlayNote(const unsigned char PitchH, const unsigned char PitchL){
	RCAP2H = PitchH;
	RCAP2L = PitchL;
	TH2 = PitchH;
	TL2 = PitchL;
	TF2 = 0;
	TR2 = 1;
	ET2 = 1;
	EA = 1;
}

void EndNote(void){
	EA = 0;
	TR2 = 0;
	TF2 = 0;
	MelodyPin = 1;
}

void delay_ms(unsigned int ms){
	for(;ms>0;ms--)
		Delay10MC(100);
}

void Melodyplay(const int Pitch, unsigned int interval){
	if(Pitch!=0)
		PlayNote(Pitch >> 8, Pitch);
	delay_ms(interval);
	EndNote();
}

void Saregama(){
	MelodyTempo(240);
	Melodyplay(pitch_Db5, qtrN);
	Melodyplay(pitch_Eb5, qtrN);
	Melodyplay(pitch_F5, qtrN);
	Melodyplay(pitch_Gb5, qtrN);
	Melodyplay(pitch_Ab5, qtrN);
	Melodyplay(pitch_Bb5, qtrN);
	Melodyplay(pitch_C6, qtrN);
	Melodyplay(pitch_Db6, qtrN);
	Melodyplay(pitch_P, wholeN);
	Melodyplay(pitch_Db6, qtrN);
	Melodyplay(pitch_C6, qtrN);
	Melodyplay(pitch_Bb5, qtrN);
	Melodyplay(pitch_Ab5, qtrN);
	Melodyplay(pitch_Gb5, qtrN);
	Melodyplay(pitch_F5, qtrN);
	Melodyplay(pitch_Eb5, qtrN);
	Melodyplay(pitch_Db5, qtrN);
}

void tanpura(){
	//MelodyTempo(120);
	Melodyplay(pitch_C6, 500);
	Melodyplay(pitch_G6, 500);
	Melodyplay(pitch_C5, 500);
	Melodyplay(pitch_P, 500);
}

void lcd_cmd(unsigned char command)  //Function to send command instruction to LCD
{
    display_port = command;
    rs= 0;
    rw=0;
    e=1;
    delay_ms(20);
    e=0;
}

void lcd_data(unsigned char disp_data)  //Function to send display data to LCD
{
    display_port = disp_data;
    rs= 1;
    rw=0;
    e=1;
    delay_ms(20);
    e=0;
}

 void lcd_init()    //Function to prepare the LCD  and get it ready
{
    lcd_cmd(0x38);  // for using 2 lines and 5X7 matrix of LCD
    delay_ms(10);
    lcd_cmd(0x0F);  // turn display ON, cursor blinking
    delay_ms(10);
    lcd_cmd(0x01);  //clear screen
    delay_ms(10);
    lcd_cmd(0x80);  // bring cursor to position 1 of line 1
    delay_ms(10);
}

void row_finder1() //Function for finding the row for column 1
{
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;

if(R1==0 && flag_keyboard==0)
{
	lcd_data('1');//7
	tempo[index]='1';//7
	index++;
}
if(R1==0 && flag_keyboard==1)
	Melodyplay(pitch_C5, 250);
if(R2==0 && flag_keyboard==0)
{
	lcd_data('5');//4
	tempo[index]='5';
	index++;
}
if(R2==0 && flag_keyboard==1)
{
	Melodyplay(pitch_E5, 250);
}
if(R3==0 && flag_keyboard==0)
{
	lcd_data('9');//1
	tempo[index]='9';
	index++;
}
if(R3==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Ab5, 250);
}
//if(R4==0 && flag_keyboard==0)
//lcd_data('O');
if(R4==0 && flag_keyboard==1)
{
	Melodyplay(pitch_C6, 250);
}
}

void row_finder2() //Function for finding the row for column 2
{
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;

if(R1==0 && flag_keyboard==0)
{
	lcd_data('2');//8
	tempo[index]='2';
	index++;
}
if(R1==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Db5, 250);
}
if(R2==0 && flag_keyboard==0)
{
	lcd_data('6');//5
	tempo[index]='6';
	index++;
}
if(R2==0 && flag_keyboard==1)
{
	Melodyplay(pitch_F5, 250);
}
if(R3==0 && flag_keyboard==0)
{
	lcd_data('0');//2
	tempo[index]='0';
	index++;
}
if(R3==0 && flag_keyboard==1)
{
	Melodyplay(pitch_A5, 250);
}
//if(R4==0 && flag_keyboard==0)
//{
//	lcd_data('0');
//	tempo[index]='0';
//	index++;
//}
if(R4==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Db6, 250);
}
}

void row_finder3() //Function for finding the row for column 3
{
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;

if(R1==0 && flag_keyboard==0)
{
	lcd_data('3');//9
	tempo[index]='3';
	index++;
}
if(R1==0 && flag_keyboard==1)
{
	Melodyplay(pitch_D5, 250);
}
if(R2==0 && flag_keyboard==0)
{
	lcd_data('7');//6
	tempo[index]='7';
	index++;
}
if(R2==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Gb5, 250);
}
//if(R3==0 && flag_keyboard==0)
//{
	//lcd_data('3');
	//tempo[index]='3';
	//index++;
//}
if(R3==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Bb5, 250);
}
if(R4==0 && flag_keyboard==0)
{
	//lcd_data('=');
	metro=1;
}
if(R4==0 && flag_keyboard==1)
{
	Melodyplay(pitch_D6, 250);
}
}

void row_finder4() //Function for finding the row for column 4
{
R1=R2=R3=R4=1;
C1=C2=C3=C4=0;

if(R1==0 && flag_keyboard==0)
{
	lcd_data('4');//a
	tempo[index]='4';
	index++;
}
if(R1==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Eb5, 250);
}
if(R2==0 && flag_keyboard==0)
{
	lcd_data('8');//b
	tempo[index]='8';
	index++;
}
if(R2==0 && flag_keyboard==1)
{
	Melodyplay(pitch_G5, 250);
}
//if(R3==0 && flag_keyboard==0)
//lcd_data('C');
if(R3==0 && flag_keyboard==1)
{
	Melodyplay(pitch_B5, 250);
}
//if(R4==0 && flag_keyboard==0)
//lcd_data('D');
if(R4==0 && flag_keyboard==1)
{
	Melodyplay(pitch_Eb6, 250);
}
}

void metronome(int tempo)
{
	MelodyTempo(tempo);
	Melodyplay(pitch_B5, eighthN);
	Melodyplay(pitch_P, eighthN);
	Melodyplay(pitch_B5, eighthN);
	Melodyplay(pitch_P, eighthN);
	Melodyplay(pitch_B5, eighthN);
	Melodyplay(pitch_P, eighthN);
	Melodyplay(pitch_B6, eighthN);
	Melodyplay(pitch_P, eighthN);
}

void main()
{
		unsigned char lib[]="Library";
		unsigned char met[]="Metronome";
		unsigned char tan[]="Tanpura";
		unsigned char key[]="Keyboard";
		unsigned char cmd[]="Tempo:";
		unsigned int i,flag=0;
		switch_library = 1;
		switch_metronome = 1;
		switch_tanpura = 1;
		switch_keyboard = 1;
    lcd_init();
    while(1)
    {    
				if(switch_library == 0)
				{
					lcd_cmd(0x01);
					//lcd_cmd(0x01);//clear display
					for(i=0;i<7;i++)
						lcd_data(lib[i]);
					Saregama();
					delay_ms(1000);
				}
				if(switch_metronome == 0 && flag==0)//display msg
				{
					metro=0;index=0;
					flag_keyboard=0;
					lcd_cmd(0x01);
					//lcd_cmd(0x01);//clear display
					for(i=0;i<9;i++)
						lcd_data(met[i]);
					lcd_cmd(0xC0);
					for(i=0;i<6;i++)
						lcd_data(cmd[i]);
					flag=1;
				}
				if(switch_metronome == 0)
				{
					if(metro==0)
					{
						delay_ms(200); 
						C1=C2=C3=C4=1;
						R1=R2=R3=R4=0;
						if(C1==0)
							row_finder1();
						else if(C2==0)
							row_finder2();
						else if(C3==0)
							row_finder3();
						else if(C4==0)
							row_finder4();
					}
					if(metro==1)
					{
						int k=((tempo[2]-'0')+((tempo[1]-'0')*10)+((tempo[0]-'0')*100));
						metronome(k);
					}
				}
				if(switch_tanpura == 0)
				{
					lcd_cmd(0x01);//clear display
					for(i=0;i<7;i++)
						lcd_data(tan[i]);
					tanpura();
				}
				if(switch_keyboard == 0 && flag_keyboard==0)
				{
					lcd_cmd(0x01);//clear display
					for(i=0;i<8;i++)
						lcd_data(key[i]);
					flag_keyboard=1;
					flag=0;
					
				}
				if(switch_keyboard == 0)
				{
					delay_ms(150); 
					C1=C2=C3=C4=1;
					R1=R2=R3=R4=0;
					if(C1==0)
						row_finder1();
					else if(C2==0)
						row_finder2();
					else if(C3==0)
						row_finder3();
					else if(C4==0)
						row_finder4();
				}
    }

}
