//
// Copyright (C) Marco Giordano
// 
// File: MG_locatorCmd.cpp
//
// MEL Command: MG_locator
//
// Author: Marco Giordano


//*******************************************************************************************************************
 

#include <maya/MPxCommand.h>
#include <maya/MFnPlugin.h>
#include <maya/MDagModifier.h>
#include <maya/MSyntax.h>
#include <maya/MGlobal.h>
#include <maya/MArgDatabase.h>
#include <string>
#include <maya/MPointArray.h>
#include <maya/MPoint.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnNurbsCurve.h>


using namespace std;
//*******************************************************************************************************************

//Curve for built the locator
//curve curve -d 1 -p 0 0 2 -p 0 0 0 -p 0 0 -2 -p 0 0 0 -p -2 0 0 -p 2 0 0 -p 0 0 0 -p 0 2 0 -p 0 -2 0 -p 0 0 0 -k 0 -k 1 -k 2 -k 3 -k 4 -k 5 -k 6 -k 7 -k 8 -k 9

class MG_loc : public MPxCommand
{
 public:
	virtual MStatus doIt (const MArgList&);
	virtual MStatus undoIt();
 	virtual MStatus redoIt();
	virtual bool isUndoable() const { return true; } 
	static void *creator() 
	 {
		 return new MG_loc;
	 }
	static MSyntax newSyntax();
private:
	MDagModifier dgMod;
	MObject loc;
};



const char *nameFlag ="-n", *nameLongFlag = "-name";
const char *positionFlag ="-p", *positionLongFlag = "-position";
MString name = "MG_loc";
double tx = 0;
double ty = 0;
double tz = 0;
MSyntax MG_loc::newSyntax()
{
	MSyntax syntax;
	syntax.addFlag(nameFlag,nameLongFlag,MSyntax::kString);
	syntax.addFlag(positionFlag,positionLongFlag,MSyntax::kDouble,MSyntax::kDouble,MSyntax::kDouble);
	return syntax;
}

  

MStatus MG_loc::doIt(const MArgList &args)
{
	MArgDatabase argData(syntax(),args);
		
	if (argData.isFlagSet(nameFlag))
		argData.getFlagArgument(nameFlag,0,name);
	if (argData.isFlagSet(positionFlag))
		argData.getFlagArgument(positionFlag,0,tx);
	if (argData.isFlagSet(positionFlag))
		argData.getFlagArgument(positionFlag,1,ty);
	if (argData.isFlagSet(positionFlag))
		argData.getFlagArgument(positionFlag,2,tz);
	return redoIt();
} 


MStatus MG_loc::undoIt()
{
	dgMod.deleteNode(loc);
	return dgMod.doIt();
} 

MStatus MG_loc::redoIt()
{
	MStatus stat;

	//Declaring and appending vertexes positions
	MPoint const oneP (0,0,2);
	MPoint const twoP (0,0,0);
	MPoint const threeP (0,0,-2);
	MPoint const fourP (0,0,0);
	MPoint const fiveP (-2,0,0);
	MPoint const sixP (2,0,0);
	MPoint const sevenP (0,0,0);
	MPoint const eightP (0,2,0);
	MPoint const nineP (0,-2,0);
	MPoint const tenP (0,0,0);

	MPointArray controlVertexs;
	controlVertexs.append(oneP);
	controlVertexs.append(twoP);
	controlVertexs.append(threeP);
	controlVertexs.append(fourP);
	controlVertexs.append(fiveP);
	controlVertexs.append(sixP);
	controlVertexs.append(sevenP);
	controlVertexs.append(eightP);
	controlVertexs.append(nineP);
	controlVertexs.append(tenP);

	//Knots sequance
	double knot1 = 0;
	double knot2 = 1;
	double knot3 = 2;
	double knot4 = 3;
	double knot5 = 4;
	double knot6 = 5;
	double knot7 = 6;
	double knot8 = 7;
	double knot9 = 8;
	double knot10 = 9;

	MDoubleArray knotsArray;
	knotsArray.append(knot1);
	knotsArray.append(knot2);
	knotsArray.append(knot3);
	knotsArray.append(knot4);
	knotsArray.append(knot5);
	knotsArray.append(knot6);
	knotsArray.append(knot7);
	knotsArray.append(knot8);
	knotsArray.append(knot9);
	knotsArray.append(knot10);
	
	//degree
	int deg = 1;

	//Creating locator
	loc = dgMod.createNode("nurbsCurve");
	dgMod.doIt();

	MFnNurbsCurve curveFn;
	curveFn.create(controlVertexs,knotsArray,deg,MFnNurbsCurve::kOpen,false,false,loc,&stat);
	if (MS::kSuccess!=stat)
		cout <<"Error creating the curve \n";

	dgMod.renameNode(loc, name);
	MFnDependencyNode nodeFn;
	MPlug plugTx = nodeFn.findPlug("translateX");
	MPlug plugTy = nodeFn.findPlug("translateY");
	MPlug plugTz = nodeFn.findPlug("translateZ");
	plugTx.setValue(tx);
	plugTy.setValue(ty);
	plugTz.setValue(tz);
	

	return stat;
}

MStatus initializePlugin (MObject obj)
{
	MFnPlugin pluging (obj,"Marco Giordano","1.0");

    MStatus stat;
	stat=pluging.registerCommand("MG_loc",MG_loc::creator,MG_loc::newSyntax);
    if(!stat)
    {
        stat.perror("registerCommand failed");
    }

    return stat;
} 

MStatus uninitializePlugin( MObject obj)
{
	MFnPlugin plugin (obj); 
	MStatus stat;
	stat=plugin.deregisterCommand("MG_loc");
	if(!stat)
	{
		stat.perror("deregisterCommand failed");
	}

	return stat;
}
