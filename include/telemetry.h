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
         * @brief Send messages to base via RF.
         * 
         * @param message String message
         */
        void send(String message);

        /**
         * @brief Send telemetry data via RF with location.
         * 
         * @param engine Engine status
         * @param temp Temperature
         * @param alt Altitude
         * @param ps Pressure
         * @param acce Acceleration
         * @param lat Latitude
         * @param lon Longitude
         */
        void telemetry(bool engine, float temp, float alt, float ps, float acce, float lat, float lon);

        /**
         * @brief Send telemetry data via RF without location.
         * 
         * @param engine Engine status
         * @param temp Temperature
         * @param alt Altitude
         * @param ps Pressure
         * @param acce Acceleration
         */
        void telemetry(bool engine, float temp, float alt, float ps, float acce);

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