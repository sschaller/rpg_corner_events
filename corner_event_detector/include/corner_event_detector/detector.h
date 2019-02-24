#pragma once

#include <string>
#include "corner_event_detector/event.h"
#include "corner_event_detector/timer.h"

namespace corner_event_detector
{

class Detector
{
public:
  Detector(bool connect = true){};
  virtual ~Detector(){};

  // check if event
  virtual bool isFeature(const corner_event_detector::Event &e) = 0;

protected:
  std::string detector_name_;
};


} // namespace
