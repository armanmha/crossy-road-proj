#include "gtest/gtest.h"
#include "../header/Lane.h"

TEST(VehicleLaneInitializationTests, ValidLaneCreation) {
    VehicleLane lane('=', 0, 5, 20, false, "Easy");
    EXPECT_EQ(lane.getShape(), '=');
    EXPECT_EQ(lane.getPosition().first, 0);
    EXPECT_EQ(lane.getPosition().second, 5);
    EXPECT_EQ(lane.getLength(), 20);
    EXPECT_FALSE(lane.isSafe());
}

TEST(VehicleLaneFunctionalityTests, SpawnVehicles) {
    VehicleLane lane('=', 0, 5, 50, false, "Easy");
    EXPECT_NO_THROW(lane.spawnVehicles());
}