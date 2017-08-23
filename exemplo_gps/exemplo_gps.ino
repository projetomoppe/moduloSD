#include <SPI.h>
#include <SD.h>
#include <TinyGPS.h>

#define ARDUINO_USD_CS 8
#define LOG_FILE_PREFIX "gpslog"
#define MAX_LOG_FILES 100
#define LOG_FILE_SUFFIX "csv"
char logFileName[13];
#define LOG_COLUMN_COUNT]= {
  "longitude", "latitude", "altitude", "speead", "course", "date", "time", "satellites"
};

#define LOG_RATE 5000
unsigned long lastlog = 0;

TinyGPSPlus tinyGPS; 
#define GPS_BAUD 9600

void setup()
{
  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
  
  SerialMonitor.println( "Configurando o cartao SD");
  
  if(!SD.begin(ARDUINO_USD_CS))
  {
    SerialMonitor.println("Erro ao inicializar o cartao SD"); // mensagem enviada se a condicao for verdadeira
  }
  updateFileName(); //sempre que se reiniciar, e criado  um novo arquivo,  e incrementado o número
  printHeader(); // Imprime um cabeçalho na parte superior do novo arquivo
}

void loop()
{
  if((lastLog + LOG_RATE) <= millis()) // Se  LOG_RATE em  milissegundos desde o último registro
  {
    if (tinyGPS.location.isUpdated()) //Se os dados do GPS forem vaildos
    {
      if (logGPSData()) // Registrar os dados do GPS
      {
        SerialMonitor.println("GPS logado"); //mostratr essa mensagem
        lastLog = millis(); // atualizar a variavel
      }
      else // se nao atulizou
      {
        SerialMonitor.println("Falha ao registrar novos dados no GPS"); // sera mostrado uma mensagem de erro no GPS
      }
    }
    else // se nao houver dados no GPS
    {
      SerialMonitor.print("Nao ha dados no GPS"); // sera imprimido esssa mensagem
      SerialMonitor.println(tinyGPS.satellites.value());
    }
  }
  
  while (gpsPort.available()) // 
     tinyGPS.encode(gpsPort.read());
}

byte logGPSData()
{
  File logFile = SD.open (logFileName, FILE_WRITE);
  
  if (logFile)
  {
    logFile.print(tinyGPS.location.lng(), 6);
    logFile.print(',');
    logFile.print(tinyGPS.location.lng(), 6);
    logFile.print(',');
    logFile.print(tinyGPS.altitude.feet(),1);
    logFile.print(',');
    logFile.print(tinyGPS.speed.mph(), 1);
    logFile.print((',');
    logFile.print(tinyGPS.course.deg(),
    logFile.print(',');
    logFile.print(tinyGPS.date.value());
    logFile.print(',');
    lohFile.print(tinyGPS.time.value());
    logFile.print(',');
    logFile.print(tinyGPS.satellites.value());
    logFile.println();
    logFile.close();
    return 1;
  }
    return 0;
}

void printHeader()
{
  File logFile = SD.open (logFileName, FILE_WRITE);
  
  if (logFile)
  {
    int i=0;
    for(; i<LOG_COLUMN_COUNT; i++)
    {
      logFile.print(log_col_names[i]);
      if (i< LOG_COLUMN_COUNT -1)
         logFile.print(',');
      else
         logFile.println();
    }
    logFile.(close);
  }
}

void updateFileName()
{
  int i=0;
  for (; i < MAX_LOG_FILES; i++)
  {
    memset(logFileName, 0, strlen(logFileName));
    
    sprintf(logFileName,"%s%d.%s", LOG_FILE_PREFIX, i, LOG_FILE_SUFIX);
    if (!SD.exists(logFileName, 0, strelen(logFileName));
    {
      break;
    }
    else
    {
      SerialMonitor.print(logFileName);
  SerialMonitor.println(" exists");
    }
  
  }

SerialMonitor.print("File name: ");
SerialMonitor.println(logFileName);
}
