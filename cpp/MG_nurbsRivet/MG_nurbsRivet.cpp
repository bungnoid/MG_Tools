




#include "MG_nurbsRivet.h"
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
#include <maya/MMatrix.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MEulerRotation.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnMatrixAttribute.h>
const double toDeg = 57.295779513082320876798154814105;

//Needed attributes

MObject MG_nurbsRivet::inputNurbSurface;
MObject MG_nurbsRivet::inputPoint;
MObject MG_nurbsRivet::recompute;
MObject MG_nurbsRivet::output;
MObject MG_nurbsRivet::vValue;
MObject MG_nurbsRivet::uValue;
MObject MG_nurbsRivet::outputRotate;
MObject MG_nurbsRivet::outputMatrix;
MObject MG_nurbsRivet::offsetMatrix;
MObject MG_nurbsRivet::inputPointX;
MObject MG_nurbsRivet::inputPointY;
MObject MG_nurbsRivet::inputPointZ;
MObject MG_nurbsRivet::outputX;
MObject MG_nurbsRivet::outputY;
MObject MG_nurbsRivet::outputZ;
MObject MG_nurbsRivet::outputRotateX;
MObject MG_nurbsRivet::outputRotateY;
MObject MG_nurbsRivet::outputRotateZ;

MTypeId MG_nurbsRivet::typeId( 0x800001 );








//Class


void* MG_nurbsRivet::creator()
{

	return new MG_nurbsRivet();
}

MStatus MG_nurbsRivet::initialize()
	{ 

		//This is the nurbs input attribute
		MFnTypedAttribute typedFn;
		MFnCompoundAttribute compund;
		MFnNumericAttribute numFn;
		MFnMatrixAttribute    matrixFn;

		inputNurbSurface  = typedFn.create("inputNurbSurface","in",MFnData::kNurbsSurface);
		typedFn.setStorable(true);
		addAttribute(inputNurbSurface);
		

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

		//all the attr affects

		attributeAffects (recompute,output);
		attributeAffects (inputPoint,output);
		attributeAffects (inputNurbSurface,output);
		attributeAffects (uValue,output);
		attributeAffects (vValue,output);
		attributeAffects (offsetMatrix,output);

		attributeAffects (recompute,outputRotate);
		attributeAffects (inputPoint,outputRotate);
		attributeAffects (inputNurbSurface,outputRotate);
		attributeAffects (uValue,outputRotate);
		attributeAffects (vValue,outputRotate);
		attributeAffects (offsetMatrix,outputRotate);

		attributeAffects (recompute,outputMatrix);
		attributeAffects (inputPoint,outputMatrix);
		attributeAffects (inputNurbSurface,outputMatrix);
		attributeAffects (uValue,outputMatrix);
		attributeAffects (vValue,outputMatrix);
		attributeAffects (offsetMatrix,outputMatrix);

		return MS::kSuccess;
	}
MStatus MG_nurbsRivet::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		


			
			//Get recompute value
			MDataHandle recomputeH = dataBlock.inputValue(recompute);
	  		bool recomputeV = recomputeH.asBool();





			//input mesh 
			MDataHandle inputNurbsH = dataBlock.inputValue(inputNurbSurface);
			MObject inputNurb = inputNurbsH.asNurbsSurfaceTransformed();
			MMatrix offsetMatrixV = dataBlock.inputValue(offsetMatrix).asMatrix(); 
			
			double U,V;
			MFnNurbsSurface nurbsFn ;
			nurbsFn.setObject(inputNurb);
			
			MStatus stat;

			if (recomputeV == true)
			{

			
				//input point 

				MDataHandle inputPointH = dataBlock.inputValue(inputPoint);
				MPoint inputP = inputPointH.asVector();
				

				
				
				MPoint closestP = nurbsFn.closestPoint(inputP,NULL,NULL,false,1e+99,MSpace::kObject);

				
				

				stat = nurbsFn.getParamAtPoint(closestP,U,V,MSpace::kObject);
				
				


				//Handle to U and V 
				MDataHandle uValueH =dataBlock.outputValue(uValue);
				MDataHandle vValueH =dataBlock.outputValue(vValue);
				
				uValueH.set(float(U));
				vValueH.set(float(V));
				uValueH.setClean();
				vValueH.setClean();



				MDataHandle recomputeOutH = dataBlock.outputValue(recompute);

	
			}  

			MDataHandle uH = dataBlock.inputValue(uValue);
			MDataHandle vH = dataBlock.inputValue(vValue);
			
			U = uH.asFloat(); 
			V = vH.asFloat();

			MPoint outPoint ;
			MVector uVec ;
			MVector vVec;
			MVector normal;
			//Get point
			stat = nurbsFn.getPointAtParam(U,V,outPoint,MSpace::kObject);
			
			//Since if getting both the U and V tangent was leading to some little rotation snapping 
			//of the rivet I only used the U tangent and calculated the next one by dot product
			//of the normal and U tangent leading to a 100% stable rivet 
			nurbsFn.getTangents(U,V,uVec,vVec,MSpace::kObject);
			
			uVec.normalize();
			vVec.normalize();
			MVector vVecCross;

	


			//Get normal



			

			normal = nurbsFn.normal(U,V,MSpace::kObject);
			normal.normalize();

			vVecCross =(uVec^normal);
			
			
			



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

			 

 

		return MS::kSuccess;
	}





