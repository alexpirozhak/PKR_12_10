#include <iostream>
#include <string>

using namespace std;

struct Member {
    string name;
    int attendance;
    Member* left;
    Member* right;

    Member(string name, int attendance) : name(name), attendance(attendance), left(nullptr), right(nullptr) {}
};

struct Leader {
    string name;
    Member* members;
    Leader* left;
    Leader* right;

    Leader(string name) : name(name), members(nullptr), left(nullptr), right(nullptr) {}
};

Leader* addLeader(Leader* root, string name) {
    if (!root) {
        return new Leader(name);
    }
    if (name < root->name) {
        root->left = addLeader(root->left, name);
    } else if (name > root->name) {
        root->right = addLeader(root->right, name);
    }
    return root;
}

Member* addMember(Member* root, string name, int attendance) {
    if (!root) {
        return new Member(name, attendance);
    }
    if (name < root->name) {
        root->left = addMember(root->left, name, attendance);
    } else if (name > root->name) {
        root->right = addMember(root->right, name, attendance);
    }
    return root;
}

void deleteTree(Member* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void deleteTree(Leader* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        deleteTree(root->members);
        delete root;
    }
}

Member* findMember(Member* root, string name) {
    if (!root || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return findMember(root->left, name);
    }
    return findMember(root->right, name);
}

Leader* findLeader(Leader* root, string name) {
    if (!root || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return findLeader(root->left, name);
    }
    return findLeader(root->right, name);
}

Member* findLeastAttendanceMember(Member* root) {
    if (!root) return nullptr;
    Member* leftLeast = findLeastAttendanceMember(root->left);
    Member* rightLeast = findLeastAttendanceMember(root->right);

    Member* least = root;
    if (leftLeast && leftLeast->attendance < least->attendance) {
        least = leftLeast;
    }
    if (rightLeast && rightLeast->attendance < least->attendance) {
        least = rightLeast;
    }
    return least;
}

Leader* removeLeader(Leader* root, string name) {
    if (!root) return nullptr;
    if (name < root->name) {
        root->left = removeLeader(root->left, name);
    } else if (name > root->name) {
        root->right = removeLeader(root->right, name);
    } else {
        if (!root->left) {
            Leader* rightChild = root->right;
            delete root;
            return rightChild;
        } else if (!root->right) {
            Leader* leftChild = root->left;
            delete root;
            return leftChild;
        }
    }
    return root;
}

void printMembers(Member* root) {
    if (root) {
        printMembers(root->left);
        cout << "Member: " << root->name << ", Attendance: " << root->attendance << endl;
        printMembers(root->right);
    }
}

void printLeaders(Leader* root) {
    if (root) {
        printLeaders(root->left);
        cout << "Leader: " << root->name << endl;
        printMembers(root->members);
        printLeaders(root->right);
    }
}

int main() {
    Leader* root = nullptr;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Leader\n";
        cout << "2. Add Member\n";
        cout << "3. Find Member with Least Attendance\n";
        cout << "4. Remove Leader with No Attendance\n";
        cout << "5. Print Tree\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        if (choice == 6) break;

        string leaderName, memberName;
        int attendance;
        switch (choice) {
            case 1:
                cout << "Enter Leader's name: ";
                cin >> leaderName;
                root = addLeader(root, leaderName);
                break;
            case 2:
                cout << "Enter Leader's name: ";
                cin >> leaderName;
                cout << "Enter Member's name: ";
                cin >> memberName;
                cout << "Enter Member's attendance: ";
                cin >> attendance;
                if (Leader* leader = findLeader(root, leaderName)) {
                    leader->members = addMember(leader->members, memberName, attendance);
                } else {
                    cout << "Leader not found.\n";
                }
                break;
            case 3:
                Member* least;
                Leader* leastLeader;
                leastLeader = nullptr;
                least = nullptr;
                //Find the Leader and Member with least attendance.
                break;
            case 4:
                cout << "Enter Leader's name to remove: ";
                cin >> leaderName;
                root = removeLeader(root, leaderName);
                break;
            case 5:
                printLeaders(root);
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
    deleteTree(root);
}



