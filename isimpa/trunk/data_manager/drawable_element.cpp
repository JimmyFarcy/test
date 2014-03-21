﻿#include "drawable_element.h"
#include <wx/glcanvas.h>
#include <GL/glu.h>
#include "data_manager/appconfig.h"
#include "last_cpp_include.hpp"

E_Drawable::E_Drawable(Element* parent,wxString Nom,ELEMENT_TYPE _type ,wxXmlNode* nodeElement)
	:Element(parent,Nom,_type,nodeElement)
{
	this->SetDrawable();
	ApplicationConfiguration::AppendRefElement(this,ApplicationConfiguration::ELEMENT_REF_TYPE_DRAWABLE);
}
E_Drawable::~E_Drawable()
{
	ApplicationConfiguration::DeleteRefElement(this,ApplicationConfiguration::ELEMENT_REF_TYPE_DRAWABLE);
}
void E_Drawable::DrawItem( vec4 unitizeValue )
{


}
void E_Drawable::PushTriangle(vec3 A,vec3 B,vec3 C)
{
	t_triangle newtriangle={A,B,C};
	this->consistentModel.push_back(newtriangle);
}

void E_Drawable::GetConsistentModel(std::vector<t_triangle>& triangleLst) //Retourne une liste de triangles qui definissent ce modèle à destination du mailleur et du moteur de calcul
{
	triangleLst=consistentModel;
	//for(int i=0;i<consistentModel.size();i++)
	//	triangleLst.push_back(consistentModel[i]);
}
void E_Drawable::Modified(Element* elementUpdated)
{
	//if(!elementUpdated->IsDrawable())
	//	if(this->pere!=NULL)
	//		this->pere->SetDrawable();
	Element::Modified(elementUpdated);
}
void E_Drawable::DrawPoint(vec3 position,vec3 color,float size)
{
	glDisable(GL_BLEND);	
	glDisable(GL_LIGHTING);  
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor4f(color.x/255,color.y/255,color.z/255,1.0);
	glVertex3fv(position);
	glEnd();

}
void E_Drawable::DrawTriangles(vec4 unitizeValue,std::vector<t_el_draw_object> &drawObject)
{
	
}

void E_Drawable::DrawFaces(std::vector<t_triangle>& unconsistentModel,vec4 couleur_ambient,vec4 couleur_diffuse,vec4 couleur_specular)
{
	
	glCullFace(GL_BACK); 
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);	
	glEnable(GL_LIGHTING); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, couleur_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,couleur_specular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 128.f);
	glBegin(GL_TRIANGLES);
	for(int i=0;i<unconsistentModel.size();i++)
	{
		vec3 normFace,vVector1,vVector2;
		Vector(unconsistentModel[i].a, unconsistentModel[i].b,vVector1);      
        Vector(unconsistentModel[i].b, unconsistentModel[i].c,vVector2);     
        Cross(vVector1, vVector2,normFace);
		normFace.normalize();

		glNormal3fv(normFace);
		glVertex3fv(unconsistentModel[i].a);
		glVertex3fv(unconsistentModel[i].b);
		glVertex3fv(unconsistentModel[i].c);
	}
	glEnd();
}

void E_Drawable::BeginLines()
{
	glLineWidth(1);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
}

void E_Drawable::DrawLine(vec3 a,vec3 b,vec4 color)
{
	glColor4fv(color);
	glVertex3fv(a);
	glVertex3fv(b);

}

void E_Drawable::EndLines()
{
  glEnd();
  glEnable(GL_LIGHTING); 
}

void E_Drawable::DrawArrow(vec3 a_arrowStart,vec3 a_arrowTip,vec3 color,float a_width)
{
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);	
	glEnable(GL_LIGHTING); 
	//glColor4f(color.x,color.y,color.z,1.0);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color*.9f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,color*.8f);


	vec3 up(0,1,0);  
	vec3 arrow = a_arrowTip-a_arrowStart;
	arrow.normalize();
	double d = fabs(up.dot(arrow));
	if (d > .9)
	{
		up = vec3(1,0,0);
	}

	LookAt(a_arrowStart,a_arrowTip,up);


	glRotatef(180,1,0,0);

	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();

	double distance = a_arrowTip.distance(a_arrowStart);

	float ARROW_CYLINDER_PORTION=0.75;
	float ARRROW_CONE_PORTION=(1.0 - 0.75);

	// set rendering style
	gluQuadricDrawStyle(quadObj, GLU_FILL);

	// set normal-rendering mode
	gluQuadricNormals(quadObj, GLU_SMOOTH);

	// render a cylinder and a cone
	glRotatef(180,1,0,0);
	gluDisk(quadObj,0,a_width,10,10);
	glRotatef(180,1,0,0);

	gluCylinder(quadObj,a_width,a_width,distance*ARROW_CYLINDER_PORTION,10,10);
	glTranslated(0,0,ARROW_CYLINDER_PORTION*distance);

	glRotatef(180,1,0,0);
	gluDisk(quadObj,0,a_width*2.0,10,10);
	glRotatef(180,1,0,0);

	gluCylinder(quadObj,a_width*2.0,0.0,distance*ARRROW_CONE_PORTION,10,10);

	// delete our quadric object
	gluDeleteQuadric(quadObj);

	glPopMatrix();

}


void E_Drawable::LookAt(const vec3& a_eye, const vec3& a_at, const vec3& a_up)
{

  // Define our look vector (z axis)
  vec3 look = a_at - a_eye;
  look.normalize();

  // Define our new x axis
  vec3 xaxis;
  Cross(look,a_up,xaxis);
  xaxis.normalize();

  // Define our new y axis as the cross of the x and z axes
  vec3 upv;
  Cross(xaxis,look,upv);

  // Turn around the z axis
  look*-1.0;
  
  // Put it all into a GL-friendly matrix
  double dm[16];
  dm[0]  = xaxis.x;
  dm[1]  = xaxis.y;
  dm[2]  = xaxis.z;
  dm[3] = 0.f;
  dm[4]  = upv.x;
  dm[5]  = upv.y;
  dm[6]  = upv.z;
  dm[7] = 0.f;
  dm[8]  = look.x;
  dm[9]  = look.y;
  dm[10] = look.z;
  dm[11] = 0.f;
  dm[12] = a_eye.x;
  dm[13] = a_eye.y;
  dm[14] = a_eye.z;
  dm[15] = 1.f;

  // Push it onto the matrix stack
  glMultMatrixd(dm);

}

void E_Drawable::AddText(wxString label,vec3 position,vec3 color)
{
	t_labelInfo infoT={label,position,color};
	labelInfo.push_back(infoT);
}


bool E_Drawable::GetMaillageVolumeInfos(t_el_vol_infos& drawableElementInformations)
{
	return false;
}