#include "MG_polyRivet.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "2.0", "Any");


	stat = fnPlugin.registerNode( "MG_polyRivet",
								  MG_polyRivet::typeId,
								  &MG_polyRivet::creator,
								  &MG_polyRivet::initialize
								  );

	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the faceRigNode node" );


	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x800000));

	return MS::kSuccess;

}