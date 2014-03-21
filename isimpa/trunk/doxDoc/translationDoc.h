/*! \page traductiontuto Note sur la gestion de la traduction
 * 
 * Ce logiciel peut être traduit dans plusieurs langues.
 *
 * Le système de traduction (I18N) utilisé est un des plus communs et est surtout natif à WxWidgets
 *
 * \section addTraduction Ecriture d'un texte à traduire
 * Il n'y a qu'une seule opération à faire pour traduire un texte.
 *
 * Voici une chaîne non traduite :
 * \dontinclude demos/demo_translation_1.h
 *
 * \skipline printf("Message
 *
 * A chaque fois qu'une chaîne de texte sera visible par l'utilisateur il faut l'entourer d'une méthode globale comme ceci :
 *
 * \skipline printf(_("Message
 *
 * \section warningtraductionTuto Attention
 * 
 * Le language de base de l'application est en français. Ensuite il y a un certains nombre de catalogue de traduction associés.
 *
 * Le catalogue de traduction français est là pour corriger les textes en francais codés en dur dans le code c++.
 * @warning Si les textes en francais codés en dur dans le code c++ sont modifié alors ces textes n'auront plus de correspondances avec les catalogues de traduction. Il faut donc uniquement faire les corrections dans le catalogue de traduction français !
 *
 *
 * \section specialtraductionTuto Cas spéciaux
 * 
 * Certaines méthodes vont elles même faire appel aux catalogue de traduction. Les textes en paramètres de ces méthodes ne doivent donc pas être déjà traduit au préalable.
 * 
 * Voici une liste non exhaustive de ces méthodes :
 *	- @ref Element::Element() "Libellé de l'élément"
 *	- @ref addprop
 *
 * Dans la documentation d'une méthode, il est indiqué dans un bloc d'avertissement si cette méthode fera elle même appel au catalogue de traduction.
 *
 * \section dictionnarytraductionTuto Modifier ou ajouter un catalogue de traduction
 * L'ajout ou la modification d'un catalogue de traduction est simplifié par l'utilisation du logiciel poEdit.
 * @see http://www.poedit.net
 * 
 * Une fois le logiciel installé, il faut se placer dans le dossier de langue.Se placer dans /fr/ pour français.
 *
 * Le fichier internat.po correspond au fichier de configuration ascii qui peut être lu par poEdit.
 *
 * Ouvrez ce fichier avec poEdit.
 *
 * Pour actualiser les chaînes de traductions depuis le code source du projet :
 *	- Ouvrez le menu "Catalogue"
 *	- Cliquez sur "Mise à jour depuis les sources"
 *
 * Vous obtenez un rapport sur les modifications et les nouvelles chaînes sont visibles dans la liste.
 * 
 * Double-cliquez sur la ligne à modifier et entrez le texte traduit.
 *
 * Enregistrez le fichier. Après enregistrement le fichier internat.mo sera créé. C'est la version binaire du fichier de traduction. Seul ce fichier est compréhensible par notre application.
 */
