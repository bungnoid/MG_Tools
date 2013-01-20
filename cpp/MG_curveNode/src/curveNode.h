#ifndef FACERIGNODE_H
#define FACERIGNODE_H

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

class curveNode : public MPxNode
{
public:
		static void* creator();

 
		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		
		//static const MString typeName;

public:

	static MObject inputMatrix;
	static MObject output;
	static MObject degree;
	static MObject transformMatrix;
	static MTypeId typeId;


		
};




#endif 