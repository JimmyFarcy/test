# -*- coding: cp1252 -*-
import libsimpa as ls

##############################################
# Tableaux
 
#Définition des 8 sommets du cube           
sommets=[   [5.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.0, 5.0, 0.0],
            [5.0, 5.0, 0.0],
            [0.0, 5.0, 5.0],
            [5.0, 5.0, 5.0],
            [0.0, 0.0, 5.0],
            [5.0, 0.0, 5.0]
        ]
#Définition des 12 faces triangulaire du cube
# [ sommetA, sommetB, sommetC, idencombrement, idmateriau, idrecepteursurf ]
faces=  [   [0, 1, 2, -1, 66, -1],
        [0, 2, 3, -1, 66, -1],
        [2, 4, 5, -1, 100, -1],
        [2, 5, 3, -1, 100, -1],
        [2, 6, 4, -1, 100, -1],
        [2, 1, 6, -1, 100, -1],
        [1, 0, 7, -1, 100, -1],
        [6, 1, 7, -1, 100, -1],
        [0, 3, 5, -1, 100, -1],
        [7, 0, 5, -1, 100, -1],
        [7, 5, 4, -1, 66, -1],
        [6, 7, 4, -1, 66, -1]
        ]
############################################
## Création du modèle 3D

def CreerModele(filepath):
    """
        Création du modèle 3D
    """
    model=ls.ioModel()
    #Ajout des sommets
    for sommet in sommets:
        model.vertices.append(ls.t_pos(sommet[0],sommet[1],sommet[2]))
    #Ajout des faces
    for face in faces:
        newface=ls.ioFace()
        newface.a=face[0]
        newface.b=face[1]
        newface.c=face[2]
        newface.idEn=face[3]
        newface.idMat=face[4]
        newface.idRs=face[5]
        model.faces.append(newface)
    #sauvegarde du modèle
    ls.CformatBIN().ExportBIN(filepath,model)
