#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	auto len = 300;
	auto span = 1;
	for (auto x = len * -0.5 + span * 0.5; x < len * 0.5; x += span) {

		for (auto y = len * -0.5 + span * 0.5; y < len * 0.5; y += span) {

			int z = ofMap(ofNoise(x * 0.015, y * 0.015 + ofGetFrameNum() * 0.02), 0, 1, 0, 50);
			z = z - z % 10;

			this->mesh.addVertex(glm::vec3(x, y, z));
			this->mesh.addColor(ofColor(ofMap(z, 0, 50, 39, 239)));
		}
	}

	int n = len / span;
	for(auto x = 1; x < n; x++){

		for (auto y = 1; y < n; y++) {

			this->mesh.addIndex(x + y * n); 
			this->mesh.addIndex((x - 1) + (y - 1) * n);
			this->mesh.addIndex((x - 1) + y * n);

			this->mesh.addIndex(x + y * n);
			this->mesh.addIndex((x - 1) + (y - 1) * n);
			this->mesh.addIndex(x + (y - 1) * n);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(315);

	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}