/** \brief lets you constraint an object on a nurbs surface
*/

/**
* @author Marco Giordano
* @version latest version : V2
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*@version	V2 : 
				- removed dependencie from vecMath.h (custom sloppy header)
				- cleaned code  and made more efficient 
				- added offset matrix 
				

* node name : MG_nurbsRivet.
* 
* details : This node let you constraint an object on a nurb surface
*			beware that so far only nurb surface are supported.

* example create node : (MEL) createNode MG_nurbsRivet.

* notes : this node comes with a python script to easly create the node
*		  and connect all the needed attributes for the rivet node.
*		  
* 
*/
#ifndef _MG_nurbsRivet
#define _MG_nurbsRivet

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

class MG_nurbsRivet : public MPxNode
{
public:
		static void* creator();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		
		//static const MString typeName;

public:
	/**
	*  Connect to this input the shape of the nurbsSurface 
	*  on which the rivet will stay on
	*/
	static MObject inputNurbSurface;
	/**
	* This is the initial position for the target object 
	*/
	static MObject inputPoint;
	/**
	*  This check box let you turn on of the recompute of the closest point on the nurbSurface
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

	static MTypeId typeId; 


		
};




#endif 
