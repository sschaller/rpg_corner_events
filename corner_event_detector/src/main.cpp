#include <iostream>     // std::cout, std::fixed
#include <fstream>
#include <iomanip>      // std::setprecision
#include <float.h>

#include "corner_event_detector/detector.h"
#include "corner_event_detector/harris_detector.h"
#include "corner_event_detector/fast_detector.h"

template <class EventTimeFile = double, class EventPixelFile = uint16_t>
bool loadAllEvents(const std::string file_path, std::vector<corner_event_detector::Event> &event_vec)
{
    std::ifstream file(file_path);

    // checks to see if file opended
    if (file.fail())
    {
        std::cout << "Error opening file" << std::endl;
        return false;
    }

    // Get the number of events

    size_t n = 0;
    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);
        ++n;
    }
    file.clear();
    file.seekg(0, std::ios::beg);

    std::cout << "Reserving " << n << " events" << std::endl;

    // Preallocate vectors
    event_vec.reserve(n);

    // Event vec must be empty
    event_vec.clear();

    size_t i_event = 0;
    while (!file.eof() && i_event < n) { // maximum number of events reached
        ++i_event;
        EventTimeFile t;
        EventPixelFile x,y;
        bool p;

        file >> t >> x >> y >> p;

        event_vec.push_back({.ts = t, .x = x, .y = y, .polarity = p});
    }

    file.close();
    return true;
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
      std::cerr << "Usage: " << argv[0] << " harris/fast folder_path/" << std::endl;
      return 1;
  }

  // load parameter
  std::string feature_type = argv[1];

  // create feature detecotr
  corner_event_detector::Detector* detector;
  if (feature_type == "harris")
  {
    std::cout << "Using Harris detector." << std::endl;
    detector = new corner_event_detector::HarrisDetector;
  }
  else if (feature_type == "fast")
  {
    std::cout << "Using fast detector." << std::endl;
    detector = new corner_event_detector::FastDetector;
  }
  else
  {
    std::cerr << "Feature type '" << feature_type.c_str() << "' is unknown." << std::endl;
    return 1;
  }

  std::string events_folder = argv[2];
  
  std::vector<corner_event_detector::Event> events;
  loadAllEvents(events_folder + "events.txt", events);
  size_t n_event = events.size();

  std::cout << "Start classifying." << std::endl;
  std::ofstream file (events_folder+"classification.txt");
  size_t i_event = 0;
  for (std::vector<corner_event_detector::Event>::iterator it = events.begin(); it != events.end(); it++) {
    bool corner = detector->isFeature(*it);
    file << (corner ? "1" : "0") << std::endl;
    if(i_event%1000000==0) std::cout << "Event: " << i_event << " / " << n_event << std::fixed << std::setprecision(2) << " (" << (float)i_event/n_event << "%)" << std::endl;
    i_event++;
  }
  file.close();

  delete detector;

  return 0;
}

