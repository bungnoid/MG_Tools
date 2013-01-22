#include "MG_trigonometry.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{  
	MStatus stat; 

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "MG_trigonometry", MG_trigonometry::typeId,
								MG_trigonometry::creator,
								MG_trigonometry::initialize, 
								MPxNode::kDependNode );
	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the poseReader node" );


	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x80004));

	return MS::kSuccess;

}
