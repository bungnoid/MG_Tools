/**
* @author Marco Giordano
* @date  10/1/2013
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_cacheValue.
* 
* details : let s you cache a value 
*			This node let s you cache a value and then chose which iteration 
*			gives out as output
*			
*			
* example create node : (MEL) createNode MG_cacheValue.
*
* @todo  add baricentric coordinates computation mode
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
		/**
		* The node id
		*/
		static	MTypeId		typeId;
		
		/**
		* THis is the input value that is going to be cached
		*/
		static MObject toCacheValue;
		/**
		* This attribute sets how many iteration will be stored in the node
		*/
		static MObject iterationStored;
		/**
		* This attribute is the out value
		*/
		static MObject outValue;
		/**
		* This is the attribute that holds the cache
		*/
		static MObject cache;
		/**
		* This attribute defines which past iteration index to show out , remember index 0 is present value , index 1 
		* is the first past value and so on
		*/
		static MObject pastIterationOutIndex; 








};

#endif


