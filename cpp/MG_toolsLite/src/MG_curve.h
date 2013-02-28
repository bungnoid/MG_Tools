/** \brief lets you generate a curve out of transform
*/

/** 
* @author Marco Giordano
* @date  11/13/2012
* @version latest version : V1
* @version changeload versions : \n
*			V1 : \n
*				- initial release \n				
*
*
* node name : MG_curve.
* 
* details : This node let you create a nurbs curve using an X number of transform as controlPoints.
*			THe output of this node is not a simple float but a shape , so i suggest you to create a nurbs curve
*			like a circle and then override the connection in the "create" attribute in the curve shape
*			
*			
* example create node : (MEL) createNode MG_curve.
*
*
*		  
* 
*/

#ifndef MG_CURVE_H
#define MG_CURVE_H

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

class MG_curve : public MPxNode
{
public:
		static void* creator();

 
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		
		//static const MString typeName;

public:
	/**
	* This is the attribute holding the input world matrix array 
	*/
	static MObject inputMatrix;
	/**
	* This is the output shape of the curve
	*/
	static MObject output;
	/**
	* This is the degree we want to use for the curve
	*/
	static MObject degree;
	/**
	* Plug this value holds the transform world matrix of the curve , if you plug it in the node 
	* we will multipy the point for the inverse matrix so the curve wont be affected by its transform
	*/
	static MObject transformMatrix;

	/**
	* The node id
	*/
	static MTypeId typeId;


		
};




#endif 