#include <gtest/gtest.h>
#include <gmock/gmock.h>

int UIThreadMain();

TEST(test_case_name, test_name) {
}

int main(int argc, char **argv) {
  if (argc >= 2 && strcmp(argv[1], "--gui") == 0) {
    return UIThreadMain();
  }
  else {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}
