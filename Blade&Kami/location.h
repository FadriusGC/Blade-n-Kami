#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <vector>

class Location {
 public:
  int id_;
  std::string name_;
  std::string description_;
  std::string detailed_description_;  // Ïîäðîáíîå îïèñàíèå äëÿ "Îñìîòðåòüñÿ"
  std::vector<int> connections_;
  std::string enemy_id_;
  std::string object_id_;  // ID îáúåêòà â ëîêàöèè (chest, merchant, altar)
  bool object_used_;       // Ôëàã èñïîëüçîâàíèÿ îáúåêòà (äëÿ ñóíäóêîâ)
  Location(int id, const std::string& name, const std::string& desc,
           const std::string& detailed_desc, const std::vector<int>& conn,
           const std::string& enemy_id, const std::string& object_id = "");
};

#endif  // LOCATION_H_
