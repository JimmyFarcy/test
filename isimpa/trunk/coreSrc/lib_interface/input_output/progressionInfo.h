#ifndef __PROGINFO_
#define __PROGINFO_
#include <iostream>
#include <math.h>

/**
 * @file progressionInfo.h
 * @brief Gestionnaire d'affichage de progression du calcul compatible avec le multithreading (à condition de ne pas détruire deux objets en même temps)
 */


/**
 * Représente une opération de calcul
 */
class progressOperation
{
public:
	/**
	 * Constructeur
	 */
	progressOperation(progressOperation* parentOperation,unsigned int sonEstimation=1)
		:parent(parentOperation),
		sizeOf(0)
		,sizeOfEstimation(sonEstimation)
	{

	}

	~progressOperation()
	{
		if(parent)
		{
			parent->PushProgression(1-(sizeOf/sizeOfEstimation));
		}
	}

	void GetState(float* thisLvlProg)
	{
		*thisLvlProg=sizeOf/sizeOfEstimation;
	}

	void Next()
	{
		PushProgression(1.f);
	}
protected:
	//friend class progressOperation;

	/**
	 *  Un des fils a changé d'état incProg constitue la différence entre la dernière mise à jour de sa progression et sa nouvelle progression
	 * @param incProg ]0;1]
	 */
	void PushProgression(float incProg)
	{
		if(sizeOf+incProg<=sizeOfEstimation)
		{
			if(parent && sizeOf>0)
				parent->PushProgression(-(sizeOf/sizeOfEstimation));
			sizeOf+=incProg;
			if(parent)
				parent->PushProgression(sizeOf/sizeOfEstimation);
		}
	}
private:
	progressOperation* parent;
	unsigned int sizeOfEstimation; //Nombre de fils estimé
	float sizeOf;				   //Nombre de fils détruits
};







/**
 * @brief Gestionnaire d'affichage de progression du calcul compatible avec le multithreading
 */
class progressionInfo
{
private:
	progressOperation mainOperation;
	float lastOutputProgression;
public:
	/**
	 * Constructeur
	 * @param firstLevelEstimation Nombre de tache au premier niveau hiérarchique de taches
	 */
	progressionInfo(int firstLevelEstimation)
		:mainOperation(NULL,firstLevelEstimation)
	{
		lastOutputProgression=0;
	}

	virtual ~progressionInfo()
	{
	}
	/**
	 * @return L'operation principale.
	 */
	progressOperation* GetMainOperation()
	{
		return &mainOperation;
	}

	/**
	 * Affiche la progression si celle-ci a changé
	 */
	void OutputCurrentProgression()
	{
		using namespace std;
		float currentProgression;
		mainOperation.GetState(&currentProgression);
		currentProgression*=100;
		if((int)(currentProgression*100)>(int)(lastOutputProgression*100) && currentProgression<100)
		{
			lastOutputProgression=currentProgression;
			DoShowProgression(currentProgression);
		}
	}
	float GetCurrentProgression()
	{
		float currentProgression;
		mainOperation.GetState(&currentProgression);
		currentProgression*=100;
		return currentProgression;
	}

protected:
	virtual void DoShowProgression(float newProg)
	{
		std::cout.precision(4);
		std::cout<<"#"<<newProg<<std::endl;
	}
};


#endif
