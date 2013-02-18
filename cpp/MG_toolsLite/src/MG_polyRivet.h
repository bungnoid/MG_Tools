/** \brief lets you constraint an object on a poly mesh
*/

/**
* @author Marco Giordano
* @date  10/26/2012
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_polyRivet.
* 
* details : This node let you constraint an object on a poly mesh
*			This node needs as input an input point, the input point is the point 
*			from where the closest point on the mesh will be calculated in order to place the rivet.
*			An input mesh  has to be provided , just connect the "worldMesh" attribute
*			from the shape of the wanted mesh to inputSurface attribute.
*			If you want to keep an offset from the calculated rivet you can set the offset matrix 
*			in the node , this has to be calculate  , I might provide a script for that in the feature.
*			Also the world matrix from the mesh transform needs to be connected to meshParentMatrix attribute.
*			Once your happy with the rivet position you can uncheck the recompute attribute , in this way
*			the closest point on mesh wont be recomputed anymore , keep it on if you want to animate the i
*			input point and slide the rivet on the mesh.
*			
* example create node : (MEL) createNode MG_polyRivet.
*
* @todo  add baricentric coordinates computation mode
*
*		  
* 
*/
#ifndef _rivetNode
#define _rivetNode

#include <maya/MPxNode.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MTypeId.h>


//Class

class MG_polyRivet : public MPxNode
{
public:
		static void* creator();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		
		//static const MString typeName;

public:
	/**
	*  Connect to this input the shape of the poly mesh
	*  on which the rivet will stay on
	*/
	static MObject inputMesh;
	/**
	* This is the initial position for the target object 
	*/
	static MObject inputPoint;
	/**
	*  This check box let you turn on of the recompute of the closest point on the polyMesh
	*/
	static MObject recompute;
	/**
	*	The output translate attribute 
	*/
	static MObject output;
	/**
	* The u value for the rivet 
	*/
	static MObject uValue;
	/**
	* The v value for the rivet
	*/
	static MObject vValue;
	/**
	*  The output rotate attribute
	*/

	static MObject outputRotate;
	/**
	* The output matrix attribute
	*/
	static MObject outputMatrix;
	/**
	* The face on which the rivet stays on
	*/

	static MObject faceId;


	/**
	* This attribute holds the offset matrix from the rivet to the target
	* that is going to be driven by the rivet
	*/
	static MObject offsetMatrix;
	/**
	* The input X for the compound attribute inputPoint
	*/
	static MObject inputPointX;
	/**
	* The input Y for the compound attribute inputPoint
	*/
	static MObject inputPointY;
	/**
	* The input Z for the compound attribute inputPoint
	*/
	static MObject inputPointZ;
	/**
	* The output  X for the compound attribute output
	*/
	static MObject outputX;
	/**
	* The output  Y for the compound attribute output
	*/
	static MObject outputY;
	/**
	* The output  Z for the compound attribute output
	*/
	static MObject outputZ;	
	/**
	* The output  X for the compound attribute outputRotate
	*/
	static MObject outputRotateX;
	/**
	* The output Y for the compound attribute outputRotate
	*/
	static MObject outputRotateY;
	/**
	* The output  Z for the compound attribute outputRotate
	*/
	static MObject outputRotateZ;	
	/**
	* This attribute is the mesh transform world matrix used to multiply the
	*rivet matrix
	
	*/
	static MObject meshParentMatrix;
	/**
	* The node id
	*/
	static MTypeId typeId; 


		
};




#endif 
