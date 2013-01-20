#include "gosthConnection.h"

#include <maya/MFnPlugin.h>








 
MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "ghostConnection",
								  gosthConnection::typeId,
								  &gosthConnection::creator,
								  &gosthConnection::initialize
								 
								  );

	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the faceRigNode node" );






	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x900090));

	return MS::kSuccess;

}