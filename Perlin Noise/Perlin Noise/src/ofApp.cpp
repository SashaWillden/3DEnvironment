/* Sasha Willden
  18/11/2019 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// enables graphs texture and media
	ofDisableArbTex(); // fades vertex + shows
	ofEnableDepthTest(); // box depth

	light.enable(); //Enabling light source

	// loading and play - two videos
	// video image from https://giphy.com/gifs/the-matrix-WoD6JZnwap6s8
	video.load("movies/matrix.mp4");
	video.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT); // GL texture
	video.play();
	// video image from https://gifer.com/en/E8SH
	video1.load("movies/glitch.mp4");
	video1.play();

	box = ofBoxPrimitive(widthbox, heightbox, depthbox);
	ofBackground(0);
	ofVec3f camDirection(0, 0, 20);
	cam.setPosition(0, -150, 60);
	cam.lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	cam.tiltDeg(10);

	for (int i = -numCols / 2; i < numCols / 2; i++) {
		for (int j = -numRows / 2; j < numRows / 2; j++) {
			mesh.addVertex(ofVec3f(i*spacing, j*spacing, 0)); // makes a new vertices
			mesh.addColor(ofFloatColor(0, 5, 0));  // added color at those vertices

			// background overlay width and height for matrix
			plane.set(i*8.4, j*8.4);
			plane.setResolution(2, 2);
		}
	}

	// Set up triangles' indices
	// only loop to -1 so they don't connect back to the beginning of the row
	for (int x = 0; x < numCols - 1; x++) {
		for (int y = 0; y < numRows - 1; y++) {
			int topLeft = x + numCols * y;
			int bottomLeft = x + 1 + numCols * y;
			int topRight = x + numCols * (y + 1);
			int bottomRight = x + 1 + numCols * (y + 1);
			mesh.addTriangle(topLeft, bottomLeft, topRight);
			mesh.addTriangle(bottomLeft, topRight, bottomRight);

		}
	}
}


//--------------------------------------------------------------
void ofApp::update() {

	// Update videos (should of been gifs, but gifs don't move on VS hence using mp4 files)
	video.update();
	video1.update();

	//Loops through mesh vertices at size in i
	for (int i = 0; i < mesh.getVertices().size(); i++) {
		float x = mesh.getVertex(i).x; //Passes through mesh i for x
		float y = mesh.getVertex(i).y; //Passes through mesh i for y


		mesh.setVertex(i, ofVec3f(x, y, getZNoiseValue(x, y))); //Mesh set for Z
		box.setPosition(boxX, boxY, getZNoiseValue(x, y) + 5); //box set for Z
		plane.setPosition(planeX, planeY, getZNoiseValue(x, y) - 5); //Plane set for Z
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	// two textures - one overlay vec3 and other for box

	//CONTROL INSTRUCTIONS - USE LOW CAPS
	ofDisableLighting(); //Disable lighting
	ofSetColor(255); //White text color
	ofDrawBitmapString("INSTRUCTIONS: ", 15, 80);
	ofDrawBitmapString("Fps: " + ofToString(ofGetFrameRate()), 15, 120);
	ofDrawBitmapString("Forward: 'W'", 15, 140);
	ofDrawBitmapString("Backward: 'S'", 15, 160);
	ofDrawBitmapString("Left: 'L'", 15, 180);
	ofDrawBitmapString("Right: 'D'", 15, 200);
	ofDrawBitmapString("Turn Forward: 'E'", 15, 220);
	ofDrawBitmapString("Turn Backward: 'Q'", 15, 240);
	ofEnableLighting(); //Enable lighting


	cam.begin(); //Cam begins

	video1.getTextureReference().bind(); //Enable texture
	box.draw(); //Box drawn
	video1.getTextureReference().unbind(); //Disable texture


	ofDisableLighting(); //Disable lighting
	video.getTextureReference().bind(); //Enable texture
	video.play(); //Video play
	plane.draw(); //Plane drawn
	mesh.drawWireframe(); // Vertex frames drawn
	video.getTextureReference().unbind(); //Disable texture
	ofEnableLighting(); //Enable lighting

	cam.end(); //Cam ends

}


float ofApp::getZNoiseValue(int x, int y) {

	float n1 = 0; //Float n1 at 0 (holds value)
	float n1_freq = 0.024; //Float n1_freq is frequency at 0.024 movement
	float n1_amp = 18; //Float n1_amp is amplitude at 18 for height of wave movement

	float time = ofGetFrameNum() * 0.006; //Float time is framed at 0.006 for slow wave frame

	n1 = ofNoise(x * n1_freq, y * n1_freq, time) * n1_amp; //Perlin Noise n1

	return n1; //Returns n1 from ofNoise

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// More camera controls i.e. tilt

	switch (key) {
	case 'w': // forward
		cam.dolly(-1);
		break;
	case 's': // backwards
		cam.dolly(1);
		break;
	case 'a': // left
		cam.panDeg(1);
		break;
	case 'd': // right
		cam.panDeg(-1);
		break;
	case 'q': // up
		cam.tilt(1);
		break;
	case 'e': // down
		cam.tilt(-1);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
