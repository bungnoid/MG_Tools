




#include "MG_polyRivet.h"
#include <maya/MPxNode.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MFloatVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MEulerRotation.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnData.h>
#include <maya/MFnMesh.h>
#include <maya/MItMeshPolygon.h>
const double toDeg = 57.295779513082320876798154814105;

//Needed attributes

MObject MG_polyRivet::inputMesh;
MObject MG_polyRivet::inputPoint;
MObject MG_polyRivet::recompute;
MObject MG_polyRivet::output;
MObject MG_polyRivet::vValue;
MObject MG_polyRivet::uValue;
MObject MG_polyRivet::outputRotate;
MObject MG_polyRivet::outputMatrix;
MObject MG_polyRivet::offsetMatrix;
MObject MG_polyRivet::inputPointX;
MObject MG_polyRivet::inputPointY;
MObject MG_polyRivet::inputPointZ;
MObject MG_polyRivet::outputX;
MObject MG_polyRivet::outputY;
MObject MG_polyRivet::outputZ;
MObject MG_polyRivet::outputRotateX;
MObject MG_polyRivet::outputRotateY;
MObject MG_polyRivet::outputRotateZ;
MObject MG_polyRivet::faceId;
MObject MG_polyRivet::parentMatrix;
MTypeId MG_polyRivet::typeId( 0x800000 );








//Class


void* MG_polyRivet::creator()
{

	return new MG_polyRivet();
}

MStatus MG_polyRivet::initialize()
	{ 

		//This is the nurbs input attribute
		MFnTypedAttribute typedFn;
		MFnCompoundAttribute compund;
		MFnNumericAttribute numFn;
		MFnMatrixAttribute    matrixFn;
		MFnGenericAttribute  genericFn;

		inputMesh  = genericFn.create("inputSurface","in");

		genericFn.addDataAccept (MFnData::kMesh );
		typedFn.setStorable(true);
		addAttribute(inputMesh);
		

		//This is the input point   attribute
		
		
		inputPointX = numFn.create("inputPointX","ipx",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(inputPointX);

		inputPointY = numFn.create("inputPointY","ipy",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(inputPointY);
		

		inputPointZ = numFn.create("inputPointZ","ipz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(inputPointZ);




		
		inputPoint= compund.create("inputPoint","ip");
		compund.addChild(inputPointX);
		compund.addChild(inputPointY);
		compund.addChild(inputPointZ);
		addAttribute(inputPoint);
	

		//This is the recompute point checkbox
	
		recompute = numFn.create("recompute","r",MFnNumericData::kBoolean,1);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(recompute);

		//This is U attribute
	
		uValue = numFn.create("uValue","u",MFnNumericData::kFloat);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(uValue);


		//This is V attribute
	
		vValue = numFn.create("vValue","v",MFnNumericData::kFloat);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(vValue);
		
		faceId = numFn.create("faceId","fid",MFnNumericData::kInt,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(faceId);


		//This is the output translate attribute 

		outputX = numFn.create("outputTranslateX","otx",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputX);

		outputY = numFn.create("outputTranslateY","oty",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputY);
		

		outputZ = numFn.create("outputTranslateZ","otz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputZ);




		
		output= compund.create("outputTranslate","ot");
		compund.addChild(outputX);
		compund.addChild(outputY);
		compund.addChild(outputZ);
		compund.setKeyable(false);
		compund.setStorable(false);
		compund.setWritable(false);
		addAttribute(output);


		//output = numFn.createPoint("outputTranslate","ot");
		//numFn.setKeyable(false);
		//numFn.setStorable(false);
		//numFn.setWritable(false);
		//addAttribute(output);


		//This is the output rotate attribute 
		outputRotateX = numFn.create("outputRotateX","orx",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputRotateX);

		outputRotateY = numFn.create("outputRotateY","ory",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputRotateY);

		outputRotateZ = numFn.create("outputRotateZ","orz",MFnNumericData::kDouble,0);
		numFn.setStorable(true);
		numFn.setKeyable(true);
		addAttribute(outputRotateZ);


		outputRotate= compund.create("outputRotate","oro");
		compund.addChild(outputRotateX);
		compund.addChild(outputRotateY);
		compund.addChild(outputRotateZ);
		compund.setKeyable(false);
		compund.setStorable(false);
		compund.setWritable(false);
		addAttribute(outputRotate);

 
		//Those are all the matrix input 

		
		outputMatrix =matrixFn.create("outputMatrix","om");
		matrixFn.setKeyable(false);
		matrixFn.setStorable(false);
		matrixFn.setWritable(false);
		addAttribute(outputMatrix); 


		//offset matrix 

		offsetMatrix =matrixFn.create("offsetMatrix","ofm");
		MMatrix defMatrix;
		defMatrix.setToIdentity();
		matrixFn.setDefault(defMatrix);
		matrixFn.setKeyable(false);
		matrixFn.setStorable(true);
		matrixFn.setWritable(true);
		addAttribute(offsetMatrix); 

		parentMatrix =matrixFn.create("meshParentMatrix","pmx");

		defMatrix.setToIdentity();
		matrixFn.setDefault(defMatrix);
		matrixFn.setKeyable(false);
		matrixFn.setStorable(true);
		matrixFn.setWritable(true);
		addAttribute(parentMatrix); 

		//all the attr affects

		attributeAffects (recompute,output);
		attributeAffects (inputPoint,output);
		attributeAffects (inputMesh,output);
		attributeAffects (uValue,output);
		attributeAffects (vValue,output);
		attributeAffects (faceId,output);
		attributeAffects (offsetMatrix,output);
		attributeAffects (parentMatrix,output);

		attributeAffects (recompute,outputRotate);
		attributeAffects (inputPoint,outputRotate);
		attributeAffects (inputMesh,outputRotate);
		attributeAffects (uValue,outputRotate);
		attributeAffects (vValue,outputRotate);
		attributeAffects (faceId,outputRotate);
		attributeAffects (offsetMatrix,outputRotate);
		attributeAffects (parentMatrix,outputRotate);

		attributeAffects (recompute,outputMatrix);
		attributeAffects (inputPoint,outputMatrix);
		attributeAffects (inputMesh,outputMatrix);
		attributeAffects (uValue,outputMatrix);
		attributeAffects (vValue,outputMatrix);
		attributeAffects (offsetMatrix,outputMatrix);
		attributeAffects (faceId,outputMatrix);
		attributeAffects (parentMatrix,outputMatrix);
		return MS::kSuccess;
	}
MStatus MG_polyRivet::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		
			//Check if there is a collider geometry connected 
			//if not skip the compute
			MPlug inputG (thisMObject(),inputMesh);

			if (inputG.isConnected()==true)
			{


		
			//Get recompute value
			MDataHandle recomputeH = dataBlock.inputValue(recompute);
	  		bool recomputeV = recomputeH.asBool();

	


			//input mesh 
			MDataHandle inputNurbsH = dataBlock.inputValue(inputMesh);
			MMatrix offsetMatrixV = dataBlock.inputValue(offsetMatrix).asMatrix(); 
			MMatrix parentMatrixV = dataBlock.inputValue(parentMatrix).asMatrix(); 
	
			int inputType = inputNurbsH.type() ;



			//needed variables 

			MPoint inputP;
			MVector vVecCross;
			MPoint outPoint ;
			MVector normal;
			MStatus stat;
			double U,V;
			int faceIdV;
			MVector uVec ;
			MVector vVec;

			

				MObject inputGeo = inputNurbsH.asMeshTransformed();
				MFnMesh  meshFn(inputGeo);



				if (recomputeV == true)
				{

					//input point 

					MDataHandle inputPointH = dataBlock.inputValue(inputPoint);
					inputP = inputPointH.asVector();
					MPoint closestP;
					float uvP[2];
					
					meshFn.getClosestPoint(inputP , closestP , MSpace::kObject , NULL ) ;
					meshFn.getUVAtPoint	(	closestP,
									uvP,
									MSpace::kObject,
									NULL ,
									&faceIdV ) ;



					//Handle to U and V 
					MDataHandle uValueH =dataBlock.outputValue(uValue);
					MDataHandle vValueH =dataBlock.outputValue(vValue);
				
					uValueH.set(float(uvP[0]));
					vValueH.set(float(uvP[1]));
					uValueH.setClean();
					vValueH.setClean();

					dataBlock.outputValue(faceId).set(faceIdV);
					dataBlock.outputValue(faceId).setClean();
				


					 
				}

			MDataHandle uH = dataBlock.inputValue(uValue);
			MDataHandle vH = dataBlock.inputValue(vValue);
		
			U = uH.asFloat(); 
			V = vH.asFloat();

			
			float uvV[2];
			 uvV[0] = U ;
			 uvV[1] = V ;	
			faceIdV = dataBlock.inputValue(faceId).asInt();
			
			


			
			//Get point
			
		
			meshFn.getPointAtUV	(	faceIdV,
							outPoint,
							uvV,
							MSpace::kObject,
							NULL ,
							 0.0
						);


			//get normal
			meshFn.getPolygonNormal(faceIdV ,normal ,MSpace::kObject ) ;

			normal.normalize();
			normal = normal*parentMatrixV;

			
			

			MPoint outTangent;
			float uvVt[2];
			uvVt[0] = U + 0.01;
			uvVt[1] = V ;	


			stat = meshFn.getPointAtUV	(	faceIdV,
						outTangent,
						uvVt,
						MSpace::kObject,
						NULL ,
						 0.0
					);

			if  ( stat == MS::kFailure) 
				{
				uvVt[0] = U - 0.01;
				uvVt[1] = V ;	


				stat = meshFn.getPointAtUV	(	faceIdV,
						outTangent,
						uvVt,
						MSpace::kObject,
						NULL ,
						 0.0
					);

				}

			
			if  ( stat == MS::kFailure) 
				{
				uvVt[0] = U ;
				uvVt[1] = V + 0.01;	


				stat = meshFn.getPointAtUV	(	faceIdV,
						outTangent,
						uvVt,
						MSpace::kObject,
						NULL ,
						 0.0
					);
				}

			if  ( stat == MS::kFailure) {

				uvVt[0] = U ;
				uvVt[1] = V - 0.01;	


				stat = meshFn.getPointAtUV	(	faceIdV,
						outTangent,
						uvVt,
						MSpace::kObject,
						NULL ,
						 0.0
					);}



				


			MVector tantStart (outPoint);
			MVector tantEnd  ( outTangent ) ;
			uVec = tantEnd - tantStart ;
			uVec.normalize();
		
			
			
			

			vVecCross =(uVec^normal);
			vVecCross.normalize();
			
			
			


			//Build the maya matrix 
			double myMatrix[4][4]={	{ uVec.x, uVec.y , uVec.z, 0},
									{ normal[0], normal[1] , normal[2], 0},
									{vVecCross.x, vVecCross.y , vVecCross.z, 0},
									{ outPoint[0], outPoint[1] , outPoint[2], 1}};
 
			
			MMatrix rotMatrix (myMatrix);
			MMatrix offsetMatrixV2 = offsetMatrixV*rotMatrix; 
			 
			MTransformationMatrix matrixFn(offsetMatrixV2);
			double angles[3];
			MTransformationMatrix::RotationOrder rotOrder;
			rotOrder =MTransformationMatrix::kXYZ;
			matrixFn.getRotation(angles,rotOrder,MSpace::kObject );
			//get back radians value
			double radX,radY,radZ;

			radX=angles[0]; 
			radY=angles[1];
			radZ=angles[2];
 
			

			//convert to degree

			double rotX,rotY,rotZ;

			rotX = radX*toDeg;
			rotY = radY*toDeg;
			rotZ = radZ*toDeg; 
			

			MDataHandle outputRotateH = dataBlock.outputValue(outputRotate);
			
			outputRotateH.set3Double(rotX,rotY,rotZ);
			outputRotateH.setClean();

			//let set the output matrix too

			MDataHandle outMH= dataBlock.outputValue(outputMatrix);
			outMH.set(rotMatrix);
			outMH.setClean();

			MDataHandle outputH = dataBlock.outputValue(output);
			outputH.set(offsetMatrixV2[3][0],offsetMatrixV2[3][1],offsetMatrixV2[3][2]);
			outputH.setClean();

			}




		return MS::kSuccess;
	}





