
					if(result)
					{
						//Il y a deux cas possible
						//Cas 1, deux triangles sont coplanaire (triangle overlapping)
						//Cas 2, Les deux triangles entrent en collision
						if(coplanar)
						{
							std::cout<<"Superposition de triangles, suppression du plus petit "<<std::endl;
							if(GetAireTriangle(*faceA,*faceB,*faceC)>GetAireTriangle(modelData.modelVertices[faceTestSommets->a],modelData.modelVertices[faceTestSommets->b],modelData.modelVertices[faceTestSommets->c]))
							{
								modelData.modelFaces.erase(modelData.modelFaces.begin()+idfaceTest);
							}else{
								modelData.modelFaces.erase(modelData.modelFaces.begin()+idface);
							}
						}else{
							//////////////////////////////////////////////////////
							//Recherche des indices de isecA et isecB
							int secAOwner=idface;
							int secBOwner=idface;
							int i_isecA(-1),i_isecB(-1);
							int idSommetCollision=GetIndiceByCoord(*faceA,*faceB,*faceC,isecA);
							if(idSommetCollision==-1)
							{
								idSommetCollision=GetIndiceByCoord(modelData.modelVertices[faceTestSommets->a],modelData.modelVertices[faceTestSommets->b],modelData.modelVertices[faceTestSommets->c],isecA);
								if(idSommetCollision!=-1)
								{
									i_isecA=modelData.modelFaces[idfaceTest].indicesSommets[idSommetCollision];
									secAOwner=idfaceTest;
								}
							}else{
								i_isecA=modelData.modelFaces[idface].indicesSommets[idSommetCollision];
							}
							if(isecA.distance(isecB)<EPSILON)
							{
								i_isecB=i_isecA;
							}else{
								idSommetCollision=GetIndiceByCoord(*faceA,*faceB,*faceC,isecB);
								if(idSommetCollision==-1)
								{
									idSommetCollision=GetIndiceByCoord(modelData.modelVertices[faceTestSommets->a],modelData.modelVertices[faceTestSommets->b],modelData.modelVertices[faceTestSommets->c],isecB);
									if(idSommetCollision!=-1)
									{
										i_isecB=modelData.modelFaces[idfaceTest].indicesSommets[idSommetCollision];
										secBOwner=idfaceTest;
									}
								}else{
									i_isecB=modelData.modelFaces[idface].indicesSommets[idSommetCollision];
								}
							}
							//////////////////////////////////////////////////////
							//Recherche locales des indices de isecA et isecB infructueuses, recherche globale
							if(i_isecA==-1)
							{
								i_isecA=FindIndexWithPosition(isecA);
								if(i_isecA==-1)
								{
									modelData.modelVertices.push_back(isecA);
									i_isecA=modelData.modelVertices.size()-1;
								}
							}
							if(i_isecB==-1)
							{
								i_isecB=FindIndexWithPosition(isecB);
								if(i_isecA==-1)
								{
									modelData.modelVertices.push_back(isecA);
									i_isecA=modelData.modelVertices.size()-1;
								}
							}

							unsigned int idFaceToSplit=idfaceTest;
							if(secAOwner==idfaceTest)
								idFaceToSplit=idface;

							int  newFaceOne, newFaceTwo;
							SplitTriangleByThree(modelData.modelFaces[idFaceToSplit],i_isecA,&newFaceOne,&newFaceTwo);

							//Gestion du point d'intersection B

						}
						return true;
						/*
						std::cout<<coplanar<<" Intersect f1:"<<idface;
						genprintVec(*faceSommets);
						std::cout<<" f2:"<<idfaceTest;
						genprintVec(*faceTestSommets);
						std::cout<<" ";
						genprintVec(isecA);
						std::cout<<" ";
						genprintVec(isecB);
						std::cout<<std::endl;
						*/
					}