#include "MG_poseReader.h"

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
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MFnMeshData.h>
#include <maya/MObjectArray.h>
#include <maya/MFloatPoint.h>


const double PI=3.14159265358979323846264338327950288419716939937510;
const double toDeg = 57.295779513082320876798154814105;
const double toRad = 0.01745329251994329576923690768489;
MTypeId MG_poseReader::typeId( 0x80005 );

//Needed attributes

MObject MG_poseReader::aimAxis;
MObject MG_poseReader::poseMatrix;
MObject MG_poseReader::readerMatrix;
MObject MG_poseReader::size;
MObject MG_poseReader::readerOnOff;
MObject MG_poseReader::axisOnOff;
MObject MG_poseReader::poseOnOff;
MObject MG_poseReader::xPositive;
MObject MG_poseReader::xNegative;
MObject MG_poseReader::yPositive;
MObject MG_poseReader::yNegative;
MObject MG_poseReader::zPositive;
MObject MG_poseReader::zNegative;





//Class


void* MG_poseReader::creator()
{

	return new MG_poseReader();
}

MStatus MG_poseReader::initialize()
	{ 
		//Declaring all the needed attribute function sets
		MFnEnumAttribute enumFn;
		MFnMatrixAttribute matrixFn;
		MFnNumericAttribute numFn;
		MFnCompoundAttribute compA;


		//Aim axis input attribute

		aimAxis = enumFn.create("aimAxis","aa",0);
		enumFn.addField("x",0);
		enumFn.addField("y",1);
		enumFn.addField("z",2);
		enumFn.setKeyable(true);
		enumFn.setStorable(true);
		addAttribute(aimAxis); 

		//Pose matrix input attribute

		
		poseMatrix =matrixFn.create("poseMatrix","psm");
		matrixFn.setKeyable(true);
		matrixFn.setStorable(true);
		addAttribute(poseMatrix); 

		//Reader matrix input attribute

		readerMatrix =matrixFn.create("readerMatrix","rm");
		matrixFn.setKeyable(true);
		matrixFn.setStorable(true);
		addAttribute(readerMatrix); 

		//Aim axis input attribute

		//Arrow size
		size =numFn.create("size","siz",MFnNumericData::kDouble,1);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(size);

		readerOnOff =numFn.create("readerOnOff","rof",MFnNumericData::kBoolean,1);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(readerOnOff);
		

		axisOnOff =numFn.create("axisOnOff","aof",MFnNumericData::kBoolean,1);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(axisOnOff);


		poseOnOff =numFn.create("poseOnOff","pof",MFnNumericData::kBoolean,1);
		numFn.setKeyable(true);
		numFn.setStorable(true);
		addAttribute(poseOnOff);



		xPositive = numFn.create("xPositive","xp",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(xPositive);

		xNegative = numFn.create("xNegative","xn",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(xNegative);

		yPositive = numFn.create("yPositive","yp",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(yPositive);

		yNegative = numFn.create("yNegative","yn",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(yNegative);

		zPositive = numFn.create("zPositive","zp",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(zPositive);

		zNegative = numFn.create("zNegative","zn",MFnNumericData::kDouble,0);
		numFn.setStorable(false);
		numFn.setWritable(false);
		addAttribute(zNegative);



		attributeAffects (aimAxis,xPositive);
		attributeAffects (poseMatrix,xPositive);
		attributeAffects (readerMatrix,xPositive);
		attributeAffects (size,xPositive);

		attributeAffects (aimAxis,xNegative);
		attributeAffects (poseMatrix,xNegative);
		attributeAffects (readerMatrix,xNegative);
		attributeAffects (size,xNegative);

		attributeAffects (aimAxis,yPositive);
		attributeAffects (poseMatrix,yPositive);
		attributeAffects (readerMatrix,yPositive);
		attributeAffects (size,yPositive);

		attributeAffects (aimAxis,yNegative);
		attributeAffects (poseMatrix,yNegative);
		attributeAffects (readerMatrix,yNegative);
		attributeAffects (size,yNegative);


		attributeAffects (aimAxis,zPositive);
		attributeAffects (poseMatrix,zPositive);
		attributeAffects (readerMatrix,zPositive);
		attributeAffects (size,zPositive);

		attributeAffects (aimAxis,zNegative);
		attributeAffects (poseMatrix,zNegative);
		attributeAffects (readerMatrix,zNegative);
		attributeAffects (size,zNegative);

		return MS::kSuccess;
	

}

bool MG_poseReader::isBounded() const
{ 
	return false ;
}

MStatus MG_poseReader::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		
	      
		MMatrix poseM = dataBlock.inputValue(poseMatrix).asMatrix();
		MMatrix readerM = dataBlock.inputValue(readerMatrix).asMatrix();

		// aim axis value 
		//0 =x
		//1 =y
		//2 =z
		int axis = dataBlock.inputValue(aimAxis).asInt();


		MVector poseAimV;
		if (axis==0)
		{
			
			poseAimV.x=poseM[0][0];
			poseAimV.y=poseM[0][1];
			poseAimV.z=poseM[0][2];
		}
		else if (axis==1)
		{
			
			poseAimV.x=poseM[1][0];
			poseAimV.y=poseM[1][1];
			poseAimV.z=poseM[1][2];

		}else
		{
			
			poseAimV.x=poseM[2][0];
			poseAimV.y=poseM[2][1];
			poseAimV.z=poseM[2][2];
		}
	
		MVector x (readerM[0][0],readerM[0][1],readerM[0][2]);
		MVector y (readerM[1][0],readerM[1][1],readerM[1][2]);
		MVector z (readerM[2][0],readerM[2][1],readerM[2][2]);
		double porjX =projVector (poseAimV,x);
		double porjXNeg =projVector (poseAimV,x*-1);
		double porjY =projVector (poseAimV,y);
		double porjYNeg =projVector (poseAimV,y*-1);
		double porjZ =projVector (poseAimV,z);
		double porjZNeg =projVector (poseAimV,z*-1);

		dataBlock.outputValue(xPositive).set(porjX);
		dataBlock.outputValue(xPositive).setClean();

		dataBlock.outputValue(xNegative).set(porjXNeg);
		dataBlock.outputValue(xNegative).setClean();


		dataBlock.outputValue(yPositive).set(porjY);
		dataBlock.outputValue(yPositive).setClean();

		dataBlock.outputValue(yNegative).set(porjYNeg);
		dataBlock.outputValue(yNegative).setClean();

		dataBlock.outputValue(zPositive).set(porjZ);
		dataBlock.outputValue(zPositive).setClean();

		dataBlock.outputValue(zNegative).set(porjZNeg);
		dataBlock.outputValue(zNegative).setClean();

		return MS::kSuccess;
	}








void MG_poseReader::draw( M3dView & view, const MDagPath & path, 
							 M3dView::DisplayStyle dispStyle,
							 M3dView::DisplayStatus status )
{ 
   
	
	MPlug sizeP (thisMObject(),size);
	double sizeV;
	sizeP.getValue(sizeV);

	MPlug poseMatrixP (thisMObject(),poseMatrix);
	MObject poseMatrixData;
	poseMatrixP.getValue(poseMatrixData);
	MFnMatrixData matrixFn(poseMatrixData);
	MMatrix poseMatrixV =matrixFn.matrix();

	MPlug readerMatrixP (thisMObject(),readerMatrix);
	MObject readerMatrixData;
	readerMatrixP.getValue(readerMatrixData);

	matrixFn.setObject(readerMatrixData);
	MMatrix readerMatrixV =matrixFn.matrix();

	MMatrix poseMatrixFix =poseMatrixV*readerMatrixV.inverse();

	MPlug aimAxisP  (thisMObject(),aimAxis);
	int aimAxisV;
	aimAxisP.getValue(aimAxisV);
	MVector aimBall;

	  
	MPlug readerOnOffP(thisMObject(),readerOnOff);
	MPlug axisOnOffP(thisMObject(),axisOnOff);
	MPlug poseOnOffP(thisMObject(),poseOnOff);

	double readerOnOffV;
	double axisOnOffV;
	double poseOnOffV;

	readerOnOffP.getValue(readerOnOffV);
	axisOnOffP.getValue(axisOnOffV);
	poseOnOffP.getValue(poseOnOffV);

	MPlug xPositiveP  (thisMObject(),xPositive);
	MPlug xNegativeP  (thisMObject(),xNegative);

	double xPositiveV;
	double xNegativeV;

	xPositiveP.getValue(xPositiveV);
	xNegativeP.getValue(xNegativeV);

	double xColor = xPositiveV;
	if (xPositiveV==0)
	{
		xColor=xNegativeV;

	}
	


	MPlug yPositiveP  (thisMObject(),yPositive);
	MPlug yNegativeP  (thisMObject(),yNegative);

	double yPositiveV;
	double yNegativeV;

	yPositiveP.getValue(yPositiveV);
	yNegativeP.getValue(yNegativeV);

	double yColor = yPositiveV;
	if (yPositiveV==0)
	{
		yColor=yNegativeV;

	}

	MPlug zPositiveP  (thisMObject(),zPositive);
	MPlug zNegativeP  (thisMObject(),zNegative);

	double zPositiveV;
	double zNegativeV;

	zPositiveP.getValue(zPositiveV);
	zNegativeP.getValue(zNegativeV);

	double zColor = zPositiveV;
	if (zPositiveV==0)
	{
		zColor=zNegativeV;

	}



		if (aimAxisV==0)
		{
			
			aimBall.x=poseMatrixFix[0][0];
			aimBall.y=poseMatrixFix[0][1];
			aimBall.z=poseMatrixFix[0][2];
		}
		else if (aimAxisV==1)
		{
			
			aimBall.x=poseMatrixFix[1][0];
			aimBall.y=poseMatrixFix[1][1];
			aimBall.z=poseMatrixFix[1][2];

		}else
		{
			
			aimBall.x=poseMatrixFix[2][0];
			aimBall.y=poseMatrixFix[2][1];
			aimBall.z=poseMatrixFix[2][2];
		}
	
      
	//*****************************************************************
	// Initialize opengl and draw
	//*****************************************************************
	view.beginGL();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2);
	if(status == M3dView::kLead)
		glColor4f(0.0,1.0,0.0,0.3f);
	else
		glColor4f(1.0,1.0,0.0,0.3f);





	MVector baseV(0,0,0);
	MVector xp(1*sizeV,0,0);
	MVector xm(-1*sizeV,0,0);
	MVector yp(0,1*sizeV,0);
	MVector ym(0,-1*sizeV,0);
	MVector zp(0,0,1*sizeV);
	MVector zm(0,0,-1*sizeV);



	double * red;
	red = new double[4];
	red[0]=1;
	red[1]=0;
	red[2]=0;
	red[3]=1;

	double * green;
	green = new double[4];
	green[0]=0;
	green[1]=1;
	green[2]=0;
	green[3]=1;

	double * blue;
	blue = new double[4];
	blue[0]=0;
	blue[1]=0;
	blue[2]=1;
	blue[3]=1;

	double * yellow;
	yellow = new double[4];
	yellow[0]=1;
	yellow[1]=1;
	yellow[2]=0.2;
	yellow[3]=0.3;



	if (readerOnOffV==1)
	{
	drawSphere(sizeV,20,20,baseV,yellow);
	}
	
	
	if  (axisOnOffV==1)
	{
	drawSphere(sizeV/7,15,15,xp,red);
	drawSphere(sizeV/7,15,15,xm,red); 
	drawSphere(sizeV/7,15,15,yp,green);
	drawSphere(sizeV/7,15,15,ym,green);
	drawSphere(sizeV/7,15,15,zp,blue);
	drawSphere(sizeV/7,15,15,zm,blue);
	}
	if (poseOnOffV==1)
	{
	  

	
	double* color = blendColor(xColor,yColor,zColor,1);

	drawSphere(sizeV/7,15,15,aimBall*sizeV,color);
	}

	glDisable(GL_BLEND);
	glPopAttrib();



}




 


double* MG_poseReader::blendColor(const double& red,const double& green,const double& blue,const double &alpha)
 {
	 

	 double* colorOut;
	 colorOut = new double[4];

	 double red255 = red * 255;
	 double green255 = green * 255;
	 double blue255 = blue * 255;

	 double redBalanced;
	 double greenBalanced ;
	 double blueBalanced ;
	 
	 
	 double total255 = red255+green255+blue255;
	 if (total255 != 0)
	 {
	   redBalanced = red*255/total255;
	   greenBalanced = green*255/total255;
	   blueBalanced = blue*255/total255;
	 }
	 else
	 {
	    redBalanced = 0;
	    greenBalanced = 0;
	    blueBalanced = 0;
	 }
	 

	 
	 colorOut[0]=redBalanced;
	 colorOut[1]=greenBalanced,
	 colorOut[2]=blueBalanced;
	 colorOut[3]=alpha;


	 return colorOut;
 }
 
void MG_poseReader::drawSphere(const double r, const int lats, const int longs,const MVector position,const double* color)
 {
     int i, j;
        for(i = 0; i <= lats; i++) {
            double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
           double z0  = sin(lat0);
           double zr0 =  cos(lat0);
    
           double lat1 = M_PI * (-0.5 + (double) i / lats);
           double z1 = sin(lat1);
           double zr1 = cos(lat1);
		   glColor4d(color[0],color[1],color[2],color[3]);
           glBegin(GL_QUAD_STRIP);
           for(j = 0; j <= longs; j++) {
               double lng = 2 * M_PI * (double) (j - 1) / longs;
               double x = cos(lng);
               double y = sin(lng);
    
			   glNormal3d((x * zr0*r)+position.x,( y * zr0*r)+position.y, (z0*r)+position.z);
               glVertex3d((x * zr0*r)+position.x, (y * zr0*r)+position.y, (z0*r)+position.z);
               glNormal3d((x * zr1*r)+position.x, (y * zr1*r)+position.y, (z1*r)+position.z);
               glVertex3d((x * zr1*r)+position.x, (y * zr1*r)+position.y, (z1*r)+position.z);
           }
           glEnd();
       }
   }

void MG_poseReader::drawArrow(const int aimAxis,const double arrowSizeV)
 {


	 //Reader vector

	double  tipX,tipY,tipZ,
			corner1X,corner1Y,corner1Z,
			corner2X,corner2Y,corner2Z,
			corner3X,corner3Y,corner3Z,
			corner4X,corner4Y,corner4Z;

	tipX = 0 ;
	tipY = 0 ;
	tipZ = 0 ;
	corner1X = 0;
	corner1Y = 0;
	corner1Z = 0;
	
	corner2X = 0;
	corner2Y = 0;
	corner2Z = 0;
	
	corner3X = 0;
	corner3Y = 0;
	corner3Z = 0;
	
	corner4X = 0;
	corner4Y = 0;
	corner4Z = 0;

	switch ( aimAxis )
			{

				case 0:
					if (aimAxis==0)
					{
						tipX=1*arrowSizeV;tipY=0.0;tipZ=0.0;
						corner1X=0.9*arrowSizeV,corner1Y=0.05*arrowSizeV,corner1Z=-0.05*arrowSizeV;
						corner2X=0.9*arrowSizeV,corner2Y=0.05*arrowSizeV,corner2Z=0.05*arrowSizeV;
						corner3X=0.9*arrowSizeV,corner3Y=-0.05*arrowSizeV,corner3Z=0.05*arrowSizeV;
						corner4X=0.9*arrowSizeV,corner4Y=-0.05*arrowSizeV,corner4Z=-0.05*arrowSizeV;


					
					}

					
				case 1:
					if (aimAxis==1)
					{
						tipX=0.0;tipY=1.0*arrowSizeV;tipZ=0.0;
						corner1Y=0.9*arrowSizeV,corner1X=0.05*arrowSizeV,corner1Z=-0.05*arrowSizeV;
						corner2Y=0.9*arrowSizeV,corner2X=0.05*arrowSizeV,corner2Z=0.05*arrowSizeV;
						corner3Y=0.9*arrowSizeV,corner3X=-0.05*arrowSizeV,corner3Z=0.05*arrowSizeV;
						corner4Y=0.9*arrowSizeV,corner4X=-0.05*arrowSizeV,corner4Z=-0.05*arrowSizeV;
						
						

					}
				case 2:
					if (aimAxis==2)
					{
						tipX=0;tipY=0.0;tipZ=1.0*arrowSizeV;
						corner1Z=0.9*arrowSizeV,corner1X=0.05*arrowSizeV,corner1Y=-0.05*arrowSizeV;
						corner2Z=0.9*arrowSizeV,corner2X=0.05*arrowSizeV,corner2Y=0.05*arrowSizeV;
						corner3Z=0.9*arrowSizeV,corner3X=-0.05*arrowSizeV,corner3Y=0.05*arrowSizeV;
						corner4Z=0.9*arrowSizeV,corner4X=-0.05*arrowSizeV,corner4Y=-0.05*arrowSizeV;
						
					
					} 
			}

	glBegin(GL_LINES);
		//draw the reader 
		glVertex3d(0,0,0);
		glVertex3d(tipX,tipY,tipZ);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3d(corner1X,corner1Y,corner1Z);
		glVertex3d(corner2X,corner2Y,corner2Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3d(corner3X,corner3Y,corner3Z);
		glVertex3d(corner2X,corner2Y,corner2Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3X,corner3Y,corner3Z);
		glVertex3d(corner4X,corner4Y,corner4Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();

	glBegin(GL_TRIANGLES);
		glBegin(GL_TRIANGLES);
		glVertex3d(corner1X,corner1Y,corner1Z);
		glVertex3d(corner4X,corner4Y,corner4Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();
 }

void MG_poseReader::drawArrowMatrix(const int aimAxis,const double arrowSizeV,const MMatrix poseM ,const MMatrix readerM)
 {

	
	 MVector tipV,corner1V,corner2V,corner3V,corner4V;
	 MMatrix tipM,corner1M,corner2M,corner3M,corner4M,baseM;
	 baseM.setToIdentity();
	 baseM*=poseM;
	 baseM*=readerM.inverse();
	 switch ( aimAxis )
			{

				case 0:
					if (aimAxis==0)
					{
						
						tipV.x=1*arrowSizeV;
						tipV.y=0.0;
						tipV.z=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.x=0.9*arrowSizeV;
						corner1V.y=0.05*arrowSizeV;
						corner1V.z=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						corner1M*=readerM.inverse();

						

						corner2V.x=0.9*arrowSizeV;
						corner2V.y=0.05*arrowSizeV;
						corner2V.z=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.x=0.9*arrowSizeV;
						corner3V.y=-0.05*arrowSizeV;
						corner3V.z=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.x=0.9*arrowSizeV;
						corner4V.y=-0.05*arrowSizeV;
						corner4V.z=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

						
					}
				case 1:
					if (aimAxis==1)
					{
						tipV.y=1*arrowSizeV;
						tipV.x=0.0;
						tipV.z=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.y=0.9*arrowSizeV;
						corner1V.x=0.05*arrowSizeV;
						corner1V.z=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						
						corner1M*=readerM.inverse();

						

						corner2V.y=0.9*arrowSizeV;
						corner2V.x=0.05*arrowSizeV;
						corner2V.z=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.y=0.9*arrowSizeV;
						corner3V.x=-0.05*arrowSizeV;
						corner3V.z=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.y=0.9*arrowSizeV;
						corner4V.x=-0.05*arrowSizeV;
						corner4V.z=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

					}

				case 2:
					if (aimAxis==2)
					{
						tipV.z=1*arrowSizeV;
						tipV.x=0.0;
						tipV.y=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.z=0.9*arrowSizeV;
						corner1V.x=0.05*arrowSizeV;
						corner1V.y=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						
						corner1M*=readerM.inverse();

						

						corner2V.z=0.9*arrowSizeV;
						corner2V.x=0.05*arrowSizeV;
						corner2V.y=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.z=0.9*arrowSizeV;
						corner3V.x=-0.05*arrowSizeV;
						corner3V.y=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.z=0.9*arrowSizeV;
						corner4V.x=-0.05*arrowSizeV;
						corner4V.y=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

					}


			}

	glBegin(GL_LINES);
		
		glVertex3d(baseM[3][0],baseM[3][1],baseM[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);


	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner1M[3][0],corner1M[3][1],corner1M[3][2]);
		glVertex3d(corner2M[3][0],corner2M[3][1],corner2M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3M[3][0],corner3M[3][1],corner3M[3][2]);
		glVertex3d(corner2M[3][0],corner2M[3][1],corner2M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3M[3][0],corner3M[3][1],corner3M[3][2]);
		glVertex3d(corner4M[3][0],corner4M[3][1],corner4M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner1M[3][0],corner1M[3][1],corner1M[3][2]);
		glVertex3d(corner4M[3][0],corner4M[3][1],corner4M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();

	


 }



void    MG_poseReader::drawText(const MString &text,const double* color, const MPoint &position,M3dView &view){

		glColor4d(color[0],color[1],color[2],1.0f);
		
		view.drawText( text, position, M3dView::kLeft );

}

double MG_poseReader::angleToPar(const double &angle, const double &maxAngle,const double &centerAngle)
{
	double par;
	
	if ((angle>maxAngle))
	{
		par=0.0;
	}
	else if (angle<0)
	{
		par=0.0;


	}else{
		//1-(angle/maxAngle)
		par = 1 - (angle/(maxAngle));
	}
		

	 
	return par;
}

MMatrix MG_poseReader::fromVecToMatrix(const MVector vec)
{
	double matrixF[4][4]={{ 1,0 , 0, 0},
						{0,1, 0, 0},
						{ 0, 0, 1, 0},
						{ vec.x,vec.y,vec.z, 1}};
	
	MMatrix matrixV(matrixF) ;
	return matrixV;
	 
	
}

MVector MG_poseReader::rotateVector( const int rotateAxis, const MVector vecToRotate, const double angle)
{
		MMatrix vetorToRotateM = fromVecToMatrix(vecToRotate);
		double rot = (angle*toRad);
		
		double rotArray[4][4];
		MVector finalV;

		switch ( rotateAxis )
			{

				case 0:
					if (rotateAxis==0)
					{
						rotArray[0][0]=1;
						rotArray[0][1]=0;
						rotArray[0][2]=0;
						rotArray[0][3]=0;

						rotArray[1][0]=0;
						rotArray[1][1]=cos(rot);
						rotArray[1][2]=-sin(rot);
						rotArray[1][3]=0;

						rotArray[2][0]=0;
						rotArray[2][1]=sin(rot);
						rotArray[2][2]=cos(rot);
						rotArray[2][3]=0;

						rotArray[3][0]=0;
						rotArray[3][1]=0;
						rotArray[3][2]=0;
						rotArray[3][3]=1;

						 
					}
				case 1:
					if (rotateAxis==1)
					{	



						rotArray[0][0]=cos(rot);
						rotArray[0][1]=0;
						rotArray[0][2]=sin(rot);
						rotArray[0][3]=0;

						rotArray[1][0]=0;
						rotArray[1][1]=1;
						rotArray[1][2]=0;
						rotArray[1][3]=0;

						rotArray[2][0]=-sin(rot);
						rotArray[2][1]=0;
						rotArray[2][2]=cos(rot);
						rotArray[2][3]=0;

						rotArray[3][0]=0;
						rotArray[3][1]=0;
						rotArray[3][2]=0;
						rotArray[3][3]=1;

			

					}

				case 2:
					if (rotateAxis==2)
					{
						
						rotArray[0][0]=cos(rot);
						rotArray[0][1]=-sin(rot);
						rotArray[0][2]=0;
						rotArray[0][3]=0;

						rotArray[1][0]=sin(rot);
						rotArray[1][1]=cos(rot);
						rotArray[1][2]=0;
						rotArray[1][3]=0;

						rotArray[2][0]=0;
						rotArray[2][1]=0;
						rotArray[2][2]=1;
						rotArray[2][3]=0;

						rotArray[3][0]=0;
						rotArray[3][1]=0;
						rotArray[3][2]=0;
						rotArray[3][3]=1;

					}


			}
	MMatrix rotArrayM(rotArray);
	vetorToRotateM*=rotArray;
	finalV.x=vetorToRotateM[3][0];
	finalV.y=vetorToRotateM[3][1];
	finalV.z=vetorToRotateM[3][2];	
	return finalV;
}

MVector MG_poseReader::matrixToAxisMatrix (const int &aimAxis , const MMatrix &matrix,const int normalize){

	MVector toVec;
	switch ( aimAxis )
			{

				case 0:
					if (aimAxis==0)
					{
						toVec[0]=matrix[0][0];
						toVec[1]=matrix[0][1];
						toVec[2]=matrix[0][2];

					
					}

					
				case 1:
					if (aimAxis==1)
					{
						toVec[0]=matrix[1][0];
						toVec[1]=matrix[1][1];
						toVec[2]=matrix[1][2];
				
					
					}
				case 2:
					if (aimAxis==2)
					{
						toVec[0]=matrix[2][0];
						toVec[1]=matrix[2][1];
						toVec[2]=matrix[2][2];


					}

			 

				
				 }
	toVec.normalize();


	return toVec;


}

MObject MG_poseReader::makePlane(const MVector& p1,const MVector& p2,const MVector& p3){

	MFnMesh meshFn;

	MPoint p1p (p1);
	MPoint p2p (p2);
	MPoint p3p (p3);
	MPointArray pArray;
	pArray.append(p1p);
	pArray.append(p2p);
	pArray.append(p3p);

	MIntArray polyCount;
	polyCount.append(3);
	MIntArray polyConnect;
	polyConnect.append(0);
	polyConnect.append(1);
	polyConnect.append(2);
	

	MFnMeshData data;
	MObject polyData = data.create();

	MStatus stat;
	meshFn.create(3,1,pArray,polyCount,polyConnect,polyData,&stat);
		


	
	return polyData;

}
double MG_poseReader::projVector (MVector vec1,MVector vec2)

{

		double proj; 
		float dot = vec1*vec2;
		float vec2L = vec2.length();
		if (vec2L!=0)
		{
		 proj = dot/vec2L;
		}else{
		 proj=0;
		}

		if ((proj<0) || (proj==-0))
			proj=0;
		return proj;
}