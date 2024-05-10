
# Dust Sensor (Waveshare GP2Y1010AU0F)

## Description du Composant
Le capteur de poussière Waveshare est un dispositif conçu pour détecter la concentration de particules en suspension dans l'air. Il utilise un laser pour mesurer la quantité de poussière présente dans l'air et fournit des données précises sur la qualité de l'air environnant.

## Spécifications Techniques
- Modèle : Waveshare Dust Sensor
- Puce : GP2Y1010AU0F
- Alimentation : 2.5V~5.5V
- Courant de crête :  20mA(max)
- Plage de température : -10℃~65℃
- Plage de mesure: 500μg/m3
- Interfaces numériques : One Wire
- Dimensions : 63.2mm × 41.3mm × 21.1mm

## Fonctionnalités Principales
- détecter les particules fines d'un diamètre supérieur à 0,8μm, même comme la fumée de cigarette.
- Faible consommation d'énergie, sortie de tension analogique, le niveau de sortie est linéaire en fonction de la densité de la poussière.
- Circuit de suralimentation intégré pour prendre en charge une large gamme d'alimentations.

| density value(μg/m3) | Air quality index AQI | Air quality level  | Air quality evaluation    |
|----------------------|-----------------------|--------------------|---------------------------|
| 0-35                 | 	0-50                 | 	Ⅰ                 | 	Excellent                |
| 35-75                | 	51-100               | 	Ⅱ                 | 	Average                  |
| 75-115               | 	101-150              | 	Ⅲ                 | 	Light pollution          |
| 115-150              | 	151-200              | 	Ⅳ                 | 	Moderate pollution       |
| 150-250              | 	201-300              | 	Ⅴ                 | 	Heavy pollution          |
| 250-500              | 	≥300                 | 	Ⅵ                 | 	Serious pollution        |     

## Guide d'Utilisation
- Connectez le capteur de poussière Waveshare à votre microcontrôleur ou système embarqué à l'aide des câbles appropriés. Assurez-vous de respecter les connexions correctes selon le schéma fourni dans la documentation du capteur.
- Avant de commencer à utiliser le capteur, assurez-vous de l'initialiser correctement en suivant les instructions fournies dans la documentation. Cela peut inclure des étapes telles que l'activation du capteur, la configuration des paramètres de fonctionnement, etc.
- Une fois le capteur initialisé, vous pouvez commencer à lire les données de poussière à partir du capteur en utilisant les fonctions appropriées de la bibliothèque logicielle. Assurez-vous de comprendre les unités dans lesquelles les données sont fournies (généralement en nombre de particules par unité de volume) et de les interpréter correctement.

## Pinout

![image](https://www.waveshare.com/w/upload/7/74/Dust-Sensor-Pico_1.jpg)

| Numéro de broche | Nom de la broche | Description                                                                                                                                                                            |
|------------------|------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1                | VCC              | Source d'alimentation de 2.5V ~ 5.0V CC                                                                                                                                                |
| 2                | GND              | Masse                                                                                                                                                                                  |
| 3                | AOUT             | MCU.IO (analog output)                                                                                                                                                                 |
| 4                | ILED             | MCU.IO (module driving pin)                                                                                                                                                            |


## Sources
- [Présentation du Dust Sensor](https://www.waveshare.com/wiki/Dust_Sensor)
- [Doc raspberry pi](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Page commercial](https://www.waveshare.com/dust-sensor.htm)
- [Repo exemple d'utilisation](https://github.com/renebohne/esp32-weather-station)