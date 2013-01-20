


#include "gosthConnection.h"

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
#include <maya/MFnMessageAttribute.h>
#include <maya/MPlugArray.h>
#include <maya/MDGModifier.h>
#include <maya/MDagModifier.h>
#include <maya/MNodeMessage.h>

MTypeId gosthConnection::typeId( 0x900090 );

MObject gosthConnection::input;
MObject gosthConnection::message;
MObject gosthConnection::outputFake;
MObject gosthConnection::connection;












//Class


void* gosthConnection::creator()
{

	return new gosthConnection();
}

MStatus gosthConnection::initialize()
{


	MFnNumericAttribute numFn;
	input = numFn.create("input","i",MFnNumericData::kFloat);



	numFn.setMin(0);
	numFn.setMax (10);
	addAttribute(input);

	outputFake = numFn.create("outputFake","of",MFnNumericData::kFloat);
	addAttribute(outputFake);
	

	
	message= numFn.create("messageFake","mef",MFnNumericData::kFloat);
	addAttribute (message);

	connection= numFn.create("conn","c",MFnNumericData::kBoolean);
	addAttribute (connection);
	attributeAffects(input,outputFake);
	attributeAffects(connection,outputFake);
	
	return MS::kSuccess;


} 



MStatus gosthConnection::compute(const MPlug& plug,MDataBlock& dataBlock)
{
		
	if (plug==outputFake)
		{

			MDataHandle connectionH = dataBlock.inputValue(connection);
			bool connOnOff = connectionH.asBool();

			if (connOnOff==0)
			{
			//Gets input attribute value 

			MDataHandle inputH  = dataBlock.inputValue(input);
			float inputValue = inputH.asFloat();

			//Plug to this attribute fake message 

			MPlug inputPlug(thisMObject(),message);


			//Array plug of incoming connection for this attribute
			MPlugArray incomingC ;
			MStatus status;
			inputPlug.connectedTo(incomingC,true,false,&status);
			
			//Get node from plugs
			MObject nodeS;
			
			if (incomingC.length()!=0)
			{
			nodeS=incomingC[0].node();
			
			
			//Now get the plug to the wanted attrbiute 
			MFnDependencyNode depFn(nodeS);
			MPlug yPlug =depFn.findPlug("translateY");
			
			
			//set the value 
			yPlug.setValue(inputValue);
			}
	
			
			


			}
		
						
			
			//set fake attribute to 0

			MDataHandle outputH = dataBlock.outputValue(outputFake);
			outputH.set(0);
			outputH.setClean();

			
					 	

	}	


		
		return MS::kSuccess;
}

void AttrChangedCB(MNodeMessage::AttributeMessage msg, MPlug & plug, MPlug & otherPlug, void* vpClientData)
		{
		

		MFnDependencyNode depFn(plug.node());
		MPlug connectionP = depFn.findPlug("conn");
		if (connectionP==plug)
		{

			cout << "Attr Change : connection" << endl;
			//Plug to this attribute fake message 

			MPlug messageP = depFn.findPlug("messageFake");
			MPlug inputP = depFn.findPlug("input");

			//Array plug of incoming connection for this attribute
			MPlugArray incomingC ;
			messageP.connectedTo(incomingC,true,false);
			
			//Get node from plugs
			MObject nodeS;
			nodeS=incomingC[0].node();
			
			//Now get the plug to the wanted attrbiute 
			MFnDependencyNode depFn(nodeS);
			MPlug yPlug =depFn.findPlug("translateY");

			MDGModifier dgMod;
			MStatus status;


			int connectionBool ; 
			connectionP.getValue(connectionBool); 

			if (connectionBool==1 )

			{

			
			status=dgMod.connect(inputP,yPlug);
			dgMod.doIt();

			}
			else
			{

				status=dgMod.disconnect(inputP,yPlug);
			dgMod.doIt();
			}



		}

		}
MCallbackId callBackH ;
void gosthConnection::postConstructor()
{
MStatus stat;
MObject moNode = thisMObject();


callBackH = MNodeMessage::addAttributeChangedCallback(moNode, AttrChangedCB, NULL, &stat);
}

gosthConnection::~gosthConnection()  
{
// Remember to remove the callback in destructor
MMessage::removeCallback(callBackH);
}