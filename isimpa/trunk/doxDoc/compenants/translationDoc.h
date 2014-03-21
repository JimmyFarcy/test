
/*! \page traductionTuto Note sur la gestion de la traduction
 * 
 * Ce logiciel est destiné à être traduit dans plusieurs langues.
 *
 * Le système de traduction utilisé est un des plus commun et est surtout natif à WxWidgets
 *
 * \section addTraduction Traduire un texte
 * Il n'y a qu'une seule opération à faire pour traduire un texte.
 *
 * Voici une chaine non traduite :
 * \dontinclude demos/demo_translation_1.h
 *
 * \skipline MARKERWRONG
 *
 * A chaque fois qu'une chaine de texte sera visible par l'utilisateur il faut l'entourer d'une méthode globale comme ceci :
 *
 * \skipline MARKEROK
 *
 * \section warningtraductionTuto Attention
 * 
 * Le language de base de l'application est en francais. Ensuite il y a un certains nombre de dictionnaires associés.
 *
 * Le dictionnaire francais est là pour corriger les textes de bases.
 * @warning Si le texte de base est modifié alors toutes les traductions ne seront plus effectuées jusqu'à la mise à jour manuel de chaque dictionnaire. Il faut donc uniquement faire les corrections dans le dictionnaire francais !
 *
 *
 * \section specialtraductionTuto Cas spéciaux
 * 
 * Certaines méthodes traduisent elles mêmes les chaines de caractères pour une bonne raison. Dans la plupart des cas cette raison est de ne pas inclure de chaines traduites au sein du fichier de projet.
 * 
 * Voici une liste non exhaustive de ces méthodes :
 *	- @ref Element::Element() "Libellé de l'élément"
 *	- @ref addprop
 *
 * Dans la documentation d'une méthode il est indiqué dans un bloc d'avertissement si un paramètre ne doit pas être traduit au préalable.
 * \section dictionnarytraductionTuto Modifier ou ajouter un dictionnaire
 * L'ajout ou la modification de dictionnaire est simplifié par l'utilisation du logiciel poEdit.
 * @see http://www.poedit.net
 * 
 * Une fois le logiciel installé se placer dans le dossier de langue.Se placer dans /fr/ pour francais.
 *
 * Le fichier internat.po correspond au fichier de configuration ascii qui peut être lu par poEdit.
 *
 * Ouvrez ce fichier avec poEdit.
 *
 * Pour actualiser les chaines de traductions depuis le code source du projet :
 *	- Ouvrez le menu "Catalogue"
 *	- Cliquez sur "Mise à jour depuis les sources"
 *
 * Vous obtenez un rapport sur les modifications et les nouvelles chaines sont visibles dans la liste.
 * 
 * Double-cliquez sur la ligne à modifier et entrez le texte traduit.
 *
 * Enregistrez le fichier. Aprés enregistrement le fichier internat.mo sera créé. C'est la version binaire du fichier de traduction. La seule compréhensible par notre application.
 */