#include <MG_nurbsRivet.h>
#include <MG_polyRivet.h>
#include <MG_jiggleVector.h>
#include <MG_vector.h>
#include <MG_trigonometry.h>
#include <MG_poseReader.h>
#include <MG_splinePath.h>
#include <MG_vectorGL.h>
#include <MG_dotProduct.h>
#include <MG_crossProduct.h>
#include <MG_cacheValue.h> 
#include <MG_curve.h> 


#include <maya/MFnPlugin.h>


 

// last MTypeId MG_trigonometry::typeId( 0x80004 );




 
MStatus initializePlugin( MObject obj )
{ 
	MStatus stat;

	MFnPlugin fnPlugin( obj, "Marco Giordano", "1.0", "Any");

	stat = fnPlugin.registerNode( "MG_polyRivet",
								MG_polyRivet::typeId,
								MG_polyRivet::creator,
								MG_polyRivet::initialize,
								MPxNode::kDependNode
								);

	stat = fnPlugin.registerNode( "MG_nurbsRivet",
								MG_nurbsRivet::typeId,
								MG_nurbsRivet::creator,
								MG_nurbsRivet::initialize,
								MPxNode::kDependNode
								);


	stat = fnPlugin.registerNode( "MG_jiggleVector",
							MG_jiggleVector::typeId,
							MG_jiggleVector::creator,
							MG_jiggleVector::initialize,
							MPxNode::kDependNode
							);

	stat = fnPlugin.registerNode( "MG_vector",
							MG_vector::typeId,
							MG_vector::creator,
							MG_vector::initialize,
							MPxNode::kDependNode
							);


	stat = fnPlugin.registerNode( "MG_trigonometry",
							MG_trigonometry::typeId,
							MG_trigonometry::creator,
							MG_trigonometry::initialize,
							MPxNode::kDependNode
							);

	
	stat = fnPlugin.registerNode( "MG_poseReader",
							MG_poseReader::typeId,
							MG_poseReader::creator,
							MG_poseReader::initialize,
							MPxNode::kLocatorNode
							);
							
	
	stat = fnPlugin.registerNode( "MG_splinePath",
							MG_splinePath::typeId,
							MG_splinePath::creator,
							MG_splinePath::initialize,
							MPxNode::kDependNode
							);

	stat = fnPlugin.registerNode( "MG_vectorGL",
							MG_vectorGL::typeId,
							MG_vectorGL::creator,
							MG_vectorGL::initialize,
							MPxNode::kLocatorNode
							);

	stat = fnPlugin.registerNode( "MG_dotProduct",
							MG_dotProduct::typeId,
							MG_dotProduct::creator,
							MG_dotProduct::initialize,
							MPxNode::kDependNode
							);

	stat = fnPlugin.registerNode( "MG_crossProduct",
							MG_crossProduct::typeId,
							MG_crossProduct::creator,
							MG_crossProduct::initialize,
							MPxNode::kDependNode
							);

	stat = fnPlugin.registerNode( "MG_cacheValue",
							MG_cacheValue::typeId,
							MG_cacheValue::creator,
							MG_cacheValue::initialize,
							MPxNode::kDependNode
							);

	stat = fnPlugin.registerNode( "MG_curve",
							MG_curve::typeId,
							MG_curve::creator,
							MG_curve::initialize, 
							MPxNode::kDependNode
							);


	
	return stat;
}


MStatus uninitializePlugin(MObject object)

{
	
	MFnPlugin pluginFn;
	pluginFn.deregisterNode(MTypeId(0x80000)); //MG_nurbsRivet
	pluginFn.deregisterNode(MTypeId(0x80001)); //MG_polyRivet
	pluginFn.deregisterNode(MTypeId(0x80002));//MG_jiggleVector
	pluginFn.deregisterNode(MTypeId(0x80003));//MG_vector
	pluginFn.deregisterNode(MTypeId(0x80004));//MG_trigonometry
	pluginFn.deregisterNode(MTypeId(0x80005)); //MG_poseReader
	pluginFn.deregisterNode(MTypeId(0x80006)); //MG_splinePath
	pluginFn.deregisterNode(MTypeId(0x80007)); //MG_vectorGL
	pluginFn.deregisterNode(MTypeId(0x80008)); //MG_dotProduct
	pluginFn.deregisterNode(MTypeId(0x80009)); //MG_crossProduct
	pluginFn.deregisterNode(MTypeId(0x80010)); //MG_cacheValue
	pluginFn.deregisterNode(MTypeId(0x80011)); //MG_curve

	return MS::kSuccess;

} 