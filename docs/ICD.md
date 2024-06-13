# ICD

La communication LoRa permet de transmettre des données par packet de 256 octets maximum. 8 octets sont occupés par les informations de la trame LoRa, il reste donc 248 octets pour les données utiles principalement issues des capteurs.

Ces données sont transmises sous forme de tableau de bytes. Les données sont structurées de la manière suivante :

| Donnée           | Taille (octets) | Plage de valeurs | Type de variable | Description                                                                                              |
|------------------|-----------------|------------------|------------------|----------------------------------------------------------------------------------------------------------|
| ID de l'émetteur | 1               | 0 à 255          | Byte             | Identifiant de l'émetteur                                                                                |
| Timestamp        | 4               | 0 à 4294967295   | Unsigned long    | Timestamp de la trame (nombre de secondes depuis le 1er janvier 1970) . Format Unix: DD/MM/YYYY HH:MM:SS |
| Latitude         | 8               | -90 à 90         | Double           | Latitude de l'émetteur en degrés décimaux __(avec 6 chiffres après la virgule)__                         |
| Longitude        | 8               | -180 à 180       | Double           | Longitude de l'émetteur en degrés décimaux __(avec 6 chiffres après la virgule)__                        |
| Poussière        | 1.5             | 0 à 4095         | Unsigned short   | Concentration de particules fines en µg/m3                                                               |
| Température      | 1.5             | -200 à 200       | Float            | Température en degrés Fahrenheit __(avec un dixième de précision)__                                      |
| Pression         | 1.5             | 0 à 1100         | Float            | Pression atmosphérique en hPa __(avec un dixième de précision)__                                         |
| Decibels         | 1.5             | 0 à 130          | Float            | Niveau sonore en dB __(avec un dixième de précision)__                                                   |
| Humidité         | 1               | 0 à 100          | Byte             | Humidité relative en %                                                                                   |


__L'ordre des données est important et doit être respecté lors de la transmission. L'initialisation des capteurs doit être faite dans le même ordre du côté de l'émetteur.__
