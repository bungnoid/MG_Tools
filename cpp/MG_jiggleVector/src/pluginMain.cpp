#include "MG_jiggleVector.h"

#include <maya/MFnPlugin.h>








 
MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "MG_jiggleVector",
								  MG_jiggleVector::typeId,
								  &MG_jiggleVector::creator,
								  &MG_jiggleVector::initialize
								  );

	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the MG_jiggleVector node" );






	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x832413));

	return MS::kSuccess;

}//
