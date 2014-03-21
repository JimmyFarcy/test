#include "stl.hpp"
#include "en_numeric.hpp"
#include <stdio.h>
#include <list>
#include <string>
#include <string.h>

namespace formatSTL
{
	char **get_words(FILE *fp, int *nwords, char **orig_line)
	{
	#define BIG_STRING 4096
	  int i,j;
	  static char str[BIG_STRING];
	  static char str_copy[BIG_STRING];
	  char **words;
	  int max_words = 10;
	  int num_words = 0;
	  char *ptr,*ptr2;
	  char *result;

	  words = (char **) malloc (sizeof (char *) * max_words);

	  /* read in a line */
	  result = fgets (str, BIG_STRING, fp);
	  if (result == NULL) {
		*nwords = 0;
		*orig_line = NULL;
		return (NULL);
	  }

	  /* convert line-feed and tabs into spaces */
	  /* (this guarentees that there will be a space before the */
	  /*  null character at the end of the string) */

	  str[BIG_STRING-2] = ' ';
	  str[BIG_STRING-1] = '\0';

	  for (ptr = str, ptr2 = str_copy; *ptr != '\0'; ptr++, ptr2++) {
		*ptr2 = *ptr;
		if (*ptr == '\t') {
		  *ptr = ' ';
		  *ptr2 = ' ';
		}
		else if (*ptr == '\n') {
		  *ptr = ' ';
		  *ptr2 = '\0';
		  break;
		}
	  }

	  /* find the words in the line */

	  ptr = str;
	  while (*ptr != '\0') {

		/* jump over leading spaces */
		while (*ptr == ' ')
		  ptr++;

		/* break if we reach the end */
		if (*ptr == '\0')
		  break;

		/* allocate more room for words if necessary */
		if (num_words >= max_words) {
		  max_words += 10;
		  words = (char **) realloc (words, sizeof (char *) * max_words);
		}

		if (*ptr == '\"') {  /* a quote indidicates that we have a string */

		  /* skip over leading quote */
		  ptr++;

		  /* save pointer to beginning of word */
		  words[num_words++] = ptr;

		  /* find trailing quote or end of line */
		  while (*ptr != '\"' && *ptr != '\0')
			ptr++;

		  /* replace quote with a null character to mark the end of the word */
		  /* if we are not already at the end of the line */
		  if (*ptr != '\0')
		*ptr++ = '\0';
		}
		else {               /* non-string */

		  /* save pointer to beginning of word */
		  words[num_words++] = ptr;

		  /* jump over non-spaces */
		  while (*ptr != ' ')
		ptr++;

		  /* place a null character here to mark the end of the word */
		  *ptr++ = '\0';
		}
	  }

	  /* return the list of words */
	  *nwords = num_words;
	  *orig_line = str_copy;
	  return (words);
	}


	int equal_strings(char *s1, char *s2)
	{
	  int i;

	  while (*s1 && *s2)
		if (*s1++ != *s2++)
		  return (0);

	  if (*s1 != *s2)
		return (0);
	  else
		return (1);
	}
	char buffer[50];

	int ToInt(const char* charArray)
	{
		return atoi(charArray);
	}

	float ToFloat(const char* charArray)
	{
		return atof(charArray);
	}


	CStl::CStl()
	{



	}

bool CStl::ExportSTL(t_model& scene, const char* mfilename)
{
  EnglishTemporaryLocale dotNumericOnly;




  FILE *outfile;

  outfile = fopen(mfilename, "w");
  if (outfile == (FILE *) NULL) {
    printf("File I/O Error:  Cannot create file %s.\n", mfilename);
    return false;
  }
  fclose(outfile);
  return true;
}

struct words_destroyer
{
	words_destroyer(char **_words):words(_words){};
	~words_destroyer(){ free(words);}
	char **words;
};
bool CStl::ImportSTL(t_model& scene,const char* mfilename)
{
  EnglishTemporaryLocale dotNumericOnly;

  char tmpBuffer[250];
  strcpy(tmpBuffer,"Empty buffer");
  FILE *infile;
  infile = fopen(mfilename, "r+");
  if (infile == (FILE *) NULL) {
    //throw -1; //("File I/O Error:  Cannot open file.\n");
    return false;
  }
  int nwords=0;
  char **words;
  char *orig_line;
  unsigned int sizeVertices=0;
  unsigned int sizeFaces=0;

  /* Lecture du fichier d'entete */
  //Lecture des 5 premier caractere, si "solid" alors format ascii
  fread(tmpBuffer,1,sizeof(char) * 6,infile);
  fclose(infile);
  infile = fopen(mfilename, "r+");
  if (infile == (FILE *) NULL) {
    //throw -1; //("File I/O Error:  Cannot open file.\n");
    return false;
  }

  if(std::string(tmpBuffer).find("solid")!=std::string::npos)
  {
	  //ASCII

	  std::list<vec3> vlist;
	  std::list<ivec3> flist;
	  unsigned int vsize=0;
	  unsigned int fsize=0;
	   while(!feof(infile))
	  {
		vec3 a,b,c;
		//Go to facet word
		while(!feof(infile))
		{
			words = get_words (infile, &nwords, &orig_line);
			words_destroyer free_words(words);
			if(nwords>1)
			{
				if(strcmp(words[0],"facet")==0)
					break;
			}
		}
		//Skip "outer loop"
		words = get_words (infile, &nwords, &orig_line);
		words_destroyer free_words(words);

		t_face newFace;
		//
		// VERTEX A
		words = get_words (infile, &nwords, &orig_line);
		words_destroyer free_words_va(words);
		if(nwords==4)
		{
			sscanf(words[1],"%f",&(a.x));
			sscanf(words[2],"%f",&(a.y));
			sscanf(words[3],"%f",&(a.z));
		}
		//
		// VERTEX B
		words = get_words (infile, &nwords, &orig_line);
		words_destroyer free_words_vb(words);
		if(nwords==4)
		{
			sscanf(words[1],"%f",&(b.x));
			sscanf(words[2],"%f",&(b.y));
			sscanf(words[3],"%f",&(b.z));
		}
		//
		// VERTEX C
		words = get_words (infile, &nwords, &orig_line);
		words_destroyer free_words_vc(words);
		if(nwords==4)
		{
			sscanf(words[1],"%f",&(c.x));
			sscanf(words[2],"%f",&(c.y));
			sscanf(words[3],"%f",&(c.z));
		}
		//Append face
		ivec3 face(vsize,vsize+1,vsize+2);
		fsize++;
		flist.push_front(face);
		vlist.push_back(a);
		vsize++;
		vlist.push_back(b);
		vsize++;
		vlist.push_back(c);
		vsize++;
	  }

	  scene.modelVertices.reserve(vsize);
	  for(std::list<vec3>::iterator itvert=vlist.begin();itvert!=vlist.end();itvert++)
	  {
		  scene.modelVertices.push_back(*itvert);
	  }
	  scene.modelFaces.reserve(fsize);
	  for(std::list<ivec3>::iterator itface=flist.begin();itface!=flist.end();itface++)
	  {
		  scene.modelFaces.push_back(t_face(*itface));
	  }
  }else{
	  //BINARY
	  char header[80];
	  unsigned int triangles_count(0);
	  float normal[3],vertexA[3],vertexB[3],vertexC[3];
	  unsigned short bytecount(0);
	  //Read header
	  fread(header,1,sizeof(char) * 80,infile);
	  //Read number of triangle
	  fread(&triangles_count,1,sizeof(unsigned int),infile);
	  scene.modelFaces.assign(triangles_count,t_face());
	  scene.modelVertices.assign(triangles_count*3,vec3());
	  for(unsigned int idtri=0;idtri<triangles_count;idtri++)
	  {
		  unsigned int a(0),b(0),c(0);
		  //Read face
		  fread(normal,1,sizeof(float) * 3,infile);
		  fread(vertexA,1,sizeof(float) * 3,infile);
		  fread(vertexB,1,sizeof(float) * 3,infile);
		  fread(vertexC,1,sizeof(float) * 3,infile);
		  fread(&bytecount,1,sizeof(unsigned short),infile);

		  scene.modelFaces[idtri].indicesSommets.set(idtri,idtri*3+1,idtri*3+2);
		  scene.modelVertices[idtri]=vertexA;
		  scene.modelVertices[idtri+1]=vertexB;
		  scene.modelVertices[idtri+2]=vertexC;
	  }
  }

  //Lectures des triangles
  fclose(infile);

  return true;
}

} //fin namespace
