#include <QApplication>
#include <QPushButton>
#include "app/blockchain.h"
#include "iostream"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    blockchain b;
    b.addBlock("block1");
    b.addBlock("block2");
    std::cout << "Blockchain is valid: " << b.isChainValid() << std::endl;
    QPushButton button("blockchain", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
