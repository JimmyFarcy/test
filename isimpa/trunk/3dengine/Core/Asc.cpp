﻿#include "Asc.h"
#include "last_cpp_include.hpp"

namespace formatASC
{

	CAsc::CAsc()
	{



	}

void CAsc::ExportASC(vec4 UnitizeValue,std::vector<SGroup3D> &pModel, std::vector<vec3> &Vertices, const char *mfilename,long nbVertices, long nbFaces)
{
  FILE *outfile;

  outfile = fopen(mfilename, "w");
  if (outfile == (FILE *) NULL) {
    return;
  }

  fprintf(outfile, "\n# Liste de points\n");
  fprintf(outfile, "Vertices\n");
  fprintf(outfile, "%ld\n", Vertices.size());

  for(int v=0; v < Vertices.size() ;v++)
  {
	vec3 realCoords=coordsOperation::GlCoordsToCommonCoords(UnitizeValue,Vertices[v]);
	fprintf(outfile, "%.17g %.17g %.17g\n",
	realCoords.x, //On remet les points à leur etat d'origine est l'on exporte
	realCoords.y,
	realCoords.z);
  }
  fprintf(outfile, "\n# Faces\n");
  fprintf(outfile, "Triangles\n");
  fprintf(outfile, "%ld\n", nbFaces);

  // To loop over the set of faces, loop over all tetrahedra, and look at
  //   the four faces of each tetrahedron. If there isn't another tetrahedron
  //   adjacent to the face, operate on the face.  If there is another adj-
  //   acent tetrahedron, operate on the face only if the current tetrahedron
  //   has a smaller pointer than its neighbor.  This way, each face is
  //   considered only once.
  for(int g=0; g < pModel.size() ;g++)
  {
		for(long j=0; j < pModel[g].pFaces.size() ;j++)
		{
			fprintf(outfile, "%ld %ld  %ld\n",
					pModel[g].pFaces[j].Vertices.a,
					pModel[g].pFaces[j].Vertices.b,
					pModel[g].pFaces[j].Vertices.c);
		}
  }

  fprintf(outfile, "\nEnd\n");
  fclose(outfile);
}


void CAsc::ExportTetraASC(vec4 UnitizeValue,triangleFace *tabVertexMaillage, const char *mfilename, long nbFaces)
{
	if(nbFaces<4)
		return;
	FILE *outfile;

	outfile = fopen(mfilename, "w");
	if (outfile == (FILE *) NULL) {
	return;
	}
	long nbtetrah=nbFaces/4;
	vec4 *tetratab = new vec4[nbtetrah]; 
	vec3 *facetab = new vec3[nbFaces]; 

	long anstetranum=0;
	long verticenum=0;
	//Affichage vertices
	/*
	Tri-mesh, Vertices: 8     Faces: 12
	Vertex list:*/
	fprintf(outfile, "Tri-mesh, Vertices: %i     Faces: %i     Tetrahedre: %i\n",nbtetrah*4,nbFaces,nbtetrah);
	for(long f=0; f < nbFaces ;f++)
	{
		long tetranum=f/4+1;
		if(tetranum!=anstetranum)
		{
			//Nouveau tetrahedre
			tetratab[tetranum-1].set(verticenum,verticenum+1,verticenum+2,verticenum+3);
			//4 faces du tetrahedre
			facetab[f].set(verticenum,verticenum+1,verticenum+2);
			facetab[f+1].set(verticenum,verticenum+1,verticenum+3);
			facetab[f+2].set(verticenum,verticenum+2,verticenum+3);
			facetab[f+3].set(verticenum+1,verticenum+2,verticenum+3);
			//4 vertex du tetrahedre
			for(int i=0;i<4;i++)
			{
				vec3 Vertices;
				if(i==0)
					Vertices=tabVertexMaillage[f].a;
				if(i==1)
					Vertices=tabVertexMaillage[f].b;
				if(i==2)
					Vertices=tabVertexMaillage[f].c;
				if(i==3)
					Vertices=tabVertexMaillage[f+1].b;
				fprintf(outfile, "Vertex %i: X: %.17g     Y: %.17g     Z: %.17g\n",verticenum,
					(Vertices.x/UnitizeValue.w)+UnitizeValue.x, //On remet les points à leur etat d'origine
					(Vertices.y/UnitizeValue.w)+UnitizeValue.y,
					(Vertices.z/UnitizeValue.w)+UnitizeValue.z);
				verticenum++;
			}
		}
		anstetranum=tetranum;
	}

	fprintf(outfile, "Face list:\n");
	for(long f=0; f < nbFaces ;f++)
	{
		fprintf(outfile, "Face %i: A: %i     B: %i     C: %i\n",f,
					(int)facetab[f].x,
					(int)facetab[f].y,
					(int)facetab[f].z);
	}
	fprintf(outfile, "Tetrahedre list:\n");
	for(long f=0; f < nbtetrah ;f++)
	{
		fprintf(outfile, "Tetrahedre %i: A: %i     B: %i     C: %i     D: %i\n",f,
					(int)tetratab[f].x,
					(int)tetratab[f].y,
					(int)tetratab[f].z,
					(int)tetratab[f].w);
	}
	fclose(outfile);
	delete[] tetratab;
	delete[] facetab;
}

} //fin namespace