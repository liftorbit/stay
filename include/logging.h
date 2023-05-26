// STAY: Solid fuel propelled rocket
// Copyright (C) 2023  Liftorbit

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
#define S_AUTH 2
#define S_COUNTDOWN 3
#define S_LAUNCH 4
#define S_MECO 5

#include <Arduino.h>

class Logging {
    private:
        String fileLog;

        /**
         * @brief Get the log file name.
         * @return char 
         */
        char* getFilename();

    public:
        /**
         * @brief Begin SD card module and log file.
         * @return true 
         * @return false 
         */
        bool begin(String filename);

        /**
         * @brief Log a information.
         * 
         * @param status Rocket status
         * @param type Log type
         * @param message Log message
         */
        void log(int status, int type, String message);

        /**
         * @brief Get the log file.
         * @return String 
         */
        String getLog();
};

#endif