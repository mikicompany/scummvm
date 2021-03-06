/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "sherlock/scalpel/scalpel_talk.h"
#include "sherlock/scalpel/scalpel_user_interface.h"
#include "sherlock/sherlock.h"
#include "sherlock/screen.h"

namespace Sherlock {

namespace Scalpel {

const byte SCALPEL_OPCODES[] = {
	128,	// OP_SWITCH_SPEAKER
	129,	// OP_RUN_CANIMATION
	130,	// OP_ASSIGN_PORTRAIT_LOCATION
	131,	// OP_PAUSE
	132,	// OP_REMOVE_PORTRAIT
	133,	// OP_CLEAR_WINDOW
	134,	// OP_ADJUST_OBJ_SEQUENCE
	135,	// OP_WALK_TO_COORDS
	136,	// OP_PAUSE_WITHOUT_CONTROL
	137,	// OP_BANISH_WINDOW
	138,	// OP_SUMMON_WINDOW
	139,	// OP_SET_FLAG
	140,	// OP_SFX_COMMAND
	141,	// OP_TOGGLE_OBJECT
	142,	// OP_STEALTH_MODE_ACTIVE
	143,	// OP_IF_STATEMENT
	144,	// OP_ELSE_STATEMENT
	145,	// OP_END_IF_STATEMENT
	146,	// OP_STEALTH_MODE_DEACTIVATE
	147,	// OP_TURN_HOLMES_OFF
	148,	// OP_TURN_HOLMES_ON
	149,	// OP_GOTO_SCENE
	150,	// OP_PLAY_PROLOGUE
	151,	// OP_ADD_ITEM_TO_INVENTORY
	152,	// OP_SET_OBJECT
	153,	// OP_CALL_TALK_FILE
	143,	// OP_MOVE_MOUSE
	155,	// OP_DISPLAY_INFO_LINE
	156,	// OP_CLEAR_INFO_LINE
	157,	// OP_WALK_TO_CANIMATION
	158,	// OP_REMOVE_ITEM_FROM_INVENTORY
	159,	// OP_ENABLE_END_KEY
	160,	// OP_DISABLE_END_KEY
	161,	// OP_CARRIAGE_RETURN
	0,		// OP_MOUSE_ON_OFF
	0,		// OP_SET_WALK_CONTROL
	0,		// OP_SET_TALK_SEQUENCE
	0,		// OP_PLAY_SONG
	0,		// OP_WALK_HOLMES_AND_NPC_TO_CANIM
	0,		// OP_SET_NPC_PATH_DEST
	0,		// OP_NEXT_SONG
	0,		// OP_SET_NPC_PATH_PAUSE
	0,		// OP_PASSWORD
	0,		// OP_SET_SCENE_ENTRY_FLAG
	0,		// OP_WALK_NPC_TO_CANIM
	0,		// OP_WALK_HOLMES_AND_NPC_TO_COORDS
	0,		// OP_WALK_HOLMES_AND_NPC_TO_COORDS
	0,		// OP_SET_NPC_TALK_FILE
	0,		// OP_TURN_NPC_OFF
	0,		// OP_TURN_NPC_ON
	0,		// OP_NPC_DESC_ON_OFF
	0,		// OP_NPC_PATH_PAUSE_TAKING_NOTES
	0,		// OP_NPC_PATH_PAUSE_LOOKING_HOLMES
	0,		// OP_ENABLE_TALK_INTERRUPTS
	0,		// OP_DISABLE_TALK_INTERRUPTS
	0,		// OP_SET_NPC_INFO_LINE
	0,		// OP_SET_NPC_POSITION
	0,		// OP_NPC_PATH_LABEL
	0,		// OP_PATH_GOTO_LABEL
	0,		// OP_PATH_IF_FLAG_GOTO_LABEL
	0,		// OP_NPC_WALK_GRAPHICS
	0,		// OP_NPC_VERB
	0,		// OP_NPC_VERB_CANIM
	0,		// OP_NPC_VERB_SCRIPT
	0,		// OP_RESTORE_PEOPLE_SEQUENCE
	0,		// OP_NPC_VERB_TARGET
	0		// OP_TURN_SOUNDS_OFF
};

/*----------------------------------------------------------------*/

ScalpelTalk::ScalpelTalk(SherlockEngine *vm) : Talk(vm) {
	static OpcodeMethod OPCODE_METHODS[] = {
		(OpcodeMethod)&ScalpelTalk::cmdSwitchSpeaker,
		(OpcodeMethod)&ScalpelTalk::cmdRunCAnimation,
		(OpcodeMethod)&ScalpelTalk::cmdAssignPortraitLocation,

		(OpcodeMethod)&ScalpelTalk::cmdPause,
		(OpcodeMethod)&ScalpelTalk::cmdRemovePortrait,
		(OpcodeMethod)&ScalpelTalk::cmdClearWindow,
		(OpcodeMethod)&ScalpelTalk::cmdAdjustObjectSequence,
		(OpcodeMethod)&ScalpelTalk::cmdWalkToCoords,
		(OpcodeMethod)&ScalpelTalk::cmdPauseWithoutControl,
		(OpcodeMethod)&ScalpelTalk::cmdBanishWindow,
		(OpcodeMethod)&ScalpelTalk::cmdSummonWindow,
		(OpcodeMethod)&ScalpelTalk::cmdSetFlag,
		(OpcodeMethod)&ScalpelTalk::cmdSfxCommand,

		(OpcodeMethod)&ScalpelTalk::cmdToggleObject,
		(OpcodeMethod)&ScalpelTalk::cmdStealthModeActivate,
		(OpcodeMethod)&ScalpelTalk::cmdIf,
		(OpcodeMethod)&ScalpelTalk::cmdElse,
		nullptr,
		(OpcodeMethod)&ScalpelTalk::cmdStealthModeDeactivate,
		(OpcodeMethod)&ScalpelTalk::cmdHolmesOff,
		(OpcodeMethod)&ScalpelTalk::cmdHolmesOn,
		(OpcodeMethod)&ScalpelTalk::cmdGotoScene,
		(OpcodeMethod)&ScalpelTalk::cmdPlayPrologue,
		
		(OpcodeMethod)&ScalpelTalk::cmdAddItemToInventory,
		(OpcodeMethod)&ScalpelTalk::cmdSetObject,
		(OpcodeMethod)&ScalpelTalk::cmdCallTalkFile,
		(OpcodeMethod)&ScalpelTalk::cmdMoveMouse,
		(OpcodeMethod)&ScalpelTalk::cmdDisplayInfoLine,
		(OpcodeMethod)&ScalpelTalk::cmdClearInfoLine,
		(OpcodeMethod)&ScalpelTalk::cmdWalkToCAnimation,
		(OpcodeMethod)&ScalpelTalk::cmdRemoveItemFromInventory,
		(OpcodeMethod)&ScalpelTalk::cmdEnableEndKey,
		(OpcodeMethod)&ScalpelTalk::cmdDisableEndKey,
		
		(OpcodeMethod)&ScalpelTalk::cmdCarriageReturn,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
	};

	_opcodes = SCALPEL_OPCODES;
	_opcodeTable = OPCODE_METHODS;
}

OpcodeReturn ScalpelTalk::cmdAssignPortraitLocation(const byte *&str) {
	People &people = *_vm->_people;

	++str;
	switch (str[0] & 15) {
	case 1:
		people._portraitSide = 20;
		break;
	case 2:
		people._portraitSide = 220;
		break;
	case 3:
		people._portraitSide = 120;
		break;
	default:
		break;
	}

	if (str[0] > 15)
		people._speakerFlip = true;

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdClearInfoLine(const byte *&str) {
	UserInterface &ui = *_vm->_ui;

	ui._infoFlag = true;
	ui.clearInfo();

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdClearWindow(const byte *&str) {
	UserInterface &ui = *_vm->_ui;
	
	ui.clearWindow();
	_yp = CONTROLS_Y + 12;
	_charCount = _line = 0;

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdDisplayInfoLine(const byte *&str) {
	Screen &screen = *_vm->_screen;
	UserInterface &ui = *_vm->_ui;
	Common::String tempString;

	++str;
	for (int idx = 0; idx < str[0]; ++idx)
		tempString += str[idx + 1];
	str += str[0];

	screen.print(Common::Point(0, INFO_LINE + 1), INFO_FOREGROUND, "%s", tempString.c_str());
	ui._menuCounter = 30;

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdElse(const byte *&str) {
	// If this is encountered here, it means that a preceeding IF statement was found,
	// and evaluated to true. Now all the statements for the true block are finished,
	// so skip over the block of code that would have executed if the result was false
	_wait = 0;
	do {
		++str;
	} while (str[0] && str[0] != _opcodes[OP_END_IF_STATEMENT]);

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdIf(const byte *&str) {
	++str;
	int flag = (str[0] - 1) * 256 + str[1] - 1 - (str[1] == 1 ? 1 : 0);
	++str;
	_wait = 0;

	bool result = flag < 0x8000;
	if (_vm->readFlags(flag & 0x7fff) != result) {
		do {
			++str;
		} while (str[0] && str[0] != _opcodes[OP_ELSE_STATEMENT] && str[0] != _opcodes[OP_END_IF_STATEMENT]);

		if (!str[0])
			_endStr = true;
	}

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdMoveMouse(const byte *&str) {
	Events &events = *_vm->_events;

	++str;
	events.moveMouse(Common::Point((str[0] - 1) * 256 + str[1] - 1, str[2]));
	if (_talkToAbort)
		return RET_EXIT;
	str += 3;
	
	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdPlayPrologue(const byte *&str) {
	Animation &anim = *_vm->_animation;
	Common::String tempString;

	++str;
	for (int idx = 0; idx < 8 && str[idx] != '~'; ++idx)
		tempString += str[idx];

	anim.play(tempString, 1, 3, true, 4);

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdRemovePortrait(const byte *&str) {
	People &people = *_vm->_people;

	if (_speaker >= 0 && _speaker < SPEAKER_REMOVE)
		people.clearTalking();
	pullSequence();
	if (_talkToAbort)
		return RET_EXIT;

	_speaker |= SPEAKER_REMOVE;
	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdSfxCommand(const byte *&str) {
	Sound &sound = *_vm->_sound;
	Common::String tempString;

	++str;
	if (sound._voices) {
		for (int idx = 0; idx < 8 && str[idx] != '~'; ++idx)
			tempString += str[idx];
		sound.playSound(tempString, WAIT_RETURN_IMMEDIATELY);

		// Set voices to wait for more
		sound._voices = 2;
		sound._speechOn = (*sound._soundIsOn);
	}

	_wait = 1;
	str += 7;

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdSummonWindow(const byte *&str) {
	Events &events = *_vm->_events;
	Screen &screen = *_vm->_screen;

	drawInterface();
	events._pressed = events._released = false;
	events.clearKeyboard();
	_noTextYet = false;

	if (_speaker != -1) {
		screen.buttonPrint(Common::Point(119, CONTROLS_Y), COMMAND_NULL, false, "Exit");
		screen.buttonPrint(Common::Point(159, CONTROLS_Y), COMMAND_NULL, false, "Up");
		screen.buttonPrint(Common::Point(200, CONTROLS_Y), COMMAND_NULL, false, "Down");
	}

	return RET_SUCCESS;
}

OpcodeReturn ScalpelTalk::cmdCarriageReturn(const byte *&str) {
	return RET_SUCCESS;
}

} // End of namespace Scalpel

} // End of namespace Sherlock
