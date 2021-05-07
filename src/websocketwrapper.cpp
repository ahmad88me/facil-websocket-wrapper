#include "websocketwrapper.hpp"

WebSocketWrapper::WebSocketWrapper() {
    int i;
}

/* Free the nickname, if any. */
void WebSocketWrapper::on_close_websocket(intptr_t uuid, void* udata) {
    cout << "Closing the websocket connection\n";
}

void WebSocketWrapper::on_open_websocket(ws_s* ws) {
    cout << "Opening websocket connection\n";
}

/* Received a message from a client, format message for chat . */
void WebSocketWrapper::handle_websocket_messages(ws_s* ws, fio_str_info_s data,
        uint8_t is_text) {
    FIOBJ nickname = (FIOBJ)websocket_udata_get(ws);
    fio_str_info_s n = fiobj_obj2cstr(nickname);
    /* allocates a dynamic string. knowing the buffer size is faster */
    FIOBJ msg = fiobj_str_buf(n.len + 2 + data.len);
    fiobj_str_write(msg, n.data, n.len);
    //    cout << "msg1: "<<msg<<endl;
    fiobj_str_write(msg, ": ", 2);
    //    cout << "msg2: "<<msg<<endl;
    fiobj_str_write(msg, data.data, data.len);
    //    cout << "msg3: "<<msg<<endl;
    //cout << "data.data: "<< data.data <<endl;
    //*((void* (string)) (WebSocketWrapper::msg_callback))("ab");
    //WebSocketWrapper::A = "123";
    //WebSocketWrapper::msg_callback = &def_msg_callback;
    (*WebSocketWrapper::msg_callback)(data.data);
    //    (*WebSocketWrapper::msg_callback)(string(data.data));
    //    cout << "data: "<< n.data<<endl;
    //fio_publish(.channel = CHAT_CHANNEL, .message = fiobj_obj2cstr(msg));
    fiobj_free(msg);
    (void)(ws);
    (void)(is_text);
}



/* Answers simple HTTP requests */
void WebSocketWrapper::answer_http_request(http_s* h) {
    http_set_header2(h, (fio_str_info_s) {
        .data = "Server", .len = 6
    },
    (fio_str_info_s) {
        .data = "facil.example", .len = 13
    });
    http_set_header(h, HTTP_HEADER_CONTENT_TYPE, http_mimetype_find((char*)"txt", 3));
    /* this both sends the response and frees the http handler. */
}

/* tests that the target protocol is "websockets" and upgrades the connection */
void WebSocketWrapper::answer_http_upgrade(http_s* h, char* target, size_t len) {
    /* test for target protocol name */
    if (len != 9 || memcmp(target, "websocket", 9)) {
        http_send_error(h, 400);
        return;
    }
    fio_str_info_s path = fiobj_obj2cstr(h->path);
    fio_str_info_s body = fiobj_obj2cstr(h->body);
    http_upgrade2ws(h, .on_open = WebSocketWrapper::on_open_websocket, .on_close = WebSocketWrapper::on_close_websocket,
                    .on_message = WebSocketWrapper::handle_websocket_messages);
}

void WebSocketWrapper::start_listening(string addr, string port, short num_of_workers, short num_of_threads) {
    //cout << "hello\n\n" << addr << " | "<<port<<endl;
    //void WebSocketWrapper::start_listening() {
    //    const char* addr_chars = "localhost";
    //    const char* port_chars = "3000";
    //    const char* addr_chars = addr.c_str();
    //    const char* port_chars = port.c_str();
    if (http_listen(port.c_str(), addr.c_str(),
                    .on_request = WebSocketWrapper::answer_http_request,
                    .on_upgrade = WebSocketWrapper::answer_http_upgrade) == -1) {
        perror("Couldn't listen for HTTP / WebSocket connections");
        exit(1);
    }
    fio_start(.threads = num_of_threads,  .workers = num_of_workers);
    fio_cli_end();
}
//void WebSocketWrapper::start_listening() {
//    if (http_listen("3000", "localhost",
//                    .on_request = WebSocketWrapper::answer_http_request,
//                    .on_upgrade = WebSocketWrapper::answer_http_upgrade) == -1) {
//        perror("Couldn't listen for HTTP / WebSocket connections");
//        exit(1);
//    }
//    fio_start(.threads = 2, .workers = 2);
//    fio_cli_end();
//}

//void WebSocketWrapper::msg_callback(string s) {
//    cout << "In msg callback: "<<s<<endl;
//}

