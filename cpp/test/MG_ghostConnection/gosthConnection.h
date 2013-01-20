#ifndef GOSTHCONNECTION_H
#define GOSTHCONNECTION_H

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
#include <maya/MNodeMessage.h>

//Class

class gosthConnection : public MPxNode
{
public:
		static void* creator();


		static MStatus initialize();
		virtual MStatus compute(const MPlug& plug,MDataBlock& dataBlock);
		virtual void postConstructor();
		virtual ~gosthConnection() ;

		
		//static const MString typeName;

public:
	static MObject input;
	static MObject message;
	static MObject outputFake;
	static MObject connection;
	

	




	static MTypeId typeId;


		
};





#endif 