// SkillsUSA-Program-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib") 

using namespace std;

// Fibonaccie Function
void fibonacciGenerator(int count, int index, vector<long>& return_vector) {
    if (index == count) {
        return; // End Recursion
    }

    if (index - 1 >= 0) { // Checks index to see if there is ONE accesable value behind it
        if (index - 2 >= 0) { // Checks index to see if there are TWO accesable value behind it
            return_vector.push_back(return_vector[index - 1] + return_vector[index - 2]); // Grabs the two previous numbers, then gets the sum and push that back to the list
            index++;
            fibonacciGenerator(count, index, return_vector);
        }
        else {
            return_vector.push_back(1); // Push back 1 as that will always be the second value
            index++;
            fibonacciGenerator(count, index, return_vector); // Recall function
        }
    }
    else {
        return_vector.push_back(0); // Pushes back 0 as that will always be the first value
        index++;
        fibonacciGenerator(count, index, return_vector); // Recall function
    }
}

string handleRequest(const string& request_string) {
    if (request_string.find("/fibonacci/") != string::npos) {
        try {
            size_t position;
            string response;
            if (request_string.find("/--one-line/") != string::npos) {
                size_t position = request_string.find("/--one-line/");
                int num = stoi(request_string.substr(position + 12)); // 11 since thats the length of the string /fibonacci/

                if (num <= 0) {
                    return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBAD REQUEST - PLEASE ENTER A NUMBER GREATER THAN 0";
                }

                // Fibonacci Vector variables
                vector<long> fib_vector = {};
                int index = 0;

                fibonacciGenerator(num, index, fib_vector);

                // Produce Result
                ostringstream response;
                response << "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{" << endl << "sequence: ";
                for (long fib : fib_vector) {
                    response << to_string(fib) << ", ";
                }
                response << "}" << endl;

                return response.str();
            }
            else if (request_string.find("/--numbering/") != string::npos) {
                size_t position = request_string.find("/--numbering/");
                int num = stoi(request_string.substr(position + 13)); // 11 since thats the length of the string /fibonacci/

                if (num <= 0) {
                    return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBAD REQUEST - PLEASE ENTER A NUMBER GREATER THAN 0";
                }

                // Fibonacci Vector variables
                vector<long> fib_vector = {};
                int index = 0;

                fibonacciGenerator(num, index, fib_vector);

                // Produce Result
                ostringstream response;
                response << "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{" << endl << "sequence: ";
                index = 1;
                for (long fib : fib_vector) {
                    response << index << ":" << to_string(fib) << ", ";
                    index++;
                }
                response << "}" << endl;

                return response.str();
            }
            else if (request_string.find("/--last-only/") != string::npos) {
                size_t position = request_string.find("/--last-only/");
                int num = stoi(request_string.substr(position + 13)); // 11 since thats the length of the string /fibonacci/

                if (num <= 0) {
                    return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBAD REQUEST - PLEASE ENTER A NUMBER GREATER THAN 0";
                }

                // Fibonacci Vector variables
                vector<long> fib_vector = {};
                int index = 0;

                fibonacciGenerator(num, index, fib_vector);

                // Produce Result
                ostringstream response;
                response << "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{" << endl << "sequence: ";
                response << to_string(fib_vector.back());
                response << "}" << endl;

                return response.str();
            }
        }
        catch (...) {
            // Catch any other bad errors
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBAD REQUEST :[";
        }
        // If /fibonacci/ isn't found
        return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNOT FOUND";
    }
    
}

int main()
{
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    // Port Setup 
    SOCKET server_fd = socket(AF_INET, SOCK_STREAM,0);
    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    std::cout << "Server runnning on http://localhost:8080\n";

    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    while (true) {
        SOCKET client_fd = accept(server_fd, nullptr, nullptr);
        char buffer[1024] = { 0 };
        recv(client_fd, buffer, sizeof(buffer), 0);
        string response = handleRequest(buffer);
        send(client_fd, response.c_str(), response.size(), 0);
        closesocket(client_fd);
    }
    WSACleanup();
}

