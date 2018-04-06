#include "../server.h"

// Forward message to every person in client's chatroom
void forward_msg(Client &clientObj, string msg) {

    // Formatting
    string newMsg = magenta_bold;
    newMsg += clientObj.username;
    newMsg += ": \33[0m" + msg + "\n";
    size_t size = get_file_size(CONNECTION);

    fstream fp;
    fp.open(CONNECTION, ios::in | ios::binary);

    Client readObj;
    while((size_t)fp.tellg() < size) {

        fp.read((char*)&readObj, sizeof(readObj));
        // Other members of client's current chatroom
        if(readObj.sockFD != clientObj.sockFD &&
        !strcmp(readObj.chatroom, clientObj.chatroom)
        && readObj.state == LOGGED_IN)

            send_msg(readObj.sockFD, newMsg.c_str(), newMsg.size() + 1);
    }
    fp.close();
}
