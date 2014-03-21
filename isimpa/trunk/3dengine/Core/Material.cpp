#include "GL/opengl_inc.h"
#include "Material.h"
#include "manager/smart_ptr.h"
#include "last_cpp_include.hpp"

extern CTexture *textures;

unsigned long CMaterial::Create(char *name,const vec4 &colorA, vec4 &colorD, vec4 &colorS) 
{
	long id = this->GetId(name);
	if(id < this->_pMaterial.size()) return id;

	SMaterial mTmp;
	mTmp.Name = name;
	mTmp.ColorA = colorA;
	mTmp.ColorD = colorD;
	mTmp.ColorS = colorS;
	mTmp.idTex = -1;
	this->_pMaterial.push_back(mTmp);
	return id;
}

unsigned long CMaterial::Create(const SMaterial *strm) 
{
	long id = this->GetId(strm->Name.c_str());
	if(id < this->_pMaterial.size()) return id;
	this->_pMaterial.push_back(*strm);
	return id;
}

unsigned long CMaterial::GetId(const std::string& name) 
{	

	long i=0;
	for(i=0; i < this->_pMaterial.size(); i++)
		if(!this->_pMaterial[i].Name.compare(name))
			break;
	return i;
}

unsigned long CMaterial::SetColor(unsigned long m,float forcetransparency) 
{	
	if(m >= this->_pMaterial.size()) m=0;

	if(this->_pMaterial.size()==0)
		return 0;

	vec4 couleur_ambient(this->_pMaterial[m].ColorA);
	vec4 couleur_diffuse(this->_pMaterial[m].ColorD);
	vec4 couleur_specular(this->_pMaterial[m].ColorS);
	

	if(forcetransparency>-1) //si l'on force une transparence on change la valeur alpha de la matière
	{
		couleur_ambient.a=forcetransparency;
		couleur_diffuse.a=forcetransparency;
		couleur_specular.a=forcetransparency;
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, couleur_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, couleur_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,couleur_specular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, this->_pMaterial[m].Shininess);
	if(this->_pMaterial[m].Transparency > 0.0f || forcetransparency>-1) 
		glEnable(GL_BLEND);
	else glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	return m;
}

unsigned long CMaterial::SetMat(unsigned long m) 
{	
	if(m >= this->_pMaterial.size()) return 0;
	if(this->_pMaterial[m].Transparency > 0.0f) 
		glEnable(GL_BLEND);
	else glDisable(GL_BLEND);
	if(this->_pMaterial[m].idTex != -1)
	{
		textures->SetTex(this->_pMaterial[m].idTex);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vec4(1.,1.,1.,1.));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vec4(1.,1.,1.,1.));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,vec4(1.,1.,1.,1.));
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 1.);
	}else{
		glDisable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->_pMaterial[m].ColorA);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->_pMaterial[m].ColorD);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,this->_pMaterial[m].ColorS);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, this->_pMaterial[m].Shininess);
	}
	return m;
}

bool CMaterial::HasTexture(unsigned long m)
{
	if(m >= this->_pMaterial.size())
		return false;
	if(this->_pMaterial[m].idTex != -1)
		return true;
	else
		return false;
}

long CMaterial::GetTextureId(unsigned long m)
{
	if(m >= this->_pMaterial.size())
		return -1;
	return this->_pMaterial[m].idTex;
}