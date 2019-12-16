/* Sasha Willden
  18/11/2019 */

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	float getZNoiseValue(int x, int y);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//Declared camera
	ofCamera cam;

	//Declared mesh and object areas modified
	ofMesh mesh;
	int numCols = 50;
	int numRows = 50;
	int spacing = 4;

	//Declared type of shapes and modified
	ofBoxPrimitive box;
	int widthbox = 10;
	int heightbox = 10;
	int depthbox = 10;
	ofPlanePrimitive plane;

	//Declared video player
	ofVideoPlayer video;
	ofVideoPlayer video1;

	//Declared ints for box and plane
	signed int boxX;
	signed int boxY;
	signed int planeX;
	signed int planeY;

	//Declared light
	ofLight light;

};
