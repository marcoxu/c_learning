#include <stdio.h>
#include <stdlib.h>
#include "escape.h"

/*


wh(0, 0)(w, h)

((w/2, 0))((w/2, h))



boolean escape(int w, int h, int n, double[] x, double[] y, double[] r)

whni(x[i],y[i])r[i]

true or false
*/
using namespace std;

const float EPSINON = 0.00000001;

// Initialize the static counter
int refcount::count = 0;

bool Coordinate::operator == (Coordinate& pos) {
	return true;
}

bool Coordinate::operator != (Coordinate& pos) {
	return true;
}

bool Detector::isOverlap(Detector& dector) {
		return true;
}

bool Detector::operator == (Detector& detector) {
	return true;
}

bool Detector::operator != (Detector& detector) {
	return true;
}

bool Detector::isCoordinateInside(Coordinate& pos) {
		return true;
}

Area::Area(int wide, int height) {
}

bool DetectorChain::CheckChain(Detector& detector) {
	bool overlap = false;
  return overlap;
}

int DetectorChain::AddToChain(Detector& detector) {
	return 0;
}

bool DetectorChain::findDetectorFromChain(Detector& detector) {
  return true;
}

void DetectorChain::ClearChain() {
	this->chain.clear();
}

void DetectorChain::mergeChain(DetectorChain& group) {
}


DetectorManager::DetectorManager(int w, int h, int n, double x[], double y[], double r[]) {
};

DetectorManager::~DetectorManager() {
}

bool DetectorManager::canEscape() {
  bool isEscapable = true;
  return isEscapable;
}

bool DetectorManager::noEscapeDetected(char posInfo) {
	return false;
}

void DetectorManager::findAndLinkChains(Detector& detector) {
}


bool escape(int w, int h, int n, double x[], double y[], double r[]) {
	DetectorManager* detectors = new DetectorManager(w, h, n, x, y, r);
	
	return detectors->canEscape();
}

int main() {
  double detectorX[] = {1.1, 4.3, 5.1, 65, 42.1};
  double detectorY[] = {50.2, 37.2, 40.1, 2.2, 93.2};
  double detectorR[] = {10.0, 20.4, 4.5, 10.9, 20.0};
  bool canEscape = escape(100, 100, 5, detectorX, detectorY, detectorR);
  printf( "Check escapable result: %d\n", canEscape);
}
