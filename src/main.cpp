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
            .methods("GET"_method)([&bc]() {
                crow::json::wvalue x({{"blocks", crow::json::load(bc.jsonify())}});
                return crow::response(x);
            });

    CROW_ROUTE(app, "/blocks")
            .methods("POST"_method)([&bc](const crow::request &req) {
                crow::json::rvalue x = crow::json::load(req.body);
                if (!x) {
                    return crow::response(400);
                }
                dynamic_array<transaction *> transactions;
                for (auto const &t: x["transactions"]) {
                    transactions.push_back(new transaction(
                            (unsigned short) t["step"].i(),
                            t["type"].s(),
                            t["amount"].d(),
                            t["nameOrig"].s(),
                            t["oldbalanceOrg"].d(),
                            t["newbalanceOrig"].d(),
                            t["nameDest"].s(),
                            t["oldbalanceDest"].d(),
                            t["newbalanceDest"].d()));
                }
                try {
                    bc.addBlock(transactions.begin(), transactions.end());
                } catch (...) {
                    return crow::response(400);
                }
                auto r = crow::json::wvalue({{"newBlock", crow::json::load(bc.getLastBlock()->jsonify())}});
                return crow::response(r);
            });
    CROW_ROUTE(app, "/recalculo").methods("GET"_method)([&bc]() {
        bc.recalculo();
        crow::json::wvalue x({{"blocks", crow::json::load(bc.jsonify())}});
        return crow::response(x);
    });

    CROW_ROUTE(app, "/transactions")
            .methods("POST"_method)([&bc](const crow::request &req) {
                crow::json::rvalue body = crow::json::load(req.body);
                if (!body) {
                    return crow::response(400);
                }
                std::string param{};
                std::string type{};
                size_t limit{};
                size_t rangeLow{};
                size_t rangeHigh{};

                if (body.has("param")) {
                    param = body["param"].s();
                }
                if (body.has("type")) {
                    type = body["type"].s();
                }
                if ((type == "max" || type == "min") && body.has("limit")) {
                    limit = body["limit"].i();
                }
                if (type == "range" && body.has("rangeLow") && body.has("rangeHigh")) {
                    rangeLow = body["rangeLow"].i();
                    rangeHigh = body["rangeHigh"].i();
                }
                auto transactions = bc.getTransactionsByParamType(param, type, limit, rangeLow, rangeHigh);
                auto r = crow::json::wvalue({{"transactions", crow::json::load(jsonifyArray(transactions))}});
                return crow::response(r);
            });

    app.port(3000).multithreaded().run();
}
