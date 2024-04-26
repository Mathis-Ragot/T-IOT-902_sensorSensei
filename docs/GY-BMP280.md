# GY-BMP280 (BMP280)

## Description du Composant
Le BMP280 est un capteur de pression atmosphérique et de température de précision développé par Bosch Sensortec. Il est utilisé dans une variété d'applications telles que la météorologie, la navigation en intérieur, la surveillance de la qualité de l'air et bien d'autres.

Le GY-BMP280 est un module spécifique qui intègre le capteur BMP280 avec d'autres composants pour faciliter son utilisation. Ce module peut inclure un régulateur de tension, des connecteurs et des résistances de pull-up nécessaires pour l'interface de communication. Il simplifie l'intégration du capteur dans des projets électroniques en fournissant une plateforme prête à l'emploi.

## Spécifications Techniques
- Modèle : GY-BMP280-3.3
- Puce : BMP280
- Alimentation : 3V/3.3V CC
- Courant de crête : 1,12 mA
- Plage de pression atmosphérique : 300-1100 hPa (équivalent à +9000…-500 m au-dessus du niveau de la mer)
- Plage de température : -40 … +85 °C
- Interfaces numériques : I²C (jusqu'à 3,4 MHz) et SPI (3 et 4 fils, jusqu'à 10 MHz)
- Consommation de courant du capteur BMP280 : 2,7 µA à un taux d'échantillonnage de 1 Hz
- Dimensions : 15,0 mm x 11,5 mm

## Fonctionnalités Principales
- Le module GY-BMP280 est équipé du capteur BMP280, qui est un capteur environnemental mesurant la température et la pression barométrique. Il représente une mise à niveau de nouvelle génération par rapport aux capteurs BMP085/BMP180/BMP183.

- Ce capteur est idéal pour une variété d'applications liées à la météo et peut être utilisé en I2C et SPI.

- Ce capteur de précision est la meilleure solution de mesure à faible coût et de haute précision pour mesurer la pression barométrique avec une précision absolue de ±1 hPa et la température avec une précision de ±1.0°C. En raison des variations de pression avec l'altitude et de la grande précision des mesures de pression, il est également possible de l'utiliser comme altimètre avec une précision de ±1 mètre.

## Guide d'Utilisation
- Connectez le capteur BMP280 à votre carte de développement à l'aide des broches VCC, GND, SCL et SDA. en utilisant les broches appropriées (VCC, GND, SCL, SDA) avec le bon niveau de tension (3.3V) pour le capteur BMP280.
- Installer la librairie Adafruit BMP280.
- Configurer le capteur BMP280 en utilisant la librairie Adafruit BMP280 selon la documentation fournie (voir [Sources](#sources)).

## Pinout

![image](https://electrocredible.com/wp-content/uploads/2022/12/bmp280-1024x539.webp)

| Numéro de broche | Nom de la broche | Description                                                                                                                                                                            |
|------------------|------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1                | VCC              | Source d'alimentation de 3,3V CC                                                                                                                                                       |
| 2                | GND              | Masse                                                                                                                                                                                  |
| 3                | SCL              | Horloge série                                                                                                                                                                          |
| 4                | SDA              | Données série                                                                                                                                                                          |
| 5                | CSB              | Broche CSB à la masse pour SPI, à VCC(3,3V) pour I2C. 	<br/>Permet de passer du mode SPI au mode I2C. Par défaut, CSB=1 donc I2C. Si CSB=0 au démarrage, alors le mode SPI est utilisé |
| 6                | SDO              | Données série en sortie / Maître entrée esclave sortie. choix de l’adresse I2C. Si SD0=0, alors l’adresse est 0x76, si SD0=1, alors l’adresse est 0x77                                                                                                                               |



## Sources
- [Présentation du GY-BMP280](https://5.imimg.com/data5/SELLER/Doc/2022/1/WG/FV/GY/1833510/gy-bmp280-3-3-high-precision-atmospheric-pressure-sensor.pdf)
- [Présentation du BMP280](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)
- [Librarie Adafruit BMP280](https://github.com/adafruit/Adafruit_BMP280_Library)
- [Données supplémentaires (basées sur un BME280)](http://gilles.thebault.free.fr/spip.php?article47)