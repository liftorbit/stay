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

#ifndef RCS_h
#define RCS_h

#include <Arduino.h>

#define RCS_WITHOUT_DATA 0
#define RCS_DISCONNECTED 1
#define READY_FOR_LAUNCH 2
#define LAUNCH_AUTHORIZED 3
#define NO_AUTHORIZED 4

class RCS {
    public:
        String begin();
        void sendLogs();
        int waitAuthorization();
};

#endif