#include "MG_jiggleVector.h"
#include <maya/MArrayDataHandle.h>
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
#include <maya/MFloatVector.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MVector.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>

using namespace std;

MTypeId MG_jiggleVector::typeId( 0x800002 );

//declaring needed objects


MObject MG_jiggleVector::outputX;
MObject MG_jiggleVector::outputY;
MObject MG_jiggleVector::outputZ;
MObject MG_jiggleVector::output;
MObject MG_jiggleVector::startPositionX; 
MObject MG_jiggleVector::startPositionY;
MObject MG_jiggleVector::startPositionZ;
MObject MG_jiggleVector::startPosition;
MObject MG_jiggleVector::damping;
MObject MG_jiggleVector::targetVector;
MObject MG_jiggleVector::targetVectorX;
MObject MG_jiggleVector::targetVectorY;
MObject MG_jiggleVector::targetVectorZ;
MObject MG_jiggleVector::stiffness;
MObject MG_jiggleVector::time;
MObject MG_jiggleVector::targetMatrix;
MObject MG_jiggleVector::useStartFrame ;
MObject MG_jiggleVector::startFrame ;
MObject MG_jiggleVector::reset;
MObject MG_jiggleVector::clampMax;
MObject MG_jiggleVector::clampMin;
MObject MG_jiggleVector::offset;
MObject MG_jiggleVector::clampRange;
MObject MG_jiggleVector::useLocalOutput;
MObject MG_jiggleVector::scaleFix;

const double PI=3.14159265358979323846264338327950288419716939937510;

double MG_jiggleVector::smoothSthep (double a , double b , double t)
{
	if (t < a )
	{
		return a;
	} 
	else if (t > b )
	{
		return b;
	
	}
	double rangeV = b -a ;
	double final = (cos(PI +((((t - a )/rangeV)*90)*PI/180))+1);
	double remap = ( a + (final * rangeV )) ;
	return remap;
}

//Class
MG_jiggleVector::MG_jiggleVector()
	
	{
		init = 0;    
		timeStored = 0;
		currentPos.x = 0;
		currentPos.y = 0;
		currentPos.z = 0;
			

		previousPos.x = 0;
		previousPos.y = 0;
		previousPos.z = 0;


	}



void* MG_jiggleVector::creator()
{

	return new MG_jiggleVector();
}

MStatus MG_jiggleVector::initialize()
	{ 
		//This is the nurbs input attribute
		MFnTypedAttribute typedFn;
		MFnCompoundAttribute compund;
		MFnNumericAttribute numFn;
		MFnMatrixAttribute    matrixFn;

		
		outputX = numFn.create("outputX","ox",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputX);

		outputY = numFn.create("outputY","oy",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputY);
		

		outputZ = numFn.create("outputZ","oz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputZ);

		
		output= compund.create("output","out");
		compund.addChild(outputX);
		compund.addChild(outputY); 
		compund.addChild(outputZ);
		addAttribute(output);


		startPositionX = numFn.create("startPositionX","spx",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(startPositionX);

		startPositionY = numFn.create("startPositionY","spy",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(startPositionY);
		

		startPositionZ = numFn.create("startPositionZ","spz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(startPositionZ);

		
		startPosition= compund.create("startPosition","sp");
		compund.addChild(startPositionX);
		compund.addChild(startPositionY);
		compund.addChild(startPositionZ);
		addAttribute(startPosition);


		targetVectorX = numFn.create("targetVectorX","tx",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(targetVectorX);

		targetVectorY = numFn.create("targetVectorY","ty",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(targetVectorY);
		

		targetVectorZ = numFn.create("targetVectorZ","tz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(targetVectorZ);




		
		targetVector= compund.create("targetVector","tav");
		compund.addChild(targetVectorX);
		compund.addChild(targetVectorY);
		compund.addChild(targetVectorZ);
		addAttribute(targetVector);

		damping = numFn.create("damping","dmp",MFnNumericData::kDouble,0.5);
		numFn.setMin(0);
		numFn.setMax(1);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(damping);

		stiffness = numFn.create("stiffness","st",MFnNumericData::kDouble,0.5);
		numFn.setMin(0);
		numFn.setMax(1);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(stiffness);

		time = numFn.create("time","tim",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(time);

		useStartFrame = numFn.create("useStartFrame","usf",MFnNumericData::kBoolean,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(useStartFrame);

		startFrame = numFn.create("startFrame","stf",MFnNumericData::kInt,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(startFrame);

		reset = numFn.create("reset","res",MFnNumericData::kBoolean,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(reset);


		clampRange = numFn.create("clampRange","clr",MFnNumericData::kBoolean,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(clampRange);


		clampMax = numFn.create("clampMax","cma",MFnNumericData::kDouble,1);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(clampMax);

		clampMin = numFn.create("clampMin","cmi",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(clampMin);

		targetMatrix =matrixFn.create("targetMatrix","tm");
		addAttribute(targetMatrix); 

		offset = numFn.create("offset","off",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(offset);


		useLocalOutput = numFn.create("useLocalOutput","ulo",MFnNumericData::kBoolean ,1);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(useLocalOutput);

		scaleFix = numFn.create("scaleFix","scf",MFnNumericData::kBoolean,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(scaleFix);


		attributeAffects ( targetVector , output ) ;
		attributeAffects ( damping , output ) ;
		attributeAffects ( stiffness , output ) ;
		attributeAffects ( time , output ) ;
		attributeAffects ( targetMatrix , output ) ;
		attributeAffects ( damping , output ) ;
		attributeAffects ( useStartFrame , output ) ;
		attributeAffects ( startFrame , output ) ;
		attributeAffects ( reset , output ) ;
		attributeAffects ( clampMax , output ) ;
		attributeAffects ( offset , output ) ;
		attributeAffects ( clampMin , output ) ;
		attributeAffects ( startPosition , output ) ;
		attributeAffects ( clampRange , output ) ;
		attributeAffects ( useLocalOutput , output ) ;
		attributeAffects ( scaleFix , output ) ;
		return MS::kSuccess;
	}
MStatus MG_jiggleVector::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		if (plug == output)
		{
		
			double dampingV = dataBlock.inputValue(damping).asDouble();
			double stiffnessV = dataBlock.inputValue(stiffness).asDouble();
			MVector targetVectorV = dataBlock.inputValue(targetVector).asVector();
			double timeV = dataBlock.inputValue(time).asDouble();
			MMatrix targetMatrixV = dataBlock.inputValue(targetMatrix).asMatrix();
			double useStartFrameV = dataBlock.inputValue(useStartFrame).asBool();
			double startFrameV = dataBlock.inputValue(startFrame).asDouble();
			double resetV = dataBlock.inputValue(reset).asBool();
			double clampMaxV = dataBlock.inputValue(clampMax).asDouble();
			double clampMinV = dataBlock.inputValue(clampMin).asDouble();
			double offsetV = dataBlock.inputValue(offset).asDouble();
			double clampRangeV = dataBlock.inputValue(clampRange).asBool();
			MVector startPositionV = dataBlock.inputValue(startPosition).asVector();
			bool scaleFixV = dataBlock.inputValue ( scaleFix ).asBool() ;
			bool useLocalOutputV = dataBlock.inputValue(useLocalOutput).asBool();
		


			if (init == 0)
			{


				init = 1;
				currentPos.x = targetMatrixV[3][0];
				currentPos.y = targetMatrixV[3][1];
				currentPos.z = targetMatrixV[3][2];
			

				previousPos.x = targetMatrixV[3][0];
				previousPos.y = targetMatrixV[3][1];
				previousPos.z = targetMatrixV[3][2];

				timeStored = 0;

			}



			if ( resetV == 1 )
			{
				dataBlock.outputValue(output).set((targetVectorV.x *offsetV)
												, (targetVectorV.y *offsetV) 
												,(targetVectorV.z *offsetV));
				dataBlock.outputValue(output).setClean();	
				return MS::kSuccess;
				
			
			}


			if ((useStartFrameV == 1) && ( startFrameV == timeV ))
			{
				
			   dataBlock.outputValue(output).set(startPositionV.x +(targetVectorV.x *offsetV ), startPositionV.y + (targetVectorV.y *offsetV) ,startPositionV.z + (targetVectorV.z *offsetV));
			   dataBlock.outputValue(output).setClean();	
			  return MS::kSuccess;
			}



			
			MPoint currentMatrixPose ;
			currentMatrixPose.x = targetMatrixV[3][0];
			currentMatrixPose.y = targetMatrixV[3][1];
			currentMatrixPose.z = targetMatrixV[3][2];


			MVector velocity = (currentPos - previousPos ) * ( 1 - dampingV);
			MPoint newPosition = currentPos + velocity;
			MPoint  targetForce = ( currentMatrixPose - newPosition ) * stiffnessV ;
			newPosition += targetForce ;


			targetVectorV.normalize();
			MVector newPositionVec (newPosition - currentMatrixPose );  

			double projectedVec ( newPositionVec * targetVectorV);
			 

			if (clampRangeV == 1 )
			{	

				if (projectedVec < clampMinV )
				{
			
				projectedVec = clampMinV;

				}

				else if (projectedVec > clampMaxV )
				{
			
				projectedVec = clampMaxV; 
				}

			}

			projectedVec += offsetV;

			MVector scaledVec ( targetVectorV * projectedVec ) ;

			//Scale fix 
			if (scaleFixV == 1 ) 
			{
			MVector scaleMatrixV (targetMatrixV[0][0] , targetMatrixV[0][1] , targetMatrixV[0][2] ) ;
			scaledVec *= scaleMatrixV.length() ;
			}

			previousPos = currentPos;
			currentPos =  newPosition;

			MVector matrixPoseVector (currentMatrixPose);

			if (useLocalOutputV == 0 ) 
			{
			scaledVec += matrixPoseVector ;
			}
			dataBlock.outputValue(output).set(scaledVec.x  , scaledVec.y  ,scaledVec.z );
			dataBlock.outputValue(output).setClean();		
		
		}



		return MS::kSuccess;
	}





