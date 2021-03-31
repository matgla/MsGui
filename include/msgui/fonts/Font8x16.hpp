// This file is part of msgui project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#include "msgui/Font.hpp"

namespace msgui
{
namespace fonts
{


class Font8x16
{
public:
    constexpr static int width                       = 8;
    constexpr static int height                      = 16;
    constexpr static int numberOfCharacters          = 96;
    constexpr static int firstAsciiCharacterPosition = 31;

    using CharType = msgui::BitMap<8, 16>;
    using FontType = msgui::Font<
        width, height, numberOfCharacters, firstAsciiCharacterPosition>;

    constexpr static FontType data =
    {
        CharType { // unknown
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // space  ASCII (32)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // !  ASCII (33)
            0,0,0,0,0,0,0,0,  
            0,0,1,1,1,0,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,1,1,1,1,1,0,0,  
            0,0,1,1,1,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,1,0,0,0,0,  
            0,0,1,1,1,0,0,0,  
            0,0,1,1,1,0,0,0,  
            0,0,0,1,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // "  ASCII (34)
            0,0,0,0,0,0,0,0,  
            0,1,1,0,0,1,1,0,  
            0,1,1,0,0,1,1,0,  
            0,1,1,0,0,1,1,0,  
            0,1,1,0,0,1,1,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // # ASCII (35)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,1,0,0,1,0,0,  
            0,1,1,0,0,1,0,0,  
            0,1,1,1,1,1,1,0,  
            0,0,1,0,0,1,0,0,  
            0,0,1,0,0,1,0,0,  
            0,1,1,1,1,1,1,0,  
            0,0,1,0,0,1,0,0,  
            0,0,1,0,0,1,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // $ ASCII (36)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,    
            0,0,0,1,0,1,0,0,  
            0,0,1,1,1,1,1,0,  
            0,1,0,1,0,1,0,0,  
            0,1,0,1,0,1,0,0,  
            0,1,0,1,0,1,0,0,  
            0,1,0,1,0,1,0,0,  
            0,0,1,1,1,1,0,0,  
            0,0,0,1,0,1,1,0,  
            0,0,0,1,0,1,1,0,  
            0,0,0,1,0,1,1,0,  
            0,0,0,1,0,1,1,0,  
            0,1,1,1,1,1,0,0,  
            0,0,0,1,0,1,0,0,
            0,0,0,0,0,0,0,0,  
        },
        CharType { // % ASCII (37)
              0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
       },
        CharType { // & ASCII (38)
               0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
      },
        CharType { // ' ASCII (39)
                0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
     },
        CharType { // ( ASCII (40)
                 0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
    },
        CharType { // ) ASCII (41)
                  0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
   },
        CharType { //ASCII (42)
                   0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
  },
        CharType { // + ASCII (43)
        },
        CharType { // , ASCII (44)
        },
        CharType { // - ASCII (45)
        },
        CharType { // . ASCII (46)
        },
        CharType { // / ASCII (47)
        },
        CharType { // 0 ASCII (48)
        },
        CharType { // 1 ASCII (49)
        },
        CharType { // 2 ASCII (50)
        },
        CharType { // 3 ASCII (51)
        },
        CharType { // 4 ASCII (52)
        },
        CharType { // 5 ASCII (53)
        },
        CharType { // 6 ASCII (54)
        },
        CharType { // 7 ASCII (55)
        },
        CharType { // 8 ASCII (56)
        },
        CharType { // 9 ASCII (57)
        },
        CharType { // : ASCII (58)
        },
        CharType { // ; ASCII (59)
        },
        CharType { // < ASCII (60)
        },
        CharType { // = ASCII (61)
        },
        CharType { // > ASCII (62)
        },
        CharType { // ? ASCII (63)
        },
        CharType { // @ ASCII (64)
        },
        CharType { // A ASCII (65)
        },
        CharType { // B ASCII (66)
        },
        CharType { // C ASCII (67)
        },
        CharType { // D ASCII (68)
        },
        CharType { // E ASCII (69)
        },
        CharType { // F ASCII (70)
        },
        CharType { // G ASCII (71)
        },
        CharType { // H ASCII (72)
        },
        CharType { // I ASCII (73)
        },
        CharType { // J ASCII (74)
        },
        CharType { // K ASCII (75)
        },
        CharType {// L ASCII (76)
        },
        CharType { // M ASCII (77)
        },
        CharType { // N ASCII (78)
        },
        CharType { // O ASCII (79)
        },
        CharType { // P ASCII (80)
        },
        CharType { // Q ASCII (81)
        },
        CharType { // R ASCII (82)
        },
        CharType { // S ASCII (83)
        },
        CharType { // T ASCII (84)
        },
        CharType { // U ASCII (85)
        },
        CharType { // V ASCII (86)
        },
        CharType { // W ASCII (87)
        },
        CharType { // X ASCII (88)
        },
        CharType { // Y ASCII (89)
        },
        CharType { // Z ASCII (90)
        },
        CharType { // [ ASCII (91)
        },
        CharType { // \ ASCII (92)
        },
        CharType { // ] ASCII (93)
        },
        CharType { // ^ ASCII (94)
        },
        CharType { // _ ASCII (95)
        },
        CharType { // ` ASCII (96)
        },
        CharType { // a ASCII (97)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,1,1,1,1,0,0,  
            0,1,0,0,0,0,1,0,  
            0,0,0,0,0,0,1,0,  
            0,0,1,1,1,1,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,1,1,0,  
            0,0,1,1,1,0,1,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // b ASCII (98)
            0,0,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,1,1,1,0,0,0,  
            0,1,0,0,0,1,0,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,1,0,0,  
            0,1,1,1,1,0,0,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // c ASCII (99)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,1,1,1,1,0,  
            0,0,1,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,0,1,0,0,0,0,0,  
            0,0,0,1,1,1,1,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // d ASCII (100)
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,1,0,
            0,0,0,1,1,1,1,0,
            0,0,1,0,0,0,1,0,
            0,1,0,0,0,0,1,0,
            0,1,0,0,0,0,1,0,
            0,1,0,0,0,0,1,0,
            0,1,0,0,0,0,1,0,
            0,0,1,0,0,0,1,0,
            0,0,0,1,1,1,1,0,
            0,0,0,0,0,0,0,0,
        },
        CharType { // e ASCII (101)
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,0,0,0,0,0,0,  
            0,0,1,1,1,1,0,0,  
            0,1,0,0,0,0,1,0,  
            0,1,0,0,0,0,1,0,  
            0,1,1,1,1,1,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,1,0,0,0,0,0,0,  
            0,0,1,1,1,1,1,0,  
            0,0,0,0,0,0,0,0,  
        },
        CharType { // f ASCII (102)
        },
        CharType { // g ASCII (103)
        },
        CharType { // h ASCII (104)
        },
        CharType { // i ASCII (105)
        },
        CharType { // j ASCII (106)
        },
        CharType { // k ASCII (107)
        },
        CharType { // l ASCII (108)
        },
        CharType { // m ASCII (109)
        },
        CharType { // n ASCII (110)
        },
        CharType { // o ASCII (111)
        },
        CharType { // p ASCII (112)
        },
        CharType { // q ASCII (113)
        },
        CharType { // r ASCII (114)
        },
        CharType { // s ASCII (115)
        },
        CharType { // t ASCII (116)
        },
        CharType { // u ASCII (117)
        },
        CharType { // v ASCII (118)
        },
        CharType { // w ASCII (119)
        },
        CharType { // x ASCII (120)
        },
        CharType { // y ASCII (121)
        },
        CharType { // z ASCII (122)
        },
        CharType { // { ASCII (123)
        },
        CharType { // | ASCII (124)
        },
        CharType { // } ASCII (125)
        },
        CharType { // ~ ASCII (126)
        }
    };
};

} // namespace fonts
} // namespace msgui