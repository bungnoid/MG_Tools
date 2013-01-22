

#include "MG_cacheValue.h"

#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MVector.h>
#include <maya/MDoubleArray.h>

MObject MG_cacheValue::toCacheValue ;
MObject MG_cacheValue::iterationStored;
MObject MG_cacheValue::outValue;
MObject MG_cacheValue::cache;
MObject MG_cacheValue::pastIterationOutIndex;


MTypeId MG_cacheValue::typeId( 0x80010 );


void* MG_cacheValue::creator()
{

	return new MG_cacheValue();
}

MStatus MG_cacheValue::initialize()
	{ 
	  MFnNumericAttribute numFn;
	  
	  
	toCacheValue = numFn.create("toCacheValue","tcv",MFnNumericData::kDouble,0);
	numFn.setStorable(true);
	numFn.setKeyable(true);
	addAttribute(toCacheValue);
	
	
	cache = numFn.create("cache","ca",MFnNumericData::kDouble,0);
	numFn.setStorable(true);
	numFn.setKeyable(true);
	numFn.setArray(true);
	addAttribute(cache);	
	
	
	iterationStored = numFn.create("iterationStored","is",MFnNumericData::kLong,0);
	numFn.setStorable(true);
	numFn.setKeyable(true);
	addAttribute(iterationStored);	
	
	pastIterationOutIndex = numFn.create("pastIterationOutIndex","pii",MFnNumericData::kLong,1);
	numFn.setStorable(true);
	numFn.setKeyable(true);
	addAttribute(pastIterationOutIndex);	
		  
	outValue = numFn.create("outValue","out",MFnNumericData::kDouble,0);
	numFn.setStorable(false);
	numFn.setKeyable(false);
	numFn.setWritable(false);
	addAttribute(outValue);	    


	attributeAffects (toCacheValue ,outValue);
	attributeAffects (iterationStored ,outValue);
	attributeAffects (iterationStored ,cache);
	attributeAffects (pastIterationOutIndex ,outValue);


	
		return MS::kSuccess;
	}

MStatus MG_cacheValue::compute(const MPlug& plug,MDataBlock& dataBlock)
	{

		int iterationStoredV = dataBlock.inputValue(iterationStored).asInt();
		MArrayDataHandle cacheH = dataBlock.inputValue(cache);
		int cacheSize = cacheH.elementCount ();
		double toCacheValueV =  dataBlock.inputValue(toCacheValue).asDouble();
		int pastIterationOutIndexV = dataBlock.inputValue(pastIterationOutIndex).asInt();
		MPlug cacheP(thisMObject(),cache);
		//Let s loop 10 times
		
		if (cacheSize<(iterationStoredV+1))
		{
		  for(int i=0;i<(iterationStoredV+1);++i)
		  {
			  
		    cacheP.selectAncestorLogicalIndex(i,cache);
		    MDataHandle pointHandle;
		    cacheP.getValue(pointHandle);
		    
		  }
		  
		}
		
		MDoubleArray cacheDouble , finalCache ;
		cacheDouble.setLength(iterationStoredV);
		finalCache.setLength(iterationStoredV);
		cacheH.jumpToArrayElement(0);
		for (unsigned int i = 0 ; i < cacheH.elementCount(); i++ ,cacheH.next())
		{

		    
		  MDataHandle inH = cacheH.inputValue();
		  double cacheV = inH.asDouble();
		  
		  cacheDouble[i] = cacheV;
		  
		}
		std::cout<<cacheDouble[0]<<endl;
		cacheH.jumpToArrayElement(0);
		

		
		MArrayDataHandle cacheOutH = dataBlock.outputValue(cache);
		cacheOutH.jumpToArrayElement(0);
		for (int i = 0 ; i <= iterationStoredV ; i++ ,cacheOutH.next())
		{
		    
		    if ( i != 0)
		    {
		      
		      finalCache[i] = cacheDouble[i-1];
		      
		      MDataHandle outH = cacheOutH.outputValue();
		      outH.set(finalCache[i]);
	
		    }else{
		      finalCache[0] = toCacheValueV;
		      
		      MDataHandle outH = cacheOutH.outputValue();
		      outH.set(finalCache[0]);
		      
		    }
		     	    
		    
		}
		if ( (pastIterationOutIndexV > 0 ) && (pastIterationOutIndexV < cacheSize) )
		{
		  
		  dataBlock.outputValue(outValue).set(finalCache[pastIterationOutIndexV]);
		}else{
		dataBlock.outputValue(outValue).set(finalCache[1]);
		}
		
	      dataBlock.outputValue(outValue).setClean();
			
			return MS::kSuccess;
	}

