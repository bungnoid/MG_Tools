#include "curveNode.h"

#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat = fnPlugin.registerNode( "curveNode",
								  curveNode::typeId,
								  &curveNode::creator,
								  &curveNode::initialize
								  );

	

	if( stat != MS::kSuccess )
		stat.perror( "could not register the faceRigNode node" );


	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x832414));

	return MS::kSuccess;

}