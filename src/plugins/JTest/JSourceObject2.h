// $Id$
//
//    File: JSourceObject2.h
// Created: Mon Oct 23 22:39:14 EDT 2017
// Creator: davidl (on Darwin harriet 15.6.0 i386)
//

#ifndef _JSourceObject2_
#define _JSourceObject2_

#include <vector>
#include <utility>
#include <string>
#include <array>

#include <JANA/JObject.h>
#include "JLogger.h"

class JSourceObject2 : public JObject
{
	public:
		
		//STRUCTORS
		JSourceObject2(double aHitE, int aHitID) : mHitE(aHitE), mHitID(aHitID) { }

		//GETTERS
		int GetHitID(void) const{return mHitID;}
		double GetHitE(void) const{return mHitE;}
		std::vector<double> GetRandoms(void) const{return mRandoms;}

		//SETTERS
		void SetHitID(int aHitID){mHitID = aHitID;}
		void SetHitE(double aHitE){mHitE = aHitE;}
		void AddRandom(double aRandom){mRandoms.push_back(aRandom);}
		void MoveRandoms(std::vector<double>&& aRandoms){mRandoms = std::move(aRandoms);}

		// supress compiler warnings
		void SupressGarbageWarning(void){ if( (mGarbage.size()>1) && (mGarbage.size()<1) ) std::cerr << "Impossible!"; }

	private:

		std::vector<double> mRandoms;
		std::array<double, 20> mGarbage = {}; //Simulate a "large" object

		double mHitE;
		int mHitID;
};

//STREAM OPERATOR
inline JLog& operator<<(JLog& aLog, const JSourceObject2& aObject)
{
  aLog << "Hit: ID=" << aObject.GetHitID() << ", E=" << aObject.GetHitE()
       << ", nrandoms=" << aObject.GetRandoms().size();
	return aLog;
}

#endif // _JSourceObject2_
