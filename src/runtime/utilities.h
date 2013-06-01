_BEG_ACL
class Utilites {
public:
  static String toToken(const String& password);
  static Entity getEntity();
  static String jsonEncode(std::map<String, String> properties);
  static std::map<String, String> properties jsonDecode(const String &json);
};
_END_ACL
