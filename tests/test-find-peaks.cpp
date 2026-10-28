#include "peak-finding.hpp"
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
  std::vector<double> SDP_20250610 = load_data(DATA_DIR "/2025-06-10_SDP.csv");
  std::vector<double> SDP_20250818 =
      load_data(DATA_DIR "/2025-08-18_SDP_2.csv");
  std::vector<double> SDP_20250819 =
      load_data(DATA_DIR "/2025-08-19_SDP_1.csv");
  std::vector<double> SDP_20251104 =
      load_data(DATA_DIR "/2025-11-04_SDP_2.csv");
  std::vector<double> SDP_20251105 =
      load_data(DATA_DIR "/2025-11-05_SDP_2.csv");
  std::vector<double> P20_20260528 = load_data(DATA_DIR "/2026-05-28_P20.csv");
};

TEST_F(PeakFindingTest, SDP_20250610_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      6,   16,  19,  31,  42,  53,  61,  66,  75,  85,  97,  99,
      106, 113, 120, 130, 139, 147, 158, 168, 181, 191, 201, 210,
      215, 223, 232, 241, 248, 256, 263, 270, 281, 289, 298, 307,
      315, 324, 331, 340, 347, 356, 364, 372, 382, 389, 397};

  auto peaks = find_peaks(SDP_20250610, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, SDP_20250818_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      428, 451, 455, 460, 468, 472, 476, 480, 483, 486, 490, 493,
      498, 502, 506, 510, 515, 519, 523, 529, 538, 541, 549, 553,
      558, 562, 565, 568, 571, 575, 577, 580, 584, 591, 594, 597};

  auto peaks = find_peaks(SDP_20250818, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, SDP_20250819_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      247, 263, 287, 303, 319, 336, 350, 369, 396, 416, 432,
      447, 464, 479, 494, 508, 531, 546, 560, 583, 598, 609,
      622, 635, 657, 670, 691, 715, 734, 753, 768, 775, 787};

  auto peaks = find_peaks(SDP_20250819, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, SDP_20251104_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {
      257, 273, 296, 313, 325, 334, 344, 354, 368, 378, 391, 405, 415, 428, 438,
      447, 459, 472, 485, 494, 509, 520, 529, 544, 554, 570, 580, 592, 608, 615,
      628, 637, 650, 664, 674, 680, 687, 698, 712, 732, 749, 760, 770, 785};

  auto peaks = find_peaks(SDP_20251104, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, SDP_20251105_peaks) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {10,  26,  75,  123, 157, 182, 222,
                                        270, 294, 333, 381, 415, 447, 484};

  auto peaks = find_peaks(SDP_20251105, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}

TEST_F(PeakFindingTest, P20_20260528) {
  PeakConditions conditions;
  conditions.set_prominence(0.01);
  conditions.set_distance(2);

  std::vector<size_t> expected_peaks = {14, 28, 51, 71};

  auto peaks = find_peaks(P20_20260528, conditions);
  std::vector<size_t> peak_indices;
  for (const auto &p : peaks)
    peak_indices.push_back(p.peak);

  EXPECT_EQ(peak_indices, expected_peaks);
}
