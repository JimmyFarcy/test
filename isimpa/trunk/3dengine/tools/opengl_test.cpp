#include "opengl_test.hpp"
#include "GL/opengl_inc.h"
#include "last_cpp_include.hpp"
#include <string.h>

namespace gltest
{
	//  Created by Richard Wright on 10/16/06.
	//  OpenGL SuperBible, 4rth Edition

	int gltIsExtSupported(const char *extension)
		{
		GLubyte *extensions = NULL;
		const GLubyte *start;
		GLubyte *where, *terminator;

		where = (GLubyte *) strchr(extension, ' ');
		if (where || *extension == '\0')
			return 0;

		extensions = (GLubyte *)glGetString(GL_EXTENSIONS);

		start = extensions;
		for (;;)
			{
			where = (GLubyte *) strstr((const char *) start, extension);

			if (!where)
				break;

			terminator = where + strlen(extension);

			if (where == start || *(where - 1) == ' ')
				{
				if (*terminator == ' ' || *terminator == '\0')
					return 1;
				}
			start = terminator;
			}
		return 0;
		}
}
