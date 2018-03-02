#include <Servo.h>
#include <ESP8266WiFi.h>

Servo m_direito;
Servo m_esquerdo;

//Nome da sua rede Wifi
const char* ssid = "Mestre";

//Senha da rede
const char* password = "qwerty123";

//IP do ESP (para voce acessar pelo browser)
IPAddress ip(192, 168, 43, 50);

//IP do roteador da sua rede wifi
IPAddress gateway(192, 168, 43, 0);

//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0);

//Criando o servidor web na porta 80
WiFiServer server(80);

//Funcao que sera executada apenas ao ligar o ESP8266
void setup() 
{
  //Preparando o GPIO2, que esta lidago ao LED
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, 1);
  digitalWrite(13, 1);

  //Conectando a� rede Wifi
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo.
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }

  //Iniciando o servidor Web
  server.begin();

  m_direito.attach(13);
  m_esquerdo.attach(12);
}

//Funcao que sera executada indefinidamente enquanto o ESP8266 estiver ligado.
void loop() 
{
  //Verificando se o servidor esta pronto.
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }

  //Verificando se o servidor recebeu alguma requisicao
  while (!client.available()) 
  {
    delay(1);
  }

  //Obtendo a requisicao vinda do browser
  String req = client.readStringUntil('\r');
  client.flush();

  //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser.
  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<head><meta http-equiv=''Acess-Control-Allow-Origin' content='*'></head><meta http-equiv='refresh' content='3'></head><body>";
  buf += "<h3>ESP8266 Servidor Web</h3>";
  buf += "<p>LED <a href=\"?function=www\"><button>Frente</button></a><a href=\"?function=jjj \"><button>Para</button></a></p>";
  buf += "<p>LED <a href=\"?function=aaa\"><button>Esquerdaw</button></a><a href=\"?function=ddd \"><button>Direita</button></a></p>";
  buf += "<h4>Infortronica Para Zumbis</h4>";
  buf += "</body></html>\n";

  //Enviando para o browser a 'pagina' criada.
  client.print(buf);
  client.flush();

  //Analisando a requisicao recebida para decidir se liga ou desliga o LED
  if (req.indexOf("www") != -1)
  {
    m_direito.write(180);
    m_esquerdo.write(180);
  }
   else if (req.indexOf("sss") != -1)
  { 
   m_direito.write(0);
   m_esquerdo.write(0);
  }
  else if (req.indexOf("aaa") != -1)
  {
   m_direito.write(90);
   m_esquerdo.write(180);
  }
  else if (req.indexOf("ddd") != -1)
  {
   m_direito.write(180);
   m_esquerdo.write(90);
  }
  else if (req.indexOf("jjj") != -1)
  {
   m_direito.write(95);
   m_esquerdo.write(95);
  }
  else
  {
    //Requisicao invalida!
    client.stop();
  }
}


