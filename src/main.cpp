#include "app/blockchain.h"
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "sstream"


int main() {
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();

    cors.global()
            .headers("Access-Control-Allow-Origin", "Access-Control-Allow-Headers", "Content-Type");

    blockchain bc;
    bc.addFromFile("../data/transactions.csv");

    CROW_ROUTE(app, "/blocks")
            .methods("GET"_method)
                    ([&bc]() {
                        crow::json::wvalue x;
                        x["blocks"] = crow::json::load(bc.jsonify());
                        crow::response res(x);
                        std::cout << bc.getSize();
                        return res;
                    });

    CROW_ROUTE(app, "/blocks")
            .methods("POST"_method)
                    ([&bc](const crow::request &req) {
                        crow::json::rvalue x = crow::json::load(req.body);
                        if (!x) {
                            return crow::response(400);
                        }
                        dynamic_array<transaction *> transactions;
                        for (auto &t: x["transactions"]) {
                            transactions.push_back(new transaction(
                                    t["step"].i(),
                                    t["type"].s(),
                                    t["amount"].d(),
                                    t["nameOrig"].s(),
                                    t["oldbalanceOrg"].d(),
                                    t["newbalanceOrig"].d(),
                                    t["nameDest"].s(),
                                    t["oldbalanceDest"].d(),
                                    t["newbalanceDest"].d())
                            );
                        }
                        try {
                            bc.addBlock(transactions);
                        } catch (std::exception &e) {
                            return crow::response(400, e.what());
                        }
                        auto r = crow::json::wvalue({{"newBlock", bc.getLastBlock()->jsonify()}});
                        return crow::response(r);
                    });
    CROW_ROUTE(app, "/transactions")
            .methods("POST"_method)
                    ([&bc](const crow::request &req) {
                         crow::json::rvalue body = crow::json::load(req.body);
                         if (!body) {
                             return crow::response(400);
                         }
                         std::string key = body["key"].s();

                         auto transactions = bc.getTransactionsByKey(key);
                         auto r = crow::json::wvalue({{"transactions", jsonifyArray(transactions)}});
                         return crow::response(r);
                     }

                    );

    app.port(3000).multithreaded().run();
}

