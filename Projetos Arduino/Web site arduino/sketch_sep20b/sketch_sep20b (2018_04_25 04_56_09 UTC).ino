/*
 Web Server - HTTP Autentication
 Baseado na versão de exemplo do Arduino.
  
   - exemplo que mostra como incluir html, css, 
   javascript e imagem em arquivos no sdcard e também
   como fazer download de um arquivo pdf do sdcard.
   
   by Fabiano A. Arndt (fabianoallex)
*/
 
/**********************************************************************************
************************************BIBLIOTECAS************************************
**********************************************************************************/
 
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
 
/**********************************************************************************
********************************FIM BIBLIOTECAS************************************
**********************************************************************************/
 
/**********************************************************************************
*************************ROTINAS USUARIO E SENHA***********************************
***********************************************************************************/
 
boolean validar_usuario(char * linebuf) {
  /*
  nesse exemplo o usuario e senha estão definidos dentro do código fonte.
  mas o usuário e senha poderiam ser autenticados de diversas maneiras,
  lendo os dados de um servidor web, arquivo texto, etc, bastando apenas atribuir
  o valor lido para a variável usuario_senha. 
  */
   
  char usuario_senha[] = "123:123";                           //usuario e senha para acessar a pagina
  int t = strlen(usuario_senha);
   
  int tamanhoEnc = (((t-1) / 3) + 1) * 4;   //tamanho da string codificada
  char out[tamanhoEnc];
  base64_encode(out, usuario_senha, t+1 );
   
  //---desconta é usado pra eliminar os caracteres '='
  int desconta = 0;
  if ((t%3) == 1) { desconta = 2; }
  if ((t%3) == 2) { desconta = 1; }
   
  char out2[tamanhoEnc-desconta];
   
  byte i;
  for (i=0; i<(tamanhoEnc-desconta);i++){ out2[i] = out[i]; }
  out2[i] = '\0';
   
  return ( strstr(linebuf, out2)>0 );
}
 
/**********************************************************************************
*************************FIM ROTINA USUARIO E SENHA********************************
***********************************************************************************/
 
/****************************************************************************************
 ****************************SD CARD INICIO***********************************************
 ****************************************************************************************/
 
#define PIN_SD_CARD 4
  
boolean iniciar_sd_card() {
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
    
  if (!SD.begin(PIN_SD_CARD)) { return false; }
    
  return true;
}
 
  
/****************************************************************************************
 ****************************SD CARD FIM**************************************************
 ****************************************************************************************/
  
 
/**********************************************************************************
***********************************PAGINAS HTML************************************
***********************************************************************************/
EthernetServer * server;
 
void write_from_file(EthernetClient &client, char * filename){
  File webFile = SD.open(filename);
  if (webFile) {
    while(webFile.available()) {
      client.write(webFile.read()); 
    }
    webFile.close();
  } else {
    Serial.print("Erro SD CARD: ");
    Serial.println(filename);
  }
}
 
void iniciar_ethernet_01(){
  byte ip[4]      = {192,168,100,50};                    //definir aqui o ip
  byte gateway[4] = {192,168,100,1};
  byte subnet[4]  = {255,255,255,0};
  byte mac[6]     = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  int  porta      = 80;
 
  server = new EthernetServer(porta);
 
  Ethernet.begin(mac, ip, gateway, subnet);         //caso necessario gateway utilizar essa linha
  server->begin();
}
 
void iniciar_ethernet_02(){
  byte ip[4]      = {192,168,200,25};                    //definir aqui o ip
  byte mac[6]     = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  int  porta      = 80;
 
  server = new EthernetServer(porta);
 
  Ethernet.begin(mac, ip);
  server->begin();
}
 
void iniciar_ethernet() {              //escolher apenas um dos dois modos de iniciar o ethernet shield
  iniciar_ethernet_01();               //inicia com ip, gateway, mascara e porta
  //iniciar_ethernet_02();             //inicia só com ip e porta
}
 
void html_cab_200_ok(EthernetClient &client){
   
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: text/html\n"
                   "Connection: keep-alive\n\n"));
}
 
 
void html_logoff(EthernetClient &client){
    client.print(F(
                 "HTTP/1.1 401 Authorization Required\n"  
                 "Content-Type: text/html\n"  
                 "Connnection: close\n\n"  
                 "<!DOCTYPE HTML>\n"  
                 "<html><head><title>Logoff</title>\n"  
                 "<script>document.execCommand('ClearAuthenticationCache', 'false');</script>"  //IE logoff
                 "<script>try {"                                                                //mozila logoff
                 "   var agt=navigator.userAgent.toLowerCase();"
                 "   if (agt.indexOf(\"msie\") != -1) { document.execCommand(\"ClearAuthenticationCache\"); }"
                 "   else {"
                 "     var xmlhttp = createXMLObject();"
                 "      xmlhttp.open(\"GET\",\"URL\",true,\"logout\",\"logout\");"
                 "     xmlhttp.send(\"\");"
                 "     xmlhttp.abort();"
                 "   }"
                 " } catch(e) {"
                 "   alert(\"erro ao fazer logoff\");"
                 " }"
                 "function createXMLObject() {"
                 "  try {if (window.XMLHttpRequest) {xmlhttp = new XMLHttpRequest();} else if (window.ActiveXObject) {xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\");}} catch (e) {xmlhttp=false;}"
                 "  return xmlhttp;"
                 "}</script>"
                 "</head><body><h1>Voce nao esta mais conectado</h1></body></html>\n"));
}
 
void html_autenticar(EthernetClient &client) {
  client.print(F("HTTP/1.1 401 Authorization Required\n"  
               "WWW-Authenticate: Basic realm=\"Area Restrita\"\n"  
               "Content-Type: text/html\n"  
               "Connnection: close\n\n"  
               "<!DOCTYPE HTML>\n"  
               "<html><head><title>Error</title>\n"  
               "</head><body><h1>401 Acesso nao autorizado</h1></body></html>\n"));
}
 
void html_autenticado(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: text/html\n"
                   "Connection: keep-alive\n"));
 
  write_from_file(client, filename);
}
 
 
void js_file(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: text/javascript\n"
                   "Connection: keep-alive\n"));
 
  write_from_file(client, filename);
}
 
void css_file(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: text/css\n"
                   "Connection: keep-alive\n"));
 
  write_from_file(client, filename);
}
 
void favicon_file(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: image/x-icon\n"
                   "Connection: keep-alive\n"));
 
  write_from_file(client, filename);
}
 
 
void pdf_file_download(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: application/download\n"
                   "Connection: close\n"));
     
  write_from_file(client, filename);
}
 
void jpg_file(EthernetClient &client, char * filename){
  client.println(F("HTTP/1.1 200 OK\n"
                   "Content-Type: file/jpg\n"
                   "Connection: close\n"));
     
  write_from_file(client, filename);
}
 
 
void exec_ethernet() {
  EthernetClient client = server->available();
  if (client) {
    char linebuf[80];
    memset(linebuf, 0, sizeof(linebuf));
     
    int     charCount          = 0;
    boolean autenticado        = false;
    boolean currentLineIsBlank = true;
    boolean logoff             = false;
    boolean indCss             = false;
    boolean indJs              = false;
    boolean indPdfDataSheet    = false;
    boolean indJpgUno          = false;
    boolean indFavicon         = false;
     
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
         
        linebuf[charCount] = c;
         
        if (charCount<sizeof(linebuf)-1) { charCount++; }
        Serial.write(c);
         
        if (c == '\n' && currentLineIsBlank) {
          if (autenticado && !logoff ) {
            if (indJs){
              js_file(client, "js.js");                          //js file
            } else if(indCss){
              css_file(client, "css.css");                       //css file
            } else if(indPdfDataSheet){
              pdf_file_download(client, "atmel.pdf");        //datasheet download
            } else if(indJpgUno){
              jpg_file(client, "uno.jpg");                       //jpg file
            } else if(indFavicon){
              jpg_file(client, "favicon.ico");                   //icone do browser
            } else {
              html_autenticado(client, "index.htm");             //página inicial
            }
          } else {
            logoff ? html_logoff(client) : html_autenticar(client);
          }
          break;
        }
        if (c == '\n') { 
          currentLineIsBlank = true;               
           
          if (strstr(linebuf, "GET /logoff"         )>0 ) { logoff = true; }
          if (strstr(linebuf, "Authorization: Basic")>0 ) { if ( validar_usuario(linebuf) )   {  autenticado = true;   } }  
          if (strstr(linebuf, "GET /css.css"        )>0 ) { indCss = true; }
          if (strstr(linebuf, "GET /js.js"          )>0 ) { indJs = true; }
          if (strstr(linebuf, "GET /atmel.pdf"      )>0 ) { indPdfDataSheet = true; }
          if (strstr(linebuf, "GET /uno.jpg"        )>0 ) { indJpgUno = true; }
          if (strstr(linebuf, "GET /favicon.ico"    )>0 ) { indFavicon = true; }
           
           
          memset(linebuf, 0, sizeof(linebuf));
          charCount = 0;
        } else if (c != '\r') {
          currentLineIsBlank = false;    // you've gotten a character on the current line
        }
      }
    }
     
    delay(1);           
    client.stop();      
  }
}
/**********************************************************************************
**************************************** FIM PAGINAS HTML**************************
***********************************************************************************/
 
 
/**********************************************************************************
*************************BASE 64 CODE/DECODE DO USUARIO E SENHA********************
***********************************************************************************/
 
void a3_to_a4(unsigned char * a4, unsigned char * a3);
void a4_to_a3(unsigned char * a3, unsigned char * a4);
unsigned char b64_lookup(char c);
 
int base64_encode(char *output, char *input, int inputLen) {
  const char b64_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  int i=0, j=0, encLen=0;
  unsigned char a3[3], a4[4];
 
  while(inputLen--) {
    a3[i++] = *(input++);
    if(i == 3) {
      a3_to_a4(a4, a3);
      for(i=0; i<4; i++) { output[encLen++] = b64_alphabet[a4[i]]; }
      i = 0;
    }
  }
 
  if (i) {
    for(j = i; j < 3; j++)     { a3[j] = '\0';                           }
    a3_to_a4(a4, a3);
    for(j = 0; j < i + 1; j++) { output[encLen++] = b64_alphabet[a4[j]]; }
    while((i++ < 3))           { output[encLen++] = '=';                 }
  }
  output[encLen] = '\0';
  return encLen;
}
 
/*
int base64_decode(char * output, char * input, int inputLen) {
  int i = 0, j = 0;
  int decLen = 0;
  unsigned char a3[3];
  unsigned char a4[4];
  while (inputLen--) {
    if (*input == '=') { break; }
    a4[i++] = *(input++);
    if (i == 4) {
      for (i = 0; i <4; i++)  { a4[i] = b64_lookup(a4[i]); }
      a4_to_a3(a3,a4);
      for (i = 0; i < 3; i++) { output[decLen++] = a3[i];  }
      i = 0;
    }
  }
 
  if (i) {
    for (j=i; j<4; j++)   { a4[j] = '\0';             }
    for (j=0; j<4; j++)   { a4[j] = b64_lookup(a4[j]);}
    a4_to_a3(a3,a4);
    for (j=0; j<i-1; j++) { output[decLen++] = a3[j]; }
  }
  output[decLen] = '\0';
  return decLen;
}
*/
 
//int base64_enc_len(int plainLen) {
//  int n = plainLen;
//  return (n + 2 - ((n + 2) % 3)) / 3 * 4;
//}
 
//int base64_dec_len(char * input, int inputLen) {
//  int i = 0;
//  int numEq = 0;
//  for(i = inputLen - 1; input[i] == '='; i--) { numEq++; }
//  return ((6 * inputLen) / 8) - numEq;
//}
 
void a3_to_a4(unsigned char * a4, unsigned char * a3) {
  a4[0] = (a3[0]  & 0xfc) >> 2;
  a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
  a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
  a4[3] = (a3[2] & 0x3f);
}
 
//void a4_to_a3(unsigned char * a3, unsigned char * a4) {
//  a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
//  a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
//  a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
//}
 
unsigned char b64_lookup(char c) {
  if(c >='A' && c <='Z') return c - 'A';
  if(c >='a' && c <='z') return c - 71;
  if(c >='0' && c <='9') return c + 4;
  if(c == '+') return 62;
  if(c == '/') return 63;
  return -1;
}
 
/**********************************************************************************
*************************FIM BASE 64 CODE/DECODE DO USUARIO E SENHA****************
***********************************************************************************/
 
/**********************************************************************************
**************************************** VOID / LOOP ******************************
***********************************************************************************/
 
void setup() {
  Serial.begin(9600);
  iniciar_sd_card();
  iniciar_ethernet();
}
 
void loop() {
  exec_ethernet();
}
 
/**********************************************************************************
*************************************FIM VOID / LOOP*******************************
***********************************************************************************/
