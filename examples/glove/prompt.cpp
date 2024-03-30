#include "prompt.h"

#define TONE_ACCEPT 1300
#define TONE_BACK 400
#define TONE_MOVE 800

char prompt_start(const char* const* prompts, unsigned char promptCount)
{
	char choice = 0;
	prompt_draw(prompts, promptCount, choice);
	
	tautInput();
	while(true) {
		delay(10);
		updateInput();
		if(A_PRESSED) {
			arduboy.tunes.tone(TONE_ACCEPT, 20);
			return choice;
		}
		if(B_PRESSED) {		
			arduboy.tunes.tone(TONE_BACK, 20);
			return 255;
		}
		if(DOWN_PRESSED) {
			if(choice < promptCount-1) {
				choice++;
				arduboy.tunes.tone(TONE_MOVE, 20);
				prompt_draw(prompts, promptCount, choice);
			}
		}
		if(UP_PRESSED) {
			if(choice > 0) {
				choice--;
				arduboy.tunes.tone(TONE_MOVE, 20);
				prompt_draw(prompts, promptCount, choice);
			}
		}
	}
	
	return choice;
}
void prompt_draw(const char* const* prompts, unsigned char promptCount, char choice)
{
	arduboy.setTextSize(1);
	arduboy.setCursor(0, 0);
	arduboy.print(rps(&(prompts[0])));
	unsigned char startPos = (choice>=6) ? choice-6 : 0;
	unsigned char endPos = startPos + 6;
	for(unsigned char i = startPos; (i<promptCount) && (i<=endPos); ++i) {
		if(i == choice) {
			arduboy.setCursor(0, 8*(i+1-startPos));
			arduboy.print(">");
		} else {
			arduboy.setCursor(0, 8*(i+1-startPos));
			arduboy.print(" ");
		}
		arduboy.setCursor(8, 8*(i+1-startPos));
		arduboy.print(rps(&(prompts[i+1])));
	}
	arduboy.display(); 
}

const char okString[] PROGMEM = "Continue";
void error(const char* message)
{
	const char* messages[] = {message, okString};
	arduboy.clear();
	prompt_start(messages, 1);
}


char prompt_table(const char choiceString[], const char* const rowStrings[], char rows, char tabWidth, char tabCount, char& cursor) {
	char i;
	for(i=0; i<rows; ++i) {
		arduboy.setCursor(0, i*8+24);
		arduboy.print(rps(&(rowStrings[i])));
	}
	
	while(true) {
		updateInput();
		if(UP_PRESSED || DOWN_PRESSED || LEFT_PRESSED || RIGHT_PRESSED) {
			arduboy.setCursor((cursor%tabCount) * 6 * tabWidth, (cursor/tabCount) * 8 + 24);
			arduboy.print(" ");
		}
		if(A_PRESSED) {
			arduboy.tunes.tone(TONE_ACCEPT, 20);
			return pgm_read_byte_near(choiceString + cursor);
		} else if(B_PRESSED) {
			arduboy.tunes.tone(TONE_BACK, 20);
			return 0;
		} else if(UP_PRESSED) {
			arduboy.tunes.tone(TONE_MOVE, 20);
			if(cursor < tabCount)
				cursor += tabCount*rows;
			cursor -= tabCount;
		} else if(DOWN_PRESSED) {
			arduboy.tunes.tone(TONE_MOVE, 20);
			cursor += tabCount;
			if(cursor >= tabCount*rows)
				cursor -= tabCount*rows;
		} else if(LEFT_PRESSED) {
			arduboy.tunes.tone(TONE_MOVE, 20);
			if(cursor % tabCount == 0)
				cursor += tabCount;
			cursor --;
		} else if(RIGHT_PRESSED) {
			arduboy.tunes.tone(TONE_MOVE, 20);
			cursor ++;
			if(cursor % tabCount == 0)
				cursor -= tabCount;
		}
		arduboy.setCursor((cursor%tabCount) * 6 * tabWidth, (cursor/tabCount) * 8 + 24);
		arduboy.print(">");
		arduboy.display();
	}
}

const char alphaRowStrings_0[] PROGMEM = " 1 2 3 4 5 6 7 8 9 0";
const char alphaRowStrings_1[] PROGMEM = " Q W E R T Y U I O P";
const char alphaRowStrings_2[] PROGMEM = " A S D F G H J K L  ";
const char alphaRowStrings_3[] PROGMEM = " Z X C V B N M      ";

const char* const alphaRowStrings[] PROGMEM = {
	alphaRowStrings_0,
	alphaRowStrings_1,
	alphaRowStrings_2,
	alphaRowStrings_3
};
const char numAlphaRows = 4;
const char keyboardReturnString[] PROGMEM = "1234567890QWERTYUIOPASDFGHJKL ZXCVBNM   ";

char prompt_keyboard(char &cursorPos)
{
	return prompt_table(keyboardReturnString, alphaRowStrings, numAlphaRows, 2, 10, cursorPos);
}

void prompt_flash(const char* msg)
{
		arduboy.clear();
		arduboy.setCursor(0, 0);
		arduboy.print(msg);
		arduboy.display();
		delay(600);
}