#include "MG_trigonometry.h"

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MFloatVector.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MPlug.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MVector.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixData.h>
#include <cmath>
#include <maya/MDataHandle.h>
const double PI=3.14159265358979323846264338327950288419716939937510;

const double toDeg = 57.295779513082320876798154814105;
const double toRad = 0.01745329251994329576923690768489;
MTypeId MG_trigonometry::typeId( 0x80004 );

//Needed attributes

MObject MG_trigonometry::input;
MObject MG_trigonometry::mathOperation;
MObject MG_trigonometry::inverseFunction;
MObject MG_trigonometry::outputValue;





//Class


void* MG_trigonometry::creator()
{

	return new MG_trigonometry();
}

MStatus MG_trigonometry::initialize()
	{ 
		//Declaring all the needed attribute function sets
		MFnEnumAttribute enumFn;
		MFnMatrixAttribute matrixFn;
		MFnNumericAttribute numFn;
		MFnCompoundAttribute compA;

		mathOperation = enumFn.create("mathOperation","mop",0);
		enumFn.addField("sin",0);
		enumFn.addField("cos",1);
		enumFn.addField("tan",2);

		enumFn.setKeyable(true);
		enumFn.setStorable(true);
		addAttribute(mathOperation);		


		input =numFn.create("input","in",MFnNumericData::kDouble);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(input);

 



		inverseFunction =numFn.create("inverseFunction","if",MFnNumericData::kBoolean);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(inverseFunction);


		



		outputValue =numFn.create("outputValue","ov",MFnNumericData::kDouble);
		numFn.setKeyable(false);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(outputValue);
			

		attributeAffects(input,outputValue);
		attributeAffects(inverseFunction,outputValue);
		attributeAffects(mathOperation,outputValue);


		return MS::kSuccess;
	

}


MStatus MG_trigonometry::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
	
		if (plug==outputValue)

		{	
			double inputV = dataBlock.inputValue(input).asDouble();			
			int operationV = dataBlock.inputValue(mathOperation).asInt();
			bool inverseV = dataBlock.inputValue(inverseFunction).asBool();
			
			double outV=0;

			if ((operationV==0) && (inverseV==1))
			{
				if (inputV>1)
				{
					outV=90;
				}
				else if (inputV<-1){
					outV=-90;
				}else{

					outV= asin(inputV)*toDeg;
				}
			}
			else if ((operationV==0) && (inverseV==0))	
			{
			outV= sin(inputV*toRad);
			}


			else if ((operationV==1) && (inverseV==1))
			{
				if (inputV>1)
				{
					outV=0;
				}
				else if (inputV<-1){
					outV=180;
				}else{

					outV= acos(inputV)*toDeg;
				}
			}
			else if ((operationV==1) && (inverseV==0))	
			{
				outV= cos(inputV*toRad);
			}


			else if ((operationV==2) && (inverseV==1))
			{
					
					outV= atan(inputV)*toDeg;
				
			}
			else if ((operationV==2) && (inverseV==0))	
			{	if (inputV>90)
				{
					outV=99999;
				}
				else if (inputV<-90){
					outV=-99999;
				}else{
				

				outV = tan(inputV*toRad);
				}
				
			}

		
		
			

			
					
		
		dataBlock.outputValue(outputValue).set(outV);
		dataBlock.outputValue(outputValue).setClean();


			

		}


		
		return MS::kSuccess;
	}









