#ifndef ACL_ACL_TREE_H_
#define ACL_ACL_TREE_H_

#include <vector>
#include <boost/unordered_map.hpp>
#include "openacl/open-acl.h"

_BEG_ACL

struct ValueRange {
  String minValue;
  String maxValue;
};

typedef boost::unordered_map<String, ValueRange> AclQuery;

class AclNode {
  typedef std::map<String, int> AclNodeMap;
  AclTree* tree_;
  std::map<String, int> children_;
  std::vector<Partition> part_list_;
public:
  bool find(const std::vector<std::string>& values, int index);
  bool authenticate(Entity entity, PrivilegeType ptype);
  AclNode* get(const string& key);
};

//scheme://path/to/url event_day=2013,2014,2015,2012:2013; {min, max}
//path to url event_day=2013, 2014
class AclTree {
  std::vector<AclNode> nodes;
  int rootId;
public:
  AclNode &getNode(int index) { return nodes[index]; }
  bool authenticateUser(Privilege & privilegeList);
  static void serializeTree(const AclTree& tree, String& str);
  static AclTree deserialzeTree(String& str); 
  static AclTree mergeTree(const AclTree& left, const AclTree& right);
};

_END_ACL

#endif
