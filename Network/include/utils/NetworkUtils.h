#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

namespace NetworkUtils {


    int send_all_data(int socketFD, const char* buffer, size_t total_length);
    int send_framed_json(int socketFD, const char* json_data);
    int recieve_all_data(int sockfd, char* buffer, size_t total_length);
    std::string recieve_framed_json(int socketFD);


}


#endif //NETWORK_UTILS_H