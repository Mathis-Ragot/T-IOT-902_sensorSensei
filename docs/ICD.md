# ICD

La communication LoRa permet de transmettre des données par packet de 256 octets maximum. 8 octets sont occupés par les informations de la trame LoRa, il reste donc 248 octets pour les données utiles principalement issues des capteurs.

Ces données sont transmises sous forme de tableau de bytes. Les données sont structurées de la manière suivante :

| Donnée           | Taille (octets) | Plage de valeurs  | Type de variable | Précision | Description                                |
|------------------|-----------------|-------------------|------------------|-----------|--------------------------------------------|
| ID de l'émetteur | 4               | 0 à 4 294 967 295 | Int              |           | Identifiant de l'émetteur. Valeur fixe.    |
| Poussière        | 1.5             | 0 à 4095          | Unsigned short   | 1 µg/m³   | Concentration de particules fines en µg/m3 |
| Température      | 1.5             | -200 à 200        | Float            | 	0.1 °F   | Température en degrés Fahrenheit           |
| Pression         | 1.5             | 0 à 4095          | Unsigned short   | 1 hPa     | Pression atmosphérique en hPa              |
| Decibels         | 1.5             | 0 à 130           | Float            | 0.1 dB    | Niveau sonore en dB                        |
| Humidité         | 1               | 0 à 100           | Byte             | 1%        | Humidité relative en %                     |


__L'ordre des données est important et doit être respecté lors de la transmission. L'initialisation des capteurs doit être faite dans le même ordre du côté de l'émetteur.__
