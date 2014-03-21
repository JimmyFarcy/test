
#include "../coreString.h"
#include <vector>

#ifndef __CXML_PARSER__
#define __CXML_PARSER__

/**
 * @file cxml.h
 * @brief Implémentation de la classe de lecture-ecriture de fichiers xml
 */

typedef CoreString xString;

/**
 * Espace de nom propre à l'algorithme interne de CXml
 */
namespace BasicXmlProcess
{
	/** @brief basicxmlnode: simple xml node memory representation */
	struct basicxmlnode
	{
	  char * tag;						/*!< always non-NULL */
	  char * text;						/*!< body + all whitespace, always non-NULL */
	  char * * attrs;					/*!< array of strings, NULL marks end */
	  char * * values;					/*!< array of strings, NULL marks end */
	  struct basicxmlnode * * children; /*!< similar */
	  int * childreni;					/*!< children positions in text */
	};
}

/**
 * @brief Classe représentant une propriété d'un noeud du fichier XML
 * @see CXml
 * @see CXmlNode
 **/
class CXmlNodeProperty
{
public:
	struct t_PropData
	{
		xString propName;
		xString propValue;
	};
public:

	CXmlNodeProperty();
	/**
	 * Constructeur par copie
	 * @param propSrc Valeurs de la propriété
	 */
	CXmlNodeProperty(CXmlNodeProperty* propSrc);
	/**
	 * Constructeur d'initialisation
	 * @param name Nom
	 * @param value Valeur
	 */
	CXmlNodeProperty(xString name,xString value);
	/**
	 * Retourne les données de la propriétés
	 */
	void GetData(t_PropData& data);

	/**
	 * Obtenir le nom de la propriété
	 * @return Nom de la propriété
	 */
	xString GetName() const;
	/**
	 * Obtenir la valeur de la propriété
	 * @return Valeur de la propriété
	 */
	xString GetValue() const;

	~CXmlNodeProperty();

private:
	t_PropData propData;
};




class CXml;

/**
 * @brief Classe représentant un noeud du fichier XML
 * @see CXml
 **/
class CXmlNode
{
public:
	/**
	 * Constructeur d'un noeud
	 * @param _parent Noeud parent
	 * @param rowData Données du noeud  (charge les données fils )
	 */
	CXmlNode(CXmlNode* _parent=NULL , BasicXmlProcess::basicxmlnode* rowData = NULL);
	~CXmlNode();
	/**
	 * Ajouter un fils à cet élément
	 * @param newChildren Adresse du fils
	 */
	void AddChildren( CXmlNode* newChildren );
	/**
	 * Affecter le noeud en parametre comme parent de ce noeud, met à jours les fils de l'ancien et du nouveau parent
	 * @param newParent Adresse du parent de this
	 */
	void ReParentNode( CXmlNode* newParent );

	/**
	 *  Retourne l'itérateur correspondant au premier élément fils
	 *
	 * @return Objet permettant de parcourir les noeuds fils un par un.
	 */
	const std::vector<CXmlNode*>::iterator GetFirstChild();


	/**
	 *  Retourne l'itérateur correspondant au dernier élément fils
	 *
	 * @return Objet permettant de parcourir les noeuds fils un par un.
	 */
	const std::vector<CXmlNode*>::iterator GetLastChild();

	/**
	 * Retourne le premier enfant ayant le nom passé en paramètre
	 * @param name Nom du noeud XML
	 * @return Pointeur vers le noeud ayant ce nom si trouvé. NULL si aucun fils n'a ce nom.
	 */

	CXmlNode* GetChild(xString name);
	/**
	 * A partir du nom de la propriété, retourne la valeur
	 *
	 */
	xString GetProperty(xString name) const;
	/**
	 * Indique si la propriété existe
	 *
	 */
	bool IsPropertyExist(xString name);

	/**
	 * Ajoute ou met à jour une propriété
	 * @param name Nom
	 * @param value Valeur
	 **/

	xString GetName() const;

	void AddProperty( xString name, xString value );

	/**
	 * Supprime une propriété
	 * @param name Nom de la propriété
	 * @return Vrai si une propriété a été supprimée, faux si la propriété n'existe pas
	 */
	bool DeleteProperty( xString name );

	/**
	 * Trie les noeuds fils dans l'ordre de la propriété passé en paramètre
	 * @param nameProperty Nom de la propriété (la valeur correspondante doit être toujours un entier)
	 * @param ascOrder A vrai le trie se fait par ordre croissant
	 */
	void OrderChildsByProperty( xString nameProperty, bool ascOrder=true);

	/**
	 * Cet méthode définit l'opérateur de comparaison (inférieur,supérieur) avec un autre noeud.
	 * @param _rEl Noeud à droite de l'opérateur
	 * @return Vrai si ce noeud est inférieur
	 **/
	bool operator>(const CXmlNode &_rEl);
	/**
	 * Cet méthode définit l'opérateur de comparaison (inférieur,supérieur) avec un autre noeud.
	 * @param _rEl Noeud à droite de l'opérateur
	 * @return Vrai si ce noeud est inférieur
	 **/
	bool operator<(const CXmlNode &_rEl);
	/**
	 * Retourne le nombre de noeuds enfants
	 * @return Nombre de noeuds enfants
	 */
	uentier CountChildrens();
	xString propertyNameSorting; /*!< Cette chaine de charactère désigne la propriété servant à trier les noeuds fils */
private:
	struct t_nodeData
	{
		xString nodeName;
		std::vector<CXmlNodeProperty> nodeProperties;
		std::vector<CXmlNode*> childrens;
		CXmlNode* parent;
	}nodeData;

	int GetIndiceProp( xString name ) const;
};

/**
 * @brief Classe de lecture et d'écriture de fichier XML
 *
 * Cette classe est une classe intermediaire avec des fonctions C de gestion de fichier XML basique.
 * @see http://www.danoneverythingelse.com/articles/Softwarebxmlnode.html
 */
class CXml
{
public:
	CXml( xString path );
	CXml ( );
	~CXml();
	CXmlNode* GetRoot();
private:
	CXmlNode* rootNode;
	void _ClearDocument();

};


#endif
