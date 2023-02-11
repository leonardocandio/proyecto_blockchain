#include "app/blockchain.h"
#include "crow/crow_all.h"


//handle get request
crow::json::wvalue handleGET(const crow::request &req, crow::response &res) {
    crow::json::wvalue x;
    x["message"] = "Hello World!";
    return x;
}

crow::json::wvalue handlePOST(const crow::request &req, crow::response &res) {
    crow::json::wvalue x;
    x["message"] = "Hello World!";
    return x;
}

int main(int argc, char *argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
            .methods("GET"_method, "POST"_method)
                    ([](const crow::request &req) {
                        crow::response response;
                        switch (req.method) {
                            case crow::HTTPMethod::GET:
                                response.json_value = handleGET(req, response);
                                return response;
                            case crow::HTTPMethod::POST:
                                response.json_value = handlePOST(req, response);
                                return response;
                            default:
                                return crow::response(404);
                        }
                    });

    app.port(18080).multithreaded().run();
}

