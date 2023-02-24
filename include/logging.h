// STAY B solid fuel propelled rocket
// Copyright (C) 2023  Firlast

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef LOGGING_h
#define LOGGING_h

#define LOG_INFO 1
#define LOG_WAIT 2
#define LOG_SUCCESS 3
#define LOG_ERROR 4

#define S_SETUP 1
#define S_READY 2
#define S_LAUNCH 3
#define S_TANK_CHANGE 4
#define S_WAIT_ALT 5
#define S_LANDING 6
#define S_LANDED 7

#include <Arduino.h>

class Logging {
    private:
        String fileLog;

    public:
        bool begin();
        void log(int status, int type, String message);

        String getLog();
};

#endif