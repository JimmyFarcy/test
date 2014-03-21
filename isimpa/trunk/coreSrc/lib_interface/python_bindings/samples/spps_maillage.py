# -*- coding: cp1252 -*-
import libsimpa as ls

def push_mesh_nodelist(maillage,vertices):
    """
        Transforme un tableau python en liste de position de noeud dans un maillage
        Le tableau python doit etre de taille nbsommets*3
    """
    for vertex in vertices:
        newnode=ls.t_binNode()
        newnode.node[0]=vertex[0]
        newnode.node[1]=vertex[1]
        newnode.node[2]=vertex[2]
        maillage.nodes.append(newnode)
def push_tetraedres(maillage,tetralst):
    """
        Transforme un tableau python en structure de données de maillage
    """
    for tetra in tetralst:
        newtetra=ls.bintetrahedre()
        newtetra.sommets[0]=tetra[0][0]
        newtetra.sommets[1]=tetra[0][1]
        newtetra.sommets[2]=tetra[0][2]
        newtetra.idVolume=tetra[1]
        for idface in range(0,4):
            face=tetra[2][idface]
            newface=newtetra.tetrafaces[idface]
            newface.marker=face[0]
            newface.neighboor=face[1]
            newface.sommets[0]=face[2][0]
            newface.sommets[1]=face[2][1]
            newface.sommets[2]=face[2][2]
        maillage.tetrahedres.append(newtetra)
        
#Définitions des sommets des tétraèdres
m_sommets=  [   [5.0, 0.0, 0.0],
                [0.0, 0.0, 0.0],
                [0.0, 5.0, 0.0],
                [5.0, 5.0, 0.0],
                [0.0, 5.0, 5.0],
                [5.0, 5.0, 5.0],
                [0.0, 0.0, 5.0],
                [5.0, 0.0, 5.0],
                [0.0, 2.5, 2.5],
                [2.5, 0.0, 2.5]
            ]
#Définition des tétrahèdres
#   _______________Sommets du tétraèdre__    _Encombrement_    __4 faces du tétraèdre_______________________________________
# [ [ sommetA, sommetB, sommetC, sommetD ] , idVolume        , [ [idfacemodel, idtetravoisin, [ SommetA, SommetB, SommetC]]  , .. ] ]
tetras= [    [[3, 9, 2], 0, [[-1, 11, [9, 0, 2]], [1, -2, [2, 0, 3]], [-1, 2, [3, 0, 9]], [-1, 12, [9, 2, 3]]]],
             [[5, 9, 7], 0, [[-1, 10, [9, 8, 7]], [-1, 9, [7, 8, 5]], [-1, 13, [5, 8, 9]], [-1, 5, [9, 7, 5]]]],
             [[3, 9, 0], 0, [[-1, 5, [9, 5, 0]], [8, -2, [0, 5, 3]], [-1, 13, [3, 5, 9]], [-1, 0, [9, 0, 3]]]],
             [[2, 8, 5], 0, [[-1, 9, [8, 4, 5]], [2, -2, [5, 4, 2]], [4, -2, [2, 4, 8]], [-1, 4, [8, 5, 2]]]],
             [[3, 8, 5], 0, [[-1, 3, [8, 2, 5]], [3, -2, [5, 2, 3]], [-1, 12, [3, 2, 8]], [-1, 13, [8, 5, 3]]]],
             [[5, 9, 0], 0, [[6, -2, [9, 7, 0]], [9, -2, [0, 7, 5]], [-1, 1, [5, 7, 9]], [-1, 2, [9, 0, 5]]]],
             [[6, 1, 8], 0, [[-1, 7, [1, 9, 8]], [-1, 10, [8, 9, 6]], [7, -2, [6, 9, 1]], [5, -2, [1, 8, 6]]]],
             [[2, 9, 8], 0, [[-1, 6, [9, 1, 8]], [5, -2, [8, 1, 2]], [-1, 11, [2, 1, 9]], [-1, 12, [9, 8, 2]]]],
             [[7, 8, 6], 0, [[4, -2, [8, 4, 6]], [11, -2, [6, 4, 7]], [-1, 9, [7, 4, 8]], [-1, 10, [8, 6, 7]]]],
             [[5, 8, 7], 0, [[-1, 8, [8, 4, 7]], [10, -2, [7, 4, 5]], [-1, 3, [5, 4, 8]], [-1, 1, [8, 7, 5]]]],
             [[7, 9, 6], 0, [[-1, 6, [9, 8, 6]], [-1, 8, [6, 8, 7]], [-1, 1, [7, 8, 9]], [7, -2, [9, 6, 7]]]],
             [[2, 9, 1], 0, [[6, -2, [9, 0, 1]], [0, -2, [1, 0, 2]], [-1, 0, [2, 0, 9]], [-1, 7, [9, 1, 2]]]],
             [[9, 3, 2], 0, [[-1, 4, [3, 8, 2]], [-1, 7, [2, 8, 9]], [-1, 13, [9, 8, 3]], [-1, 0, [3, 2, 9]]]],
             [[3, 9, 5], 0, [[-1, 1, [9, 8, 5]], [-1, 4, [5, 8, 3]], [-1, 12, [3, 8, 9]], [-1, 2, [9, 5, 3]]]]
        ]

def CreerMaillage(filepath):
    """
        Création du fichier de maillage
    """
    maillage=ls.trimeshmodel()
    #Ajout des sommets
    push_mesh_nodelist(maillage,m_sommets)
    #Ajout des tétraèdres
    push_tetraedres(maillage,tetras)

    #sauvegarde du maillage
    ls.CMBIN().SaveMesh(filepath,maillage)
