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

#ifndef GPS_h
#define GPS_h
#endif

class GPS {
    private:
        float lat, lon;
    
    public:
        /**
         * @brief Starts connection with GPS module.
         */
        void begin();

        /**
         * @brief Update latitude and longitude.
         * 
         */
        void update();

        /**
         * @brief Get the latitiude.
         * @return float 
         */
        float getLat();
        
        /**
         * @brief Get the longitude.
         * @return float 
         */
        float getLon();
};