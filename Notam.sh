#!/bin/bash

# Vérifier si un code ICAO a été fourni
if [ -z "$1" ]; then
    echo "Utilisation : ./run.sh <CODE_ICAO>"
    exit 1
fi

# Supprimer le fichier HTML s'il existe déjà
if [ -f "page.html" ]; then
    echo "🗑 Suppression de l'ancienne page.html..."
    rm page.html
fi

echo "🔍 Récupération des NOTAM..."
./notam "$1"

echo "📄 Génération du fichier HTML..."
./GEN

# Vérifier si page.html a bien été créé avant de continuer
if [ ! -f "page.html" ]; then
    echo "Erreur : page.html n'a pas été généré."
    exit 1
fi

echo "Conversion en PDF..."
./convert

# Suppression du fichier HTML après conversion
echo "🗑 Suppression de page.html..."
rm page.html

echo "Processus terminé. Le fichier PDF est prêt."
#ouverture 
echo "ouverture"
google-chrome output.pdf
