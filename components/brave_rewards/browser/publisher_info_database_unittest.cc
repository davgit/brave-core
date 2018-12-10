/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <fstream>
#include <streambuf>

#include "brave/components/brave_rewards/browser/publisher_info_database.h"

#include "base/files/file_path.h"
#include "base/files/scoped_temp_dir.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "sql/database.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --PublisherInfoDatabaseTest.*

namespace brave_rewards {

// Test data directory, relative to source root
const base::FilePath::CharType kTestDataRelativePath[] =
  FILE_PATH_LITERAL("brave/vendor/bat-native-ledger/test/data");

class PublisherInfoDatabaseTest : public ::testing::Test {
 protected:
  PublisherInfoDatabaseTest() {
    // You can do set-up work for each test here
  }

  ~PublisherInfoDatabaseTest() override {
    // You can do clean-up work that doesn't throw exceptions here
  }

  // If the constructor and destructor are not enough for setting up and
  // cleaning up each test, you can use the following methods

  void SetUp() override {
    // Code here will be called immediately after the constructor (right before
    // each test)

    base::ScopedTempDir temp_dir_;
    ASSERT_TRUE(temp_dir_.CreateUniqueTempDir());
    base::FilePath db_file =
      temp_dir_.GetPath().AppendASCII("PublisherInfoDatabaseTest.db");

    publisher_info_database_ = std::make_unique<PublisherInfoDatabase>(db_file);
    ASSERT_TRUE(publisher_info_database_);

    db_ = publisher_info_database_->GetDB();
    ASSERT_TRUE(db_);
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right before the
    // destructor)
  }

  // Objects declared here can be used by all tests in the test case
  std::string GetMockDataPath(const std::string& filename) {
    base::FilePath path(kTestDataRelativePath);
    path = path.AppendASCII(filename);
    return path.value();
  }

  std::unique_ptr<PublisherInfoDatabase> publisher_info_database_;

  sql::Database db_;
};

TEST_F(PublisherInfoDatabaseTest, InsertContributionInfoTest) {
  ContributionInfo info;
  info.probi = "12345678901234567890123456789012345678901234";
  info.month = ledger::PUBLISHER_MONTH::JANUARY;
  info.year = 1970;
  info.category = ledger::REWARDS_CATEGORY::AUTO_CONTRIBUTE;
  info.date = base::Time::UnixEpoch();
  info.publisher_key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  bool success = publisher_info_database_->InsertContributionInfo(info);
  EXPECT_TRUE(success);

  sql::Statement info_sql(db_.GetUniqueStatement(
    "SELECT publisher_id FROM publisher_info WHERE publisher_id=?"));

  info_sql.BindString(0, info.publisher_key);

  EXPECT_TRUE(info_sql.Step());
}

TEST_F(PublisherInfoDatabaseTest, GetTipsTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, InsertOrUpdatePublisherInfoTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetPublisherInfoTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetPanelPublisherTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, RestorePublishersTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, InsertOrUpdateActivityInfoTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetActivityListTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, InsertOrUpdateMediaPublisherInfoTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetMediaPublisherInfoTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, InsertOrUpdateRecurringDonationTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetRecurringDonationsTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, RemoveRecurringTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetCurrentVersionTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, VacuumTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, GetDiagnosticInfoTest) {
  EXPECT_TRUE(false);
}

// private
TEST_F(PublisherInfoDatabaseTest, CreateContributionInfoTableTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateContributionInfoIndexTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreatePublisherInfoTableTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateActivityInfoTableTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateActivityInfoIndexTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateMediaPublisherInfoTableTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateRecurringDonationTableTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, CreateRecurringDonationIndexTest) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, MigrateV1toV2Test) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, MigrateV2toV3Test) {
  EXPECT_TRUE(false);
}

TEST_F(PublisherInfoDatabaseTest, EnsureCurrentVersion) {
  EXPECT_TRUE(false);
}

}  // namespace brave_rewards
