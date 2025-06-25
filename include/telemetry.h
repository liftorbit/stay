// STAY: Solid fuel propelled rocket
// Copyright (C) 2024  Liftorbit

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

#ifndef TELEMETRY_h
#define TELEMETRY_h
#endif

#include <Arduino.h>

class Telemetry {
    public:
        /**
         * @brief Start serial communication
         * 
         */
        void begin();

        /**
         * @brief Send computer logs
         * @param log Computer log
        */
        void sendLog(String log);

        /**
         * @brief Send messages to base via RF.
         * 
         * @param message String message
         */
        void send(String message);

        /**
         * @brief Send a signal to base via RF.
         * 
         * @param code Signal code
         */
        void send(char code);

        /**
         * @brief Send telemetry data to base via RF
         * 
         * @param engine Engine status
         * @param temp Temperature
         * @param alt Altitude
         * @param ps Pressure
         * @param lat Latitude
         * @param lon Longitude
         * @param acZ Z-axis acceleration
         * @param acX X-axis acceleration
         * @param acY Y-axis acceleration
         */
        void send(bool engine, float temp, float alt, float ps, double lat, double lon, float acZ, float acX, float acY);

        /**
         * @brief Check if data is available.
         * 
         * @return true 
         * @return false 
         */
        bool dataAvailable();

        /**
         * @brief Receive data via RF.
         * 
         * @return String
         */
        String receive();
};