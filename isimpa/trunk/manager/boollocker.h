#ifndef __BOOL_LOCKER__
#define __BOOL_LOCKER__
/**
 * Permet de remettre en l'état un booleen meme en cas d'exception
 */
class BoolLocker
{
public:
	BoolLocker(bool* _marker,bool initialState)
		:marker(_marker),stateBeforeLock(*_marker)
	{
		*marker=initialState;
	}
	~BoolLocker()
	{
		Release();		
	}
	void Release()
	{
		if(marker)
		{
			*marker=stateBeforeLock;
			marker=NULL;
		}
	}
private:
	bool* marker;
	bool stateBeforeLock;
};

#endif