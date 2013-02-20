/** \brief lets you extract a twist value from two transforms
*/
/**
* @author Marco Giordano
* @date  1/24/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				


* node name : MG_twist
.
* 
* details : This node  lets you extract a twist value from two transforms
*			
* example create node : (MEL) createNode MG_twist.
*		  
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
	*  The attribute that will hold the twist value
	*/
	static MObject twistValues;
	/**
	*  How many output twist will be computed
	*/
	static MObject outputNumber;
	
	static MTypeId typeId; 

private :
	MQuaternion vecToRotQuat(MVector vec);
		
};




#endif 
