typedef map<string, string> Properties

enum UserType {
 	kManagered,
 	kExternal
}

struct User {
 	1: required string name,
 	2: required UserType type
}

enum RoleType {
	kPrivate,
	kProtected,
	kPublic
}

struct Role {
	1: required string name,
	2: RoleType type
}

enum PrivilegeType {
	kList,
	kRead,
	kWrite
}

struct Entity {
	1: string scheme,
	2: string path, 
	3: string query //part1=1,3&part2=2&part3=3&part4=3
}

struct Privilege {
	1: PrivilegeType type,
	2: list<Entity> entities
}

struct AuthStatus {
	1: i32 code,
	2: string message
}

struct UserInfo {
	1: User user
	2: string token
	3: Properties properties
}

struct RoleInfo {
	1: Role role;
	2: Properties properties;
}

enum AuditLevel {
	kTrace,
	kInfo,
	kCritical
}

//for audit usage
struct AuditInfo {
	1: required AuditLevel level, 
	2: required string user, // who
	3: required string action, // do what
	4: required string entity, //to whom
	5: optional string date, //when
	6: optional Properties detail //in json's format
}

struct AuditCriteria {
	1: string condition, //key can be user, action, entity, date, only level is kCritical is avaliable
	2: i32 offset,
	3: i32 limit,
	4: string order
}

service AclService {
	AuthStatus validateUser(1:User user, 2:string password);
	void open(1:User user, 2:string password);
	void close();
	AuthStatus addUser(1:UserInfo userinfo, 2:AuditInfo info);
	AuthStatus removeUser(1:User user, 2:AuditInfo info);
	AuthStatus addRole(1:RoleInfo roleInfo, 2:AuditInfo info);
	AuthStatus removeRole(1:Role role, 2:AuditInfo info);
	AuthStatus grantRoleToUser(1:User user, 2:Role role, 3:i64 expireTime, 4:AuditInfo info);
	AuthStatus grantPrivilegeToRole(1:Role role, 2:list<Privilege> privilege, 3:i64 expireTime, 4:AuditInfo info);
	AuthStatus revokeRole(1:User user, 2:Role role, 3:AuditInfo info);
	AuthStatus revokePrivilege(1:Role role, 2:list<Privilege> privilege, 3:AuditInfo info);
	AuthStatus authenticateUser(1:User user, 2:list<Privilege> privilege);
	AuthStatus authenticateRole(1:Role role, 2:list<Privilege> privilege);

    //will force refresh acl tree
    AuthStatus expireUserPrivilege(1:User user);
    AuthStatus expireRolePrivilege(1:Role role);

	RoleInfo getRoleInfo(1:Role role);
	UserInfo getUserInfo(1:User user);
	list<Role> getRolesByUser(1:User user);
	list<Privilege> getPrivilegesByRole(1:Role role);
	list<UserInfo> getUsersHasRole(1:Role role);
	list<RoleInfo> getRolesHasPrivilege(1:Privilege privilege);

	//for audit service
	void addAuditInfo(1:AuditInfo info);
	list<AuditInfo> getAuditInfo(1:AuditCriteria query);
}
