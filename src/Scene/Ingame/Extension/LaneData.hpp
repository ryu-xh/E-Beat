﻿//
//  LaneData.hpp
//  E-Beat
//
//  Created by 一ノ瀬琉聖 on 29/07/2019.
//

// 레인에 대한 모든 데이터를 가지고 처리하는 곳
#ifndef __LANE_DATA_HPP_
#define __LANE_DATA_HPP_

#include <iostream>
#include "../ofMain.h"
#include "ofNote.hpp"

typedef struct Note {
	bool isExist = false; // 값이 존재하면 참
	bool isProcessed = false; // 노트가 처리되면 참
	string type; // 값
	string position; // 레인번호
	ofNote *note; // 노트 삭제의 상황을 위하여 액세스 하기 위해 가지는 값
	double syncTime; // 실제 처리 타이밍
} Note;


typedef struct NoteBar {
	vector<Note*> note;
} NoteBar;

typedef struct NoteLane {
	map<string, map<int, NoteBar>> lane;
} NoteLane;

typedef struct SlideNoteLane {
	map<string, map<int, map<string, NoteBar>>> lane;
} SlideNoteLane;


typedef struct Marker {
	double bpm = 0; // 옵션 1 증감
	double speed = 1; // 옵션 2 증감
	double barBeat = 0; // 옵션 4 증감
	double syncTime = 0;
	unsigned char option = 0;
} Marker;

class LaneData {
public: 

	void AddBPMList(int _num, double _value);

	void AddBPM(int _bar, int _key);
	void AddSpeed(int _bar, int _position, double _value);
	void AddBarBeat(int _bar, double _value);

	void AddNote(int _bar, string _key, string _value);
	void AddLongNote(int _bar, string _key, string _group, string _value);
	void AddSlideNote(int _bar, string _key, string _group, string _value);

	void Process();

private:
	// @NoteLane noteLane: noteLane.lane[레인번호][마디번호].note[값순서] 
	NoteLane noteLane;

	// @NoteLane longNoteLane: longNoteLane.lane[구분번호][마디번호].note[값순서]
	NoteLane longNoteLane;

	// @NoteLane slideLane: slideLane.lane[구분번호][마디번호][레인번호].note[값순서]
	SlideNoteLane slideLane;

	map<int, double> bpms;

	// 타임라인 값 참조: optionTimeLine[마디번호];
	map<int, Marker*> optionTimeLine;

};

#endif  /*  __LANE_DATA_HPP_ */