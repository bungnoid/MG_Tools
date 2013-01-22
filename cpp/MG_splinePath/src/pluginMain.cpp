#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h>

#include "MG_splinePath.h"


// init
MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj );
    status = plugin.registerNode( "MG_splinePath", MG_splinePath::typeId, MG_splinePath::creator,
        MG_splinePath::initialize);

	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

    status = plugin.deregisterNode( MG_splinePath::typeId );

	return status;
}
