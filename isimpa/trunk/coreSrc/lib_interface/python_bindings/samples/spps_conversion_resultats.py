# -*- coding: cp1252 -*-

# Titre: Script de conversion en fichiers CSV
# Description: Script de conversion des fichiers de sortie créés par SPPS en fichier CSV
# Date: Avril 2009
# Auteur: N. Fortin et J. Picaut
# Contact: Judicael.Picaut@lcpc.fr

# Chargement des librairies
import os
import libsimpa as ls

def GabeToCsv(filepath,csvpath):
    """
        Converti un fichier GABE (Generic Array Binary Exchange) en format CSV (Comma Separated Values)
    """
    # Instanciation du lecteur
    reader=ls.Gabe_rw()
    # Lecture du fichier gabe
    if reader.Load(filepath):
        # Conversion en liste
        data=reader.ToList()
        # Rotation des données (les colonnes deviennent des lignes)
        data=zip(*data)
        # Ecriture des données
        fich=open(csvpath,'w')
        for line in data:
            firstcol=True
            for col in line:
                if not firstcol:
                    fich.write(",")
                else:
                    firstcol=False
                fich.write(str(col))    # Ecriture de la cellule et virgule
            fich.write("\n")            # Retour à la ligne
        fich.close()

