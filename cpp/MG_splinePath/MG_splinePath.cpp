// HEADER FILES:
#include "MG_splinePath.h"
#include <maya/MIOStream.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MVectorArray.h>
#include <maya/MDoubleArray.h>
#include <cmath>

MObject MG_splinePath::inputCurve;
MObject MG_splinePath::firstUpVec;
MObject MG_splinePath::firstUpVecX;
MObject MG_splinePath::firstUpVecY;
MObject MG_splinePath::firstUpVecZ;
MObject MG_splinePath::outputTranslateX;
MObject MG_splinePath::outputTranslateY;
MObject MG_splinePath::outputTranslateZ;
MObject MG_splinePath::outputTranslate;
MObject MG_splinePath::outputRotateX;
MObject MG_splinePath::outputRotateY;
MObject MG_splinePath::outputRotateZ;
MObject MG_splinePath::outputRotate;
MObject MG_splinePath::numberOfSamples;
MObject MG_splinePath::numberOfOutput;
MObject MG_splinePath::parentMatrix;
MObject MG_splinePath::offset;




MTypeId MG_splinePath::typeId( 0x800006 );

// FOR CREATING AN INSTANCE OF THIS NODE:
void *MG_splinePath::creator()
{
   return new MG_splinePath();
}


// INITIALIZES THE NODE BY CREATING ITS ATTRIBUTES:
MStatus MG_splinePath::initialize()
{
    MFnTypedAttribute typedFn;
    MFnCompoundAttribute compund;
    MFnNumericAttribute numFn;
    MFnMatrixAttribute    matrixFn;
    MFnUnitAttribute    uAttr;
    
    
    
    inputCurve  = typedFn.create( "inputCurve", "ic", MFnData::kNurbsCurve );
    addAttribute(inputCurve);
    
    
    numberOfSamples = numFn.create("numberOfSamples","nos",MFnNumericData::kInt,1);
    numFn.setMin(1);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(numberOfSamples);
    
    numberOfOutput = numFn.create("numberOfOutput","noo",MFnNumericData::kInt,1);
    numFn.setMin(1);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(numberOfOutput);
    
    
    firstUpVecX = numFn.create("firstUpVecX","fux",MFnNumericData::kDouble,0);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(firstUpVecX);

    firstUpVecY = numFn.create("firstUpVecY","fuy",MFnNumericData::kDouble,1);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(firstUpVecY);
    

    firstUpVecZ = numFn.create("firstUpVecZ","fuz",MFnNumericData::kDouble,0);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(firstUpVecZ);

    
    firstUpVec= compund.create("firstUpVec","fu");
    compund.addChild(firstUpVecX);
    compund.addChild(firstUpVecY); 
    compund.addChild(firstUpVecZ);
    addAttribute(firstUpVec);    
    
    
    
    
    parentMatrix =matrixFn.create("parentMatrix","parm");

		addAttribute(parentMatrix); 
    
    
    offset = numFn.create("offset","off",MFnNumericData::kDouble,0);
    numFn.setStorable(true);
    numFn.setKeyable(true);
    addAttribute(offset);
  
    outputTranslateX = numFn.create("outputTranslateX","otx",MFnNumericData::kDouble,0);
    numFn.setStorable(false);
    numFn.setKeyable(false);
    numFn.setWritable(false);
    addAttribute(outputTranslateX);

    outputTranslateY = numFn.create("outputTranslateY","oty",MFnNumericData::kDouble,0);
    numFn.setStorable(false);
    numFn.setWritable(false);
    numFn.setKeyable(false);
    addAttribute(outputTranslateY);
    

    outputTranslateZ = numFn.create("outputTranslateZ","otz",MFnNumericData::kDouble,0);
    numFn.setStorable(false);
    numFn.setKeyable(false);
    numFn.setWritable(false);
    addAttribute(outputTranslateZ);

    
    outputTranslate= compund.create("outputTranslate","ot");
    compund.addChild(outputTranslateX);
    compund.addChild(outputTranslateY); 
    compund.addChild(outputTranslateZ);
    compund.setArray(true);
    compund.setStorable(false);
    compund.setKeyable(false);
    compund.setWritable(false);

    addAttribute(outputTranslate);
    
    
    outputRotateX = uAttr.create("outputRotateX","orx",MFnUnitAttribute::kAngle,0.0);
    numFn.setStorable(false);
    numFn.setWritable(false);
    numFn.setKeyable(false);
    addAttribute(outputRotateX);

    outputRotateY = uAttr.create("outputRotateY","ory",MFnUnitAttribute::kAngle,0.0);
    numFn.setStorable(false);
    numFn.setKeyable(false);
    numFn.setWritable(false);

    addAttribute(outputRotateY);
    

    outputRotateZ = uAttr.create("outputRotateZ","orz",MFnUnitAttribute::kAngle,0.0);
    numFn.setStorable(false);
    numFn.setKeyable(false);
    numFn.setWritable(false);
    
    addAttribute(outputRotateZ);

    
    outputRotate= compund.create("outputRotate","or");
    compund.addChild(outputRotateX);
    compund.addChild(outputRotateY); 
    compund.addChild(outputRotateZ);
    compund.setArray(true);
    compund.setStorable(false);
    compund.setKeyable(false);
    compund.setWritable(false);
    addAttribute(outputRotate);
    
  
    
    
    
    
    
    
    
    
    
    attributeAffects (offset , outputTranslate);
    attributeAffects (offset , outputRotate);
    
    
    attributeAffects (parentMatrix , outputTranslate);
    attributeAffects (parentMatrix , outputRotate);
    
    attributeAffects (inputCurve , outputTranslate);
    attributeAffects (inputCurve , outputRotate);
    
    
    attributeAffects (firstUpVec , outputTranslate);
    attributeAffects (firstUpVec , outputRotate);
    
    attributeAffects (numberOfSamples , outputTranslate);
    attributeAffects (numberOfSamples , outputRotate);
    
    attributeAffects (numberOfOutput , outputTranslate);
    attributeAffects (numberOfOutput , outputRotate);
    
       
   return MS::kSuccess;
}


// COMPUTE METHOD'S DEFINITION:
MStatus MG_splinePath::compute(const MPlug &plug, MDataBlock &data)
{
    //Get the data
    
//     if ((plug == outputTranslate) || (plug == outputRotate))
//     {
    
    MObject inputCurveV = data.inputValue (inputCurve).asNurbsCurve();
    MVector firstUpVecV = data.inputValue(firstUpVec).asVector();
    firstUpVecV.normalize();
    int numberOfSamplesV = data.inputValue(numberOfSamples).asInt();
    int numberOfOutputV = data.inputValue(numberOfOutput).asInt();
    MMatrix parentMatrixV = data.inputValue(parentMatrix).asMatrix();
    double offsetV = data.inputValue(offset).asDouble();
    
    MVectorArray normals;
    normals.setLength(numberOfSamplesV);
    
    MFnNurbsCurve curveFn(inputCurveV);
    double length = curveFn.length();
    double subvidsSample = length/double(numberOfSamplesV)  ;
    double subvidsOutput = length/double(numberOfOutputV);

    

    MPointArray outTArray ;
    outTArray.setLength(numberOfSamplesV);
    
    MDoubleArray paramValues;
    paramValues.setLength(numberOfSamplesV);
    
    //GetMaxUv 
    
    
    
    //First sample the curve
    
   
    MVector currentNormal = firstUpVecV;
    for ( int i = 0 ; i < numberOfSamplesV ; i++ )
    {
      
      double param = curveFn.findParamFromLength(i*subvidsSample);
      MVector tan = curveFn.tangent(param , MSpace::kObject);
      MPoint outPos;
      curveFn.getPointAtParam(param , outPos , MSpace::kObject);
      tan.normalize();
      MVector cross1 = currentNormal^tan;
      cross1.normalize() ;
      MVector cross2 =  tan^cross1;
      cross2.normalize();
      currentNormal = cross2 ;
      normals[i] = cross2;

      
    }
    

    MArrayDataHandle outTH = data.outputArrayValue (outputTranslate);
    MArrayDataHandle outRH = data.outputArrayValue (outputRotate);
    outTH.jumpToArrayElement(0);
    outRH.jumpToArrayElement(0);
    
    if ((outTH.elementCount() == numberOfOutputV) && (outRH.elementCount() == numberOfOutputV))
    {
		
		for ( int i = 0 ; i < numberOfOutputV ; i++  , outTH.next() , outRH.next())
		{
	  
			//Translate
			MPoint outTranslate;
	  
			double tempLength = double(i)*subvidsOutput ;
			double  timesLength = ( offsetV / length);
			int  timesLengthFloor = 0;
			if (offsetV > 0 )
			{
			timesLengthFloor = floor(timesLength) ;
			}
			else
			{
			  timesLengthFloor = ceil(timesLength) ;
			  
			}
			
			offsetV-= (length*timesLengthFloor);

		

			
	
			tempLength+=offsetV;
			if (tempLength < 0)
			{
			  
			  tempLength = length + tempLength;
			  
			  
			}
			
			else if (tempLength > length )
			{
			  tempLength -= length; 
			  
			  
			}
			
			double param = curveFn.findParamFromLength(tempLength);
			
			
			curveFn.getPointAtParam(param , outTranslate , MSpace::kObject);
			outTArray[i] = outTranslate;
	  
			double toRound = tempLength/subvidsSample;
			int  sampleIndex = floor(toRound) ;
			
			MVector tan = curveFn.tangent(param , MSpace::kObject);
			MVector cross1 = normals[sampleIndex] ^ tan;
			cross1.normalize();
			MVector cross2 = tan^cross1 ;
			
			cross2.normalize();
			
			
			double myMatrix[4][4]={	{ tan.x, tan.y , tan.z, 0},
						{ cross2.x, cross2.y , cross2.z, 0},
						{cross1.x, cross1.y , cross1.z, 0},
						{ outTranslate[0], outTranslate[1] , outTranslate[2], 1}};
				  
				  
			MMatrix rotMatrix (myMatrix);
			rotMatrix*=parentMatrixV;
			MTransformationMatrix matrixFn(rotMatrix);
			double angles[3];
			MTransformationMatrix::RotationOrder rotOrder;
			rotOrder =MTransformationMatrix::kXYZ;
			matrixFn.getRotation(angles,rotOrder,MSpace::kObject );

			double radX,radY,radZ;

			radX=angles[0]; 
			radY=angles[1];
			radZ=angles[2];
	  
	    
			MDataHandle currentT = outTH.outputValue();
			MDataHandle currentR = outRH.outputValue();
			MVector tempOut (rotMatrix[3][0],rotMatrix[3][1],rotMatrix[3][2]);
			currentT.setMVector(tempOut);
	    
	 
			currentR.set(radX,radY,radZ);
			
		}
	
		}
		else
		{
		  //MGlobal::dislayError("not enough output arrays index");
      
      
		}
    
    outTH.setAllClean();
    outRH.setAllClean();
//     }// end if ((plug == outputTranslate) || (plug == outputRotate))
   return MS::kSuccess;
}


















