

#include <maya/MFnMatrixAttribute.h>
#include <maya/MMatrix.h>
#include <maya/MFloatMatrix.h>
#include <maya/MPoint.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFloatPoint.h>
#include <math.h>
#include <sstream>
#include <maya/MGlobal.h>
#include <maya/MDataHandle.h>
#include <maya/MMatrix.h>
#include <maya/MFnCompoundAttribute.h>
#include <MG_vector.h>

  
  

MObject MG_vector::inputM1;
MObject MG_vector::inputM2;
MObject MG_vector::magnitude;
MObject MG_vector::oVecX;
MObject MG_vector::oVecY;
MObject MG_vector::oVecZ;
MObject MG_vector::oVec;
MObject MG_vector::normalize;


MTypeId MG_vector::typeId( 0x800003 );

void* MG_vector::creator()
{

	return new MG_vector();
}

MStatus MG_vector::initialize(){

		//Create the matrix input attribute 

		//MAtrix one attribute
		MFnMatrixAttribute matrixInAttr;
		inputM1= matrixInAttr.create("inputMatrix1","m1");


		addAttribute(inputM1);

		//Matrix two attribute

		MFnMatrixAttribute matrixInAttr2;
		inputM2= matrixInAttr2.create("inputMatrix2","m2");

		addAttribute(inputM2);



		//Magnitude attr

		MFnNumericAttribute floatAttr;
		magnitude=floatAttr.create("magnitude","m",MFnNumericData::kDouble);
		addAttribute(magnitude);

		//Normalize attr

		MFnNumericAttribute normAttr;
		normalize=normAttr.create("normalize","n",MFnNumericData::kBoolean );
		addAttribute(normalize);


		//Output vector
		
		MFnNumericAttribute oVecXAttr;
		oVecX= oVecXAttr.create("outputVectorX","vx",MFnNumericData::kDouble);
		addAttribute(oVecX);
	
		MFnNumericAttribute oVecYAttr;
		oVecY= oVecYAttr.create("outputVectorY","vy",MFnNumericData::kDouble);
		addAttribute(oVecY);
		
		MFnNumericAttribute oVecZAttr;
		oVecZ= oVecZAttr.create("outputVectorZ","vZ",MFnNumericData::kDouble);
		addAttribute(oVecZ);

		//Output vector compound attribute 

		MFnCompoundAttribute FoVec;
		oVec= FoVec.create("outputVector","ov");
		FoVec.addChild(oVecX);
		FoVec.addChild(oVecY);
		FoVec.addChild(oVecZ);
		addAttribute(oVec);


		//Attribute affecting
		
		attributeAffects(inputM1,magnitude);
		attributeAffects(inputM2,magnitude);
		attributeAffects(inputM1,oVecX);
		attributeAffects(inputM1,oVecY);
		attributeAffects(inputM1,oVecZ);
		attributeAffects(inputM2,oVecX);
		attributeAffects(inputM2,oVecY);
		attributeAffects(inputM2,oVecZ);
		attributeAffects(normalize,oVecX);
		attributeAffects(normalize,oVecY);
		attributeAffects(normalize,oVecZ);


		return MS::kSuccess;
	}


MStatus MG_vector::compute(const MPlug& plug,MDataBlock& dataBlock)
	{	MStatus returnStatus;
		if ((plug==magnitude)||(plug==oVec)||(plug==oVecX)||(plug==oVecY)||(plug==oVecZ))
			/*get time */
		{
		

			//Data handles for input attributes


			MDataHandle m1Data = dataBlock.inputValue(inputM1,&returnStatus);
			MDataHandle m2Data = dataBlock.inputValue(inputM2,&returnStatus);
			MDataHandle normData = dataBlock.inputValue(normalize,&returnStatus);
			MMatrix in1 = m1Data.asMatrix();
			MMatrix in2 = m2Data.asMatrix();
			bool norm =normData.asBool();
			

			

			//Debugging display
			//MGlobal::displayInfo(MString("MMatrix1=")+in1[3][0]+" "+in1[3][1]+" " +in1[3][2]);
			//MGlobal::displayInfo(MString("MMatrix2=")+in2[3][0]+" "+in2[3][1]+" " +in2[3][2]);


			//Creating point 
			
			MPoint  point1 ( in1[3][0], in1[3][1], in1[3][2]);
			MPoint  point2 ( in2[3][0], in2[3][1], in2[3][2]);

			//Debugging display
			//MGlobal::displayInfo(MString("MPoint1=")+point1[0]+" "+point1[1]+" " +point1[2]);
			//MGlobal::displayInfo(MString("MPoint2=")+point2[0]+" "+point2[1]+" " +point2[2]);	
			
			//Calculating magnitude
			 
			double distance = sqrt(pow((point1[0]-point2[0]),2)+pow((point1[1]-point2[1]),2)+pow((point1[2]-point2[2]),2));
			//float distance = point1.distanceTo(point2);


			//Calculating vector 
			 
			//if statement for normalization


			double xVal,yVal,zVal;
			

			if (distance >0.001)
			{
				if (norm ==false )

				{
				

				xVal= in2[3][0]-in1[3][0];
				yVal= in2[3][1]-in1[3][1];
				zVal= in2[3][2]-in1[3][2];

				
				}else if (norm ==true){

				xVal= (in2[3][0]-in1[3][0])/distance;
				yVal= (in2[3][1]-in1[3][1])/distance;
				zVal= (in2[3][2]-in1[3][2])/distance;
				}
			}else{
			xVal=0;
			yVal=0;
			zVal=0;
			}


			//Output data handle
			MDataHandle outputHandle = dataBlock.outputValue(magnitude,&returnStatus);
			MDataHandle ValOut = dataBlock.outputValue(oVec,&returnStatus);	

			

			outputHandle.set(distance);
			ValOut.set(xVal,yVal,zVal);
			dataBlock.setClean(magnitude);
			dataBlock.setClean(oVec);



		}else{
			return MS::kUnknownParameter;
		
		};
		return MS::kSuccess;
	}



