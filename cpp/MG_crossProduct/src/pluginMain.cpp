

#include <maya/MFnPlugin.h>
#include <MG_crossProduct.h> 




MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat  =fnPlugin.registerNode("MG_crossProduct",MTypeId(0x832497),
		MG_crossProduct::creator,
		MG_crossProduct::initialize);

	if( stat != MS::kSuccess )
		stat.perror( "could not register the crossPorduct node" );

	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
\
	pluginFn.deregisterNode(MTypeId(0x80009)); 
	return MS::kSuccess;

}