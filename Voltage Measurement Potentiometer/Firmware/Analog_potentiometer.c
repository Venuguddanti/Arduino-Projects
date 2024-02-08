#define RS 0
#define E 2
#define D0 3
#define D1 4
#define D2 5
#define D3 6
#define D4 9
#define D5 10
#define D6 11
#define D7 12
int d;int e;
void setup()
{
  int arr[10]={RS,E,D0,D1,D2,D3};
  for(int i=0;i<10;i++){
    pinMode(arr[i],OUTPUT);
  }
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  lcd_init();
  str("Voltage :");
}
void lcd_init()
{
  cmd(0x38);delay(5);
  cmd(0x01);delay(5);
  cmd(0x0c);delay(5);
  cmd(0x06);delay(5);
  cmd(0x80);delay(5);
}
void cmd(char data){
  digitalWrite(RS,0); 
  digitalWrite(D0,(data&(1<<0))>>0);
  digitalWrite(D1,(data&(1<<1))>>1);
  digitalWrite(D2,(data&(1<<2))>>2);
  digitalWrite(D3,(data&(1<<3))>>3);
  digitalWrite(D4,(data&(1<<4))>>4);
  digitalWrite(D5,(data&(1<<5))>>5);
  digitalWrite(D6,(data&(1<<6))>>6);
  digitalWrite(D7,(data&(1<<7))>>7);
  digitalWrite(E,HIGH);
  digitalWrite(E,LOW);
}
void data(char data){
  digitalWrite(RS, 1);                   
  digitalWrite(D0,(data&(1<<0))>>0);
  digitalWrite(D1,(data&(1<<1))>>1);
  digitalWrite(D2,(data&(1<<2))>>2);
  digitalWrite(D3,(data&(1<<3))>>3);
  digitalWrite(D4,(data&(1<<4))>>4);
  digitalWrite(D5,(data&(1<<5))>>5);
  digitalWrite(D6,(data&(1<<6))>>6);
  digitalWrite(D7,(data&(1<<7))>>7);
  digitalWrite(E,HIGH);
  digitalWrite(E,LOW);
}
void str(char *str)
{
  while(*str!='\0'){
    data(*str++);
  }
}
float analog=0;
float i=analog;
void loop()
{
  float a=analogRead(A0);
  analogWrite(13,a);
  analog=a*5/1023;
  cmd(0xc0);
  lcdprintfloat(analog);
  if(i==analog){
    cmd(0xc0);
  }
  i=analog;
}
void lcdprintfloat(float num){
  int integerpart=(int)num;
  int decimalpart=(int)((num - integerpart)*100);
  lcdprintint(integerpart);
  str(".");
  if (decimalpart < 10) {
     str("0");
  }
  lcdprintint(decimalpart);
}
void lcdprintint(int num) {
    char buffer[16];
    sprintf(buffer, "%d", num);
    str(buffer);
}
