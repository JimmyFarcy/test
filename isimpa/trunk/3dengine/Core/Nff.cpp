#include "Nff.h"
#include "en_numeric.hpp"
#include <stdio.h>
#include "last_cpp_include.hpp"
namespace formatNFF
{

	CNff::CNff()
	{



	}
	///////////////////////////////////////////////////////////////////////////////
	//                                                                           //
	// ExportNFF
	//                                                                           //
	///////////////////////////////////////////////////////////////////////////////
	void CNff::ExportNFF(vec4 UnitizeValue,std::vector<SGroup3D> &pModel, std::vector<vec3> &Vertices, const char *mfilename,long nbVertices, long nbFaces)
	{
	  EnglishTemporaryLocale();
	  FILE *outfile;

	  outfile = fopen(mfilename, "w");
	  if (outfile == (FILE *) NULL) {
		return;
	  }

	  fprintf(outfile, "v\n");
	  fprintf(outfile, "from X Y Z\n");
	  fprintf(outfile, "at X Y Z\n");
	  fprintf(outfile, "up 0 1 0\n");
	  fprintf(outfile, "angle 50\n");
	  fprintf(outfile, "hither 1\n");
	  fprintf(outfile, "resolution 512 512\n");
	  fprintf(outfile, "b 0.1 0.5 0.7\n");
	  fprintf(outfile, "l X Y Z\n");
	  fprintf(outfile, "f 0.000 0.000 1.000 1 0 0 0 1\n");

	  for(int g=0; g < pModel.size() ;g++)
	  {
			for(long j=0; j < pModel[g].pFaces.size() ;j++)
			{
				vec3 realCoordsa=coordsOperation::GlCoordsToCommonCoords(UnitizeValue,Vertices[pModel[g].pFaces[j].Vertices.a]);
				fprintf(outfile, "p 3\n");
				fprintf(outfile, "%f  %f  %f\n",
					realCoordsa.x,realCoordsa.y,realCoordsa.z);
				vec3 realCoordsb=coordsOperation::GlCoordsToCommonCoords(UnitizeValue,Vertices[pModel[g].pFaces[j].Vertices.b]);
				fprintf(outfile, "%f  %f  %f\n",realCoordsb.x,realCoordsb.y,realCoordsb.z);
				vec3 realCoordsc=coordsOperation::GlCoordsToCommonCoords(UnitizeValue,Vertices[pModel[g].pFaces[j].Vertices.c]);
				fprintf(outfile, "%f  %f  %f\n",realCoordsc.x,realCoordsc.y,realCoordsc.z);
			}
	  }
	  fclose(outfile);
	}



	void CNff::ExportTetraNFF(vec4 UnitizeValue,triangleFace *tabVertexMaillage, const char *mfilename, long nbFaces)
	{
	    EnglishTemporaryLocale();
		if(nbFaces<4)
			return;
		FILE *outfile;

		outfile = fopen(mfilename, "w");
		if (outfile == (FILE *) NULL) {
		return;
		}


		fprintf(outfile, "v\n");
		fprintf(outfile, "at X Y Z\n");
		fprintf(outfile, "at X Y Z\n");
		fprintf(outfile, "up 0 1 0\n");
		fprintf(outfile, "angle 50\n");
		fprintf(outfile, "hither 1\n");
		fprintf(outfile, "resolution 512 512\n");
		fprintf(outfile, "b 0.1 0.5 0.7\n");
		fprintf(outfile, "l X Y Z\n");
		fprintf(outfile, "f 0.000 0.000 1.000 1 0 0 0 1\n");

		for(long f=0; f < nbFaces ;f++)
		{
			fprintf(outfile, "p 3\n");
			fprintf(outfile, "%.17g  %.17g  %.17g\n",
				(tabVertexMaillage[f].a[0]/UnitizeValue.w)+UnitizeValue.x,
				(tabVertexMaillage[f].a[1]/UnitizeValue.w)+UnitizeValue.y,
				(tabVertexMaillage[f].a[2]/UnitizeValue.w)+UnitizeValue.z);
			fprintf(outfile, "%.17g  %.17g  %.17g\n",
				(tabVertexMaillage[f].b[0]/UnitizeValue.w)+UnitizeValue.x,
				(tabVertexMaillage[f].b[1]/UnitizeValue.w)+UnitizeValue.y,
				(tabVertexMaillage[f].b[2]/UnitizeValue.w)+UnitizeValue.z);
			fprintf(outfile, "%.17g  %.17g  %.17g\n",
				(tabVertexMaillage[f].c[0]/UnitizeValue.w)+UnitizeValue.x,
				(tabVertexMaillage[f].c[1]/UnitizeValue.w)+UnitizeValue.y,
				(tabVertexMaillage[f].c[2]/UnitizeValue.w)+UnitizeValue.z);
		}

		fclose(outfile);
	}

} //fin namespace
