# API

## Framework & libraries

- Actix web
- Diesel
- Tungstenite

## Databases

- InfluxDB
- PostgreSQL

## Endpoints

Sensors
-----

#### GET /api/v1/sensors
#### POST /api/v1/sensors
#### PATCH /api/v1/sensors
#### DELETE /api/v1/sensors

#### GET /api/v1/sensors/{:id}/measurements
#### GET /api/v1/sensors/{:id}/logs

-----

Devices
-----

#### GET /api/v1/devices
#### POST /api/v1/devices
#### PATCH /api/v1/devices
#### DELETE /api/v1/devices

-----

Auth
-----

#### POST /api/v1/auth/login
#### POST /api/v1/auth/register
#### POST /api/v1/auth/logout