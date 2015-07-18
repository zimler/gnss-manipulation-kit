#include "Utils/BaseTest.h"
#include "Common/File.h"

namespace Greis
{
    namespace Tests
    {
        BaseTest::BaseTest()
        {

        }

        BaseTest::~BaseTest()
        {

        }

        void BaseTest::SetUp()
        {
            sLogger.Info("Connecting to the test database...");
            this->_connection = Common::Connection::FromSettings("Db");
            sLogger.Info(QString("{host: %1, port: %2, database: %3, user: %4}")
                .arg(this->_connection->Hostname)
                .arg(this->_connection->Port)
                .arg(this->_connection->DatabaseName)
                .arg(this->_connection->Username));
            this->_connection->Connect();

            this->_connection->DbHelper()->ExecuteQuery("SET autocommit=0;");

            sLogger.Info("Starting a new transaction...");
            ASSERT_TRUE(this->_connection->Database().driver()->hasFeature(QSqlDriver::Transactions));
            bool transactionStarted = this->_connection->Database().transaction();
            if (!transactionStarted)
            {
                auto errText = this->_connection->Database().lastError().text();
                throw Common::Exception("Failed to start a database transaction: " + errText);
            }
            sLogger.Info("SetUp Succeeded...");
        }

        void BaseTest::TearDown()
        {
            this->_connection->Database().rollback();
            sLogger.Info("Transaction has been reverted.");
        }

        const std::shared_ptr<Common::Connection>& BaseTest::Connection() const
        {
            return this->_connection;
        }

        QString BaseTest::ResolvePath(const QString& fileName) const
        {
            QString baseDir = QCoreApplication::applicationDirPath();
            QString fullPath1(baseDir + "/../../../TestData/" + fileName);
            if (QFile::exists(fullPath1))
            {
                return fullPath1;
            }

            QString fullPath2 = baseDir + "/../../TestData/" + fileName;
            if (QFile::exists(fullPath2))
            {
                return fullPath2;
            }

            throw Common::Exception(QString("File %1 does not exist. Checked pathes: %2 %3.").arg(fileName).arg(fullPath1).arg(fullPath2));
        }

        QByteArray BaseTest::ReadJpsBinary(const QString& fileName) const
        {
            QByteArray binaryData;
            auto file = Common::File::OpenReadBinary(fileName);
            binaryData = file->readAll();
            int i;
            for (i = 0; i < binaryData.size(); i++)
            {
                if (binaryData.at(i) != '\0')
                {
                    break;
                }
            }
            binaryData.remove(0, i);
            return binaryData;
        }

    }
}
