//used

#include <maya/MFnPlugin.h>
#include <MG_vector.h>



MStatus initializePlugin( MObject obj )
{
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");

	MFnPlugin pluginFn(obj,("MG","1.0","any"));
	pluginFn.registerNode("MG_vector",MTypeId(0x832495),MG_vector::creator,MG_vector::initialize);


	return stat; 
}


MStatus uninitializePlugin( MObject obj)
{
	MStatus stat;

	
	MFnPlugin fnPlugin( obj );

	
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x800003));

	
	return stat;
}
