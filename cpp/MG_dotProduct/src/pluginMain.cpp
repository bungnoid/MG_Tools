

#include <maya/MFnPlugin.h>
#include <MG_dotProduct.h>




MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");


	stat  =fnPlugin.registerNode("MG_dotProduct",
		MTypeId(0x832496),MG_dotProduct::creator,
		MG_dotProduct::initialize);

	if( stat != MS::kSuccess )
		stat.perror( "could not register the CustomLocator node" );

	return stat; 
}


MStatus uninitializePlugin(MObject object)

{
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x80008));
	return MS::kSuccess;

}