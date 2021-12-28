#include "Character.h"

namespace Game {
    void Character::SetCharaPos(size_t index, string_view strPos, int x, int y) {
        if (index < 0 || index >= vchara.size()) {
            return;
        }
        vchara[index].img_body = Image();
        vchara[index].img_face = Image();
        vchara[index].strPos = strPos;
        vchara[index].x = x;
        vchara[index].y = y;
    }

    void Character::SetBody(string_view strFile, string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.img_body.SetImage(strFile, pos.x, pos.y, 1.0);
                pos.img_body.ChangeVisible(true);
            }
        }
    }

    void Character::SetFace(string_view strFile, string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.img_face.SetImage(strFile, pos.x, pos.y, 1.0);
                pos.img_face.ChangeVisible(true);
            }
        }
    }

    void Character::DeleteBody(string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.img_body.Clear();
            }
        }
    }

    void Character::DeleteFace(string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.img_face.Clear();
            }
        }
    }

    void Character::Main() {
        for (auto& pos : vchara) {
            pos.img_body.Main();
            pos.img_face.Main();
        }
    }
}