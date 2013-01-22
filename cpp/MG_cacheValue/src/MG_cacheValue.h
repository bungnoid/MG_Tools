/** \brief lets you cache a value
*/

/**
* @author Marco Giordano
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*@version	V2 : 


* node name : MG_cacheValue.
* 
* details : This node let you cache a value.
* 
* 
*		  
* 
*/
#ifndef _MG_cacheValue
#define _MG_cacheValue
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


 
class MG_cacheValue : public MPxNode
{

public:
		static void* creator();
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);

		static	MTypeId		typeId;
		
		static MObject toCacheValue;
		static MObject iterationStored;
		static MObject outValue;
		static MObject cache;
		static MObject pastIterationOutIndex; 








};

#endif


