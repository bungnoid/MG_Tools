
#include <maya/MFnNumericAttribute.h>
#include <maya/MFloatPoint.h>
#include <MG_crossProduct.h>
#include <MG_vecMath.h>



  

MObject MG_crossProduct::vector1;
MObject MG_crossProduct::vector2;
MObject MG_crossProduct::normalize;
MObject MG_crossProduct::crossProductA;
MObject MG_crossProduct::reverse;
MObject MG_crossProduct::parallelogramA;
MObject MG_crossProduct::triangleA;



MTypeId MG_crossProduct::typeId( 0x80009 );

void* MG_crossProduct::creator()
{

	return new MG_crossProduct();
}

MStatus MG_crossProduct::initialize(){

				//Input vector 1

		MFnNumericAttribute numericAttrFn;
		vector1 = numericAttrFn.createPoint("vector1","v1");
		addAttribute(vector1);
		numericAttrFn.setStorable(true);
 
		//Input vector 2

		vector2 = numericAttrFn.createPoint("vector2","v2");
		addAttribute(vector2);
		numericAttrFn.setStorable(true);

		//cross product attribute
		crossProductA = numericAttrFn.createPoint("crossProduct","cp");
		addAttribute(crossProductA);
		numericAttrFn.setWritable(false);
		numericAttrFn.setStorable(false);

		//normalize attribute 

		
		normalize=numericAttrFn.create("normalize","n",MFnNumericData::kBoolean );
		addAttribute(normalize);
		numericAttrFn.setStorable(true);
		

		//revers cross attribute 

		
		reverse=numericAttrFn.create("reverseCross","rc",MFnNumericData::kBoolean );
		addAttribute(reverse);
		numericAttrFn.setStorable(true);


		parallelogramA=numericAttrFn.create("parallelogramArea","pa",MFnNumericData::kFloat );
		addAttribute(parallelogramA);
		numericAttrFn.setStorable(true);

		triangleA=numericAttrFn.create("triangleArea","ta",MFnNumericData::kFloat );
		addAttribute(triangleA);
		numericAttrFn.setStorable(true);

		attributeAffects(vector1,crossProductA);
		attributeAffects(vector2,crossProductA);
		attributeAffects(normalize,crossProductA);
		attributeAffects(reverse,crossProductA);


		attributeAffects(vector1,parallelogramA);
		attributeAffects(vector2,parallelogramA);
		attributeAffects(normalize,parallelogramA);

		attributeAffects(vector1,triangleA);
		attributeAffects(vector2,triangleA);
		attributeAffects(normalize,triangleA);


		return MS::kSuccess;
	}


MStatus MG_crossProduct::compute(const MPlug& plug,MDataBlock& dataBlock)
{
	if ((plug==crossProductA)||(plug==triangleA)||(plug==parallelogramA))


		{	
 
			//Creating handles 
			MDataHandle vector1DataH = dataBlock.inputValue(vector1);
			MFloatPoint vector1V = vector1DataH.asFloatVector();
			
			MDataHandle vector2DataH = dataBlock.inputValue(vector2);
			MFloatPoint vector2V = vector2DataH.asFloatVector();


			MDataHandle normData = dataBlock.inputValue(normalize);
			bool norm =normData.asBool();

			MDataHandle reverseData = dataBlock.inputValue(reverse);
			bool rev =reverseData.asBool();



			//Creating vectors
			float vec1Array[3] = {vector1V[0],vector1V[1],vector1V[2]};
			vector <float> vec1 = makeVector(vec1Array) ;

			float vec2Array[3] = {vector2V[0],vector2V[1],vector2V[2]};
			vector <float> vec2 = makeVector(vec2Array) ;


			vector <float> crossProductResult;
			if (norm==0)
			{
				if(rev==0)
				{
			//Cross product
			
					crossProductResult = vectorCrossProduct(vec1,vec2);
				}else{
					crossProductResult = negativeVector(vectorCrossProduct(vec1,vec2));

				}



			

			}else{
				if(rev==0){


					vector <float> vec1Norm =normVector(vec1);
					vector <float> vec2Norm =normVector(vec2);
					crossProductResult = vectorCrossProduct(vec1Norm,vec2Norm);
				}else{

					vector <float> vec1Norm =normVector(vec1);
					vector <float> vec2Norm =normVector(vec2);
					crossProductResult = negativeVector(vectorCrossProduct(vec1Norm,vec2Norm));
				}



			}

			float area = vectorLength(crossProductResult);
			float areaHalf = area/2;

			MDataHandle crossOutput = dataBlock.outputValue(crossProductA);
			crossOutput.set(crossProductResult[0],crossProductResult[1],crossProductResult[2]);
			MDataHandle areaOutput = dataBlock.outputValue(parallelogramA);
			areaOutput.set(area);

			MDataHandle areaHalfOutput = dataBlock.outputValue(triangleA);
			areaHalfOutput.set(areaHalf);

			crossOutput.setClean();
			areaOutput.setClean();
			areaHalfOutput.setClean();

		}
		

		return MS::kSuccess;
	}
