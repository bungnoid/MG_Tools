/** \brief lets you constraint an object on a nurbs surface
*/

/**
* @author Marco Giordano
* @date  10/26/2012
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				


* node name : rivetNode.
* 
* details : This node let you constraint an object on a poly mesh
*			
* example create node : (MEL) createNode MG_polyRivet.
* @todo  add baricentric coordinates computation mode
* notes : this node comes with a python script to easly create the node
*		  and connect all the needed attributes for the MG_polyRivet.
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
	static MObject inputPointX;
	static MObject inputPointY;
	static MObject inputPointZ;
	static MObject outputX;
	static MObject outputY;
	static MObject outputZ;	
	static MObject outputRotateX;
	static MObject outputRotateY;
	static MObject outputRotateZ;	
	static MObject parentMatrix;

	static MTypeId typeId; 


		
};




#endif 
