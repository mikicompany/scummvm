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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "fullpipe/fullpipe.h"

#include "fullpipe/objectnames.h"
#include "fullpipe/constants.h"

#include "fullpipe/gameloader.h"
#include "fullpipe/motion.h"
#include "fullpipe/scenes.h"
#include "fullpipe/statics.h"

#include "fullpipe/interaction.h"
#include "fullpipe/behavior.h"


namespace Fullpipe {

void scene16_initScene(Scene *sc) {
	g_vars->scene16_var01 = 200;
	g_vars->scene16_var02 = 200;
	g_vars->scene16_var03 = 300;
	g_vars->scene16_var04 = 300;
	g_vars->scene16_var05.clear();
	g_vars->scene16_var06 = 0;
	g_vars->scene16_var07 = 0;
	g_vars->scene16_var08 = 200;
	g_vars->scene16_wire = sc->getStaticANIObject1ById(ANI_WIRE16, -1);
	g_vars->scene16_mug = sc->getStaticANIObject1ById(ANI_MUG, -1);
	g_vars->scene16_jettie = sc->getStaticANIObject1ById(ANI_JETTIE, -1);
	g_vars->scene16_boot = sc->getStaticANIObject1ById(ANI_BOOT_16, -1);
	g_vars->scene16_var09 = 0;
	g_vars->scene16_sound = SND_16_034;

	if (g_fp->getObjectState(sO_Bridge) == g_fp->getObjectEnumState(sO_Bridge, sO_Convoluted)) {
		g_vars->scene16_var10 = 1;

		StaticANIObject *boy[2];
		boy[0] = sc->getStaticANIObject1ById(ANI_BOY, -1);
		boy[0]->loadMovementsPixelData();

		boy[1] = new StaticANIObject(boy[0]);
		sc->addStaticANIObject(boy[1], 1);
		
		int idx = 0;
		
		for (int i = 0; i < 3; i++) {
			g_vars->scene16_var05.push_back(boy[idx]);

			idx++;

			if (idx >= 2)
				idx = 0;
		}
		
		g_vars->scene16_var05.push_back(sc->getStaticANIObject1ById(ANI_GIRL, -1));

		for (int i = 0; i < 4; i++) {
			g_vars->scene16_var05.push_back(boy[idx]);

			idx++;

			if (idx >= 2)
				idx = 0;
		}
	} else {
		g_fp->setObjectState(sO_Girl, g_fp->getObjectEnumState(sO_Girl, sO_IsSwinging));

		g_vars->scene16_var10 = 0;

		StaticANIObject *ani = new StaticANIObject(g_fp->accessScene(SC_COMMON)->getStaticANIObject1ById(ANI_BEARDED_CMN, -1));
		ani->_movement = 0;
		ani->_statics = (Statics *)ani->_staticsList[0];
		sc->addStaticANIObject(ani, 1);
	}

	if (g_fp->getObjectState(sO_Girl) == g_fp->getObjectEnumState(sO_Girl, sO_IsLaughing)) {
		StaticANIObject *girl = sc->getStaticANIObject1ById(ANI_GIRL, -1);

		girl->show1(554, 432, MV_GRL_LAUGH_POPA, 0);
		girl->_priority = 20;
	}

	if (g_fp->getObjectState(sO_Cup) == g_fp->getObjectEnumState(sO_Cup, sO_In_16)) {
		g_vars->scene16_mug->_statics = g_vars->scene16_mug->getStaticsById(ST_MUG_EMPTY);
		g_vars->scene16_mug->_movement = 0;
		g_vars->scene16_mug->setOXY(409, 459);
		g_vars->scene16_mug->_priority = 5;
		g_vars->scene16_mug->_flags |= 4;
	}
}

int scene16_updateCursor() {
	g_fp->updateCursorCommon();

	if (g_fp->_objectIdAtCursor == PIC_SC16_TUMBA) {
		if (g_fp->_cursorId == PIC_CSR_DEFAULT)
			g_fp->_cursorId = PIC_CSR_ITN;
	} else {
		if (g_fp->_objectIdAtCursor == ANI_MUG && g_fp->_cursorId == PIC_CSR_ITN && g_vars->scene16_mug->_statics->_staticsId == ST_MUG_FULL)
			g_fp->_cursorId = PIC_CSR_ITN_GREEN;
	}

	return g_fp->_cursorId;
}

void sceneHandler16_laughSound() {
	warning("STUB: sceneHandler16_laughSound()");
}

void sceneHandler16_showBearded() {
	warning("STUB: sceneHandler16_showBearded()");
}

void sceneHandler16_showMugFull() {
	warning("STUB: sceneHandler16_showMugFull()");
}

void sceneHandler16_fillMug() {
	warning("STUB: sceneHandler16_fillMug()");
}

void sceneHandler16_startLaugh() {
	warning("STUB: sceneHandler16_startLaugh()");
}

void sceneHandler16_mugClick() {
	warning("STUB: sceneHandler16_mugClick()");
}

void sceneHandler16_showMan() {
	warning("STUB: sceneHandler16_showMan()");
}

void sceneHandler16_showMug() {
	warning("STUB: sceneHandler16_showMug()");
}

void sceneHandler16_hideMan() {
	warning("STUB: sceneHandler16_hideMan()");
}

void sceneHandler16_hideMug() {
	warning("STUB: sceneHandler16_hideMug()");
}

void sceneHandler16_hideWire() {
	warning("STUB: sceneHandler16_hideWire()");
}

void sceneHandler16_showWire() {
	warning("STUB: sceneHandler16_showWire()");
}

void sceneHandler16_sub01() {
	warning("STUB: sceneHandler16_sub01()");
}

void sceneHandler16_sub02() {
	warning("STUB: sceneHandler16_sub02()");
}

void sceneHandler16_sub03() {
	warning("STUB: sceneHandler16_sub03()");
}

int sceneHandler16(ExCommand *cmd) {
	if (cmd->_messageKind != 17)
		return 0;

	switch(cmd->_messageNum) {
	case MSG_SC16_LAUGHSOUND:
		sceneHandler16_laughSound();
		break;

	case MSG_SC16_SHOWBEARDED:
		sceneHandler16_showBearded();
		break;

	case MSG_SC16_SHOWMUGFULL:
		sceneHandler16_showMugFull();
		break;

	case MSG_SC16_FILLMUG:
		sceneHandler16_fillMug();
		break;

	case MSG_SC16_STARTLAUGH:
		sceneHandler16_startLaugh();
		break;

	case MSG_SC16_MUGCLICK:
		if (!g_fp->_aniMan->isIdle() || g_fp->_aniMan->_flags & 0x100)
			cmd->_messageKind = 0;
		else
			sceneHandler16_mugClick();

		break;

	case MSG_SC16_SHOWMAN:
		sceneHandler16_showMan();
		break;

	case MSG_SC16_SHOWMUG:
		sceneHandler16_showMug();
		break;

	case MSG_SC16_HIDEMAN:
		sceneHandler16_hideMan();
		break;

	case MSG_SC16_HIDEMUG:
		sceneHandler16_hideMug();
		break;

	case MSG_SC16_HIDEWIRE:
		sceneHandler16_hideWire();
		break;

	case MSG_SC16_SHOWWIRE:
		sceneHandler16_showWire();
		break;

	case 33:
		if (g_fp->_aniMan2) {
			int x = g_fp->_aniMan2->_ox;

			g_vars->scene16_var11 = x;
			g_vars->scene16_var12 = g_fp->_aniMan2->_oy;

			if (x < g_fp->_sceneRect.left + g_vars->scene16_var01) {
				g_fp->_currentScene->_x = x - g_vars->scene16_var03 - g_fp->_sceneRect.left;

				x = g_vars->scene16_var11;
			}

			if (x > g_fp->_sceneRect.right - g_vars->scene16_var01)
				g_fp->_currentScene->_x = x + g_vars->scene16_var03 - g_fp->_sceneRect.right;
		}

		if (g_vars->scene16_var10) {
			g_vars->scene16_var08++;

			if (g_vars->scene16_var08 < 280) {
				sceneHandler16_sub01();

				g_vars->scene16_var08 = 0;
			}
		}

		if (g_vars->scene16_var09) {
			if (g_fp->_aniMan->_movement)
				if (g_fp->_aniMan->_movement->_id == MV_MAN_TURN_RL)
					sceneHandler16_sub03();
		}

		g_fp->_behaviorManager->updateBehaviors();
		g_fp->startSceneTrack();

	}

	return 0;
}

} // End of namespace Fullpipe