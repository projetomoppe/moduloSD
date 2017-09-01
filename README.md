# moduloSD
Testes com o Módulo SD

## começando
O Módulo SD será usado com intuito de armazenamento de dados 

## Execultando os testes
Faremos os testes ultizando uma placa arduino juntamente com sensores de nivel icos e com o sensor ultrasônico 

## Notas adicionais sobre como implantar isso em um sistema ao vivo

'''

É preciso adicionar algumas bibliotecas especificas para o bom andamento do teste

#include <SPI.h> (É um protocolo de dados usado por microcontroladores para se comunicar dispositivos periféricos em curtas distâncias)

#include <SD.h> (Oferece os recursos básicos para gravar e ler arquivos SD)

#include <TinyGPS.h> (Fornece algumas funcionalidades como:  posição, data, hora, altitude, velocidade entre outros) 

#include <SdFat.h> (Inicializa ou imprime um erro)

'''


## Construindo Com:

* https://github.com/projetomoppe/moduloSD/blob/master/exemplo_gps/exemplo_gps.ino
