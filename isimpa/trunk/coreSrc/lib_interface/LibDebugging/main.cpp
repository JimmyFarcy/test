#include <input_output/bin.h>
#include <iostream>

int main(int argc, char* argv[])
{
  using namespace formatCoreBIN;
  int szint=sizeof(uint32_t);
  std::cout<<"uint32_t="<<szint<<std::endl;
  ioModel model;
  CformatBIN tool;
  if(tool.ImportBIN(model, "mesh.cbin"))
  {
    std::cout<<"Model load success"<<std::endl;
    std::cout<<"There are "<<model.faces.size()<<" faces"<<std::endl;
  }else{
    std::cout<<"Model load failed"<<std::endl;
  }
 return 0;
}
/*
#include <tools/vol_identifier.hpp>
#include <tools/vol_splitter.hpp>
#include <iostream>
int main(int argc, char* argv[])
{
	using namespace volume_identifier;
	using namespace formatMBIN;
	CMBIN triimporter;
	trimeshmodel modeltri=triimporter.LoadMesh("tetramesh.mbin");
	formatCoreBIN::CformatBIN importer;
	formatCoreBIN::ioModel model;
	importer.ImportBIN(model,"mesh.cbin");

	//VolumeIdentifier::IdentifyVolumes(modeltri);
	volumes_splitter::VolumesSplitter splitvol;
	splitvol.LoadDomain(model,modeltri);
	int volxid;
	double vol;
	std::vector<std::size_t> faces;
	std::vector<std::size_t> neigh;
	//splitvol.GetVolumeInformation(0,volxid,vol,faces,neigh);
	//0.598193" y="1.766407" z="0.750000
	int idtet=splitvol.GetTetraByPosition(modeltri,0.598193f,1.766407f,0.750000f);
	std::cout<<"Id tet:"<<idtet<<std::endl;
}

*/
/*
#include "tools/surf_merging.hpp"
int main(int argc, char* argv[])
{
	using namespace surf_merge;
	formatCoreBIN::ioModel model;
	formatCoreBIN::CformatBIN importer;
	importer.ImportBIN(model,"modeldebug.cbin");
	surf_merge::SurfaceMerging merger;
	merger.LoadGroups(model);
}
*/
/*
#include <input_output/exportRecepteurSurf/std_rsbin.hpp>
#include <Core/mathlib.h>

int main(int argc, char* argv[])
{
	using namespace formatRSBIN;
	rsurf_data datars;
	rsurf_io::Load("rs_cut.csbin",datars);

	rsurf_iso_contouring contouringTool(datars,0);
	contouringTool.SmoothGrid(1);
	float dbcurve=13.27f;
	std::list<t_curve> curvlst;
	//powf(10.f,dbcurve/10)*powf(10.f,-12.f)
	contouringTool.GetIsoLevelCurves(dbcurve,curvlst);
	return 0;
}
*/
