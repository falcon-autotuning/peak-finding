#include "peak-finding/peak-finding.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace findPeaks;

namespace {
std::vector<double> load_data(const std::string &path) {
  std::ifstream file(path);
  if (!file)
    throw std::runtime_error("cannot open " + path);
  std::string line;
  std::getline(file, line);
  std::vector<double> values;
  while (std::getline(file, line))
    values.push_back(std::stod(line.substr(line.find(',') + 1)));
  return values;
}
} // namespace

class PeakFindingTest : public ::testing::Test {
protected:
  std::vector<double> sim_1 = 
      load_data(DATA_DIR "/sim_1.csv");
  std::vector<double> sim_2 =
      load_data(DATA_DIR "/sim_2.csv");
  std::vector<double> sim_3 =
      load_data(DATA_DIR "/sim_3.csv");
  std::vector<double> sim_4 =
      load_data(DATA_DIR "/sim_4.csv");
  std::vector<double> sim_5 =
      load_data(DATA_DIR "/sim_5.csv");
  std::vector<double> sim_6 = 
      load_data(DATA_DIR "/sim_6.csv");
};

TEST_F(PeakFindingTest, sim_1_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      43, 60, 74, 90, 104, 120, 136, 147, 163, 174, 189, 201, 217,
      231, 244, 257, 267, 279, 294, 309, 323, 336, 353, 371, 386, 
      401, 416, 429, 440, 455, 469, 482, 496, 512, 529, 542, 556, 
      569, 583, 596, 609, 625, 637, 652, 663, 679, 695, 707, 723, 
      734, 747, 758, 772, 788
    };

  auto peaks = find_peaks(sim_1, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, sim_2_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      154, 190, 219, 253, 291, 320, 349, 381, 412, 452, 487, 521, 
      562, 593
    };

  auto peaks = find_peaks(sim_2, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, sim_3_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      284, 305, 324, 350, 368, 387, 407, 434, 456, 474, 500, 
      519, 536, 560, 587, 613, 629, 651, 669, 689, 707, 732, 
      751, 778
    };

  auto peaks = find_peaks(sim_3, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, sim_4_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      215, 235, 259, 283, 306, 328, 352, 377, 392, 412, 429, 
      454, 471, 495, 514, 530, 549, 571, 592, 612, 629, 654, 
      676, 698, 714, 738, 755, 776, 791
    };

  auto peaks = find_peaks(sim_4, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, sim_5_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      299, 308, 316, 323, 330, 337, 346, 353, 361, 367, 373, 
      380, 387, 394, 401, 409, 416, 425, 431, 437, 443, 451, 
      457, 463, 470, 476, 485, 491, 498, 507, 514, 521, 530, 
      537, 544,553, 559, 568, 575, 582, 591
  };

  auto peaks = find_peaks(sim_5, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, sim_6) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      107, 128, 152, 182, 199, 219, 249, 274, 294, 319, 342, 
      367, 393
    };

  auto peaks = find_peaks(sim_6, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}
