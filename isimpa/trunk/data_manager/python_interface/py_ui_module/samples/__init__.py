# -*- coding: cp1252 -*-
from __future__ import print_function #compatibilité python 3.0
import uictrl
import sys

class manager:
    """
        This class make the user able to enable or disable a group of emitters with one click only
    """
    def __init__(self):
        """
            Constructor. Register the two new menu functions
        """
        self.enable_grp_sourcesid=uictrl.application.register_event(self.enable_grp_sources)
        self.disable_grp_sourcesid=uictrl.application.register_event(self.disable_grp_sources)
    def set_grp_src_activation(self,idgrp,newstate):
        grpsrc=uictrl.element(idgrp)
        all_property=grpsrc.getallelementbytype(uictrl.element_type.ELEMENT_TYPE_SCENE_SOURCES_SOURCE_PROPRIETES)
        for prop in all_property:
            uictrl.element(prop).updateboolconfig("enable",newstate)
    def enable_grp_sources(self,idgrp):
        """
            Called by user interface when the user click on the enable menu item
        """
        self.set_grp_src_activation(idgrp,True)
    def disable_grp_sources(self,idgrp):
        """
            Called by user interface when the user click on the disable menu item
        """
        self.set_grp_src_activation(idgrp,False)
    def getmenu(self,typeel,idel,menu):
        """
            Called by the user interface
            The list menu structure contains the current implemented functions.
        """
        submenu=[(uictrl._("Enable"),self.enable_grp_sourcesid),(uictrl._("Disable"),self.disable_grp_sourcesid)]
        menu.insert(2,(uictrl._("All emitters"),submenu))
        menu.insert(2,())
        return True
#register the menu manager class instance.
uictrl.application.register_menu_manager(uictrl.element_type.ELEMENT_TYPE_SCENE_SOURCES, manager())

