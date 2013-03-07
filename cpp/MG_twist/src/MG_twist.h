/** \brief lets you extract a twist value from two transforms
*/
/**
* @author Marco Giordano
* @date  1/24/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n
*			V2 : \n
*				- implemented different twist axis rather then only Y \n
* node name : MG_twist
.
* 
* details : This node  lets you extract a twist value from two transforms
*			
* example create node : (MEL) createNode MG_twist.
*
* @todo set output data with a single array data builder rather then one at the time in order to improve 
* performances
* @todo implement more type of distribuition for for the outputs
* 
*/
#ifndef _MG_twist
#define _MG_twist

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
#include <maya/MQuaternion.h>


//Class

class MG_twist : public MPxNode
{
public:
		static void* creator();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		
		//static const MString typeName;

public:
	/**
	*  The first matrix to calculate the twist from
	*/
	static MObject matrix1;
	/**
	*  The second matrix to calculate the twist from
	*/
	static MObject matrix2;
	/**

	*  How many output twist will be computed
	*/
	static MObject numberOfOutputs;
	/**
	*  This is the axis that will be used for computation
	*/
	static MObject twistAxis;
	/**
	* This is the X component of the output translate array
	*/
    static MObject outputTranslateX;
	/**
	* This is the Y component of the output translate array
	*/
    static MObject outputTranslateY;
	/**
	* This is the Z component of the output translate array
	*/
    static MObject outputTranslateZ;
	/**
	* This is the output translate array
	*/
    static MObject outputTranslate;
	/**
	* This is the X component of the output Rotate array
	*/
    static MObject outputRotateX;
	/**
	* This is the Y component of the output Rotate array
	*/
    static MObject outputRotateY;
	/**
	* This is the Z component of the output Rotate array
	*/
    static MObject outputRotateZ;
	/**
		* This is the output Rotate array
		*/
      static MObject outputRotate;
	


	static MTypeId typeId; 

private :
	/**
	*  This function is used to convert a given vector to a qauaternion rotation from a starting axis
	*@param vec : MVector , this is the vector we want to transform into a quaternion rotation
	*@param axis: int , this is the axis we want to use as a reference for the rotation 
	*						accepted values : - 0 = x 
	*										  - 1 = y 
	*										  - 2 = z 
	*/
	
	MQuaternion vecToRotQuat(MVector vec , int axis);
	
};




#endif 
