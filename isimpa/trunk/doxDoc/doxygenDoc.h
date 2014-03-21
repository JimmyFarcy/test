/*! \page doxygentuto Génération automatique de la documentation
 * 
 * Les commentaires dans les fichiers d'entêtes du code source de cette application comporte des commentaires un peu spéciaux.
 *
 * L'utilité de ce formalisme est la génération automatique de la documentation développeur.
 *
 * Cette génération automatique est produite par la suite Doxygen. A partir du moment où vous respectez ce formalisme, une documentation à jour est produite en pdf ou en html trés 
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 *
 * \section whentodox Quand documenter les fichiers sources ?
 *
 * Un bloc de commentaire doit être créé :
 *	- À chaque création d'@ref howtodoxfile "un nouveau fichier d'entête";
 *	- À chaque création d'@ref howtodoxclass "une classe";
 *	- À chaque création d'@ref howtodoxmethod "une méthode publique";
 *	- À chaque création d'@ref howtodoxstruct "une structure publique";
 *	- À chaque création d'@ref howtodoxvar "une variable publique".
 *
 * La documentation des méthodes publiques permet d'utiliser toutes les classes à disposition rapidement sans avoir besoin de lire le code source.
 *
 * \dontinclude demos/demo_doxygen.h
 * 
 * \section howtodoxfile Comment documenter un nouveau fichier d'entête ?
 * 
 * Après les commandes d'inclusions de fichiers externes, le bloc de commentaires suivant doit être créé :
 *
 * \skip customdlg
 * \until ***
 *
 * Il y a deux commandes dans ce bloc dont un lien dynamique :
 *	- La commande "\file Nom du fichier" indique que ce bloc désigne la documentation du fichier;
 *	- La commande "@brief" Indique que le texte suivant correspond à la description brève du fichier (jusqu'à un double saut de ligne);
 *	- Le nom de la classe wxCustomEntryDialog est automatiquement lié si l'élément existe (classes, fonctions, méthodes, variables, fichiers or URL).
 * 
 *
 * La dernière ligne correspond aux commentaires de détail du fichier. 
 *
 * @note À la fin du bloc de commentaire seul *\/ est normalement nécessaire. Pour l'établissement de cette page de documentation que vous êtes en train de lire il a été nécessaire de terminer le bloc de commentaire par ***\/(contrainte de Doxygen pour la recherche de la fin du bloc de référence du code source).
 *
 * \section howtodoxclass Comment documenter une classe ?
 *
 * Juste avant la déclaration de la classe, un bloc de commentaires doit être inséré :
 *
 * \skip **
 * \until  ***
 * 
 * Deux nouvelles commandes sont visibles dans ce bloc :
 *	- La commande qui permet de créer une liste est simplement le caractère - suivi d'un espace.
 *	- La commande \@see permet de déclarer un bloc "Voir également:" dans le bloc de commentaire actuel.
 *
 * \section howtodoxmethod Comment documenter une méthode ?
 *
 * Chaque méthode publique doit être documentée afin de décrire sa fonction au sein de la classe, ses paramètres et les données de sorties.
 * 
 * \skip ** Permet
 * \until  ;
 * 
 * Deux nouvelles commandes sont visibles dans ce bloc :
 *	- La commande "@param variable" permet de documenter un des paramètres. [in] correspond aux paramètres en entrée de la méthode. [out] correspond aux paramètres en sortie.[in-out] Dans les deux sens.
 *	- La commande "@return" permet de créer un bloc de commentaire sur la valeur de retour.
 *
 *
 * \section howtodoxstruct Comment documenter une structure ?
 *
 * La documentation des structures permet de connaître à quoi correspond chaque élément de la structure ainsi que les données attendues.
 *
 * \skip un champ
 * \until }
 *
 *
 * \section howtodoxvar Comment documenter une variable ?
 * 
 * \skipline isModified
 * 
 * Les trois premiers caractères permettent de spécifier un bloc de commentaires qui porte sur une déclaration déjà effectuée sur la même ligne.
 *
 * \section moreondox Autres commandes
 *
 * Il y a beaucoup d'autres commandes possibles. Se référer à la documentation de Doxygen "Special Commands".
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual.html
 *
 * \section fulldox Fichier de démonstration complet
 * 
 * \include demos/demo_doxygen.h
 */