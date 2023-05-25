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

#ifndef BAROMETER_h
#define BAROMETER_h

class Barometer {
    private:
        float groundAltitude;

    public:
        /**
         * @brief Begin BMP280 barometer.
         * @return true 
         * @return false 
         */
        bool begin();

        /**
         * @brief Get the altitude from barometer.
         * @return float 
         */
        float getAltitude();

        /**
         * @brief Get the pressure from barometer.
         * @return float 
         */
        float getPressure();

        /**
         * @brief Get the temperature from barometer.
         * @return float 
         */
        float getTemperature();

        /**
         * @brief Get the ground distance.
         * @return float 
         */
        float getGroundDistance();

        /**
         * @brief Get the average speed.
         * 
         * @param periodOfTime Time to perform the measurement.
         * @return float 
         */
        float getAverageSpeed(int periodOfTime);

        /**
         * @brief Save ground altitude. This data is
         * used to get ground distance.
         */
        void saveGroundAltitude();
};

#endif