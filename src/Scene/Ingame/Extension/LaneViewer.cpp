﻿//
//  LaneViewer.cpp
//  E-Beat
//
//  Created by 一ノ瀬琉聖 on 01/05/2019.
//

#include "LaneViewer.hpp"

LaneViewer::LaneViewer() {
	gui.setup();
	gui.add(rX.setup("Rotate X", 56.6, -100, 100));
	gui.add(rY.setup("Rotate Y", 0, -100, 100));
	gui.add(rZ.setup("Rotate Z", 165, -360, 360));
	gui.add(tX.setup("Translate X", 903, 500, 1200));
	gui.add(tY.setup("Translate Y", 634.125, -500, 2400));
	gui.add(tZ.setup("Translate Z", -110, -300, 200));
	gui.add(x.setup("x", 0, -3000, 3000));
	gui.add(y.setup("y", 0, -3000, 3000));
	gui.add(w.setup("width", 113.8, -500, 500));
	gui.add(h.setup("height", 150, -500, 500));
	gui.add(tilt.setup("tilt", 0, -100, 100));

	texturePtr.loadImage("Scene/Ingame/LaneViewer/airNote.png");
}

LaneViewer::~LaneViewer() {

}

void LaneViewer::update() {
	texturePtr.resize(w, h / 2);

	airNote.clear();
	airNote.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	airNote.addVertex(ofPoint(x, y, 0));
	airNote.addTexCoord(ofVec2f(0, 0));
	airNote.addVertex(ofPoint(x + w, y, 0));
	airNote.addTexCoord(ofVec2f(w, 0));
	airNote.addVertex(ofPoint(x + w - tilt, y + (h / 2), 0));
	airNote.addTexCoord(ofVec2f(w, h / 2));
	airNote.addVertex(ofPoint(x - tilt, y + (h / 2), 0));
	airNote.addTexCoord(ofVec2f(0, h / 2));
	airNote.addVertex(ofPoint(x, y, 0));
	airNote.addTexCoord(ofVec2f(0, 0));
	
}

void LaneViewer::draw() {
	ofPushMatrix();
		ofRotateX(rX);
		ofTranslate(tX, tY, tZ);
		ofSetColor(255, 255, 255, 100);
		ofDrawRectangle(x, y, w, -700);

		ofRotateX(rX - (rX*2));
		ofRotateY(rY);
		ofRotateX(rZ);
		
		ofSetColor(255, 255, 255, 255);
		texturePtr.bind();
		airNote.draw();
		texturePtr.unbind();
	ofPopMatrix();

	gui.draw();
}