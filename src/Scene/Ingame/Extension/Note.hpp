//
//  Note.hpp
//  E-Beat
//
//  Created by 一ノ瀬琉聖 on 05/05/2019.
//

#ifndef __NOTE_HPP_
#define __NOTE_HPP_

enum NOTE_TYPE {
	NORMAL,
	LONG,
	AIR_UP,
	AIR_DOWN,
	AIR_LONG
};

class Note {
public:
	Note();
	~Note();

	void update();
	void draw();

	void setNoteOption(NOTE_TYPE _type);


private:
	NOTE_TYPE type;
};

#endif // __NOTE_HPP_