
int a =  12;// define the digital interface to connect a seven segment LED 11
int b =  14;// define the connection b Digital Interface 6-segment LED 10 
int c =  27;// define paragraph (c) Digital Interface 5 digital connection 8
int d =  25;// define the digital interface 11 is connected to d-segment digital tube 6
int e =  33;// define the digital interface 10 is connected to e-segment digital tube 5
int f =  13;// define the digital interface 8 digital tube connection f 12
int g =  26;// define the digital interface 9 g of the digital control connection 7
int dp = 13;// define the digital interface 4 digital tube connecting dp
int arr[7] = {a,b,c,d,e,f,g};

void digital_0 (void) // display the number 0
{
unsigned char j;

for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
digitalWrite (g, 0);
}

void digital_1 (void) // display the number 1
{ unsigned char j;
  for (j = 0; j < 8; j++) // off remaining segments
    digitalWrite (arr[j], 0);
  digitalWrite (c, 1) ;// to the digital interface 5-pin 0, lit paragraph (c)
  digitalWrite (b, 1) ;// lit paragraph b
  
//  digitalWrite (dp, 1) ;
}

void digital_2 (void) // display number 2
{ unsigned char j;
  for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (c, 0);
  digitalWrite (f, 0);

}

void digital_3 (void) // display the number 3
{ unsigned char j;
  for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (f, 0);
  digitalWrite (e, 0);
}

void digital_4 (void) // show 4
{ digitalWrite (c, 1);
  digitalWrite (b, 1);
  digitalWrite (f, 1);
  digitalWrite (g, 1);
  digitalWrite (a, 0);
  digitalWrite (e, 0);
  digitalWrite (d, 0);
}

void digital_5 (void) // display the number 5
{
unsigned char j;
for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
digitalWrite (c, 1);
digitalWrite (d, 1);
digitalWrite (b,0);
digitalWrite (e,0);
}

void digital_6(void) // display the number 6
{
unsigned char j;
for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
digitalWrite (c, 1);
digitalWrite (b, 0);
}

void digital_7(void) // display the number 7
{
unsigned char j;
for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
for (j = 3; j < 7; j++)
  digitalWrite (arr[j], 0);
}

void digital_8 (void) // display the number 8
{
unsigned char j;
for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
}

void digital_9 (void) // display the number 9
{ unsigned char j;
  for (j = 0; j < 8; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (e, 0);
}

void digital_a (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (d, 0);
}
void digital_b (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (a, 0);
  digitalWrite (b, 0);
}
void digital_c (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (g, 0);
  digitalWrite (b, 0);
  digitalWrite (c, 0);
}
void digital_d (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (a, 0);
  digitalWrite (f, 0);
}
void digital_e (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (b, 0);
  digitalWrite (c, 0);
}
void digital_f (void){
  unsigned char j;
  for (j = 0; j < 7; j++)
    digitalWrite (arr[j], 1);
  digitalWrite (b, 0);
  digitalWrite (c, 0);
  digitalWrite (d, 0);
}

void setup()
{ int i;// define variables
  for(i = 0; i < 8; i++)
    pinMode(arr[i],OUTPUT);// set 4 to 11 pin to output mode
}

void loop()
{
  
  digital_0() ; // display the number 0
  delay (1000); // delay 2s
  digital_1() ; // display the number 1
  delay (1000); // delay 2s
  digital_2() ; // display the number 2
  delay (1000); // delay 1s
  digital_3() ; // display the number 3
  delay (1000); // delay 1s
  digital_4() ; // display the number 4
  delay (1000); // delay 1s
  digital_5() ; // display the number 5
  delay (1000); // delay 1s
  digital_6() ; // display the number 6
  delay (1000); // delay 1s
  digital_7() ; // display the number 7
  delay (1000); // delay 1s
  digital_8() ; // display the number 8
  delay (1000); // delay 1s
   digital_9() ; // display the number 9
  delay (1000); // delay 1s
  digital_a() ; // display the number 9
  delay (1000); // delay 1s
  digital_b() ; // display the number 9
  delay (1000); // delay 1s
  digital_c() ; // display the number 9
  delay (1000); // delay 1s
  digital_d() ; // display the number 9
  delay (1000); // delay 1s
  digital_e() ; // display the number 9
  delay (1000); // delay 1s
  digital_f() ; // display the number 9
  delay (1000); // delay 1s
 
}
