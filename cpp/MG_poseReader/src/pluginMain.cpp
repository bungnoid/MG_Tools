#include "MG_poseReader.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{  
	MStatus stat; 

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "poseReader", MG_poseReader::typeId,
								MG_poseReader::creator,
								MG_poseReader::initialize, 
								MPxNode::kLocatorNode );
	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the MG_poseReader node" );


	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x80005));

	return MS::kSuccess;

}