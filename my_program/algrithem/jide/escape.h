#ifndef H_ESCAPE
#define H_ESCAPE  

#include <iostream>
#include <list>

using namespace std;

/* Corresponding bit is set in case of below situatoins:
 *   A: Reach left border
 *   B: Reach right border
 *   C: Reach top border at the left side of the entry
 *   D: Reach top border at the right side of the entry
 *   E: Reach bottom border at the left side of the exit
 *   F: Reach bottom border at the right side of the exit
 *
 *     Bit 1@:   1   2   3   4   5   6
 * Indication:   A   B   C   D   E   F
 */
static const int REACH_LEFT_BIT            = 0x20; // 10 0000
static const int REACH_RIGHT_BIT           = 0x10; // 01 0000
static const int REACH_TOP_ON_LEFT_BIT     = 0x08; // 00 1000
static const int REACH_TOP_ON_RIGHT_BIT    = 0x04; // 00 0100
static const int REACH_BOTTOM_ON_LEFT_BIT  = 0x02; // 00 0010
static const int REACH_BOTTOM_ON_RIGHT_BIT = 0x01; // 00 0001

static const char NO_ESCAPE_1 = REACH_LEFT_BIT|REACH_RIGHT_BIT;                     // 11 0000
static const char NO_ESCAPE_2 = REACH_LEFT_BIT|REACH_TOP_ON_RIGHT_BIT;              // 10 0100
static const char NO_ESCAPE_3 = REACH_LEFT_BIT|REACH_BOTTOM_ON_RIGHT_BIT;           // 10 0001
static const char NO_ESCAPE_4 = REACH_RIGHT_BIT|REACH_TOP_ON_LEFT_BIT;              // 01 1000
static const char NO_ESCAPE_5 = REACH_RIGHT_BIT|REACH_BOTTOM_ON_LEFT_BIT;           // 01 0010
static const char NO_ESCAPE_6 = REACH_TOP_ON_LEFT_BIT|REACH_TOP_ON_RIGHT_BIT;       // 00 1100
static const char NO_ESCAPE_7 = REACH_TOP_ON_LEFT_BIT|REACH_BOTTOM_ON_RIGHT_BIT;    // 00 1001
static const char NO_ESCAPE_8 = REACH_TOP_ON_RIGHT_BIT|REACH_BOTTOM_ON_LEFT_BIT;    // 00 0110
static const char NO_ESCAPE_9 = REACH_BOTTOM_ON_LEFT_BIT|REACH_BOTTOM_ON_RIGHT_BIT; // 00 0011


// Record the counter of instances in order to prevent memory leak
class refcount {
public:
	refcount() {count ++; if(DBG) printf("Construct Object: %d\n", count);};
	virtual ~refcount() {count --; if(DBG) printf("Destruct Object: %d\n", count);};
	int getCurrentCount() {return count;}

protected:
	void log(const char* s) {if(DBG) printf("%s", s);};
private:
	static int count;
	static const bool DBG = false;
};

class Coordinate : public refcount {
public:
	Coordinate(double x, double y): posX(x), posY(y){log("Constructor Coordinate\n");};
	virtual ~Coordinate() {log("Destructor Coordinate\n");};

	bool operator == (const Coordinate& pos);
	bool operator != (const Coordinate& pos);
	double getX() const {return posX;}
	double getY() const {return posY;}
private:
	double posX;
	double posY;
};

class Detector : public refcount{
public:
	Detector(double x, double y, double r): radius(r) {
		log("Constructor Detector\n");
		center = new Coordinate(x, y);
	};

  virtual ~Detector() {delete center; log("Destructor Detector\n");};
	Coordinate& getCenter() const {return *center;}
	double getR() const {return radius;}
	bool isOverlap(const Detector& dector);	
	bool operator == (const Detector& detector);	
	bool operator != (const Detector& detector);
	bool isCoordinateInside(const Coordinate& pos);
private:
	Coordinate* center;
	double radius;
};

class Area : public refcount {
public:
	virtual ~Area() {delete entry; delete exit; log("Destructor Area\n");};
	Area(int wide, int height);
	
	int getWide() const {return wideX;}
	int getHeight() const {return heightY;}
	Coordinate& getEntry() const {return *entry;};
	Coordinate& getExit() const {return *exit;};
private:
	int wideX;
	int heightY;
	Coordinate* entry;
	Coordinate* exit;
};

typedef list<Detector*> DETECTORLIST;

class DetectorChain : public refcount {
public:
	DetectorChain(Area& area):
		 topX(-1),
		 topY(-1),
		 bottomX(-1),
		 bottomY(-1),
		 left(-1),
		 right(-1),
		 groupPosInfoByte(0),
		 inArea(area) {
		 log("Constructor DetectorChain\n");
	};
	
	virtual ~DetectorChain() {	log("Destructor DetectorChain\n");};
	
	bool CheckChain(const Detector& detector);
	int AddToChain(Detector& detector);
  bool findDetectorFromChain(const Detector& detector);  
  void ClearChain();  
	void mergeChain(DetectorChain& group);	
	double getTopX() const {return topX;}
	double getTopY() const {return topY;}
	double getBottomX() const {return bottomX;}
	double getBottomY() const {return bottomY;}
	double getLeft() const {return left;}
	double getRight() const {return right;}
	DETECTORLIST& getChain() {return chain;};
	char getGroupPosInfoByte() const {return groupPosInfoByte;}
private:
	void setReachLeft() {groupPosInfoByte|=REACH_LEFT_BIT;};
	void setReachRight() {groupPosInfoByte|=REACH_RIGHT_BIT;};
	void setReachTopOnLeft() {groupPosInfoByte|=REACH_TOP_ON_LEFT_BIT;};
	void setReachTopOnRight() {groupPosInfoByte|=REACH_TOP_ON_RIGHT_BIT;};
	void setReachBottomOnLeft() {groupPosInfoByte|=REACH_BOTTOM_ON_LEFT_BIT;};
	void setReachBottomOnRight() {groupPosInfoByte|=REACH_BOTTOM_ON_RIGHT_BIT;};

	double topX;
	double topY;
	double bottomX;
	double bottomY;
	double left;
	double right;
	char groupPosInfoByte;
	Area& inArea;
	DETECTORLIST chain;
};

typedef list<DetectorChain*> DETECTORCHAINLIST;

class DetectorManager : public refcount {
public:
  DetectorManager(int w, int h, int n, double x[], double y[], double r[]);
  virtual ~DetectorManager();
  bool canEscape();

private:
  bool noEscapeDetected(char posInfo);
  void findAndLinkChains(Detector& detector);
	DETECTORLIST mDetectors;
	DETECTORCHAINLIST mDetectorChains;
	Area* mArea;
};


#endif