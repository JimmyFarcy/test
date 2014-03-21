#include "mesh.h"
#include "en_numeric.hpp"
#include "manager/stringTools.h"
#include <locale.h>
#include "last_cpp_include.hpp"

namespace formatMESH
{

	CMesh::CMesh()
	{



	}
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// ExportMESH()    Format mesh créé par INRIA
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void CMesh::ExportMESH(vec4 UnitizeValue,std::vector<SGroup3D> &pModel, std::vector<vec3> &Vertices, const char *mfilename,long nbVertices, long nbFaces)
{
  FILE *outfile;
  char mefilename[FILENAMESIZE];
  EnglishTemporaryLocale();
  outfile = fopen(mfilename, "w");
  if (outfile == (FILE *) NULL) {
    printf("File I/O Error:  Cannot create file %s.\n", mefilename);
    return;
  }

  fprintf(outfile, "MeshVersionFormatted 1\n");
  fprintf(outfile, "\n");
  fprintf(outfile, "Dimension\n");
  fprintf(outfile, "3\n");
  fprintf(outfile, "\n");

  fprintf(outfile, "\n# Set of mesh vertices\n");
  fprintf(outfile, "Vertices\n");
  fprintf(outfile, "%ld\n", Vertices.size());
  // Medit need start number form 1.
  for(int v=0; v < Vertices.size() ;v++)
  {
	// Face j Point coordinates. Vertice 1 of 3
	vec3 realCoords=coordsOperation::GlCoordsToCommonCoords(UnitizeValue,Vertices[v]);
	fprintf(outfile, "%f    %f    %f ",
	realCoords.x, //On remet les points à leur etat d'origine est l'on exporte
	realCoords.y,
	realCoords.z);
	fprintf(outfile, "    0\n");
  }
  fprintf(outfile, "\n# Set of Triangles\n");
  fprintf(outfile, "Triangles\n");
  fprintf(outfile, "%ld\n", nbFaces);

  for(int g=0; g < pModel.size() ;g++)
  {
		for(long j=0; j < pModel[g].pFaces.size() ;j++)
		{
			fprintf(outfile, "%5d  %5d  %5d",
					pModel[g].pFaces[j].Vertices.a+1,
					pModel[g].pFaces[j].Vertices.b+1,
					pModel[g].pFaces[j].Vertices.c+1);
			fprintf(outfile, "    0\n");
		}
  }

  fprintf(outfile, "\nEnd\n");
  fclose(outfile);
}

} //fin namespace
