# Test Fonctionnal

## 1 - Capteur de température (chaud)
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre la première mesure en se connectant sur Grafana afin de voir les valeurs.
> Des valeurs sont apparues dans l'emplacement de la température.

3. Prendre le capteur de température et le positionner dans un endroit plus chaud (entre vos mains) et attendre la prochaine prise de mesure.

4. Regarder la fluctuation de température sur Grafana.
> Une valeur plus élevée doit apparaître après la première.

## 2 - Capteur de température (froid)
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre la première mesure en se connectant sur Grafana afin de voir les valeurs.
> Des valeurs sont apparues dans l'emplacement de la température.

3. Prendre le capteur de température et le positionner dans un endroit plus froid et attendre la prochaine prise de mesure.
4. Regarder la fluctuation de température sur Grafana.
> Une valeur plus faible doit apparaître après la première.

## 3 - Capteur d'humidité
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre la première mesure en se connectant sur Grafana afin de voir les valeurs.
> Des valeurs sont apparues dans l'emplacement de l'humidité.

3. Prendre le capteur d'humidité et le positionner dans un endroit plus humide (entouré d'un chiffon humide) et attendre la prochaine prise de mesure.
4. Regarder la fluctuation d'humidité sur Grafana.
> Une valeur plus élevée doit apparaître après la première.

## 4 - Capteur de poussière (Dust Sensor)
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre la première mesure en se connectant sur Grafana afin de voir les valeurs.
Des valeurs sont apparues dans l'emplacement du capteur de poussière.

3. Prendre le capteur de poussière et altérer la zone du capteur (cheveux devant, fumer) et attendre la prochaine prise de mesure.
4. Regarder la fluctuation de valeurs sur Grafana.
> Une valeur plus élevée doit apparaître après la première.

## 5 - Capteur Sonore
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre la première mesure en se connectant sur Grafana afin de voir les valeurs.
> Des valeurs sont apparues dans l'emplacement du capteur sonore.

3. Prendre le micro et faire du bruit (parler devant le micro) et attendre la prochaine prise de mesures.
4. Regarder la fluctuation de valeurs sur Grafana.
> Une valeur plus élevée doit apparaître après la première.

## 6 - Wifi
1. Allumer l'émetteur et le récepteur.
> Une diode rouge apparaît sur les deux éléments.

2. Attendre les premières mesures en se connectant sur Grafana afin de voir les valeurs.
> Des valeurs sont apparues dans les emplacements des capteurs.

3. Couper le wifi, et attendre la prochaine prise de mesures.
> Aucune autre valeur n'apparaît dans Grafana.

4. Rallumer le wifi, et attendre la prochaine prise de mesures.
> De nouvelles valeurs apparaissent dans Grafana.