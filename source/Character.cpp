#include "Character.h"

namespace Game {
    void Character::SetCharaPos(size_t index, string_view strPos, int x, int y) {
        if (index < 0 || index >= vchara.size()) {
            return;
        }
        vchara[index].gh_body = 0;
        vchara[index].gh_face = 0;
        vchara[index].strPos = strPos;
        vchara[index].x = x;
        vchara[index].y = y;
    }

    void Character::SetBody(int gh, string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.gh_body = gh;
            }
        }
    }

    void Character::SetFace(int gh, string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.gh_face = gh;
            }
        }
    }

    void Character::DeleteBody(string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.gh_body = 0;
            }
        }
    }

    void Character::DeleteFace(string_view strPos) {
        for (auto& pos : vchara) {
            if (strPos == pos.strPos) {
                pos.gh_face = 0;
            }
        }
    }

    void Character::Main() {
        for (const auto& pos : vchara) {
            if (pos.gh_body != 0) {
                DrawGraph(pos.x, pos.y, pos.gh_body, TRUE);
            }
            if (pos.gh_face != 0) {
                DrawGraph(pos.x, pos.y, pos.gh_face, TRUE);
            }
        }
    }
}