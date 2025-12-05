#include "gtest/gtest.h"
#include "../header/Vehicle.h"

TEST(VehicleTest, InitialSpeed) {
    Vehicle vehicle('V', 0, 0, 3, 5, false);
    EXPECT_EQ(vehicle.getSpeed(), 5);
}

TEST(VehicleTest, InitialShape) {
    Vehicle vehicle('V', 0, 0, 3, 5, false);
    EXPECT_EQ(vehicle.getShape(), 'V');
}

TEST(VehicleTest, InitialPosition) {
    Vehicle vehicle('V', 0, 0, 3, 5, false);
    EXPECT_EQ(vehicle.getPosition(), std::make_pair(0, 0));
}
