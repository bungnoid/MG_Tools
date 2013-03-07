#include "MG_softIk.h"
#include <maya/MArrayDataHandle.h>
#include <maya/MFnStringData.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFloatVector.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MVector.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>
#include <math.h>

using namespace std;

MTypeId MG_softIk::typeId( 0x80015 );

//declaring needed objects


MObject MG_softIk::startMatrix ;
MObject MG_softIk::endMatrix ;
MObject MG_softIk::upInitLength ;
MObject MG_softIk::downInitLength ;
MObject MG_softIk::upScale ;
MObject MG_softIk::downScale ;
MObject MG_softIk::stretch ;
MObject MG_softIk::softDistance ;
MObject MG_softIk::outputTranslateX;
MObject MG_softIk::outputTranslateY;
MObject MG_softIk::outputTranslateZ;
MObject MG_softIk::outputTranslate;
MObject MG_softIk::slide;
MObject MG_softIk::globalScale;
const double PI=3.14159265358979323846264338327950288419716939937510;





double MG_softIk::smoothSthep (double a , double b , double t)
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
MG_softIk::MG_softIk()
	
	{


	}



void* MG_softIk::creator()
{

	return new MG_softIk();
}

MStatus MG_softIk::initialize()
	{ 		
	  
	  //This is the nurbs input attribute
	  MFnTypedAttribute typedFn;
	  MFnCompoundAttribute compund;
	  MFnNumericAttribute numFn;
	  MFnMatrixAttribute    matrixFn;
	  
	  
	  
	  startMatrix =matrixFn.create("startMatrix","stm");
	  addAttribute(startMatrix); 
		
	  endMatrix =matrixFn.create("endMatrix","enm");
	  addAttribute(endMatrix); 
	  
	  
	  upInitLength = numFn.create("upInitLength","uil",MFnNumericData::kDouble,0);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  addAttribute(upInitLength);
	  

	  
	  
	  downInitLength = numFn.create("downInitLength","dil",MFnNumericData::kDouble,0);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  addAttribute(downInitLength);
	  

	  globalScale = numFn.create("globalScale","gb",MFnNumericData::kDouble,0);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  numFn.setMin(0.001);
	  addAttribute(globalScale);

	  softDistance = numFn.create("softDistance","sd",MFnNumericData::kDouble,0);
	  numFn.setMin(0.001);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  addAttribute(softDistance);

	  stretch = numFn.create("stretch","str",MFnNumericData::kDouble,0);
	  numFn.setMin(0.0);
	  numFn.setMax(1.0);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  addAttribute(stretch);
	  
	  slide = numFn.create("slide","sld",MFnNumericData::kDouble,0.5);
	  numFn.setMin(0.0);
	  numFn.setMax(1.0);
	  numFn.setStorable(true);
	  numFn.setKeyable(true);
	  addAttribute(slide);
	  
	  upScale = numFn.create("upScale","ups",MFnNumericData::kDouble,1);
	  numFn.setStorable(false);
	  numFn.setKeyable(false);
	  numFn.setWritable(false);
	  addAttribute(upScale);
	  
	  

	  
	  downScale = numFn.create("downScale","dws",MFnNumericData::kDouble,1);
	  numFn.setStorable(false);
	  numFn.setKeyable(false);
	  numFn.setWritable(false);
	  addAttribute(downScale);
	
	  
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
	  compund.setStorable(false);
	  compund.setKeyable(false);
	  compund.setWritable(false);
	  addAttribute(outputTranslate);
	  
	  
	  attributeAffects( startMatrix ,outputTranslate) ;
	  attributeAffects( endMatrix ,outputTranslate) ;
	  attributeAffects( softDistance ,outputTranslate) ;
	  attributeAffects( stretch ,outputTranslate) ;
	  attributeAffects( slide ,outputTranslate) ;
	  attributeAffects( globalScale ,outputTranslate) ;
	  
	  attributeAffects( startMatrix ,upScale) ;
	  attributeAffects( endMatrix ,upScale) ;
	  attributeAffects( stretch ,upScale) ;
	  attributeAffects( softDistance ,upScale) ;
	  attributeAffects( slide ,upScale) ;
	  attributeAffects( globalScale ,upScale) ;

	  attributeAffects( startMatrix ,downScale) ;
	  attributeAffects( endMatrix ,downScale) ;
	  attributeAffects( softDistance ,downScale) ;
	  attributeAffects( stretch ,downScale) ;
	  attributeAffects( slide ,downScale) ;
	  attributeAffects( globalScale ,downScale) ;

 	  return MS::kSuccess;
	}
MStatus MG_softIk::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		
		//Get data 
		if ((plug == outputTranslate) ||(plug == downScale) ||(plug == upScale) )
		{
		
		MMatrix startMatrixV = dataBlock.inputValue(startMatrix).asMatrix();
		MMatrix endMatrixV = dataBlock.inputValue(endMatrix).asMatrix();
		double upInitLengthV = dataBlock.inputValue(upInitLength).asDouble();
		double downInitLengthV = dataBlock.inputValue(downInitLength).asDouble();
		double softDistanceV = dataBlock.inputValue(softDistance).asDouble();
		double stretchV= dataBlock.inputValue(stretch).asDouble();
		double slideV = dataBlock.inputValue(slide).asDouble();
		double globalScaleV  = dataBlock.inputValue(globalScale).asDouble();
		upInitLengthV = upInitLengthV*(slideV*2)*globalScaleV ;
		downInitLengthV = downInitLengthV*((1 - slideV)*2)*globalScaleV;
 		double chainLength = upInitLengthV + downInitLengthV ;
		
		
		MVector startVector (startMatrixV[3][0] , startMatrixV[3][1] , startMatrixV[3][2] );
		MVector endVector  (endMatrixV[3][0] , endMatrixV[3][1] , endMatrixV[3][2] );
		MVector currentLengthVector  = endVector -  startVector ;
		
		double  currentLength = currentLengthVector.length() ;
		double startSD = chainLength - softDistanceV;
		
		double stretchParam = 1;
		double upScaleOut = 1 ;
		double downScaleOut = 1 ;
		
		if (startSD <= currentLength)
		{
		
		  if (softDistanceV != 0 )
		  {
		  double expParam =  ( currentLength - startSD) / softDistanceV;
		  expParam*= -1 ;
		  double softLength = ( (softDistanceV *(1 - exp ( expParam)) )+  startSD );
		  currentLengthVector.normalize();
		  currentLengthVector*=softLength ;
		  
		   if (stretchV != 0 )
		  {
		    
		     stretchParam = (currentLength/softLength  );
		     double delta = (stretchParam - 1); 
		     delta*=stretchV;
		     stretchParam = 1*(1 + delta);
		     currentLengthVector  *=(1 + delta );
		      
		  }
		  }
		  
		  
		}
		

		//slide computing
		
		upScaleOut = (slideV*2) *stretchParam ;
		downScaleOut = ((1 - slideV)*2)*stretchParam;
		
		
		MVector outVec =  startVector + currentLengthVector;
		dataBlock.outputValue(outputTranslate).setMVector(outVec);
		dataBlock.outputValue(outputTranslate).setClean();
		
		dataBlock.outputValue(downScale).set(downScaleOut);
		dataBlock.outputValue(downScale).setClean();
		
		
		dataBlock.outputValue(upScale).set(upScaleOut);
		dataBlock.outputValue(upScale).setClean();
		
		

		}
		return MS::kSuccess;
	}





