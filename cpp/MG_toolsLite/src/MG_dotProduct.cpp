


#include <maya/MFnNumericAttribute.h>
#include <maya/MFloatPoint.h>
#include <maya/MGlobal.h>
#include <maya/MFloatArray.h>
#include <math.h>
#include <MG_dotProduct.h>
#include <MG_vecMath.h>
#include <maya/MFnCompoundAttribute.h>

#define PI 3.14159265


  


	 MObject MG_dotProduct::vector1;
	 MObject MG_dotProduct::vector2;
	 MObject MG_dotProduct::dotProductA;
	 MObject MG_dotProduct::normalize;
	 MObject MG_dotProduct::dotProductMax;
	 MObject MG_dotProduct::proj1on2;
	 MObject MG_dotProduct::proj2on1;
	 MObject MG_dotProduct::angleInBetweenAttr;
	 MObject MG_dotProduct::angleX;
	 MObject MG_dotProduct::angleY;
	 MObject MG_dotProduct::angleZ;
	 MObject MG_dotProduct::projAxisX;
	 MObject MG_dotProduct::projAxisXa;
	 MObject MG_dotProduct::projAxisXb;
	 MObject MG_dotProduct::projAxisXc;
	 MObject MG_dotProduct::projAxisY;
	 MObject MG_dotProduct::projAxisYa;
	 MObject MG_dotProduct::projAxisYb;
	 MObject MG_dotProduct::projAxisYc;
	 MObject MG_dotProduct::projAxisZ;
	 MObject MG_dotProduct::projAxisZa;
	 MObject MG_dotProduct::projAxisZb;
	 MObject MG_dotProduct::projAxisZc;


MTypeId MG_dotProduct::typeId( (0x80008) );

void* MG_dotProduct::creator()
{

	return new MG_dotProduct();
}

MStatus MG_dotProduct::initialize(){

//Input vector 1

		MFnNumericAttribute numericAttrFn;
		vector1 = numericAttrFn.createPoint("vector1","v1");
		addAttribute(vector1);
		numericAttrFn.setStorable(true);
 
		//Input vector 2

		vector2 = numericAttrFn.createPoint("vector2","v2");
		addAttribute(vector2);
		numericAttrFn.setStorable(true);


		//Projection axis attributes ,needs to be created as compound in order to set a default value 
		// X axis

		projAxisXa = numericAttrFn.create("xAxisProjectionX","xPrjx",MFnNumericData::kFloat,1);
		addAttribute(projAxisXa);
		numericAttrFn.setStorable(true);


		projAxisXb = numericAttrFn.create("xAxisProjectionY","xPrjy",MFnNumericData::kFloat,0);
		addAttribute(projAxisXa);
		numericAttrFn.setStorable(true);

		projAxisXc = numericAttrFn.create("xAxisProjectionZ","xPrjz",MFnNumericData::kFloat,0);
		addAttribute(projAxisXa);
		numericAttrFn.setStorable(true);



		MFnCompoundAttribute compund;
		projAxisX= compund.create("xAxisProjection","xproj");
		compund.addChild(projAxisXa);
		compund.addChild(projAxisXb);
		compund.addChild(projAxisXc);
		addAttribute(projAxisX);

		// Y axis

		projAxisYa = numericAttrFn.create("yAxisProjectionX","yPrjx",MFnNumericData::kFloat,0);
		addAttribute(projAxisYa);
		numericAttrFn.setStorable(true);


		projAxisYb = numericAttrFn.create("yAxisProjectionY","yPrjy",MFnNumericData::kFloat,1);
		addAttribute(projAxisYb);
		numericAttrFn.setStorable(true);

		projAxisYc = numericAttrFn.create("yAxisProjectionZ","yPrjz",MFnNumericData::kFloat,0);
		addAttribute(projAxisYc);
		numericAttrFn.setStorable(true);




		projAxisY= compund.create("yAxisProjection","yproj");
		compund.addChild(projAxisYa);
		compund.addChild(projAxisYb);
		compund.addChild(projAxisYc);
		addAttribute(projAxisY);

		// Z axis

		projAxisZa = numericAttrFn.create("zAxisProjectionX","zPrjx",MFnNumericData::kFloat,0);
		addAttribute(projAxisZa);
		numericAttrFn.setStorable(true);


		projAxisZb = numericAttrFn.create("zAxisProjectionY","zPrjy",MFnNumericData::kFloat,0);
		addAttribute(projAxisZb);
		numericAttrFn.setStorable(true);

		projAxisZc = numericAttrFn.create("zAxisProjectionZ","zPrjz",MFnNumericData::kFloat,1);
		addAttribute(projAxisZc);
		numericAttrFn.setStorable(true);




		projAxisZ= compund.create("zAxisProjection","zproj");
		compund.addChild(projAxisZa);
		compund.addChild(projAxisZb);
		compund.addChild(projAxisZc);
		addAttribute(projAxisZ);



		//normalize attribute 

		
		normalize=numericAttrFn.create("normalize","n",MFnNumericData::kBoolean );
		addAttribute(normalize);
		numericAttrFn.setStorable(true);


		//Output attribute that will hold the dot product value 

		dotProductA = numericAttrFn.create("dotProduct","dp",MFnNumericData::kFloat);
		addAttribute(dotProductA);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		//dot product max value

		dotProductMax = numericAttrFn.create("dotProductMaxValue","dpm",MFnNumericData::kFloat);
		addAttribute(dotProductMax);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		//Input vector1 projection on vector 2


		proj1on2 = numericAttrFn.createPoint("projectionV1onV2","pV1");
		addAttribute(proj1on2);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);


		//Input vector2 projection on vector 1


		proj2on1 = numericAttrFn.createPoint("projectionV2onV1","pV2");
		addAttribute(proj2on1);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);


		//angle inbetween

		angleInBetweenAttr = numericAttrFn.create("angleInBetween","aib",MFnNumericData::kFloat);
		addAttribute(angleInBetweenAttr);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		
		//Output attribute that will hold Xvalue of the angle inbetween
		angleX = numericAttrFn.create("angleX","ax",MFnNumericData::kFloat);
		addAttribute(angleX);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		//Output attribute that will hold Xvalue of the angle inbetween
		angleY = numericAttrFn.create("angleY","ay",MFnNumericData::kFloat);
		addAttribute(angleY);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		//Output attribute that will hold Xvalue of the angle inbetween
		angleZ = numericAttrFn.create("angleZ","az",MFnNumericData::kFloat);
		addAttribute(angleZ);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);
		

		//setting attribute affects
		attributeAffects(vector1,dotProductA);
		attributeAffects(vector2,dotProductA);
		attributeAffects(normalize,dotProductA);

		attributeAffects(vector1,dotProductMax);
		attributeAffects(vector2,dotProductMax);
		attributeAffects(normalize,dotProductMax);

		attributeAffects(vector1,proj1on2);
		attributeAffects(vector2,proj1on2);

		attributeAffects(vector1,proj2on1);
		attributeAffects(vector2,proj2on1);

		attributeAffects(vector1,angleInBetweenAttr);
		attributeAffects(vector2,angleInBetweenAttr);

		attributeAffects(vector1,angleX);
		attributeAffects(vector2,angleX);

		attributeAffects(vector1,angleY);
		attributeAffects(vector2,angleY);

		attributeAffects(vector1,angleZ);
		attributeAffects(vector2,angleZ);

		attributeAffects(projAxisXa,angleX);
		attributeAffects(projAxisXb,angleX);
		attributeAffects(projAxisXc,angleX);
		attributeAffects(projAxisYa,angleX);
		attributeAffects(projAxisYb,angleX);
		attributeAffects(projAxisYc,angleX);
		attributeAffects(projAxisZa,angleX);
		attributeAffects(projAxisZb,angleX);
		attributeAffects(projAxisZc,angleX);

		attributeAffects(projAxisXa,angleY);
		attributeAffects(projAxisXb,angleY);
		attributeAffects(projAxisXc,angleY);
		attributeAffects(projAxisYa,angleY);
		attributeAffects(projAxisYb,angleY);
		attributeAffects(projAxisYc,angleY);
		attributeAffects(projAxisZa,angleY);
		attributeAffects(projAxisZb,angleY);
		attributeAffects(projAxisZc,angleY);

		attributeAffects(projAxisXb,angleZ);
		attributeAffects(projAxisXc,angleZ);
		attributeAffects(projAxisYa,angleZ);
		attributeAffects(projAxisYb,angleZ);
		attributeAffects(projAxisYc,angleZ);
		attributeAffects(projAxisZa,angleZ);
		attributeAffects(projAxisZb,angleZ);
		attributeAffects(projAxisZc,angleZ);


		return MS::kSuccess;
	}


		MStatus MG_dotProduct::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		MStatus returnStatus;
		if ((plug==dotProductA)||
			(plug==dotProductMax)||
			(plug==proj1on2)||
			(plug==proj2on1)||
			(plug==angleInBetweenAttr)||
			(plug==angleX)||
			(plug==angleY)||
			(plug==angleZ))
			/*get time */
		
		{
				
			//creating handles to the input values

			MDataHandle vector1DataH = dataBlock.inputValue(vector1);
			MFloatPoint vector1V = vector1DataH.asFloatVector();
			
			MDataHandle vector2DataH = dataBlock.inputValue(vector2);
			MFloatPoint vector2V = vector2DataH.asFloatVector();

			MDataHandle xAxisH = dataBlock.inputValue(projAxisX);
			MFloatPoint xAxisData = xAxisH.asFloatVector();

			MDataHandle yAxisH = dataBlock.inputValue(projAxisY);
			MFloatPoint yAxisData = yAxisH.asFloatVector();

			MDataHandle zAxisH = dataBlock.inputValue(projAxisZ);
			MFloatPoint zAxisData = zAxisH.asFloatVector();
			
			MDataHandle normData = dataBlock.inputValue(normalize);
			bool norm =normData.asBool();
			

			//Creating some neededs variables

			float dotResult; // variable that will hold the dot product result
			float maxValue; //variable that will hold the dot product max value 
			float distance1; // variable that will hold the vector 1 lenght 
			float distance2; //variable that will hold the  vector 2 lenght
			float angleDeg;  //variable that will hold the  angle inbetween the two vectors
			//float cosRad ;   //variable that will hold the cosine value in radiants 
				
			//Dot product math 

			float vec1Array[3] = {vector1V[0],vector1V[1],vector1V[2]};
			vector <float> vec1 = makeVector(vec1Array) ;

			float vec2Array[3] = {vector2V[0],vector2V[1],vector2V[2]};
			vector <float> vec2 = makeVector(vec2Array) ;

			dotResult = vecDotProduct(vec1,vec2);
			distance1 = vectorLength(vec1);
			distance2 = vectorLength(vec2);
			maxValue = distance1*distance2;

			
			if (norm == 1) 

			{
				if (maxValue ==0)
				{
					dotResult=0;
				}else{
					dotResult = dotResult/maxValue;
				}
			} 
  
			


				
				

			//Projection v2 on v1

			float projV2=0;  //variable that will hold the value projection of v2 projected on v1
			vector <float> v1Norm; // variable that will hold the normalized v1 vector
			vector<float> v2Vec; // variable that will hold the projected vector

			if (distance1 != 0) 
			{
 
				projV2 = projVector(vec2,vec1);
				

				v1Norm = normVector(vec1);


				v2Vec = scalarVector(v1Norm,projV2);
				
				

			}else{

				//initialize the vector as 0 0 0
				float zeroVec2[3]= {0,0,0};
				v2Vec=makeVector(zeroVec2);
			}


			//Projection v1 on v2

			float projV1=0; //variable that will hold the value projection of v1 projected on v2
			vector <float> v2Norm;// variable that will hold the normalized v2 vector
			vector <float> v1Vec;// variable that will hold the projected vector

			if (distance2 != 0) 
			{
				projV1 = projVector(vec1,vec2);


				v2Norm = normVector(vec2);
				v1Vec = scalarVector(v2Norm,projV1);
			}else{
				//initialize the vector as 0 0 0
				float zeroVec1[3]= {0,0,0};
				v1Vec=makeVector(zeroVec1);
			}

			
			//Angle in between 


			if ((distance2*distance1)!=0)
			{
			angleDeg=angleInbetweenVector(vec1,vec2);
			}else{
				angleDeg=0;

			}

			//Angle inbetween splitted into X,Y,Z world rotation 
			
			//float dotResultV1X;
			// splitting inbetween angle into X Y Z rotation



			//converting axis from node into vector class
			float xAxisArray[3] = {xAxisData[0],xAxisData[1],xAxisData[2]};
			vector<float> xAxisVec = makeVector(xAxisArray) ;
			
			float yAxisArray[3] = {yAxisData[0],yAxisData[1],yAxisData[2]};
			vector<float> yAxisVec = makeVector(yAxisArray) ;

			float zAxisArray[3] = {zAxisData[0],zAxisData[1],zAxisData[2]};
			vector<float> zAxisVec = makeVector(zAxisArray) ;


			float angleProjXYDeg=0 ;
			float angleProjYZDeg=0 ;
			float angleProjXZDeg=0 ;

			// angle Z
			

			vector<float> projectedV1;
			vector<float> projectedV2;

			projectedV1= projectVectorOnPlane(vec1,xAxisVec,yAxisVec);
			projectedV2= projectVectorOnPlane(vec2,xAxisVec,yAxisVec);
			angleProjXYDeg=angleInbetweenVector(projectedV1,projectedV2);



			// angle X
			

			projectedV1= projectVectorOnPlane(vec1,zAxisVec,yAxisVec);
			projectedV2= projectVectorOnPlane(vec2,zAxisVec,yAxisVec);
			angleProjYZDeg=angleInbetweenVector(projectedV1,projectedV2);


			// angle Y
			

			projectedV1= projectVectorOnPlane(vec1,zAxisVec,xAxisVec);
			projectedV2= projectVectorOnPlane(vec2,zAxisVec,xAxisVec);
			angleProjXZDeg=angleInbetweenVector(projectedV1,projectedV2);

















			//Setting output values

			MDataHandle output = dataBlock.outputValue(dotProductA);
			MDataHandle outputMax = dataBlock.outputValue(dotProductMax);
			MDataHandle projV1Output = dataBlock.outputValue(proj1on2);
			MDataHandle projV2Output = dataBlock.outputValue(proj2on1);
			MDataHandle angleInBetweenOutput = dataBlock.outputValue(angleInBetweenAttr);
			MDataHandle angleXout = dataBlock.outputValue(angleX);
			MDataHandle angleYout = dataBlock.outputValue(angleY);
			MDataHandle angleZout = dataBlock.outputValue(angleZ);




			output.set(dotResult);
			outputMax.set(maxValue);
			projV1Output.set(v1Vec[0],v1Vec[1],v1Vec[2]);
			projV2Output.set(v2Vec[0],v2Vec[1],v2Vec[2]);
			angleInBetweenOutput.set(angleDeg);
			angleXout.set(angleProjYZDeg);
			angleYout.set(angleProjXZDeg);
			angleZout.set(angleProjXYDeg);

			//SetClean tells maya attribute is update
			outputMax.setClean();
			output.setClean();
			projV1Output.setClean();
			projV2Output.setClean();
			angleInBetweenOutput.setClean();
			angleXout.setClean();
			angleYout.setClean();
			angleZout.setClean();
		}
		
		return MS::kSuccess;


		}


