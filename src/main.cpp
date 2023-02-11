#include "app/blockchain.h"
#include "crow.h"
#include "sstream"

//handle get request
std::string handleGET(const crow::request &req, crow::response &res, blockchain &bc) {
    std::stringstream ss;
    ss << R"({"blocks" : )" << bc.jsonify() << "}";
    std::cout << ss.str();
    return ss.str();
}

crow::json::wvalue handlePOST(const crow::request &req, crow::response &res, blockchain &bc) {
    crow::json::wvalue x;
    x["message"] = "Hello Wojjjj!";
    return x;
}

int main(int argc, char *argv[]) {
    crow::SimpleApp app;
    blockchain bc;
    bc.addBlock("First block");
    bc.addFromFile("../data/transactions_debug.csv");


    CROW_ROUTE(app, "/blocks")
            .methods("GET"_method, "POST"_method)
                    ([&bc](const crow::request &req) {
                        crow::response response;
                        response.add_header("Access-Control-Allow-Origin", "*");
                        response.add_header("Access-Control-Allow-Headers", "Content-Type");
                        switch (req.method) {
                            case crow::HTTPMethod::GET:
                                response.write(handleGET(req, response, bc));
                                break;
                            case crow::HTTPMethod::POST:
                                break;
                        }
                        return response;
                    });

    app.port(3000).multithreaded().run();
}

