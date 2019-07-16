//
//  MusicSelect.cpp
//  E-Beat
//
//  Created by 一ノ瀬琉聖 on 20/03/2019.
//

#include "MusicSelect.hpp"

MusicSelect::MusicSelect() {
}

MusicSelect::MusicSelect(FileSystem* _file){
	file = _file;
    maxCountMusic = file->getMusicCount();
	
	musicLinerBackRect.loadImage("Scene/MusicSelect/BackRect.png");
	musicLinerBackRect.resize(1920, 1080);

	// 하단 버튼
	bottombuttonsRect.loadImage("Scene/MusicSelect/BottomButtons.png");
	bottombuttonsRect.resize(1920, 1080);

	// 하단 키빔
	button[0].setCount(0);
	button[0].setColor("Green");
	button[1].setCount(1);
	button[1].setColor("Green");
	button[2].setCount(2);
	button[2].setColor("White");
	button[3].setCount(3);
	button[3].setColor("Red");

	bgaPlayer = new ofBackgroundPlayer();

	slider.setMaxCount(maxCountMusic);
	musicList.setMaxCount(maxCountMusic);
	
	for (int i = 0; i < maxCountMusic; i++) {
		musicList.addItem(file->getMusicData(i));
	}

	musicList.setPosition(0);
}

MusicSelect::~MusicSelect() {

}

void MusicSelect::update(bool keys[256]) {
	// 키 갱신
	if (keys['d'] == true)
		button[0].Active();

	if (keys['f'] == true)
		button[1].Active();

	if (keys['j'] == true)
		button[2].Active();

	if (keys['k'] == true)
		button[3].Active();

	// BGA 갱신
	bgaPlayer->update();

	// 노래 리스트 갱신
	musicList.update();
	
	// 키빔 갱신
	button[0].update();
	button[1].update();
	button[2].update();
	button[3].update();

	//if (keys['a'])
		//cout << bgaPlayer->getCurrentFrame() << endl;
	
	//여러가지 갱신
	updateMusic();
	if(!musicList.isMoving())
		if (isLoadCue) {
			if (LoadCueCounter-- < 0) {
				bgaPlayer->loadAsync(file->getMusicData(pos));
				bgaPlayer->videoPlay();
				isLoadCue = false;
			}
		}
}

void MusicSelect::draw(){
	// BGA 부분 처리
	//setMusic(pos);
	bgaPlayer->draw(-265, -150, 2450, 1380);
	
	// 하단 버튼 키빔
	button[0].draw();
	button[1].draw();
	button[2].draw();
	button[3].draw();

	// 백그라운드 Rect
	musicLinerBackRect.draw(0, 0);


	// 하단 버튼 인디케이터
	bottombuttonsRect.draw(0, 0);

	
	// 하단 슬라이더
	slider.draw();
	
	// 카드 카메라 이동
	musicList.draw();

	// 상태 표시
	ofDrawBitmapStringHighlight("MusicSelect Scene", 20, 20);
	//ofDrawBitmapStringHighlight("Amount : " + to_string(mouseX), 20, 40);
	//ofDrawBitmapStringHighlight("Iterations : " + to_string(mouseY), 20, 60);
	

	// 흰색으로 설정을 왜하느냐 묻는다면 그것은 수련이 부족한 것
	ofSetColor(255, 255, 255, 255);
}

void MusicSelect::keyPressed(int key) {
	if (key == 'd') {
		--pos;
	}
		
	if (key == 'f') {
		++pos;	
	}
	
	if (key == 'k') {
		// 게임 시작 처리
		file->setNowMusicNumber(pos);
		isSelectedMusic = true;
	}

}

void MusicSelect::keyReleased(int key) {

}

bool MusicSelect::isReady() {
	return isSelectedMusic;
}


void MusicSelect::updateMusic() {
	static int p_pos = -1;
	if (p_pos == pos) return;

	if (pos < 0) {
		pos = 0;
		return;
	}

	if (pos >= maxCountMusic) {
		pos = maxCountMusic - 1;
		return;
	}

	p_pos = pos;

	musicList.setPosition(pos);
	slider.setPosition(pos);

	bgaPlayer->SetLoopFrame(2005, 3072);
	
	//bgaPlayer->setMusic(pos);

	isLoadCue = true;
	LoadCueCounter = 15;
	bgaPlayer->videoStop();
}
