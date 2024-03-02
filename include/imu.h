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

#ifndef IMU_h
#define IMU_h

class IMU {
    private:
        float ax, ay, az;

    public:
        /**
         * @brief Begin BMI160 IMU.
         * @return true 
         * @return false 
         */
        bool begin();

        /**
         * @brief Update X, Y and Z position.
         */
        void updatePosition();

        /**
         * @brief Get the accelerometer X axis.
         * @return float 
         */
        float getAccelerometerX();

        /**
         * @brief Get the accelerometer Y axis.
         * @return float 
         */
        float getAccelerometerY();

        /**
         * @brief Get the accelerometer Z axis.
         * @return float 
         */
        float getAccelerometerZ();

        /**
         * @brief Convert IMU raw data to acceleration in m/s.
         * 
         * @param rawData Sensor raw data
         * @return float 
         */
        float convertRaw(int rawData);

        /**
         * @brief Convert axis to servo angle.
         * 
         * @param axis X, Y or Z angle
         * @return int 
         */
        int rawToServoAngle(float axis);
};

#endif