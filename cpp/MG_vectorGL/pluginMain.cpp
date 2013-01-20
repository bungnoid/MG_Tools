#include "MG_vectorGL.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{  
	MStatus stat; 

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "MG_vectorGL", MG_vectorGL::typeId,
								MG_vectorGL::creator,
								MG_vectorGL::initialize, 
								MPxNode::kLocatorNode );
	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the MG_vectorGL node" );


	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x80006));

	return MS::kSuccess;

}