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
*			This node needs as input an input point, the input point is the point 
*			from where the closest point on the nurbs will be calculated in order to place the rivet.
*			An input nurbs surface has to be provided , just connect the "worldSpace" attribute
*			from the shape of the wanted nurbs curve.
*			If you want to keep an offset from the calculated rivet you can set the offset matrix 
*			in the node , this has to be calculate  , I might provide a script for that in the feature.
*			Once your happy with the rivet position you can uncheck the recompute attribute , in this way
*			the closest point on surface wont be recomputed anymore , keep it on if you want to animate the i
*			input point and slide the rivet on the surface
*			

* example create node : (MEL) createNode MG_nurbsRivet.
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
	* The node id
	*/
	static MTypeId typeId; 


		
};




#endif 
