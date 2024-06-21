#!/bin/bash

source .env

sh ./stop_app.sh &&
docker-compose --env-file .env up -d
