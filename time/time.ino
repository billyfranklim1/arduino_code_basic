int segundo,minuto, hora, dia, mes,ano;
unsigned long UtlTime;
void setup()
{
UtlTime=0;
minuto=0;
hora=0;
dia=0;
mes=0;
ano=0;
Serial.begin(9600);
while(minuto==0)
{
if (Serial.available() > 0) 
{
minuto= 50; //adicionar minuto
}
}
while(hora==0)
{
if (Serial.available() > 0) 
{
hora= 18; // entrar com a hora
}
}
while(dia==0)
{
if (Serial.available() > 0) 
{
dia = 8 ; // entrar com o dia
}
}
while(mes==0)
{
if (Serial.available() > 0) 
{
mes=9; // entrar com o mes
}
}
while(ano==0)
{
if (Serial.available() > 0) 
{
ano= 2017;// entrar com o ano
}
}

}
void loop(){
  horacerta();
  }



  
void horacerta()
{
if(millis()-UtlTime<0)
{
UtlTime=millis();
}else
{
segundo=int((millis()-UtlTime)/1000);
}
if(segundo>59)
{
segundo=0;
minuto++;
UtlTime=millis();
if(minuto>59)
{
hora++;
minuto=0;
if(hora>23)
{
dia++;
hora=0;
if(mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)
{
if(dia>31)
{
dia=1;
mes++;
if(mes>12)
{
ano++;
mes=1;
}
}
}
else if(mes==2)
{
if(ano%400==0)
{
if(dia>29)
{
dia=1;
mes++;
}
}
else if((ano%4==0)&&(ano%100!=0))
{
if(dia>29)
{
dia=1;
mes++;
}
}
else
{
if(dia>28)
{
dia=1;
mes++;
}
}
}
else
{
if(dia>30)
{
dia=1;
mes++;
}
}
}
}
} 
Serial.print(dia);
Serial.print("/");
Serial.print(mes);
Serial.print("/");
Serial.print(ano);
Serial.print(" ");
Serial.print(hora);
Serial.print(":");
Serial.print(minuto);
Serial.print(":");
Serial.print(segundo);
Serial.print("\n");
delay(1000);
}
