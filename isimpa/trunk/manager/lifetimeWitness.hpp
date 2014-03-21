#include "first_header_include.hpp"

#include "manager/smart_ptr.h"
/*
 * @file lifetimeWitness.hpp
 * Cette classe permet de lier la fin d'un objet à une liste d'événements.
 *
 */
#ifndef __LIFETIME_WITNESS__
#define __LIFETIME_WITNESS__

struct t_outsideOperator
{
	virtual ~t_outsideOperator(){}
};

struct t_baseEvtCatcher
{
	virtual void OnModified(const int& elid){}
	virtual void OnNewChildElement(const int& childType,const int& parentid,const int& childid){}
	virtual ~t_baseEvtCatcher(){}
};
typedef smart_ptr<t_outsideOperator> LifeTimeWitness;
typedef smart_ptr<t_baseEvtCatcher> EventCatcher;

#endif