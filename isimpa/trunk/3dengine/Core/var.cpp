#include "var.h"
#include "manager/stringTools.h"
#include "en_numeric.hpp"
#include "last_cpp_include.hpp"

namespace formatVAR
{

	CVar::CVar()
	{



	}

bool CVar::BuildVar(t_file& sceneconst,const char* mfilename)
{
  EnglishTemporaryLocale dotNumericOnly;
  FILE *outfile;
  char mefilename[FILENAMESIZE];

  outfile = fopen(mfilename, "w");
  if (outfile == (FILE *) NULL) {
    printf("File I/O Error:  Cannot create file %s.\n", mefilename);
    return false;
  }

  unsigned int quantConstraints=sceneconst.facetsConstraints.size();
  fprintf(outfile, "# Facet constraints\n");
  fprintf(outfile, "%i\n",quantConstraints);
  for(int v=0; v < quantConstraints ;v++)
  {
	  /*
	fprintf(outfile, "%i  %i  %s\n",
	v+1,
	sceneconst.facetsConstraints[v].boundaryMarker,
	Convertor::ToString(sceneconst.facetsConstraints[v].areaConstraint,'.'));
	*/
	  fprintf(outfile, wxString::Format("%i  %i %g\n",v+1,
	sceneconst.facetsConstraints[v].boundaryMarker,
	sceneconst.facetsConstraints[v].areaConstraint
	));
  }
  fprintf(outfile, "# Segment constraints\n");
  fprintf(outfile, "0");
  fclose(outfile);

  return true;
}

} //fin namespace