#include "MG_vectorGL.h"

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
MTypeId MG_vectorGL::typeId( 0x80007 );

//Needed attributes


MObject MG_vectorGL::upVecX;
MObject MG_vectorGL::upVecY;
MObject MG_vectorGL::upVecZ;
MObject MG_vectorGL::upVec;
MObject MG_vectorGL::vecX;
MObject MG_vectorGL::vecY;
MObject MG_vectorGL::vecZ;
MObject MG_vectorGL::vecs;
MObject MG_vectorGL::fakeOut;
MObject MG_vectorGL::drawIt;
MObject MG_vectorGL::startPointX;
MObject MG_vectorGL::startPointY;
MObject MG_vectorGL::startPointZ;
MObject MG_vectorGL::startPoint;
MObject MG_vectorGL::arrowSize;

//Class


void* MG_vectorGL::creator()
{

	return new MG_vectorGL();
}

MStatus MG_vectorGL::initialize()
{ 
  
  //Declaring all the needed attribute function sets
  MFnEnumAttribute enumFn;
  MFnMatrixAttribute matrixFn;
  MFnNumericAttribute numFn;
  MFnCompoundAttribute compA;
  
  
  drawIt =numFn.create("drawIt","drw",MFnNumericData::kBoolean,1);
  numFn.setKeyable(true);
  numFn.setStorable(true);
  addAttribute(drawIt);
  
  arrowSize =numFn.create("arrowSize","as",MFnNumericData::kDouble,1);
  numFn.setKeyable(true);
  numFn.setStorable(true);
  addAttribute(arrowSize);
  
  
  fakeOut =numFn.create("fakeOut","fo",MFnNumericData::kBoolean,1);
  numFn.setKeyable(true);
  numFn.setStorable(true);
  addAttribute(fakeOut);
    
  
  
  upVecX =numFn.create("upVecX","uvx",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(upVecX);

  upVecY =numFn.create("upVecY","uvy",MFnNumericData::kDouble,1);

  numFn.setStorable(true);
  addAttribute(upVecY);


  upVecZ =numFn.create("upVecZ","uvz",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(upVecZ);

  upVec= compA.create("upVec","uv" );
  compA.addChild(upVecX);
  compA.addChild(upVecY);
  compA.addChild(upVecZ);

  addAttribute(upVec);
  
  vecX =numFn.create("vecX","vx",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(vecX);

  vecY =numFn.create("vecY","vy",MFnNumericData::kDouble,1);

  numFn.setStorable(true);
  addAttribute(vecY);


  vecZ =numFn.create("vecZ","vz",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(vecZ);

  vecs= compA.create("vecs","vs" );
  compA.addChild(vecX);
  compA.addChild(vecY);
  compA.addChild(vecZ);
  compA.setArray(true);

  addAttribute(vecs);  
  
  
  startPointX =numFn.create("startPointX","spx",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(startPointX);

  startPointY =numFn.create("startPointY","spy",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(startPointY);


  startPointZ =numFn.create("startPointZ","spz",MFnNumericData::kDouble,0);

  numFn.setStorable(true);
  addAttribute(startPointZ);

  startPoint= compA.create("startPoints","sp" );
  compA.addChild(startPointX);
  compA.addChild(startPointY);
  compA.addChild(startPointZ);
  compA.setArray(true);

  addAttribute(startPoint); 
  
  
  attributeAffects(arrowSize , fakeOut);
  attributeAffects(startPoint , fakeOut);
  attributeAffects(upVec , fakeOut);
  attributeAffects(drawIt , fakeOut);
  attributeAffects(vecs , fakeOut);
  
  return MS::kSuccess;
	

}

bool MG_vectorGL::isBounded() const
{ 
	return false ;
}

MStatus MG_vectorGL::compute(const MPlug& plug,MDataBlock& dataBlock)
	{
		


		return MS::kSuccess;
	}








void MG_vectorGL::draw( M3dView & view, const MDagPath & path, 
							 M3dView::DisplayStyle dispStyle,
							 M3dView::DisplayStatus status )
{ 
   
	MPlug drawItP (thisMObject(),drawIt);
	bool drawItV;
	drawItP.getValue(drawItV);
	
	
	MPlug arrowSizeP (thisMObject(),arrowSize);
	double arrowSizeV;
	arrowSizeP.getValue(arrowSizeV);
	
	MPlug upVecP (thisMObject(),upVec);
	MVector upVecV;
	upVecP.child(0).getValue(upVecV.x);
	upVecP.child(1).getValue(upVecV.y);
	upVecP.child(2).getValue(upVecV.z);
	
	MPlug vecsP (thisMObject(),vecs);
	MPlug startPointP (thisMObject(),startPoint);

	 
	int elemVecs   =  vecsP.numElements();
	int elemPoints =  startPointP.numElements();
	
	if ( drawItV == 0 )
	{
	  return ;
	  
	}
	
	if (elemVecs != elemPoints )
	{
	  return;
	  
	}
	
	
	// Draw it 
	view.beginGL();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2);
	if(status == M3dView::kLead)
		glColor4f(0.0,1.0,0.0,1.0f);
	else
		glColor4f(1.0,1.0,0.0,1.0f);
	
	for ( unsigned int i = 0 ; i < elemVecs ; i++ )
	{
	   vecsP.selectAncestorLogicalIndex( i , vecs);
	   startPointP.selectAncestorLogicalIndex( i , startPoint);

	
	   MVector currentVec ;
	   MPoint currentPoint;
	  
	  vecsP.child(0).getValue(currentVec.x);
	  vecsP.child(1).getValue(currentVec.y);
	  vecsP.child(2).getValue(currentVec.z);
	  
	  startPointP.child(0).getValue(currentPoint.x);
	  startPointP.child(1).getValue(currentPoint.y);
	  startPointP.child(2).getValue(currentPoint.z);
	    
	  drawArrow(currentVec , upVecV , arrowSizeV , currentPoint);
	  

	}


	glDisable(GL_BLEND);
	glPopAttrib();



}




 




void MG_vectorGL::drawArrow( MVector vec  ,  MVector upVec , double arrowSizeV ,  MPoint startPointV )
 {
	
	vec.normalize();
	upVec.normalize();

	
	double tipX , tipY , tipZ, 
	      corner1X ,corner1Y ,corner1Z ,
	      corner2X ,corner2Y ,corner2Z ,
	      corner3X ,corner3Y ,corner3Z ,
	      corner4X ,corner4Y ,corner4Z ;
	
	double dot = vec*upVec;
	if (dot >= 0.99 )
	{
	  tipX=(0.0)+startPointV.x;
	  tipY=(1.0*arrowSizeV)+startPointV.y;
	  tipZ=(0.0)+startPointV.z;
	  
	  
	  corner1Y=(0.9*arrowSizeV)+startPointV.y;
	  corner1X=(0.05*arrowSizeV)+startPointV.x ;
	  corner1Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner2Y=(0.9*arrowSizeV)+startPointV.y;
	  corner2X=(0.05*arrowSizeV)+startPointV.x;
	  corner2Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner3Y=(0.9*arrowSizeV)+startPointV.y;
	  corner3X=(-0.05*arrowSizeV)+startPointV.x;
	  corner3Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  corner4Y=(0.9*arrowSizeV)+startPointV.y;
	  corner4X=(-0.05*arrowSizeV)+startPointV.x;
	  corner4Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	}
 	
 	else if (dot <= -0.99)
	{
	  tipX=(0.0)+startPointV.x;
	  tipY=(1.0*arrowSizeV*-1)+startPointV.y;
	  tipZ=(0.0)+startPointV.z;
	  
	  
	  corner1Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner1X=(0.05*arrowSizeV)+startPointV.x ;
	  corner1Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner2Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner2X=(0.05*arrowSizeV)+startPointV.x;
	  corner2Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner3Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner3X=(-0.05*arrowSizeV)+startPointV.x;
	  corner3Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  corner4Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner4X=(-0.05*arrowSizeV)+startPointV.x;
	  corner4Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  
	}
	
	else
	{
	  
	   MVector cross1Pos = vec^upVec;
	   cross1Pos.normalize();
	   MVector cross2Pos = cross1Pos^vec;
	   
	   MVector vecScaled = vec*0.9;
	   MVector corner1 = (((cross1Pos*0.07)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner2 = (((cross2Pos*0.07)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner3 = (((cross1Pos*0.07*-1)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner4 = (((cross2Pos*0.07*-1)+vecScaled)*arrowSizeV)+startPointV;
	   
	   corner1X = corner1.x;
	   corner1Y = corner1.y;
	   corner1Z = corner1.z;
	   
	   corner2X = corner2.x;
	   corner2Y = corner2.y;
	   corner2Z = corner2.z;
	   
	   corner3X = corner3.x;
	   corner3Y = corner3.y;
	   corner3Z = corner3.z;
	   
	   corner4X = corner4.x;
	   corner4Y = corner4.y;
	   corner4Z = corner4.z;
	   
	   tipX = (vec.x*arrowSizeV) +startPointV.x;
	   tipY = (vec.y*arrowSizeV)+startPointV.y;
	   tipZ = (vec.z*arrowSizeV)+startPointV.z;
	}
	  
 	
	glBegin(GL_LINES);
		//draw the reader 
		glVertex3d(0+startPointV.x,0+startPointV.y,0+startPointV.z);
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

