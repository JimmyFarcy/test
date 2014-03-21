# -*- coding: cp1252 -*-

_=uictrl._ #Make an alias of the translation function

class mdf(uictrl.element):
    """
      Diffusion model calculation core.
    """
    def __init__(self,idel):
        uictrl.element.__init__(self,idel)
        
        if not self.hasproperty("exeName"): #Test if this is a new project initialisation
            #If this is a new project then we add properties
            #Add tetgen parameters
            self.appendfilsbytype(uictrl.element_type.ELEMENT_TYPE_CORE_CORE_CONFMAILLAGE)
            #Add frequencies selection
            self.appendfilsbytype(uictrl.element_type.ELEMENT_TYPE_CORE_CORE_BFREQSELECTION)
            #Add configuration core
            coreconf=uictrl.element(self.appendfilsbytype(uictrl.element_type.ELEMENT_TYPE_CORE_CORE_CONFIG))
            #Append hidden config, used by I-SIMPA to find the core files and binaries
            uictrl.element(self.appendpropertytext("modelName","","mesh.cbin",True,True)).hide()
            uictrl.element(self.appendpropertytext("tetrameshFileName","","tetramesh.mbin",True,True)).hide()
            uictrl.element(self.appendpropertytext("exeName","","md.py")).hide()
            uictrl.element(self.appendpropertytext("corePath","","md\\")).hide()
            
            #User options
            coreconf.appendpropertylist("solver_mode","Calculation mode",[["Time","Static"],[0,1]],0,False,1,True)
            coreconf.appendpropertybool("with_direct_sound","Use direct sound",True,True)
            _("Calculation mode")
            _("Use direct sound")
            _("Time")
            _("Static")
            
            
        else:
            pass #Here in case of loading an existing project
    def gettreelabel(self):
        """
            Return label
        """
        return "Mdf"
    def geticonid(self,state_open):
        """
            Return tree icon Id
        """
        if state_open:
            return uictrl.graph.GRAPH_FOLDER_OPEN
        else:
            return uictrl.graph.GRAPH_FOLDER
    def modified(self,idelmodified):
        #In case of sub element modification this func is call by ui
        #We disable the time dependant parameters in case of static solver mode
        if uictrl.element(idelmodified).getinfos()["name"]=="solver_mode":
            elconf=uictrl.element(self.getelementbytype(uictrl.element_type.ELEMENT_TYPE_CORE_CORE_CONFIG))
            is_temporal=(elconf.getlistconfig("solver_mode")==0)
            elconf.setreadonlyconfig("duree_simulation",not is_temporal)
            elconf.setreadonlyconfig("pasdetemps",not is_temporal)
        uictrl.element.modified(self,idelmodified)
