#include <QFile>
#include <QDebug>
#ifndef AESFILECRYPTO_H
#define AESFILECRYPTO_H

class AesFileCrypto
{
public:
    AesFileCrypto(const QByteArray &key, const QByteArray &iv = QByteArray());
    bool encryptFile(const QString &inputFile, const QString &outputFile);
    bool decryptFile(const QString &inputFile, const QString &outputFile);

private:
    QByteArray m_key;
    QByteArray m_iv;
};

#endif // AESFILECRYPTO_H
