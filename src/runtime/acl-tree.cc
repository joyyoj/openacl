#include "runtime/acl-tree.h"

_BEG_ACL

void AclTree::build() {
	
}
bool AclTree::authenticateUser(const std::vector<Privilege> & privilege) {
	for (int i = 0; i < privilege.size(); ++i) {
		
	}
}

class OpenAclImpl {
public:
	void roleHasPrivilege(RoleInfo roleInfo, Privilege privilege) {
		struct Record;
		Record record;
		//dt: /data/udwtable/pb/voice ?event_day=20130301,20130302;event_hour=20130201 write
		//
		//dt: /data              = 1,2,4,7
		//dt: /data/udwtable
		//dt: /data/udwtable/pb
		//dt: /data/udwtable/pb/voice
		getUserPrivileges();
		//user tree
		//updateUserTree();
		record.path is prefix of entity 
	}
};
//sort privilege tree 
struct EntityTreeNode {
	EntityTreeNode* children;
	int children_count;
	int code;//1, 2, 4, 7
	string name;
	string parent;
private:
	~EntityTreeNode() {
		stack<EntityTreeNode*> stack;
		push_all(this, stack);
		while (!stack.emtpy()) {
			EntityTreeNode* node = stack.pop();
			push_all(stack, nodes);
			for (int childIndex = 0; childIndex < children_count; ++childIndex) {
				nodes.push_back(node->children[childIndex]);
			}
			node->children[childIndex] = NULL;
			node->children_count = 0;
			delete node;	
		}		
	}

	void checkPath(list<Privilege> privileges) {

		if (path is prefix and this->code & code) {
			checkPath(path, path.next());
		}
		for (child : children) {

		}
	}
};

removeEntity();
//path 
00000|00000000| 000000000
scheme/db/table/ query

1                   
dt:/data       
dt:/data/udwtable

path entity_id parent_id
dt:/data 1      0
dt:/data/udwtable 2     1
int main() {
	AclTree tree;
	tree.build();
	std::vector<Privilege> privilegeList;
	Privilege priv;
	priv.entities.push_back(Entity("path/to/event", "event_day=20130101:20150501"));
	privilegeList.push_back();
	tree.authenticateUser();
}
}


_END_ACL
