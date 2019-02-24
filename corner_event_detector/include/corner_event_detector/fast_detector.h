#pragma once

#include <deque>

#include <Eigen/Dense>

#include "corner_event_detector/detector.h"

namespace corner_event_detector
{

class FastDetector : public Detector
{
public:
  FastDetector(bool connect = true);
  virtual ~FastDetector();

  bool isFeature(const corner_event_detector::Event &e);

private:
  // SAE
  Eigen::MatrixXd sae_[2];

  // pixels on circle
  int circle3_[16][2];
  int circle4_[20][2];

  // parameters
  static const int sensor_width_ = 240;
  static const int sensor_height_ = 180;
};


} // namespace
