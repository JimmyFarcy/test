# -*- coding: utf-8 -*-
import time
import codecs

endlinearr=[",","/*","="]

cppFile=u"""
//Généré par generate_enum_def.py le datestamp
#include "element_pywrap.hpp"
#include "data_manager/element.h"
#include "data_manager/python_interface/instanceManager.hpp"
#ifdef USE_PYTHON
#include <boost/python/enum.hpp>


using namespace boost::python;

void export_enum()
{
    EvtEnum

    ElTypeEnum

    GraphEnum
}
#endif
"""

doxyhppFile=u"""
//Généré par generate_enum_def.py le datestamp
/**
 * @file enum_doxygen.h
 * \~french Déclaration des énumérations
 * \~english Enum declarations
 */
namespace uictrl
{

 /**
     *  \~french Enumeration des fonctions "built-in" disponibles pour les éléments
     *  \~english Avaible built-in events
     */
    EvtEnum

 /**
     *  \~french Enumeration de tout les types d'élément "built-in" existant
     *  \~english Avaible built-in element types
     */
    ElTypeEnum

 /**
     *  \~french Enumeration des icones déjà chargées
     *  \~english Application tree icons
     */
    GraphEnum

    /**
     * @brief Alias
     */
    struct Element
    {
        typedef element_type ELEMENT_TYPE;
        typedef idevent IDEVENT;
        typedef graph GRAPH;
    };
}

"""

def GetFirstOccurance(line, endlinearr):
    nearest=-1
    for ele in endlinearr:
        addr=line.find(ele)
        if addr!=-1 and (addr<nearest or nearest==-1):
            nearest=addr
    if nearest==-1:
        nearest=len(line)
    return nearest
def GetComment(ligne):
    return ligne[ligne.find("/*"):ligne.rfind("*/")+2]
def GetDoxyDefEvtEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_evt='enum idevent\n\t{\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_evt+='\t\t'+eventline+','+GetComment(line)+'\n'
    enumdef_evt+="\n\t};"
    return enumdef_evt
def GetDoxyDefTypeEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_evt='enum element_type\n\t{\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_evt+='\t\t'+eventline+','+GetComment(line)+'\n'
    enumdef_evt+="\n\t};"
    return enumdef_evt
def GetDoxyDefGraphEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_evt='enum graph\n\t{\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_evt+='\t\t'+eventline+','+GetComment(line)+'\n'
    enumdef_evt+="\n\t};"
    return enumdef_evt




def GetDefEvtEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_evt='enum_<Element::IDEVENT>("idevent")\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_evt+='\t\t.value("'+eventline+'",Element::'+eventline+')\n'
    enumdef_evt+="\t\t;"
    return enumdef_evt
def GetDefTypeEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_type='enum_<Element::ELEMENT_TYPE>("element_type")\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_type+='\t\t.value("'+eventline+'",Element::'+eventline+')\n'
    enumdef_type+="\t\t;"
    return enumdef_type
def GetDefGraphEnum(eventText):
    eventTab=eventText.splitlines()
    enumdef_type='enum_<Element::GRAPH>("graph")\n'
    for line in eventTab:
        eventline=line[:GetFirstOccurance(line, endlinearr)].strip()
        enumdef_type+='\t\t.value("'+eventline+'",Element::'+eventline+')\n'
    enumdef_type+="\t\t;"
    return enumdef_type


fichelement=codecs.open("../../element.h",'r',encoding="utf-8")
stateParsing="seek"
buffEnum=""
for line in fichelement:
    if stateParsing=="seek":
        if line.find("enum ELEMENT_TYPE")!=-1:
            stateParsing="ELEMENT_TYPE"
            buffEnum=""
        elif line.find("enum IDEVENT")!=-1:
            stateParsing="IDEVENT"
            buffEnum=""
        elif line.find("enum GRAPH_STATE")!=-1:
            stateParsing="seek"
            buffEnum=""
        elif line.find("enum GRAPH")!=-1:
            print "graph found"
            stateParsing="GRAPH"
            buffEnum=""
    else:
        if stateParsing=="IDEVENT":
            if line.find("};")!=-1:
                cppFile=cppFile.replace("EvtEnum",GetDefEvtEnum(buffEnum))
                doxyhppFile=doxyhppFile.replace("EvtEnum",GetDoxyDefEvtEnum(buffEnum))
                stateParsing="seek"
            else:
                buffEnum+=line
        elif stateParsing=="ELEMENT_TYPE":
            if line.find("};")!=-1:
                cppFile=cppFile.replace("ElTypeEnum",GetDefTypeEnum(buffEnum))
                doxyhppFile=doxyhppFile.replace("ElTypeEnum",GetDoxyDefTypeEnum(buffEnum))
                stateParsing="seek"
            else:
                buffEnum+=line      
        elif stateParsing=="GRAPH":
            if line.find("};")!=-1:
                cppFile=cppFile.replace("GraphEnum",GetDefGraphEnum(buffEnum))
                doxyhppFile=doxyhppFile.replace("GraphEnum",GetDoxyDefGraphEnum(buffEnum))
                stateParsing="seek"
            else:
                buffEnum+=line         


cppFile=cppFile.replace("datestamp",time.ctime())
doxyfichdest=open("enum_doxygen.h",'w')
fichdest=open("enum_def.cpp",'w')
fichdest.write(cppFile.encode("utf-8"))
doxyfichdest.write(doxyhppFile.encode("utf-8"))
fichdest.close()
doxyfichdest.close()
print "Seeking done"

