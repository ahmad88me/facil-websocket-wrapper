#include "websocketwrapper.hpp"
#include<iostream>
#include <facil/fio.h>
#include <facil/http/http.h>
#include <facil/cli/fio_cli.h>


using namespace std;

///* Free the nickname, if any. */
//static void on_close_websocket(intptr_t uuid, void* udata) {
//    cout << "Closing the websocket connection\n";
//}

//static void on_open_websocket(ws_s* ws) {
//    cout << "Opening websocket connection\n";
//}

///* Received a message from a client, format message for chat . */
//static void handle_websocket_messages(ws_s* ws, fio_str_info_s data,
//                                      uint8_t is_text) {
//    FIOBJ nickname = (FIOBJ)websocket_udata_get(ws);
//    fio_str_info_s n = fiobj_obj2cstr(nickname);
//    /* allocates a dynamic string. knowing the buffer size is faster */
//    FIOBJ msg = fiobj_str_buf(n.len + 2 + data.len);
//    fiobj_str_write(msg, n.data, n.len);
//    //    cout << "msg1: "<<msg<<endl;
//    fiobj_str_write(msg, ": ", 2);
//    //    cout << "msg2: "<<msg<<endl;
//    fiobj_str_write(msg, data.data, data.len);
//    //    cout << "msg3: "<<msg<<endl;
//    cout << "data.data: "<< data.data <<endl;
//    //    cout << "data: "<< n.data<<endl;
//    //fio_publish(.channel = CHAT_CHANNEL, .message = fiobj_obj2cstr(msg));
//    fiobj_free(msg);
//    (void)(ws);
//    (void)(is_text);
//}



///* Answers simple HTTP requests */
//static void answer_http_request(http_s* h) {
//    http_set_header2(h, (fio_str_info_s) {
//        .data = "Server", .len = 6
//    },
//    (fio_str_info_s) {
//        .data = "facil.example", .len = 13
//    });
//    http_set_header(h, HTTP_HEADER_CONTENT_TYPE, http_mimetype_find((char*)"txt", 3));
//    /* this both sends the response and frees the http handler. */
//    http_send_body(h, (char*)"This is a simple Websocket chatroom example.", 44);
//}

///* tests that the target protocol is "websockets" and upgrades the connection */
//static void answer_http_upgrade(http_s* h, char* target, size_t len) {
//    /* test for target protocol name */
//    if (len != 9 || memcmp(target, "websocket", 9)) {
//        http_send_error(h, 400);
//        return;
//    }
//    fio_str_info_s path = fiobj_obj2cstr(h->path);
//    fio_str_info_s body = fiobj_obj2cstr(h->body);
//    // Websocket upgrade will use our existing response.
//    //    if (http_upgrade2ws(
//    //                h, .on_open = on_open_websocket, .on_close = on_close_websocket,
//    //                .on_message = handle_websocket_messages, .udata = (void*)n))
//    http_upgrade2ws(h, .on_open = on_open_websocket, .on_close = on_close_websocket,
//                    .on_message = handle_websocket_messages);
//}


void custom_callback(string s) {
    cout << "This is a custom callback\n";
    cout << "received message: "<<s<<endl;
}

void (*WebSocketWrapper::msg_callback) (string) =  &custom_callback;


int main() {
    string port, addr;
    port = "3000";
    addr = "localhost";
    cout << "Web Socket\n";
    //    int uuid = websocket_connect("ws://localhost:8765", nullptr);
    //    cout << "uuid: "<<uuid<<endl;
    //    if (http_listen("3000", "localhost",
    //                    .on_request = answer_http_request,
    //                    .on_upgrade = answer_http_upgrade) == -1) {
    //        perror("Couldn't listen for HTTP / WebSocket connections");
    //        exit(1);
    //    }
    //    fio_start(.threads =2, .workers = 2);
    //    fio_cli_end();
    WebSocketWrapper::start_listening(addr, port, 1, 1);
    //WebSocketWrapper::start_listening();
    return 0;
}
