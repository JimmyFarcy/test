#include <boost/smart_ptr.hpp>
#include "mathlib.h"

typedef unsigned int cell_id_t;


template<class cellData_t>
class Cell
{
   private :
   cell_id_t Size;
   boost::shared_ptr<Cell> nextCell;
   cellData_t cellData;
   public :
	   Cell() : cellData(0),Size(0) {}
   Cell(const cell_id_t& _DomainSize ) : cellData(_DomainSize),Size(_DomainSize) {};
   /**
    * Utilis� via la m�thode at, si une cellule doit etre cr��
	*/
   void SetCellSize( const cell_id_t& cellSize) { this->Size = cellSize; }
   void SetNextCell( boost::shared_ptr<Cell>& _nextCell)
   {
		nextCell=_nextCell;
   }

   void Count( unsigned int& cnt)
   {
		cellData.Count(cnt);
		if(nextCell.get())
		{
			(*nextCell).Count(cnt);
		}
   }
   /**
    * Acceder � cellData
	*/
   const cellData_t& operator [](const cell_id_t& id) const
   {
	   cell_id_t curId=id;
	   Cell* curCell=this;
	   while(curCell)
	   {
		   if(curId<curCell->Size)
		   {
			   return curCell->cellData;
		   }else{
				curId=curId-curCell->Size;
				curCell=curCell->nextCell.get();
		   }
	   }
	#ifdef _DEBUG
	throw "Cell access out of array limit !";
	#endif
   }
   /**
    * Sp�cifier des donn�es, cr�� le noeud avec cet indice
	* Todo supprimer mod�le iteratif
	*/
   cellData_t& at( const cell_id_t& id, const cell_id_t& domainSize)
   {
	   
	   cell_id_t curId=id;
	   Cell* curCell=this;
	   while(curCell)
	   {
		   if(curCell->Size==1 && curId==0) //Retourner les donn�es courantes
		   {
			   return curCell->cellData;
		   }else if(curId<curCell->Size){	//Subdiviser cette cellule en 2 ou 3 cellules
			   if(curId==0) //Subdiviser cette cellule en 2 cellules, retourner la premi�re
			   {
				  boost::shared_ptr<Cell> NextNextCell(curCell->nextCell);
				  curCell->nextCell=boost::shared_ptr<Cell>(new Cell(domainSize));
				  (*curCell->nextCell).SetCellSize(curCell->Size-1);
				  curCell->SetCellSize(1);
				  (*curCell->nextCell).SetNextCell(NextNextCell);
				  return curCell->cellData;
			   }else if(curId==curCell->Size-1){//Subdiviser cette cellule en 2 cellules, retourner la deuxi�me
				  boost::shared_ptr<Cell> NextNextCell(curCell->nextCell);
				  curCell->nextCell=boost::shared_ptr<Cell>(new Cell(domainSize));
				  (*curCell->nextCell).SetCellSize(1);
				  curCell->SetCellSize(curCell->Size-1);
				  (*curCell->nextCell).SetNextCell(NextNextCell);
				  return (*curCell->nextCell).cellData;
			   }else{ //Subdiviser cette cellule en 3 cellules, retourner celle du milieu
				  boost::shared_ptr<Cell> NextNextNextCell(curCell->nextCell);
				  boost::shared_ptr<Cell> NextNextCell(new Cell(domainSize));
				  curCell->nextCell=boost::shared_ptr<Cell>(new Cell(domainSize));
				  (*curCell->nextCell).SetCellSize(1);
				  (*NextNextCell).SetCellSize((curCell->Size-1)-curId);
				  curCell->SetCellSize(curId);
				  (*curCell->nextCell).SetNextCell(NextNextCell);
				  (*NextNextCell).SetNextCell(NextNextNextCell);
				  return (*curCell->nextCell).cellData;			  
			   }
		   }else{				//Continuer vers la prochaine cellule
				curId=curId-curCell->Size;
				curCell=curCell->nextCell.get();
		   }		
	 }
	#ifdef _DEBUG
	throw "Cell access out of array limit !";
	#endif
   }
};


template<class cellData_t>
class CellArray
{
   private :
   cell_id_t Size;
   boost::shared_array<cellData_t> cellData;
   public :
   CellArray() : Size(0) {};
   CellArray(const cell_id_t& _DomainSize ) : cellData(boost::shared_array<cellData_t>(new cellData_t[_DomainSize])),Size(_DomainSize)
   {
		for(cell_id_t cellId=0;cellId<Size;cellId++)
			cellData[cellId].SetCellSize(_DomainSize);
   }
   /**
    * Utilis� via la m�thode at, si une cellule doit etre cr��
	*/
   void SetCellSize( const cell_id_t& cellSize) {
	   this->Size = cellSize;
	   cellData=boost::shared_array<cellData_t>(new cellData_t[this->Size]);
		for(cell_id_t cellId=0;cellId<Size;cellId++)
			cellData[cellId].SetCellSize(this->Size);
   }

	void Count( unsigned int& cnt)
	{
		for(cell_id_t cellId=0;cellId<Size;cellId++)
			cellData[cellId].Count(cnt);
	}
   /**
    * Acceder � cellData
	*/
   const cellData_t& operator [](const cell_id_t& id) const
   {
		return cellData[id];
   }
   /**
    * Sp�cifier des donn�es, cr�� le noeud avec cet indice
	* Todo supprimer mod�le iteratif
	*/
   cellData_t& at( const cell_id_t& id, const cell_id_t& domainSize)
   {
	   	#ifdef _DEBUG
	    if(id>=Size)
			throw "Cell access out of array limit !";
		#endif
		return cellData[id];
   }
};
class CellData
{
 public:
	 CellData(  const cell_id_t& domainSize ) {};  //Ce param�tre n'est pas utilis�
	 vec3 dotValue;
	 void Count( unsigned int& cnt)
	 {
		cnt++;
	 }
};
//operator [] retourne le cell data de ce noeud si  id est inf�rieur � Size, sinon il retourne  (*nextCell)[id-Size] (�viter la r�cursivit�)

typedef Cell<CellData> zcell_t;
typedef CellArray<zcell_t> ycell_t;
typedef CellArray<ycell_t> xcell_t;

inline CellData& FindOrCreateCell(xcell_t& cellArray,const cell_id_t& domainSize, const cell_id_t& x,const cell_id_t& y,const cell_id_t& z)
{
	return cellArray.at(x,domainSize).at(y,domainSize).at(z,domainSize);
}


inline CellData& FindOrCreateCell(xcell_t& cellArray,const cell_id_t& domainSize, const ivec3& position)
{
	return cellArray.at(position.x,domainSize).at(position.y,domainSize).at(position.z,domainSize);
}
