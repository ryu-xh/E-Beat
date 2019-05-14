//
//  Note.hpp
//  E-Beat
//
//  Created by 一ノ瀬琉聖 on 05/05/2019.
//

#ifndef __NOTE_HPP_
#define __NOTE_HPP_

#include "../ofMain.h"

enum NOTE_TYPE {
	NORMAL_NOTE,
	LONG_NOTE,
	AIR_UP_NOTE,
	AIR_DOWN_NOTE,
	AIR_LONG_NOTE
};

class Note {
public:
	Note();
	Note(NOTE_TYPE _type);
	~Note();

	void update();
	void draw(float x, float y);

	void setNoteImage(ofImage *img);
	void setNoteLength(int _length);
	void setNoteOption(NOTE_TYPE _type);
	void setPosition(int _pos);

	void hide();

private:
	NOTE_TYPE type;
	ofImage *noteImage[3];
	int length;
	int pos;

	const float noteHeight = 20;
	const float noteWidth = 14.25;
	const float noteBorder = 1.2;
	
	bool isVisible = true;
};

#endif // __NOTE_HPP_