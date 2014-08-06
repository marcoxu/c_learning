#include <stdio.h>
#include <stdlib.h>
#include "escape.h"

using namespace std;

const float EPSINON = 0.00000001;

// Initialize the static counter
int refcount::count = 0;

bool Coordinate::operator == (const Coordinate& pos) {
	double deltaX = pos.getX() - posX;
	double deltaY = pos.getY() - posY;
	if(!(deltaX>=-EPSINON && deltaX<= EPSINON)) {
		return false;
	} else if (!(deltaY>=-EPSINON && deltaY<= EPSINON)) {
		return false;
	}
	
	return true;
}

bool Coordinate::operator != (const Coordinate& pos) {
	if(*this == pos) {
		return false;
	}		
	return true;
}

bool Detector::isOverlap(const Detector& dector) {
	double deltaX = (center->getX() > dector.getCenter().getX())?
	                (center->getX()-dector.getCenter().getX()):(dector.getCenter().getX()-center->getX());
	double deltaY = (center->getY() > dector.getCenter().getY())?
	                (center->getY()-dector.getCenter().getY()):(dector.getCenter().getY()-center->getY());
	double sumRadius = radius + dector.getR();
	
	// ToDo: need to check over flow
	double deltaCenter = deltaX*deltaX - sumRadius*sumRadius + deltaY*deltaY;
	if(deltaCenter > EPSINON) {
		return false;
	} else {
		return true;
	}
}

bool Detector::operator == (const Detector& detector) {
	double deltaR = detector.getR() - radius;
	if(!(deltaR>=-EPSINON && deltaR<= EPSINON)) {
		return false;
	} else if (detector.getCenter() != *center) {
		return false;
	}
	
	return true;
}

bool Detector::operator != (const Detector& detector) {
	if(*this == detector) {
		return false;
	}		
	return true;
}

// Check if the specified coordinate is inside the detect area
bool Detector::isCoordinateInside(const Coordinate& pos) {
	double deltaX = (center->getX() > pos.getX())?
	                (center->getX()-pos.getX()):(pos.getX()-center->getX());
	double deltaY = (center->getY() > pos.getY())?
	                (center->getY()-pos.getY()):(pos.getY()-center->getY());

	double deltaCenter = deltaX*deltaX - radius*radius + deltaY*deltaY;
	if(deltaCenter > EPSINON) {
		return false;
	} else {
		return true;
	}
}

Area::Area(int wide, int height) {
	log("Constructor Area\n");
	wideX = wide;
	heightY = height;
	entry = new Coordinate(wideX/2, heightY);
	exit = new Coordinate(wideX/2, 0);
}

bool DetectorChain::CheckChain(const Detector& detector) {
	bool overlap = false;
	DETECTORLIST::iterator iter;
		
  for (iter = chain.begin(); iter != chain.end(); iter++) {
  	if((*iter)->isOverlap(detector)) {
  		overlap = true;
  		break;
  	}
  }
  return overlap;
}

// Add the spcified detectro into the chain
int DetectorChain::AddToChain(Detector& detector) {
	chain.push_back (&detector);
	
	double newTopX = detector.getCenter().getX();
	double newTopY = detector.getCenter().getY() + detector.getR();
	double newBottomX = detector.getCenter().getX();
	double newBottomY = detector.getCenter().getY() - detector.getR();
	double newLeft = detector.getCenter().getX() - detector.getR();
	double newRight = detector.getCenter().getX() + detector.getR();
	
	bool updateInfo = false;
	if(newRight > right || right < 0) {
		right = newRight;
		updateInfo = true;
	} 
	
	if (newLeft < left || left < 0) {
		left = newLeft;
		updateInfo = true;
	}
	
	if(newTopY > topY || topY < 0) {
		topY = newTopY;
		topX = newTopX;
		updateInfo = true;
	} 
	
	if (newBottomY < bottomY || bottomY < 0) {
		bottomY = newBottomY;
		bottomX = newBottomX;
		updateInfo = true;
	}
	
	if(detector.isCoordinateInside(inArea.getEntry())) {
		setReachTopOnLeft();
		setReachTopOnRight();
	}
	
	if(detector.isCoordinateInside(inArea.getExit())) {
		setReachBottomOnLeft();
		setReachBottomOnRight();
	}

	if(updateInfo) {
		// do update the position info
		// check left side
		if(left <= 0) {
			setReachLeft();
		}
		
		// check right side
		if(right >= inArea.getWide()) {
			setReachRight();
		}

		// check top side
		if(topY >= inArea.getHeight()) {
		  if(topX < inArea.getEntry().getX()) {
			  setReachTopOnLeft();
		  } else if(topX > inArea.getEntry().getX()) {
			  setReachTopOnRight();
		  }
		}

		// check bottom side
		if(bottomY <= 0) {
		  if(bottomX < inArea.getExit().getX()) {
			  setReachBottomOnLeft();
		  } else if(bottomX > inArea.getExit().getX()) {
			  setReachBottomOnRight();
		  }
		}
	}
}

// Check if the specified detector has overlap with the chain
bool DetectorChain::findDetectorFromChain(const Detector& detector) {
	bool found = false;
	DETECTORLIST::iterator iter;
		
  for (iter = this->chain.begin(); iter != this->chain.end(); iter++) {
  	if((**iter) == detector) {
  		found = true;
  		break;
  	}
  }
  return found;
}

void DetectorChain::ClearChain() {
	this->chain.clear();
}

// Merge the specified chain into the current one
void DetectorChain::mergeChain(DetectorChain& group) {
	DETECTORLIST::iterator iter;
		
  for (iter = group.getChain().begin(); iter != group.getChain().end(); iter++) {
  	if(!findDetectorFromChain(**iter)) {
  		AddToChain(**iter);
  	}
  }
  group.ClearChain();
}


DetectorManager::DetectorManager(int w, int h, int n, double x[], double y[], double r[]) {
	log("Constructor DetectorManager\n");
	mArea = new Area(w, h);
	
	if(n > 0) {
		int i;
		for(i=0;i<n;i++) {
			Detector* detector = new Detector(x[i], y[i], r[i]);
			mDetectors.push_back(detector);
		}
	}
};

DetectorManager::~DetectorManager() {
	DETECTORCHAINLIST::iterator iterChain;
	DETECTORLIST::iterator iter;

  for (iter = mDetectors.begin(); iter != mDetectors.end();) {
	  DETECTORLIST::iterator iterT = iter++;
	  Detector* detector = *iterT;
	  delete detector;
  }
  mDetectors.clear();
		
  for (iterChain = mDetectorChains.begin(); iterChain != mDetectorChains.end();) {
	  DETECTORCHAINLIST::iterator iterChainT = iterChain++;
	  DetectorChain* chain = *iterChainT;
	  delete chain;
  }
  mDetectorChains.clear();
  
	delete mArea;
	log("Destructor DetectorManager\n");
}

bool DetectorManager::canEscape() {
	DETECTORLIST::iterator iter;
		
  for (iter = mDetectors.begin(); iter != mDetectors.end(); iter++) {
  	if(mDetectorChains.size() > 0) {
  		findAndLinkChains(**iter);
  	} else {
  		DetectorChain* chain = new DetectorChain(*mArea);
  		chain->AddToChain(**iter);
			mDetectorChains.push_back(chain);
  	}
  }
  
  bool isEscapable = true;
	DETECTORCHAINLIST::iterator iterChain;
	
  for (iterChain = mDetectorChains.begin(); iterChain != mDetectorChains.end(); iterChain++) {
  	char ChainPosInfo = (*iterChain)->getGroupPosInfoByte();
  	if(noEscapeDetected(ChainPosInfo)) {
  		isEscapable = false;
  		break;
  	}
  }
  return isEscapable;
}

bool DetectorManager::noEscapeDetected(char posInfo) {
	if((posInfo & NO_ESCAPE_1) == NO_ESCAPE_1 ||
		 (posInfo & NO_ESCAPE_2) == NO_ESCAPE_2 ||
		 (posInfo & NO_ESCAPE_3) == NO_ESCAPE_3 ||
		 (posInfo & NO_ESCAPE_4) == NO_ESCAPE_4 ||
		 (posInfo & NO_ESCAPE_5) == NO_ESCAPE_5 ||
		 (posInfo & NO_ESCAPE_6) == NO_ESCAPE_6 ||
		 (posInfo & NO_ESCAPE_7) == NO_ESCAPE_7 ||
		 (posInfo & NO_ESCAPE_8) == NO_ESCAPE_8 ||
		 (posInfo & NO_ESCAPE_9) == NO_ESCAPE_9) {
		 	return true;
	}
	
	return false;
}

void DetectorManager::findAndLinkChains(Detector& detector) {
	// find out the chains that are linked by the specific detector
	DETECTORCHAINLIST ChainsForMerge;
	int chainCount = mDetectorChains.size();
	int i;
		
  for (i = 0; i< chainCount; i++) {
  	DetectorChain* chain = mDetectorChains.front();
  	if(chain->CheckChain(detector)) {
  		mDetectorChains.pop_front();
  		ChainsForMerge.push_back(chain);
  	} else {
  		mDetectorChains.pop_front();
  		mDetectorChains.push_back(chain);
  	}
  }
  
  // Merge the chains in ChainsForMerge since they are overlaped 
  if(ChainsForMerge.size() > 0) {
	  DetectorChain* chain = ChainsForMerge.front();
    ChainsForMerge.pop_front();
	  DETECTORCHAINLIST::iterator iter;
		
    for (iter = ChainsForMerge.begin(); iter != ChainsForMerge.end();) {
    	chain->mergeChain(**iter);
	    DETECTORCHAINLIST::iterator iterT = iter++;
	    ChainsForMerge.erase(iterT);
    }
    chain->AddToChain(detector);
    mDetectorChains.push_back(chain);
  } else {
  	DetectorChain* chain = new DetectorChain(*mArea);
    chain->AddToChain(detector);
    mDetectorChains.push_back(chain);
  }
}


bool escape(int w, int h, int n, double x[], double y[], double r[]) {
	DetectorManager* detectors = new DetectorManager(w, h, n, x, y, r);
	
  bool result = detectors->canEscape();
  delete detectors;
	
	return result;
}

int main() {
	bool canEscape = false;
	int n = 0;
	
  double detectorX1[] = {1.1, 4.3, 5.1, 65, 42.1};
  double detectorY1[] = {50.2, 37.2, 40.1, 2.2, 93.2};
  double detectorR1[] = {10.0, 20.4, 4.5, 10.9, 20.0};
  n = sizeof(detectorX1)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX1, detectorY1, detectorR1);
  printf( "Escapable result for detector group 1: %s\n", canEscape?"TRUE":"FALSE");
  
  // Entry is coverred by detectors
  double detectorX2[] = {45.1, 4.3, 5.1, 65, 42.1};
  double detectorY2[] = {98.2, 37.2, 40.1, 2.2, 93.2};
  double detectorR2[] = {10.0, 20.4, 4.5, 10.9, 20.0};
  n = sizeof(detectorX2)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX2, detectorY2, detectorR2);
  printf( "Escapable result for detector group 2: %s\n", canEscape?"TRUE":"FALSE");
  
  // Exit is coverred by detectors
  double detectorX3[] = {1.1, 51.2, 4.3, 65, 42.1};
  double detectorY3[] = {50.2, 3.1, 37.2, 2.2, 93.2};
  double detectorR3[] = {10.0, 12.5, 20.4, 10.9, 20.0};
  n = sizeof(detectorX3)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX3, detectorY3, detectorR3);
  printf( "Escapable result for detector group 3: %s\n", canEscape?"TRUE":"FALSE");
  
  // dector chain goes across the area from left to right
  double detectorX4[] = {10.1, 35.3, 50.1, 75, 90.1};
  double detectorY4[] = {50.2, 50.2, 50.1, 50.2, 50.2};
  double detectorR4[] = {15.0, 15.4, 15.5, 15.9, 15.0};
  n = sizeof(detectorX4)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX4, detectorY4, detectorR4);
  printf( "Escapable result for detector group 4: %s\n", canEscape?"TRUE":"FALSE");
  
  // Only one detector in middle of the area
  double detectorX5[] = {50.1};
  double detectorY5[] = {50.1};
  double detectorR5[] = {15.5};
  n = sizeof(detectorX5)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX5, detectorY5, detectorR5);
  printf( "Escapable result for detector group 5: %s\n", canEscape?"TRUE":"FALSE");
  
  // No detector in middle of the area
  double detectorX6[] = {};
  double detectorY6[] = {};
  double detectorR6[] = {};
  n = sizeof(detectorX6)/sizeof(double);
  canEscape = escape(100, 100, 0, detectorX6, detectorY6, detectorR6);
  printf( "Escapable result for detector group 6: %s\n", canEscape?"TRUE":"FALSE");
  
  // dector chain goes across the area from left to right
  double detectorX7[] = {10, 24, 38, 52, 66, 80, 94};
  double detectorY7[] = {10, 24, 38, 52, 66, 80, 94};
  double detectorR7[] = {11, 11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX7)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX7, detectorY7, detectorR7);
  printf( "Escapable result for detector group 7: %s\n", canEscape?"TRUE":"FALSE");
  
  // remove the detector on the far right side of the group 7
  double detectorX8[] = {10, 24, 38, 52, 66, 80};
  double detectorY8[] = {10, 24, 38, 52, 66, 80};
  double detectorR8[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX8)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX8, detectorY8, detectorR8);
  printf( "Escapable result for detector group 8: %s\n", canEscape?"TRUE":"FALSE");
  
  // remove the detector on the far left side of the group 7
  double detectorX9[] = {24, 38, 52, 66, 80, 94};
  double detectorY9[] = {24, 38, 52, 66, 80, 94};
  double detectorR9[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX9)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX9, detectorX9, detectorR9);
  printf( "Escapable result for detector group 9: %s\n", canEscape?"TRUE":"FALSE");

  // remove the 2nd detector of the group 7
  double detectorX10[] = {10, 38, 52, 66, 80, 94};
  double detectorY10[] = {10, 38, 52, 66, 80, 94};
  double detectorR10[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX10)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX10, detectorY10, detectorR10);
  printf( "Escapable result for detector group 10: %s\n", canEscape?"TRUE":"FALSE");

  // remove the 3rd detector of the group 7
  double detectorX11[] = {10, 24, 52, 66, 80, 94};
  double detectorY11[] = {10, 24, 52, 66, 80, 94};
  double detectorR11[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX11)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX11, detectorY11, detectorR11);
  printf( "Escapable result for detector group 11: %s\n", canEscape?"TRUE":"FALSE");

  // remove the 4th detector of the group 7
  double detectorX12[] = {10, 24, 38, 66, 80, 94};
  double detectorY12[] = {10, 24, 38, 66, 80, 94};
  double detectorR12[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX12)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX12, detectorY12, detectorR12);
  printf( "Escapable result for detector group 12: %s\n", canEscape?"TRUE":"FALSE");

  // remove the 5th detector of the group 7
  double detectorX13[] = {10, 24, 38, 52, 80, 94};
  double detectorY13[] = {10, 24, 38, 52, 80, 94};
  double detectorR13[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX13)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX13, detectorY13, detectorR13);
  printf( "Escapable result for detector group 13: %s\n", canEscape?"TRUE":"FALSE");

  // remove the 6th detector of the group 7
  double detectorX14[] = {10, 24, 38, 52, 66, 94};
  double detectorY14[] = {10, 24, 38, 52, 66, 94};
  double detectorR14[] = {11, 11, 11, 11, 11, 11};
  n = sizeof(detectorX14)/sizeof(double);
  canEscape = escape(100, 100, n, detectorX14, detectorY14, detectorR14);
  printf( "Escapable result for detector group 14: %s\n", canEscape?"TRUE":"FALSE");
}
