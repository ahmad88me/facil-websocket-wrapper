#ifndef WebSocketWrapper_H
#define WebSocketWrapper_H

#include <iostream>

#include <facil/fio.h>
#include <facil/http/http.h>
#include <facil/cli/fio_cli.h>

using namespace std;

//void def_msg_callback(string s) {
//    cout << "def_msg_callback: "<<s<<endl;
//}

class WebSocketWrapper {
    public:
        WebSocketWrapper();
        //static string A;
        static void (*msg_callback) (string);// = &def_msg_callback;
        static void on_close_websocket(intptr_t uuid, void* udata);
        static void on_open_websocket(ws_s* ws);
        static void handle_websocket_messages(ws_s* ws, fio_str_info_s data, uint8_t is_text);
        static void answer_http_request(http_s* h);
        static void answer_http_upgrade(http_s* h, char* target, size_t len);
        //static void start_listening();
        //static void start_listening(string, string );
        static void start_listening(string addr, string port, short num_of_workers, short num_of_threads);


        //        static void start_listening();
};

#endif
