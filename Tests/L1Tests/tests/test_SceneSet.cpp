#include <gtest/gtest.h>
#include "SceneSet.h"
#include "ServiceMock.h"
#include <gmock/gmock.h>

using namespace WPEFramework::Plugin;
using ::testing::Return;

class SceneSetTest : public ::testing::Test {
protected:
    SceneSet* sceneSet;

    void SetUp() override {
        sceneSet = new SceneSet();
    }

    void TearDown() override {
        delete sceneSet;
    }
};

TEST_F(SceneSetTest, Construction) {
    ASSERT_NE(sceneSet, nullptr);
}


TEST_F(SceneSetTest, Initialize_DefaultConfig) {
    ServiceMock serviceMock;
    EXPECT_CALL(serviceMock, ConfigLine()).WillOnce(Return("{"refAppName":"rdk-reference-app"}"));
    EXPECT_CALL(serviceMock, AddRef()).Times(1);
    std::string result = sceneSet->Initialize(&serviceMock);
    EXPECT_EQ(result, "");
}

TEST_F(SceneSetTest, Deinitialize_CallsRelease) {
    ServiceMock serviceMock;
    EXPECT_CALL(serviceMock, ConfigLine()).WillOnce(Return("{\"refAppName\":\"rdk-reference-app\"}"));
    EXPECT_CALL(serviceMock, AddRef()).Times(1);
    sceneSet->Initialize(&serviceMock);
    EXPECT_CALL(serviceMock, Release()).Times(1);
    sceneSet->Deinitialize(&serviceMock);
}

