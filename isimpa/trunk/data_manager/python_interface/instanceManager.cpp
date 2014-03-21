#include "instanceManager.hpp"
#include "last_cpp_include.hpp"


InstanceManager::t_HashObjectArray InstanceManager::HashObjectArray;



void InstanceManager::AppendReference(const OBJECT_REF_TYPE& refType, const int& index, VALHASHEL ref)
{
	HashObjectArray.ptr_hash[refType][index]=ref;
}


void InstanceManager::RemoveReference(const OBJECT_REF_TYPE& refType, const int& index)
{
	//if(!HashObjectArray.ptr_hash[refType].empty())
	HashObjectArray.ptr_hash[refType].erase(index);
}

bool InstanceManager::GetReference(const OBJECT_REF_TYPE& refType, const int& index,VALHASHEL* pt_ref)
{
	t_HashPspsObject::iterator it=HashObjectArray.ptr_hash[refType].find(index);
	if( it != HashObjectArray.ptr_hash[refType].end())
	{
		*pt_ref=it->second;
		return true;
	}else{
		return false;
	}
}

size_t InstanceManager::GetElementCount()
{
	size_t counter=0;
	for(int typeEl=0;typeEl<OBJECT_REF_TYPE_SIZE;typeEl++)
	{
		counter+=HashObjectArray.ptr_hash[typeEl].size();
	}
	return counter;
}