# Choix des composants

## Firmware existant

Fonctionnalités du firmware actuel du projet Sensor Community :

- Connexion au réseau WiFi : Le firmware permet à l'appareil de se connecter à un réseau WiFi disponible, ce qui permet la communication avec d'autres appareils et services en ligne.
- Collecte de données avec un capteur DHT22 : Le firmware est capable de collecter des données de température et d'humidité à l'aide du capteur DHT22. Cette fonctionnalité permet de surveiller les conditions environnementales.
- Envoi des données à sensor.community : Une fois les données collectées, le firmware les envoie à la plateforme sensor.community. Cela permet de partager les informations collectées avec la communauté et de contribuer à une base de données plus large pour la surveillance environnementale.

En résumé, le firmware actuel du projet Sensor Community permet de collecter des données de température et d'humidité à l'aide d'un capteur DHT22, de les envoyer à la plateforme sensor.community via une connexion WiFi, facilitant ainsi la surveillance environnementale et la collaboration au sein de la communauté.


## Amélioration du firmware existant

Nous avons entrepris d'enrichir le firmware du projet Sensor Community en intégrant une gamme de nouveaux composants qui élargissent considérablement nos capacités de collecte et de transmission de données.

1. Heltec Automation LoRa 32 et LilyGo LoRa32 : Ces deux cartes de développement intègrent des modules LoRa, permettant ainsi la communication à longue portée et à faible consommation d'énergie. En les utilisant comme émetteurs et récepteurs, nous serons en mesure d'établir des liaisons robustes pour la transmission des données collectées par nos capteurs.

2. SPH0645 : Le module SPH0645 est un microphone à électret avec un préamplificateur intégré. Son ajout au firmware nous permettra de détecter et d'enregistrer les niveaux sonores ambiants. Cela enrichira considérablement notre ensemble de données en permettant une surveillance précise de l'environnement acoustique, ce qui est crucial dans de nombreuses applications telles que la surveillance de l'environnement urbain ou la détection d'événements sonores anormaux.

3. DHT11 : Le capteur DHT11 est largement utilisé pour mesurer la température et l'humidité relative. Avec sa conception compacte et son interface de communication simple, il offre une solution abordable et fiable pour la surveillance environnementale. L'ajout du DHT11 permettra d'enrichir les données collectées avec des informations sur la température et l'humidité, offrant ainsi une vision plus complète de l'environnement.

4. Waveshare dust sensor : Le capteur de poussière de Waveshare détecte les particules en suspension dans l'air. Son intégration dans le firmware nous permettra de surveiller la qualité de l'air en mesurant la concentration de particules fines. Cela nous permettra de fournir des informations cruciales sur la pollution atmosphérique, aidant ainsi les décideurs et la communauté à prendre des mesures pour protéger la santé publique.

En combinant ces nouveaux composants avec nos capacités de transmission LoRa et WiFi, nous créons un système robuste et polyvalent pour la collecte et la transmission de données environnementales. Ces améliorations permettront à la communauté de Sensor Community d'avoir une vision plus complète et précise de leur environnement, facilitant ainsi la prise de décision informée et la protection de l'environnement. 


## Choix techniques

Utiliser le capteur DHT11 plutôt que le BMP280 peut être préférable pour plusieurs raisons :

1. Simplicité d'utilisation : Le DHT11 est reconnu pour sa facilité d'intégration et son interface de communication simple, ce qui en fait un choix idéal pour les projets où la simplicité est une priorité. Avec seulement une broche de données nécessaire pour la communication, le DHT11 est plus accessible aux débutants en électronique et aux projets nécessitant une mise en œuvre rapide.

2. Mesure combinée de température et d'humidité relative : Le DHT11 fournit des mesures de température et d'humidité relative dans un seul composant, offrant ainsi une solution compacte et tout-en-un pour la surveillance environnementale. Cette fonctionnalité intégrée simplifie la conception du système en réduisant le nombre de composants nécessaires et en économisant de l'espace sur la carte de circuit imprimé.

3. Convivialité pour les applications spécifiques : Si votre application ne nécessite que des mesures de température et d'humidité relative dans une plage de mesure limitée, le DHT11 peut être parfaitement adapté à vos besoins. En évitant les fonctionnalités supplémentaires comme la mesure de la pression atmosphérique offerte par le BMP280, vous pouvez concevoir un système plus simple et plus économe en ressources.

4. Absence de mesure d'humidité pour le BMP280 : Contrairement au DHT11, le BMP280 ne prend pas en charge la mesure de l'humidité relative. Si cette donnée est cruciale pour votre application, choisir le DHT11 est la solution logique pour obtenir des informations complètes sur l'environnement.

En résumé, le DHT11 offre une combinaison de simplicité, de fonctionnalité tout-en-un et de convivialité pour les applications spécifiques qui en font un choix attractif par rapport au BMP280, en particulier si la mesure de l'humidité relative est un élément clé de votre projet.
